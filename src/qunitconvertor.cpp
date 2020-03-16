#include "qunitconvertor.h"

QUnitConvertor::QUnitConvertor()
{

}

bool QUnitConvertor::canConvert(const QString &in, const QString &out) const
{
    return convert(in, out).isValid();
}

QLinearFunction QUnitConvertor::convert(const QString &in, const QString &out) const
{
    return QLinearFunction();
}

double QUnitConvertor::convert(double value, const QString &in, const QString &out) const
{
    QLinearFunction function = convert(in, out);
    if (!function.isValid())
        return NAN;
    return function.y(value);
}
