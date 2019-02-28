Utility Function
================

is_number
^^^^^^^^^

.. code-block:: cpp

    bool is_number(const std::string& s) {
        std::string::const_iterator it = s.begin();
        while (it != s.end() && std::isdigit(*it)) ++it;
        return !s.empty() && it == s.end();
    }

expression evalation
^^^^^^^^^^^^^^^^^^^^

Code:

.. code-block:: cpp

    int precedence(char op){ 
        if(op == '+'||op == '-') 
        return 1; 
        if(op == '*'||op == '/') 
        return 2; 
        return 0; 
    } 

    int applyOp(int a, int b, char op){ 
        switch(op){ 
            case '+': return a + b; 
            case '-': return a - b; 
            case '*': return a * b; 
            case '/': return a / b; 
        }
        return a + b; // to hide warning
    }
    
    // Function that returns value of 
    // expression after evaluation. 
    int evaluate(string tokens){ 
        int i; 
        
        // stack to store integer values. 
        stack <int> values; 
        
        // stack to store operators. 
        stack <char> ops; 
        
        for(i = 0; i < tokens.length(); i++){ 
            
            if(tokens[i] == ' ') 
                continue;
            else if(tokens[i] == '('){ 
                ops.push(tokens[i]); 
            }
            else if(isdigit(tokens[i])){ 
                int val = 0; 
                
                while(i < tokens.length() &&  
                            isdigit(tokens[i])) 
                { 
                    val = (val*10) + (tokens[i]-'0'); 
                    i++; 
                } 
                
                values.push(val); 
            }
            else if(tokens[i] == ')') 
            { 
                while(!ops.empty() && ops.top() != '(') 
                { 
                    int val2 = values.top(); 
                    values.pop(); 
                    
                    int val1 = values.top(); 
                    values.pop(); 
                    
                    char op = ops.top(); 
                    ops.pop(); 
                    
                    values.push(applyOp(val1, val2, op)); 
                } 
                
                // pop opening brace. 
                ops.pop(); 
            }
            else
            {
                while(!ops.empty() && precedence(ops.top()) 
                                    >= precedence(tokens[i])){ 
                    int val2 = values.top(); 
                    values.pop(); 
                    
                    int val1 = values.top(); 
                    values.pop(); 
                    
                    char op = ops.top(); 
                    ops.pop(); 
                    
                    values.push(applyOp(val1, val2, op)); 
                }
                ops.push(tokens[i]); 
            } 
        }

        while(!ops.empty()){ 
            int val2 = values.top(); 
            values.pop(); 
                    
            int val1 = values.top(); 
            values.pop(); 
                    
            char op = ops.top(); 
            ops.pop(); 
                    
            values.push(applyOp(val1, val2, op)); 
        }
        
        return values.top(); 
    }

Example:

.. code-block:: cpp

    cout << evaluate("10 + 2 * 6") << "\n";
    cout << evaluate("100 * 2 + 12") << "\n";
    cout << evaluate("100 * ( 2 + 12 )") << "\n"; 
    cout << evaluate("100 * ( 2 + 12 ) / 14")  << endl;



postfix to infix
^^^^^^^^^^^^^^^^

postfix: abcd^e-fgh*+^*+i-
infix: ((a+(b*(((c^d)-e)^(f+(g*h)))))-i)

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

Example:

.. code-block:: cpp

    string exp = "abcd^e-fgh*+^*+i-"; 
    cout << getInfix(exp) << endl;


infix to postfix
^^^^^^^^^^^^^^^^

infix: a+b*(c^d-e)^(f+g*h)-i
postfix: abcd^e-fgh*+^*+i-

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

Example:

.. code-block:: cpp

    string exp = "a+b*(c^d-e)^(f+g*h)-i";
    infixToPostfix(exp);


Prime
^^^^^

Sieve Of Eratosthenes
=====================

print all primes less than N

Code:

.. code-block:: cpp

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

        // Print all isprime numbers
        for (int p=2; p<=n; p++)
        if (isprime[p])
            cout << p << " ";
    }

Example:

.. code-block:: cpp

    SieveOfEratosthenes(100);
