#include "qaliasdictionarytests.h"

QAliasDictionaryTests::QAliasDictionaryTests(QObject *parent) : QObject(parent)
{

}

void QAliasDictionaryTests::basicTests()
{
    QAliasDictionary<QString> dictionary;
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

void QAliasDictionaryTests::basicStdStringTests()
{
    QAliasDictionary<std::string> dictionary;
    QVERIFY(dictionary.isEmpty());
    dictionary.addAlias("name", "alias");
    dictionary.addAlias("name", "alias2");
    dictionary.addAlias("name", "alias3");

    QVERIFY(!dictionary.isEmpty());
    QVERIFY(dictionary.name("name") == "name");
    QVERIFY(dictionary.name("alias") == "name");
    QVERIFY(dictionary.name("alias2") == "name");
    QVERIFY(dictionary.name("alias3") == "name");
    QVERIFY(dictionary.name("alias4").size() == 0);

    dictionary.addAlias("name2", "alias_for_name2");
    dictionary.addAlias("name2", "alias2_for_name2");
    QVERIFY(dictionary.name("alias_for_name2") == "name2");
    QVERIFY(dictionary.name("alias2_for_name2") == "name2");
    QVERIFY(dictionary.name("alias2_for_name3").size() == 0);

    auto aliases = dictionary.aliases("name");
    QVERIFY(aliases.contains("alias"));
    QVERIFY(aliases.contains("alias2"));
    QVERIFY(aliases.contains("alias3"));
}
