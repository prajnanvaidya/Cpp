#include<bits/stdc++.h>

using namespace std;



//PS: Find next permutation of a array
//If arr contains 3 elem total permutation(possible arrangements) possible is 3!=6

//Ex arr-{2, 3, 1}
// 1 2 3
// 1 3 2
// 2 1 3
// 2 3 1
// 3 1 2 
// 3 2 1

//Its lexicograpp[hic order i.e each in sorted order to next 
//Here ans - {3 1 2}
//If given last order, arr -{3, 2, 1}
//then result is ans - {1, 2, 3}


//Brute -  
void NextPerm(vector<int>& arr){
    if(arr[1]<arr[2])
        sort(arr.begin()+1, arr.end(), greater<int>());
    else{
        auto maxi = max_element(arr.begin()+1, arr.end());
        int m = maxi - arr.begin();
        auto mini = min_element(arr.begin()+1, arr.end());
        int n = mini - arr.begin();

        if(arr[n]>arr[0] && arr[n]<arr[m]){
            swap(arr[n], arr[0]);
            sort(arr.begin()+1, arr.end());
        }
        else if(arr[m]>arr[0]){
            swap(arr[m], arr[0]);
            sort(arr.begin()+1, arr.end());
        }
        else{
            sort(arr.begin(), arr.end());
        }
    }
}


// Brut- create all permutation in lexicographic order and then do a linear search for the current arr and give next arr as result   

void allPermutationSwap(vector<int>& arr, int index, vector<vector<int>>& ans){
    if(index >= arr.size()){
        ans.push_back(arr);
        return;
    }
    for(int i=index;i<arr.size();i++){
        swap(arr[index], arr[i]);
        allPermutationSwap(arr, index+1, ans);
        swap(arr[index], arr[i]);
    }
}
//Even though its optimal for generating allPermutation it doesnt guarantee result in lexicographic order! Why? consider u swap a element with other having gap say 1,2,3,4 swap index 1 and 3 now: 1,4,3,2 that doesnt guarantee after swap the remaining element in sorted order!

void allPermutationMap(map<int, int> mpp, vector<int>& temp, vector<vector<int>>& ans){
    if(temp.size() == mpp.size()){
        ans.push_back(temp);
        return;
    }

    for(auto v:mpp){
        if(v.second > 0){
            temp.push_back(v.first);
            mpp[v.first]--;
            allPermutationMap(mpp, temp, ans);
            temp.pop_back();
            mpp[v.first]++;
        }
    }
}
//TC - O(n.n!.log(n!)) {for n elems we get n! factorial of permutation and for getting each permutation we do loop n times and logn! for map operations as we insert temp to map once it gets full}
//Sc - Output space - O(n * n!) {as ans stores n! permutation each of size n}, Auxillary space - O(n * n! + n) {considering Tail Recursioin Optimization is not possible} extra space n is used for map 

//The whole code is to make sure ans stores permutations in lexicographic order thats made possible as each time we choose first map key that has positive value and it maintains keys in sorted fashion SO cannot use unordered map!


auto nextPermutationBrut(vector<int>& arr){
    vector<vector<int>> ans;

    map<int, int> mpp;
    for(auto v:arr)
        mpp[v]++;

    vector<int> temp;
    allPermutationMap(mpp, temp, ans);

    int i;
    for(i=0;i<ans.size();i++){
        if(ans[i] == arr)  //ans[i] == arr does not check whether ans[i] and arr refer to the same object. For std::vector, the == operator compares the vectors element-by-element (and requires the same size).
            break;
    }

    if(i+1 >= ans.size())
        return ans[0];

    return ans[i+1];
}
//TC - O(n*n! + n!*n) {first for generating all permutation and 2nd for looping to find the current arr}
//SC - O(n*n! + n + n*n!) (first stack space and 2nd is for map and 3rd is for output space)

//---------------------------------------------------------------------------------------------------

//Some optimization can be done while calculating allPermutation itself along with stop condition we can check for equating temp to arr if satisfied then do the recursiun for 1 more time and then completely stop go back and return that next full temp
//Is it possible how?, never done that before!


bool nextPermutationBool(vector<int>& arr, map<int, int>& mpp, vector<int>& temp, bool& flag){
    if(temp.size() == arr.size()){
        if(flag){
            return true;
        }
        if(temp == arr){
            flag = true;
        }
        return false;
    }

    for(auto& v:mpp){
        if(v.second > 0){
            temp.push_back(v.first);
            v.second--;    //brings down Tc from O(logn) to O(1) using &
            bool res = nextPermutationBool(arr, mpp, temp, flag);
            
            if(res) return true;

            temp.pop_back();
            v.second++;
        }
    }
    return false;
}


auto nextPermutationBrut2(vector<int>& arr){

    map<int, int> mpp;
    for(auto v:arr)
        mpp[v]++;

    vector<int> temp;
    bool flag=false;
    nextPermutationBool(arr, mpp, temp, flag);

    if(temp.empty()){
        vector<int> s=arr;
        sort(s.begin(), s.end());
        return s;
    }
    return temp;
}
//TC - O(n*n! + nlogn)
//SC - O(n + n)

//------------------------------------------------------------------------------------------------------------
//Optimal algorithm:
//1. First find the dip, start from last elem and see whether u get any pair such first_elem<sec_elem if yes note that first_elem index, but start from last as we require first dip from right to give next permutation
//2. from remaining elem find that which greater then index but smaller then other greater elems on right, that ensures to replace index with one step further candid from right, its done by going through right part from last and swapping the first elem which found to be greater then index
//Why first elem to swap and then break cuz after the dip always the elems are organized in descending fashion

//After swap just reverse the right half as elems are in descending fashion also after swap

void nextPermutationOpt(vector<int>& arr){
    int idx=-1;
    for(int i=arr.size()-2;i>=0;i--){
        if(arr[i] < arr[i+1]){
            idx = i;
            break;
        }
    }
    if(idx == -1){
        reverse(arr.begin(), arr.end());
        return;
    }
    for(int i=arr.size()-1;i>idx;i--){
        if(arr[i]>arr[idx]){
            swap(arr[i], arr[idx]);
            break;
        }
    }
    reverse(arr.begin()+idx+1, arr.end());
}
//TC - O(n + n + n  )
//Sc - O(1)


int main(){
    vector<int> arr={2,1,5,4,3,0,0};
    
    nextPermutationOpt(arr);
    for(auto i:arr) cout<<i<<" ";

    return 0;
}