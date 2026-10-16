#include<bits/stdc++.h>

using namespace std;

//Pascals Triangle
/*
                1
              1   1
            1   2   1
          1   3   3   1
        1   4   6   4   1
      1   5  10  10   5   1
    1   6  15  20  15   6   1
*/
// the 1st and last col will have 1 as col value and middle element will be sum of previous rows 2 corresponding col values

//Given row and col number find pascal triangle value of it 
// formula: (row-1)C(col-1)

long long factorial(int n){
    if(n==1)
        return 1;
    return n*factorial(n-1);
}
//Tc - o(n), Sc - o(n)

long long pascalRowCol(int row, int col){
    long long n=factorial(row-1);
    long long r=factorial(col-1);
    long long n_r = factorial(row-1-col+1);
    return n/(n_r * r);
}
// TC - O(row + col), Sc - O(row+col)

//Optimal: making nCr = n*(n-1)*(n-2)..r times / r*r-1*..1
long long pascalRowColOpt(int row, int col){
    long long res=1;
    for(int i=0;i<col-1;i++){
        res*=(row-1-i);
        res/=(i+1);
    }
    return res;
}
//TC - O(col), Sc - O(1)

//--------------------------------------------------------------------

//Given a row no give all row elems
//Brut way find that particular elem using (row-1)C(col-1) logic
void PascalRow(int r){
    vector<int> ans;
    for(int i=0;i<r;i++){
        auto res=pascalRowColOpt(r, i+1);
        ans.push_back(res);
    }
    for(auto v:ans) cout<<v<<" ";
}

//use 0 based col indexing and each value of r row will be (after 2nd val) (previous*(r-col_index)/col_index)
auto pasclaRowOpt(int r){
    vector<int> ans;
    int res=1;
    ans.push_back(res);
    for(int i=1;i<r;i++){
        res*=(r-i);
        res/=i;
        ans.push_back(res);
    }
    return ans;
}

//---------------------------------------------------------------------------------------

//Given row print whole pascal triangle upto that
//Brut- for each elem col r-1Cc-1
void printPascal(int r){
    vector<vector<int>> ans;
    vector<int> row;
    int res;
    for(int i=1;i<=r;i++){
        row.clear();
        for(int j=1;j<=i;j++){
            res=pascalRowColOpt(i,j);
            row.push_back(res);
        }
        ans.push_back(row);
    }
    for(auto v:ans){
        for(auto i:v) cout<<i<<" ";
        cout<<endl;
    }
}
//TC - O(r^2*col) ~ O(n^3)
//SC - O(1) auxillary

//Opt
void printPascalOpt(int r){
    vector<vector<int>> ans;
    vector<int> row;
    for(int i=1;i<=r;i++){
        row = pasclaRowOpt(i);
        ans.push_back(row);
    }
    for(auto v:ans){
        for(auto i:v) cout<<i<<" ";
        cout<<endl;
    }
}
// TC ~ O(n^2)

//--------------------------------------------------------------------------------------------
//Majority element that appears greater then floor(n/2) times
// if n=9 floor(9/2)=4, there could be only 1 answer possible for a arr
//Optimal
// to check which is that we maintain counter and loop through arr and each time if counter 0 initialize our result to that elem and counter as 1 and else then check elem considered same as current if yes then increment the counter and if no decrement counter
//Overall we are cancelling a one type of elem with other that makes only that elem remain which appears greater then n/2 

auto majorityElemNBy2(vector<int>& arr){
    int n=arr.size();
    int cnt=0, el=INT_MIN;
    for(int i=0;i<n;i++){
        if(cnt == 0){
            cnt++;
            el=arr[i];
        }
        else{
            if(el == arr[i]){
                cnt++;
            }
            else{
                cnt--;
            }
        }
    }
    if(el == INT_MIN)
        return -1;
    return el;
}

//-----------------------------------------------------------------------------------

//Majority elem appearing greater then floor(n/3)
//At max there could be only 2 elems apearing greater then n/3!

//Brut check for each new elem the whole arr how much times it appears
void majorityElemGNBy3(vector<int>& arr){
    int n=arr.size();
    int cnt;
    vector<int> ls;
    for(int i=0;i<n;i++){
        cnt=1;
        if(ls.size()==0 || (ls.size()==1 && ls[0]!=arr[i]))
            for(int j=i+1;j<n;j++){
                if(arr[i]==arr[j])
                    cnt++;
            }
        if(cnt>(n/3))
            ls.push_back(arr[i]);
        if(ls.size() == 2) break;
    }
    for(auto v:ls) cout<<v<<" ";
}
//TC - O(n^2), Sc - O(1)

//Better: Use a hash map
void majorityElemGNBy3Bet(vector<int>& arr){
    unordered_map<int, int> hash;
    int n=arr.size();
    vector<int> ls;

    for(int i=0;i<n;i++){
        hash[arr[i]]++;
        if(hash[arr[i]] > (n/3)){
            ls.push_back(arr[i]);
        }
        if(ls.size() == 2) break;
    }

    for(auto v:ls) cout<<v<<" ";

}
//TC - O(n), Sc - o(n)

//Optimal: The intuision: basically for >n/2 we did clear 1 element over other but here we consider 2 elems and cancel or increment 1 elem at a time
//U maintain cnt1 , el1 and cnt2, el2 when cnt1=0: cnt=1, el1=curr if not then cnt2=0: cnt2=1,el2=curr if not curr=el1: cnt1++ if not curr=el2: cnt2++ if not cnt1--, cnt2--

//The main edge case is that when cnt1=0; we need to check if we are actually encountering a differnt elem or just el2 and only if its not el2 then should proceed as cnt++,el1=curr otherwise it will go to condition curr=el2: cnt2++
//And same with cnt2==0 here also check curr!=el1 only then cnt2++, el2=curr

void majorityElemGNB3Opt(vector<int>& arr){
    int n=arr.size();

    int cnt1=0, cnt2=0;
    int el1=INT_MIN, el2=INT_MIN;

    for(int i=0;i<n;i++){
        if(cnt1 == 0 && el2 != arr[i]){
            cnt1++;
            el1 = arr[i];
        }
        else if(cnt2 == 0 && el1 != arr[i]){
            cnt2++;
            el2 = arr[i];
        }
        else if(el1 == arr[i]){
            cnt1++;
        }
        else if(el2 == arr[i]){
            cnt2++;
        }
        else{
            cnt1--;
            cnt2--;
        }
    }

    //Just for confirmation
    if(el1 != INT_MIN && el2 != INT_MIN){
        int mini = (int)n/3;
        int con1=0, con2=0;
        for(auto v:arr){
            if(v == el1) con1++;
            else if(v == el2) con2++;
        }
        if(con1>mini && con2>mini){
            cout<<el1<<" "<<el2;
        }
    }
    
}
//TC - O(n), Sc - O(1)

//----------------------------------------------------------------------------------------------------------------------------

//3 Sum
// Given an arr and k need to return no of triplets each including uniq elems of arr not duplicates can sum upto to 1

//Brut
void ThreeSum(vector<int>& arr, int s){
    int sum;
    int cnt=0;
    int n=arr.size();

    for(int i=0;i<n;i++){
        sum=arr[i];
        for(int j=i+1;j<n;j++){
            sum+=arr[j];
            for(int k=j+1;k<n;k++){
                sum+=arr[k];
                // cout<<sum<<endl;
                if(sum == s){
                    cnt++;
                }
                sum-=arr[k];
            }
            sum-=arr[j];
        }
    }
    cout<<cnt;
}
//Tc - O(n^3), Sc - o(1)
//The above approach also counts the duplicates , duplicates in the sense the does not mean u use the same element twice in the triad but the actual arr may contain duplicates and a triad may have (-1, 2, 0) but 2 of index 1 and another triad may have (-1,0,2) here 2 is of index 3

//Correct Brut
// I use a set to store the triads and then return it
auto ThreeSumBrut(vector<int>& arr, int target){
    int n=arr.size(), sum;
    set<vector<int>> st;
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            for(int k=j+1;k<n;k++){
                sum = arr[i] + arr[j] + arr[k];
                if(sum == target){
                    vector<int> temp = {arr[i], arr[j], arr[k]};
                    sort(temp.begin(), temp.end()); //only if the ques mentions triads should be in sorted order
                    st.insert(temp);
                }
            }
        }
    }
    vector<vector<int>> ans(st.begin(), st.end());
    return ans;
}
//Tc - O(n^3*logn), SC - O(n + 3)
//Gives TLE

//Trying to remove 3rd loop, use hashMap, store all elems between i and j in hashmap and check target-(arr[i]+arr[j]) exist in hash if yes then put in set other wise move on
//  0  1  2  3   4   5
// -1, 0, 1, 2, -1, -4

// u move the loop j and each time if difference doesnt exist then move j and before that put j value to hash
auto ThreeSumBet(vector<int>& arr, int target){
    set<vector<int>> st;
    set<int> hash;

    int n=arr.size();
    for(int i=0;i<n;i++){
        hash.clear();
        for(int j=i+1;j<n;j++){
            int diff = target - (arr[i] + arr[j]);
            if(hash.find(diff) != hash.end()){
                vector<int> temp = {arr[i], arr[j], diff};
                sort(temp.begin(), temp.end());
                st.insert(temp);
            }
            hash.insert(arr[j]);
        }
    }

    vector<vector<int>> ans(st.begin(), st.end());
    return ans;
}
//TC - O(n^2 * logn), Sc - O(n)

//Optimal Not uses set
//Uses 3 pointers, i, j, k
//i - remains constant when j and k moves, initially j=i+1, k=n-1 and each time sum goes less then target move k left and if goes greater then target move j right, loop through arr once for each i, Make arr sorted before

auto ThreeSumOpt(vector<int>& arr, int target){
    int i, j, k;
    int sum;
    int n=arr.size();
    vector<vector<int>> ans;
    sort(arr.begin(), arr.end());

    for(i=0;i<n;i++){
        if(i>0 && arr[i]==arr[i-1]) continue;
        j=i+1, k=n-1;
        while(j<k){
            sum = arr[i]+arr[j]+arr[k];
            if(sum<target){
                j++;
                while(j<k && arr[j]==arr[j-1]) j++;
            }
            else if(sum>target){
                k--;
                while(k>j && arr[k]==arr[k+1]) k--;
            }
            else{
                vector<int> temp = {arr[i], arr[j], arr[k]};
                sort(temp.begin(), temp.end());
                ans.push_back(temp);
                j++;
                while(j<k && arr[j]==arr[j-1]) j++;
                k--;
                while(k>j && arr[k]==arr[k+1]) k--;
            }
        }
    }
    return ans;
}
//Tc - O(n^2), SC - O(1)

//---------------------------------------------------------------------------------------------------------------

//4-Sum
//Given an arr and a target get all uniq combination of 4 arr elements that sum up to target without repeating particular arr elems

auto FourSumBrut(vector<int>& arr, int target){
    int n = arr.size();
    long long sum;
    set<vector<int>> st;
    vector<int> temp;
    
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            for(int k=j+1;k<n;k++){
                for(int l=k+1;l<n;l++){
                    sum = arr[i]+arr[j]+arr[k]+arr[l];
                    if(sum == target){
                        temp = {arr[i], arr[j], arr[k], arr[l]};
                        st.insert(temp);
                    }
                }
            }
        }
    }
    vector<vector<int>> ans(st.begin(), st.end());
    return ans;
}
//TC - O(n^4*logn), SC - O(n)

//Bet using hashArr reducing from 4 loops to 3 loops
auto FourSumBet(vector<int>& arr, int target){
    int n=arr.size();
    set<vector<int>> st;
    set<int> hash;
    vector<int> temp;
    
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            hash.clear();
            for(int k=j+1;k<n;k++){
                int diff = target - (arr[i]+arr[j]+arr[k]);
                if(hash.find(diff) != hash.end()){
                    temp = {arr[i], arr[j], arr[k], diff};
                    sort(temp.begin(), temp.end());
                    st.insert(temp);
                }
                hash.insert(arr[k]);
            }
        }
    }
    vector<vector<int>> ans(st.begin(), st.end());
    return ans;
}
//TC - O(n^3 * logn), SC - O(n)

//Optimal: Use 4 pointers i,j,k,l 
//i,j remains constant and k and l moves if sum>target move l left and if sum<target then move k right

auto FourSumOpt(vector<int>& arr, int target){
    int n = arr.size();
    int sum;
    int i, j, k, l;
    vector<vector<int>> ans;
    for(i=0;i<n;i++){
        while(i>0 && arr[i]==arr[i-1]) continue;
        for(j=i+1;j<n;j++){
            while(j>i+1 && arr[j]==arr[j-1]) continue;
            while(k<l){
                sum=arr[i]+arr[j]+arr[k]+arr[l];
                if(sum<target){
                    k++;
                    while(k<l && arr[k] == arr[k-1]) k++;;
                }
                else if(sum>target){
                    l--;
                    while(k<l && arr[l] == arr[l+1]) l--;
                }
                else{
                    vector<int> temp = {arr[i], arr[j], arr[k], arr[l]};
                    ans.push_back(temp);
                    k++;
                    while(k<l && arr[k]==arr[k-1]) k++;
                    l--;
                    while(k<l && arr[l]==arr[l+1]) l--;
                }
            }
        }
    }

    return ans;
}
//Tc - O(n^3), SC - O(1)
//---------------------------------------------------------------------------------


int main(){
    // cout<<pascalRowColOpt(6, 5);

    // printPascalOpt(6);

    // vector<int> arr = {2, 2, 1, 1, 1, 2, 2};
    // cout<<majorityElemNBy2(arr);

    // vector<int> arr = {1, 2, 1, 1, 3, 2, 2};
    // majorityElemGNB3Opt(arr);

    vector<int> arr={1, 0, -1, 0, -2, 2};
    auto res = FourSumBet(arr, 0);

    for(auto v:res){
        for(auto i:v){
            cout<<i<<" ";
        }
        cout<<endl;
    }

    return 0;
}