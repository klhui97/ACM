String
======

Pattern Searching
-----------------

Knuth Morris Pratt algorithm
++++++++++++++++++++++++++++

https://www.geeksforgeeks.org/kmp-algorithm-for-pattern-searching/

Example:

.. code-block:: cpp

    char txt[] = "ABABDABACDABABCABAB"; 
    char pat[] = "ABABCABAB"; 
    KnuthMorrisPrattSearch(pat, txt);


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

Longest Common Subsequence
--------------------------

Examples:
LCS for input Sequences “ABCDGH” and “AEDFHR” is “ADH” of length 3.
LCS for input Sequences “AGGTAB” and “GXTXAYB” is “GTAB” of length 4.

https://www.geeksforgeeks.org/cpp-program-for-longest-common-subsequence/

.. code-block:: cpp

    /* Returns length of LCS for X[0..m-1], Y[0..n-1] */
    int LongestCommonSubSequence(char* X, char* Y, int m, int n) 
    { 
        int L[m + 1][n + 1]; 
        int i, j; 
    
        /* Following steps build L[m+1][n+1] in bottom up fashion. Note  
        that L[i][j] contains length of LCS of X[0..i-1] and Y[0..j-1] */
        for (i = 0; i <= m; i++) { 
            for (j = 0; j <= n; j++) { 
                if (i == 0 || j == 0) 
                    L[i][j] = 0; 
    
                else if (X[i - 1] == Y[j - 1]) 
                    L[i][j] = L[i - 1][j - 1] + 1; 
    
                else
                    L[i][j] = max(L[i - 1][j], L[i][j - 1]); 
            } 
        } 
    
        /* L[m][n] contains length of LCS for X[0..n-1] and Y[0..m-1] */
        return L[m][n]; 
    }
