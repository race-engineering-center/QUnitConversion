#ifndef QLINEARFUNCTION_H
#define QLINEARFUNCTION_H

#include <QtGlobal>

/**
 * @brief The QLinearFunction class describes a linear function
 * with a format of Y = k*X + b
 */
class QLinearFunction
{
public:
    /**
     * @brief Default constructor
     * @details Constructs a default invalid (k = 0) linear function
     */
    QLinearFunction();

    /**
     * @brief Constructor
     * @param k K value
     * @param b B value
     */
    QLinearFunction(double k, double b);

    /**
     * @brief Checks if linear function is valid, i.e. if k != 0
     * @return `true` if function is valid, `false` otherwise
     */
    bool isValid() const;

    /**
     * @brief Reverses current linear function so X = k*Y + b
     * @return an object of type QLinearFunction containing inversed function
     * @details This function doesn't perform validity check so applying it to
     * invalid function will cause division by zero
     */
    QLinearFunction inversed() const;

    /**
     * @brief Function value
     * @param x function argument
     * @return value of a function with an argument `x`
     */
    double y(double x);


    double k() const;
    void setK(double value);

    double b() const;
    void setB(double value);

    static QLinearFunction combined(const QLinearFunction & first, const QLinearFunction & second);

protected:
    double m_k;
    double m_b;
};

#endif // QLINEARFUNCTION_H
