Math
====

Math Library
------------

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


Extended Euclidean algorithms(to find gcd)
------------------------------------------

.. code-block:: cpp

    int gcdExtended(int a, int b, int *x, int *y) 
    { 
        // Base Case 
        if (a == 0) 
        { 
            *x = 0; 
            *y = 1; 
            return b; 
        } 
    
        int x1, y1; // To store results of recursive call 
        int gcd = gcdExtended(b%a, a, &x1, &y1); 
    
        // Update x and y using results of recursive 
        // call 
        *x = y1 - (b/a) * x1; 
        *y = x1; 
    
        return gcd; 
    }
