#include "qunitconvertortests.h"

QUnitConvertorTests::QUnitConvertorTests(QObject *parent) : QObject(parent)
{

}

void QUnitConvertorTests::addRuleTest()
{
    QUnitConvertor convertor;
    convertor.addConversionRule(QUnitConversionRule("length", "m", "km", 0.001, 0));
    QVERIFY(convertor.m_families.contains("length"));
    QVERIFY(convertor.m_baseUnitsByFamilies.contains("length"));
    QVERIFY(convertor.m_familiesByUnit.contains("m"));
    QVERIFY(convertor.m_familiesByUnit.contains("km"));
    QVERIFY(convertor.m_familiesByUnit.size() == 2);
    QVERIFY(convertor.m_families.size() == 1);
    QVERIFY(convertor.m_baseUnitsByFamilies.size() == 1);

    convertor.addConversionRule(QUnitConversionRule("length", "m", "cm", 100, 0));
    QVERIFY(convertor.m_familiesByUnit.contains("m"));
    QVERIFY(convertor.m_familiesByUnit.contains("km"));
    QVERIFY(convertor.m_familiesByUnit.contains("cm"));
    QVERIFY(convertor.m_familiesByUnit.size() == 3);
    QVERIFY(convertor.m_families.size() == 1);
    QVERIFY(convertor.m_baseUnitsByFamilies.size() == 1);

    convertor.addConversionRule(QUnitConversionRule("length", "m", "mm", 1000, 0));
    QVERIFY(convertor.m_familiesByUnit.contains("m"));
    QVERIFY(convertor.m_familiesByUnit.contains("km"));
    QVERIFY(convertor.m_familiesByUnit.contains("cm"));
    QVERIFY(convertor.m_familiesByUnit.contains("mm"));
    QVERIFY(convertor.m_familiesByUnit.size() == 4);
    QVERIFY(convertor.m_families.size() == 1);
    QVERIFY(convertor.m_baseUnitsByFamilies.size() == 1);

    // passing existing family with a differnt base unit
    QVERIFY_EXCEPTION_THROWN(convertor.addConversionRule(QUnitConversionRule("length", "km", "m", 1000, 0)), std::invalid_argument);

    // passing a different family with an existing base unit
    QVERIFY_EXCEPTION_THROWN(convertor.addConversionRule(QUnitConversionRule("notlength", "m", "km", 0.001, 0)), std::invalid_argument);

    // passing the same conversion once again should work
    convertor.addConversionRule(QUnitConversionRule("length", "m", "mm", 1000, 0));

    // let's make sure that none of containers did change
    QVERIFY(convertor.m_familiesByUnit.size() == 4);
    QVERIFY(convertor.m_families.size() == 1);
    QVERIFY(convertor.m_baseUnitsByFamilies.size() == 1);

    // note "min" here, since we have to make sure that all unit names are different
    // we need to differ minutes from meters
    convertor.addConversionRule(QUnitConversionRule("time", "s", "min", double(1) / 60, 0));
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

    QStringList families = convertor.families();
    QVERIFY(families.contains("length"));
    QVERIFY(families.contains("time"));

    QStringList units = convertor.units("length");
    qDebug()<<units;
    QVERIFY(units.size() == 4);
    QVERIFY(units.contains("m"));
    QVERIFY(units.contains("km"));
    QVERIFY(units.contains("cm"));
    QVERIFY(units.contains("mm"));

    QVERIFY(qFuzzyCompare(convertor.convert(0, "m", "km"), 0));
    QVERIFY(qFuzzyCompare(convertor.convert(50, "m", "km"), 0.05));
    QVERIFY(qFuzzyCompare(convertor.convert(50, "km", "m"), 50000));
    QVERIFY(qFuzzyCompare(convertor.convert(500, "cm", "m"), 5));
    QVERIFY(qFuzzyCompare(convertor.convert(500, "cm", "km"), 0.005));
    QVERIFY(qFuzzyCompare(convertor.convert(500, "m", "m"), 500));
}

void QUnitConvertorTests::fromJsonTest()
{
    QUnitConvertor convertor;
    QFile file(QCoreApplication::applicationDirPath() + "/../testdata/conversion_rules.json");
    QVERIFY(file.exists());
    QVERIFY(file.open(QIODevice::ReadOnly));
    QJsonObject object = QJsonDocument::fromJson(file.readAll()).object();
    convertor.loadFromJson(object);

    QVERIFY(qFuzzyCompare(convertor.convert(0, "m", "km"), 0));
    QVERIFY(qFuzzyCompare(convertor.convert(50, "m", "km"), 0.05));
    QVERIFY(qFuzzyCompare(convertor.convert(50, "km", "m"), 50000));
    QVERIFY(qFuzzyCompare(convertor.convert(500, "cm", "m"), 5));
    QVERIFY(qFuzzyCompare(convertor.convert(500, "cm", "km"), 0.005));

    QVERIFY(qFuzzyCompare(convertor.convert(100, "C", "K"), 373.15));
    QVERIFY(qFuzzyCompare(convertor.convert(-40, "C", "F"), -40));
}
