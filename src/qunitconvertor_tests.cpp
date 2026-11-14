#include <algorithm>

#ifdef QUNITCONV_QT_TESTS
#include <QString>
#endif
#include <gtest/gtest.h>

#include "qunitconvertor.h"

namespace {

template<class Container, class T>
bool contains(const Container &c, const T &value)
{
    return std::find(c.begin(), c.end(), value) != c.end();
}

}

template<typename T>
class QUnitConvertorTest : public ::testing::Test {};

using StringTypes = ::testing::Types<
    std::string
#ifdef QUNITCONV_QT_TESTS
    , QString
#endif
>;
TYPED_TEST_SUITE(QUnitConvertorTest, StringTypes);

TYPED_TEST(QUnitConvertorTest, AddRule)
{
    QUnitConvertor<TypeParam> convertor;
    convertor.addConversionRule(QUnitConversionRule<TypeParam>("length", "m", "km", 0.001, 0));
    ASSERT_TRUE(contains(convertor.families(), TypeParam{"length"}));
    ASSERT_NE(convertor.family("m"), TypeParam{});
    ASSERT_NE(convertor.family("km"), TypeParam{});
    ASSERT_EQ(convertor.families().size(), 1);
    ASSERT_EQ(convertor.baseUnit("length"), "m");

    convertor.addConversionRule(QUnitConversionRule<TypeParam>("length", "m", "cm", 100, 0));
    ASSERT_NE(convertor.family("m"), TypeParam{});
    ASSERT_NE(convertor.family("km"), TypeParam{});
    ASSERT_NE(convertor.family("cm"), TypeParam{});
    ASSERT_EQ(convertor.families().size(), 1);
    ASSERT_EQ(convertor.units("length").size(), 3);

    convertor.addConversionRule(QUnitConversionRule<TypeParam>("length", "m", "mm", 1000, 0));
    ASSERT_NE(convertor.family("m"), TypeParam{});
    ASSERT_NE(convertor.family("km"), TypeParam{});
    ASSERT_NE(convertor.family("cm"), TypeParam{});
    ASSERT_NE(convertor.family("mm"), TypeParam{});
    ASSERT_EQ(convertor.families().size(), 1);
    ASSERT_EQ(convertor.units("length").size(), 4);

    // passing existing family with a different base unit
    ASSERT_THROW(convertor.addConversionRule(
        QUnitConversionRule<TypeParam>("length", "km", "m", 1000, 0)),
        std::invalid_argument
    );

    // passing a different family with an existing base unit
    ASSERT_THROW(convertor.addConversionRule(
        QUnitConversionRule<TypeParam>("notlength", "m", "km", 0.001, 0)),
        std::invalid_argument
    );

    // passing the same conversion once again should work
    convertor.addConversionRule(QUnitConversionRule<TypeParam>("length", "m", "mm", 1000, 0));

    // let's make sure that none of the state changed
    ASSERT_EQ(convertor.families().size(), 1);
    ASSERT_EQ(convertor.units("length").size(), 4);

    // note "min" here, since we have to make sure that all unit names are different
    // we need to differ minutes from meters
    convertor.addConversionRule(QUnitConversionRule<TypeParam>("time", "s", "min", double(1) / 60, 0));
    ASSERT_TRUE(contains(convertor.families(), TypeParam{"length"}));
    ASSERT_TRUE(contains(convertor.families(), TypeParam{"time"}));
    ASSERT_EQ(convertor.families().size(), 2);
    ASSERT_NE(convertor.family("m"), TypeParam{});
    ASSERT_NE(convertor.family("km"), TypeParam{});
    ASSERT_NE(convertor.family("cm"), TypeParam{});
    ASSERT_NE(convertor.family("mm"), TypeParam{});
    ASSERT_NE(convertor.family("s"), TypeParam{});
    ASSERT_NE(convertor.family("min"), TypeParam{});
    ASSERT_EQ(convertor.baseUnit("length"), "m");
    ASSERT_EQ(convertor.baseUnit("time"), "s");

    auto families = convertor.families();
    ASSERT_TRUE(contains(families, TypeParam{"length"}));
    ASSERT_TRUE(contains(families, TypeParam{"time"}));

    auto units = convertor.units("length");
    ASSERT_EQ(units.size(), 4);
    ASSERT_TRUE(contains(units, TypeParam{"m"}));
    ASSERT_TRUE(contains(units, TypeParam{"km"}));
    ASSERT_TRUE(contains(units, TypeParam{"cm"}));
    ASSERT_TRUE(contains(units, TypeParam{"mm"}));

    ASSERT_NEAR(convertor.convert(0, "m", "km"), 0, 1e-10);
    ASSERT_NEAR(convertor.convert(50, "m", "km"), 0.05, 1e-10);
    ASSERT_NEAR(convertor.convert(50, "km", "m"), 50000, 1e-10);
    ASSERT_NEAR(convertor.convert(500, "cm", "m"), 5, 1e-10);
    ASSERT_NEAR(convertor.convert(500, "cm", "km"), 0.005, 1e-10);
    ASSERT_NEAR(convertor.convert(500, "m", "m"), 500, 1e-10);

    auto conversions = convertor.conversions("m");
    ASSERT_TRUE(contains(conversions, TypeParam{"m"}));
    ASSERT_TRUE(contains(conversions, TypeParam{"km"}));
    ASSERT_TRUE(contains(conversions, TypeParam{"cm"}));
    ASSERT_TRUE(contains(conversions, TypeParam{"mm"}));
    ASSERT_EQ(conversions.size(), 4);

    conversions = convertor.conversions("mm");
    ASSERT_TRUE(contains(conversions, TypeParam{"m"}));
    ASSERT_TRUE(contains(conversions, TypeParam{"km"}));
    ASSERT_TRUE(contains(conversions, TypeParam{"cm"}));
    ASSERT_TRUE(contains(conversions, TypeParam{"mm"}));
    ASSERT_EQ(conversions.size(), 4);

    conversions = convertor.conversions("mmmm");
    ASSERT_TRUE(conversions.empty());

    ASSERT_EQ(convertor.family("m"), "length");
    ASSERT_EQ(convertor.family("km"), "length");
    ASSERT_EQ(convertor.family("mmmmm"), TypeParam{});
}

TYPED_TEST(QUnitConvertorTest, SetAliases)
{
    QUnitConvertor<TypeParam> convertor;
    convertor.addConversionRule(QUnitConversionRule<TypeParam>("length", "m", "km", 0.001, 0));
    ASSERT_TRUE(convertor.canConvert("m", "km"));
    ASSERT_TRUE(convertor.canConvert("km", "m"));
    ASSERT_FALSE(convertor.canConvert("km", "meter"));

    QAliasDictionary<TypeParam> aliases;
    aliases.addAlias("m", "m");
    aliases.addAlias("m", "meter");
    aliases.addAlias("m", "meters");

    convertor.setAliases(aliases);

    ASSERT_TRUE(convertor.canConvert("km", "meter"));
    ASSERT_TRUE(convertor.canConvert("km", "meters"));
}

TYPED_TEST(QUnitConvertorTest, AddAlias)
{
    QUnitConvertor<TypeParam> convertor;
    convertor.addConversionRule(QUnitConversionRule<TypeParam>("length", "m", "km", 0.001, 0));

    QAliasDictionary<TypeParam> aliases;
    aliases.addAlias("m", "m");
    aliases.addAlias("m", "meter");

    convertor.setAliases(aliases);

    ASSERT_TRUE(convertor.canConvert("km", "meter"));
    ASSERT_FALSE(convertor.canConvert("km", "meters"));

    convertor.addAlias("m", "meters");

    ASSERT_TRUE(convertor.canConvert("km", "meters"));
}

TYPED_TEST(QUnitConvertorTest, ConvertAliasToSameUnit)
{
    QUnitConvertor<TypeParam> convertor;
    convertor.addConversionRule(QUnitConversionRule<TypeParam>("length", "m", "km", 0.001, 0));
    convertor.addAlias("m", "meter");
    convertor.addAlias("m", "meters");
    convertor.addAlias("km", "kilometer");

    // Alias and its unit name the same unit, so the conversion is identity
    ASSERT_TRUE(convertor.canConvert("meter", "m"));
    ASSERT_TRUE(convertor.canConvert("m", "meter"));
    ASSERT_TRUE(convertor.canConvert("meter", "meters"));
    ASSERT_TRUE(convertor.canConvert("kilometer", "km"));

    ASSERT_NEAR(convertor.convert(500, "meter", "m"), 500, 1e-10);
    ASSERT_NEAR(convertor.convert(500, "m", "meter"), 500, 1e-10);
    ASSERT_NEAR(convertor.convert(500, "meter", "meters"), 500, 1e-10);
    ASSERT_NEAR(convertor.convert(500, "kilometer", "km"), 500, 1e-10);
}

