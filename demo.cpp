#include<bits/stdc++.h>

using namespace std;


//Implement Min stack
// that gives operations as:
// - push
// - pop
// - top
// - size
// - getMin - which gives min elem of stack 

//one brut way is scan through stack can take O(n + n) n for scanning and poping and  n for reinputing all elems back also need anothre stack in that case

//Better use stack<pair> which stores the cur_val and min and updates min simultaneously

class minStack{
    private:
    stack<pair<int, int>> st;

    public:
    void push(int n){
        if(st.empty()){
            st.push({n,n});
            return;
        }
        if(st.top().second > n){
            st.push({n, n});
        }
        else{
            st.push({n, st.top().second});
        }
    }

    void pop(){
        if(st.empty()){
            cout<<"Stack is Empty!"<<endl;
            return;
        }
        st.pop();
    }

    int top(){
        if(st.empty()){
            cout<<"Stack is empty!";
            return -1;
        }
        return st.top().first;
    }

    int size(){
        return st.size();
    }

    int getMin(){
        if(st.empty()){
            cout<<"Stack is empty!: ";
            return -1;
        }
        return st.top().second;
    }

};
//TC - O(1) for all, Sc - O(2*n) as for each elem we maintain a pair

//Optimal approach:
// - It follows the ides of maintaining min var and update each time we see a elem pushing to stack
// - Ex: st.push(12) min=12
//       st.push(15) min=12
//       st.push(10) min=10
//       st.pop() min=10 but min should be 12 but there is no way we can go back to see previous min

// - Maintain a min variable
// - formual: 2*cur_val-min everytime u push elem to stack pass the result of formula
// - when poped the stack_top < min, then modify min as min = 2*min-stack_top, which gives previous min 
// - If poped stack_top > min, then just pop it out no need to modify min

// All this comes from formula: when pushd_val < min, 2*pushed_val - previous_min = result, where always result < min, u push result to stack and not pushed_val and later update min=pushed_val

class minStackOpt{
    private:
    stack<int> st;
    int min=INT_MAX;

    public:
    void push(int n){
        if(st.empty()){
            st.push(n);
            min=n;
            return;
        }
        if(min > n){
            int x = 2*n-min;
            st.push(x);
            min=n;
        }
        else{
            st.push(n);
        }
    }

    void pop(){
        if(st.empty()){
            cout<<"Stack is empty!"<<endl;
            return;
        }
        if(st.top() < min){
            min = 2*min-st.top();
            st.pop();
        }
        else{
            st.pop();
        }
    }

    int top(){
        if(st.empty()){
            cout<<"stack is empty!";
            return -1;
        }
        if(st.top() < min){
            return min;
        }
        return st.top();
    }

    int size(){
        return st.size();
    }

    int getMin(){
        if(st.empty()){
            cout<<"Stack is empty!: ";
            return -1;
        }
        return min;
    }

};

//TC - O(1) for all, SC - O(n) only for stack

//-------------------------------------------------------------------------------------------------------

//Next Greater Element;
//Monotonic stack - elements in stack are stored in specific order like increasing, decreasing or custom order
// U need to return a arr that has NGE for every elem in input arr
//nge is find the first greater elem that is greater then current elem if not found put -1 to its place

//Ex: {6,0,8,1}, res = {8,8,-1,3,-1} (-1 when there is no greater elem on right of arr)

//Brut O(n^2) for each elem traverse all right elem to find greatest
auto NGEBrut(vector<int>& arr){
    vector<int> res(arr.size());
    int grt;
    for(int i=0;i<arr.size()-1;i++){
        grt=-1;
        for(int j=i+1;j<arr.size();j++){
            if(arr[j]>arr[i]){
                grt=arr[j];
                break;
            }
        }
        res[i] = grt;
    }
    res[arr.size()-1] = -1;
    return res;
}
//TC - O(n^2), Sc - o(n){output space}


//Optimal: Use stack and traverse from back inorder to know elems after a particular cuz thats what needed for finding the next greater elem then the current one

//Each time as u traverse compare elem to top of stack if top smaller then current then pop the stack and go on if stack empty and u not got elem which is greater then the current tehn put -1 to that

// Note: Even though u removed a elem from stack as it was smaller then cur_elem it doesnt effect as even though there is a elem lesser then the removed on left then even its next greater elem would be cur_elem rather then the removed one


auto NGEOpt(vector<int>& arr){
    stack<int> st;
    int n=arr.size();
    vector<int> res(n);

    for(int i=n-1;i>=0;i--){
        while(!st.empty() && st.top() <= arr[i]){
            st.pop();
        }
        if(st.empty()){
            res[i] = -1;
        } 
        else{
            res[i] = st.top();
        }
        st.push(arr[i]);
    }
    return res;
}
//TC - O(2*n){worst case}, SC - O(n){auxillary}

//--------------------------------------------------------------------------------------------------------
// Next greater element part-2
// Same as part 1 but if u didnt get anything on right that is greater then the current then u go circular start searching on left of current elem until u get any if not only then u g with -1
//So for a elem u cannot get next greater elem part 2 only when that particular element is greatest of all in arr

//Ex; 
// 0   1   2  3   4
// 2, 10, 12, 1, 11

// res = 10, 12, -1, 11, 12

//Brut
auto NGEPart2(vector<int>& arr){
    int n=arr.size();
    vector<int> res;

    for(int i=0;i<n;i++){
        int j=(i+1)%n;
        while(j!=i){
            if(arr[j] > arr[i]){
                res.push_back(arr[j]);
                break;
            }
            j = (j+1)%n;
            if(j==i) res.push_back(-1);
        }
    }
    return res;
}
//TC - O(n^2), SC - O(n){output space}

//Optimal: By using monotonic stack
//Take a stack
//Traverse from last and each time u found a elem<st.top() push it if else then pop from stack until u get to elem<st.top()
//again traverse from last now update the res

auto NGE2Opt(vector<int>& arr){
    stack<int> st;

    int n=arr.size();
    vector<int> res(n);
    for(int i=n-1;i>=0;i--){
        while(!st.empty() && arr[i] > st.top()){
            st.pop();
        }
        st.push(arr[i]);
    }

    for(int i=n-1;i>=0;i--){
        while(!st.empty() && arr[i] >= st.top()){
            st.pop();
        }
        if(st.empty()){
            res[i] = -1;
        }
        else{
            res[i]=st.top();
        }
        st.push(arr[i]);
    }
    return res;

}
//TC - O(2*n + 2*n), SC - o(2*n + n) {since at worst case stack can store elems near to 2*n}

//His way: To do both works in 1 loop
auto NGEOptHis(vector<int>& arr){
    int n=arr.size();
    vector<int> res(n);
    stack<int> st;

    for(int i=2*n-1;i>=0;i--){
        while(!st.empty() && arr[i%n] >= st.top()){
            st.pop();
        }
        if(i<n){
            (st.empty())?res[i]=-1:res[i]=st.top();
        }
        st.push(arr[i%n]);
    }
    return res;
}

//---------------------------------------------------------------------------------------------------------

//Nearest Smaller elem
//Given an arr need to return next smaller elem of arr
//Next smaller elem of a elem: go left stop at first elem that is lesser then the cur_elem and if not found any then put -1
//-1 to put when the cur_elem is smallest all elem til cur from left

//Ex: {4,5,2,10,8}
// res = {-1,4,-1,2,2}

auto NSEBrut(vector<int>& arr){
    int n=arr.size();
    vector<int> res(n);
    
    for(int i=0;i<n;i++){
        int j=i-1;
        for(;j>=0;j--){
            if(arr[j] < arr[i]){
                res[i]=arr[j];
                break;
            }
        }
        if(j==-1) res[i]=-1;
    }
    return res;
}

//Optimal
// Use a stack
//I should know elems that are left of a particular element
//Traverse from front and each time if st.top()>cur_elem then pop top until st.top()<cur_elem
//if stack is empty even at the end of expedition then put -1 in result
//else put st.top() in result

auto NSEOpt(vector<int>& arr){
    int n=arr.size();
    stack<int> st;
    vector<int> res(n);

    for(int i=0;i<n;i++){
        while(!st.empty() && st.top()>=arr[i]){
            st.pop();
        }
        (st.empty())?res[i]=-1:res[i]=st.top();
        st.push(arr[i]);
    }
    return res;
}
//TC - O(2*n), SC - O(n+n)

//---------------------------------------------------------------------------------------------------------------------

//Trapping rain water
//INput : arr of non negative integers, each elem represents height of the building 

// [image-comments/image-20261013-182821-jlw0q0.png]

// Need to return the total units of water that is trapped between the buildings here = 6000
//The intuition is: for water to be traped there should exist 2 buildinghs on right and left whose height is greater then current
// - U will go for each building and find their leftmax(which is buildings on current left greater height then itself) and rightmax(i.e buildings on current right greater height then itself)
// - take min(leftmax, rightmax)-arr[i] {the water is trapped only upto min height building from left and right and above the hieight pof current building}
// - This will get us with water stored on top of perticular building or even may be ground when height is 0
// Note: taking leftmax is same as NGE on left and rightmax: NGE on right 

//Brut: 

int trapedWater(vector<int>& arr){
    int n=arr.size();
    int leftMax, rightMax;
    int res=0;

    for(int i=0;i<n;i++){
        leftMax = INT_MIN;
        rightMax = INT_MIN;

        for(int j=0;j<i;j++){
            if(leftMax < arr[j] && arr[j]>arr[i]){
                leftMax=arr[j];
            }
        }
        for(int j=i+1;j<n;j++){
            if(rightMax < arr[j] && arr[j] > arr[i]){
                rightMax = arr[j];
            }
        }

        if(leftMax!=INT_MIN && rightMax!=INT_MIN){
            int u = min(leftMax, rightMax)-arr[i];
            res+=u;
        }
    }
    return res;
}
//TC - O(n^2), Sc - O(1)


int trapedWaterBet(vector<int>& arr){
    int n=arr.size();
    int leftMax, rightMax;
    int res=0;
    int maxiL = INT_MIN;

    for(int i=0;i<n;i++){
        leftMax = INT_MIN;
        rightMax = INT_MIN;

        if(maxiL > arr[i]){
            leftMax=maxiL;
        }

        if(arr[i]>maxiL){
            maxiL=arr[i];
        }

        for(int j=i+1;j<n;j++){
            if(rightMax < arr[j] && arr[j] > arr[i]){
                rightMax = arr[j];
            }
        }

        if(leftMax!=INT_MIN && rightMax!=INT_MIN){
            int u = min(leftMax, rightMax)-arr[i];
            res+=u;
        }
    }
    return res;
}
//Tc - o(n^2), Sc - o(1)

//Using prefixMax and suffixMax
int trapedWaterBet2(vector<int>& arr){
    int n=arr.size();
    vector<int> suffixMax(n), prefixMax(n);
    suffixMax[n-1] = arr[n-1];
    prefixMax[0]=arr[0];
    for(int i=1;i<n;i++){
        prefixMax[i] = max(prefixMax[i-1], arr[i]);
    }
    for(int i=(n-2);i>=1;i--){
        suffixMax[i] = max(suffixMax[i+1], arr[i]);
    }

    int res=0;
    for(int i=0;i<n;i++){
        if(prefixMax[i]>arr[i] && suffixMax[i]>arr[i]){
            res += min(prefixMax[i], suffixMax[i])-arr[i];
        }
    }
    return res;
}
//TC - O(3*n), SC - O(2*n)

// Above can be optimized by taking a element for leftMax and using suffixMax

//Optimal: Here mnaintain a ptr at begining and another at end 
//Traverse until left=right and the index at which left and right will be is at the highest building elem
//take smaller among left and right elem
//maintain 2 variables leftMax and rightMax initially assign them with -1
//check smaller one is it less then corresponding var if so then increment result with ptrMax-arr[ptr]
//if the ptrMax < arr[ptr] then update ptrMax=arr[ptr]
//At end do ptr++;

int TrapedWaterOpt(vector<int>& arr){
    int total=0;
    int leftMax=-1, rightMax=-1;
    int l=0, r=arr.size()-1;

    while(l<r){
        if(arr[l]<=arr[r]){
            if(leftMax > arr[l]){
                total+=leftMax-arr[l];
            }
            else{
                leftMax=arr[l];
            }
            l++;
        }
        else{
            if(rightMax > arr[r]){
                total+=rightMax-arr[r];
            }
            else{
                rightMax=arr[r];
            }
            r--;
        }
    }
    return total;
}
//TC - O(n), Sc - O(1)
//Correctness lies in fact that: if r_ptr > l_ptr  i gives guarantee that there is support or buildin with higher height on right so u can only check or left and each time we move ptr we will update ptrvar with max height on each side

//----------------------------------------------------------------------------------------------

//Sum of subarr minimums
//Take all subarrs find minimum in each of them and sum all minimums and if the result is too large mod it with (10^9+7)

//Brut:

int sumSubMin(vector<int>& arr){
    int n=arr.size();
    int sum=0, mini;
    int mod = (int)(1e9+7);

    for(int i=0;i<n;i++){
        mini=INT_MAX;
        for(int j=i;j<n;j++){
            mini=min(mini, arr[j]);
            sum = (sum+mini)%mod;
        }
    }
    return sum;
}

//

int sumSubMinOpt(vector<int>& arr){
    stack<int> st;
    int n=arr.size();
    vector<int> nse(n);
    vector<int> pse(n);
    int mod = (1e9+7);
    for(int i=n-1;i>=0;i--){
        while(!st.empty() && arr[st.top()]>=arr[i]){
            st.pop();
        }
        if(st.empty()){
            nse[i] = n;
        }
        else{
            nse[i] = st.top();
        }
        st.push(i);
    }

    while(!st.empty())
        st.pop();

    for(int i=0;i<n;i++){
        while(!st.empty() && arr[st.top()] > arr[i] ){ //Edge case explained below
            st.pop();
        }
        if(st.empty()){
            pse[i]=-1;
        }
        else{
            pse[i] = st.top();
        }
        st.push(i);
    }

    int sum=0;
    for(int i=0;i<n;i++){
        int l= i - pse[i];
        int r= nse[i] - i;
        sum = (sum+arr[i]*(l*r)) % mod;
    }
    return sum;
}
//Tc - O(n + n + n), Sc - O(n + n + n){stack, nse, pse}

//Edge case why u consider previous smaller or equal element and not stricter previous smaller element? 
//Ex: [1,1]
// nse - [2, 2]
// pse = [-1, -1]

// now for index-0: l= 0-(-1) = 1
//                  r= 2-0 = 2, sum=2
//                 considered subarr: 1, 1 1
//         index-1: l= 1-(-1) = 2
//                  r= 2-1 = 1, sum=4
//                  considered sdubarr = 1, 1 1
// here 1 1 is considered 2 times because of Previous smaller element instead we make it previous smaller or equal element just change condition to pop stack from arr[st.top()] >= arr[i] to arr[st.top()] > arr[i]
// in that case:
// Ex: [1, 1]
// nse - [2, 2]
// psee - [-1, 0] sum=3

//-------------------------------------------------------------------------------------------------

//Sum of subarr ranges
// Take each subarr and for each take max-min and add total, return total

//Ex:1 4 3 2
// 1          0
// 1 4        3
// 1 4 3      3
// 1 4 3 2    3

// 4          0
// 4 3        1
// 4 3 2      2

// 3          0
// 3 2        1

// 2          0
// Res = 13

int sumSubRanges(vector<int>& arr){
    int n=arr.size();
    int total=0;
    int ranges, maxi, mini;

    for(int i=0;i<n;i++){
        maxi=INT_MIN;
        mini=INT_MAX;
        for(int j=i;j<n;j++){
            maxi=max(maxi, arr[j]);
            mini=min(mini, arr[j]);
            ranges = maxi-mini;
            total+=ranges;
        }
    }
    return total;
}

//Better:
auto nse(vector<int>& arr){
    int n=arr.size();
    vector<int> nse(n);

    stack<int> st;
    for(int i=n-1;i>=0;i--){
        while(!st.empty() && arr[st.top()] >= arr[i]){
            st.pop();
        }
        if(st.empty()){
            nse[i]=n;
        }
        else{
            nse[i]=st.top();
        }
        st.push(i);
    }
    return nse;
}

auto psee(vector<int>& arr){
    int n=arr.size();
    vector<int> psee(n);
    stack<int> st;

    for(int i=0;i<n;i++){
        while(!st.empty() && arr[st.top()] > arr[i]){
            st.pop();
        }
        if(st.empty()){
            psee[i] = -1;
        }
        else{
            psee[i]=st.top();
        }
        st.push(i);
    }
    return psee;
}

auto nge(vector<int>& arr){
    int n=arr.size();
    vector<int> nge(n);
    stack<int> st;

    for(int i=n-1;i>=0;i--){
        while(!st.empty() && arr[st.top()] <= arr[i]){
            st.pop();
        }
        if(st.empty()){
            nge[i] = n;
        }
        else{
            nge[i]=st.top();
        }
        st.push(i);
    }
    return nge;
}

auto pgee(vector<int>& arr){
    int n=arr.size();
    vector<int> pgee(n);
    stack<int> st;

    for(int i=0;i<n;i++){
        while(!st.empty() && arr[st.top()] < arr[i]){
            st.pop();
        }
        if(st.empty()){
            pgee[i]=-1;
        }
        else{
            pgee[i]=st.top();
        }
        st.push(i);
    }
    return pgee;
}
//Tc - O(n+n), SC - o(n+n)

int sumSubarrRangesBet(vector<int>& arr){
    int n=arr.size();

    auto Psee = psee(arr);
    auto Nse = nse(arr);

    auto Pgee = pgee(arr);
    auto Nge = nge(arr);

    long long maxTotal=0, minTotal=0;
    int mod = (1e9+7);

    for(int i=0;i<n;i++){
        long long mini = (i-Psee[i])*(Nse[i]-i);
        long long maxi = (i-Pgee[i])*(Nge[i]-i);

        maxTotal = (maxTotal + (maxi*arr[i])) % mod;
        minTotal = (minTotal + (mini*arr[i]))%mod;
    }

    return maxTotal-minTotal;
}
//TC - O(10*n), SC - o(10*n)

//---------------------------------------------------------------------------------------------------

//Astroid Collision
//Given an array of positive and negatives
//Asteroid size is absolute of arr value
// - Astroid with +ve moves rightwards and astroid with negative moves leftwards
// - 2 asteroids with same sign can move simultaneously
// - 2 asteroids of different sign if came up then one with greater size remains other destroys
// - 2 asteroid with different sign but same size came up then both get destroyed
// Return the final remaining asteroids i.e all the remaining will be moving in same direction (having same sign)

//Ex; {4, 7, 1, 1, 2, -3, -7, 17, 15, -16}

auto asteroidCollision(vector<int> arr){
    int i=0;
    int n=arr.size();
    vector<int> hash(n, 1);
    while(i<n){
        if(arr[i]>0 && hash[i]==1){
            i++;
            continue;
        }
        else if(arr[i]<0 && hash[i]==1){
            int j=i-1;
            while(j>=0){
                if(hash[j]==1 && arr[j]>0){
                    if(abs(arr[i]) < abs(arr[j])){
                        hash[i]=0;
                        break;
                    }
                    else if(abs(arr[i]) > abs(arr[j])){
                        hash[j]=0;
                    }
                    else{
                        hash[j]=0;
                        hash[i]=0;
                        break;
                    }
                }
                j--;
            }
        }
        i++;
    }

    vector<int> res;
    for(int i=0;i<n;i++){
        if(hash[i]==1){
            res.push_back(arr[i]);
        }
    }
    return res;
}
//TC - O(n^2), SC - O(n)

//Optimal: Use a stack or if u want to maintain the order in which asteroids are there in input then use List
//So the remaining asteroids at the end will be as in stack
auto asteroidRemOpt(vector<int>& arr){
    int n=arr.size();
    stack<int> st;
    int flag=0;

    for(int i=0;i<n;i++){
        if(st.empty() || arr[i]>0 || (st.top()<0 && arr[i]<0)){
            st.push(arr[i]);
        }
        else{
            while(!st.empty() && st.top()>0 && (abs(arr[i]) > abs(st.top()))){
                st.pop();
                flag=1;
            }
            if(!st.empty() && st.top()>0 && (abs(arr[i]) == abs(st.top()))){
                st.pop();
                flag=0;
            }
            else if(!st.empty() && st.top()>0 && (abs(arr[i]) < abs(st.top()))){
                flag=0;
            }
            if(flag){
                st.push(arr[i]);
                flag=0;
            } 
        }
    }

    vector<int> res;
    while(!st.empty()){
        res.push_back(st.top());
        st.pop();
    }
    reverse(res.begin(), res.end());

    return res;
}

//TC - O(n+n+n), SC - O(n+n)

//Without using fucking flag and complicating
//Use list to preserve order so we do not need to store it in another vector and reverse and return

auto asteroidCollisionOpt(vector<int>& arr){
    int n=arr.size();
    list<int> ls;

    for(int i=0;i<n;i++){
        if(arr[i]>0){
            ls.push_back(arr[i]);
        }
        else{
            while(!ls.empty() && ls.back()>0 && ls.back() < abs(arr[i])){
                ls.pop_back();
            }
            if(!ls.empty() && ls.back() == abs(arr[i])){
                ls.pop_back();
            }
            else if(ls.empty() || ls.back()<0){
                ls.push_back(arr[i]);
            }
        }
    }

    return ls;
}
//TC - O(n+n), SC - O(n)

//-------------------------------------------------------------------------------------------------

//Largest Rectangle in histogram
// Given arr of non negatives where each elem represents a bar graph of unit width and elem value represents height of bar graph
//U need to return max area of rectangle that could be formed it doesnt mean u supposed to return max arr elem it could be anyhow formed vertical or horiszontal combining several bars or several parts of bars

//Ex: {2, 1, 5, 6, 2, 3}
// [image-comments/image-20261015-032415-65mnce.png]
// rectangles possible:
// 1. len=6, width=1, a=6
// [image-comments/image-20261015-032615-q98a0u.png]

// 2. len=4, width=2, a=8
// [image-comments/image-20261015-032724-lyqpwb.png]

// 3. len=2, width=5, a=10
// [image-comments/image-20261015-032816-pfsu6j.png]

// res=10

int rectangleMaxArea(vector<int>& arr){
    int n=arr.size();
    int area=0;
    for(int i=0;i<n;i++){
        int len = arr[i];
        int wid=1;
        for(int j=i-1;j>=0;j--){
            if(arr[j] >= arr[i]){
                wid++;
            }
            else
                break; 
        }
        for(int j=i+1;j<n;j++){
            if(arr[j] >= arr[i])
                wid++;
            else
                break;
        }
        area = max(area, (len*wid));
    }
    return area;
}
//TC - O(n^2), SC - O(1)

//Better
// U can go with nse and pse - make pse and nse arr with indices and len=arr[i], wid=(nse[i]-i)+(i-pse[i]-1)

auto pse(vector<int>& arr){
    int n=arr.size();
    stack<int> st;
    vector<int> pse(n);

    for(int i=0;i<n;i++){
        while(!st.empty() && arr[st.top()] >= arr[i]){
            st.pop();
        }
        if(st.empty()){
            pse[i] = -1;
        }
        else{
            pse[i]=st.top();
        }
        st.push(i);
    }
    return pse;

}

int rectangleMaxAreaBet(vector<int>& arr){
    int n=arr.size();

    auto Pse = pse(arr);
    auto Nse = nse(arr);

    for(auto v:Pse) cout<<v<<" ";
    cout<<endl;

    for(auto v:Nse) cout<<v<<" ";
    cout<<endl;
    
    int area=0;
    for(int i=0;i<n;i++){
        int len = arr[i];
        int wid = (Nse[i]-Pse[i]-1);
        area = max(area, (len*wid));
    }
    return area;

}
//Tc - O(5*n), SC - O(6*n)

int rectangleMaxAreaOpt(vector<int>& arr){
    int n=arr.size();
    stack<int> st;
    int area=0;

    for(int i=0;i<n;i++){
        while(!st.empty() && arr[st.top()] >= arr[i]){
            int curId = st.top();
            st.pop();
            if(!st.empty())
                area = max(area, arr[curId] * (i-st.top()-1));
            else{
                area = max(area, arr[curId] * (i));  
            }
        }
        if(st.empty() || arr[st.top()] < arr[i]){
            st.push(i);
        }
    }

    while(!st.empty()){
        int curId = st.top();
        st.pop();
        if(!st.empty())
            area = max(area, (arr[curId] * (n-st.top()-1)));
        else
            area = max(area, (arr[curId] * (n)));
    }
    return area;
}
//TC - O(n+n), SC - O(n)

//----------------------------------------------------------------------------------------------------

//Maximal rectangle
//Given a matrix of 0 and 1, need to find the max area rectangle that has only 1s
// Ex: 
// 1 0 1 0 1
// 1 0 1 1 1
// 1 1 1 1 1
// 1 0 0 1 0
//Take prefix sum only when there exist 1 for each column 
//Take each row pass it for Largest rectangle in histogram then and the results max is stored 

// 1 0 1 0 1
// 2 0 2 1 2
// 3 1 3 2 3
// 4 0 0 3 0

// row1: area=1
// row2: a=3
// row3: a=6
// row4: a=4
//res=6

int maximalRectangle(vector<vector<int>>& arr){
    int n=arr.size();
    int m=arr[0].size();

    int pfix;
    for(int j=0;j<m;j++){
        pfix=0;
        for(int i=0;i<n;i++){
            if(arr[i][j] == 1){
                pfix += arr[i][j];
                if(arr[i][j]==0) pfix=0; //prefixSum only when there are contigous 1s if any 0 breaks then again sum initializes to 0
                arr[i][j]=pfix;
            }
        }
    }

    int area=0;
    for(int i=0;i<n;i++){
        int row_area =  rectangleMaxAreaOpt(arr[i]);
        area = max(area, row_area);
    }

    return area;
}
//TC - O(n*m + n*2m), SC - O(M) {stack}

//---------------------------------------------------------------------------------------------------------

//Remove k digits
//Given a string which contains 0-9 digits u need to remove any k digits such that the remaining no arranged in input order is the smallest number 

//Ex: "1432219", k=3
//remove: 4,3,2 res: 12219
// Note: u can remove non contigously also!

//Intuition: keeping first k digits as small as possible
//Use stack and each time when found a elem lesser then stack top then pop st top and insert cur and do this removal only k no of times and when k =0 just put all elems back to stack
// the stack represents thr return string

// Some edge cases
// 1. if k>=n return "0"
// 2. if stack has "00100" then trim trailing 0s
// 3. if k stil has some value as the input follows increasing order like n="012345" now after traversal k=3 so remove last 3 

string removeKElems(string s, int k){
    int n=s.size();

    if(k>=n){
        return "0";
    }
    stack<int> st;
       
    for(int i=0;i<n;i++){
        while(!st.empty() && st.top()>s[i] && k>0){
            st.pop();
            k--;
        }
        if(st.empty() || k<=0 || st.top() <= s[i]){
            st.push(s[i]);
        }
    }

    while(k>0){
        st.pop();
        k--;
    }
    if(st.empty()) return "0";

    string res="";
    while(!st.empty()){
        res+=st.top();
        st.pop();
    }
    reverse(res.begin(), res.end());

    for(int i=0;i<res.size();i++){
        if(res[i]=='0'){
            res.erase(res.begin()+i);
        }
        else break;
    }
    if(res=="") return "0";

    return res;
}
// TC - O(n), Sc - o(n)


int main(){
    // minStackOpt st;
    // st.push(12);
    // st.push(15);
    // st.push(10);

    // cout<<st.getMin()<<endl;
    // st.pop();
    // cout<<st.getMin()<<endl;
    // cout<<st.top()<<endl;
    // st.push(10);
    // cout<<st.top()<<endl;

    //=================================

    // vector<int> arr = {5,7,9,6,7,4,5,1,3,7};
    // auto res = NSEOpt(arr);
    // for(auto v:res) cout<<v<<" ";

    //==================================

    // vector<int> arr={0,1,0,2,1,0,1,3,2,1,2,1};
    // cout<<TrapedWaterOpt(arr);

    //=================================

    // vector<int> arr = {1,1};
    // cout<<sumSubMinOpt(arr);

    //=================================

    // vector<int> arr={1,4,3,2};
    // cout<<sumSubarrRangesBet(arr);

    //=================================

    // vector<int> arr={4, 7, 1, 1, 2, -3, -7, 17, 15, -18, -19};
    // auto res=asteroidCollisionOpt(arr);
    // for(auto v:res) cout<<v<<" ";
    // cout<<endl;

    //==================================
    // vector<vector<int>> arr = {
    // {1, 0, 1, 0, 1},
    // {1, 0, 1, 1, 1},
    // {1, 1, 1, 1, 1},
    // {1, 0, 0, 1, 0}
    // };

    // cout<<maximalRectangle(arr);
    //==================================

    string s="1432219";
    string res = removeKElems(s, 3);
    cout<<res;


    return 0;
}