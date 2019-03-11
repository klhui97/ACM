STL Library Examples
====================

Initizalize
^^^^^^^^^^^

Fill an array

.. code-block:: cpp

	bool visited[100];
	memset(visited, false, sizeof visited);


Sorting
^^^^^^^^

Simple example

.. code-block:: cpp

	bool compare(int a, int b) { 
		return (a > b); // TRUE = put a into the font, FALSE = put b into the font
	}

	int a[10] = {0};
	sort(a, a+10, compare);


Map
^^^

string map example

.. code-block:: cpp

	map<string, int> m;
	m["key"] = 23;
	cout << "Key: " << m.find("key")->first << endl;
	cout << "Value: " << m.find("key")->second << endl;
	cout << "isEmpty: " << m.find("key")->first.empty() << endl;

Set
^^^

.. code-block:: cpp

	set<int> s;
	s.insert(300);
	s.insert(333);
	s.insert(233);
	s.insert(433);
	for(set<int>::iterator it = s.begin(); it != s.end(); it++) {
		cout << *it << "\n";
	}
