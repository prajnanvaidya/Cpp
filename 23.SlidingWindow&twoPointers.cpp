#include<bits/stdc++.h> 

using namespace std;

//------------------------------------------------------------------------------------------------------------

//Sliding window & 2 Pointers
//4 patterns in sliding window and 2 pointers

//1. Constant Window
// Given an arr of posities and negaties and int k find maximum sum by picking 4 elem consecutively
// arr - {-1, 2, 3, 3, 4, 5, -1} k=4

int ConstWind(vector<int>& arr, int k){
    int sum, maxi=INT_MIN;
    for(int i=0;i<arr.size()-3;i++){
        sum=arr[i];
        for(int j=i+1;j<i+k;j++){
            sum+=arr[j];
            maxi = max(maxi, sum);
        }
    }
    return maxi;
}
//Tc - O(n^2), Sc - O(1)


//Using sliding window

int ConstWindOpt(vector<int>& arr, int k){
    int i=0, j=0;
    int sum=0, maxi=INT_MIN;

    while(i<arr.size() && j<arr.size()){
        sum+=arr[j];
        maxi=max(sum, maxi);
        if(j>=(k-1)){
            sum-=arr[i];
            i++;
        }
        j++;
    }
    return maxi;
}
//Tc - O(n), Sc - o(1)

//----------------------------------------------------------------------------------------------------------

//2. Varying length sliding window 
// Longest Subarr or Substring with sum<=k
//subarr - any consecutive pportion of arr
auto longestSub(vector<int>& arr, int k){
    vector<int> temp;
    int sum=0, maxi=INT_MIN, m,n, maxLen=0;
    bool flag;
    for(int i=0;i<arr.size();i++){
        flag=false;
        sum=arr[i];
        if(sum<=k && maxi<sum && maxLen<=1){
            flag=true;
            maxi=sum;
            n=i;
            m=i;
            maxLen=1;
        }
        for(int j=i+1;j<arr.size();j++){
            sum+=arr[j];
            if(sum<=k && maxi<sum && maxLen<=j-i+1){
                flag=true;
                maxi=sum;
                n=i;
                m=j;
                maxLen=(j-i+1);
            }
        }
        if(flag){
            temp.clear();
            while(n<=m){
                temp.push_back(arr[n]);
                n++;
            }
        }
        
    }
    return temp;
}
//Tc - o(n^2), Sc - o(1)


//Better using sliding window of variable size

//Returning maximum length subarr of sum<=k
//If question tells a constraint: if same len subarr with sum,=k then return one which is more near to k
auto longestSubBet(vector<int>& arr, int k){
    int l=0, r=0;
    int maxLen=0;
    int sum=0;
    int prevSum;
    vector<int> maxLenSub;
    vector<int> temp;

    while(l<=r && r<arr.size()){
        sum+=arr[r];
        temp.push_back(arr[r]);

        while(sum>k){
            temp.erase(temp.begin());
            sum-=arr[l];
            l++;
        }
        if(maxLen<=(r-l+1)){
            if(maxLen=(r-l+1)){
                if(prevSum<sum){
                    maxLenSub=temp;
                    prevSum=sum;
                }
            }
            else{
                maxLen=max(maxLen, r-l+1);
                maxLenSub = temp;
                prevSum=sum;
            }
        }
        r++;
    }
    return maxLenSub;
}
//Tc - O(n + n), Sc - O(n + n)

//Returning only maximum length
int longestSubBetLen(vector<int>& arr, int k){
    int sum=0;
    int maxLen=0;
    int l=0, r=0;

    while(l<=r && r<arr.size()){
        sum+=arr[r];
        while(sum>k){
            sum-=arr[l];
            l++;
        }
        maxLen=max(maxLen, r-l+1);
        r++;
    }
    return maxLen;
}
//TC - O(n + n), Sc - O(1)

//Optimal: Here the window is not strinked less then maxLen as already we obtained a answer following condition.
//main goal is to return maximu length of subar whose sum<=k, here i don want to return a subarr whose sum is near to k, i just want to return a subarr with hisghest len, 
// for ex: arr - {1,1,1,4,9,1}, k=14, sub1: {1,1,1,4} len=4 sum=7, sub2: {4,9,1} len=3, sum=14 yet answer = 4

//So every time we sum>k we just do l++ one time
int longestSubOptimal(vector<int>& arr, int k){
    int sum=0;
    int l=0, r=0;
    int maxLen=0;
    while(l<=r && r<arr.size()){
        sum+=arr[r];
        if(sum>k){
           sum-=arr[l];
           l++;  
        }
        maxLen = max(maxLen, r-l+1);
        r++;
    }
    return maxLen;
}
//TC - O(n), SC - O(1)

//But this approach not possible if we have to return the subarr
// cuz in ex: [2,5,1,7,10], k=14 here even though 2,5,1 and 5,1,7 are of same len=3 but if question asked near to k then ans=5 1 7

//----------------------------------------------------------------------------------------------------------

//No of subarr in a given arr which matches the condition
// Ex: Give no of subarrs with sum=k

int noOfSub(vector<int>& arr, int k){
    int sum=0;
    int n=0;
    for(int i=0;i<arr.size();i++){
        sum=arr[i];
        if(sum==k)
            n++;
        for(int j=i+1;j<arr.size();j++){
            sum+=arr[j];
            if(sum==k)
                n++;
        }
    }
    return n;
}
//TC - O(n^2), SC - o(1)

//Its difficult to do it in sliding window as we dont really figure out when to increment the left and right pointers
// For that reason we take
// ans1 = no of subarrs with sum<=k
// ans2 = no of subarrs with sum<=(k-1)
//no of subarrs with sum=k = (ans2 - ans1)
//Because when sum<=k we know when interm,ediate_sum>k move left ptr and when inter_sum<k move right ptr

int noOfSubHelper(vector<int>& arr, int k){
    int r=0, l=0;
    int n=0, sum=0;
    while(r<arr.size()){
        sum+=arr[r];
        while(sum>k){
            sum-=arr[l];
            l++;
        }
        if(sum>0)
            n++;
        r++;
    }
    return n;
}
//Not possible its code for longest subarr with sum<=k but i want no of subarrs with sum<=k, 

int noOfSubOpt(vector<int>& arr, int k){
    int res1=noOfSubHelper(arr, k);
    int res2=noOfSubHelper(arr, k-1);
    cout<<res1<<" "<<res2<<endl;

    return (res1-res2);
}

//------------------------------------------------------------------------------------------------------------

//3.Minimum/Shortest Window with condition
//First get a valid window and shrink it to check does it remains valid or not

//----------------------------------------------------------------------------------------------------------
// Problmes:
// 1. Maximum points that can be obtained from n cards
// arr - {6, 2, 3, 4, 7, 2, 1, 7, 1} k=4
//U can go with either front or back direction or both but total should be k such that sum of elem should be maximum
//Here ans - {6,2,7,1}

int maxPoints(vector<int>& arr, int k){
    int r=k, l=arr.size();
    int sum=0, maxi=0;
    for(int i=0;i<k;i++){
        sum+=arr[i];
    }
    maxi = max(maxi, sum);
    for(int i=0;i<k;i++){
        r--;
        sum-=arr[r];
        l--;
        sum+=arr[l];
        maxi = max(maxi, sum);
    }
    return maxi;
}
//Tc - O(k), SC - O(1)

auto maxPointsVec(vector<int>& arr, int k){
    int r=k, l=arr.size();
    int sum=0, maxi=0;
    vector<int> temp;
    vector<int> maxTemp;
    for(int i=0;i<k;i++){
        sum+=arr[i];
        temp.push_back(arr[i]);
    }
    maxi = max(maxi, sum);
    for(int i=0;i<k;i++){
        r--;
        temp.erase(temp.begin()+r);
        sum-=arr[r];
        l--;
        temp.push_back(arr[l]);
        sum+=arr[l];
        if(maxi<sum){
            maxi=sum;
            maxTemp=temp;
        }
    }
    return maxTemp;
}
//TC - O(k^2), SC - O(k + k)


int maxPointsVecHis(vector<int>& arr, int k){
    int lsum=0, rsum=0;
    int maxi=0;
    int r_index=arr.size()-1;
    
    for(int i=0;i<k;i++)
        rsum+=arr[i];
    maxi=max(maxi, lsum+rsum);
    for(int i=k-1;i>=0;i--){
        rsum-=arr[i];
        lsum+=arr[r_index];
        r_index--;
        maxi=max(maxi, lsum+rsum);
    }
    return maxi;
}

//----------------------------------------------------------------------------------------------------------

//2. Longest Substring withot repeating characters
//s={c,a,d,b,z,a,b,c,d}
//ans - {c,a,d,b,z}
int longestSubChar(vector<char>& arr){
    unordered_map<char, int> CharHash;
    int maxLen=0;
    int l=0, r=0;
    while(r<arr.size()){
        if(CharHash.find(arr[r]) == CharHash.end()){
            CharHash[arr[r]]=r;
            r++;
        }
        else{
            l=CharHash[arr[r]]+1;
            maxLen = max(maxLen, int(CharHash.size()));
            r=l;
            CharHash.clear();
        }
    }
    maxLen = max(maxLen, int(CharHash.size()));
    return maxLen;
}
//TC - O(n), SC - O(n){if arr has unique chars}


auto longestSubCharRet(vector<char>& arr){
    unordered_map<char, int> CharHash;
    int maxLen=0;
    int l=0, r=0;
    vector<char> temp;
    while(r<arr.size()){
        if(CharHash.find(arr[r]) == CharHash.end()){
            CharHash[arr[r]]=r;
            r++;
        }
        else{
            l=CharHash[arr[r]]+1;
            if(maxLen < int(CharHash.size())){
                maxLen = int(CharHash.size());
                for(auto v:CharHash)
                    temp.push_back(v.first);
            }
            r=l;
            CharHash.clear();
            temp.clear();
        }
    }
    if(maxLen < int(CharHash.size())){
        maxLen = int(CharHash.size());
        for(auto v:CharHash)
            temp.push_back(v.first);
    }
    return temp;
}
//Tc - O(n), SC - O(n+n)

//Brute
//Find all possible subarr and each time maintain a hash arr of size 256 where index represents char and value represents index
int longestSubBrut(vector<char> arr){
    
    int maxLen=0;
    for(int i=0;i<arr.size();i++){
        vector<int> hash(256, 0);
        for(int j=i;j<arr.size();j++){
            if(hash[arr[j]] != 0)
                break;
            hash[arr[j]]=j;
            maxLen = max(maxLen, j-i+1);
        }
    }
    return maxLen;
}
//Tc - O(n^2), Sc - O(256)

int longestSubOptHis(vector<char> arr){
    vector<int> hash(256, -1);
    int l=0, r=0, maxLen=0;
    while(r<arr.size()){
        if(hash[arr[r]] < l){
            hash[arr[r]]=r;
            r++;
        }
        else{
            maxLen = max(maxLen, (r-1)-l+1);
            l = hash[arr[r]]+1;
        }
    }
    maxLen = max(maxLen, (r-1)-l+1);
    return maxLen;
}
// { 'a', 'd', 'b', 'z', 'a', 'b', 'c'};
//Tc - O(n), Sc - O(256)


//------------------------------------------------------------------------------------------------------------------


//3. Maximum consecutive ones - 3
// Flip at most of k zeroes to find maximum consecutive 1s
//Given arr of 0 and 1's and k 
//This can also said as finding longest subarr with max zeroes as k


int MaxConsecOnes3(vector<int> arr, int k){
    int zrs;
    int maxLen=0;
    
    for(int i=0;i<arr.size();i++){
        zrs=0;
        for(int j=i;j<arr.size();j++){
            if(arr[j]==0)
                zrs++;
            if(zrs <= k){ //< because sometimes there is no intended no of zeroes
                maxLen=max(maxLen, j-i+1);
            }
            else if(zrs>k)
                break;
        }
    }
    return maxLen;
}

//Maintain a vector of size k the val representing the index in which the ith zero is found, So when 0 increase u can take left ptr to 1 index ahead of first 0 and then upodate the index of first zer to previous second and so on

int MaxConsecOnes3Bet(vector<int>& arr, int k){
    vector<int> temp(k, -1);
    int l=0, r=0;
    int zrs=0, z;
    int first1=1;
    int maxLen=0;
    while(r<arr.size()){
        if(arr[r]==0){
            if(zrs<k)
                temp[zrs]=r;
            zrs++;
        }        
        // else{
        //     if(k==0 && first1){
        //         temp.push_back(r);
        //         first1=0;
        //     }
        // }
        if(zrs>k){
            if(k>0)
                l=temp[0]+1;
            // else{
            //     int g=temp[0]+1;
            //     while(arr[g]!=1){
            //         g++;
            //     }
            //     l=g;
            //     temp[0]=l;
            // }

            if(k>1){
                z=1;
                while(z<k){
                    swap(temp[z-1], temp[z]);
                    z++;
                }
                temp[z-1] = r; 
            }
            else if(k==1){
                temp[0]=r;
            }
            zrs--;
        }

        if(zrs == k){
            maxLen=max(maxLen, r-l+1);
            cout<<maxLen<<": "<<l<<","<<r<<" "<<zrs<<endl;
        }
        r++;
    }
    return maxLen;
}
//TC - O(n),SC - O(k)

//using a hash arr becomes too complicated for the purpose so loop instead to find the no after the first zero to update left ptr
int MaxConsecOnes3Opt(vector<int>& arr, int k){
    int l=0, r=0;
    int maxLen=0;
    int zrs=0;

    while(r<arr.size()){
        if(arr[r]==0)
            zrs++;
        while(zrs>k){
            if(arr[l]==0)
                zrs--;
            l++;
        }
        if(zrs==k)
            maxLen = max(maxLen, r-l+1);
        r++;
    }
    return maxLen;
}
//Tc - o(n + n), Sc - o(1)

//make it more optimal tc - O(n)
//Do not decrease the len of window beyond maxLen, possible by converting while loop to if condfition so it only moves left ptr one step ahead of previous

int MaxConsecOnes3Optimal(vector<int> & arr, int k){
    int l=0, r=0, maxLen=0, zrs=0;
    while(r<arr.size()){
        if(arr[r]==0)
            zrs++;
        if(zrs>k){
            if(arr[l]==0)
                zrs--;
            l++;
        }
        if(zrs==k)
            maxLen = max(maxLen, r-l+1);
    }
    return maxLen;
}
//Tc - O(n), Sc - O(1)

//-------------------------------------------------------------------------------------------------------------------

//4. Fruit into basket
// U got to a farm where u are given with 2 buckets and there exist n different trees producing different types of fruit 
// U need to pick maximum fruits such that each basket can only store 1 type of fruit and u can go only in a sequential fashion to collect fruits from trees and stop when a tree produces a different fruit type other then type 1 and 2 u just started collecting

//              0  1  2  3  4  5  6  7  8  9 10
//input: arr - {3, 3, 3, 1, 2, 1, 1, 2, 3, 3, 4}
// here index represents different trees and vals represents fruit type, go contigously and find the maximum no of fruits that can be picked inside 2 baskets stop when u get a fruit of different type.
//Ans - 1,2,1,1,2 - 5


int FruitIntoBasket(vector<int>& arr){
    int maxLen=0;
    int nType=0;
    int prevType, nextType;
    for(int i=0;i<arr.size();i++){
        nType=1      ;
        prevType=arr[i];
        for(int j=i;j<arr.size();j++){
            if(arr[j]!=prevType && nType==1){
                nextType=arr[j];
                nType++;
            }
            if(arr[j] == prevType || arr[j] == nextType){
                maxLen = max(maxLen, j-i+1);
            }
            else{
                break;
            }
        }
    }
    return maxLen;
}
//Tc - O(n^2), Sc - O)(1)

int FruitToBasketBet(vector<int>& arr){
    int maxLen=0;
    int nType=-1, pType=-1;
    int n=0;

    bool flag=false;

    int l=0, r=0;
    while(r<arr.size()){
        if(nType==-1 && pType==-1){
            pType=r;
            n=1;
        }
        else if(arr[r]!=arr[pType] && n==1){
            nType=r;
            n++;
        }
        if(arr[r]==arr[pType] || arr[r]==arr[nType] ){
            maxLen=max(maxLen, r-l+1);
        }
        else{
            l=nType;
            pType=l;
            nType=-1;
            n=1;
            flag=true;
        }
        
        if(flag == false){
            r++;
        }
        else{
            r=l+1;
            flag=false;
        }
    }
    return maxLen;
}
// Greater then O(n) lesser then O(n^2), Sc-O(1)

//He used set rather then variable to store firsat and second elem
//replace n with set.size() and replace prevtype, nexType with set elems
int FruitToBaskethis(vector<int>& arr){
    set<int> stt;
    int maxLen=0;
    for(int i=0;i<arr.size();i++){
        stt.clear();
        for(int j=i;j<arr.size();j++){
            stt.insert(arr[j]);
            if(stt.size() > 2){
                break;
            }
            maxLen = max(maxLen, j-i+1);
        }
    }
    return maxLen;
}
//TC - O(n^2){logn doesnt contribute even though used set because set size cannot go greater then 2 so log 3 ~ O(1)}, Sc - O(3)

//Using sliding window along with a map inorder to remove moving right ptr again back to updated_left+1
int FruitToBasketBetHis(vector<int>& arr){
    unordered_map<int, int> mpp;
    int l=0, r=0;
    int maxLen=0;
    while(r<arr.size()){
        if(mpp.size()<3){
            mpp[arr[r]]++;
        }
        while(mpp.size()>2){
            mpp[arr[l]]--;
            if(mpp[arr[l]] == 0){
                mpp.erase(arr[l]);
            }
            l++;
        }
        maxLen = max(maxLen, r-l+1);
        r++;
    }
    return maxLen;
}
//TC - O(n + n){since map doesnt exceed 3 keys}, Sc - O(1){O(3)}

//To make it optimal {O(n)} use if over while, which never allows window size to go less then or equal to maxLen, why? - because as soon as u see first extra fruitType u stop there and make condition execute and go inside to increment left by 1 place it works just by incremeneting 1 time because the before loop the mpp was valid and maxLen was updated with length
int FruitToBasketOptimal(vector<int>& arr){
    unordered_map<int, int> mpp;
    int l=0, r=0;
    int maxLen=0;

    while(r<arr.size()){
        mpp[arr[r]]++;
        if(mpp.size()>2){
            mpp[arr[l]]--;
            if(mpp[arr[l]] == 0){
                mpp.erase(arr[l]);
            }
            l++;
        }
        if(mpp.size() <= 2){
            maxLen = max(maxLen, r-l+1);
        }
        r++;
    }
    return maxLen;
}
//Tc - O(n), SC - O(1)

//To make bucket size variable
int FruitToBasketOptimalK(vector<int>& arr, int k){
    unordered_map<int, int> mpp;
    int l=0, r=0;
    int maxLen=0;

    while(r<arr.size()){
        mpp[arr[r]]++;
        if(mpp.size()>k){
            mpp[arr[l]]--;
            if(mpp[arr[l]] == 0){
                mpp.erase(arr[l]);
            }
            l++;
        }
        if(mpp.size() <= k){
            maxLen = max(maxLen, r-l+1);
        }
        r++;
    }
    return maxLen;
}

//-------------------------------------------------------------------------------------------------------------------
//5. Longest substring with atmost k distinct characters  
//Ex: a,a,a,b,b,c,c,d k=2
//Ans - {a,a,a,b,b}
int LongestSubKDist(vector<char>& arr, int k){
    int maxLen=0;
    set<int> st;
    for(int i=0;i<arr.size();i++){
        st.clear();
        for(int j=i;j<arr.size();j++){
            st.insert(arr[j]);
            if(st.size()>k){
                break;
            }
            maxLen = max(maxLen, j-i+1);
        }
    }
    return maxLen;
}

//Better using map and sliding window
int LongestSubKDistBet(vector<char>& arr, int k){
    unordered_map<int, int> mpp;
    int l=0, r=0;
    int maxLen=0;
    while(r<arr.size()){
        mpp[arr[r]]++;
        while(mpp.size() > k){
            mpp[arr[l]]--;
            if(mpp[arr[l]] == 0){
                mpp.erase(arr[l]);
            }
            l++;
        }
        if(mpp.size() == k)
            maxLen=max(maxLen, r-l+1);
        r++;
    }
    return maxLen;
}
//TC - O(n + n) {where at worst case left can move full arr for ex: {a, a, a, a, b}, k=1}, Sc - O(1)

//Optimal: do not allow length of window to go less then maxLen, can be made just changing while to if condition cuz the fact that we are looping and in previous loop the maxLen is configured if window is vaid so this iteration if mpp is invalid so its possible to check only incrementing left one time and as right always increments

int LongestSubKDistOpt(vector<char>& arr, int k){
    unordered_map<char, int> mpp;
    int l=0, r=0;
    int maxLen=0;

    while(r<arr.size()){
        mpp[arr[r]]++;
        
        if(mpp.size() > k){
            mpp[arr[l]]--;
            if(mpp[arr[l]] == 0){
                mpp.erase(arr[l]);
            }
            l++;
        }
        if(mpp.size() == k){
            maxLen = max(maxLen, r-l+1);
        }
        r++;
    }
    return maxLen;
}
//Tc - O(n){map takes atmost O(log(256)) as max chars in cpp is 256 so doesnt matter}, Sc - O(1)
//-------------------------------------------------------------------------------------------------------------------
//6. Number of substrings containing all 3 characters(a, b, c) in arr containing chars a, b, c
//Ex - b,b,a,c,b,a  res=9
int NoSubConAll3(vector<char>& arr){
    int n=0;
    unordered_set<char> st;
    for(int i=0;i<arr.size();i++){
        st.clear();
        for(int j=i;j<arr.size();j++){
            st.insert(arr[j]);
            if(st.size()==3)
                n++;
            else if(st.size() > 3)
                break;
        }
    }
    return n;
}


int NoSubConAll3BrutHash(vector<char>& arr){
    int n=0;
    vector<int> hash(3, 0);

    for(int i=0;i<arr.size();i++){
        hash = {0,0,0};
        for(int j=i;j<arr.size();j++){
            hash[arr[j] - 'a'] = 1;
            if(hash[0]==1 && hash[1]==1 && hash[2]==1){
                n= n+(arr.size()-j); //optimization when j reaches the point where 3 chars are found it should consider all remaining indices till last as answer
                break;
            }
        }
    }
    return n;

}
//TC - O(n^2), Sc - O(1)

int NoSubConAll3Opt(vector<char>& arr){
    int n=0;
    vector<int> hashAr(3, -1);
    int r=0; //No need to maintain any left ptr 

    while(r<arr.size()){
        hashAr[arr[r]-'a']=r;
        if(hashAr[0]!=-1 && hashAr[1]!=-1 && hashAr[2]!=-1){     //Can also exclude this check as if any elem in hashAr is -1, then min_element comes out to be -1+1=0 cnt remains same
            n+=*(min_element(hashAr.begin(), hashAr.end()))+1;
        }
        r++;
    }
    return n;
} 
//TC - O(n), Sc - O(1)

//--------------------------------------------------------------------------------------------------------------------------------------
//7. Longest Repeating Character Replacement
//Given an arr of characters, and k, u can convert atmpost k characters in a substring , so with that find out longest substring having same characters after conversion
//Output: Lenghth of longest repeating substring
//U can replace k different characters also

//Brute: generate all subarr and in each subarr startime keep a hash arr of size 256 , each time u see a elem in subarr increment it in hash arr for corresponding ascii of char as index and when u see hash size lesser then or equal to k+1


int longrepeatCharreplace(vector<char>& arr, int k){
    vector<int> hash;
    int maxLen=0;
    int replace_needed=0, distinct=0;
    int maxi;

    for(int i=0;i<arr.size();i++){
        hash = vector<int>(256, 0);
        for(int j=i;j<arr.size();j++){
            hash[arr[j]-'A']++;

            maxi = *(max_element(hash.begin(), hash.end()));
            replace_needed = (j-i+1) - maxi;
            if(replace_needed<=k){
                maxLen=max(maxLen, j-i+1);
            }
        }
    }
    return maxLen;
}
//Tc - O(n^2), SC - O(1)

//Brut with optimization as if a subarr found with distinct character or hash siuze>k+1 then there is no way it can considered as a extra character cannot be replaced even in best case i.e all elem in hash except the elem with max freq is ahaving val 1
int longrepeatCharreplaceOpted(vector<char>& arr, int k){
    vector<int> hash;
    int maxLen=0;
    int replace_needed=0, distinct=0;
    int maxi;

    for(int i=0;i<arr.size();i++){
        distinct=0;
        hash = vector<int>(256, 0);
        for(int j=i;j<arr.size();j++){
            if(hash[arr[j]-'A'] == 0)
                distinct++;
            hash[arr[j]-'A']++;
            if(distinct > k+1){
                break;
            }
            else{
                maxi = *(max_element(hash.begin(), hash.end()));
                replace_needed = (j-i+1) - maxi;
                if(replace_needed<=k){
                    maxLen=max(maxLen, j-i+1);
                }
            }
        }
    }
    return maxLen;
}
//Tc - O(n^2) { since finding maxi doesnt take greater then O(256) = O(1)}, Sc - o(1)

int longrepeatCharReplaceBrutHis(vector<char>& arr, int k){
    int maxLen=0, max_freq;
    vector<int> hash;
    int replacement_needed;

    for(int i=0;i<arr.size();i++){
        hash = vector<int>(26, 0);
        max_freq=0;
        for(int j=i;j<arr.size();j++){
            hash[arr[j]-'A']++;
            max_freq = max(max_freq, hash[arr[j]-'A']);
            replacement_needed = (j-i+1) - max_freq;
            if(replacement_needed <= k){
               maxLen = max(maxLen, (j-i+1));
            }
            else{
                break;
            }
        }
    }
    return maxLen;
}
//Tc - o(n^2), Sc - o(1)

int longRepaeatCharReplaceBet(vector<char>& arr, int k){
    int max_freq=0;
    unordered_map<char, int> mpp;
    int l=0, r=0;
    int replace_needed=0, maxLen=0;

    while(r<arr.size()){
        mpp[arr[r]]++;
        max_freq = max(max_freq, mpp[arr[r]]);
        replace_needed = (r-l+1)-max_freq;
        while(replace_needed > k){
            mpp[arr[l]]--;
            l++;
            max_freq=0;
            for(auto v:mpp)
                max_freq=max(max_freq, v.second);
            replace_needed=(r-l+1)-max_freq; 
        }
        maxLen=max(maxLen, r-l+1);
        r++;      
    }
    return maxLen;
}
//TC - O(n + n*256), SC - O(1)

//Same using hash arr
int longRepeatCharReplaceBetHash(vector<char>& arr, int k){
    vector<int> hash(26, 0);
    int maxLen=0;
    int max_freq=0;
    int l=0, r=0;

    while(r<arr.size()){
        hash[arr[r]-'A']++;
        max_freq=max(max_freq, hash[arr[r]-'A']);

        while(((r-l+1)-max_freq)>k){
            hash[arr[l]-'A']--;
            l++;
            for(auto v:hash){
                max_freq=max(max_freq, v);
            }
        }
        maxLen=max(maxLen, r-l+1);
        r++;
    }
    return maxLen;
}
//Tc - O(n + n.26), SC - O(26)

//To make it Optimal we will not make length of window less then maxLen and also not calculate max_freq again as there is no point in decreasing in max_freq 
int longRepeatCharReplaceOpt(vector<char>& arr, int k){
    vector<int> hash(26, 0);
    int maxLen=0, max_freq=0;
    int l=0, r=0;
    while(r<arr.size()){
        hash[arr[r]-'A']++;
        max_freq=max(max_freq, hash[arr[r]-'A']);
        if(((r-l+1)-max_freq) > k){
            hash[arr[l]-'A']--;
            l++;
        }
        if(((r-l+1)-max_freq) <= k){
            maxLen = max(maxLen, (r-l+1));
        }
        r++;
    }
    return maxLen;
}
//Tc - o(n), Sc - O(1)
//------------------------------------------------------------------------------------------------------------------------------------

//8. Binary subarray with sum
//Given a arr of 0 and 1's and int k, u need to count all subarrs whose sum of elems equal to k
//Ex: arr - {1, 0, 1, 0, 1}, k=2
// 1 0 1
// 1 0 1 0
// 0 1 0 1
// 1 0 1
// res=4

//Brut: find all subarrs and if sum=k then increment count

int binarySubSumK(vector<int>& arr, int k){
    int n=0;
    int sum;
    for(int i=0;i<arr.size();i++){
        sum=0;
        for(int j=i;j<arr.size();j++){
            sum+=arr[j];
            if(sum==k)
                n++;
            else if(sum>k)
                break;
        }
    }
    return n;
}
//Tc - O(n^2), SC - O(1)

int binarySubSumKBet(vector<int>& arr, int k){
    int l=0, r=0;
    int sum=0;
    int n=0;
    while(r<arr.size()){
        sum+=arr[r];
        if(sum<k){
            r++;
            continue;
        }
        else if(sum==k){
            while(sum==k){
                n++;
                sum-=arr[l];
                l++;
            }
        }
        else{
            while(sum>k){
                sum-=arr[l];
                l++;
            }
        }
        r++;
    }
    return n;
}

//This is the problem arises when applied sliding window and 2 pointer naively cuz if u moved l upto the point where u get window size equal to k to increment count then u miss some subarr which may include future r and l elems cuz adding 0 to some doesnt affect
//So we will do (no of subarrr's with sum <= k) - (no of subarr's with sum <= (k-1)) 

int SumlessthenEqualHelper(vector<int> arr, int goal){
    if(goal<0){
        return 0;
    }
    int sum=0;
    int n=0;
    int l=0, r=0;
    while(r<arr.size()){
        sum+=arr[r];
        while(sum>goal){
            sum-=arr[l];
            l++;
        }
        n+=(r-l+1);
        r++;
    }
    return n;
}
//TC - o(2*n), Sc - O(1)

int NoSubBinaryKOpy(vector<int>& arr, int k){
    
    return (SumlessthenEqualHelper(arr, k)-SumlessthenEqualHelper(arr, k-1));
}
//Tc - O(2*(2N)), Sc - O(1)


//Better not optimal using a formula (first_1_index - left)+1 gives no of subarrs that can be found iteratively
//Ur finding by dry running on examples
int BinaryNoSubBetHash(vector<int>& arr, int k){
    int sum=0, n=0, hs_id=0;
    vector<int> hash(k, -1);
    int l=0, r=0;
    while(r<arr.size()){
        sum+=arr[r];
        while(sum>k){
            sum-=arr[l];
            if(arr[l]==1){
                for(int i=1;i<k;i++)
                    hash[i-1]=hash[i];
                hs_id--;
            }
            l++;
        }
        //or
        // if(sum>k){
        //     sum-=1;
        //     l=hash[0]+1;
        //     for(int i=1;i<k;i++)
        //         hash[i-1]=hash[i];
        //     hs_id--;
        // }

        if(arr[r]==1){
            hash[hs_id++] = r;
        }
        if(sum==k)
            n+=((hash[0]-l)+1);
        r++;
    }
    return n;
}

//Same implementation but using a deque rather then maintaining sum and separate hash arr, as we can consider sum = size of deque and easily can pop front and push front

int BinaryNoSubBetDeque(vector<int>& arr, int k){
    if(k==0){
        int zrs=0, ans=0;
        for(auto v:arr){
            if(v==0)
                zrs++;
            else
                zrs=0;
            ans+=zrs;
        }
        return ans;
    }

    deque<int> dq;
    int n=0;
    int l=0, r=0;

    while(r<arr.size()){
        if(arr[r]==1)
            dq.push_back(r);
        if(dq.size()>k){
            l=dq.front()+1;
            dq.pop_front();
        }
        if(dq.size() == k){
            n+=(dq.front()-l+1);
        }
        r++;
    }
    return n;
}
//Tc - O(n)

//Actual better implementation using a hash arr using concept of prefix sum;
// for given arr take prefix sum arr and maintain a map which stores frequency of time a distinct prefix sum is obtained and loop through it and find if [prefix_sum_at_i - k] exist in freq map say has freq m times if yes then do ans+=m
int BinaryNoSubBetActual(vector<int>& arr, int k){
    unordered_map<int, int> mpp;
    for(int i=0;i<arr.size();i++)
        mpp[i];
    mpp[0]=1;
    int sum=0;
    int ans=0;
    for(int i=0;i<arr.size();i++){
        sum+=arr[i];
        mpp[sum]++;
        if(sum>=k){
            ans+=mpp[sum-k];
        }
    }
    return ans;
}
//Tc - O(n), Sc - O(n)
//-------------------------------------------------------------------------------------------------------------------------------------

//Count the number of nice subarrs
//Nice here means given a arr of int and k return the number of subarrs whose odd nos count equal to k
//Ex: arr - [1, 1, 2, 1, 1], k=3
// 1 1 2 1
// 1 2 1 1 
// ans=2

//Can be solved just by cvonsidering all evens as 0 and odds as 1 and just it bercomes previous problems where we can say in a binary arr find the no of subarrs whose sum=k 
//1 0 1 1, k=3


//Optimal: (sum<=k)-(sum<=(k-1)) : sum=k
int theHelper(vector<int>& arr, int k){
    int l=0, r=0;
    int sum=0;
    int ans=0;
    while(r<arr.size()){
        sum+=arr[r];
        while(sum>k){
            sum-=arr[l];
            l++;
        }
        ans+=(r-l+1);
        r++;
    }
    return ans;
}

int cntNiceSubs(vector<int>& arr, int k){
    vector<int> binArr(arr.size());
    for(int i=0;i<arr.size();i++){
        if(arr[i]%2==0)
            binArr[i]=0;
        else
            binArr[i]=1;
    }
    return (theHelper(binArr, k)) - (theHelper(binArr, k-1));
}
//Tc - O(n + 2 * 2n), SC - O(n)

//-------------------------------------------------------------------------------------------------------------------------------------
//Subarrs with k different integers
//Return the no of subarrs with k different integers from a arr

int subsKDiffInt(vector<int>& arr, int k){
    if(k<=0){
        return 0;
    }
    int n=0;
    set<int> st;
    for(int i=0;i<arr.size();i++){
        st.clear();
        for(int j=i;j<arr.size();j++){
            st.insert(arr[j]);
            if(st.size()==k)
                n++;
            else if(st.size()>k)
                break;
        }
    }
    return n;
}
//Tc - O(n^2), Sc - O(1)

//This is the Opt cuz they are asking no of substring not longest substring
int subsKDistHelper(vector<int>& arr, int k){
    unordered_map<int, int> mpp;
    int l=0, r=0;
    int cnt=0;
    while(r<arr.size()){
        mpp[arr[r]]++;
        while(mpp.size()>k){
            mpp[arr[l]]--;
            if(mpp[arr[l]]==0)
                mpp.erase(arr[l]);
            l++;
        }
        cnt+=(r-l+1);
        r++;
    }
    return cnt;
}

int NoSubsDistK(vector<int>& arr, int k){
    return subsKDistHelper(arr, k) - subsKDistHelper(arr, k-1);
}

//---------------------------------------------------------------------------------------------------------------------
//Minimum Window Substring
// Given a string s and string t u have to give me a minimum length substring that has the string t from s
// Ex: s= d,d,a,a,a,b,b,c,a   t= a,b,c
// res= b,c,a
// The resultant substring the occurences of characters should be either equal to greater then what is t
//Exc: s= d,d,a,a,a,b,b,c,a, t= b,a,b,c
// res= a,b,b,c

//Brute: generate all substrings, maintain hash for t and for each substring also maintain a hash and check the ocurrences is equal to greater then put to minLen 

//Just return minLen 

int minimumWindowSub(string s, string t){
    int minLen=INT_MAX;

    vector<int> tHash(26);
    for(auto v:t){
        tHash[v-'a']++;
    }

    int tCnt=0, unique_t=0;
    for(auto v:tHash)
        if(v>0)
            unique_t++;

    vector<int> sHash;

    for(int i=0;i<s.size();i++){
        sHash = vector<int>(26, 0);
        for(int j=i;j<s.size();j++){
            sHash[s[j] - 'a']++;
            tCnt=0;
            for(int k=0;k<26;k++){
                if(tHash[k]!=0 && sHash[k] >= tHash[k])
                    tCnt++;
            }
            if(tCnt == unique_t){
                minLen = min(minLen, j-i+1);
            }
        }
    }
    if(minLen==INT_MAX)
        return -1;
    return minLen;
}
//Tc - O(26 + 26 + n^2.26), Sc - O(52)


//Better then above
int minimumWindowSubBrut(string s, string t){
    unordered_map<char, int> mpp;
    bool flag;
    int minLen=INT_MAX;
    for(int i=0;i<s.size();i++){
        mpp.clear();
        for(auto v:t){
            mpp[v]++;
        }

        for(int j=i;j<s.size();j++){
            mpp[s[j]]--;

            flag=false;
            for(auto v:mpp){
                if(v.second>0)
                    flag=true;
            }

            if(!flag){
                minLen=min(minLen, j-i+1);
            }
        }
    }
    if(minLen==INT_MAX)
        return -1;
    return minLen;
}
//Tc - O(n^2 * m * (m+n)), Sc - O(m+n), where m-t.size(), n-s.size() 

//We can further make it take less time by removing looping over map to see if any char has val > 0, if so setting flag to indicate all elem in t is present in substyring and go to finding length of that to update minLen
//A small optimization: Once find a valid substring and updating the minLen just break and do not go further forward as even though u get valid going further but length does increase so no use

int minimumWindowSubBruteHis(string s, string t){
    vector<int> hash;
    int start_index, cnt=0;
    int minLen = INT_MAX;

    for(int i=0;i<s.size();i++){
        cnt=0;
        hash = vector<int> (256);
        for(auto v:t){
            hash[v]++;
        }
        for(int j=i;j<s.size();j++){
            if(hash[s[j]]>0)
                cnt++;
            hash[s[j]]--;
            if(cnt==t.size()){
                minLen=min(minLen, j-i+1);
                start_index=i;
                break;
            }
        }
    }
    string min_window=s.substr(start_index, minLen);
    cout<<min_window<<endl;
    if(minLen==INT_MAX)
        return -1;
    return minLen;
}
//TC - O(26 * n^2), Sc - O(256)


int minimumWindowSubBet(string s, string t){
    vector<int> hash(256, 0);
    for(auto v:t){
        hash[v]++;
    }
    int cnt=0;
    int l=0, r=0;
    int minLen=INT_MAX;
    int start_index=-1;
    while(r<s.size()){
        if(hash[s[r]]>0)
            cnt++;
        hash[s[r]]--;
        while(cnt==t.size()){
            if(minLen>(r-l+1)){
                minLen=r-l+1;
                start_index=l;
            }

            hash[s[l]]++;
            if(hash[s[l]]>0)
                cnt--;
            l++;
        }
        r++;
    }

    if(start_index!=-1)
        cout<<"Minimum Window: "<<s.substr(start_index, minLen)<<endl;

    if(minLen==INT_MAX)
        return -1;
    return minLen;
}
//Tc - O(m + 2*n), SC - O(1)

//---------------------------------------------------------------------------------------------------------------------

int main(){
    // vector<int> arr={1,1,1,4,9,1};
    // cout<<ConstWindOpt(arr, 4);

    // auto v=longestSubBet(arr, 14);
    // for(auto i:v)
    //     cout<<i<<" ";

    // cout<<longestSubOptimal(arr, 14);

    // vector<int>  arr={1, 2, 1, 2, 1};
    // cout<<noOfSubOpt(arr, 3);

    // vector<int> arr={6,2,3,4,7,2,1,7,1};
    // auto c = maxPointsVec(arr, 4);
    // for(auto v:c)
    //     cout<<v<<" ";

    // cout<<maxPointsVecHis(arr, 4);

    // vector<char> chr = {'a','b','c','d','e',
    // 'a','b','c','d','e',
    // 'a','b','c','d','e'};
    // auto v = longestSubCharRet(chr);
    // reverse(v.begin(), v.end());
    // for(auto i:v)
    //     cout<<i<<" ";

    // cout<<longestSubChar(chr);

    // vector<int> arr={1,1,1,0,0,0,1,1,1,1,0,1};
    // cout<<MaxConsecOnes3Optimal(arr, 1);

    // vector<int> arr = {3,3,3,1,2,1,1,2,3,3,4};
    // cout<<FruitToBasketOptimalK(arr, 1);

    // vector<char> arr = {'a', 'a', 'a', 'b', 'b', 'c', 'c', 'd'};
    // cout<<LongestSubKDistOpt(arr, 2);
    
    // vector<char> arr={'b', 'b', 'a', 'c', 'b', 'a'};
    // cout<<NoSubConAll3Opt(arr);

    // vector<char> arr={'A', 'B', 'B', 'A', 'C', 'B', 'B'};
    // cout<<longRepeatCharReplaceOpt(arr, 2);

    // vector<int> arr={0,1,1};
    // cout<<NoSubBinaryKOpy(arr, 0);

    // vector<int> arr={1, 1, 2, 1, 1};
    // cout<<cntNiceSubs(arr, 3);

    // vector<int> arr={1, 2, 1, 3, 4};
    // cout<<NoSubsDistK(arr, 3);

    string s = "aabxacaab";
    string t = "xabb";
    cout<<minimumWindowSub(s, t);

    return 0;
}