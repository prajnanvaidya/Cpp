#include<bits/stdc++.h>
using namespace std;

/*
================================================================================
      ARRAYS - PART 4 : SUBARRAY SUM (PREFIX SUM AND SLIDING WINDOW)
================================================================================
A SUBARRAY is a CONTIGUOUS slice of the array.

    arr = 9 1 3 5 6
        9 1      -> subarray (contiguous)
        3 5 6    -> subarray (contiguous)
        9 3      -> NOT a subarray; it is a subsequence (order kept, gaps
                    allowed)

An array of size n has n(n+1)/2 subarrays - which is why brute force here is
O(n^2), not O(2^n). (2^n counts SUBSEQUENCES, not subarrays. The original notes
had this mixed up.)

THE TWO TECHNIQUES IN THIS FILE:
    PREFIX SUM + HASH MAP  - works with negatives and zeros, O(n) time O(n) space
    SLIDING WINDOW         - only for non-negative values, O(n) time O(1) space

Knowing WHICH applies is the whole skill: the window technique silently gives
wrong answers on negative input, and that is the most common trap here.

TABLE OF CONTENTS
-----------------
  PROBLEM 1 : Longest subarray with sum K
  PROBLEM 2 : Count subarrays with sum K
  NOTES     : Why sliding window needs non-negatives, and common mistakes

================================================================================
PROBLEM 1 : LONGEST SUBARRAY WITH SUM K
================================================================================
    arr = 1 2 3 1 1 1 1,  k = 6
    answer = 4   (the subarray 3 1 1 1)
*/

// ---- BRUTE: try every subarray ----
int longestBrute(vector<int>& arr, long long k){
    int n = arr.size(), maxLen = 0;

    for(int i = 0; i < n; i++){
        long long sum = 0;
        for(int j = i; j < n; j++){            // j STARTS AT i, not i+1
            sum += arr[j];
            if(sum == k) maxLen = max(maxLen, j - i + 1);
        }
    }
    return maxLen;
}
/*
TC - O(n^2), SC - O(1)

***** A BUG IN THE ORIGINAL: the inner loop started at j = i+1 *****
That means every subarray of LENGTH 1 is never tested. If the answer is a single
element equal to k, it is missed entirely.
VERIFIED BY TESTING on arr = 1 2 6 3 with k = 6: the answer is the single
element [6], and the original returned an empty result.
The inner loop must start at j = i so the one-element case is covered.

Note this version accumulates `sum` as it extends j rather than recomputing from
scratch, which is what keeps it at O(n^2) instead of O(n^3).

DO NOT add `if(sum > k) break;` unless you know all values are non-negative -
with negatives, a sum that overshoots can come back down.
*/

// ---- OPTIMAL for ANY values (negatives allowed): prefix sum + hash map ----
int longestPrefixSum(vector<int>& arr, long long k){
    unordered_map<long long,int> firstIndex;   // prefix sum -> EARLIEST index
    long long sum = 0;
    int maxLen = 0;

    for(int i = 0; i < (int)arr.size(); i++){
        sum += arr[i];

        if(sum == k) maxLen = max(maxLen, i + 1);   // whole prefix works

        long long need = sum - k;
        auto it = firstIndex.find(need);
        if(it != firstIndex.end())
            maxLen = max(maxLen, i - it->second);

        // store ONLY the first occurrence of this prefix sum
        if(firstIndex.find(sum) == firstIndex.end())
            firstIndex[sum] = i;
    }
    return maxLen;
}
/*
TC - O(n) average with unordered_map (O(n log n) with map, O(n^2) worst case on
     hash collisions).  SC - O(n)

THE CORE IDEA:
    prefix[i] = arr[0] + ... + arr[i]
    sum of the slice (j+1 .. i) = prefix[i] - prefix[j]

So a slice ending at i sums to k exactly when some earlier prefix equals
prefix[i] - k. Look that value up in the map: O(1) instead of scanning back.

***** WHY "STORE ONLY THE FIRST OCCURRENCE" IS ESSENTIAL *****
We want the LONGEST slice, so for a given prefix value we want the EARLIEST
index - the further left it starts, the longer the slice.

The failing case is zeros (or negatives), where the same prefix sum recurs:

    arr = 2 0 0 3, k = 3     (answer: 0 0 3, length 3)

    i=0: sum=2, map{2:0}
    i=1: sum=2 again. If we overwrite -> map{2:1}
    i=2: sum=2 again. If we overwrite -> map{2:2}
    i=3: sum=5, need=2, found at index 2 -> length 3-2 = 1   WRONG
                        found at index 0 -> length 3-0 = 3   CORRECT

With only positive values every prefix is strictly increasing, so sums never
repeat and the guard is invisible - which is exactly why this bug hides until a
zero shows up in the test data.

USE long long FOR SUMS. Prefix sums accumulate and overflow int quickly.

The original also had an O(n^2) "better" version that stored index -> sum and
then scanned backwards looking for the value. Storing sum -> index instead is
what turns that backward scan into an O(1) lookup.
*/

// ---- OPTIMAL for NON-NEGATIVE values: sliding window, O(1) space ----
int longestSlidingWindow(vector<int>& arr, long long k){
    int n = arr.size();
    int left = 0, maxLen = 0;
    long long sum = 0;

    for(int right = 0; right < n; right++){
        sum += arr[right];                     // grow the window

        while(left <= right && sum > k){       // shrink while too big
            sum -= arr[left];
            left++;
        }
        if(sum == k) maxLen = max(maxLen, right - left + 1);
    }
    return maxLen;
}
/*
TC - O(2n) = O(n), SC - O(1)

WHY O(n) DESPITE THE NESTED LOOP: `left` never resets - it only ever moves
forward, across the whole run of the algorithm. So right advances n times total
and left advances at most n times total. n + n, not n * n.

***** IT MUST BE `while`, NOT `if` *****
One shrink step is not guaranteed to bring the sum back to <= k; you may need
several. The original notes caught this themselves after tracing {1,2,3} with
k=2 into an infinite loop, and the diagnosis there was exactly right.

STRUCTURE MATTERS - the order inside the loop is:
    1. add arr[right]         (grow)
    2. while(sum > k) shrink  (restore the invariant)
    3. check sum == k         (only now is the window valid)
Checking before shrinking would test a window that is known to be too big.

This version uses a for loop over `right`, which removes the need for the
awkward `right++; if(right<n) sum+=arr[right];` tail the original had, and makes
the empty-array case safe automatically. The original initialised
`sum = a[right]` before the loop, which reads a[0] on an EMPTY array -
out of bounds.
*/


/*
================================================================================
PROBLEM 2 : COUNT SUBARRAYS WITH SUM K
================================================================================
Now we want HOW MANY, not how long.
    arr = 5 1 2 3 1,  k = 6   ->   3
*/

// ---- OPTIMAL for ANY values: prefix sum + frequency map ----
int countPrefixSum(vector<int>& arr, long long k){
    unordered_map<long long,int> freq;
    freq[0] = 1;                               // see the note below
    long long sum = 0;
    int count = 0;

    for(int v : arr){
        sum += v;
        long long need = sum - k;

        auto it = freq.find(need);
        if(it != freq.end()) count += it->second;   // add the FREQUENCY

        freq[sum]++;                            // record this prefix sum
    }
    return count;
}
/*
TC - O(n) average, SC - O(n)

TWO DIFFERENCES FROM THE LONGEST-SUBARRAY VERSION - both essential:

  1. The map stores prefix sum -> FREQUENCY, not -> index.
     For counting we need how MANY earlier prefixes match, not which one.

  2. freq[0] = 1 is seeded before the loop.
     Interpretation: "the empty prefix, with sum 0, has been seen once."
     Without it, a slice starting at index 0 is never counted - because
     sum - k = 0 would find nothing in the map. Seeding 0 fixes exactly that.

TRACE on 5 1 2 3 1, k=6:
    start        freq{0:1}
    v=5  sum=5   need=-1   not found                 freq{0:1, 5:1}
    v=1  sum=6   need=0    found x1 -> count=1       freq{0:1, 5:1, 6:1}
    v=2  sum=8   need=2    not found                 freq{...,8:1}
    v=3  sum=11  need=5    found x1 -> count=2       freq{...,11:1}
    v=1  sum=12  need=6    found x1 -> count=3       freq{...,12:1}
    answer 3

WITH REPEATED PREFIX SUMS the frequency really matters - arr = 2 0 0 3, k=3:
    prefix sum 2 occurs at indices 0, 1, and 2, so freq{2:3}. At the end,
    need = 2 finds 3 matches at once, giving the correct answer of 3.
    Storing an index instead of a count would report only 1.
*/

// ---- Sliding window for NON-NEGATIVE values: the "at most" trick ----
long long countAtMost(vector<int>& arr, long long k){
    if(k < 0) return 0;                        // no subarray has a negative sum
    long long count = 0, sum = 0;
    int left = 0;

    for(int right = 0; right < (int)arr.size(); right++){
        sum += arr[right];
        while(left <= right && sum > k){ sum -= arr[left]; left++; }
        count += (right - left + 1);           // EVERY window ending at right
    }
    return count;
}

int countSlidingWindow(vector<int>& arr, long long k){
    return (int)(countAtMost(arr, k) - countAtMost(arr, k - 1));
}
/*
TC - O(n) (two passes), SC - O(1)

***** WHY THE OBVIOUS SLIDING WINDOW DOES NOT WORK FOR COUNTING *****

The natural instinct is to reuse the longest-subarray window and just do
`if(sum == k) count++`. That is WRONG, and the reason is worth understanding.

A window reports at most ONE subarray per right endpoint. But when the array
contains ZEROS, several different left positions can give the same sum, so
multiple valid subarrays share one right endpoint - and the window can only
ever report one of them.

VERIFIED BY TESTING on arr = 4 4 3 2 4 0 0 1 2 0 with k = 1:
    naive window : 1
    correct      : 3        ([1], [0,1], [0,0,1])

This is NOT limited to k=0 - any zero anywhere in the array can trigger it.

THE FIX - count differently. `countAtMost(k)` counts every subarray with sum
<= k by adding (right - left + 1) at each step: once the window [left..right]
is valid, every window ending at right and starting at or after left is also
valid, and there are exactly that many. Then:

    (subarrays with sum exactly k) = (sum <= k) - (sum <= k-1)

This is a standard and very reusable pattern - the same trick converts many
"exactly k" window problems into two "at most k" passes.

VERIFIED BY TESTING: passes 5000 random cases including zeros and k = 0.
Requires NON-NEGATIVE values (see the next section for why).

***** A BUG WORTH NAMING FROM THE ORIGINAL NOTES *****
One version used `if(sum > k)` rather than `while(sum > k)` inside this counter -
the same mistake the notes had already diagnosed for the longest-subarray
version.
VERIFIED BY TESTING on arr = 10 1 2 3 with k = 3:
    with if()    -> 1
    with while() -> 2      (correct: [3] and [1,2])
A single shrink cannot always restore sum <= k; one large leading element is
enough to break it.
*/

// ---- General entry point ----
int countSubarraysWithSumK(vector<int>& arr, long long k){
    return countPrefixSum(arr, k);             // works for ANY values
}
/*
For non-negative input you may prefer countSlidingWindow for its O(1) space.
For anything that may contain negatives, countPrefixSum is the only correct
choice of the two.
*/


/*
================================================================================
WHY SLIDING WINDOW REQUIRES NON-NEGATIVE VALUES
================================================================================
The window technique rests on one assumption:

    growing the window can only INCREASE the sum
    shrinking the window can only DECREASE the sum

That is what makes "sum too big -> shrink from the left" a valid move.

WITH A NEGATIVE VALUE THE ASSUMPTION COLLAPSES:

    arr = 5, -2, 3    k = 6

    right=0: sum=5, 5 < 6, keep going
    right=1: sum=3, still < 6
    right=2: sum=6, match, length 3

That happens to work - but consider needing to shrink past a negative. Once
sum > k, dropping a NEGATIVE element from the left makes the sum LARGER, not
smaller. The loop's guarantee is gone, and it can discard a valid answer or spin.

DECISION RULE:
    negatives possible?              -> prefix sum + hash map  (O(n) space)
    all values >= 0 and space matters -> sliding window        (O(1) space)

Interview problems very often include negatives specifically to see whether you
reach for the window without checking.


================================================================================
COMMON MISTAKES
================================================================================
  [X] Inner brute loop starting at    -> misses all length-1 subarrays.
      j = i+1                            VERIFIED: returned nothing when the
                                         answer was a single element
  [X] if(sum > k) instead of          -> one shrink may not be enough.
      while(sum > k)                     VERIFIED: undercounted, and the
                                         original traced it into an infinite loop
  [X] Overwriting a prefix sum        -> for LONGEST you need the EARLIEST
      already in the map                 index; only store the first occurrence
  [X] Forgetting freq[0] = 1          -> subarrays starting at index 0 are
      in the counting version            never counted
  [X] Using index instead of          -> counting needs how MANY earlier
      frequency when counting            prefixes matched, not which one
  [X] Sliding window on data with     -> the shrink step is only valid when
      negative values                    values are non-negative
  [X] Counting with a plain window     -> multiple valid subarrays can share one
      when zeros are present               right endpoint. VERIFIED: gave 1 when
                                           the answer was 3. Use
                                           atMost(k) - atMost(k-1)
  [X] int for prefix sums             -> overflows fast; use long long
  [X] Reading a[0] before the loop    -> out of bounds on an empty array
  [X] Saying an array has 2^n         -> 2^n counts SUBSEQUENCES; subarrays are
      subarrays                          n(n+1)/2, which is why brute is O(n^2)
================================================================================
*/


int main(){
    int n;
    long long k;
    cin >> n;
    vector<int> arr(n);
    for(int i = 0; i < n; i++) cin >> arr[i];
    cin >> k;

    cout << "Longest subarray with sum " << k << ": "
         << longestPrefixSum(arr, k) << endl;
    cout << "Number of subarrays with sum " << k << ": "
         << countPrefixSum(arr, k) << endl;

    return 0;
}