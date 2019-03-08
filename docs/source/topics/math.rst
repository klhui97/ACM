Math
====

Greatest Common Divisor(GCD)
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. code-block:: cpp

    int gcd(int a, int b) {
        if (a == 0)
            return b;
        return gcd(b % a, a);
    }
