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
// - with space if u want to input use: cin.getline(var_name, length, delimeter); by default delimeter is "\n", where len is len of input u want to take in     

// - String is a class built for ease of use instead of char arr 
// - string str="Hello"


int main(){
    char arr[7];
    cin.getline(arr, 5);
    cout<<arr<<endl;



    return 0;
}