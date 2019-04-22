Dynamic Programming
===================

0/1 Knapsack problem
--------------------

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

Longest increasing subsequence
------------------------------

Example: 1 7 3 7 3 6 5
LIS = 1 -> 3 -> 3 -> 6, maxLength = 4

Remove repeated item:
Change b_search if(target >= dp[mid]) to if(target > dp[mid])
LIS = 1 -> 3 -> 6, maxLength = 3

.. code-block:: cpp

    int dp[maxn], a[maxn];

    int b_search(int n, int target)
    {
        int low = 0, high = n - 1;
        while(low <= high)
        {
            int mid = (low + high)/2;
            if(target >= dp[mid])
                low = mid + 1;
            else
                high = mid - 1;
        }
        return low;
    }
    
    int solve(int *a, int n)
    {
        int len = 1;
        dp[0] = a[0];
        for (int i = 1; i < n; ++i)
        {
            int pos = b_search(len, a[i]);
            dp[pos] = a[i];
            len = max(len, pos + 1);
        }
        return len;
    }