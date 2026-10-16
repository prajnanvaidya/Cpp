#include<bits/stdc++.h>

using namespace std;

//Balanced Parenthesis:
//Given: string containing (),{},[]

//Return bool whether it is balanced or not

// Balanced means:
// - If there is a opening parenthesis there should exist closing parenthesis
// - After a opening parenthesis '{' if inside u got some other parenthesis '(' before its closing parenthesis '}' then ')' it should exist before closing parenthesis '}' only then it is balanced

// Ex: s = ()[{}()] balanced, s = ()[{}(]) unbalanced
// s = (()  , s = )) unbalanced

bool balancedParenthesis(string s){
    stack<int> st;
    for(int i=0;i<s.size();i++){
        if(s[i] == '(' || s[i] == '{' || s[i] == '['){
            st.push(s[i]);
        }
        else{
            if( !st.empty() && 
                ((st.top() == '(' && s[i] == ')') || 
                 (st.top() == '{' && s[i] == '}') || 
                 (st.top() == '[' && s[i] == ']')))
                st.pop();
            else
                return false;
        }
    }
    return true;
}
//TC - O(n), Sc - O(n)

//========================================================================

//Prefix, Infix and Pstfix conversions
//Operator and operand 
//operators - +,-,*,/,%,^, >>, <<, &, &&, |, ||, !=, ==, 
//operands - 0-9, A-Z, a-z

//Priority order of oerators
//3 - (power operator)in python: ** (right to left associativity) in cpp: pow(base, exponent)-it doesnt come under the operator precedence as its just a function but even if when put in a expresiion it can be the first as in operator precedence parenthesis comes above all but below the unary i.e -, So pow(-2, 2) = 4 and not -4 to get -4 u should do -pow(2,2) = -4,
//2 - *, / (left to right associativity)
//1 - +,-   ""
//-1 - anything below them 

//Prefix - operator operand Ex: *+pq-mn
//Infix - operator operand operator Ex: (p+q)*(mm-n) {commonly used}
//Postfix - operand operator Ex; pq-mn-*

// Use case:
// Prefix: programming language known as LISP, tree DS
// Infix: commonly used and understanded by programming languages like c++
// Postfix: In stack based calculator


//Infix to Postfix conversion
//1. Maintain a stack and when encountered a operand just print it 
//2. When encountered a operator if stack is empty then put it inside the stack if not check priority if operator found has priority higher or equal then the operator in top of stack then push it 
//3. If operator found has priority lesser or equal then stack top then pop out and print the top of stack until u get the top that priority lesser to ur operator 
//4. If found a ( opening bracket just push it to stack
//5.When found ) bracket just pop and print until u get opening ( bracket
//6.Do not include ( or ) in answer

string infixToPostfix(string s){
    string ans;
    map<char, int> preced = {{'^',3}, {'*', 2}, {'/',2}, {'+',1}, {'-',1}};
    stack<int> st;
    for(int i=0;i<s.size();i++){
        if( (s[i] >= 'A' && s[i] <= 'Z') || (s[i] >= 'a' && s[i] < 'z') || (s[i]>='0' && s[i]<='9')){
            ans.push_back(s[i]);
        }
        else if(st.empty() || s[i]=='(' || st.top()=='('){
            st.push(s[i]);
        }
        else if(s[i]==')'){
            while(!st.empty() && st.top() != '('){
                ans.push_back(st.top());
                st.pop();
            }
            st.pop();
        }
        else{
            while(!st.empty() && preced[s[i]] <= preced[st.top()]){
                ans.push_back(st.top());
                st.pop();
            }
            st.push(s[i]);
        }
    }
    while(!st.empty()){
        ans.push_back(st.top());
        st.pop();
    }

    return ans;
}

//TC - O(n+ n){outer for loop, inner while loops like: when s[i]=')' while, when char is operator}
//SC - O(n + n)

//------------------------------------------------------------------------------------------------------------

//Infix to Prefix conversion:
// - First reverse the given string
// - Change '(' to ')' and vice versa
// - Convert it to postfix with one rule change
//     - When operator found is '^' go with normal rule i.e remove top from stack and print til the priority(st.top()) >= priority('^')
//     - But when operator found is other then '^' then follow: remove top elem fro stack and print till the priority(st.top()) > priority(s[i])
// - Reverse the resultant postfix to get prefix expressioin

string infixToPrefix(string s){
    //reverse string
    reverse(s.begin(), s.end());
    stack<int> st;
    string ans;
    map<char, int> preced = {{'^',3}, {'*',2}, {'/',2}, {'+',1}, {'-',1}};

    //Changing '(' to ')'
    for(int i=0;i<s.size();i++){
        if(s[i] == '(') s[i] = ')';
        else if(s[i] == ')') s[i] = '(';
    }

    //Converting to postfix
    for(int i=0;i<s.size();i++){
        // cout<<i;
        if((s[i]>='A' && s[i]<='Z') || (s[i]>='a' && s[i]<='z') || (s[i]>='0' && s[i]<='9')){
            ans.push_back(s[i]);
        }
        else if(st.empty() || s[i] == '(' || st.top()=='('){
            st.push(s[i]);
        }
        else if(s[i]==')'){
            while(!st.empty() && st.top()!='('){
                ans.push_back(st.top());
                st.pop();
            }
            st.pop();
        }
        else{   //change of rule followed
            if(s[i] == '^'){
                while(!st.empty() && preced[s[i]] <= preced[st.top()]){
                    ans.push_back(st.top());
                    st.pop();
                }
            }
            else{
                while(!st.empty() && preced[s[i]] < preced[st.top()]){
                    ans.push_back(st.top());
                    st.pop();
                }
            }
            st.push(s[i]);
        }
    }

    while(!st.empty()){
        ans.push_back(st.top());
        st.pop();
    }

    reverse(ans.begin(), ans.end());
    return ans;
}
//Tc - O(n/2 + n/2 + n + n) = O(2n) {n/2 for reverse if done in binary search and 2n for traversing string and updating stack}
// SC - O(n+n){one ofr stack and other for ans}

//Postfix to infix
//Take a stack 
//As u get the operands just push to stack
//If u get operator then take top1 and top2 elem from stack and convert them to (top2 operator top1) and push to stack
//The top of the stack is your desired infix expre at after input traversal end

string postfixToInfix(string s){
    stack<string> st;

    for(int i=0;i<s.size();i++){
        if((s[i]>='A' && s[i]<='Z') || (s[i]>='a' && s[i]<='z') || (s[i]>='0' && s[i]<='9')){
            st.push(string(1,s[i])); //inorder to push a character to stack<string> as it can only accept string u should first convert using string(len, char) where len is length of converted string
        }
        else{
            string top1 = st.top();
            st.pop();
            string top2=st.top();
            st.pop();

            string con = '('+ top2 + s[i] + top1 + ')';
            st.push(con); 
        }
    }
    return st.top();
}

//kind of problems i.e all below and this take same TC and SC 
//TC - O(n^2)-worst case {nested n is for string concatenation}
//Sc - O(n) it doesnt stack stores n strings but means at any point the stack has in total n characters 

//Prefix to infix
// Here as prefix has operands on left so we traverse from right to left
// - Take stack
// - if got operand then push it into stack 
// - If got operator then take top1 and top2 and push (top1 operator top2)
// - End of traversal return top of stack

string prefixToInfix(string s){
    stack<string> st;

    for(int i=s.size()-1;i>=0;i--){
        if( (s[i]>='A' && s[i]<='Z') || (s[i]>='a' && s[i]<='z') || (s[i]>='0' && s[i]<='9')){
            st.push(string(1, s[i]));
        }
        else{
            string top1 = st.top();
            st.pop();
            string top2 = st.top();
            st.pop();
            string con = '(' + top1 + s[i] + top2 + ')';
            st.push(con);
        }
    }
    return st.top();
}

//Postfix to prefix
// Take stack
// - Traverse the input from left to right cuz input is postfix
// - If got operand push to stack
// - if got operator then take top1 and top2 and make 'operator top2 top1' and push it to stack (top2 comes first as input is postfix as seen in postfixToInfix Conversion)
// - After traversal return top of stack

string postfixToPrefix(string s){
    stack<string> st;

    for(int i=0;i<s.size();i++){
        if( (s[i]>='A' && s[i]<='Z') || (s[i]>='a' && s[i]<='z') || (s[i]>='0' && s[i]<='9')){
            st.push(string(1, s[i]));
        }
        else{
            string top1 = st.top();
            st.pop();
            string top2 = st.top();
            st.pop();
            string con = s[i] + top2 + top1;
            st.push(con);
        }
    }
    return st.top();
}

//Prefix to Postfix conversion
// - Take a stack
// - Traverse from left to right (since input is prefix)
// - If got operand push to stack
// - If got operator then take top1 and top2 and make 'top1 top2 operator' and push to stack (top1 comes first as input is prefix as seen in prefix to infix conversion)

string prefixToPostfix(string s){
    stack<string> st;

    for(int i=s.size()-1;i>=0;i--){
        if( (s[i]>='A' && s[i]<='Z') || (s[i]>='a' && s[i]<='z') || (s[i]>='0' && s[i]<='9')){
            st.push(string(1, s[i]));
        }
        else{
            string top1 = st.top();
            st.pop();
            string top2 = st.top();
            st.pop();
            string con = top1 + top2 + s[i];
            st.push(con);
        }
    }
    return st.top();
}


int main(){

    // string s = "()[{}()]";
    // cout<<balancedParenthesis(s);

    //============================

    string s = "/-AB*+DEF";
    string ans = prefixToPostfix(s);
    cout<<ans;

    //===========================

    return 0;
}