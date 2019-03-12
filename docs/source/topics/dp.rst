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
