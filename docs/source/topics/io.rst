Input / Output
==============

read line, spliting
-------------------

split char by space.

.. code-block:: cpp

    char str[] = "- This, a sample string.";
    char *pch;
    pch = strtok (str," ,.-");
    while (pch != NULL) {
        cout << pch << endl;
        pch = strtok(NULL, " ,.-");
    }

Convert a string back to input stream (similar as cin)

.. code-block:: cpp

    int input;
    stringstream ss("23 45 63 47 23");
    while(ss >> input) {
        cout << input << endl;
    }


This example is used to count the number words in line separated by space.

.. code-block:: cpp

    char buf[16384];
    gets(buf); // get line
    for (n = 0, p = buf;;) {
        if (*p == ' ') {
            n++;
        }else if (*p == '\0') {
            n++;
            break;
        }
        p++;
    }
    cout << "The numbers of elements: " << n << endl;

precision
---------

.. code-block:: cpp

    #include <iomanip>
    double x = 0;
    cout << fixed << setprecision(3) << x << endl;
    // 0.000% is printed out
