#include "qunitconvertortests.h"
#include "qaliasdictionary.h"

#include <algorithm>

using String = QString;

namespace {

template <template <typename, typename> class Container, typename Key, typename Value>
bool contains(const Container<Key, Value>& container, const Key& key)
{
    return std::find(container.begin(), container.end(), key) != container.end();
}

}

QUnitConvertorTests::QUnitConvertorTests(QObject *parent) : QObject(parent)
{

}

void QUnitConvertorTests::addRuleTest()
{
    QUnitConvertor<String> convertor;
    convertor.addConversionRule(QUnitConversionRule<String>("length", "m", "km", 0.001, 0));
    QVERIFY(convertor.m_families.contains("length"));
    QVERIFY(convertor.m_baseUnitsByFamilies.contains("length"));
    QVERIFY(convertor.m_familiesByUnit.contains("m"));
    QVERIFY(convertor.m_familiesByUnit.contains("km"));
    QVERIFY(convertor.m_familiesByUnit.size() == 2);
    QVERIFY(convertor.m_families.size() == 1);
    QVERIFY(convertor.m_baseUnitsByFamilies.size() == 1);

    convertor.addConversionRule(QUnitConversionRule<String>("length", "m", "cm", 100, 0));
    QVERIFY(convertor.m_familiesByUnit.contains("m"));
    QVERIFY(convertor.m_familiesByUnit.contains("km"));
    QVERIFY(convertor.m_familiesByUnit.contains("cm"));
    QVERIFY(convertor.m_familiesByUnit.size() == 3);
    QVERIFY(convertor.m_families.size() == 1);
    QVERIFY(convertor.m_baseUnitsByFamilies.size() == 1);

    convertor.addConversionRule(QUnitConversionRule<String>("length", "m", "mm", 1000, 0));
    QVERIFY(convertor.m_familiesByUnit.contains("m"));
    QVERIFY(convertor.m_familiesByUnit.contains("km"));
    QVERIFY(convertor.m_familiesByUnit.contains("cm"));
    QVERIFY(convertor.m_familiesByUnit.contains("mm"));
    QVERIFY(convertor.m_familiesByUnit.size() == 4);
    QVERIFY(convertor.m_families.size() == 1);
    QVERIFY(convertor.m_baseUnitsByFamilies.size() == 1);

    // passing existing family with a differnt base unit
    QVERIFY_THROWS_EXCEPTION(std::invalid_argument, convertor.addConversionRule(QUnitConversionRule<String>("length", "km", "m", 1000, 0)));

    // passing a different family with an existing base unit
    QVERIFY_THROWS_EXCEPTION(std::invalid_argument, convertor.addConversionRule(QUnitConversionRule<String>("notlength", "m", "km", 0.001, 0)));

    // passing the same conversion once again should work
    convertor.addConversionRule(QUnitConversionRule<String>("length", "m", "mm", 1000, 0));

    // let's make sure that none of containers did change
    QVERIFY(convertor.m_familiesByUnit.size() == 4);
    QVERIFY(convertor.m_families.size() == 1);
    QVERIFY(convertor.m_baseUnitsByFamilies.size() == 1);

    // note "min" here, since we have to make sure that all unit names are different
    // we need to differ minutes from meters
    convertor.addConversionRule(QUnitConversionRule<String>("time", "s", "min", double(1) / 60, 0));
    QVERIFY(convertor.m_families.contains("length"));
    QVERIFY(convertor.m_families.contains("time"));
    QVERIFY(convertor.m_families.size() == 2);
    QVERIFY(convertor.m_familiesByUnit.contains("m"));
    QVERIFY(convertor.m_familiesByUnit.contains("km"));
    QVERIFY(convertor.m_familiesByUnit.contains("cm"));
    QVERIFY(convertor.m_familiesByUnit.contains("mm"));
    QVERIFY(convertor.m_familiesByUnit.contains("s"));
    QVERIFY(convertor.m_familiesByUnit.contains("min"));
    QVERIFY(convertor.m_baseUnitsByFamilies.contains("length"));
    QVERIFY(convertor.m_baseUnitsByFamilies.contains("time"));
    QVERIFY(convertor.m_baseUnitsByFamilies["length"] == "m");
    QVERIFY(convertor.m_baseUnitsByFamilies["time"] == "s");

    auto families = convertor.families();
    QVERIFY(contains(families, String("length")));
    QVERIFY(contains(families, String("time")));

    auto units = convertor.units("length");
    QCOMPARE(units.size(), 4);
    QVERIFY(contains(units, String("m")));
    QVERIFY(contains(units, String("km")));
    QVERIFY(contains(units, String("cm")));
    QVERIFY(contains(units, String("mm")));

    QVERIFY(qFuzzyCompare(convertor.convert(0, "m", "km"), 0));
    QVERIFY(qFuzzyCompare(convertor.convert(50, "m", "km"), 0.05));
    QVERIFY(qFuzzyCompare(convertor.convert(50, "km", "m"), 50000));
    QVERIFY(qFuzzyCompare(convertor.convert(500, "cm", "m"), 5));
    QVERIFY(qFuzzyCompare(convertor.convert(500, "cm", "km"), 0.005));
    QVERIFY(qFuzzyCompare(convertor.convert(500, "m", "m"), 500));

    auto conversions = convertor.conversions("m");
    QVERIFY(contains(conversions, String("m")));
    QVERIFY(contains(conversions, String("km")));
    QVERIFY(contains(conversions, String("cm")));
    QVERIFY(contains(conversions, String("mm")));
    QVERIFY(conversions.size() == 4);

    conversions = convertor.conversions("mm");
    QVERIFY(contains(conversions, String("m")));
    QVERIFY(contains(conversions, String("km")));
    QVERIFY(contains(conversions, String("cm")));
    QVERIFY(contains(conversions, String("mm")));
    QVERIFY(conversions.size() == 4);

    conversions = convertor.conversions("mmmm");
    QVERIFY(conversions.empty());

    QVERIFY(convertor.family("m") == "length");
    QVERIFY(convertor.family("km") == "length");
    QVERIFY(convertor.family("mmmmm") == String());

}

void QUnitConvertorTests::setAliasesTest()
{
    QUnitConvertor<String> convertor;
    convertor.addConversionRule(QUnitConversionRule<String>("length", "m", "km", 0.001, 0));
    QVERIFY(convertor.canConvert("m", "km"));
    QVERIFY(convertor.canConvert("km", "m"));
    QVERIFY(!convertor.canConvert("km", "meter"));

    QAliasDictionary<String> aliases;
    aliases.addAlias("m", "m");
    aliases.addAlias("m", "meter");
    aliases.addAlias("m", "meters");

    convertor.setAliases(aliases);

    QVERIFY(convertor.canConvert("km", "meter"));
    QVERIFY(convertor.canConvert("km", "meters"));

}

void QUnitConvertorTests::addAliasTest()
{
    QUnitConvertor<String> convertor;
    convertor.addConversionRule(QUnitConversionRule<String>("length", "m", "km", 0.001, 0));

    QAliasDictionary<String> aliases;
    aliases.addAlias("m", "m");
    aliases.addAlias("m", "meter");

    convertor.setAliases(aliases);

    QVERIFY(convertor.canConvert("km", "meter"));
    QVERIFY(!convertor.canConvert("km", "meters"));

    convertor.addAlias("m", "meters");

    QVERIFY(convertor.canConvert("km", "meters"));

}

