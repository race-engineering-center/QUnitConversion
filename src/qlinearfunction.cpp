#include "qlinearfunction.h"

QLinearFunction::QLinearFunction()
{
    m_k = 0;
    m_b = 0;
}

QLinearFunction::QLinearFunction(double k, double b)
{
    m_k = k;
    m_b = b;
}

bool QLinearFunction::isValid() const
{
    return !qFuzzyIsNull(m_k);
}

QLinearFunction QLinearFunction::inversed() const
{
    if (!isValid()) return {};
    return {1. / m_k, -m_b / m_k};
}

double QLinearFunction::y(double x)
{
    return x * m_k + m_b;
}

double QLinearFunction::k() const
{
    return m_k;
}

void QLinearFunction::setK(double value)
{
    m_k = value;
}

double QLinearFunction::b() const
{
    return m_b;
}

void QLinearFunction::setB(double value)
{
    m_b = value;
}

QLinearFunction QLinearFunction::combined(const QLinearFunction &first, const QLinearFunction &second)
{
    return {first.k() * second.k(), second.k() * first.b() + second.b()};
}
