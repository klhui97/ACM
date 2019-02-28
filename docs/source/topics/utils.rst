Utility Function
================

is_number
^^^^^^^^^^^

.. code-block:: cpp

    bool is_number(const std::string& s) {
        std::string::const_iterator it = s.begin();
        while (it != s.end() && std::isdigit(*it)) ++it;
        return !s.empty() && it == s.end();
    }

postfix to infix
^^^^^^^^^^^^^^^^

postfix: abcd^e-fgh*+^*+i-
infix: ((a+(b*(((c^d)-e)^(f+(g*h)))))-i)

.. code-block:: cpp

    string exp = "abcd^e-fgh*+^*+i-"; 
    cout << getInfix(exp) << endl;

Code:

.. code-block:: cpp

    bool isOperand(char x) 
    { 
    return (x >= 'a' && x <= 'z') || 
            (x >= 'A' && x <= 'Z'); 
    } 

    string getInfix(string exp) 
    { 
        stack<string> s; 
    
        for (int i=0; exp[i]!='\0'; i++) 
        {
            if (isOperand(exp[i])) 
            { 
            string op(1, exp[i]); 
            s.push(op); 
            }
            else
            { 
                string op1 = s.top(); 
                s.pop(); 
                string op2 = s.top(); 
                s.pop(); 
                s.push("(" + op2 + exp[i] + 
                    op1 + ")"); 
            } 
        }
        return s.top(); 
    }

infix to postfix
^^^^^^^^^^^^^^^^

infix: a+b*(c^d-e)^(f+g*h)-i
postfix: abcd^e-fgh*+^*+i-

Example:

.. code-block:: cpp

    string exp = "a+b*(c^d-e)^(f+g*h)-i";
    infixToPostfix(exp);

Code:

.. code-block:: cpp

    int prec(char c)
    {
        if (c == '^')
            return 3;
        else if (c == '*' || c == '/')
            return 2;
        else if (c == '+' || c == '-')
            return 1;
        else
            return -1;
    }

    void infixToPostfix(string s)
    {
        stack<char> st;
        st.push('N');
        int l = s.length();
        string ns;
        for (int i = 0; i < l; i++)
        {
            // If the scanned character is an operand, add it to output string.
            if ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z'))
                ns += s[i];
            else if (s[i] == '(')
                st.push('(');
            else if (s[i] == ')')
            {
                while (st.top() != 'N' && st.top() != '(')
                {
                    char c = st.top();
                    st.pop();
                    ns += c;
                }
                if (st.top() == '(')
                {
                    char c = st.top();
                    st.pop();
                }
            }
            else
            {
                while (st.top() != 'N' && prec(s[i]) <= prec(st.top()))
                {
                    char c = st.top();
                    st.pop();
                    ns += c;
                }
                st.push(s[i]);
            }
        }

        while (st.top() != 'N')
        {
            char c = st.top();
            st.pop();
            ns += c;
        }

        cout << ns << endl;
    }