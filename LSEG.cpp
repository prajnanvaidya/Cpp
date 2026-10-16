#include<bits/stdc++.h>
#include<span>
using namespace std;


/*
Problem Statement:

A person goes to the gym on certain days of the week. You are given a
vector of strings representing the days on which the person visited the
gym, in chronological order.

The days are given using:

    Mon, Tue, Wed, Thu, Fri, Sat, Sun

The vector represents visits that occurred over one or more weeks.

Find and return the total number of weeks covered by these visits.

Rules:

1. The first visit belongs to week 1.

2. If the current visit's day comes before or is the same as the previous
   visit's day in the weekly order, it means the visit has moved into a
   new week.

   For example:

       Mon -> Tue -> Fri
       All belong to the same week.

       Fri -> Mon
       This starts a new week.

3. If the day stays ahead of the previous day, the visit is still within
   the same week.

4. Return the minimum number of weeks required to contain all the given
   visits.

Example 1:

    Input:
        ["Mon", "Tue", "Fri"]

    Explanation:
        Mon -> Tue -> Fri

        No week transition occurs.

    Answer:
        1


Example 2:

    Input:
        ["Mon", "Fri", "Tue", "Sun", "Mon"]

    Explanation:

        Week 1: Mon -> Fri
        Week 2: Tue -> Sun
        Week 3: Mon

    Answer:
        3


Function:

    int gymMem(vector<string>& visits);

Expected Complexity:

    Time Complexity:  O(n)
    Space Complexity: O(1)
*/

int gymmemberShip(vector<string>& visits){
    int N=0;
    vector<string> days={"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};
    unordered_map<string, int> mpp={ {"Mon", 1}, {"Tue", 2}, {"Wed", 3}, {"Thu", 4}, {"Fri", 5}, {"Sat", 6}, {"Sun", 7} };

    int cnt=0;
    for(int i=0;i<visits.size();i++){
        days.erase(days.begin(), days.begin() + mpp[visits[i]] - cnt);
        if(i==(visits.size()-1) || (i<visits.size() && !days.empty() && mpp[visits[i+1]]<mpp[days[0]]) || days.empty()){
            N++;
            days = {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};
            cnt=0;
        } 
        else{
            cnt++;
        }
    }
    return N;
}



// 0    1    2
// Mon, Mon, Mon

// days={"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"}
// loop: i=0, i<3
//     days - {"Tue", "Wed", "Thu", "Fri", "Sat", "Sun"}
//     N=1
//     days - {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"}

// loop: i=1, i<3
//     days - {"Tue", "Wed", "Thu", "Fri", "Sat", "Sun"}
//     N=2
//     days - {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"}

// loop: i=2, i<3
//     days - {"Tue", "Wed", "Thu", "Fri", "Sat", "Sun"}
//     N=3

// 0    1    2    3    4
// Mon, Tue, Mon, Sun, Tue
// N=0
// days - {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"}
// mpp - { {"Mon", 1}, {"Tue", 2}, {"Wed", 3}, {"Thu", 4}, {"Fri", 5}, {"Sat", 6}, {"Sun", 6} }

// loop: i=0, i<5
//     days - {"Tue", "Wed", "Thu", "Fri", "Sat", "Sun"}

// loop: i=1, i<5
//     days - {"Wed", "Thu", "Fri", "Sat", "Sun"}
//     N=1
// loop: i=2, i<5
//     days - {"Tue", "Wed", "Thu", "Fri", "Sat", "Sun"}
// loop: i=3, i<5
//     days - {}
//     N=2
//     days - {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"}
// loop: i=4, i<5
//     days - { "Wed", "Thu", "Fri", "Sat", "Sun"}
//     N=3

// 0    1    2    3    4
// Mon, Tue, Mon, Mon, Tue
// N=0
// days - {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"}
// mpp - { {"Mon", 1}, {"Tue", 2}, {"Wed", 3}, {"Thu", 4}, {"Fri", 5}, {"Sat", 6}, {"Sun", 7} }

// loop: i=0, i<5
//     days - {"Tue", "Wed", "Thu", "Fri", "Sat", "Sun"}

// loop: i=1, i<5
//     days - {"Wed", "Thu", "Fri", "Sat", "Sun"}
//     N=1

// loop:i=2, i<5
//     days - {"Tue", "Wed", "Thu", "Fri", "Sat", "Sun"}
//     N=2

// loop: i=3, i<5
//     days - {"Tue", "Wed", "Thu", "Fri", "Sat", "Sun"}
    
// loop: i=4, i<5
//     days - {"Wed", "Thu", "Fri", "Sat", "Sun"}
//     N=3


int gymMem(vector<string>& visits){
    int current, last, N=1;
    unordered_map<string, int> mpp={{"Mon", 1}, {"Tue", 2}, {"Wed", 3}, {"Thu", 4}, {"Fri", 5}, {"Sat", 6}, {"Sun", 7}};

    last=mpp[visits[0]];
    for(int i=1;i<visits.size();i++){
        current = mpp[visits[i]];

        if(current<=last)
            N++;
        last=current;
    }
    return N;
}
//TC - O(n), SC - O(1)



/*
Problem Statement:

You are given a vector of integers representing the bottom-most layer
of a pyramid.

Construct the pyramid using the following rules:

1. Each upper layer contains exactly 2 fewer elements than the layer
   immediately below it.

2. For every pair of adjacent elements in the current lower layer,
   the corresponding element in the upper layer is calculated as:

       upper[i] = max(lower[i], lower[i + 1])

3. Continue constructing the pyramid until the top-most layer contains
   exactly one element.

Examples of layer sizes:

   Odd-sized input:
       5 -> 3 -> 1
       7 -> 5 -> 3 -> 1
       9 -> 7 -> 5 -> 3 -> 1

   Even-sized input:
       2 -> 1
       4 -> 2 -> 1
       6 -> 4 -> 2 -> 1
       8 -> 6 -> 4 -> 2 -> 1

4. Consider all elements from all layers, including the original
   bottom-most layer.

5. Find and return the element that occurs the maximum number of times
   across all layers.

6. If multiple elements have the same maximum frequency, any one of
   them may be returned.

Example:

   Input:
       [2, 5, 1, 4, 3]

   Pyramid:

       2   5   1   4   3
        \ / \ / \ /
         5   5   4
          \ / \ /
           5

   Frequencies across all layers:

       2 -> 1
       5 -> 4
       1 -> 1
       4 -> 2
       3 -> 1

   Therefore, the answer is:
       5

Function:

   int PyramidNon(vector<int>& arr);

Constraints:
   - The input vector may contain positive, negative, or zero values.
   - The vector can have any size >= 1.
*/



int PyramidNon(vector<int>& arr){
    if(arr.size()<1)
        return -1;

    unordered_map<int, int> freq;
    for(auto v:arr)
        freq[v]++;

    int i, j;
    int maxi;
    vector<int> temp;

    int n=(arr.size()/2);
    for(int k=0;k<n;k++){
        i=0;
        j=1;

        do{
            maxi = max(arr[i], arr[j]);
            freq[maxi]++;
            temp.push_back(maxi);
            i++;
            j++;
        }while(i<arr.size()-2);

        arr.swap(temp);
        temp.clear();
    }
    for(auto v:freq)
        cout<<v.first<<":"<<v.second<<", ";
    cout<<endl;

    int maxed = 0;
    int val=arr[0];
    for(auto v:freq)
        if(v.second>maxed){
            maxed=v.second;
            val=v.first;
        }
        
    return val;
}
//TC - O(n^2), SC - O(n)

// 0 1 2 3 4
// 4 2 3 6 8

// freq - 
// i, j
// sp, maxi
// temp

// loop: k=0, k<3
//     i=0
//     j=1
//     else 
//         sp=3
//     loop: i=0,j=1, i<3
//         maxi=4
//         freq- 4:1
//         temp - 4
//         i=1, j=2
//     loop: i=1, j=2, i<3
//         maxi=3
//         freq - 4:1, 3:1
//         temp - 4, 3
//         i=2, j=3
//     loop: i=2, j=3, i<3
//         maxi=6
//         freq - 4:1, 3:1, 6:1
//         temp - 4,3,6
//     arr - 4,3,6
//     temp - 

// 0 1 2 
// 4 3 6
// loop: k=1, k<3
//     i=0
//     j=1
//     loop: i=0, j=1, i<1
//         maxi=4
//         freq - 4:2, 3:1, 6:1
//         temp - 4
//         i=1, j=2
    
// loop: k=2, k<3






int main(){
    vector<string> visits={"Mon", "Tue", "Mon", "Sun", "Tue"};
    int n=gymMem(visits);
    // cout<<n;

    cout<<endl;
    vector<int> v={5,4,4,4,5};
    cout<<PyramidNon(v);
    return 0;
}

