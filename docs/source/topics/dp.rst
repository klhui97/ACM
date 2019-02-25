Dynamic Programming
===================

0/1 Knapsack problem
^^^^^^^^^^^^^^^^^^^^

* Gvien set of items with weight and value
* Maximize the value in C capacity
* where total weight <= C

- i: row (item)
- j: col (capacity)
- values[i]: value of item i
- weights[i]: weight of item i

.. code-block:: cpp

    int dp[total_items + 1][maximum_capacity + 1];
    memset(dp, 0, sizeof dp);
    for (i = 1; i <= total_items; i++) {
        for (j = 0; j <= maximum_capacity; j++) {
            int value = values[i];
            int weight = weights[i];
            if (j - weight >= 0)
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - weight] + value);
            else
                dp[i][j] = dp[i - 1][j];
        }
    }

Pattern Searching
^^^^^^^^^^^^^^^^^

Knuth Morris Pratt algorithm
----------------------------

https://www.geeksforgeeks.org/kmp-algorithm-for-pattern-searching/

.. code-block:: cpp

    void computeLPSArray(char *pat, int M, int *lps)
    {
        int len = 0;
        lps[0] = 0;
        int i = 1;
        while (i < M)
        {
            if (pat[i] == pat[len])
            {
                len++;
                lps[i] = len;
                i++;
            }
            else
            {
                if (len != 0)
                {
                    len = lps[len - 1];
                }
                else
                {
                    lps[i] = 0;
                    i++;
                }
            }
        }
    }

    int KnuthMorrisPrattSearch(char *pat, char *txt)
    {
        int M = strlen(pat);
        int N = strlen(txt);

        int lps[M];

        computeLPSArray(pat, M, lps);

        int i = 0;
        int j = 0;
        while (i < N)
        {
            if (pat[j] == txt[i])
            {
                j++;
                i++;
            }

            if (j == M)
            {
                printf("Found pattern at index %d\n", i - j); 
                // Start of - modified to return
                return i - j;
                // End of - modified to return
                j = lps[j - 1];
            }
            else if (i < N && pat[j] != txt[i])
            {
                if (j != 0)
                    j = lps[j - 1];
                else
                    i = i + 1;
            }
        }
        // Start of - modified to return
        return -1; // if not found
        // End of - modified to return
    }

