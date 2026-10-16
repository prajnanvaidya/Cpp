
#include<bits/stdc++.h>

using namespace std;

auto binary(int n){
    vector<int> res;
    while(n!=0){
        if(n%2==0)
            res.push_back(0);
        else
            res.push_back(1);

        n/=2;
    }
    reverse(res.begin(), res.end());
    return res;
}
//TC - O(logn), SC - O(logn)

int decimal(vector<int> bn){
    int res=0;
    for(int i=bn.size()-1;i>=0;i--){
        if(bn[i]==1)
            res+=pow(2, (bn.size()-i-1));
    }
    return res;
}
//TC - O(len(binary)), SC - O(1)

int main(){

    int n, elem;
    vector<int> bn;
    cin>>n;

    for(int i=0;i<n;i++){
        cin>>elem;
        bn.push_back(elem);
    }

    auto dc = decimal(bn);
    cout<<dc;

    return 0;
}