STL Library Examples
====================

Initizalize
^^^^^^^^^^^

Fill an array

.. code-block:: cpp

	bool visited[100];
	memset(visited, false, sizeof visited);


Sorting
^^^^^^^^^^^^

Simple Example

.. code-block:: cpp

	bool compare(int a, int b) { 
		return (a > b); // TRUE = put a into the font, FALSE = put b into the font
	}

	int a[10] = {0};
	sort(a, a+10, compare);


