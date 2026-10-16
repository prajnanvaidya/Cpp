#include<bits/stdc++.h>
using namespace std;

// Majority element prblm - find elem in arr which appears more than n/2 times
//Ex: 2 2 3 3 1 2 2 - n=7, n/2=3, res=2

//Brute: for each elem calculate the occurence if its >n/2 then return elem
int MajorityBrute(vector<int> a, int n){
    int k=n/2;
    int count, temp;
    for(int i=0;i<n;i++){
        count=1;
        temp=a[i];
        for(int j=i+1;j<n;j++){
            if(a[j]==temp)
                count++;
        }
        if(count>(n/2)){
            return a[i];
        }
    }
    return -1;
}
//TC: near to O(n^2), SC:O(1)

//Using hashing: key - unique elem, val - frequency
int MajorityBetter(vector<int> a, int n){
    map<int, int> mpp;
    // for(int i=0;i<n;i++){
    //     if(mpp.find(a[i])!=mpp.end()){
    //         mpp[a[i]]++;
    //     }
    //     else{
    //         mpp[a[i]]=1;
    //     }
    // }
    //instead of above u could just
    for(int i=0;i<n;i++)
        mpp[a[i]]++;  //As map in cpp is capable to create if notexist with 0 as default val with statement mpp[a[i]] and doing ++ changes val to 1

    for(auto v:mpp){
        if(v.second>(n/2))
            return v.first;
    }
    return -1;
}
//TC: O(nlogn + n) - map, O(n*1 + n) - unordered map ->in worst case
//SC: O(n) - in worst case


//Moore's voting algorithm
// As it says voting it predicts that a perticular element may be the majority element it doesnt guarantees
//U will maintain 2 things - elem, count - and iterate upto arr size and check whether each time if count=0, then initialize elem with current val and if count!=0 then if curr elem is same as elem then increment cnt or else decrement. 
// At last check the cnt of elem in entire arr by iterating again and check if cnt is greater than n/2  - this is to guarantee the claim of Moores voting

//Dry run:
// 7 7 5 7 5 1 5 7 5 5 7  7  5  5  5  5
// 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
// elem    index
//   7       
// cnt=1     0
// cnt=2     1
// cnt=1     2
// cnt=2     3
// cnt=1     4
// cnt=0     5
// for arr - 7 7 5 7 5 1, n=6, n/2=3, no elem is majority

//  5        
// cnt=1     6
// cnt=0     7
// arr - 5 7, n=2, n/2=1,   

//  5
// cnt=1     8
// cnt=2     9
// cnt=1     10
// cnt=0     11
// arr - 5 5 7 7 

//  5
// cnt=1     12
// cnt=2     13
// cnt=3     14
// cnt=4     15
// probable majority element = elem = 5

// veerification: 
// loop from index 0 to 15 count 5, count=9>n/2
// res=5

//If given arr was 7 7 5 7 5 1 5 7 5 5 7  7  1 1 1 1 now elem=1, but count=4<n/2 hence no majority elem

//In moores voting the verification looping can be skipped if mentione in question the given arr will always have a majority elem

int MajorityMooresOptimal(vector<int> a, int n){
    int elem, count=0;
    for(int i=0;i<n;i++){
        if(count==0){
            elem=a[i];
            count++;
        }
        else if(elem==a[i])
            count++;
        else
            count--;
    }
    int cnt=0;
    for(int i=0;i<n;i++){
        if(a[i]==elem)
            cnt++;
    }
    if(cnt>(n/2))
        return elem;
    return -1;
}



int main(){
    int n, elem;
    cin>>n;
    vector<int> arr;
    for(int i=0;i<n;i++){
        cin>>elem;
        arr.push_back(elem);
    }
    int res=MajorityMooresOptimal(arr, n);
    cout<<res<<endl;
}