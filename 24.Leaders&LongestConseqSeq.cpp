#include<bits/stdc++.h>

using namespace std;


//1. Leaders in an array
// Leaders - everything on right should be smaller

// Ex: [10, 22, 12, 3, 0, 6] here 22, 12, 6 are leaders
//Note: last lem is always a leader

//Brut
auto LeadersInArr(vector<int>& arr){
    bool flag;
    vector<int> ans;
    for(int i=0;i<arr.size();i++){
        flag=0;
        for(int j=i+1;j<arr.size();j++){
            if(arr[i]<arr[j]){
                flag=1;
                break;
            }
        }
        if(!flag){
            ans.push_back(arr[i]);
        }
    }
    return ans;
}
//TC - O(n^2)
//SC - O(1) {output space O(leaders)}

//Better
//Start from last elem and maintain a maxi and check subsequent elem with maxi if found greater make it as leader and update maxi
auto LeadersInArrBet(vector<int>& arr){
    int maxi = arr[arr.size()-1];
    vector<int> ans;
    ans.push_back(maxi);

    for(int i=arr.size()-2;i>=0;i--){
        if(arr[i]>maxi){
            ans.push_back(arr[i]);
            maxi = arr[i];
        }
    }
    // reverse(ans.begin(), ans.end()) //If ur ques asks in the order in Leaders found in arr as output
    return ans;
}
//Tc - O(n), Sc - O(1)

//---------------------------------------------------------------------------------------------------------------------------------

//2. Longest Consecutive Sequence
//consecutive - the nos one after the other
//Return length of longest consecutive sequence

//Ex: [102, 4, 100, 1, 101, 3, 2, 1, 1]
// longest consecutive seq is: 1, 2, 3, 4 another: 100, 101, 102
// res = 4

//Brut
void longestConseqBrut(vector<int>& arr){
    if(arr.empty()){
        cout<<0;
        return;
    }
    int len=1; //As there would be atleast 1 elem to be conseq if arr is non empty

    int cnt;
    int maxLen=1;
    for(int i=0;i<arr.size();i++){
        len = 1;
        cnt=1;
        int j=0;
        while(j<arr.size()){
            if(arr[i]+cnt == arr[j]){
                len++;
                j=0;
                cnt++;
                continue;
            }
            j++;
        }
        maxLen = max(maxLen, len);
    }
    cout<<maxLen;
}
//Tc - O(n^2*m) where m is len of longest conseq elems in arr
//Sc - O(1)

//Better - see if sorting works
void longestConseqBetSort(vector<int>& arr){
    sort(arr.begin(), arr.end());

    int len=1;
    int maxLen = 1;
    int st=0, cnt=1;

    for(int i=1;i<arr.size();i++){
        if(arr[st] + cnt == arr[i]){
            len++;
            cnt++;
            maxLen = max(maxLen, len);
        }
        else if((arr[st] + cnt-1) == arr[i]){
            continue;
        }
        else{
            len = 1;
            st = i;
            cnt=1;
        }
    }
    cout<<maxLen;
}
//TC - O(nlogn + n), SC - O(1)


//Maintain last_elem and each time as u move in sorted arr check is my current elem-1 = last_elem if yes then increm,ent len otherwise if current_elem != lastElem then update last_elem as curr and make len 1 and if curr_elem == last_elem do nothing.

void longestConseqBetSortHis(vector<int>& arr){
    int lastElem=arr[0];
    int len=1;
    int maxLen = 1;

    for(int i=1;i<arr.size();i++){
        if(arr[i]-1 == lastElem){
            len++;
            lastElem = arr[i];
        }
        else if(lastElem != arr[i]){
            len=1;
            lastElem = arr[i];
        }
        maxLen = max(len, maxLen);
    }
    cout<<maxLen;
}


void longestConseqAnBet (vector<int>& arr){
    int len=0;

    int maxi = *(max_element(arr.begin(), arr.end()));
    vector<int> hashArr(maxi+1, 0);
    for(int i=0;i<arr.size();i++){
        hashArr[arr[i]]=1;
    }
    int maxLen = INT_MIN;
    
    for(int i=0;i<=maxi;i++){
        if(len > maxLen){
            maxLen = len;
        }

        if(hashArr[i] > 0) len++;
        else if(hashArr[i] == 0) len=0;
    }
    cout<<maxLen;
}
//TC - O(n + maxElem), Sc - O(maxElem)

//Optimal using unordered_set
void longestConseqOpt(vector<int>& arr){
    unordered_set<int> st;
    for(int i=0;i<arr.size();i++){
        st.insert(arr[i]);
    }
    int len=0;
    int maxLen=INT_MIN;

    int i=0, cnt, fst_elem;

    for(auto v:st){
        cnt=1;
        fst_elem=v;
        while(st.find(v-cnt) != st.end()){
            fst_elem = v-cnt;
            cnt++;
        }
        len = v-fst_elem+1;
        maxLen = max(maxLen, len);
    }
    cout<<maxLen;
}
//Here TC - O(n + n*m) where m is non starting elem of sequence as only those n whose n-1 exist in set goes to while loop not other starting elem of seq

//Can be improved: can make only those elements which are starting elem of a sequence can be made to go to inner while making TC - O(n + 2*n)

void longestConseqOptHis(vector<int>& arr){
    int maxLen = 0;
    int len;
    unordered_set<int> st;
    for(int i=0;i<arr.size();i++){
        st.insert(arr[i]);
    }

    for(auto v:st){
        if(st.find(v-1) == st.end()){
            len=1;
            int x=v;
            while(st.find(x+1) != st.end()){
                x=x+1;
                len++;
            }
            maxLen = max(maxLen, len);
        }
    }
    cout<<maxLen;
}
//TC - O(n+ 2*n), Sc - O(m), m-uniq elems of arrr


int main(){
    //1.
    // vector<int> arr = {10, 22, 12, 3, 0, 6};
    // auto v=LeadersInArr(arr);
    // for(auto i:v) cout<<i<<" ";

    //2.
    vector<int> arr = {100, 102, 100, 101, 101,  2, 2, 1, 1, 1, 2, 3, 3, 4};
    longestConseqOptHis(arr);

    return 0;
}
