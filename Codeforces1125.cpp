#include<bits/stdc++.h>

using namespace std;

void InSearchOfConvienience(int x, int y, int R){
    int flag=0;
    for(int i=-35;i<35;i++){
        for(int j=-35;j<35;j++){
            int res = ((x-i)*(x-i) + (y-j)*(y-j));
            if(  res == R*R ){
                cout<<i<<" "<<j<<endl;
                flag=1;
            }
        }
        if(flag)
            break;
    }
}
void INSearchConvinienceOpt(){
    int t, x, y, R;
    cin>>t;
    for(int i=0;i<t;i++){
        cin>>x>>y>>R;
        cout<<x+R<<" "<<y<<endl;
    }
}

void DidNotGoToPrint(int n, string s){
    stack<int> sk;
    int k=0;
    vector<int> arr;

    for(int i=0;i<n;i++){
        if(s[i] == '1'){
            sk.push(i+1);
        }
        else if(s[i] == '2' && !sk.empty()){
            sk.pop();
            arr.push_back(i+1);
        }
    }
    k=sk.size()+arr.size();
    cout<<k<<endl;

    if(k!=0){
        while(!sk.empty()){
            arr.push_back(sk.top());
            sk.pop();
        }

        sort(arr.begin(), arr.end());
        for(auto v:arr) cout<<v<<" ";
        cout<<endl;
    }

}
//Tc - o(n + n + nlogn + n){1st for looping upto n, 2nd for looping through stack, 3rd nlogn for sorting arr, 4th n to print arr}
//TC - O(nlogn)
//Sc - O(n + n) { for stack and arr}
//Sc - O(n)

//Can make it TC - O(n)

void DidNotGoToPrintOpt(int n, string s){
    stack<int> sk;
    int cnt=0;
    vector<bool> printDoc(n+1, false);

    for(int i=0;i<n;i++){
        int doc = i+1;
        if(s[i]=='1'){
            sk.push(doc);
        }
        else if(s[i] == '2'){
            if(!sk.empty()){
                printDoc[sk.top()]=true;
                sk.pop();
            }
            else{
                printDoc[doc]=true;
            }
        }
        else{
            printDoc[doc]=true;
        }
    }

    for(int i=1;i<n+1;i++){
        if(!printDoc[i])
            cnt++;
    }
    cout<<cnt<<endl;

    if(cnt!=0)
        for(int i=1;i<n+1;i++){
            if(!printDoc[i])
                cout<<i+1<<" ";
        }
    cout<<endl;
}


void unrequitedLove(int n, vector<int>& arr){
    int st = n-4;
    map<vector<int>, int> mpp;
    
    vector<int> triad;
    int i=0, aud_love=0;
    int j=i;
    while(i<st){
        triad.push_back(j);
        if(triad.size() != 3){
            aud_love+=arr[j];
            j+=2;
        }
        else{
            aud_love -= arr[j];
            mpp[triad] = aud_love;
            aud_love = 0;
            triad.clear();
            i++;
            j=i;
        }
    }

    int ans=0;
    for(map<vector<int>, int>::iterator v=mpp.begin();v!=mpp.end();v++){
        auto i = next(v);
        while(i!=mpp.end()){
            if(i->second == v->second){

                int flag=0;
                for(auto m:v->first){
                    for(auto n:i->first){
                        if(m == n) flag = 1;
                    }
                }
                if(!flag) ans++;
            }
            i++;
        }
    }
    cout<<ans<<endl;
}
//Tc - O( n-4 + (n-4)^2) but as per constraint n max val=2*10^5, so it gives error as TLE as n^2 is 10^10 
//TLE cuz ques says 2 sec time limit for each test case but a test case having n=10^5 could potentially go upto 10^10 that means cpp solves 10^9/sec so 10*10^9 so it takes 10seconds !!Error!!
//SC - O(n-4)

//We can reduce it by decreasing time complexity to O(n)
//For that we use 2 vectors: 1.love - whose index: represents starting index of triad and value: audience love val of formula
// 2. freq: index: represents audience love, val: repr no of triads with that love
// as index cannot be negative but audience love can be so we go with consiodering below constraint in quest:
// ai in arr min: 10^-4 and max: 10^4 so audience_love_max = -10^4-10^4-10^4 = -3*10^4, audience_love_max = 10^4 + 10^4 - (-10^4) = 3*10^4

// So for any audience love index in freq should be aud_love + 30000, as first 30k represents negative aud_love next 30k represents +ve aud_love

void unrequitedLoveOpt(int n, vector<int>& arr){
    int m=n-4;
    vector<int> love(m, 0);
    vector<int> freq(60001, 0);

    long long ans=0;
    for(int i=0;i<m;i++){
        love[i] = arr[i] + arr[i+2] - arr[i+4];
        int idx = love[i]+30000;

        ans += freq[idx]; //here before updating the freq we would add those many triads with same aud_love to ans as they gonna pair with current triad, here every pair is considered not checking do they have same key or not

        freq[idx]++;
    }

    //Removing pair overlaping triad from ans
    for(int i=0;i<m;i++){
        if(i+2 < m && love[i] == love[i+2]) ans--;
        if(i+4 < m && love[i] == love[i+4]) ans--;
    }
    cout<<ans<<endl;

}

int main(){ 

    int t;
    cin>>t;

    int n;
    vector<int> arr;
    for(int i=0;i<t;i++){
        cin>>n;
        int elem;
        for(int i=0;i<n;i++){
            cin>>elem;
            arr.push_back(elem);
        }
        unrequitedLoveOpt(n, arr);
        arr.clear();
    }

    return 0;
}