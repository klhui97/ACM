#include <iostream>
#include <string>
#include <stack>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <algorithm>
#include <iomanip>

using namespace std;

int precedence(char op) { 
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
    return 0;
}

bool isHex(char a) {
    if (a >= '0' && a <= '9')
        return true;
    if (a >= 'A' && a <= 'F')
        return true;
    return false;
}

int intValue(char a) {
    if (a >= '0' && a <= '9')
        return a - '0';
    if (a >= 'A' && a <= 'F')
        return a - 'A' + 10;
    return a;
}

int evaluate(string tokens){ 
    int i;
    stack <int> values; 
    stack <char> ops; 
      
    for(i = 0; i < tokens.length(); i++){
        if(tokens[i] == '('){ 
            ops.push(tokens[i]); 
        } else if(isHex(tokens[i])){ 
            int val = 0;
            val = (val*16) + intValue(tokens[i]);
            values.push(val); 
        } else if(tokens[i] == ')') { 
            while(!ops.empty() && ops.top() != '(') { 
                int val2 = values.top(); 
                values.pop(); 
                  
                int val1 = values.top(); 
                values.pop(); 
                  
                char op = ops.top(); 
                ops.pop(); 
                  
                values.push(applyOp(val1, val2, op)); 
            } 
            
            ops.pop(); 
        } else {
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

void printHex(int n) {

    if (n == 0) {
        cout << 0 << endl;
        return;
    }

    char hexaDeciNum[100];
    int i = 0; 
    while(n != 0) 
    {    
        int temp  = 0; 
        temp = n % 16; 
          
        if(temp < 10) { 
            hexaDeciNum[i] = temp + 48; 
            i++; 
        }else { 
            hexaDeciNum[i] = temp + 55; 
            i++; 
        } 
          
        n = n / 16; 
    } 

    for(int j=i-1; j>=0; j--) 
        cout << hexaDeciNum[j]; 
    cout << endl;
}

void mainFunction() {
    string line;

    while(true) {
        getline(cin, line);
            
        if (line.length() == 0 || !cin) {
            break;
        }
        // cout <<  << endl;
        printHex(evaluate(line));
    }
}

int main() {
    mainFunction();
    return 0;
}