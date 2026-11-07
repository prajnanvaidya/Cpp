#include<bits/stdc++.h>

using namespace std;

//DP
// Ways to solve DP PRoblems:
// 1. Tabulation  - Bottom Up DP
// 2. Memoization - Top down DP


// Each Problem will have:
// 1. Memoization solution its TC and SC 
// 2. Tabulation solution: its TC and SC 
// 3. Space Optimization

//-----------------------------------------------------------------------------------------------------------------------
// Ex: Fibonacci no:
// 0 1 1 2 3 5 8 ...

// By recursion:
int fib(int n){
    if(n<=1) return n;
    return fib(n-1)+fib(n-2);
}
//TC - O(2^n), SC - O(n)

// Using memoization: i.e not finding the value for same input again and again 

// fib(5) = 5
//         fib(5)
//         /  \
//     fib(4) fib(3)
//     /  \      
// fib(3) f(2) {we are again finding f(2) although we already found it}  
//  /     \    
// f(2)=1 f(1)
// /   \
// f(1) f(0)
// 1     0

// Inorder to keep track of what we alrady found we maintain a hash table where it will store result of already found stuff

int fibmemo(int n, vector<int>& dp){
    if(n<=1) return n;
    
    if(dp[n] != -1) return dp[n];
    dp[n] = fibmemo(n-1, dp)+fibmemo(n-2, dp);
    return dp[n];
}

// fib(5) = 5
//         fib(5)=5
//         /    \
//     fib(4)=3 fib(3)=2
//     /    \      
// fib(3)=2 f(2)=1
//  /     \    
// f(2)=1 f(1)
// /   \    1
// f(1) f(0)
// 1     0

// dpth - n, no of calls in each depth - 1
// So TC - O(n), SC - O(n + n) {recursion stacvk place + memo Arr}
//Memo is top down appproach as recxursin: i.e go from top starting point to bottom 0,1 and come back to get answer 

//Tabularization: Bottom up approach: i.e go from base case to required answer
// We first assign base case value to dp[0]=0, dp[1]=1
// And we build up fib(n) from 2 to upto n, and return dp[n]

int fibTab(int n, vector<int>& dp){
    for(int i=2;i<=n;i++){
        dp[i] = dp[i-1] + dp[i-2];
    }
    return dp[n];
}
//TC - O(n), SC - O(n) {no stack space}

// 3.Space optimization: SC- O(1)

int fibTabSC(int n, int prev=1, int prev2=0, int i=2 ){
    if(i == n){
        return prev + prev2;
    }
    return fibTabSC(n, prev+prev2, prev, i+1);
}
//TC - O(n), SC - O(1) but stack space - O(n)

// So use loop in space opt:
int fibTabSCL(int n){
    int prev2=0;
    int prev=1;
    for(int i=2;i<n;i++){
        int cur = prev + prev2;
        prev2 = prev;
        prev = cur;
    }
    return prev+prev2;
}
//TC - O(n), SC - O(1)

//-----------------------------------------------------------------------------------------------------------------------

//Climb n stair 

//Given n stairs
//Start from 0th stair
//Each time can climb 1 stair or 2 stairs
//Supposed to return no of distinct ways in which u can climb the nth stair

// Ex:
// n=3, res = 3
// [image-comments/image-20261107-034732-ldfogj.png]

// How do u know a problem is DP
// In questions where they ask: Count distinct ways or 
// If there can be multiple ways doing something and they asku about Min Output or Max Output  of that

// Whnever the concept of try all possible ways comes in where they ask Count or figure out Best way
// In that cases u apply recursion
// Inorder to count or find best the brut is u should perform all possible ways and return from it

// Note: Shortcut to solve DP problems:
// 1. Try to represent a problem in terms of index
// 2. Do all possible stuffs on that index according to the Problem statement
// 3. if quest states count all stuff: Sum up all stuffs
//     if ques states find min: Take min(all stuffs)
//     if ques states find max: Take max(all stuffs)

// Count all possible ways to reach nth stair:
// 1. Treating each step as ind
// So we need no of ways to reach from 0 to n 

// Base case: standing at 0th stair: res = 1
// So:
// f(n){
//     if(n==0) return 0;

//     left = f(n-1);  //jumping 1 step at a time
//     right = f(n-2); //jumping 2 steps at a time

//     return left+right; //inorder to count all ways 
// }
// But there is a edge case what if n=1 then n-1=-1 So its a problem, need to add a edge when n=1 then res=1
// f(n){
//     if(n<=1) return n;

//     return f(n-1)+f(n-2);
// }

// So the problem is same as fibonacci 
// Where for each step the result is sum of its previous possible way and before-prev possible way

// But constraint in question:
// 0 <= N <= 10^18
// So in Space optimized TB Fib we use a for loop and we cannot loop till 10^18 (limit: 10^8 or 9)
// So O(n) is not popsible here 
// So it should be solved by Matrix Exponention which takes O(logn)

//-----------------------------------------------------------------------------------------------------------------------

//Frog Jump
// PS: // [image-comments/image-20261107-043108-b27hmc.png]
// [image-comments/image-20261107-043139-o52kkp.png]
// [image-comments/image-20261107-043159-x0defl.png]

int frogJump(int n, vector<int>& height){
    if(n==0){
        return 0;
    }
    int One_step = frogJump(n-1, height)+abs(height[n]-height[n-1]);
    int Two_step;
    if(n-2>=0) 
        Two_step = frogJump(n-2, height) + abs(height[n]-height[n-2]);
    else
        Two_step = INT_MAX;
    
    return min(One_step, Two_step);
}
//TC - O(2^n), SC - O(n)

//Now whether in this question does it have any overlaping subproblem?
// Consider: 
//  0   1   2   3   4   5
// 30, 10, 60, 10, 60, 50

//         f(5)
//         /  \ 
//      f(4)  f(3)
//       /  \ 
//     f(3) f(2)
//     /   \ 
//   f(2)  f(1) {already calculated}
//   /  \     
// f(1) f(0) 
//  /  \ 
// f(0) f(-1)
// Hence there exist

//Using memoization by using a arr[n+1]

int frogJumpMemo(int n, vector<int>& height, vector<int>& dp){
    if(n==0){
        return 0;
    }
    if(dp[n] != -1){
        return dp[n];
    }

    int left = frogJumpMemo(n-1, height, dp) + abs(height[n] - height[n-1]);
    int right;

    if(n>1)
        right = frogJumpMemo(n-2, height, dp) + abs(height[n] - height[n-2]);
    else 
        right = INT_MAX;

    dp[n] = min(left, right);
    return dp[n];
}
//TC - O(n), SC - O(2*n)
//Top down approach

//Using Tabularisation: bottom up
// dp[0]=0, dp[1] = abs(height[1] - height[0])

int frogJumpTab(int n, vector<int>& height, vector<int>& dp){
    for(int i=1;i<=n;i++){
        int left = dp[i-1] + abs(height[i] - height[i-1]);
        int right;
        if(i>1)
            right = dp[i-2] + abs(height[i] - height[i-2]);
        else 
            right = INT_MAX;

        dp[i] = min(left, right);
    }
    return dp[n];
}
//TC - O(n), SC - O(n)

//Space optimization
// Our right depends dp[i-2] and left depends on dp[i-1] so only 2 we have to maintain dp[i-1] as prev and dp[i-2] as prev2

int frogJumpTabSC(int n, vector<int>& height){
    if(n==1) return 0;
    int prev2 = 0;
    int prev = abs(height[1] - height[0]);
    for(int i=2;i<=n;i++){
        int left = prev + abs(height[i]-height[i-1]);
        int right = prev2 + abs(height[i]-height[i-2]);

        prev2 = prev;
        prev = min(left, right);
    }
    return min(prev, prev2);
}
//TC - O(n), SC - O(1)

int frogJumpTabScHis(int n, vector<int>& height){
    int prev2=0, prev=0, curi;
    for(int i=1;i<n;i++){
        int fs = prev + abs(height[i]-height[i-1]);
        int ss = INT_MAX;
        if(i>1) ss = prev2 + abs(height[i]-height[i-2]);
        curi = min(fs, ss);
        prev2 = prev;
        prev = curi;
    }
    return curi;
}

//-----------------------------------------------------------------------------------------------------------------------

//Follow up to previous 
// previous said frog can jump i-1, i-2
// But now say frog can jump k distance, i-1, i-2, i-3, ..., i-k

//If so then at 1 depth there could be k functon calls taking TC to O(k^n)

int frogJumpK(int n, int k, vector<int>& height){
    if(n==0){
        return 0;
    }
    vector<int> kCal(k, 0);
    for(int i=0;i<k;i++){
        if(n-(i+1)>=0) 
            kCal[i] = frogJumpK(n-(i+1), k, height) + abs(height[n] - height[n-(i+1)]);
        else
            kCal[i] = INT_MAX;
    }
    return *(min_element(kCal.begin(), kCal.end()));
}
//TC - O(k^n), SC - O(n + k)

int frogJumpKMemo(int n, int k, vector<int>& height, vector<int>& dp){
    if(n==0){
        return 0;
    }
    if(dp[n] != -1) return dp[n];
    vector<int> kCall(k, -1);
    for(int i=0;i<k;i++){
        if(n-(i+1) >= 0) kCall[i] = frogJumpKMemo(n-(i+1), k, height, dp) + abs(height[n]-height[n-(i+1)]);
        else kCall[i] = INT_MAX;
    }
    dp[n] = *(min_element(kCall.begin(), kCall.end()));
    return dp[n];
}
//TC - O(n*k), SC - O(n + k + n)

// But we can reduce intermediate k vector size by just maintaining a mini variable
int frogJumpKMemoOpt(int n, int k, vector<int>& height, vector<int>& dp){
    if(n==0){
        return 0;
    }
    if(dp[n] != -1) return dp[n];
    int mini = INT_MAX;
    for(int i=0;i<k;i++){
        if(n-(i+1) >= 0) mini = min(mini, frogJumpKMemoOpt(n-(i+1), k, height, dp) + abs(height[n]-height[n-(i+1)]));
        else break;
    }
    dp[n] = mini;
    return dp[n];
}
//TC - O(n*k), SC - O(n+n)

//Tabularisation: Bottom up approach

int frogJumpTab(int n, int k, vector<int>& height, vector<int>& dp){
    int mini;
    for(int i=1;i<=n;i++){
        mini = INT_MAX;
        for(int j=0;j<k;j++){
            if(i-(j+1)>=0) mini = min(mini, dp[i-(j+1)]+abs(height[i] - height[i-(j+1)]));
        }
        dp[i] = mini;
    }
    return dp[n];
}
//TC - O(n*k), SC - O(1)

//Space Optimization
// Here belive, u should require just a arr[k+1] and not arr[n+1]
int frogJumpTabSc(int n, int k, vector<int>& height) {
    if(n <= 1) return 0;

    vector<int> kprev(k, INT_MAX);
    kprev[0] = 0;  // dp[0]

    for(int i = 1; i < n; i++) {
        int curr = INT_MAX;

        for(int j = 1; j <= k && i-j >= 0; j++) {
            curr = min(curr,
                kprev[j-1] + abs(height[i] - height[i-j]));
        }

        // Shift previous K states
        for(int j = k-1; j > 0; j--) {
            kprev[j] = kprev[j-1];
        }

        kprev[0] = curr;
    }

    return kprev[0];
}
//Tc - O(n*k), SC - O(k)


int frogJumpTabSc(int n, int k, vector<int>& height){
    if(n<=1) return 0;
    vector<int> kprev(k+1, INT_MAX);
    kprev[0]=0;
    for(int i=1;i<n;i++){
        int cur = INT_MAX;
        for(int j=0;j<=k;j++){
            if(i-j>=0) cur = min(cur, kprev[(i-j)%(k+1)] + abs(height[i] - height[i-j]));
            else break;
        }
        kprev[i%(k+1)] = cur;
    }
    return kprev[(n-1)%(k+1)];
}
//Too difficult at this momement

//As per difficulty in here taking space from O(n) to O(k) is not that better in terms of complexity

//----------------------------------------------------------------------------------------------------------

//Maximum sum of non adjacent elements



int main(){

    // //Memo fib
    // int n=8;
    // vector<int> dp(n+1, -1);
    // // cout<<fibmemo(8, dp);

    // //Tab
    // dp[0]=0;
    // dp[1]=1;
    // // cout<<fibTab(8, dp);

    // //SC
    // cout<<fibTabSCL(8);

    //=====================================

    vector<int> height = {10, 20, 30, 10};
    int n=3;
    vector<int> dp(n+1, -1);
    dp[0] = 0; 
    cout<<frogJumpTabSc(n,2,height);

    
    return 0;
}