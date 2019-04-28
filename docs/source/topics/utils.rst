Utility Function
================

is_number
---------

.. code-block:: cpp

    bool is_number(const std::string& s) {
        std::string::const_iterator it = s.begin();
        while (it != s.end() && std::isdigit(*it)) ++it;
        return !s.empty() && it == s.end();
    }

expression evalation
--------------------

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
----------------

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
----------------

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

Rotate 2D array
---------------

.. code-block:: cpp

    /* 
    * rotate the values of 2D array by 90 degree
    */
    void rotateMatrix(int mat[][N], bool clockwise) 
    {
        for (int x = 0; x < N / 2; x++) 
        {
            for (int y = x; y < N-x-1; y++) 
            {
                int temp = mat[x][y];

                if (clockwise) {
                    mat[x][y] = mat[y][N-1-x]; 
                    mat[y][N-1-x] = mat[N-1-x][N-1-y]; 
                    mat[N-1-x][N-1-y] = mat[N-1-y][x];
                    mat[N-1-y][x] = temp; 
                }else {
                    mat[x][y] = mat[N-1-y][x];
                    mat[N-1-y][x] = mat[N-1-x][N-1-y];
                    mat[N-1-x][N-1-y] = mat[y][N-1-x];
                    mat[y][N-1-x] = temp;
                }
            } 
        } 
    }

Convert fraction to decimal string
----------------------------------

.. code-block:: cpp

    cout << fractionToDecString(49, 22) << endl;
    cout << fractionToDecString(-1, -2) << endl; 
    cout << fractionToDecString(0, 1) << endl;
    // Output
    // 2.2(27)
    // 0.5
    // 0

.. code-block:: cpp

    // Function to return the required fraction 
    // in string format 
    string fractionToDecString(int num, int den) 
    { 
        // If the numerator is zero, answer is 0 
        if (num == 0) 
            return "0"; 
    
        // If any one (out of numerator and denominator) 
        // is -ve, sign of resultant answer -ve. 
        int sign = (num < 0) ^ (den < 0) ? -1 : 1; 
    
        num = abs(num); 
        den = abs(den); 
    
        // Calculate the absolute part (before decimal point). 
        int initial = num / den; 
    
        // Output string to store the answer 
        string res; 
    
        // Append sign 
        if (sign == -1) 
            res += "-"; 
    
        // Append the initial part 
        res += to_string(initial); 
    
        // If completely divisible, return answer. 
        if (num % den == 0) 
            return res; 
    
        res += "."; 
    
        // Initialize Remainder 
        int rem = num % den;  
        map<int, int> mp; 
    
        // Position at which fraction starts repeating 
        // if it exists 
        int index; 
        bool repeating = false; 
        while (rem > 0 && !repeating) { 
            // If this remainder is already seen, 
            // then there exists a repeating fraction. 
            
            if (mp.find(rem) != mp.end()) { 
                // Index to insert parantheses 
                index = mp[rem]; 
                repeating = true; 
                break; 
            } 
            else {
                mp[rem] = res.size();
            }
                
    
            rem = rem * 10; 
    
            // Calculate quotient, append it to result and 
            // calculate next remainder 
            int temp = rem / den; 
            res += to_string(temp); 
            rem = rem % den; 
        } 
    
        // If repeating fraction exists, insert parantheses. 
        if (repeating) { 
            res += ")";
            res.insert(index, "("); 
        } 

        return res; 
    }

Convert number(with recurring number) to fraction
-------------------------------------------------

.. code-block:: cpp

    cout << "2.3(27) = " << decStringToFraction("2", "3", "27") << "\n";
    cout << "0.3(27) = " << decStringToFraction("0", "3", "27") << "\n";
    cout << "-0.125 = " << decStringToFraction("-0", "125", "") << "\n";
    cout << "0.(142857) = " << decStringToFraction("0", "", "142857") << "\n";
    cout << "3.(142857) = " << decStringToFraction("3", "", "142857") << "\n";
    cout << "3 = " << decStringToFraction("3", "", "") << "\n";

.. code-block:: cpp

    int findGcd(int a, int b) {
        if (a == 0)
            return b;
        return findGcd(b%a, a);
    }

    string decStringToFraction(string integer, string point, string recurring) {
        string res;
        integer[0] == '-'? res = "-": res = "";

        int ivalue = stoi(integer);
        ivalue = abs(ivalue);

        int ppow = point.length(), rpow = recurring.length();
        int pvalue = 0;
        int rvalue = 0;
        if (ppow > 0)
            pvalue += stoi(point);
        if (rpow > 0)
            rvalue += stoi(recurring);

        if (ppow == 0 && rpow == 0) {
            res += to_string(ivalue);
            res += "/";
            res += "1";
        }else {
            // num = convert point & recurring into integer
            // it is multiplied by 10^(ppow + rpow)
            int num = pvalue * pow(10, rpow) + rvalue;
            int den = pow(10, ppow + rpow);
            if (rpow > 0) {
                den -=  pow(10, ppow);
                num -= pvalue;
            }

            int gcd = findGcd(num, den);

            // append numerator
            res += to_string((den * ivalue + num) / gcd);
            res += "/";
            // append denominator
            res += to_string(den / gcd);
        }
        return res;
    }