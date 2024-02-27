#include "qaliasdictionarytests.h"

#include <map>
#include <set>

QAliasDictionaryTests::QAliasDictionaryTests(QObject *parent) : QObject(parent)
{

}

void QAliasDictionaryTests::basicTests()
{
    QAliasDictionary<QMap, QSet> dictionary;
    QVERIFY(dictionary.isEmpty());
    dictionary.addAlias("name", "alias");
    dictionary.addAlias("name", "alias2");
    dictionary.addAlias("name", "alias3");

    QVERIFY(!dictionary.isEmpty());
    QVERIFY(dictionary.name("name") == "name");
    QVERIFY(dictionary.name("alias") == "name");
    QVERIFY(dictionary.name("alias2") == "name");
    QVERIFY(dictionary.name("alias3") == "name");
    QVERIFY(dictionary.name("alias4").isEmpty());

    dictionary.addAlias("name2", "alias_for_name2");
    dictionary.addAlias("name2", "alias2_for_name2");
    QVERIFY(dictionary.name("alias_for_name2") == "name2");
    QVERIFY(dictionary.name("alias2_for_name2") == "name2");
    QVERIFY(dictionary.name("alias2_for_name3").isEmpty());

    auto aliases = dictionary.aliases("name");
    QVERIFY(aliases.contains("alias"));
    QVERIFY(aliases.contains("alias2"));
    QVERIFY(aliases.contains("alias3"));
}

void QAliasDictionaryTests::templateTests()
{
    QAliasDictionary<std::map, std::set> dictionary;
    QVERIFY(dictionary.isEmpty());
    dictionary.addAlias("name", "alias");
    dictionary.addAlias("name", "alias2");
    dictionary.addAlias("name", "alias3");

    QVERIFY(!dictionary.isEmpty());
    QVERIFY(dictionary.name("name") == "name");
    QVERIFY(dictionary.name("alias") == "name");
    QVERIFY(dictionary.name("alias2") == "name");
    QVERIFY(dictionary.name("alias3") == "name");
    QVERIFY(dictionary.name("alias4").isEmpty());

    dictionary.addAlias("name2", "alias_for_name2");
    dictionary.addAlias("name2", "alias2_for_name2");
    QVERIFY(dictionary.name("alias_for_name2") == "name2");
    QVERIFY(dictionary.name("alias2_for_name2") == "name2");
    QVERIFY(dictionary.name("alias2_for_name3").isEmpty());

    auto aliases = dictionary.aliases("name");
    QVERIFY(aliases.contains("alias"));
    QVERIFY(aliases.contains("alias2"));
    QVERIFY(aliases.contains("alias3"));
}

void QAliasDictionaryTests::fromJsonTests()
{
    QAliasDictionary<QMap, QSet> dictionary;
    QFile file(":testdata/aliases.json");
    QVERIFY(file.exists());
    QVERIFY(file.open(QIODevice::ReadOnly));

    dictionary.loadFromJson(QJsonDocument::fromJson(file.readAll()).object());
    QVERIFY(dictionary.name("m") == "m");
    QVERIFY(dictionary.name("meters") == "m");
    QVERIFY(dictionary.name("meter") == "m");
    QStringList aliases = dictionary.aliases("m");
    QVERIFY(aliases.contains("meters"));
    QVERIFY(aliases.contains("meter"));
    QVERIFY(dictionary.name("km/h") == "km/h");
    QVERIFY(dictionary.name("kmph") == "km/h");
    QVERIFY(dictionary.name("kmh") == "km/h");

    QVERIFY(dictionary.contains("m"));
    QVERIFY(dictionary.contains("meters"));
    QVERIFY(dictionary.contains("meter"));

    QVERIFY(dictionary.contains("km/h"));
    QVERIFY(dictionary.contains("kmph"));
    QVERIFY(dictionary.contains("kmh"));
}
