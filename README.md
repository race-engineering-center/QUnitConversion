# QUnitConversion

## Overview

`QUnitConversion` is a simple lightweight library providing tools for unit conversion built on top of Qt5 Framework.

`QUnitConversion` stores units as strings grouped by "family" (for example length or temperature). Each family has its own base unit, conversion inside a family is performed by converting through base unit
providing conversion from any unit to any other unit in a family. Conversion rules can be added dynamically
and/or loaded from JSON-formatted string so you can add your own conversions if needed. An example of 
an input JSON file is provided in `/testdata/conversion_rules.json`.

Note that each unit should have a unique name, as long as conversion is unit name-based.

## Example

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

## License

`QUnitConversion` is distributed under MIT license

## Documentation

Documentation can be generated using `doxygen`, doxyfile is provided inside a `src` folder and requires
`dot` tool installed and added to PATH to generate graphs. 

## Repo contents

| Directory     | Contents                       |
|---------------|--------------------------------|
| `./src`       | Source code.                   |
| `./test`      | Unittest code.                 |
| `./testdata`  | Unittest data.                 |

Copyright Dmitriy Linev 2020