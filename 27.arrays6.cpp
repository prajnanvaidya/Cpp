#include<bits/stdc++.h>

using namespace std;

//Find count of subarrs whose XOR(i.e xor every element in whicever order) equals target
//Given a arr and target_xor, return count of subarr

//Brute: form all possible subarrs 1 by 1 and measure their xor equals target
int CntSubXOR(vector<int>& arr, int target){
    int cnt=0;

    int x;
    for(int i=0;i<arr.size();i++){
        x=0;
        for(int j=i;j<arr.size();j++){
            x = (x^arr[j]);
            if(x == target)
                cnt++;
        }
    }
    return cnt;
}
//Tc - o(n^2), SC - o(1)

//Optimal: Using prefix xors map as we did for counting subarr with given sum for arr including negatives

int CntSubXOROpt(vector<int>& arr, int target){
    int cnt=0;
    int x=0;
    unordered_map<int, int> pXor;
    pXor[x]++;

    for(int i=0;i<arr.size();i++){
        x^=arr[i];
        int prevSubXor = x^target;
        cnt += pXor[prevSubXor]; //Can be kept as is no need to check does prevSubXor indeed appears or not as even if doesnt appear then its been filled with 0 so no problem
        pXor[x]++;
    }
    return cnt;
}
//TC - O(n), SC - O(n){in worst case it could generate uniqu xor val each time}

//---------------------------------------------------------------------------------------------------------------------
long long fib(int n){
        if(n==0 || n==1){
            return n;
        }
        return fib(n-1)+fib(n-2);
    }
bool threeFibonacciSum(int n) {
    int cnt=2;
    long long res=fib(cnt);
    long long sum;
    while(res < n){
        sum = fib(cnt-2);
        sum+=fib(cnt-1);
        sum+=fib(cnt);
        
        if(sum==n) return true;
        
        res = fib(++cnt);
    }
    return false;
}

//----------------------------------------------------------------------------------------------------

//Merge Overlaping intervals
//Given arr of pairs or arr of arrs, each elem arr containing 2 nos, 1st start of interval and 2nd end of interval, there are multiple intervals u need to return a arr of arrs such that the intervals are reduced at most as possible based on repeated interval that can come under a higher one

//Ex: (1,3), (2,6), (8,9), (9,11), (8,10), (2,4), (15,18), (16,17)
//Here (1,3), (2,6), (2,4) lie inside (1,6)
//  (8,9), (9,11), (8,10) lie inside (8,11)
//  (15,18), (16,17) lie inside (15, 18)
//Res - (1,6), (8,11), (15,18)

//Inorder to get that might seem difficult but once u sort the input then clears, sort: based on 1st if same then based on 2nd
// sorted: (1,3), (2,4), (2,6), (8,9), (8,10), (9,11), (15,18), (16,17)
// Now we consider a hash Map that stores resultant intervals, how to put those: traverse each interval and consider its first elem as st and second as en now check if our hashmap is not empty if yes then check for whether last arr inside hash's 2nd elem is it greter then the start if yes then choose ur hash's last elem's 2nd elem to be max(end, hash.back()[1]) and if hash is empty then just put in {st, en} in hash or even if hash.back()[1]<st then also we will put {st, en} in hash.


// (1,3), (2,4), (2,6), (8,9), (8,10), (9,11), (15,18), (16,17)
auto MergeOverlapIntercvals(vector<vector<int>>& arr){
    vector<vector<int>> res;

    sort(arr.begin(), arr.end());

    for(int i=0;i<arr.size();i++){
        int st=arr[i][0], en=arr[i][1];
        if((!res.empty()) && res.back()[1]>st){
            res.back()[1] = max(res.back()[1], en);
        }
        else
            res.push_back({st, en});
    }
    return res;
}
//TC - O(n), SC - O(n){in worst case all n intervals may belong to different regions}

//-------------------------------------------------------------------------------------------------------------------

//Merge Sorted Arrs
//2 sorted arrs are given u need to return a 2 sorted arrs as if they are merged

//Ex: [1, 3, 5, 7], [0, 2, 6, 8, 9]
// res = [0, 2, 1, 3], [5, 6, 7, 8, 9]

//Brut: use 2 pointers and take another arr and at last split elements of larger arr into inputs based on their length

void MergeSortedArr(vector<int>& arr1, vector<int>& arr2){
    int i=0, j=0;
    vector<int> res;
    while(i<arr1.size() && j<arr2.size()){
        if(arr1[i]<arr2[j]){
            res.push_back(arr1[i]);
            i++;
        }
        else{
            res.push_back(arr2[j]);
            j++;
        }
    }
    while(i<arr1.size()) res.push_back(arr1[i++]);
    while(j<arr2.size()) res.push_back(arr2[j++]);

    arr1 = vector<int>(res.begin(), res.begin()+arr1.size());
    arr2 = vector<int>(res.begin()+arr1.size(), res.end());
}
//TC - O(n + m), SC - O(n+m)

//Optimal asks sorting merged arrs in place without using O(n+m) space!

//Way 1: we use 2 pointers here: 1 ptr points to last elem of arr1(i.e largest elem), and another ptr to first elem of arr2(i.e to the smallest elem) and loop until i reaches id 0 of arr1 or j reaches id n of arr2, each time: compare them if i>j then swap i,j elem and if i<=j stop and return, why? - as all elems before i is less then i so if i<j then all before are and all rem indices >j are indeed greater then j so if i<j at point done work, at last sort 2 arrs

void mergeSortedArrOpt(vector<int>& arr1, vector<int>& arr2){
    int i=arr1.size()-1, j=0;
    while(i>=0 && j<arr2.size()){
        if(arr1[i]>arr2[j]){
            swap(arr1[i], arr2[j]);
            i--;
            j++;
        }
        else break;
    }
    sort(arr1.begin(), arr1.end());
    sort(arr2.begin(), arr2.end());
}
//TC - O(min(n,m) + nlogn + mlogm), SC - O(1)

//Another way: use concept of shell sort
//Step1: find gap = ciel(n/2)
//Step2: Take 2 pointers such that distance between them is gap times
//Step3: And check until j meets end i.e j<arr2.size()+arr1.size() and i can go outside arr1 too, each time check i>j if yes swap otherwise do nothing and increment i and j
//Step4: Once a gap ptr meet ends again modify gap = ciel(gap/2) and follow step3 until gap=1

//Ex: 
// 0 1 2 3  4 5 6 7 8
// 1 3 5 7  0 2 6 8 9

// gap=9/2=4.5=5
// i=0, j=5, 
// res: 0 1 2 3  4 5 6 7 8
//      1 3 5 7  0 2 6 8 9

// gap=5/2 = 2.5 = 3
// i=0, j=3
// res: 0 1 2 3  4 5 6 7 8
//      1 0 2 6  3 5 7 8 9

// gap=3/2=1.5=2
// i=0, j=2
// res: 0 1 2 3  4 5 6 7 8
//      1 0 2 5  3 6 7 8 9

// gap=2/2=1
// i=0, j=1
// res: 0 1 2 3  4 5 6 7 8
//      0 1 2 3  5 6 7 8 9

void swapArrElems(vector<int>& arr1, vector<int>& arr2, int i, int j){
    if(arr1[i]>arr2[j])
        swap(arr1[i], arr2[j]);
}

void mergeSortedArrsOptShell(vector<int>& arr1, vector<int>& arr2){
    int n=arr1.size(), m=arr2.size();
    int gap = (n+m)/2 + (n+m)%2;

    while(gap>0){
        int i=0, j=gap;
        while(j < (n+m)){
            if(j<arr1.size()){
                swapArrElems(arr1, arr1, i, j);
            }
            else if(i<arr1.size()){
                swapArrElems(arr1, arr2, i, j-n);
            }
            else{
                swapArrElems(arr2, arr2, i-n, j-m);
            }
            i++;
            j++;
        }
        if(gap==1) break;
        gap = gap/2 + gap%2;
    }
}
//TC - O(log(m+n) * (n+m)), SC - O(1)

//------------------------------------------------------------------------------------------------------------------------------
//Find the repeating and missing number
//Given an arr of n integer and it will have first n natural nos may not be in order and 1 elem out of them is missing and 1 elem is repeating u should return pair {missing, repeating}

//Ex: {4, 3, 6, 2, 1, 1}, n=6

//Brut
auto missingRepeating(vector<int>& arr){
    int n=arr.size();
    vector<int> hash(n+1, 0);
    for(int i=0;i<n;i++){
        hash[arr[i]]++;
    }
    int m=-1, r=-1;
    for(int i=1;i<n;i++){
        if(hash[i]==0)
            m=i;
        else if(hash[i]>1)
            r=i;
        if(m!=-1 && r!=-1) break;
    }
    return make_pair(m, r);
}
//TC - O(n + n), SC - O(n)     

//Optimal: way1: we will use 2 equation to find missing and repeating characters
// 1st eq: sum all arr elems-S
//         sum all naturals til n = n*(n+1)/2 - Sn
//         S-Sn = val1 = repeating-missing = X-Y

// 2nd eq: sum of square all arr elems - S2
//         sum of square of naturals till n - S2n
//         S2 - S2n = val2 = X^2 - Y^2 = (X+Y)*(X-Y)
//         val2 = val1*(X+Y)
//         X+Y = val2/val1 = val3
// solve: X = val3+val1 / 2
//         Y=X-val1

vector<int> MissingRepeatOpt1(vector<int>& arr){
    int n=arr.size();
    long long S=0, Sn=0, S2=0, S2n=0;
    for(int i=0;i<n;i++){
        S += arr[i];
        Sn += i+1;
        S2 += (long long)arr[i]*arr[i];
        S2n += (long long)(i+1)*(i+1);
    }
    long long val1 = S-Sn;
    long long val2 = S2 - S2n;
    long long val3 = val2/val1;

    int missing = (val3+val1)/2;
    int repeating = missing - val1;

    vector<int> res = {missing, repeating};
    return res;
}

//About type casting:
/*
NOTE: C++ Type Conversion & Overflow

1. The operands decide the type of an operation, NOT the variable receiving the result.

   int + int       -> int
   int * int       -> int
   int / int       -> int
   int + long long -> long long
   long long * int -> long long

2. If both operands are int and the result may exceed int range,
   convert/cast ONE operand before the operation:

   long long x = (long long)a * b;
   long long x = (long long)a + b;

   Wrong:
   long long x = a * b;   // multiplication happens as int first

3. If one operand is already long long, no cast is needed:

   long long a;
   long long x = a * b;   // b can be int

4. Assignment to long long does NOT prevent overflow that happened
   during an int operation.

5. For division:
   int / int -> integer division

   long long x = 5 / 2;          // 2
   double x = (double)5 / 2;     // 2.5
*/

//2nd Optimal way: Using Xor method
// 1.Xor all arr elems and naturals upto n
// 2. If u xor then resultant will be: missing ^ repeating = val, because a^a=0, 0^a=a, as repeating occurs 3 times it remains and missing occurs only once so it remains
// 2. In the result val find first set bit from left for this we use & (and operator), we and by 1 to every position of val if result is not 0 then it means that bit is set
// 3. Once found the missing bit then classify all ur arr elems and naturals to 0 group and 1 group based on their bit at missing position found
// 4. Then xor all elems in each group, the resultant u get in each group is one of missing or repeating
// 5. Inorder to find the which is actual missing and repeating u do a loop through arr and return finding

vector<int> missingRepeatingXor(vector<int>& arr){
    int xr=0;
    int n=arr.size();
    //Xoring
    for(int i=0;i<n;i++){
        xr = xr^arr[i];
        xr = xr^(i+1);
    }

    //Finding 1st set bit from left
    int bitno=0;
    while(1){
        if((xr&(1<<bitno)) != 0){
            break;
        }
        bitno++;
    }

    //Classifying all elems into gangs
    int zrGang=0, onGang=0;
    for(int i=0;i<n;i++){
        if((arr[i] & (1<<bitno)) != 0){
            zrGang = zrGang^arr[i];
        }
        else{
            onGang = onGang^arr[i];
        }
    }
    for(int i=0;i<n;i++){
        if(((i+1) & (1<<bitno)) != 0){
            zrGang = zrGang^(i+1);
        }
        else{
            onGang = onGang^(i+1);
        }
    }

    //Checking which one is what
    int miss, rep, cnt=0;
    for(int i=0;i<n;i++){
          if(arr[i] == zrGang){
            rep = arr[i];
            cnt++;
          }
          if(cnt>0) break;
    }
    if(cnt == 0){
        rep = onGang;
        miss = zrGang;
    }
    else{
        miss = onGang;
    }
    vector<int> ans = {miss, rep};
    return ans;
}

//--------------------------------------------------------------------------------------------------------------------------------

//Count inversions in an arr
//Given arr need to return count of inversions possible or pair of elems such that i<j and arr[i]>arr[j]

//Ex: {5, 3, 2, 4 , 1}
// res:
// (5,3)
// (5,2)
// (5,4)
// (5,1)
// (3,2)
// (3,1)
// (2,1)
// (4,1)

//Brut:
int cntInversionsBrut(vector<int>& arr){
    int n=arr.size();
    int cnt=0;
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            if(arr[i]>arr[j]) cnt++;
        }
    }
    return cnt;
}
//TC - O(n^2), Sc - O(1)

//Optimal
//We use merge sort, in merge sort it divided the arr into 2 parts, and each part is furthr divided until left arr with 1 elem and further step up merged arr is formed by 2 pointer techique, thats how at last we get sorted arr in O(nlogn)
//Here while merging 2 sorted arr we calculate the cnt putting a condition such a[left]>a[right] if so then increment count by remaining elem i.e mid-left where left=low, right=mid+1(which is starting of 2nd arr)


int merge(vector<int>& arr, int low, int mid, int high){
    int i=low, j=mid+1;
    vector<int> temp;
    int cnt=0;
    while(i<=mid && j<=high){
        if(arr[i]<arr[j]){
            temp.push_back(arr[i]);
            i++;
        }
        else{
            cnt+=mid-i+1;
            temp.push_back(arr[j]);
            j++;
        }
    }
    while(i<=mid) temp.push_back(arr[i++]);
    while(j<=high) temp.push_back(arr[j++]);

    for(int i=low;i<=high;i++){
        arr[i] = temp[i-low]; 
    }
    return cnt;
}

int mergeSort(vector<int>& arr, int low, int high){
    int cnt=0;
    if(low>=high) return cnt;

    int mid = low+(high-low)/2;
    cnt+=mergeSort(arr, low, mid);
    cnt+=mergeSort(arr, mid+1, high);
    cnt+=merge(arr, low, mid, high);
    return cnt;
}
//TC - O(nlogn), SC - o(n){for temp}

//------------------------------------------------------------------------------------------------------------------------------


int main(){

    // vector<int> arr = {4,2,2,6,4};
    // cout<<CntSubXOR(arr, 6);

    // vector<vector<int>> arr = {
    // {1, 3},
    // {2, 6},
    // {8, 9},
    // {9, 11},
    // {8, 10},
    // {2, 4},
    // {15, 18},
    // {16, 17}
    // };

    // auto res = MergeOverlapIntercvals(arr);

    // for(auto v:res){
    //     for(auto i:v)
    //         cout<<i<<" ";
    //     cout<<endl;
    // }

    //==================================================

    // vector<int> arr1={1, 3, 5, 7};
    // vector<int> arr2={0, 2, 6, 8, 9};

    // mergeSortedArrsOptShell(arr1, arr2);
    // for(auto v:arr1) cout<<v<<" ";
    // cout<<endl;
    // for(auto v:arr2) cout<<v<<" ";

    //==================================================

    // vector<int> arr = {4, 3, 6, 2, 1, 1};
    // auto pr = missingRepeatingXor(arr);
    // for(auto v:pr) cout<<v<<" ";

    //==================================================

    vector<int> arr={5, 3, 2, 4 , 1};
    cout<<mergeSort(arr, 0, arr.size()-1);

    return 0;
}