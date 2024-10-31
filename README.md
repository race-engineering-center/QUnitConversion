# QUnitConversion

## Overview

`QUnitConversion` is a simple lightweight library providing tools for runtime unit conversion built on top of Qt Framework.

`QUnitConversion` stores units as strings grouped by "family" (for example length or temperature). 
Each family has its own base unit, conversion inside a family is performed by converting through base unit
providing conversion from any unit to any other unit in a family.

Note that each unit should have a unique name, as long as conversion is unit name-based.

`QUnitConversion` supports aliases for unit names, see aliases example below.

## Documentation

Documentation is available [here](https://beardedbeaver.github.io/QUnitConversion/index.html)

## Examples

### Basic usage:

```cpp
QUnitConvertor<QString> convertor;

// fill the convertor instance with rules
convertor.addConversionRule(QUnitConversionRule("length", "m", "km", 0.001, 0));
convertor.addConversionRule(QUnitConversionRule("length", "m", "cm", 100, 0));

// you can convert a single value
double km = convertor.convert(50, "km", "m");   // returns value of a 50 km converted to meters

// or get a linear function that holds conversion from one unit to another
// to apply this conversion to many numbers without finding a conversion each time 
QLinearFunction convertFunction = convertor.convert("m", "km");
std::vector<double> meters;
// meters is filled here...
std::vector<double> kilometers;
for (double m: meters)
    kilometers.push_back(convertFunction.y(m));
```

### Aliases:

`QUnitConversion` supports aliases for units with possible conversion on the fly, so you km/h, kmph and kmh 
will be converted to m/s properly. 

```
// TODO: add updated alias example
```

## License

`QUnitConversion` is distributed under MIT license

## Repo contents

| Directory           | Contents                       |
|---------------------|--------------------------------|
| `./QUnitConversion` | Library source code.           |
| `./tests`           | Unittests code.                |

Copyright Dmitriy Linev 2020-2024
