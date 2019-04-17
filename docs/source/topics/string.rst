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

.. code-block:: cpp

    int LongestCommonSubSequence(char* X, char* Y)
    {
        int m = strlen(X);
        int n = strlen(Y);
        int L[m + 1][n + 1];
        int i, j;

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

        return L[m][n];
    }

Suffix Array
------------

kasai’s Algorithm
+++++++++++++++++

LCP Array is an array of size n (like Suffix Array). A value lcp[i] indicates length of the longest common prefix of the suffixes inexed by suffix[i] and suffix[i+1]. suffix[n-1] is not defined as there is no suffix after it.

Code:

.. code-block:: cpp

    struct suffix 
    { 
        int index;
        int rank[2];
    }; 

    int cmp(struct suffix a, struct suffix b) 
    { 
        return (a.rank[0] == b.rank[0])? (a.rank[1] < b.rank[1] ?1: 0): 
            (a.rank[0] < b.rank[0] ?1: 0); 
    } 

    vector<int> buildSuffixArray(string txt, int n) 
    {
        struct suffix suffixes[n]; 

        for (int i = 0; i < n; i++) 
        { 
            suffixes[i].index = i; 
            suffixes[i].rank[0] = txt[i] - 'a'; 
            suffixes[i].rank[1] = ((i+1) < n)? (txt[i + 1] - 'a'): -1; 
        } 

        sort(suffixes, suffixes+n, cmp);
        int ind[n];

        for (int k = 4; k < 2*n; k = k*2) 
        { 
            int rank = 0; 
            int prev_rank = suffixes[0].rank[0]; 
            suffixes[0].rank[0] = rank; 
            ind[suffixes[0].index] = 0; 
    
            for (int i = 1; i < n; i++) 
            { 
                if (suffixes[i].rank[0] == prev_rank && 
                        suffixes[i].rank[1] == suffixes[i-1].rank[1]) 
                { 
                    prev_rank = suffixes[i].rank[0]; 
                    suffixes[i].rank[0] = rank; 
                } 
                else
                { 
                    prev_rank = suffixes[i].rank[0]; 
                    suffixes[i].rank[0] = ++rank; 
                } 
                ind[suffixes[i].index] = i; 
            } 

            for (int i = 0; i < n; i++) 
            { 
                int nextindex = suffixes[i].index + k/2; 
                suffixes[i].rank[1] = (nextindex < n)? 
                                    suffixes[ind[nextindex]].rank[0]: -1; 
            }
            sort(suffixes, suffixes+n, cmp); 
        } 
        vector<int>suffixArr; 
        for (int i = 0; i < n; i++) 
            suffixArr.push_back(suffixes[i].index); 
        return  suffixArr; 
    } 

    vector<int> kasai(string txt, vector<int> suffixArr) 
    { 
        int n = suffixArr.size(); 
    
        vector<int> lcp(n, 0);
        vector<int> invSuff(n, 0); 

        for (int i=0; i < n; i++) 
            invSuff[suffixArr[i]] = i; 

        int k = 0; 

        for (int i=0; i<n; i++) 
        {
            if (invSuff[i] == n-1) 
            { 
                k = 0; 
                continue; 
            }
            int j = suffixArr[invSuff[i]+1]; 
    
            while (i+k<n && j+k<n && txt[i+k]==txt[j+k]) 
                k++; 
    
            lcp[invSuff[i]] = k;
            if (k>0) 
                k--; 
        }
        return lcp; 
    }

    void printArr(vector<int>arr, int n) 
    { 
        for (int i = 0; i < n; i++) 
            cout << arr[i] << " "; 
        cout << endl; 
    }

Example:

.. code-block:: cpp

    string str = "banana"; 
    
    vector<int>suffixArr = buildSuffixArray(str, str.length());
    int n = suffixArr.size();

    cout << "Suffix Array : \n"; 
    vector<int>lcp = kasai(str, suffixArr);
    for (int i = 0; i < n; i++) 
        cout << &str[suffixArr[i]] << "      " << lcp[i] << "\n"; 