#include<bits/stdc++.h>

using namespace std;

//Greedy
// We have a parent has n child, every children has greed factor shown as value in arr greed whose index represents respective child, parent has m cookies and cookie arr represents size of each cookie 

// A child will be satisfied if gave a cookie >= greed factor 
// Parent can assign 1 cookie to 1 children 
// task is to assign maximum no of cookies to children

// Ex: greed = {1, 5, 3, 3, 4}, cookie = {4, 2, 1, 2, 1, 3}

// {1, 3, 3, 4, 5}   {1, 1, 2, 2, 3, 4}
// 1 = 1
// 3 = 3
// 3 = 4

int AssignCookies(vector<int>& greed, vector<int>& cookie){
    sort(greed.begin(), greed.end());
    sort(cookie.begin(), cookie.end());

    int cok_ass=-1;
    for(int i=0;i<cookie.size();i++){
        for(int j=cok_ass+1;j<greed.size();j++){
            if(greed[j] > cookie[i]){
                break;
            }
            else{
                cok_ass++;
                break;
            }
        }
    }
    return cok_ass+1;
}
//TC - O(nlogn + mlogm + m) where m-cookie size, n - greed size


//  0  1  2  3  4     0  1  2  3  4  5
// {1, 3, 3, 4, 5}   {1, 1, 2, 2, 3, 4}
int assignCookiesBet(vector<int>& greed, vector<int>& cookie){
    sort(greed.begin(), greed.end());
    sort(cookie.begin(), cookie.end());

    int n = greed.size();
    int m = cookie.size();
    int i=0, j=0;
    int cok_ass=0;
    while(i<n && j<m){
        if(cookie[j] >= greed[i]){
            cok_ass++;
            i++;
            j++;
        }
        else{
            j++;
        }
    }
    return cok_ass;
}
//TC - O(nlogn + mlogm + min(m,n)), SC - O(1)

//-----------------------------------------------------------------------------------------------------------------------------

//Lemonade Change

//U have a lemonade stand: need to serve lemonade to customers which costs 5 per lemonade,
// Given a arr which represents the money ith customer will give inorder to buy 1 lemonade, the customer will buy only 1 lemonade and each customer can come up with amount 5, 10, 20
// - When customer come up with 5 u should give nothing back
// - When customer come up with 10 u should give 5 back 
// - When customer come up with 20 u should give three 5 back or one 10 and 1 5 back

// U should tell how can u satisfy all customers or not, by giving the lemonade only if u have change

bool LemonadeChange(vector<int>& cust){
    int f=0, t=0, tw=0;
    for(int i=0;i<cust.size();i++){
        if(cust[i] == 5){
            f++;
        }
        else if(cust[i]==10){
            if(f>=1){
                t++;
                f--;
            }
            else return false;
        }
        else{
            if((f>=1 && t>=1) || (f>=3)){
                if(t>=1){
                    f--;
                    t--;
                    tw++;
                }
                else{
                    f-=3;
                    tw++;
                }
            }
            else return false;
        }
    }
    return true;
}
// TC- O(n), SC - O(1) {tw var is not needed in above f}

//-----------------------------------------------------------------------------------------------------------------------------

//Shortest Job First
// Its a sheduling policy that selects the waiting process with smallest execution time to execute next
// Given a arr which represent execution time of ith process
// bt = [4, 3, 7, 1, 2]
// U need to return average waiting time 
// avg waiting time = summ of all Execution start time of each process / no of processes

// sort arr
// For each process find execution start time, sum up all execution starting time for all process 
// - A process strting time = t
// - next proxcess start time = t + input[i]

int SJF(vector<int>& procss){
    if(procss.size() == 0) return 0;
    sort(procss.begin(), procss.end());

    int avg=0;
    int t=0;
    for(int i=0;i<procss.size();i++){
        avg += t;
        t += procss[i];
    }
    avg = avg/procss.size();

    return avg;
}
//TC - O(nlogn + n), SC - o(1)

//-----------------------------------------------------------------------------------------------------------------------------

//Jump Game
// Given an arr: Each elem val signifies the maximum u can jump, u need to return bool: can u reach last elem if u start from first elem 
// Ex; 
//  0  1  2  3  4
// {2, 3, 1, 0, 4} possible comb: 2 -> 3 -> 4

//  0  1  2  3  4
// {3, 2, 1, 0, 4} not possible as every comb make u reach idx 3; 3->0, 3->2->0, 3->2->1->0, 3->1->0

//  0  1  2  3  4  5  6  7
// {1, 2, 3, 1, 1, 0, 2, 5} not possible as every comb make u reach idx 5, 1->2->3->0, 1->2->3->1->1->0, 1->2->1->1->0

// Trying to apply greedy thinking i will jump the max val at a index as i want to reach end fast: will not work 
// Ex: {1, 2, 3, 1, 0, 1, 2, 5} check 1->2->1->0 but 1->2->3->1->2->5

// so if u reach 0 then check with all other combinations possible if neither of them cannot cross u 0 then u are done bro, its false 
// If any one of them able to pass then there is a hope still left
// -> edge: If arr has no 0 then its surely true

bool jumpGame(vector<int>& jumps){
    int n = jumps.size();
    int maxIndex = 0;

    int i=0;
    while(i<n){
        if(i > maxIndex) return false;
        maxIndex = max(maxIndex, i+jumps[i]);

        if(maxIndex >= n-1) break;
        i++;
    }

    return true;
}
//TC - O(n), SC - O(1)

//-----------------------------------------------------------------------------------------------------------------------------

// Jump Game - 2
// Given an arr of jumps u start from begining, and jump i+val of ith index at max same as previous but here u should return min steps taken to reach end of arr
// Each step considered as 1 step

//Ex:
// {2, 3, 1, 1, 4} 
// min Steps: 2->3->4 = 3

// Brut sol:
// As once u start the jump the no of possible jumps goes from 1 to arr[i] and there is no limit for arr[i] So writing nested loop is not possible, So write a recursive code at ech depth it would make arr[i] no of calls taking TC - O(max(arr)^n) at worst case

int jumpGame2(vector<int>& jumps, int idx, int stepsTaken){
    if(idx >= jumps.size()-1) return stepsTaken;

    vector<int> possibleStepMin(jumps[idx]+1, INT_MAX);

    for(int i=1;i<=jumps[idx];i++){
        possibleStepMin[i] = jumpGame2(jumps, idx+i, stepsTaken+1);
    }
    stepsTaken = *(min_element(possibleStepMin.begin(), possibleStepMin.end()));
    return stepsTaken;
}
//Tc - O(max(jumps)^n), SC - O(n + max(jumps))

//As we only need minimum no need to maintain arr of every possible answer
int jumpGame2RecBet(vector<int>& jumps, int idx, int stepsTaken){
    if(idx >= jumps.size()-1) return stepsTaken;

    int mini = jumps.size()-1;

    for(int i=1;i<=jumps[idx];i++){
        mini = min(mini, jumpGame2(jumps, idx+i, stepsTaken+1));
    }
    return mini;
}
//TC - O(max(jumps)^n) ~ O(n^n), SC - O(n){stack space}

// Can we use DP, memo
// i.e Top down approach use dp arr to store already found answer
// first of all is there a overlaping subproblem here
// yes there is and u should maintain a dp arr for no of min steps remaining fro that index

int jumpGame2Memo(vector<int>& jumps, vector<int>& dp, int idx, int stepsTaken){
    if(idx >= jumps.size()-1){
        return stepsTaken;
    }
    
    if(dp[idx] != -1){
        if(dp[idx] == INT_MAX) return INT_MAX;
        return stepsTaken+dp[idx];
    }
    int mini = INT_MAX;
    for(int i=1;i<=jumps[idx];i++){
        if(idx+i < jumps.size()) mini = min(mini, jumpGame2Memo(jumps, dp, idx+i, stepsTaken+1));
    }
    if(mini == INT_MAX) dp[idx] = INT_MAX;
    dp[idx] = mini - stepsTaken;
    
    return mini;
}
//TC - O(n^2) {only depth until last elem}, SC - O(n^2 + n){stack space + dp}

// Can we do TAbularisation: Bottom Up approach using this concept of dp arr where we store min steps from that index to reach end i think we cannot go bottom up as dp[0] itself our required answer and if indeed we have a base condition then that is dp[n-1] = 0 and dp[n-2] = 1 if jumps[n-1]>0 

// His Memo: storing dp[idx][stepsTaken]
int jumpGame2HisMemo(vector<int>& jumps, vector<vector<int>>& dp, int idx, int stepsTaken){
    if(idx >= jumps.size()-1){
        return stepsTaken;
    }
    if(dp[idx][stepsTaken] != -1){
        return dp[idx][stepsTaken];
    }
    int mini = jumps.size()-1;
    for(int i=1;i<=jumps[idx];i++){
        mini = min(mini, jumpGame2HisMemo(jumps, dp, idx+i, stepsTaken+1));
    }
    dp[idx][stepsTaken] = mini;
    return dp[idx][stepsTaken];
}
//TC - O(n^2), SC - O(2*n^2)

// But we want greedy approach 
// We maintain a range with 2 ptrs l and r and var jumps, it says with jumps no of jump we can go to elems between l and r where l is least index elem we can reach and r is the greatest index elem we can reach

int jumpGame2Greedy(vector<int>& arr){
    int n=arr.size();
    int jumps = 0;
    int l=0, r=0;

    while(r<(n-1)){
        int farthest = 0;
        for(int i=l;i<=r;i++){
            farthest = max(farthest, i+arr[i]);
        }
        l = r+1;
        r = farthest;
        jumps++;
    }
    return jumps;
}
// TC - O(n), SC - O(1)f
//Converted recursive to range based solution

//----------------------------------------------------------------------------------------------------------------------------------

//Job sequencing problem
// Given n no of jobs every job has its id(to identify), deadline(job should be performed not beyond this day), profit(profit associated with job)
//Note: Every job takes 1 day to complete
// U can perform any no of jobs inorder to maximize the profit, u can perform any no of jobs but it should be performed under deadline and a job takes 1 day to complete from its start
//Return max Profit
// For ex:
// id    deadline    profit
// 1       4           40
// 2       1           10
// 3       1           40
// 4       1           30

// Here to maximise profit: day1; job3, day2: job1; tot_profit=80

// So we should choose that job 1st which has least deadline and max profit, So use a pq 

struct compare{
    bool operator()(const tuple<int, int, int>& a, const tuple<int, int, int>& b) const{
        if(get<0>(a) != get<0>(b)){
            return get<0>(a) > get<0>(b);
        }
        if(get<1>(a) != get<1>(b)){
            return get<1>(a) < get<1>(b);
        }
        return get<2>(a) > get<2>(b);
    }
};

int jobSeqP(vector<vector<int>>& jobs){
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, compare> pq;
    for(int i=0;i<jobs.size();i++){
        pq.push({jobs[i][1], jobs[i][2], i});
    }
    int maxProfit = 0;
    int i=1;
    while(!pq.empty()){
        while(i > get<0>(pq.top()) && !pq.empty()){
            pq.pop();
        }
        if(!pq.empty()){
            maxProfit += get<1>(pq.top());
            pq.pop();
            i++;
        }
    }
    return maxProfit;
}
//TC - O(3*n + n), SC - O(1)

// Found 2 approaches:
// Approach 1; Go for highest profit, if profit same then go for one with least deadline
// Approach 2: Select 1 with least deadline and if deadline same then select 1 with highest profit 
// And after many dry runs figured out somehow, end result = max_of_profit_obtained_in(approach 1 , approach2)

// Seems its wrong 
// Correct approach:
// Arrange jobs in increasing order of their profit
// Go through each and check can they be assigned in any day from deadline to 1, if yes then assign in most farthest day as possible within deadline and move forward

int jobSecGreedy(vector<vector<int>>& jobs){
    priority_queue<tuple<int, int>> pq;
    int maxDead = -1;
    for(int i=0;i<jobs.size();i++){
        pq.push({jobs[i][2], i});
        maxDead = max(maxDead, jobs[i][1]);
    }    
    vector<int> jobAss(maxDead+1, -1);

    int maxProfit = 0;
    while(!pq.empty() ){
        int dead = jobs[get<1>(pq.top())][1];
        for(int j=dead;j>=1;j--){
            if(jobAss[j] == -1){
                jobAss[j] = get<1>(pq.top());
                maxProfit += get<0>(pq.top());
                break;
            }
        }
        pq.pop();
    }
    return maxProfit;
}
//TC - o(n*logn + n*maxdead*logn), SC - o(maxdead + n)

// Operation	                        Complexity
// Building priority queue	            O(N log N)
// Processing N jobs	                O(N log N)
// Searching for free slots	        O(N × D)
// Auxiliary space	                    O(N + D)

// Here, D is the maximum deadline.

// Final TC: O(N log N + N × D)

// Final SC: O(N + D)


//His approach: sorting the input arr based on profit and then making a arr of size maxDeadline and going to each sortd job and asssigning it to max possible day corresponding to its deadline

class jobs{
    public:
    int id;
    int deadline;
    int profit;

    jobs(int id1, int dead1, int profit1){
        id = id1;
        deadline = dead1;
        profit = profit1;
    }
};

bool compare(const jobs& a, const jobs& b){
    return a.profit > b.profit;
}

pair<int, int> jobSeqPHisOpt(vector<jobs>& arr){
    sort(arr.begin(), arr.end(), compare);

    int maxDead = -1;
    for(int i=0;i<arr.size();i++){
        maxDead = max(maxDead, arr[i].deadline);
    }
    vector<int> jobAss(maxDead+1, -1);

    int maxProfit = 0;
    int cnt = 0; //count of jobs done
    for(int i=0;i<arr.size();i++){
        for(int j=arr[i].deadline;j>=1;j--){
            if(jobAss[j] == -1){
                jobAss[j] = arr[i].id;
                maxProfit += arr[i].profit;
                cnt++;
                break;
            }
        }
    }
    return {cnt, maxProfit};
}
//TC - O(n*logn + n + n*maxDead), SC - O(maxDead)

//----------------------------------------------------------------------------------------------------------------------------------

//N meeting in 1 room

// Given a meeting room and 2 arrs repsenting start time and end time of each meeting
// Should choose meetings such that no 2 meetings should overlap and such that u should maximize the no of meetings held

// start - {0, 3, 1, 5, 5, 8}
// end - {5, 4, 2, 9, 7, 9}

// for ex:
// choosing 0-5, cannot choose 3-4, cannot 1-2, cannot 5-9 and 5-7, 8-9 possible: this way can choose only (0-5) and (8-9), total=2

// But choosing (1-2) and (3-4) and (5-7) and (8-9), total = 4

// Only 1 way: first choose meeting with smallest end time thats all
//Return max no of meeting possible

bool compareStart(const pair<int, int>& a, const pair<int, int>& b){
    return a.second < b.second;
}

int NMeeting(vector<pair<int, int>>& start_end){
    sort(start_end.begin(), start_end.end(), compareStart);

    int res=0;
    int endTime=-1;
    for(int i=0;i<start_end.size();i++){
        if(start_end[i].first > endTime){
            endTime = start_end[i].second;
            res++;
        }
    }
    return res;
}
//TC - O(nlogn + n), SC - O(1)

//----------------------------------------------------------------------------------------------------------------------------------

//Non Overlapping Intervals
// U are given start and end time of each meetigs u need to say minimum no of removals inorder to make whole set of meetings non overlapping
//Intervals are in sorted order and no overlap exist in them
// - 2 meetings having a.end_time = b.start_time is not overlaping (Note: in all other intervals problem it would be considered overlaping including in previous but not here)
// For ex:
// {{1,2}, {2,3}, {3,4}, {1,3}}
// 1__2
//    2__3
//       3__4
// 1_____3

// min removals - 1 {(1,3)}

// This quest is reverse of previous why? cuz it asks remopva;l to make non overlaping and previous asked no of them if aim to keep non overlaping So total - prev_result

int nonOverlaping(vector<pair<int, int>>& arr){
    sort(arr.begin(), arr.end(), compareStart);

    int endTime = arr[0].second;
    int noOfMeet = 1;
    for(int i=1;i<arr.size();i++){
        if(arr[i].first >= endTime){
            endTime = arr[i].second;
            noOfMeet++;
        }
    }
    return (arr.size()-noOfMeet);
}
//TC - O(nlogn + n), SC - O(1)

//----------------------------------------------------------------------------------------------------------------------------------

//Insert Intervals
// Given interval arr: which is non overlapping (Note: no 2 meet even has a.end_time = b.start_time), and newInterval arr/pair which u have to insert and give back

// Ex:
// intervals = {{1,3}, {6,9}}, new_interval = {2,5}
// res = {{1,5}, {6,9}}

// {{1,3}, {6,9}}, new_interval = {4,5}
// res = {{1,3}, {4,5}, {6,9}}

// {{1,2}, {3,4}, {6,7}, {8,10}, {12,16}}, new = {5,8}
// res - {{1,2}, {3,4}, {5,10}, {12,16}}

//____________________________________________________________

// So first check (arr[i].endTime < new_interval.start_time && arr[i+1].start_time > new_interval.start_time) once found such i insert the pair in position (i+1) once inserted 
// Now for end_time go on checking for next i:
// if(arr[i].start_time > new_interval.end_time): 
//     then make insert_interval.end_time = new_interval.end_time and 
// if (arr[i].start_time < new_interval.end_time) && (arr[i].end_time > new_interval.end_time): 
//     then insert_interval.endTime = arr[i].endTime

// vector<pair<int, int>> insertIntervals(vector<pair<int, int>>& intervals, vector<int>& newInterval){
//     vector<pair<int, int>> res;
//     for(int i=0;i<intervals.size()-1;i++){
//         if( (intervals[i].second < newInterval[0]) && (intervals[i+1].first > newInterval[0])){
//             int endTime = newInterval[1];
//             int j=i+1;
//             while(j<intervals.size()){
//                 if(arr[i].first > newInterval[1]){
//                     endTime = newInterval[1];
//                     j--;
//                     break;
//                 }
//                 else if(arr[i].first < newInterval[1] && arr[i].second > newInterval[1]){
//                     endTime = arr[i].second;
//                     break;
//                 }
//                 j++;
//             }
//             res.push_back({newInterval[0], endTime})
//             i = j+1;
//         }
//         else if(intervals[i].first > newInterval[0]){
            
//         }
//     }
// }
//____________________________________________________________



// Apparently ur above is complicated and jumbled
// U should divide problm int 3section i. left non overlaping, ii.overlaping intervals, iii. right non overlaping
auto insertNewInsert(vector<pair<int, int>>& intervals, vector<int>& newInterval){
    vector<pair<int,int>> res;
    //leftEnd
    int leftEnd=0;
    while(leftEnd<intervals.size()){
        if(intervals[leftEnd].second >= newInterval[0]){
            break;
        }
        leftEnd++;
    }
    if(leftEnd != 0){
        int i=0;
        while(i<leftEnd){
            res.push_back({intervals[i].first, intervals[i].second});
            i++;
        }
    }

    //Find Overlapping;
    int rightStart = leftEnd; 
    vector<int> choice = {newInterval[0], newInterval[1]};
    while(rightStart < intervals.size()){
        if(intervals[rightStart].first > newInterval[1]){
            break;
        }
        choice.push_back(intervals[rightStart].first);
        choice.push_back(intervals[rightStart].second);
        rightStart++;
    }

    int midStart = *(min_element(choice.begin(), choice.end()));
    int midEnd = *(max_element(choice.begin(), choice.end()));

    res.push_back({midStart, midEnd});

    //Right non overlapping addition
    while(rightStart < intervals.size()){
        res.push_back({intervals[rightStart].first, intervals[rightStart].second});
        rightStart++;
    }

    return res;
}
//TC - O(n), SC - o(n)

//Possible only cuz intervals is sorted

//----------------------------------------------------------------------------------------------------------------------------------

//Minimum no of platforms required for a railway station

// Given arrival and departure arr, need to find minimum platforms for all trains to handle
// Ex:
// arrival = {900, 945, 955, 1100, 1500, 1800}
// dep = {920, 1200, 1130f, 1150, 1900, 2000}
// res = 3
 
int minPlatforms(vector<int>& arrival, vector<int>& departure){
    int cnt=0;
    int cnt_changed = 0;
    vector<vector<pair<int, int>>> platforms;
    for(int i=0;i<arrival.size()-1;i++){
        if(arrival[i+1] > departure[i]){
            if(platforms.empty() || cnt_changed){
                vector<pair<int, int>> arr = {{departure[i], arrival[i+1]}};
                platforms.push_back(arr);
            }
            else{
                platforms[cnt].push_back({departure[i], arrival[i+1]});
            }
        }
        else if(arrival[i+1] < departure[i]){
            int flag_fit=0;
            for(int k=0;k<platforms.size();k++){
                for(int j=0;j<platforms[k].size();j++){
                    auto pr = platforms[k][j];
                    if((arrival[i+1] >= pr.first && departure[i+1] <= pr.second) || (j==0 && departure[i+1]<=pr.first) || (j==platforms[k].size() && arrival[i+1] >= pr.second)){
                        platforms[k][j] = {-1, -1};
                        flag_fit=1;
                    }
                }
            }
            if(!flag_fit){
                cnt++;
                cnt_changed = 1;
            }
        }
    }
    return cnt+1;
}

//The above idea is fine but complicates the solution
// His Brut:
// Check max Intersection of a train(arrival, departure) with all remaining, the max intersection is itself is the min no of platforms required

// Ex:
// arrival = {900, 945, 955, 1100, 1500, 1800}
// dep = {920, 1200, 1130, 1150, 1900, 2000}

// Here, 
// (900 - 920) intersecting with none, max=1;
// (945 - 1200) intersecting with (955 - 1130), max = 2;
// (955 - 1130) intersecting with (945-1200), (1100-1150), max=3;
// (1100 - 1150) intersecting with (955-1130), max=3;
// (1500 - 1200) intersecting with (1800-2000), max=3;
// (1800 - 2000) intersecting with (1500-1900), max=3;

// Inorder to find whether a intersection happens or not:
// check 
// 1. Other:   |start      end|
//    Our:   |start           end|   

// 2. Other:   |start      end|
//    Our:  |satrt      end|

// 3. Other:   |start      end|
//    Our:         |start     end| 

// 4. Other:   |start      end|
//    Our:       |start  end|

// That is: 1.Early start and late end, 2.Early start and mid end, 3.Mid Start and late end, 4.Mid Start and mid end

int minPlatformsBrut(vector<int>& arrivals, vector<int>& departure){
    int maxInter = 1;
    for(int i=0;i<arrivals.size();i++){
        int inter=1;
        for(int j=i+1;j<arrivals.size();j++){
            int ourAr = arrivals[i], ourDep = departure[i];
            int otherAr = arrivals[j], otherDep = departure[j];
            if( !((ourAr < otherAr && ourDep <= otherDep) || (ourAr >= otherAr && ourDep > otherDep)) ){
                inter++;
            }
        }
        maxInter = max(maxInter, inter);
    }
    return maxInter;
}
//Tc - O(n^2), SC - O(1)

//Optimal:
/*
Minimum Number of Platforms Required for a Railway Station

We are given two arrays:
- arrival[]   : Arrival times of all trains.
- departure[] : Departure times of all trains.

Step 1: Sort both arrays independently in ascending order.

Step 2: Initialize two pointers and two counters.

    int i = 0, j = 0;
    int cnt = 0, maxi = 0;

- i points to the next unprocessed arrival.
- j points to the next unprocessed departure.
- cnt keeps track of the number of trains currently present
  at the station.
- maxi stores the maximum number of trains present simultaneously.

Step 3: Compare the times pointed to by the two pointers.

While both pointers are within their respective arrays:

1. If arrival[i] <= departure[j]:
   - The next event is an arrival (including equality).
   - Increment cnt because one more train has arrived.
   - Update maxi = max(maxi, cnt).
   - Move the arrival pointer: i++.

2. Otherwise, if arrival[i] > departure[j]:
   - The next event is a departure.
   - Decrement cnt because one train has left.
   - Move the departure pointer: j++.

Step 4: Continue until either pointer reaches the end.

Return maxi.

Why does it work?

- Every arrival occupies one additional platform.
- Every departure frees one platform.
- Sorting both arrays independently allows us to process
  all arrival and departure events in chronological order.
- We do not need to track individual trains or platforms.
- The maximum number of trains present simultaneously
  gives the minimum number of platforms required.

Note:
We use arrival[i] <= departure[j] instead of <
because, in the standard problem, an arriving train cannot
reuse a platform at the exact time another train departs.

Time Complexity: O(N log N)
Auxiliary Space: O(1), excluding sorting space.
*/

int minPlatformsBet(vector<int>& arrivals, vector<int>& departure){
    sort(arrivals.begin(), arrivals.end());
    sort(departure.begin(), departure.end());

    int i=0, j=0;
    int cnt=0, maxi=0;
    while(i<arrivals.size() && j<departure.size()){
        if(arrivals[i] <= departure[j]){
            cnt++;
            i++;
        }
        else{
            cnt--;
            j++;
        }
        maxi = max(maxi, cnt);
    }
    return maxi;
}
//TC - O(2*n*logn + 2*n), SC - O(1)

//----------------------------------------------------------------------------------------------------------------------------------

//Valid Parenthesis:
// Given * along () u can convert * - empty, ( or )
// Ex:
// s=(), valid
// s=(*), valid {*-empty}
// s=(*)), valid {* - (}
// s=(**(, invalid

// For normal without asterisk say 
// s = (()()), u can use cnt var do cnt++ wehen saw ( and cnt-- when saw )
// -> But a edge case:
//     0 1 2 3 
//     ( ) ) (
//     ->i=0, cnt=1
//       i=1, cnt=0
//       i=2, cnt=-1
//       i=3, cnt=0
// Note: So whenever cnt<0 break and say invalid

// But here we have *
// Ex: s = ()*)*(), s = (**(

//One method using recursion
bool validAstParent(string str, int idx, int cnt){

    for(int i=idx;i<str.size();i++){
        if(str[i] == '('){
            cnt++;
        }
        else if(str[i] == ')'){
            cnt--;
            if(cnt < 0) return false;
        }
        else{
            str[i] = '(';
            bool open = validAstParent(str, i, cnt);

            str[i] = ')';
            bool closed = validAstParent(str, i, cnt); 

            // for(int k=i;k<str.size()-1;k++){
            //     str[k] = str[k+1];
            // }
            //or
            str.erase(i, 1);
            bool emp = validAstParent(str, i, cnt); 

            if(open || closed || emp) return true;
            else return false;
        }
    }
    if(!cnt) return true;
    return false;
}
//TC - O(3^n), Sc - O(3^n)

//Clean recursion

bool validParentRec(string str, int idx, int cnt){
    if(idx >= str.size()){
        return (cnt==0);
    }
    if(cnt<0 || str.size()==0) return false;

    if(str[idx] == '('){
        return validParentRec(str, idx+1, cnt+1);
    }
    else if(str[idx] == ')'){
        return validParentRec(str, idx+1, cnt-1);
    }
    return (validParentRec(str, idx+1, cnt+1) || validParentRec(str, idx+1, cnt-1) || validParentRec(str, idx+1, cnt));
}
//TC - O(3^n), SC - O(3^n)
 
//Using DP inorder to reduce TC from O(3^n) to O(n^2)

// Is there a overlaping subproblem - yes where
// ex:
// 0 1 2 3 4 5 6
// ( ) * ) * ( )
//             f(str,0,0)
//             /
//         f(str,1,1)
//         /
//     f(str,2,0)
//     /           |                      \
//  f(str,3,1)=1 f(s,3,-1)=0          f(s,3,0)=0
//     /           0                    |
// f(s,4,0) = 1                      f(s,4,-1)
// /        |        \                   0        
// f(s,5,1) f(s,5,-1) f(s,5,0)     
//  |          0         |           
// f(s,6,2)           f(s,6,1)    
//  |                    |
// f(s,7,1)           f(s,7,0)
// 0                      1
// res = 1

bool validParentDP(string str, int idx, int cnt, vector<vector<int>>& dp){
    if(idx >= str.size()){
        return (cnt==0);
    }
    if(cnt<0) return false;

    if(dp[idx][cnt] != -1){
        return dp[idx][cnt];
    }

    if(str[idx] == '('){
        dp[idx][cnt] = validParentDP(str, idx+1, cnt+1, dp);
    }
    else if(str[idx] == ')'){
        dp[idx][cnt] = validParentDP(str, idx+1, cnt-1, dp);
    }
    else{
        dp[idx][cnt] = (validParentDP(str, idx+1, cnt, dp) || validParentDP(str, idx+1, cnt+1, dp) || validParentDP(str, idx+1, cnt-1, dp));
    }
    return dp[idx][cnt];
}
//TC - O(n^2) { as max no of asterisk possible is n and once all possible (idx,cnt) of depth is travelled and found then all other calls can be found in O(1)}, SC - O(2*n^2)

// U can do Tabularisation and space opt it seems but still TC - O(n^2)
//Optimal: using min and max ranges when got ( incrementing min and max by 1, when got ) decrementing both min and max by 1 check if min<0 if so then do not decrement min and when got * 
// - add min and max by 1: 
// - decre min and max by 1
// - do nothing 
// take min and max out of all these operat and update min, max

bool validParentAAstOpt(string str){
    int mini=0, maxi=0;
    for(int i=0;i<str.size();i++){
        if(str[i] == '('){
            mini++;
            maxi++;
        }
        else if(str[i] == ')'){
            if(mini-1 >= 0) mini--;
            if(maxi-1 >= 0) return false; //as a closing without early opening surely not valid
        }
        else{
            if(mini-1 >= 0) mini--;
            maxi++;
        }
    }
    return (mini==0);
}
//TC - O(n), SC - O(1)

bool validParentAAstOptHis(string str){
    int mini=0, maxi=0;
    for(int i=0;i<str.size();i++){
        if(str[i] == '('){
            mini++;
            maxi++;
        }
        else if(str[i] == ')'){
            mini--;
            maxi--;
        }
        else{
            mini--;
            maxi++;
        }
        if(mini < 0) mini = 0;
        if(maxi < 0) maxi = 0;
    }
    return (mini==0);
}

//----------------------------------------------------------------------------------------------------------------------------------

//Candy
// Given a arr, u have to assign candies to each arr element such that
// 1. Every child(arr elem) should get atleast 1 candy
// 2. A child with greater value should get higher no of candies then its neughbours
// Return minimum no of candies need to assign

//Brut;
// Go through arr left to right assign candies satisfying left neigbour i.e assign 1 more candy to child if left neighbour val less then current 
//     - Note: If left neighbor val is same as current then assign 1 candy, only if current > leftNeighbor then left_candyAss+1
// Go through arr right to left and assign candy satisfying right neighbor
//     - Note: if rightNeighbor = current then assign 1 candy, if rightNeighbor > current then assign right_candyAss+1

// And the final candy assignment will be max(leftAss, rightAss)
int CandyBrut(vector<int>& arr){
    int n = arr.size();
    vector<int> leftAss(n, 0);
    vector<int> rightAss(n, 0);

    for(int i=0;i<n;i++){
        if(i>0 && arr[i]>arr[i-1]){
            leftAss[i] = leftAss[i-1]+1;
        }
        else{
            leftAss[i]=1;
        }
    }

    for(int i=n-1;i>0;i--){
        if(i<(n-1) && arr[i] > arr[i+1]){
            rightAss[i] = rightAss[i+1]+1;
        }
        else{
            rightAss[i] = 1;
        }
    }

    int minCandies = 0;
    for(int i=0;i<n;i++){
        minCandies += max(leftAss[i], rightAss[i]);
    }
    return minCandies;
}
//Why max(left, right) works cuz:
// we can saidfy both left and right using max 
//TC - O(3*n), SC - O(2*n)

// Ex:
// arr - {1,2,3}
// left - {1, 2, 3}
// right - {1, 1, 1}
// Actual - {1, 2, 3} minCandies=6

// 2. {1, 3, 2, 1}
// left - {1, 2, 1, 1}
// right - {1, 3, 2, 1}
// actual - {1, 3, 2, 1} min = 7

// 3. {0, 2, 4, 3, 2, 1, 1, 3, 5, 6, 4, 0, 0}
// left - {1, 2, 3, 1, 1, 1, 1, 2, 3, 4, 1, 1, 1}
// right- {1, 1, 4, 3, 2, 1, 1, 1, 1, 3, 2, 1, 1}
// actual-{1, 2, 4, 3, 2, 1, 1, 2, 3, 4, 2, 1, 1}, min = 27

//Brut Optimized
//Removing right arr 

int CandyBrutOpt(vector<int>& arr){
    int n = arr.size();
    vector<int> leftAss(n, 0);
    vector<int> rightAss(n, 0);

    for(int i=0;i<n;i++){
        if(i>0 && arr[i]>arr[i-1]){
            leftAss[i] = leftAss[i-1]+1;
        }
        else{
            leftAss[i]=1;
        }
    }

    int minCandies=0;
    int cur;
    int prev;
    for(int i=n-1;i>=0;i--){
        if(i<(n-1) && arr[i] > arr[i+1]){
            cur = prev+1;
            prev = cur;
        }
        else{
            cur = 1;
            prev = cur;
        }
        minCandies += max(leftAss[i], cur);
    }

    return minCandies;
}
//TC - O(2*n), SC - O(n)

//Optmal: using slope concept
int minCandyOpt(vector<int>& arr){
    int i=1;
    int minCandies=1;
    int n=arr.size();

    while(i<n){
        if(arr[i] == arr[i-1]){
            minCandies++;
            i++;
            continue;
        }

        int peak = 1;
        while(i<n && arr[i] > arr[i-1]){
            peak++;
            minCandies += peak;
            i++;
        }

        int down = 1;
        while(i<n && arr[i] < arr[i-1]){
            minCandies += down;
            down++;
            i++;
        }

        if(peak < down){
            minCandies += (down - peak);
        }
    }
    return minCandies;
}
//TC - O(n), SC - O(1)

//----------------------------------------------------------------------------------------------------------------------------------
//Fractional Knapsack

// Given arr of pairs each repesenting knapsacks value and weight, and given a max weight need to choose knapsack such that they should under given weight and maximise profit/value
// Note: Can choose a knapsack fractinal if total is not fitable in remaining weight

// arr = {(100,20), {60,10}, (100,50), (200,50)}, W=90

// - (100, 20), v=100, w=80
// - (60, 10), v=160, w=70
// - (100, 50), v=260, w=20
// - (200, 50), v=260 + (200/50)*10 = 300, w=0
// res = 300

// But maxval:
// - (100, 20), v=100, w=80
// - (60, 10), v=160, w=70
// - (200, 50), v=360, w=20
// - (100, 50), v=360 + (100/50)*10 = 380, w=0
// res = 400

//Apparently do not go like first based on weight ascendingly and then based on profit if weight tie 
//Sort desc based on unit val, unit val = value/weight

bool compareKnap(const pair<int, int>& a, const pair<int, int>& b){
    return (a.first/a.second) > (b.first/b.second);
}

int fractionalKnapsack(vector<pair<int, int>>& arr, int weight){
    sort(arr.begin(), arr.end(), compareKnap);

    int maxVal=0;
    for(int i=0;i<arr.size();i++){
        if(arr[i].second < weight){
            maxVal += arr[i].first;
            weight -= arr[i].second;
        }
        else{
            maxVal += (arr[i].first/arr[i].second)*weight;
            weight = 0;
            break;
        }
    }
    return maxVal;
}
//TC - O(nlogn + n), SC - O(1)

int main(){
    // vector<int> greed = {1, 5, 3, 3, 4};stepsTaken
    // vector<int> cookie = {4, 2, 1, 2, 1, 3};

    // cout<<assignCookiesBet(greed, cookie);

    //======================================

    // vector<int> lem = {5,5,10,10,20};
    // cout<<LemonadeChange(lem);

    //======================================

    // vector<int> procss = {4, 3, 7, 1, 2};
    // cout<<SJF(procss);

    //======================================

    // vector<int> arr = {2, 3, 1, 1, 4};
    // // vector<int> dp(arr.size(), -1);
    // vector<vector<int>> dp(arr.size(), vector<int>(arr.size(), -1));
    // cout<<jumpGame2HisMemo(arr, dp, 0, 0);

    //======================================

//     vector<vector<int>> arr = {
//     {1, 2, 100},
//     {2, 1, 19},
//     {3, 2, 27},
//     {4, 1, 25},
//     {5, 3, 15}
// };
//     cout<<jobSecGreedy(arr);

    // vector<jobs> arr;
    // vector<vector<int>> jbs = {
    //     {1, 2, 100},
    //     {2, 1, 19},
    //     {3, 2, 27},
    //     {4, 1, 25},
    //     {5, 3, 15}
    // };

    // for(int i=0;i<jbs.size();i++){
    //     jobs obj(jbs[i][0], jbs[i][1], jbs[i][2]);
    //     arr.push_back(obj);
    // }
    // auto pr = jobSeqPHisOpt(arr);
    // cout<<pr.first<<" "<<pr.second<<endl;

    //======================================================

    // vector<pair<int, int>> arr = {{1,2}, {2,3}, {3,4}, {1,3}};
    // cout<<nonOverlaping(arr);

    //======================================================

    // vector<pair<int, int>> intervals = {{1,2}, {3,4}, {6,7}, {8,10}, {12,16}};
    // vector<int> newInterval = {5,8};

    // auto res = insertNewInsert(intervals, newInterval);
    // for(auto v:res){
    //     cout<<"("<<v.first<<" "<<v.second<<") ";
    // }

    //======================================================

    // vector<int> arr = {900, 945, 955, 1100, 1500, 1800};
    // vector<int> dep = {920, 1200, 1130, 1150, 1900, 2000};
    // cout<<minPlatformsBet(arr, dep);

    //======================================================

    // string str = "(**(";
    // vector<vector<int>> dp(str.size(), vector<int>(str.size(), -1));
    // cout<<validParentAAstOpt(str);

    //======================================================

    // vector<int> arr = {0, 2, 4, 3, 2, 1, 1, 3, 5, 6, 4, 0, 0};
    // cout<<minCandyOpt(arr);

    //======================================================

    vector<pair<int, int>> arr = {{100,20}, {60,10}, {100,50}, {200,50}};
    cout<<fractionalKnapsack(arr, 90);
    
    return 0;
}
