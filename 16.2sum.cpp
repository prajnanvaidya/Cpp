#include<bits/stdc++.h>
using namespace std;

//1.Two sum: given an array and an target tell whether the arr has any 2 elements that add to give target val return bool Yes or No

//Brute
bool TwoSumBrute(vector<int> &a, int target){
    int n=a.size();
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(a[i]+a[j]==target)
                return true;
        }
    }
    return false;
}
//TC: O(n*n), SC: O(1)

bool TwoSumBruteBetter(vector<int> &a, int target){
    int n=a.size();
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            if(a[i]+a[j]==target)
                return true;
        }
    }
    return false;
}

//Any better sol in ur mind - each elem - target = res whether this res is present somewhere inorderto search for it to present or not better to maitain a map, but in a map what are keys and values if keys are arr elem and values are target-elem so we will need one loop to fill map and other to traverse on values of map for searching for corresponding elem in arr using map itself if present then return true or after full traversing return false

bool TwoSumBetter(vector<int> a, int target){
    int n=a.size();
    map<int, int> mpp;
    for(int i=0;i<n;i++){
        mpp[a[i]] = (target-a[i]);
    }
    for(auto v:mpp){
        if(mpp.find(v.second)!=mpp.end())
            return true;
    }
    return false;
}
//TC: O( nlogn + n) - worst case, Sc: O(n) 
//Improved terms of TC but SC has worsen


bool TwoSumBetterBetter(vector<int> a, int target){
    int n=a.size();
    map<int, int> mpp;
    for(int i=0;i<n;i++){
        if(mpp.find(target-a[i])!=mpp.end()){
            return true;
        }
        mpp[a[i]]=i;
    }
    return false;
}
//TC: O(nlogn)-for map, O(n)-for unordered map or in collision - O(n^2)

//Any optimal idea - no idea :/

//Optimal solution: Using greedy approach where in array is sorted 1st and left ptr to 0 index and right ptr to n-1 index and applying while loop until left crosses right each time left val+right val if less then target then move left ptr ahead or if greater then target then move right ptr behind
//Here just in case got any left+right = target return 
bool TwoSumoptimal(vector<int> a, int target){
    int n=a.size();
    int right=n-1, left=0;
    sort(a.begin(), a.end());
    int temp;
    while(left<right){
        temp=a[left]+a[right];
        if(temp==target)
            return true;
        else if(temp<target)
            left++;
        else
            right--;
    }
    return false;
}
//TC: near to O(nlogn + n) where nlogn for sorting, SC: O(1)



//2.Two sum : same but return index at which a and b present which adds upto give target val
//Brute
pair<int, int> TwoSumvar2Brute(vector<int> a, int target){
    int n=a.size();
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            if(a[i]+a[j]==target)
                return make_pair(i, j);
        }
    }
    return make_pair(-1, -1);
}
//TC: Near to O(n^2) more precisely n(n-1)/2, SC: O(1)

//Better
pair<int, int> TwoSumvar2Optimum(vector<int> a, int target){
    int n=a.size();
    map<int, int> mpp;
    int temp;
    for(int i=0;i<n;i++){
        temp=target-a[i];
        if(mpp.find(temp)!=mpp.end())
            return make_pair(i, mpp[temp]);
        mpp[a[i]]=i;
    }
    return make_pair(-1, -1);
}
//TC: O(nlogn)-map ,O(n*1)-unordered map
//SC: O(n)

//Optimal
//2 pointer greedy approach 
auto TwoSumvar2Better(vector<int> a, int target){
    int n=a.size();
    int left=0, right=n-1;
    int temp;
    map<int, int> mpp;
    for(int i=0;i<n;i++){
        mpp[a[i]]=i;
    }
    sort(a.begin(), a.end());
    while(left<right){
        temp=a[left]+a[right];
        if(temp==target){
            return make_pair(mpp[a[left]], mpp[a[right]]);
        }
        else if(temp<target)
            left++;
        else
            right--;
    }
    return make_pair(-1, -1);
}
//TC: O(nlogn + nlogn + n ), SC: O(n)

int main(){
    int n, elem;
    cin>>n;
    vector<int> arr;
    for(int i=0;i<n;i++){
        cin>>elem;
        arr.push_back(elem);
    }
    auto res=TwoSumvar2Better(arr, 13);
    cout<<res.first<<","<<res.second<<endl;


    return 0;
}