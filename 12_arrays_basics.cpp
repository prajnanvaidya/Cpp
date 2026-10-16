#include<bits/stdc++.h>
using namespace std;

/*
================================================================================
              ARRAYS - PART 1 : BASICS AND SINGLE-PASS PROBLEMS
================================================================================
An ARRAY is a collection of elements of the SAME data type stored in a
CONTIGUOUS block of memory.

    dataType name[size];              // declaration
    dataType name[] = {1, 2, 3};      // declaration + initialisation

0-BASED INDEXING throughout.

MEMORY: the OS finds a contiguous block of the requested size. You cannot
predict WHERE it lands, so you never address elements by absolute address - you
address them by INDEX, and the compiler computes
    address = base_address + index * sizeof(T)
That one multiply-and-add is why arr[i] is O(1).

SIZE LIMITS (approximate, platform-dependent):
    global declaration : ~10^7 ints    (large static area, auto zero-filled)
    local  declaration : ~10^6 ints    (the stack is only ~1-8 MB)
Large arrays go global, or use a vector (heap).

--------------------------------------------------------------------------------
THE THREE-TIER APPROACH
--------------------------------------------------------------------------------
Almost every DS problem has three levels of answer. Always find them in order -
the brute force teaches you what the problem actually is, and the optimisation
usually comes from noticing what the brute force repeats.

    BRUTE FORCE : the obvious way. Usually O(n^2) or worse.
    BETTER      : usually trades memory for speed (hashing, extra arrays).
    OPTIMAL     : usually O(n) time and O(1) space.

TABLE OF CONTENTS
-----------------
  PROBLEM 1 : Largest element
  PROBLEM 2 : Second largest element
  PROBLEM 3 : Second largest AND second smallest
  PROBLEM 4 : Check if array is sorted
  PROBLEM 5 : Remove duplicates from a sorted array
  PROBLEM 6 : Count unique elements
  NOTES     : Common mistakes

================================================================================
PROBLEM 1 : LARGEST ELEMENT
================================================================================
BRUTE: sort the array and return arr[n-1].
       TC O(n log n), SC O(1). Correct but wasteful - sorting does far more work
       than the question asks for, and it destroys the input order.

OPTIMAL: one pass, tracking the maximum seen so far.
*/

int largestElement(vector<int>& arr){
    int largest = arr[0];
    for(int i = 1; i < (int)arr.size(); i++){
        if(arr[i] > largest) largest = arr[i];
    }
    return largest;
}
// TC - O(n), SC - O(1)
// STL equivalent: *max_element(arr.begin(), arr.end())


/*
================================================================================
PROBLEM 2 : SECOND LARGEST ELEMENT
================================================================================
"Second largest" means the second largest DISTINCT value.
    {5, 5, 2}  ->  second largest is 2, not 5.

BRUTE: sort, take arr[n-1] as largest, then scan backwards for the first value
       that differs from it. TC O(n log n + n).

BETTER: two passes without sorting - first find the largest, then find the
        biggest value that is not the largest.
*/

int secondLargestTwoPass(vector<int>& arr){
    int n = arr.size();
    int largest = arr[0];
    for(int i = 1; i < n; i++)
        if(arr[i] > largest) largest = arr[i];

    int secL = INT_MIN;                    // sentinel, see the note below
    for(int i = 0; i < n; i++)
        if(arr[i] != largest && arr[i] > secL) secL = arr[i];

    return secL;                            // INT_MIN means "does not exist"
}
/*
TC - O(2n) = O(n), SC - O(1)

***** TWO BUGS FIXED FROM THE ORIGINAL *****

BUG 1 - `return largest, secL;`
That is the COMMA OPERATOR, not a way to return two values. It evaluates
`largest`, throws the result away, and returns `secL`. The function silently
returns only one value while looking like it returns two.
VERIFIED BY TESTING on {5,2,9,1}: the function returned 5, not 9.
To return two values, use pair<int,int> and `return {largest, secL};`

BUG 2 - `int secL = -1;`
-1 only works as an "empty" marker if every array value is non-negative. With
negative input like {-5, -2, -9} the real second largest is -5, but -1 beats it
in the comparison and the function returns -1, which is not even in the array.
Use INT_MIN, or return a flag/optional separately.
*/

// ---- OPTIMAL: one pass ----
pair<int,int> largestAndSecondLargest(vector<int>& arr){
    int n = arr.size();
    int largest = arr[0];
    int secL = INT_MIN;

    for(int i = 1; i < n; i++){
        if(arr[i] > largest){
            secL = largest;                 // the old champion is demoted
            largest = arr[i];
        }
        else if(arr[i] < largest && arr[i] > secL){
            secL = arr[i];                   // not the biggest, but beats 2nd
        }
        // arr[i] == largest -> a duplicate of the max, deliberately ignored
    }
    return {largest, secL};
}
/*
TC - O(n), SC - O(1)

THE KEY INSIGHT: when a new maximum arrives, the OLD maximum automatically
becomes the second largest. You never have to search backwards.

WHY THE `arr[i] < largest` CHECK MATTERS: without it, a duplicate of the maximum
would fall into the second branch and set secL = largest, which is wrong.
Requiring a STRICT inequality is what makes "second largest DISTINCT" work.
*/


/*
================================================================================
PROBLEM 3 : SECOND LARGEST AND SECOND SMALLEST IN ONE PASS
================================================================================
Same idea, mirrored. Track four values simultaneously.
*/

pair<int,int> secondLargestAndSmallest(vector<int>& arr){
    int largest  = INT_MIN, secLarge = INT_MIN;
    int smallest = INT_MAX, secSmall = INT_MAX;

    for(int v : arr){
        // maximum side
        if(v > largest){ secLarge = largest; largest = v; }
        else if(v < largest && v > secLarge) secLarge = v;

        // minimum side
        if(v < smallest){ secSmall = smallest; smallest = v; }
        else if(v > smallest && v < secSmall) secSmall = v;
    }
    return {secLarge, secSmall};
}
/*
TC - O(n), SC - O(1)

NOTE ON THE `else if` CONDITION: it needs BOTH halves.
    else if(v < largest && v > secLarge)
An element smaller than the largest can still be LARGER than the current second
largest - that is exactly the case that must update secLarge. Checking only
`v < largest` would overwrite secLarge with something smaller.

SENTINEL FIX: the original used secLarge = INT_MIN+1 and secSmall = INT_MAX-1.
Those offsets are unnecessary and actively harmful - if the true second largest
IS INT_MIN, the +1 sentinel already beats it. Use the plain extremes.

EDGE CASE: with fewer than 2 distinct values the sentinels come back unchanged
(INT_MIN / INT_MAX), which is your signal that no answer exists. Check for that
in the caller.
*/


/*
================================================================================
PROBLEM 4 : CHECK IF THE ARRAY IS SORTED
================================================================================
Compare every adjacent pair. One violation is enough to answer no.
*/

bool isSorted(vector<int>& arr){
    for(int i = 1; i < (int)arr.size(); i++){
        if(arr[i-1] > arr[i]) return false;   // early exit
    }
    return true;
}
// TC - O(n) worst case, O(1) best case (fails on the first pair)
// SC - O(1)
// Note `>` not `>=`: duplicates are allowed in a sorted array.
// STL equivalent: is_sorted(arr.begin(), arr.end())


/*
================================================================================
PROBLEM 5 : REMOVE DUPLICATES FROM A SORTED ARRAY
================================================================================
The array is SORTED, so duplicates are always ADJACENT. That is the property
every solution below exploits.

Return the new length; the first k positions hold the unique values.
*/

// ---- BRUTE: erase duplicates in place ----
void removeDupErase(vector<int>& arr){
    for(int i = 1; i < (int)arr.size(); i++){
        if(arr[i-1] == arr[i]){
            arr.erase(arr.begin() + i);
            i--;      // after erasing, everything shifts LEFT by one, so the
                       // next element now sits at index i. Without i-- the loop
                       // would skip it and miss runs of 3+ duplicates.
        }
    }
}
/*
TC - O(n^2), SC - O(1)

WHY O(n^2): vector::erase from the middle is O(n) because every element after
the removal point must shift left. Doing that up to n times gives O(n^2).

This is what motivates the optimal solution: instead of ERASING (which shifts),
OVERWRITE in place and resize once at the end.
*/

// ---- OPTIMAL: two pointers, overwrite instead of erase ----
int removeDupTwoPointer(vector<int>& arr){
    if(arr.empty()) return 0;

    int i = 0;                              // last index of the unique region
    for(int j = 1; j < (int)arr.size(); j++){
        if(arr[i] != arr[j]){
            arr[++i] = arr[j];               // extend the unique region
        }
        // equal -> skip; j moves on, i stays
    }
    arr.resize(i + 1);
    return i + 1;
}
/*
TC - O(n), SC - O(1)

TRACE on 1 1 2 2 2 3 4 4 5:

    i=0                       arr = 1 1 2 2 2 3 4 4 5
    j=1: arr[0]==arr[1]       skip
    j=2: differ -> i=1, arr[1]=2   ->  1 2 2 2 2 3 4 4 5
    j=3: arr[1]==arr[3]       skip
    j=4: arr[1]==arr[4]       skip
    j=5: differ -> i=2, arr[2]=3   ->  1 2 3 2 2 3 4 4 5
    j=6: differ -> i=3, arr[3]=4   ->  1 2 3 4 2 3 4 4 5
    j=7: arr[3]==arr[7]       skip
    j=8: differ -> i=4, arr[4]=5   ->  1 2 3 4 5 3 4 4 5

    resize(i+1) = resize(5)        ->  1 2 3 4 5

i marks the boundary of the answer; j scans ahead. Everything past i is garbage
until the resize discards it. This "slow pointer writes, fast pointer scans"
shape appears constantly - learn it once and you get move-zeros, remove-element,
and partition for free.

***** THIS ONLY WORKS ON SORTED INPUT *****
It relies on duplicates being ADJACENT. On unsorted input like 5 2 3 2 1 2 2 3
it removes only consecutive repeats and leaves the rest, producing 5 2 3 2 1 2 3.
For unsorted data either sort first (O(n log n)) or use a set.
*/

// ---- ALTERNATIVE: using a set ----
vector<int> removeDupSet(vector<int>& arr){
    set<int> s(arr.begin(), arr.end());      // sorted + unique
    return vector<int>(s.begin(), s.end());
}
/*
TC - O(n log n), SC - O(n)
Works on UNSORTED input and returns sorted output.
Swap to unordered_set for O(n) average, but the result is then unordered - and
it degrades to O(n^2) on hash collisions.
*/


/*
================================================================================
PROBLEM 6 : COUNT UNIQUE ELEMENTS
================================================================================
*/

// ---- BRUTE: for each element, look back to see if it appeared before ----
int countUniqueBrute(vector<int>& arr){
    int n = arr.size(), cnt = 0;
    for(int i = 0; i < n; i++){
        bool seen = false;
        for(int j = 0; j < i; j++){          // only look BACKWARDS
            if(arr[i] == arr[j]){ seen = true; break; }
        }
        if(!seen) cnt++;                      // count only the FIRST occurrence
    }
    return cnt;
}
/*
TC - O(n^2), SC - O(1)
Does NOT modify the input, which is the advantage over the erase-based version.

***** A REAL BUG IN THE ORIGINAL ERASE VERSION *****
The original counted duplicates by erasing them inside the inner loop:

        for(j=i+1; j<arr.size(); j++)
            if(arr[i]==arr[j]){ cnt--; arr.erase(arr.begin()+j); }

After an erase everything shifts LEFT, but j still increments - so the element
that moved INTO position j is never examined. Runs of 3+ duplicates are
undercounted.
VERIFIED BY TESTING on {1,1,1,2,3}: returned 4, correct answer is 3.
It also destroys the caller's array. Looking backwards with a flag avoids both
problems.
*/

// ---- BETTER: hash set ----
int countUniqueSet(vector<int>& arr){
    unordered_set<int> s(arr.begin(), arr.end());
    return s.size();
}
// TC - O(n) average (O(n^2) worst case on collisions), SC - O(n)

// ---- OPTIMAL for space: sort then two pointers ----
int countUniqueSorted(vector<int>& arr){
    if(arr.empty()) return 0;
    sort(arr.begin(), arr.end());
    int i = 0;
    for(int j = 1; j < (int)arr.size(); j++)
        if(arr[i] != arr[j]) arr[++i] = arr[j];
    return i + 1;
}
/*
TC - O(n log n), SC - O(1) auxiliary - but it MODIFIES the input (sorts it and
overwrites the front). If the caller still needs the original, that is not free.

CHOOSING BETWEEN THEM:
    input must be preserved, memory is tight   -> brute O(n^2)
    speed matters, memory available            -> hash set O(n)
    input may be modified, memory is tight     -> sort + two pointers
*/


/*
================================================================================
COMMON MISTAKES
================================================================================
  [X] return a, b;                   -> comma operator; only b is returned.
                                         Use pair<int,int> and return {a, b};
  [X] Sentinel -1 for "not found"    -> breaks on negative input; use INT_MIN
  [X] erase() inside a forward loop  -> elements shift left; either i-- or,
      without adjusting the index       better, avoid erase entirely
  [X] erase() in a loop at all       -> each erase is O(n) -> O(n^2) overall;
                                         overwrite and resize once instead
  [X] Applying the sorted two-pointer-> it only removes ADJACENT duplicates
      dedup to unsorted data
  [X] Forgetting `arr[i] < largest`  -> a duplicate of the max would overwrite
      in the second-largest check       the second largest
  [X] Not handling n < 2             -> arr[0] on an empty vector is UB
================================================================================
*/


int main(){
    int n;
    cin >> n;
    vector<int> arr(n);
    for(int i = 0; i < n; i++) cin >> arr[i];

    if(n == 0){ cout << "empty array\n"; return 0; }

    cout << "Largest: " << largestElement(arr) << endl;

    auto p = largestAndSecondLargest(arr);
    cout << "Largest: " << p.first;
    if(p.second == INT_MIN) cout << "  Second largest: none (all values equal)";
    else                    cout << "  Second largest: " << p.second;
    cout << endl;

    cout << "Sorted? " << (isSorted(arr) ? "yes" : "no") << endl;
    cout << "Unique count: " << countUniqueBrute(arr) << endl;

    return 0;
}