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


Modulation
----------

| xy mod n = (x mod n)(y mod n) mod n
| x^y mod n = (x mod n) ^ y mod n

.. code-block:: cpp

    // return a^b mod c
    unsigned ModExp(unsigned a, unsigned b, unsigned c) {
        unsigned tmp;

        if(a==0) return 0;
        a%=c;

        if(b==1) return a;
        if(b==0) return (1);
        
        tmp = ModExp(a, b>>1, c);
        tmp = (tmp*tmp)%c;

        if (b&1) tmp = (tmp*a)%c;

        return tmp;
    }

Extended Euclidean algorithms(to find gcd)
------------------------------------------

| a * x + b * y = gcd(a, b);

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
