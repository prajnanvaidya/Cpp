#include<bits/stdc++.h>
using namespace std;

//Maximum subarray sum
//Given an array find subarray that gives max sum val out of all subarrays possible
//-2, -3, 4, -1, -2, 1, 5, -3, res = 4 -1 -2 1 5 (7)

//Brutal approach
int MaximumBrute(vector<int> &a, int n){
    int sum=0, maxSum=INT_MIN;
    for(int i=0;i<n;i++){
        for(int j=i;j<n;j++){
            sum=0;
            for(int k=i;k<=j;k++){
                sum+=a[k];
                maxSum=max(sum, maxSum);
            }
        }
    }
    return maxSum;
}
//TC: O(n*3), SC: O(1)

//dry run:
// -2 1 -3 4 -1 2 1 -5 4
//  0 1  2 3  4 5 6  7 8
// n=9
// sum=0, maxSum=-888
// loop: i=0
//     loop: j=0
//         sum=0
//         loop: k=0, k<=0
//             sum=-2
//             maxSum=-2
//     loop: j=1
//         sum=0
//         loop: k=0, k<=1
//             sum=-2
//         loop: k=1, k<=1
//             sum=-1
//             maxSum=-1
//     loop: j=2
//         sum=0
//         loop: k=0; k<=2
//             sum=-2
//         loop: k=1;k<=2
//             sum=-1
//         loop: k=2; k<=2
//             sum=-4
//             maxSum=-1
//     loop: j=3
// The point of this dry run is:
//     outer loop: considers starting point
//     inner loop: considers ending point
//     -> For every new ending point u need new sum, sum=0
//     -> For every ending point i.e j u calculate sum for every subarray with perticular starting point even though all those except one including new ending point i.e  j is already calculated and checked against maxSum during previous ending point i..e j-1.
//     -> The aboove creates redundancy 

//How to kill that redundancy - which comes whole lotely by innermost loop remove and make the inner loop work both as taking the end index of a subarray as well looping from start to end i.e basically at each j taken u are updating already existent sum for starting elem i and checking against maxSum



//Brute
int MaximumBetter(vector<int> &a, int n){
    int sum=0, maxSum=INT_MIN;
    for(int i=0;i<n;i++){
        sum=0;
        for(int j=i;j<n;j++){
            sum+=a[j];
            maxSum=max(sum, maxSum);
        }
    }
    return maxSum;
}
//TC: O(n*n), SC:O(1)

//Optimal
//Kadanes algo
// The main intuition behind the kadanes algo -- consider u start a subarray with i as starting index and go on iterating over ending index j which is like from subarray of 1, 2, .. length if in any j as ending index u get a negative sum then there is no sense in carrying it or checking it for next ending indices as the negative sum just reduces the sum of subarrays only continue if the sum os 0 or positive

//Ex: 
// -2 -3 4 -1 -2 1 5 -3
//  0  1 2  3  4 5 6  7

// start - i=0
// j=0
// sum=-2, no sense in moving j further so, 

// i=1
// j=1, sum=-3

// i=2
// j=2, sum=4, now u can carry it further, maxSum=4
// j=3, sum=3
// j=4, sum=1
// j=5, sum=2
// j=6, sum=7, maxSum=7
// j=7, sum=4

// i=3
// j=3, sum=-1

// i=4
// j=4, sum=-2

// i=5
// j=5, sum=1
// j=6, sum=6
// j=7, sum=3

// i=6
// j=6, sum=5
// j=7, sum=2

// i=7
// j=7, sum=-3

// maxSum=7

//Even though arr is like -3 -2
// i=0:
    // j=0, sum=-3 -> this itself is maxSum on going further witth -ve will decrement sum even if the next term is +ve or -ve

int MaximumOptimalKadaneMine(vector<int> a, int n){
    int sum, maxSum=INT_MIN;
    for(int i=0;i<n;i++){
        sum=0;
        for(int j=i;j<n;j++){
            sum+=a[j];
            maxSum=max(sum, maxSum);
            if(sum<0)
                break;
        }
    }
    return maxSum;
}
//TC: less then O(n*n), SC:O(1)

//Its find out that inner for loop is redundant entirely removing it 
long long MaximumKadaneOptimal(vector<int> a, int n){
    long long sum=0, maxi=LONG_MIN;
    for(int i=0;i<n;i++){
        sum+=a[i];
        maxi=max(maxi, sum);
        if(sum<0)
            sum=0;
    }
    if(maxi<0)
        maxi=0;
    return maxi;
}
//TC: O(n), SC: O(1)
//the last condition means for arr where maxSum is -ve consider u can also have empty subarray so take maxSum=0
//Ex: -4 -3 -2 -1, here by our traditional approach maxSum=-1, but as we also consider empty sbarray as valid maxSum=0

//Now return max subarray
auto MaximumOptimalSub(vector<int> a, int n){
    long long sum=0, maxi=LONG_MIN;
    vector<int> sub;
    int start, end, ansStart;
    for(int i=0;i<n;i++){
        if(sum==0)     //Each time sum becomes 0 take index as start and specific cond is required as start should be initialised to a index at start or not break for arr(2 -1 2 3 4 -5) or just (1 2 3)
            start=i;
        sum+=a[i];
        if(maxi<sum){
            maxi=sum;
            ansStart=start; //its required for another var to store start index as for every time sum<0 it is not guaranteed the output is maximum sum so it breaks for arr (2 -1 2 3 -10 5) 
            end=i;  //As updating maxi so should end be that index where u update maxi
        }

        if(sum<0){
            sum=0;
        }
    }
    for(int k=ansStart;k<=end;k++){
        sub.push_back(a[k]);
    }
    if(maxi<0){
        maxi=0;
        sub.clear();
    }
    return sub;
}
//Dry run:
// 2  -1  2  3  -10  5
// 0   1  2  3   4   5
// n=6, sum=0, maxi=-999
// loop: i=0
//     if: sum=0
//         start=0
//     sum=2
//     if: maxi<sum    
//         maxi=2
//         ansStart=0
//         end=0
//     if: sum>0
// loop: i=1
//     if: sum>0
//     sum=1
//     if: maxi>sum
//     if: sum>0
// loop: i=2
//     if: sum>0
//     sum=3
//     if: maxi<sum
//         maxi=3
//         ansStart=0
//         end=2
//     if: sum>0
// loop: i=3
//     if: sum>0
//     sum=6
//     if: maxi<sum
//         maxi=6
//         ansStart=0
//         end=3
//     if: sum>0
// loop: i=4
//     if: sum>0
//     sum=-4
//     if: maxi>sum
//     if: sum<0
//         sum=0
// loop: i=5
//     if: sum=0
//         start=5
//     sum=1
//     if: maxi>sum //Here u see anStart is not updated to start(5) since the subarray did not give max o/p
//     if: sum>0
// Final - ansStart=0, end=3, 2 -1 2 3



//Using kadane if want to return indices of subarr start and end!
pair<int, pair<int, int>> submaxBet(vector<int>& arr){
    int sum=0;
    int i=0, j=0,v,u;
    int maxi=INT_MIN;
    while(i<arr.size() && j<arr.size()){
        sum+=arr[j];
        if(sum>maxi){
            v=i;
            u=j;
            maxi=sum;
        }
        if(sum<=0){
            sum=0;
            j++;
            i=j;
        }
        else{
            j++;
        }
    }
    return {maxi, {v,u}};
}
//TC - O(n), SC - O(1)

int main(){
    int n;
    cin>>n;
    vector<int> a;
    int elem;
    for(int i=0;i<n;i++){
        cin>>elem;
        a.push_back(elem);
    }

    auto msub=MaximumOptimalSub(a, n);
    for(auto v:msub){
        cout<<v<<" ";
    }
    return 0;
}