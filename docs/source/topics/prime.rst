Prime
=====

Prime - Check if a number is prime
++++++++++++++++++++++++++++++++++

.. code-block:: cpp

    bool is_prime(int n)
    {
        int i, j;
        if (n<4)
            return true;
        if ((n % 2) == 0)
            return false;
        j = (int)sqrt((double)n);
        for (i = 3; i <= j; i += 2)
            if (n%i == 0)
                return 0;
        return true;
    }

Prime - Bitwise Sieve
+++++++++++++++++++++

| Use less based to store if a number is primes
| print all primes less than or equal to maxn

.. code-block:: cpp

    int composite[(maxn>>6)+1];

    bool isPrime(int x){
        return x==2 || (x>2 && (x&1) && !(composite[x>>6]&(1<<((x>>1)&63))));
    }

    void bitwiseSieve() {
        for(int i=3;i<=int(sqrt(maxn));i+=2)
        {
            if(!(composite[i>>6]&(1<<((i>>1)&63)))){
                for(int j=i*i;j<=maxn;j+=i+i)
                    composite[j>>6]|=(1<<((j>>1)&63));
            }
        }

        for (int i = 2; i <= maxn; i++) {
            if (isPrime(i))
                cout << i << " ";
        }
        cout << "\n";
    }


Prime - Sieve Of Eratosthenes
+++++++++++++++++++++++++++++

.. code-block:: cpp

    /* 
    * print all primes less than or equal to N
    */
    void SieveOfEratosthenes(int n)
    {
        bool isprime[n+1];
        memset(isprime, true, sizeof(isprime));

        for (int p=2; p*p<=n; p++)
        {
            if (isprime[p] == true)
            {
                for (int i=p*p; i<=n; i += p)
                    isprime[i] = false;
            }
        }

        for (int p=2; p<=n; p++)
            if (isprime[p])
                cout << p << " ";
        cout << "\n";
    }

Prime factors of a number
+++++++++++++++++++++++++

.. code-block:: cpp

    // A function to print all prime factors of a given number n 
    void primeFactors(int n) 
    { 
        // Print the number of 2s that divide n 
        while (n%2 == 0) 
        { 
            printf("%d ", 2); 
            n = n/2; 
        } 
    
        // n must be odd at this point.  So we can skip  
        // one element (Note i = i +2) 
        for (int i = 3; i <= sqrt(n); i = i+2) 
        { 
            // While i divides n, print i and divide n 
            while (n%i == 0) 
            { 
                printf("%d ", i); 
                n = n/i; 
            } 
        } 
    
        // This condition is to handle the case when n  
        // is a prime number greater than 2 
        if (n > 2) 
            printf ("%d ", n); 
    } 

Prime factors of a big number
+++++++++++++++++++++++++++++

.. code-block:: cpp

    long long n = 1000000000000000000; 
    factorize(n);
    // Output : 	2  18
    //      		5  18
    // Explanation: The prime factors of 1000000000000000000
    // are 2 and 5. The prime factor 2 appears 18 times in 
    // the prime factorization. 5 appears 18 times

.. code-block:: cpp

    // function to calculate all the prime factors and  
    // count of every prime factor 
    void factorize(long long n) 
    { 
        int count = 0; 
    
        // count the number of times 2 divides  
        while (!(n % 2)) { 
            n >>= 1; // equivalent to n=n/2; 
            count++; 
        } 
    
        // if 2 divides it 
        if (count) 
            cout << 2 << "  " << count << endl; 
    
        // check for all the possible numbers that can  
        // divide it 
        for (long long i = 3; i <= sqrt(n); i += 2) { 
            count = 0; 
            while (n % i == 0) { 
                count++; 
                n = n / i; 
            } 
            if (count) 
                cout << i << "  " << count << endl; 
        } 
    
        // if n at the end is a prime number. 
        if (n > 2) 
            cout << n << "  " << 1 << endl; 
    } 