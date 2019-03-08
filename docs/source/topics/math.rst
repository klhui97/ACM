Math
====

Math Library
^^^^^^^^^^^^

.. code-block:: cpp

#include <math.h>

    double floor(double x); // deduce x to next smallest integer
    double ceil(double x); // raise x to next largest integer
    double fabs(double x); // absolute value of x

    double sqrt(double x); // square roots of x
    double exp(double x); // compute e^x
    double log(double x); // base log e
    double log10(double x); // base log 10
    double pow(double x, double y); // compute x^y


Greatest Common Divisor(GCD)
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. code-block:: cpp

    int gcd(int a, int b) {
        if (a == 0)
            return b;
        return gcd(b % a, a);
    }
