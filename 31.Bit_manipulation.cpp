
#include<bits/stdc++.h>

using namespace std;

//Converting a decimal to binary
// Divide the no by 2 until it comes down to 1 and each time store reminder and reverse it and return

string DecimalToBinary(int n){
    string res="";
    while(n>0){
        res += char('0' + n%2);
        n=n/2;
    }
    reverse(res.begin(), res.end());
    return res;
}
//TC - O(logn), SC - O(1) Output-O(logn)

//------------------------------------------------------------------------------------------------

//Convert binary to decimal 
//take sum and traverse multiply with 2^index to each elem and update sum

int binaryToDecimalHis(string s){
    int n=s.size();
    int res=0, p2=1;
    for(int i=n-1;i>=0;i--){
        if(s[i] == '1'){
            res += p2;
        }
        p2 *= 2;
    }
    return res;
}

int binaryToDecimal(string s){
    int sum=0;
    int n=s.size();
    for(int i=n-1;i>=0;i--){
        sum+= (s[i]-'0') * pow(2,(n-1)-i);
    }
    return sum;
}
//TC - O(n)

//------------------------------------------------------------------------------------------------

// What comp stores when said
// int x=13;
// Here int is of 4 bytes or 32 bits
// -> comp allocates 32 bits as 000...01101 where 28 0's trail 1101 binary

// Note: long long - 64bits

//-------------------------------------------------------------------------

// 1s compliment - convert decimal to binary and flip bits
// Ex: 23 - 10111
// res - 01000 - 8(dec)

// 3s compliment - find 1s compliment and add 1 to it
// Ex: 25 - 11001
// 1s - 00110 - 6
// add 1 - 00111

//-------------------------------------------------------------------------

// Operator:
// 1.And - all true - true
//       1 false - false
// Ex: 13 & 7 & 9
//     1101
//     0111
//     1001
// res=0001 

// 2.Or - 1 true = true
//        all false = false
// Ex: 13 | 7 | 9
//     1101
//     0111
//     1001
// res=1111 = 15

// 3.Xor - no of 1s odd = 1 (one high one low)
//         no of 1s even=0 (both are high or low)
// Ex: 13 ^ 7 ^ 9
//     1101
//     0111 = 1010
//     1001 = 0011
// res=0011

// 3.Shift 
// - right shift(>>): all bits move right by 1 place and the last bit is removed
// Ex: 13>>1 = 00..001101>>1 = 000..00110 = 6
// 13>>2 = 1101 = 0011 = 3
// 13>>3 = 0001 = 1
// 13>>4 = 0000 = 0

// Note: x >> k = x/2^k

//------------------------------------------------------------------------------------------

// //negative and positive number storing in computer 
// int x = -13
// How computers stores it:
// - the first bit in memory block of int represents sign bit, i.e 31st bit (in 32nd position)
//     - if 31st bit = 0(positive), 1(negative)

// To store negative numbers
// - take its positive no binary and convert its 2s compliment 
// - In 2s compliment result itself the first bit will be 1 representing negative

// Ex: int x = -13
// - 13 = 000..01101
// - 1s = 111..10010
// - 2s = 111..10011 (-13)

//--------------------------------------------------------------------------------------------

// //Largest no that can be stored: for int
// - 01111..11 = 2^30 + 2^29 + 2^28 +...+ 2^1 + 2^0 = 2^31-1 = 10^9

// //Smallest: -2^31 from intuition i.e 10000..000 
// - 1000...00
// - 1s 0111...1
// - add1 1000...0

//-----------------------------------------------------------------------------------------------
   
// - left shift: x<<k move the leftmost of the clip k times and move every left by k place
// Ex: 13<<1 - 000..001101<<1 - 000..011010 = 26

// Note: x<<k = x * 2^k
// What if u do left shift largest no that can be held in int i.e 01111...11 this result in overflow as even if u left u get 11111...10 but this is not (2^31-1)*2 its a negative no So do left shift under boundary to avoid overflow

//------------------------------------------------------------------------------------------------

// 4.Not operator: (~)
// Rules:
// - Flip all including sign bit 
// - Check +ve or -ve by seeing sign bit 
// - If -ve then result is its 2s compliment (while taking in 1st step as u do 1s compliment do not flip sign bit)
// - If +ve then result is same stop

// Ex: x=~(5)
// 0000...0101
// 1111...1010
// its negative
// Take 2s compliment
// 1000...0101
// Add 1:
// 1000...0110 (result) = -2^31 + 2^2 + 2^1

// x=~(-6)
// First take -6
// 0000...0110 = 1111...1001 = 1111...1010

// - 1111...1010
// - 0000...0101
// I(ts positive so the result)

// Note: When u convert binary to decimal if there exist 1 in 31st bit(sign bit) then take -2^31 to add to rest result and just not adding 2^31
// convert: 1111...1010 = -2^31 + 2^30 + 2^29 + 2^28 + ... + 2^3 + 2^2 + 2^1 = -2^31 + (2^31 - 1) - 5 = -6
// convert: 1000...0110 = -2^31 + 2^3 + 2^1

//----------------------------------------------------------------------------------------------------------------

//Swap 2 numbers
void swapNo(int& a, int& b){
    int temp = a;
    a = b;
    b = temp;
}

void swapXor(int& a, int& b){
    a = a^b;
    b = a^b;
    a = a^b;
}
// a = 1101
// b = 1100
// a = a^b = 0001
// b = 1100
// b = a^b = 1101 = 13
// a = 0001
// a = a^b = 1100 = 12

// Note:
// a = a^b
// b = a^b = a^b^b = a
// a = a^b = a^b^a = b

//------------------------------------------------------------------------------------------------------

//Check the ith bit is set or not

// Using left shift
bool checkIBit(int n, int i){
    if(i <= 0) return -1;

    if(n & (1<<(i-1)) == 0) return 0;
    return 1;
}

//Using right shift
bool checkIBitR(int n, int i){
    if(i <= 0) return -1;

    if(((n>>(i-1)) & 1) == 1) return 1;
    return 0;
}
//TC - O(1), SC - O(1) comp performs bitwise operation faster

//-------------------------------------------------------------------------------------------------------------
//Set the ith bit
void setIBit(int& n, int i){
    if(i<=0 || i>31) return;
    n = n | (1<<(i-1));
}
//-------------------------------------------------------------------------------------------------------------

//Clear the ith i bit

void clearIBit(int& n, int i){
    if(i<=0 || i>31) return;
    int j=1, x=0, p=1;
    
    while(j<i){
        x+=p;
        p=p*2;
        j++;
    }
    n = n & (((-2)<<(i-1))+x);
}
//Someway the above is unsafe

//Correct way use not operator(not operator ~ basically flips the bits and checking for sign bit is 1 and taking 1s compliment of first 31 bit and adding 1 is just used to identify decimal equivalent and not operator just flips the bits)

void clearIBitC(int& n, int i){
    if(i<=0 && i>32) return;
    n=n & ~(1<<(i-1));
}
//-------------------------------------------------------------------------------------------------------------------

//Toggle the ith bit
// toggle means change whatever present if 1 make 0 and if 0 make 1

void toggleIBit(int& n, int i){
    if(i<=0 && i>32) return;
    
    n = n ^ (1<<(i-1));
}
//----------------------------------------------------------------------------------------------------------------

//Remove the last set bit
// remove the right most set bit

//Note: when u take n-1 then it will have all 1s after the 1st 1 in n
// Ex: n=16 10000, n-1 = 15 01111
// n=40 101000, n-1 = 39 100111
// n=84 1010100, n-1 = 83 1010011

// Doing N&(N-1) clears the first set bit
// 1010100
// 1010011
// And - 1010000

void removeLastSetBit(int& n){
    n = n&(n-1);
}

//--------------------------------------------------------------------------------------------------------------

//check if a no is power of 2 or not 
bool checkPower(int n){
    if((n&(n-1)) == 0) return 1;
    return 0;
}

//--------------------------------------------------------------------------------------------------------------
//Count the number of set bits
int countSetBits(int n){
    int cnt=0;
    while(n > 0){
        cnt++;
        n = (n&(n-1));
    }
    return cnt;
}
//TC - O(no of ones)

int cntSetBitsHis(int n){
    int cnt=0;
    while(n>0){
        if(n%2 == 1) cnt++;
        n /= 2;
    }
    return cnt;
}
//TC - O(logn)

//Every odd no has the 1st bit to be set, so doing and with 1 yields 1 if no is odd
// check for n is odd: (n%2==1) or better (n&1 == 1)

int cntSetBitsBet(int n){
    int cnt=0;
    while(n > 0){
        cnt += (n&1);
        n = n>>1;
    }
    return cnt;
}

//--------------------------------------------------------------------------------------------------------------

//Minimum set bits to convertt a number 

// Given with start and end both +ve nos
// Need to find no of bits to change from start inorder to convert it to end
//Ex:
// start = 10, end = 7
// 1010, 0111, res = 3

// start=3, end = 4
// 011, 100, res=3

int minSetBits(int s, int e){
    int x = (s^e);
    int cnt=0;
    while(x>0){
        cnt++;
        x = (x&(x-1));
    }
    return cnt;
}

//--------------------------------------------------------------------------------------------------------------

//Power Set
// Given arr print all subsets
// Ex: {1,2,3}
// res = 
// 1
// 1 2
// 1 3
// 1 2 3
// 2
// 2 3
// 3
//Note: power set = subsequence = subset (order should be preserved and elems can be skipped)

// Problem term	Can skip elements?	Must preserve original order?                 No of them
// Subarray	        No	                Yes                                         n(n+1)/2
// Subsequence	        Yes	                Yes                                         2^n
// Subset	            Yes	                No                                          2^n
// Power set	        Yes	                No; it is the collection of all subsets     2^n

//Recursive solution
void printSubset(vector<int>& arr, int index, vector<int>& temp){
    if(index >= arr.size()){
        for(auto v:temp) cout<<v<<" ";
        cout<<endl;
        return;
    }
    temp.push_back(arr[index]);
    index++;
    printSubset(arr, index, temp);
    temp.pop_back();
    printSubset(arr, index, temp);
}

//Inorder to find subarr (contigous selection and order is preserved) - (not sol for power set)
void printSubarr(vector<int>& arr){
    int n=arr.size();
    vector<int> temp;
    for(int i=0;i<n;i++){
        temp.clear();
        for(int j=i;j<n;j++){
            temp.push_back(arr[j]);
            for(auto v:temp) cout<<v<<" ";
            cout<<endl;
        }
    }
}
//Tc - o(n^2), Sc - O(n)

//Printing subarr withouyt using extra space
void printSubarrSOpt(vector<int>& arr){
    int n=arr.size();
    for(int i=0;i<n;i++){
        for(int j=i;j<n;j++){
            for(int k=i;k<=j;k++){
                cout<<arr[k]<<" ";
            }
            cout<<endl;
        }
    }
}

//Power set using bit manipulation
// Ex: {1,2,3}
// No of subsets - 2^n = 1<<n = 1<<3 = 1000 = 8
// No of indices is n=arr.size(), n=3, the split between 0 and 1 is: 
// when    n=3 4 2 1
//         n=4 8 4 2 1
//         n=5 16 8 4 3 2 1

// index:  
//     0:  2 1 0
//     1:  0 0 0 
//     2:  0 0 1
//     3:  0 1 0
//     4:  0 1 1
//     5:  1 0 0
//     6:  1 0 1
//     7:  1 1 0
//     8:  1 1 1
// Note: as can see the split can refernced by decimal nos starting from 0 to 2^n-1

// We can go through each of them and based on in particular index if it hsa 1 then it suggest take that elem if has 0 then do not take it
// it can be achived by:
// i - 0->(n-1)
// if: num & 1<<i != 0 then take that arr[i] in consideration otherwise no

void printPowerSetBit(vector<int>& arr){
    int n=arr.size();
    vector<int> temp;

    for(int i=0;i<(1<<n);i++){ //1<<n = 2^n
        temp.clear();
        for(int j=0;j<n;j++){
            if((i & (1<<j)) != 0){
                temp.push_back(arr[j]);
            }
        }
        for(auto v:temp) cout<<v<<" ";
        cout<<endl;
    }
}
//TC - O(2^n * n), SC - O(n)

//--------------------------------------------------------------------------------------------------------------

//Single Number
// Given arr of nos, all appear twice except 1 return that single elem appearing 1s

//Brut: nested for loops(too simple)
//may be hash
int singleElem(vector<int>& arr){
    int n=arr.size();
    int maxi = *(max_element(arr.begin(), arr.end()));
    vector<int> hash(maxi+1, 0);

    for(int i=0;i<n;i++){
        hash[arr[i]]++;
    }
    for(int i=0;i<maxi+1;i++){
        if(hash[i] == 1) return i;
    }
    return -1;
}
//Tc - O(2*n + max_elem), S - O(max_elem)

//Using bit manp: use xor as n^n = 0 If u xor all remaining is the elem appearing once
int singleElemOpt(vector<int>& arr){
    int n=arr.size();
    int x=arr[0];
    for(int i=1;i<n;i++){
        x = (x^arr[i]);
    }
    if(x==0) return -1;
    return x;
}

//--------------------------------------------------------------------------------------------------------------

//Single no-2
// Given arr where every no appears thrice except 1 return that elem
//Brut: Using hash map

int singleNo2(vector<int>& arr){
    int n = arr.size();
    map<int, int> mpp;

    for(int i=0;i<n;i++){
        mpp[arr[i]]++;
    }
    for(auto v:mpp){
        if(v.second==1) return v.first;
    }
    return -1;
}
//Tc - O(n*logm + m) where m is no of unq elems(m = (n/3)+1), Sc - O(m)

// We calculate total no of set bit for that particula index from 0 to 31 if any no of set bits is not multiple of 3 then it is then its the one set in our result elem
// Ex: {5,5,5,6,4,4,4}
// id: 3210
// 0   0101
// 1   0101
// 2   0101
// 3   0110
// 4   0100
// 5   0100
// 6   0100

//      no of set bits
// id0: 3
// id1: 1
// id2: 7
// id4: 0
// .
// .
// .
// id31:0

// So res has set bits in id1 and id2 = 110

int singleNo2Bet(vector<int>& arr){
    int n=arr.size();
    vector<int> hash(32);

    for(int i=0;i<n;i++){
        for(int j=0;j<32;j++){
            if((arr[i]&(1<<j)) != 0) hash[j]++;
        }
    }
    int res=0;
    int p=1;
    for(int i=0;i<32;i++){
        if(hash[i]%3 != 0){
            res += p;
        }
        p*=2;
    }
    return res;
}
//TC - o(n*32 + 32), Sc - O(32)

int singleNo2betC(vector<int>& arr){
    int n=arr.size();

    int ans=0, cnt;
    for(int i=0;i<32;i++){
        cnt=0;
        for(int j=0;j<n;j++){
            if( (arr[j]&(1<<i)) != 0){
                cnt++;
            }
        }
        if(cnt%3 != 0){
            ans = (ans|(1<<i));
        }
    }
    return ans;
}
//TC - O(32*n), SC - O(1)

//Better: use sorting
int singleNo2Better(vector<int>& arr){
    int n=arr.size();
    sort(arr.begin(), arr.end());
    
    int i=1;
    while(i<n){
        if(arr[i] != arr[i-1])
            return arr[i-1];
        i = i+3;
    }
    if(n%3 !=0)
        return arr[n-1];
    else
        return -1; //thre is no elem appearing once
}
//TC - o(nlogn + n/3), SC - O(1)

// Why above is better then previous which took O(n*32) cuz here we inorder for O(nlogn) to become O(n*32) it has to have n=2^32 > 10^9 so not possible as vector stored in heap and heap constraints

//Optimal: use of buckets
// we will have 3 buckets
// buk1
// buk2
// buk3

// Rule:
// 1. If element not in buk2 then it goes to buk1
// 2. If elem in buk1 then it goes to buk2
// 3. If elem in buk2 then goes to buk3

// Note: the buk3 is not actually needed as we are focusing on elem that appears once
// At last buk1 will have elem appearing once

// Ex: {2,2,2,1}
// - Inorder to check does any buk has arr[i] elem we can either use | or ^
// We use ^ why? see on *
//     So: buk1=2(0010), buk1 ^ arr[0], 2^2 = 0(if it already has 2)
//         buk1=0(0000), buk1 ^ arr[1], 0^2 = 2(as it doesnt have any)

// - Inorder to check whether a buk doesnt have the intended elem use: elem & ~(buk)
//     So: buk1 = 0, buk2 = 2(0010), (buk1^arr[0])&(~buk2) = (0^2)&(~0010) = 2 & (1101) = 0
//         buk1 = 0, buk2 = 0(0000), (0^2)&(~0000) = 2&(1111) = 2
    
// - So the check is: (buk^arr[i]) & (~buk)

// * we use ^ ot | as even though 0|2=2, 0^2=2 but 2^2=0 and 2|2=2 So if elem already their in buk then even | makes it to not delete but to retain that value

// Dry run:
// {2,2,2,1}
// buk1=0
// buk2=0

// i=0:
// check if buk2 has arr[i] if not then add it to buk1
// buk1 = (buk1^arr[i])&(~buk2) = (0^2)&(~000) = 2&(111) = 2
// buk2 = (buk2^arr[i])&(~buk1) = (0^2)&(~010) = 2&(101) = 0

// i=1:
// check if buk1 has elem if yes then put that elem to buk2
// buk1 = (buk1^arr[i])&(~buk2) = (2^2)&(~000) = 0&(111) = 0 (got deleted from buk1)
// buk2 = (buk2^arr[i])&(~buk1) = (0^2)&(~000) = 2&(111) = 2

// i=2:
// check if buk2 has elem if s then add it to buk3(we dont really maintain buk3 here so make buk1 and buk2 empty)
// buk1 = (0^2)&(~010) = 2&(101) = 0
// buk2 = (2^2)&(~000) = 0&(111) = 0

// i=3:
// check if elem exist on buk2 if not put to buk1
// buk1 = (0^1)&(~000) = 1&(111) = 1
// buk2 = (0^1)&(~001) = 1&(110) = 0

// return buk1

int singleElem2Opt(vector<int>& arr){
    int n=arr.size();
    int buk1=0, buk2=0;
    for(int i=0;i<n;i++){
        buk1 = (buk1 ^ arr[i])&(~buk2);
        buk2 = (buk2 ^ arr[i])&(~buk1);
    }
    return buk1;
}
//Tc - O(n), Sc - O(1)

//--------------------------------------------------------------------------------------------------------------

//Single Number - 3
// Given arr where every elem occurs twice except 2 number return those
//Brut: use map

//Optimal: Use buckets 
// Step1: xor all elems of arr, left with: x^y = res, as everything else cancel out and u remain with x and y which appear exactly once
// Step2: Find first set bits from left (as there is atleast 1 bit difference in x and y) say set_bit
// Step3: Separate out all elems of arr based on whether set_bit position is 0 or 1 in them in to buckets one and two
// Step4: xor all elems in 2 buckets and u remain with x and y that appear ones

auto singleElem3(vector<int>& arr){
    int n=arr.size();
    long x=0;
    for(int i=0;i<n;i++){
        x = x^(arr[i]);
    }
    int set_bit = (x & (x-1))^x;
    int buk1=0, buk0=0;
    for(int i=0;i<n;i++){
        if((arr[i] & (set_bit)) > 0 ){
            buk1 = buk1^arr[i];
        }
        else{
            buk0 = buk0^arr[i];
        }
    }
    return make_pair(buk1, buk0);
}
//Tc - O(n), SC - O(1)

// Note: Why take x as long
// Ex: {1,1,0,-2^31}
// now x = -2^31
// so set_bit = x&(x-1)^x = (-2^31)&(-2^31-1)^(-2^31)
// This (-2^31-1) cannot be stored in int operations so making x long will make comp to do long operation and that can hold this no

//--------------------------------------------------------------------------------------------------------------

//Xor of nos in given range
// Given int n return xor of all nos from 1 to n
// Brut: loop from 1 to n and xor and return taking O(n)

//Optimal:
// Observation:
// 1                   = 1
// 1^2                 = 3
// 1^2^3               = 0
// 1^2^3^4             = 4

// 1^2^3^4^5           = 1
// 1^2^3^4^5^6         = 7
// 1^2^3^4^5^6^7       = 0
// 1^2^3^4^5^6^7^8     = 8

// 1^2^3^4^5^6^7^8^9   = 1
// .
// .
// Here pattern repeats after every 4 times, so 
// if:
// n%4 == 0: res = n
// n%4 == 1: res = 1
// n%4 == 2: res = n+1
// n%4 == 3: res = 0

int xorAll(int n){
    int x = n%4;
    if(x == 0) return n;
    else if(x == 1) return 1;
    else if(x == 2) return (n+1);
    else return 0;
}
//Tc - Sc - O(1)

// What if asked between a range giving l and r

int xorAllLR(int l, int r){
    int x = xorAll(l-1);
    int y = xorAll(r);

    return (x^y);
}

//--------------------------------------------------------------------------------------------------------------
//Divide 2 integers without using / operator
// dividend = 22
// divisor = 3
// res = 7

// int range = (-2^31, 2^31-1)
// if: dividend = -2^31 and divisor = -1 then res = (-2^31)/-1 = 2^31 but it cannot be stored at the case return INT_MAX i.e 2^31-1

void divide2IntBrut(int x, int y){
    if(x == INT_MIN && y == -1){
        cout<<INT_MAX<<endl;
        return;
    }
    int sum=0;
    int cnt=0;
    while(sum+y <= x){
        sum+=y;
        cnt++;
    }
    cout<<cnt;
}
//TC - o(x/y)

//Optimal:
// divisor = 3, dividend = 22
// 3 * 7 = 22
// 3 * (2^2 + 2^1 + 2^0) = 3 * (4 + 2 + 1)
void divide2IntOpt(int dividend, int divisor){
    if(dividend == INT_MIN && divisor == -1){
        cout<<INT_MAX<<endl;
        return;
    }
    else if(divisor == 0){
        cout<<"Zero division error"<<endl;
        return;
    }

    long long x = abs(dividend); //Why long long since if divisor is 2^-31 it becomes 2^31 which overflows
    long long y = abs(divisor);

    long long sum=0, p, maxi;
    while(x>=y){
        p=1, maxi = -1;
        for(int i=0;i<32;i++){
            if((x - y*p) >= 0) maxi = p;
            else{
                sum+=maxi;
                x = x - y*maxi;
                break;
            }
            p*=2;
        }
    }
    if((dividend<0 && divisor>0) || (dividend>0 && divisor<0)){
        cout<<'-'<<sum;
        return;
    }

    cout<<sum;
}

int divide2IntOptHis(int dividend, int divisor){
    if(divisor == 0){
        return -1;
    }

    long long x = abs(dividend);
    long long y = abs(divisor);

    int sign=1;
    if( (dividend>0 && divisor<0) || (dividend<=0 && divisor>0)) sign=0;

    int cnt;
    long long sum=0;
    while(x >= y){
        cnt = 0;
        while(x >= (y<<(cnt+1)) ){
            cnt++;
        } 
        sum += (1<<cnt);
        x = x-(y*(1<<cnt));
    }

    if(sum > INT_MAX){
        if(sign) return INT_MAX;
        else return INT_MIN;
    }
    if(sign) return sum;
    else return (-1*sum);
}
//TC - O(log2n * log2n), SC - o(1)

//------------------------------------------------------------------------------------------------------------------------

int main(){

    // int n=8;
    // cout<<DecimalToBinary(n);

    //===================================

    // string s="101";
    // // vector<int> s={1,0,1};
    // cout<<binaryToDecimalHis(s);

    //===================================

    // int a=13, b=12;
    // swapXor(a, b);
    // cout<<a<<" "<<b;

    //===================================

    // cout<<checkIBitR(13, 2); //1101

    //=================================
    // int n=13;
    // setIBit(n, 5);
    // cout<<n;
    //==================================
    // int n=84;
    // removeLastSetBit(n); 
    // cout<<n;
    //==================================
    // int n=16;
    // cout<<checkPower(n);
    //==================================
    // cout<<cntSetBitsHis(29); //11101
    //=================================

    // cout<<minSetBits(10,7);

    //=================================

    // vector<int> arr={1,2,3,4};
    // vector<int> temp;
    // // printSubset(arr, 0, temp);
    // printPowerSetBit(arr);

    //================================

    // vector<int> arr={5,5,5,6,4,4,4};
    // cout<<singleElem2Opt(arr);

    //================================

    // vector<int> arr={2,4,2,14,8,7,7,8};
    // auto p=singleElem3(arr);
    // cout<<p.first<<" "<<p.second<<endl;

    //==================================

    // cout<<xorAllLR(3,6);

    //===============================

    cout<<divide2IntOptHis(22,3);


    return 0;
}