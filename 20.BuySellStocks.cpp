#include<bits/stdc++.h>
using namespace std;

//Best time to buy and sell stocks
//For ex:
// given arr: 7 1 5 3 6 4
// day      : 1 2 3 4 5 6
// When do you buy and sell stocks to make maximum profit
// Here stock is bought on 2nd day and sold on 5th day i.e profit=6-1=5

// note:1. U should sell stock once after the bought date cannot go to previous dates and if sold on same day u earn 0 profit
// 2. U can only buy and sell stock once

//Sol: if u consider any date to sell it then from previous u choose the date when stock price is minimum i.e
// if sold on ith day then u buy it for a day where price is min from 0 to i-1

int BuySell(vector<int> a, int n){
    int minPrice=INT_MAX, profit=INT_MIN;
    for(int i=0;i<n;i++){
        for(int j=0;j<i;j++){
            if(minPrice>a[j])
                minPrice=a[j];
        }
        if(profit<(a[i]-minPrice))
            profit=(a[i]-minPrice);
    }
    return profit;
}
//TC: near to O(n^2), SC:O(1)
//Dry run:
// minPrice=999, profit=-999
// loop: i=0
//     loop: j=0;j<0 -stop
//     if: profit<7-999
//         profit=-992

// loop: i=1
//     loop: j=0
//         if: minPrice>7
//             minPrice=7
//     if: profit<1-7
//         profit=-6

// loop: i=2
//     loop: j=0
//         if: minPrice=7
//     loop: j=1
//         if: minPrice>1
//             minPrice=1
//     if: profit<5-1
//         profit=4

// loop: i=3
//     loop: j=0
//         if: minPrice<7
//     loop: j=1
//         if: minPrice=1
//     loop: j=2
//         if: minPrice<5
//     if: profit>2

// loop: i=4
//     loop: j=0
//         if: minPrice<7
//     loop: j=1
//         if: minPrice=1
//     loop: j=2
//         if: minPrice<5
//     loop: j=3
//         if: minPrice<3
//     if: profit<6-1=5
//         profit=5

// loop: i=5
//     loop: j=0
//         if: minPrice<7
//     loop: j=1
//         if: minPrice=1
//     .
//     .
//     if: profit>4-1=3
// profit=5

//Here we could see the redundancy as minPrice is again for each i checked from the 0 but we could reduce and check only the index i-1 
int BuySellBetter(vector<int> a, int n){
    int profit=INT_MIN, minPrice=INT_MAX;
    for(int i=0;i<n;i++){
        if((i-1)>0 && minPrice>a[i-1])
            minPrice=a[i-1];
        if(profit<(a[i]-minPrice))
            profit=(a[i]-minPrice);
    }
    return profit;

int BuySellHis(vector<int> a, int n){
    int mini=a[0], profit=0, cost;
    for(int i=1;i<n;i++){
        cost=a[i]-mini;
        profit=max(profit, cost);
        mini=min(mini, a[i]);
    }
    return profit;
}
//TC - O(n), SC - O(1)

//If u want to return day at which the stocks are bought and sold
pair<int, pair<int, int>> BuySellRet(vector<int> arr){
    int profit=0, cost;
    int bought=0, sold=0;

    for(int i=1;i<arr.size();i++){
        cost = arr[i]-arr[bought];

        if(cost > profit){
            profit=cost;
            sold=i;
        }
        if(arr[bought] > arr[i]){
            bought=i;
        }
    }
    return {profit, {bought, sold}};
}


int main(){
    int n, elem;
    cin>>n;
    vector<int> arr;
    for(int i=0;i<n;i++){
        cin>>elem;
        arr.push_back(elem);
    }
    int profit=BuySellHis(arr, n);
    cout<<profit<<endl;
}