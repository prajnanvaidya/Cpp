#include<bits/stdc++.h>
using namespace std;

//Rearrange arr elements by sigen
// - Given an arr that contains equal +ve, -ve elements
// Constraint 
// - For ex a arr has n elem then n/2 - +ve, n/2 - -ve
// - n is always a even number
// - Should rearrange such that +ve, -ve, +ve, -ve,... (should be alternate +ve and -ve with start from +ve)
// - The original order should be maintained

// Ex:
// 3, 1, -2, -5, 2, -4
// result: 3, -2, 1, -5, 2, -4

//Brute - loop through as +ve comes put to temp1 vector and as -ve comes put to temp2 vector and later loop through arr length and put once temp1 and later temp2
void Rearrange(vector<int>& arr){
    vector<int> positive;
    vector<int> negative;

    for(auto v:arr){
        if(v<0){
            negative.push_back(v);
        }
        else{
            positive.push_back(v);
        }
    }

    int k=0, l=0;
    for(int i=0;i<arr.size();i++){
        if((i%2) == 0){
            arr[i]=positive[k];
            k++;
        }
        else{
            arr[i]=negative[l];
            l++;
        }
    }
}
//TC - O(n), SC - O(n)

void RarrangeClean(vector<int>& arr){  
    vector<int> positive;
    vector<int> negative;
    for(auto v:arr){
        if(v<0)
            negative.push_back(v);
        else
            positive.push_back(v);
    }  
    int id_p=0, id_n=0;
    int i=0;
    while(id_p<positive.size() && id_n<negative.size()){
        arr[i++]=positive[id_p++];
        arr[i++]=negative[id_n++];
    }
}

void Rearrangebet(vector<int>& arr){
    unordered_map<int, int> mpp;
    int p=0, n=1;
    for(auto v:arr){
        if(v<0){
            mpp[v]=n;
            n+=2;
        }
        else{
            mpp[v]=p;
            p+=2;
        }
    }

    for(auto v:mpp){
        arr[v.second]=v.first;
    }
}
//Tc - O(n), SC - O(n)
//Not recomended as it cannot handle duplicate value

void RearrangeBet2(vector<int>& arr){
    int p=0, n=1;
    vector<int> temp=arr;
    for(int i=0;i<arr.size();i++){
        if(temp[i]<0){
            arr[n]=temp[i];
            n+=2;
        }
        else{
            arr[p]=temp[i];
            p+=2;
        }
    }
}
//Tc - O(n), SC - O(n)


void RearrangeOpt(vector<int>& arr){
    int p=0, n=1;
    int temp;
    int cnt=0;
    int sz=arr.size();
    for(int i=0;i<arr.size();i=i+1+cnt){
        if(arr[i]<0){
            if(p>i){
                temp=arr[i];
                arr.insert(arr.begin()+i+1, arr[p]);
                cnt++;
                arr[p]=arr[i];
                p+=2;
            }
            else{
                arr[p]=arr[i];
                p+=2;
                if(cnt>0)
                    cnt--;
            }
        } 
        else{
            if(n>i){
                temp = arr[n];
                arr.insert(arr.begin()+i+1, arr[n]);
                cnt++;
            }
            else{
                arr[n]=arr[i];
                n+=2;
                if(cnt>0)
                    cnt--;
            }
        }
    }
    arr.resize(sz);
}                      

//Same problem but its not guaranteed that n/2 is +ve and n/2 is negative and also n is even
//The remaining should be put at the end without disrupting the order

void Rearrange2Brut(vector<int>& arr){
    vector<int> positive;
    vector<int> negative;
    int no_p=0, no_n=0;
    int id_p=0, id_n=0;

    for(auto v:arr){
        if(v<0){
            negative.push_back(v);
            no_n++;
        }
        else{
            positive.push_back(v);
            no_p++;
        }
    }
    int i;
    for(i=0;i<arr.size();i++){
        if(i%2==0 && no_p>0){
            arr[i]=positive[id_p++];
            no_p--;
        }
        else if(i%2!=0 && no_n>0){
            arr[i]=negative[id_n++];
            no_n--;
        }
    }
    while(no_p>0 && i<arr.size()){
        arr[i++]=positive[id_p++];
        no_p--;
    }

    while(no_n>0 && i<arr.size()){
        arr[i++]=negative[id_n++];
        no_n--;
    }

}
//TC - O(n+n) - O(n), SC - O(n)


void Rearrange2BrutClean(vector<int>& arr){
    vector<int> positive;
    vector<int> negative;

    for(auto v:arr){
        if(v<0)
            negative.push_back(v);
        else
            positive.push_back(v);
    }

    int id_p=0, id_n=0, i=0;
    while(id_p<positive.size() && id_n<negative.size()){
        arr[i++]=positive[id_p++];
        arr[i++]=negative[id_n++];
    }

    while(id_p<positive.size())
        arr[i++]=positive[id_p++];
    
    while(id_n<negative.size())
        arr[i++]=negative[id_n++];

}


//Using a single temp rather then separate positive and negative vectors
void Rearrange2bet(vector<int>& arr){
    int no_n=0, no_p=0;
    int n=1, p=0;
    vector<int> temp=arr;

    for(auto v:arr){
        if(v<0)
            no_n++;
        else
            no_p++;
    }
    int i;
    for(i=0;i<arr.size();i++){
        if(temp[i]<0 && no_p>0 && n<arr.size()){
            arr[n]=temp[i];
            n+=2;
            no_n--;
        }
        else if(temp[i]>=0 && no_n>0 && p<arr.size()){
            arr[p]=temp[i];
            p+=2;
            no_p--;
        }
    }
    while(no_n>0 && i<arr.size()){
        arr[p]=temp[i];
        no_n--;
        p++;
        i++;
    }

    while(no_p>0 && i<arr.size()){
        arr[n]=temp[i];
        no_p--;
             n++;
        i++;
    }
}
//Tc - O(n+n), SC - O(n)
//This fails to do job as it here p and n even though separate pointers they go to positions alternatively only if extra positives or negatives handling them becomes difficult as linear movement is not possible

//Here i maintain 2 pointers but they wont move alternatively rather linearly 
void Rearrange2betCorrect(vector<int>& arr){
    vector<int> temp = arr;
    int p=0, n=0, i=0;

    while( (p < arr.size() || n < arr.size()) && i<arr.size()){
        while(p<arr.size() && temp[p]<0)
            p++;
        while(n<arr.size() && temp[n]>=0)
            n++;
        if(p<arr.size()){
            arr[i++]=temp[p];
            p++;
        }
        if(n<arr.size() && i<arr.size()){
            arr[i++]=temp[n];
            n++;
        }
    }
}

//  0 1  2  3  4 5  6 7  8  9 10
// -4 7 -2 -1 -8 5 -3 6 -9 10 -2

// n=0, p=0, i=0
// loop: i=0,n=0,p=0, i<11, n<11, p<11
//     loop: p=0, p<11, temp[0]=-4<0
//         p=1
//     loop: p<11, temp[1]=7

//     loop: n=0, n<11, temp[0]=-4
//     if: p=1, p<11
//         arr - 7
//         i=1, p=2
//     if: n=0, i=1, n<11, i<11
//         arr - 7, -4
//         n=1, i=2

// loop: i=2, n=1, p=2, i<11, p<11, n<11
//     loop: p=2, p<11, temp[2]=-2<0
//         p=3
//     loop: p<11, temp[3]=-1<0
//         p=4
//     loop: p<11, temp[4]=-8<0
//         p=5
//     loop: p<11, temp[5]=5

//     loop: n=1, n<11, temp[1]=7>0
//         n=2
//     loop: n<11, temp[2]=-2

//     if: p=5, p<11
//         arr- 7, -4, 5
//         i=3
//         p=6
//     if: n=2, n<11
//         arr- 7, -4, 5, -2
//         n=3
//         i=4
    
// loop: p=6, n=3, i=4, i<11, n<11, p<11
//     loop: p=6, p<11, temp[6]=-3<0
//         p=7
//     loop: p<11, temp[7]=6

//     loop: n=3, n<11, temp[3]=-1

//     if: p=7, p<11
//         arr - 7, -4, 5, -2, 6
//         p=8
//         i=5
//     if: n=3, n<11, i<11
//         arr - 7, -4, 5, -2, 6, -1
//         n=4
//         i=6
    
// loop: p=8, n=4, i=6, p<11, n,11, i<11
//     loop: p=8, p<11, temp[8]=-9<0
//         p=9
//     loop: p<11, temp[9]=10

//     loop: n=4, n<11, temp[4]=-8

//     if: p=9, p<11
//         arr - 7, -4, 5, -2, 6, -1, 10
//         i=7
//         p=10
//     if: n=4, i=7, n<11,i<11
//         arr - 7, -4, 5, -2, 6, -1, 10, -8
//         n=5
//         i=8
    
// loop: p=10, n=5, i=8, p<11, n<11, i<11
//     loop: p=10, p<11, temp[10]=-2<0
//         p=11
//     loop: p=11

//     loop: n=5, n<11, temp[5]=5>0
//         n=6
//     loop: n<11, temp[6]=-3

//     if: p=11

//     if: n=6, n<11, i=8, i<<11
//         arr - 7, -4, 5, -2, 6, -1, 10, -8, -3
//         n=7
//         i=9
    
// loop: p=11, n=7, i=9, p=11, n<11, i<11
//     loop: p=11

//     loop: n=7, n<11, temp[7]=6>0
//         n=8
        
//     if: p=11
//     if: n=8, n<11, i=9, i<11
//         arr - 7, -4, 5, -2, 6, -1, 10, -8, -3, -9
//         n=9
//         i=10

// loop: p=11, n=9, i=10, n<11, i<11
//     loop: p=11
//     loop: n=9, n<11, temp[9]=10>0
//         n=10
//     loop: n=10, n<11, temp[10]=-2
//     if: p=11
//     if: n=10, n<11, i=10, i<11
//         arr - 7, -4, 5, -2, 6, -1, 10, -8, -3, -9, -2
//         n=11
//         i=11


void Rearrange2His(vector<int>& arr){
    vector<int> pos;
    vector<int> neg;

    for(auto v:arr){
        if(v<0)
            neg.push_back(v);
        else
            pos.push_back(v);
    }

    if(pos.size()<neg.size()){
        for(int i=0;i<pos.size();i++){
            arr[2*i] = pos[i];
            arr[2*i+1] = neg[i];
        }
        int index = pos.size()*2; //starting index of arr remaining to fill with leftover
        for(int i=pos.size();i<neg.size();i++){
            arr[index] = neg[i];
            index++;
        }
    }
    else{
        for(int i=0;i<neg.size();i++){
            arr[2*i] = pos[i];
            arr[2*i+1] = neg[i];
        }
        int index = neg.size()*2;
        for(int i=neg.size();i<pos.size();i++){
            arr[index]=neg[i];
            index++;
        }
    }
}
//TC - O(n + (n/2)) in best case as no of +ves and -ves are same , In worst case - O(n + n) =O(n), SC - O(n)


int main(){
    vector<int> v={-4, 7, -2, -1, -8, 5, -3, 6, -9, 10, -2};
    Rearrange2His(v);
    for(auto i:v)
        cout<<i<<" ";

    return 0;
}