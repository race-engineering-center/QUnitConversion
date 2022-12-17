# QUnitConversion

## Overview

`QUnitConversion` is a simple lightweight library providing tools for runtime unit conversion built on top of Qt5 Framework.

`QUnitConversion` stores units as strings grouped by "family" (for example length or temperature). 
Each family has its own base unit, conversion inside a family is performed by converting through base unit
providing conversion from any unit to any other unit in a family. Conversion rules can be added dynamically
and/or loaded from JSON-formatted string so you can add your own conversions if needed. An example of 
an input JSON file is provided in `test/testdata/conversion_rules.json`.

Note that each unit should have a unique name, as long as conversion is unit name-based.

`QUnitConversion` supports aliases for unit names, see aliases example below.

## Documentation

Documentation is available [here](https://beardedbeaver.github.io/QUnitConversion/index.html)

## Examples

### Basic usage:

```cpp
QUnitConvertor convertor;

// fill the convertor instance with rules
convertor.addConversionRule(QUnitConversionRule("length", "m", "km", 0.001, 0));
convertor.addConversionRule(QUnitConversionRule("length", "m", "cm", 100, 0));

// you can convert a single value
double km = convertor.convert(50, "km", "m");   // returns value of a 50 km converted to meters

// or get a linear function that holds conversion from one unit to another
// to apply this convertion to many numbers without finding a conversion each time 
QLinearFunction convertFunction = convertor.convert("m", "km");
std::vector<double> meters;
// meters is filled here...
std::vector<double> kilometers;
for (double m: meters)
    kilometers.push_back(convertFunction.y(m));
```

### Aliases:

`QUnitConversion` supports aliases for units with possible conversion on the fly, so you km/h, kmph and kmh 
will be converted to m/s properly. Also this example illustrates loading conversions and aliases from
JSON-formatted file.

```cpp
QUnitConvertor convertor;

// load conversion rules from JSON
QFile conversions("conversion_rules.json");
conversions.open(QIODevice::ReadOnly);
convertor.loadFromJson(QJsonDocument::fromJson(conversions.readAll()).object());

// load aliases for unit names from JSON
QFile aliases("aliases.json");
aliases.open(QIODevice::ReadOnly);
convertor.loadAliasesFromJson(QJsonDocument::fromJson(aliases.readAll()).object());

double km;
km = convertor.convert(50, "km", "m");   // returns value of a 50 km converted to meters
km = convertor.convert(50, "km", "meter");  // "meter" is an alias for "m" written in loaded json
km = convertor.convert(50, "km", "meters"); // and "meters" a as well
```

## License

`QUnitConversion` is distributed under MIT license

## Repo contents

| Directory           | Contents                       |
|---------------------|--------------------------------|
| `./QUnitConversion` | Library source code.           |
| `./tests`           | Unittests code.                |

Copyright Dmitriy Linev 2020-2022
