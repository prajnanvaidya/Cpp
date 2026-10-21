#include<bits/stdc++.h>
using namespace std;

//Strings
// - We have char arrs which are immutable once created but they are difficult to operate operate on
// - char arr[] = {'a', 'b', 'c'}; here length cannot be increased or decreased once declared
// - cout<<arr; o/p: abcHp��� cuz there is no '\0' marking the end of char arr so it prints until encounters '\0'

// - char arr[] = {'a', 'b', 'c', '\0'};
//   cout<<arr; o/p: abc

// or u can directly use string literal which by default puts '\0' at end (A literal is a raw value written directly into your code. It has no name and cannot be changed because it is hardcoded.)
// char arr[] = "abc";
// cout<<arr; o/p: abc

// - Inorder to input char arr without spaces use cin>>arr;
// - with space if u want to input use: cin.getline(var_name, length, delimeter); by default delimeter is "\n", where len is len of input u want to take in, it should be below the size established while declaring
// strlen(charArr) - gives size


// - String is a class built for ease of use instead of char arr 
// - string str="Hello"
// - U can do str.push_back(), use reverse() any kind of thing as done for vector
//To take input with spaces as delimeter use cin>>str
//To take until '\n' use getline(cin, str_var, delimeter)
//To get size can do str.length() or str.size()

//---------------------------------------------------------------------------------------------------------------
//Remove Outermost Parenthesis
// Ex: (()())(()) ans = ()()()
// Supposed to remove parenthesis from each part if multiple
// The input string is valid(balanced) -  means if a parenthesis starts in a part it ens inside same part

// Using stack
string removeParenthesis(string str){
    int n=str.size();
    stack<char> ms;
    string res="";

    int st=-1, en=-1;
    for(int i=0;i<n;i++){
        if(str[i] == '('){
            if(ms.empty()) st=i;
            ms.push('(');
        }
        else{
            ms.pop();
            if(ms.empty()) en=i;
        }
        if(st != -1 && en != -1){
            res+=str.substr(st+1, en-st-1);
            st=-1;
            en=-1;
        }
    }
    return res;
}
//TC - O(n), SC - o(n/2)

//Using stack without using substr and noting starting and ending

string removeParenthesisStB(string str){
    int n=str.size();
    stack<char> ms;
    string res="";

    for(int i=0;i<n;i++){
        if(str[i] == '('){
            if(!ms.empty()){
                res+='(';
            }
            ms.push('(');
        }
        else{
            ms.pop();
            if(!ms.empty())
                res+=')';
        }
    }
    return res;
}

//Better way of writing:
string removeParentheBet(string str){
    stack<int> ms;
    string res="";

    for(auto v:str){
        if(v == ')') ms.pop();
        if(!ms.empty()) res += v;
        if(v == '(') ms.push(v);
    }
    return res;
}
//TC - O(n), SC - O(n)

//Optimal: use cnt var and increent when saw ( and decrement when saw ) and if on seeing ( before incrementing if cnt>0 then add it to res and when saw ) if after poping if cnt>0 then add it to res

string removeParenthesisOpt(string str){
    string res="";
    int cnt=0;
    for(auto v:str){
        if(v==')') cnt--;
        if(cnt>0) res+=v;
        if(v=='(') cnt++;
    }
    return res;
}

//-------------------------------------------------------------------------------------------------------------
// Given a sentence reverse the words
// Ex: "the sky is blue"
// res = "blue is sky the"

string reverseWords(string str){
    vector<string> temp;
    string res="";

    for(auto v:str){
        if(v != ' '){
            res+=v;
        }
        else if(v == ' '){
            temp.push_back(res);
            res.clear();
        }
    }
    temp.push_back(res);
    reverse(temp.begin(), temp.end());

    for(int i=1;i<temp.size()-1;i++){
        res += " "+temp[i];
    }
    res += " "+temp[temp.size()-1];
    
    return res;
}
//TC - O(n + 2*m) where m is no of words, SC - O(n)

string reverseWordsBet(string str){
    stack<string> stk;
    string res="";
    for(auto v:str){
        if(v == ' '){
            stk.push(res);
            res.clear();
        }
        else{
            res+=v;
        }
    }
    while(!stk.empty()){
        res+= " " + stk.top();
        stk.pop();
    }
    return res;
}
// TC - O(n + m), m-no of words, SC - O(n)

//Both of above approaches works only if there exist no trailing spaces or leading spaces after sentence and exactly 1 space between words

//Optimal: use res and just put a loop through and some condition
string reverseSentenceOpt(string s){
    int i=s.size();
    string res="";
    int end;
    while(i>0){
        while(i>0 && s[i-1]==' '){
            i--;
        }
        if(i==0) break;
        end=i;
        while(i>0 && s[i-1] != ' '){
            i--;
        }
        if(!res.empty()) res+=' ';
        res.append(s, i, end-i);
    }
    return res;
}
//TC - O(n), Sc - o(1)

//-------------------------------------------------------------------------------------------------------------

//Given num as string need to return largest odd number that can be formed with its substring or if there is no odd nos return empty string
//Return a string

// Ex: num = "52", res="5"
// num = "4206", res=""
// num = "35427", res="35427"

// constraints: 1 <= num.len <= 10^5, input doesnt contain any trailing 0's and other then 0-9

string largestOdd(string s){
    int n=s.size();
    string res;
    
    long long temp, p, maxi=LLONG_MIN;
    for(int i=n-1;i>=0;i--){
        temp=0;
        p=1;
        for(int j=i;j>=0;j--){
            temp+=(s[j]-'0')*p;
            p = p*10;
            if(temp%2 == 1)
                maxi = max(maxi, temp);
        }
    }
    if(maxi == INT_MIN)
        return "";
    while(maxi>0){
        res += char((maxi%10) + '0');
        maxi = maxi/10;
    }
    reverse(res.begin(), res.end());
    return res;
}
//TC - O(n^2 + 2*n), SC - o(1)

//Serious iusse: It overflows
// int - max value is -10^9 to 10^8, total = 10 digits
// long long -> -10^18 to 10^18, total = 18 digits

// But the constraint says the input can have at max 10^5 chars
// - As above u convert string to numbers u will surely overflow whichever dataType u use
// - Why a string can hold 10^5 chars and int-10digits and long long-18digits
//     - as int occupies 4bytes and longlong 8 bytes but a string each char only 1 byte so a string of 10^5 chars should have 100KB memory but int can only go upto 2^31-1=10^9 and lonlong can go upto 2^63-1 = 10^18

// Some useful Functions
// stoi()     vs   stoll()
// Function	    Return type	Typical maximum positive value
// stoi(str)	    int	2,147,483,647
// stoll(str)	    long long	9,223,372,036,854,775,807

// Note: Inorder to convert a int or long long to string use to_string(var_name) same can also be used to convert char to string like to_string(len, char_var);

//Optimal: Go through input from last and the index u got to be odd then ans=s.substr(0,i+1)

string largestOddOpt(string str){
    int n=str.size();
    for(int i=n-1;i>=0;i--){
        if((str[i]-'0')%2 == 1) return str.substr(0, i+1);
    }
    return "";
}
//TC - O(n), SC - O(1)

//-------------------------------------------------------------------------------------------------------------

//Longest common Prefix string

//Given arr of strings find longest common prefix if ther is no prefix then return ""

//Ex: {"flower", "flow", "flight"} o/p: fl
// {"dog", "racecar", "car"} there is no common prefix among all elems in arr so res = ""

string longestComPref(vector<string> arr){
    int n=arr.size();

    if(n==0) return "";
    else if(n==1) return arr[0];

    string temp = arr[0];
    int mini = temp.size();
    string pfx;

    for(int i=1;i<n;i++){
        mini = min(mini, (int)arr[i].size());
        pfx="";
        for(int j=0;j<mini;j++){
            if(temp[j] == arr[i][j]){
                pfx+=temp[j];
            }
            else break;
        }
        if(pfx == "") break;
        else{
            temp = pfx;
            mini = temp.size();
        }
    }
    return pfx;
}
//TC - O(n*m) where n=arr.size(), m=arr[0].size() {in worst case}, SC - O(2*m)

string LongestComOpt(vector<string>& arr){
    int n=arr.size();
    if(n==0) return "";

    string temp = arr[0];
    int end=-1;

    for(int i=1;i<n;i++){
        for(int j=0;j<temp.size();j++){
            if(temp[j] == arr[i][j]) end = j;
            else break;
        }
        if(end == -1) break;
        temp = arr[i].substr(0, end+1);
    }
    return temp;
}

string longestCommPOptHis(vector<string>& arr){
    int n=arr.size();
    if(n==0) return "";
    int m=arr[0].size();

    for(int j=0;j<m;j++){
        char c = arr[0][j];
        for(int i=1;i<n;i++){
            if(j >= arr[i].size() || arr[i][j] != c)
                return arr[0].substr(0, j);
        }
    }
    return arr[0];
}

//-------------------------------------------------------------------------------------------------------------

    /*
        Problem: Isomorphic Strings

        Given two strings s and t, determine if they are isomorphic.

        Definition:
        Two strings s and t are isomorphic if the characters in s can be
        replaced to get t, while preserving the order of characters.

        Rules:
        1. All occurrences of a character must be replaced with another character
        while preserving the order of characters.
        2. No two different characters can map to the same character.
        3. A character can map to itself.

        Example 1:
        Input:  s = "egg", t = "add"
        Output: true

        Explanation:
        - Map 'e' to 'a'.
        - Map 'g' to 'd'.

        Example 2:
        Input:  s = "foo", t = "bar"
        Output: false

        Explanation:
        The character 'o' would need to map to both 'a' and 'r',
        which is not allowed.

        Example 3:
        Input:  s = "paper", t = "title"
        Output: true
    */

    /*
    Example 1 — Rule 3: A character can map to itself

    Input:  s = "abc", t = "adc"
    Output: true

    Mapping:
    'a' -> 'a', 'b' -> 'd', 'c' -> 'c'

    Explanation:
    Here, 'a' and 'c' map to themselves, which is allowed.


    Example 2 — Rule 3: All characters map to themselves

    Input:  s = "hello", t = "hello"
    Output: true

    Explanation:
    Every character maps to itself:
    'h' -> 'h', 'e' -> 'e', 'l' -> 'l', 'o' -> 'o'.


    Example 3 — Rule 2: Two characters cannot map to the same character

    Input:  s = "ab", t = "cc"
    Output: false

    Explanation:
    Both 'a' and 'b' would map to 'c', which is not allowed.


    Example 4 — Repeated character pattern must match

    Input:  s = "badc", t = "baba"
    Output: false

    Explanation:
    The character 'b' in s maps to 'b' in t, and 'a' maps to 'a'.
    However, 'd' would also need to map to 'b', which is already
    mapped from 'b'. This violates the one-to-one mapping rule.
*/

//Brut:Rule1: the diff types of chars and no of times they appear should be same in both 
    // Rule2: the order in which those chars placed in original s and t should also be same

    // the no of times each distinct char appear we considered to check that addition of all char freq in 1 map and its same as checking s.size()==t.size()

bool isomorphicCheck(string s, string t){
    int n = s.size();
    int m = t.size();
    if(n!=m) return false;

    map<char, int> mps;
    map<char, int> mpt;

    for(int i=0;i<n;i++){
        mps[s[i]]++;
        mpt[t[i]]++;
    }
    if(mps.size() != mpt.size()) return false;

    //Order checking
    vector<int> mps_or, mpt_or;
    for(int i=0;i<n;i++){
        mpt_or.push_back(mps[s[i]]);
        mps_or.push_back(mpt[t[i]]);
    }

    for(auto v:mps_or) cout<<v<<" ";
    cout<<endl;

    for(int i=0;i<n;i++){
        if(mpt_or[i] != mps_or[i]) return false;
    }
    return true;
}
//TC - O(nlogk) where n-len of string and k-max no of chars, SC - O(k)

//The above fails for cddc and baba cuz u only differ between order by no of times they appear but in this case the no of times both c and d appears is 2 i.e same

//Optimal: maintain 2 hash arrs and 1 to map sTot and other to map tTos intially store all -1 and each time check whether the mapping right as per current cenaro

bool CheckIsomorphicOpt(string s, string t){
    if(s.size() != t.size()) return false;
    vector<int> tTos(256, -1), sTot(256, -1);

    for(int i=0;i<s.size();i++){
        unsigned char a = s[i];
        unsigned char b = t[i];

        if(sTot[a] != -1 && sTot[a] != b) return false;

        if(tTos[b] != -1 && tTos[b] != a) return false;

        sTot[a]=b;
        tTos[b]=a;
    }
    return true;
}
//T - O(n), Sc - O(2*256) where n = s.size()

//-------------------------------------------------------------------------------------------------------------

/*
    Problem: Strings Rotations of Each Other

    Given two strings s1 and s2, determine whether s2 is a rotation
    of s1.

    A string is a rotation of another string if characters are moved
    from one end to the other while preserving their relative order.

    Example 1:
    Input:  s1 = "abcd", s2 = "cdab"
    Output: true

    Explanation:
    After 2 right rotations, s1 becomes equal to s2.
    "abcd" -> "dabc" -> "cdab"


    Example 2:
    Input:  s1 = "aab", s2 = "aba"
    Output: true

    Explanation:
    After 1 left rotation, s1 becomes equal to s2.
    "aab" -> "aba"


    Example 3:
    Input:  s1 = "abcd", s2 = "acbd"
    Output: false

    Explanation:
    s2 cannot be obtained by rotating s1 because the character
    order does not match any rotation of s1.

    Note:
    Both strings must have the same length to be rotations of
    each other.
*/

//Brut: take s1 rotate left or right (n-1) times and check each time if its equal to s2
bool stringRotat(string s1, string s2){
    if(s1.size() != s2.size()) return false;
    if(s1 == s2) return true;
    int i=0;
    int n=s1.size();

    while(i<(n-1)){
        char c = s1[0];
        for(int i=1;i<n;i++) s1[i-1]=s1[i];
        s1[n-1] = c;

        if(s1 == s2) return true;
        i++;
    }
    return false;
}
//TC - O(n^2), SC - O(1)

//Better: the possible rotations of s1 is a substring in s1+s2
// Ex; s1="abcd", 
// s1+s2 = "abcdabcd"
// u take each n of them starting from 0 until the (s1+s2).size()-4
// abcd
// bcda
// cdab
// dabc

bool StringRotatBet(string s1, string s2){
    if(s1.size() != s2.size()) return false;
    int n=s1.size();
    string s3 = s1+s1;

    for(int i=0;i<=n;i++){
        if(s3.substr(i, n) == s2){
            return true;
        }
    }
    return false;
}
//TC - O(n), sc - O(1)

//Using find method
bool StringRotatBet2(string s1, string s2){
    if(s1.size() != s2.size()) return false;

    string s3 = s1+s1;

    return (s3.find(s2) != string::npos);
}

//-------------------------------------------------------------------------------------------------------------
// Check if 2 strings are anagrams of each other
// 2 strings are anagrams if they contain same characters with exactly same frequencies regardless of their order

// Ex: s1 = "geeks", s2=kseeg, res=true
// s1 = allergy, s2=allergyy, res= false

bool checkAnagrams(string s1, string s2){
    vector<int> hashS1(256, 0);
    vector<int> hashS2(256, 0);

    for(auto v:s1) hashS1[v]++;
    for(auto v:s2) hashS2[v]++;

    for(int i=0;i<256;i++){
        if(hashS1[i] != hashS2[i]) return false;
    }
    return true;
}
//TC - O(n+m), SC - O(2*256)

//Optimal: using 1 hashArr
bool checkAnagramsOpt(string s1, string s2){
    vector<int> hash(256, 0);

    for(auto v:s1) hash[v]++;
    for(auto v:s2) hash[v]--;

    for(auto v:hash) if(v!=0) return false;
    return true;
}

//-------------------------------------------------------------------------------------------------------------

/*
    Problem: Sort Elements by Decreasing Frequency

    Given a string s, sort it in decreasing order based on the
    frequency of its characters. The frequency of a character is
    the number of times it appears in the string.

    Return the sorted string. If there are multiple answers,
    return any of them.

    Example 1:
    Input: s = "tree"
    Output: "eert"

    Explanation:
    'e' appears twice, while 'r' and 't' both appear once.
    So 'e' must appear before both 'r' and 't'.
    Therefore, "eetr" is also a valid answer.
*/


string sortElemsDesc(string& s){
    string res="";
    map<char, int> mpp;

    for(auto v:s){
        mpp[v]++;
    }

    vector<int> temp;
    for(auto v:mpp){
        temp.push_back(v.second);
    }
    sort(temp.begin(), temp.end(), greater<int>());

    for(auto v:temp){
        for(auto it=mpp.begin();it!=mpp.end();it++){
            if(it->second == v){
                for(int i=0;i<v;i++)
                    res+=it->first;
                mpp.erase(it);
                break;
            }
        }
    }

    return res;
}
//n- size of input, k-no of uniq chars in input
// SC-O(2*k), TC - O(n + k + klogk + k^2logk + n) = O(k^2logk + n)

string sortElemsDescBet(string& s){
    string res="";
    vector<int> hash(256, 0);

    for(auto v:s){
        hash[v]++;
    }

    vector<int> temp;
    for(auto v:hash){
        if(v>0)
            temp.push_back(v);
    }
    sort(temp.begin(), temp.end(), greater<int>());

    for(auto v:temp){
        for(int i=0;i<hash.size();i++){
            if(hash[i]>0 && v == hash[i]){
                res.append(string(v, char(i)));
                hash[i]=0;
                break;
            }
        }
    }

    return res;
}
//TC - O(n + 256 + klogk + 256*k + n) = O(klogk + n), SC - O(k + 256)

// Note:
// 1. std::to_string(num) -> Converts a single number to text.
//    Example: std::to_string(42)  -> "42"
//    Example: std::to_string('A') -> "65" (uses ASCII value)

// 2. std::string(count, char) -> Repeats a character 'count' times.
//    Example: std::string(5, 'A')     -> "AAAAA"
//    Example: std::string(v, char(i)) -> Repeats character 'i', 'v' times

//Cleaner approach using vector<int> hash(256) and vector<pair<int, char>

string sortElemsFreqDescOpt(string& s){
    vector<int> hash(256, 0);

    for(auto v:s){
        hash[v]++;
    }
    
    vector<pair<int, unsigned char>> temp;
    for(int i=0;i<hash.size();i++){
        if(hash[i]>0){
            temp.push_back({hash[i], static_cast<unsigned char>(i)});
        }
    }

    sort(temp.begin(), temp.end(), 
    [](const auto& a, const auto & b){
        return a.first>b.first;
    });

    string res="";
    for(auto v:temp){
        res.append(v.first, static_cast<char>(v.second));
    }
    return res;
}
//TC - O(n + 256 + klogk + k), Sc - O(256 + k)

//-------------------------------------------------------------------------------------------------------------

/*
    Problem: Maximum Nesting Depth of the Parentheses

    Given a valid parentheses string s, return the nesting depth of s.
    The nesting depth is the maximum number of nested parentheses.

    Example 1:
    Input:  s = "(1+(2*3)+((8)/4))+1"
    Output: 3

    Explanation:
    Digit 8 is inside 3 nested parentheses in the string.

    Example 2:
    Input:  s = "(1)+((2))+(((3)))"
    Output: 3

    Explanation:
    Digit 3 is inside 3 nested parentheses in the string.

    Example 3:
    Input:  s = "()((())())"
    Output: 3


    Constraints:
    - 1 <= s.length <= 100
    - s consists of digits 0-9 and characters '+', '-', '*', '/', '(',
      and ')'.
    - It is guaranteed that the parentheses expression s is a VPS
      (Valid Parentheses String).
*/

int nestedParenthesis(string& s){
    int n=s.size();
    int cnt=0;
    int maxi = 0;
    for(int i=0;i<n;i++){
        if(s[i] == '('){
            cnt++;
            maxi = max(maxi, cnt);
        }
        else if(s[i] == ')'){
            cnt--;
        }
    }
    return maxi;
}
//TC - O(n), SC - O(n)

//-------------------------------------------------------------------------------------------------------------

/*
    Problem: Roman Number to Integer

    Roman numerals are represented by seven different symbols:
    Symbol: I, V, X, L, C, D, M
    Value:  1, 5, 10, 50, 100, 500, 1000

    For example:
    - 2 is written as II (1 + 1).
    - 12 is written as XII (10 + 1 + 1).
    - 27 is written as XXVII (10 + 10 + 5 + 1 + 1).

    Roman numerals are usually written from largest to smallest
    from left to right.

    However, subtraction is used in six cases:
    - I before V (5) and X (10) makes 4 and 9.
    - X before L (50) and C (100) makes 40 and 90.
    - C before D (500) and M (1000) makes 400 and 900.

    Given a Roman numeral, convert it to an integer.


    Example 1:
    Input:  s = "III"
    Output: 3
    Explanation: III = 3.


    Example 2:
    Input:  s = "LVIII"
    Output: 58
    Explanation: L = 50, V = 5, III = 3.


    Example 3:
    Input:  s = "MCMXCIV"
    Output: 1994
    Explanation: M = 1000, CM = 900, XC = 90, IV = 4.


    Constraints:
    - 1 <= s.length <= 15
    - s contains only the characters 'I', 'V', 'X', 'L', 'C', 'D', 'M'.
    - It is guaranteed that s is a valid Roman numeral in the range
      [1, 3999].
*/

    int romanToInt(string s){
        int n=s.size();

        int sum=0;
        for(int i=0;i<n;i++){
            if(s[i] == 'I'){
                if(s[i+1] == 'V'){
                    sum += 4;
                    i++;
                }
                else if(s[i+1] == 'X'){
                    sum += 9;
                    i++;
                }
                else{
                    sum+=1;
                }
            }
            else if(s[i] == 'V'){
                sum += 5;
            }
            else if(s[i] == 'X'){
                if(s[i+1] == 'L'){
                    sum+=40;
                    i++;
                }
                else if(s[i+1] == 'C'){
                    sum+=90;
                    i++;
                }
                else{
                    sum+=10;
                }
            }
            else if(s[i] == 'L'){
                sum += 50;
            }
            else if(s[i]=='C'){
                if(s[i+1] == 'D'){
                    sum += 400;
                    i++;
                }
                else if(s[i+1] == 'M'){
                    sum += 900;
                    i++;
                }
                else{
                    sum+=100;
                }
            }
            else if(s[i] == 'M'){
                sum+=1000;
            }
        }
        return sum;
    }
    //TC - O(n), SC - O(1)

// Note: the subtractive cases are only 6 and any other would mean invalid roman numeral for ex: XD != 490 & != 510, 
// I-1,  V-5, X-10, L-50, C-100, D-500, M-1000
// subtractive: IV - 5-1=4, IX - 10-1=9, XL - 50-10=40, XC - 100-10=90, CD - 500-100 = 400, CM - 1000-100 = 900

//Cleaner but can only givee correct result for valid roman numeral

int romanVal(char c){
    switch(c){
        case 'I': return 1;

        case 'V': return 5;

        case 'X': return 10;

        case 'L': return 50;

        case 'C': return 100;

        case 'D': return 500;

        case 'M': return 1000;

        default: return 0;
    }
}

int romanToIntCl(string s){
    int n=s.size();
    int sum=0;

    for(int i=0;i<n;i++){
        int inter = romanVal(s[i]);
        if(i+1<n && inter<romanVal(s[i+1])){
            sum -= inter;
        }
        else{
            sum+=inter;
        }
    }
    return sum;
}
//TC - O(n), SC - O(1)

//-------------------------------------------------------------------------------------------------------------

/*
    Problem: Implement Atoi

    Given a string s, convert it into an integer without using any
    built-in functions.

    Steps for atoi() conversion:
    1. Skip all leading whitespaces.
    2. Check for a sign ('+' or '-'). Default to positive if no sign
       is present.
    3. Read the integer, ignoring leading zeros, until a non-digit
       character is encountered or the end of the string is reached.
       If no digits are present, return 0.
    4. If the integer is greater than INT_MAX (2147483647), return
       INT_MAX. If the integer is smaller than INT_MIN (-2147483648),
       return INT_MIN.


    Examples:

    Example 1:
    Input: s = "-123"
    Output: -123
    Explanation: It is possible to convert -123 into an integer,
    so we return -123.


    Example 2:
    Input: s = " -"
    Output: 0
    Explanation: No digits are present, therefore the returned
    answer is 0.


    Example 3:
    Input: s = "1231232132311133"
    Output: 2147483647
    Explanation: The converted number is greater than INT_MAX,
    therefore return INT_MAX (2147483647).


    Example 4:
    Input: s = "-999999999999"
    Output: -2147483648
    Explanation: The converted number is smaller than INT_MIN,
    therefore return INT_MIN (-2147483648).


    Example 5:
    Input: s = "  -0012gfg4"
    Output: -12
    Explanation: Leading whitespaces and zeros are ignored.
    Reading stops when the first non-digit character 'g' is
    encountered, so the result is -12.
*/

int atoi(string s){
    int n=s.size();
    int sign = 1;

    int i=n-1;
    long long cnvrt = 0, p=1;
    while(i>=0){
        if(s[i] == '-') sign = 0;

        if(s[i] >= '0' && s[i] <= '9'){
            cnvrt += (s[i] - '0')*p;
            p = p*10;
        }
        i--;
    }

    if(sign == 0) cnvrt = (-1 * cnvrt);

    if(cnvrt > INT_MAX) return INT_MAX;
    else if(cnvrt < INT_MIN) return INT_MIN;

    return cnvrt;
}
//TC - O(n), SC - O(1)
//Problem states should stop after seeing first non digit character but in above we dont
// Another issue: even if - is in middle it considers that as sign of whole number
// THe leading whitespaces should be ignored

int atoiCor(string& s){
    int start=-1, end=-1;
    int n=s.size();
    long long sum=0;
    int sign = 1;

    int TwoSignFlag = 0;

    int i=0;
    while(i<n){
        if((!(s[i]>='0' && s[i]<='9') && s[i] != ' ' && s[i] != '-' && s[i] != '+') || TwoSignFlag == 2 || (TwoSignFlag == 1 && s[i] == ' ')){
            break;
        }
        else if(s[i]>='0' && s[i]<='9'){
            start = i;
            break;
        }
        else if(s[i] == '-'){
            sign = 0;
            TwoSignFlag++;
        }
        else if(s[i] == '+'){
            TwoSignFlag++;
        }
        i++;
    }
    if(start == -1) return 0;

    int j=start+1;
    while(j<n){
        if(!(s[j] >= '0' && s[j] <= '9')){
            end = j-1;
            break;
        }
        j++;
    }
    if(end == -1) end = n-1;

    int k=start;
    while(k<=end){
        if(sign == 0 && sum > (long long)(((long long)INT_MAX+1 - (s[k]-'0'))/10)) return INT_MIN;
        if(sign == 1 && sum > (long long)((INT_MAX - (s[k]-'0'))/10)) return INT_MAX;

        sum = sum*10 + (s[k]-'0');
        k++;
    }

    if(sign == 0) sum = (-1 * sum);

    return sum;
}
//Tc - O(2*n), SC - O(1)

//Above after many fixes even then it fails, the only solution is as below:
int atoiCorrect(string s){
    int n=s.size();

    long long sum=0;
    int i=0, sign = 1;

    while(i<n && s[i] == ' '){
        i++;
    }

    while(i<n && (s[i]=='+' || s[i]=='-')){
        if(s[i] == '-') sign = -1;
        i++;
    }

    long long limit = (sign == 1)? INT_MAX: -(long long)INT_MIN;

    while(i<n && (s[i]>='0' && s[i]<='9')){
        int digit = (s[i]-'0');

        if(sum > (limit - digit)/10){
            if(sign == 1) return INT_MAX;
            else return INT_MIN;
        }
        sum = sum*10 + digit;
        i++;
    }

    sum = (sign * sum);
    return static_cast<int>(sum);
}
//TC - O(n), SC - O(1)

//-------------------------------------------------------------------------------------------------------------
/*
    Problem: Count Number of Substrings

    Given a string s of length n, count the total number of
    non-empty substrings.

    A substring is a contiguous sequence of characters in a string.
    Repeated substrings are counted separately.

    Example 1:
    Input:  s = "abc"
    Output: 6

    Explanation:
    Substrings: "a", "b", "c", "ab", "bc", "abc".
    Total = 6.


    Example 2:
    Input:  s = "abcd"
    Output: 10

    Explanation:
    There are 4 substrings of length 1, 3 of length 2,
    2 of length 3, and 1 of length 4.
    Total = 4 + 3 + 2 + 1 = 10.


    Formula:
    Total number of non-empty substrings = n * (n + 1) / 2
*/

void aboutSubstrings(string s){
    int n=s.size();
    cout<<"Count: "<<(n*(n+1))/2<<endl;

    vector<char> temp;
    for(int i=0;i<n;i++){
        temp.clear();
        for(int j=i;j<n;j++){
            temp.push_back(s[j]);

            for(auto v:temp) cout<<v<<" ";
            cout<<endl;
        }
    }
}
//TC - O(n^2), SC - O(n)

//-------------------------------------------------------------------------------------------------------------

/*
    Problem: Longest Palindromic Substring

    Given a string s, return the longest palindromic substring in s.
    If there are multiple answers, return the one that appears first
    in the given string s.

    Note:
    A substring is a contiguous sequence of characters within a string,
    i.e., s[i...j] where 0 <= i <= j < len(s).


    Example 1:
    Input:  s = "forgeeksskeegfor"
    Output: "geeksskeeg"

    Explanation:
    There are several possible palindromic substrings like "kssk",
    "ss", "eeksskee", etc. But "geeksskeeg" is the longest among all.


    Example 2:
    Input:  s = "abacac"
    Output: "aba"

    Explanation:
    The palindromic substrings "aba", "aca", and "cac" all have the
    same length. Since "aba" appears first, it is the answer.


    Example 3:
    Input:  s = "geeks"
    Output: "ee"

    Explanation:
    The longest palindromic substring present in the given string
    is "ee".


    Constraints:
    1 <= s.length <= 10^4
*/

//Brut: find all possible substring and for each check whether its a palindrome or not

bool checkPalindrome(string s){
    int n=s.size();
    int i=0, j=n-1;

    while(i<j){
        if(s[i] != s[j]) return false;
        i++;
        j--;
    }
    return true;
}

string longestPalindromeSubstr(string s){
    int n = s.size();
    string temp;
    int maxi = 0;
    string res;

    for(int i=0;i<n;i++){
        temp = "";
        for(int j=i;j<n;j++){
            temp.push_back(s[j]);
            if(checkPalindrome(temp)){
                if(maxi < temp.size()){
                    maxi = temp.size();
                    res = temp;
                }
            };
        }
    }
    return res;
}
//TC - O(n^3), SC - O(2*n)

//Optimal: the optimal approach does check every possible center possible for a string
// What are every possible centers:
// - for a odd len string there exist single center ex: "cbabc" n=5, center=3rd pos
// - for even len string there exist double center ex: "abba" n=4, center=2&3 pos

// Keep 2 ptrs and check for every elem being single center and other time 2 ptrs poiting to i and i+1

string longPalSubstrOpt(string s){
    int n = s.size();
    int start=0, maxi=0;

    int l, r;
    for(int i=0;i<n;i++){
        l=i, r=i;
        while(l>=0 && r<n && s[l] == s[r]){
            if(r-l+1 > maxi){
                maxi = r-l+1;
                start = l;
            }
            l--;
            r++;
        }

        l=i, r=i+1;
        while(l>=0 && r<n && s[l] == s[r]){
            if(r-l+1 > maxi){
                maxi = r-l+1;
                start = l;
            }
            l--;
            r++;
        }
    }
    return s.substr(start, maxi);
}
//Tc - O(n^2), SC - O(1)

// 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
// f o r g e e k s s k e  e  g  f  o  r

// maxi = 0, start=0, n=16
// -> i=0
//     l=0, r=0
//         l>=0 && r<16 && s[l]=s[r]
//             maxi = 1
//             start = 0
//             l=-1, r=1
    
//     l=0, r=1
//         l>=0 && r<16 && s[l]!=s[r]
    
// -> i=1
//     l=1, r=1
//         l>=0 and r<16 and s[l]=s[r]
//             l=0, r=2
//         l>=0 and r<16 and s[l]!=s[r]
        
//     l=1, r=2
//         l>=0 and r<16 and s[l]!=s[r]

// -> i=2
//     l=2, r=2 
//         l>=0 and r<16 and s[l]=s[r]
//             l=1, r=3
//         l>=0 and r<16 and s[l]!=s[r]
//     l=2, r=3
//         l>=0 and r<16 and s[l]!=s[r]
// -> i=3
//     l=3, r=3
//         l>=0 and r<16 and s[l]=s[r]
//             l=2, r=4
//         l>=0 and r<16 and s[l]!=s[r]
//     l=3 and r=4
//         l>=0 and r<16 and s[l]!=s[r]
// -> i=4
//     l=4, r=4
//         l>=0 and r<16 and s[l]=s[r]
//             l=3, r=5
//         l>0 and r<16 and s[l]!=s[r]
//     l=4 and r=5
//         l>=0 and r<16 and s[l]=s[r]
//             maxi = 2
//             l=3 and r=6
//         l>=0 and r<16 and s[l]!=s[r]
// -> i=5
//     l=5, r=5
//         l>=0 and r<16 and s[l]=s[r]
//             l=4, r=6
//         l>=0 and r<16 and s[l]!=s[r]
//     l=5, r=6
//         l>=0 and r<16 and s[l]!=s[r]
// -> i=6 
//     l=6, r=6 
//         l>=0 and r<16 and s[l]=s[r]
//             l=5, r=7
//         l>=0 and r<16 and s[l]!=s[r]
//     l=6, r=7
//         l.=0 and r<16 and s[l]!=s[r]
// -> i=7
//     l=7, r=7
//         l>=0 and r<16 and s[l]=s[r]
//             l=6, r=8
//         l>=0 and r<16 and s[l]!=s[r]
//     l=7, r=8
//         l>=0 and r<16 and s[l]=s[r]
//             l=6, r=9
//         l>=0 and r<16 and s[l]=s[r]
//             maxi = 3
//             start=6
//             l=5, r=10
//         l>=0 and r<16 and s[l]=s[r]
//             maxi = 6
//             start=5
//             l=4, r=11
//         l>=0 and r<16 and s[l]=s[r]
//             maxi = 8
//             start=4
//             l=3, r=12
//         l>=0 and r<16 and s[l]=s[r]
//             maxi=10
//             start=3
//             l=2, r=13
//         l>=0 and r<16 and s[l]!=s[r]
// .
// .
// .
// return s.substr(3, 10) = geeksskeeg
            
//-------------------------------------------------------------------------------------------------------------

/*
    Problem: Sum of Beauty of All Substrings

    Given a string s, return the sum of beauty of all its substrings.

    The beauty of a string is defined as the difference in frequencies
    between the most frequent and least frequent characters.

    For example, the beauty of "aaac" is 3 - 1 = 2.


    Example 1:
    Input:  s = "aaac"
    Output: 3

    Explanation:
    The substrings with non-zero beauty are ["aaac", "aac"],
    where the beauty of "aaac" is 2 and the beauty of "aac" is 1.


    Example 2:
    Input:  s = "geeksforgeeks"
    Output: 62

    Explanation:
    There are 91 substrings of "geeksforgeeks".
    The sum of the beauties of all substrings is 62.


    Example 3:
    Input:  s = "aabcb"
    Output: 5

    Explanation:
    The substrings with non-zero beauty are
    ["aab", "aabc", "aabcb", "abcb", "bcb"],
    each with beauty equal to 1.


    Example 4:
    Input:  s = "aabcbaa"
    Output: 17


    Constraints:
    - 1 <= s.length <= 500
    - s consists of only lowercase English letters.
*/

//Brut: Take out all substrings and for each calculate beauty and sum up

int beautyS(string s){
    vector<int> hash(256, 0);
    int n=s.size();
    int maxi = 0 , mini = n;

    for(auto v:s) hash[v]++;


    for(auto v:hash){
        if(mini > v && v!=0) mini = v;
        maxi = max(maxi, v);
    }
    return maxi-mini;
}
//Tc - O(n), SC - O(1)

int sumBeautySubstr(string s){
    int n=s.size();
    int sum=0;
    string temp;

    for(int i=0;i<n;i++){
        temp = "";
        for(int j=i;j<n;j++){
            temp += s[j];
            sum += beautyS(temp);
        }
    }

    return sum;
}
//TC - O(n^3), Sc - O(n)

// aabcb
// a     - 0
// aa    - 0
// aab   - 1
// aabc  - 1
// aabcb - 1
// a     - 0
// ab    - 0
// abc   - 0
// abcb  - 1
// b     - 0
// bc    - 0
// bcb   - 1
// c     - 0
// cb    - 0
// b     - 0
// res = 5

//Optimal: the main loss in time is when creating hash arr we again traverse through substring that we already traversed while creating so maintain a hash arr and update each time a substring with new start is started

int sumBeautySubOpt(string s){
    int n=s.size();
    vector<int> hash; //as constraint says only lowercase alphabets
    int maxi, mini;
    int sum=0;

    for(int i=0;i<n;i++){
        hash = vector<int>(26, 0);

        for(int j=i;j<n;j++){
            hash[(s[j] - 'a')]++;

            for(auto v:hash){
                if(v > 0){
                    maxi = max(maxi, v);
                    mini = min(mini, v);
                }
            }
            sum += (maxi-mini);
            maxi = 0, mini = n;
        }
    }

    return sum;
}
// TC - O(n^2), SC - O(1)

//-------------------------------------------------------------------------------------------------------------

//Check Palindrome: optimal is using 2 pointers already done while doing longest palindromic substring


int main(){
    // char arr[7];
    // cin.getline(arr, 7, '$');
    // cout<<arr<<endl;

    //===================================================

    // string str = "((())(()))(())"; //((())(()))(())
    // // cout<<str;
    // cout<<removeParenthesisOpt(str);

    //===================================================

    // string str = "  the   sky is blue  ";
    // cout<<reverseSentenceOpt(str);

    //===================================================

    // string str="35427";
    // cout<<largestOddOpt(str);

    //===================================================

    // vector<string> arr = {"flower", "flow", "flight"};
    // cout<<longestCommPOptHis(arr);

    //===================================================

    // string s="cddc", t="baba";
    // cout<<CheckIsomorphicOpt(s, t);

    //===================================================

    // string s1="abcd", s2="acbd";
    // cout<<StringRotatBet2(s1, s2);

    //===================================================

    // string s1="geeks", s2="kseeg";
    // cout<<checkAnagramsOpt(s1, s2);

    //===================================================

    // string s="tree";
    // cout<<sortElemsFreqDescOpt(s);

    //===================================================

    // string str = "()((())())";
    // cout<<nestedParenthesis(str);

    //===================================================

    // string str = "LVIII";
    // cout<<romanToIntCl(str);

    //===================================================

    // string str = "  -0012gfg4";
    // cout<<atoiCorrect(str);

    //===================================================

    // string str = "abcd";
    // aboutSubstrings(str);

    //===================================================

    // string str = "forgeeksskeegfor";
    // cout<<longPalSubstrOpt(str);

    //===================================================

    string str = "aabcb";
    cout<<sumBeautySubOpt(str);


    return 0;
}