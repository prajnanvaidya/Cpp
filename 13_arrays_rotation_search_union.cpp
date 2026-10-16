#include<bits/stdc++.h>
using namespace std;

/*
================================================================================
        ARRAYS - PART 2 : ROTATION, PARTITIONING, SEARCH, SET OPERATIONS
================================================================================

TABLE OF CONTENTS
-----------------
  PROBLEM 1 : Left rotate by 1 place
  PROBLEM 2 : Left rotate by D places
  PROBLEM 3 : Right rotate by D places
  PROBLEM 4 : Move all zeros to the end
  PROBLEM 5 : Linear search
  PROBLEM 6 : Union of two sorted arrays
  PROBLEM 7 : Intersection of two sorted arrays
  NOTES     : The reversal trick, and common mistakes

================================================================================
PROBLEM 1 : LEFT ROTATE BY 1 PLACE
================================================================================
    1 2 3 4   ->   2 3 4 1

Every element moves one slot left; the first element wraps to the end.
*/

void leftRotateByOne(vector<int>& arr){
    if(arr.empty()) return;
    int n = arr.size();
    int temp = arr[0];                       // save the element that wraps
    for(int i = 1; i < n; i++) arr[i-1] = arr[i];
    arr[n-1] = temp;
}
/*
TC - O(n), SC - O(1)

A NOTE ON "O(1) SPACE": the array itself is O(n), but that is the INPUT. Space
complexity by convention means AUXILIARY space - the extra memory the algorithm
allocates on top of the input. Here that is one int, so O(1).

An alternative using repeated swaps does the same thing:
    for(int i=0; i<n-1; i++) swap(arr[i], arr[i+1]);
It works, but does 3 assignments per step instead of 1. Prefer the shift.
*/


/*
================================================================================
PROBLEM 2 : LEFT ROTATE BY D PLACES
================================================================================
    1 2 3 4, d=2   ->   3 4 1 2

FIRST, ALWAYS REDUCE d:  rotating by n returns the original array, so only
d % n matters. Skipping this makes d = 10^9 take forever for no reason.

    1 2 3 4  ->  2 3 4 1 (d=1)  ->  3 4 1 2 (d=2)  ->  4 1 2 3 (d=3)  ->
    1 2 3 4 (d=4, back to the start)
*/

// ---- BRUTE: rotate by one, d times ----
void leftRotateBrute(vector<int>& arr, int d){
    if(arr.empty()) return;
    int n = arr.size();
    d %= n;
    for(int r = 0; r < d; r++) leftRotateByOne(arr);
}
// TC - O(n * d), worst case O(n^2) when d ~ n.  SC - O(1)

// ---- BETTER: save the first d elements, shift, put them back ----
void leftRotateBetter(vector<int>& arr, int d){
    if(arr.empty()) return;
    int n = arr.size();
    d %= n;
    if(d == 0) return;

    vector<int> temp(arr.begin(), arr.begin() + d);   // save the first d
    for(int i = d; i < n; i++) arr[i - d] = arr[i];    // shift the rest left
    for(int i = 0; i < d; i++) arr[n - d + i] = temp[i];  // append the saved d
}
/*
TC - O(n), SC - O(d)

This is a clean rewrite of two attempts in the original notes:

  - One version ran the whole shift loop d times inside an outer loop, giving
    O(n*d) - it saved the elements but not the work.
  - Another tried to place elements directly with `arr[i] = arr[k+i]`, which
    goes OUT OF BOUNDS as soon as k+i exceeds n-1. The original notes spotted
    this ("problem is when k=n-1... if index goes out of bound bring it back"),
    and the fix is modular arithmetic - but by then the reversal method below is
    simpler and uses no extra memory at all.
*/

// ---- OPTIMAL: the reversal trick ----
void leftRotateOptimal(vector<int>& arr, int d){
    if(arr.empty()) return;
    int n = arr.size();
    d %= n;

    reverse(arr.begin(), arr.begin() + d);    // reverse the first d
    reverse(arr.begin() + d, arr.end());      // reverse the rest
    reverse(arr.begin(), arr.end());          // reverse the whole thing
}
/*
TC - O(d) + O(n-d) + O(n) = O(2n) = O(n),  SC - O(1)

WHY IT WORKS - trace 1 2 3 4 5 6 7 with d=3:

    start                        1 2 3 | 4 5 6 7
    reverse first d              3 2 1 | 4 5 6 7
    reverse the rest             3 2 1 | 7 6 5 4
    reverse everything           4 5 6 7 | 1 2 3      <- rotated left by 3

The first two reversals put each block in backwards order; the final full
reversal un-reverses both blocks AND swaps their positions. Reversing twice
restores order, and the outer reversal is what moves the blocks past each other.

Same O(n) time as the "better" version, but O(1) space instead of O(d). This is
the answer to give in an interview.
*/


/*
================================================================================
PROBLEM 3 : RIGHT ROTATE BY D PLACES
================================================================================
    1 2 3 4 5, d=2   ->   4 5 1 2 3

Same reversal trick, with the split point mirrored: instead of splitting after
the first d, split after the first (n-d).
*/

void rightRotateOptimal(vector<int>& arr, int d){
    if(arr.empty()) return;
    int n = arr.size();
    d %= n;
    if(d == 0) return;

    reverse(arr.end() - d, arr.end());              // reverse the LAST d
    reverse(arr.begin(), arr.end() - d);            // reverse the first n-d
    reverse(arr.begin(), arr.end());                // reverse everything
}
/*
TC - O(n), SC - O(1)

USEFUL EQUIVALENCE: rotating RIGHT by d is the same as rotating LEFT by (n-d).
So you can implement one and call it from the other:
    void rightRotate(vector<int>& a, int d){ leftRotateOptimal(a, a.size() - d % a.size()); }
*/

// ---- Simple non-optimal alternative, worth knowing ----
void rightRotateSimple(vector<int>& arr, int d){
    if(arr.empty()) return;
    int n = arr.size();
    d %= n;
    if(d == 0) return;
    arr.insert(arr.begin(), arr.end() - d, arr.end());  // copy tail to front
    arr.resize(n);                                        // drop the overflow
}
/*
TC - O(n), SC - O(n)
Short and readable, but insert at begin() shifts everything and the temporary
growth means real extra memory. Note: SC is O(n), not O(1) - inserting at the
front of a vector reallocates. The original notes listed this as O(1), which
misses the reallocation.
*/


/*
================================================================================
PROBLEM 4 : MOVE ALL ZEROS TO THE END
================================================================================
    1 0 2 3 0 6   ->   1 2 3 6 0 0
The relative order of the NON-ZERO elements must be preserved.
*/

// ---- BRUTE: for each zero, find the next non-zero and swap ----
void moveZerosBrute(vector<int>& arr){
    int n = arr.size();
    int zeros = count(arr.begin(), arr.end(), 0);

    for(int i = 0; i < n - zeros; i++){
        if(arr[i] == 0){
            for(int j = i + 1; j < n; j++){
                if(arr[j] != 0){ swap(arr[i], arr[j]); break; }
            }
        }
    }
}
/*
TC - O(n^2) worst case, SC - O(1)
The `n - zeros` bound is a genuine optimisation: once you reach the region that
will hold only zeros, there is nothing left to pull forward.
*/

// ---- BETTER: copy non-zeros to a temp, write back, pad with zeros ----
void moveZerosTemp(vector<int>& arr){
    int n = arr.size();
    vector<int> temp;
    for(int v : arr) if(v != 0) temp.push_back(v);

    for(int i = 0; i < n; i++)
        arr[i] = (i < (int)temp.size()) ? temp[i] : 0;
}
// TC - O(2n) = O(n), SC - O(n) worst case (no zeros at all)

// ---- OPTIMAL: two pointers ----
void moveZerosOptimal(vector<int>& arr){
    int n = arr.size();

    int j = -1;                              // index of the FIRST zero
    for(int i = 0; i < n; i++){
        if(arr[i] == 0){ j = i; break; }
    }
    if(j == -1) return;                      // no zeros at all - already done

    for(int i = j + 1; i < n; i++){
        if(arr[i] != 0){
            swap(arr[i], arr[j]);
            j++;
        }
    }
}
/*
TC - O(n), SC - O(1)

HOW IT WORKS: j always points at the LEFTMOST zero. Whenever i finds a non-zero,
swapping sends that value back to j (where it belongs) and pushes the zero
forward to position i. Advancing j then lands it on the NEXT zero, because
everything between the old j and i was already zero.

TRACE on 1 0 0 2 0 4:

    j=1 (first zero), i=2
    i=2: arr[2]=0, skip
    i=3: arr[3]=2 -> swap(3,1) -> 1 2 0 0 0 4, j=2
    i=4: arr[4]=0, skip
    i=5: arr[5]=4 -> swap(5,2) -> 1 2 4 0 0 0, j=3
    done

The first swap is obvious; the later ones look mysterious until you notice they
are simultaneously pulling non-zeros forward AND pushing the accumulated block
of zeros rightward.

FIX vs THE ORIGINAL: it initialised `int j = n` when no zero was found, then
started the loop at i = j+1 = n+1. The loop never runs, so it works by accident -
but j = n is a valid-looking index that is actually out of range. Using -1 with
an explicit early return states the intent and cannot be misread.

SIMPLER EQUIVALENT (same complexity, fewer moving parts):
    int j = 0;
    for(int i = 0; i < n; i++)
        if(arr[i] != 0) swap(arr[i], arr[j++]);
Here j is "where the next non-zero goes" rather than "the first zero". Both are
correct; this one needs no pre-scan.
*/


/*
================================================================================
PROBLEM 5 : LINEAR SEARCH
================================================================================
*/

int linearSearch(vector<int>& arr, int key){
    for(int i = 0; i < (int)arr.size(); i++)
        if(arr[i] == key) return i;           // return the INDEX
    return -1;                                 // not found
}
/*
TC - O(n) worst, O(1) best.  SC - O(1)

Return the index, not index+1. Returning a 1-based position (as the original
did) is a needless inconsistency with C++'s 0-based world and invites off-by-one
bugs at the call site.

If the array is SORTED, use binary search instead - O(log n).
*/


/*
================================================================================
PROBLEM 6 : UNION OF TWO SORTED ARRAYS
================================================================================
    a = 1 1 2 3 4 5
    b = 2 3 4 4 5 6
    union = 1 2 3 4 5 6          (sorted, NO duplicates)
*/

// ---- BRUTE: concatenate, sort, dedup ----
vector<int> unionBrute(vector<int> a, vector<int> b){
    a.insert(a.end(), b.begin(), b.end());
    sort(a.begin(), a.end());
    a.erase(unique(a.begin(), a.end()), a.end());   // erase-remove idiom
    return a;
}
// TC - O((n+m) log(n+m)), SC - O(n+m)
// Works even if the inputs are NOT sorted.

// ---- BETTER: use a set ----
vector<int> unionSet(vector<int>& a, vector<int>& b){
    set<int> s(a.begin(), a.end());
    s.insert(b.begin(), b.end());
    return vector<int>(s.begin(), s.end());
}
/*
TC - O((n+m) log(n+m)), SC - O(n+m)
set gives sorted+unique for free. unordered_set would be O(n+m) average but the
result needs sorting afterwards, which puts the log back.
*/

// ---- OPTIMAL: two pointers on the already-sorted inputs ----
vector<int> unionOptimal(vector<int>& a, vector<int>& b){
    int n = a.size(), m = b.size();
    vector<int> result;
    int i = 0, j = 0;

    while(i < n && j < m){
        if(a[i] <= b[j]){
            if(result.empty() || result.back() != a[i]) result.push_back(a[i]);
            i++;
        } else {
            if(result.empty() || result.back() != b[j]) result.push_back(b[j]);
            j++;
        }
    }
    while(i < n){                              // drain whichever side is left
        if(result.empty() || result.back() != a[i]) result.push_back(a[i]);
        i++;
    }
    while(j < m){
        if(result.empty() || result.back() != b[j]) result.push_back(b[j]);
        j++;
    }
    return result;
}
/*
TC - O(n+m), SC - O(number of unique elements), worst case O(n+m)

THE DEDUP TRICK: because both inputs are sorted, the result is built in sorted
order too - so any duplicate must equal the element just pushed. Comparing
against result.back() is enough; no set or lookup needed.

***** A SEVERE BUG IN THE ORIGINAL *****
The original's tail-drain loop read:

        else if(j >= n2){
            while(i < n2){ ... i++; }        // <-- n2 instead of n1
        }

It bounds a's index by b's LENGTH. If a is longer than b, most of a is silently
dropped.
VERIFIED BY TESTING with a = 1..9 (9 elements) and b = {1,2}:
    returned  : 1 2
    expected  : 1 2 3 4 5 6 7 8 9
Seven elements vanished. The version above avoids the whole class of bug by
using two unconditional drain loops - after the main loop at most one of them
can run, so no `if` is needed at all.

The original also indexed result[count] with a manually tracked counter, which
must stay in sync with the vector's size. result.back() cannot desynchronise.
*/


/*
================================================================================
PROBLEM 7 : INTERSECTION OF TWO SORTED ARRAYS
================================================================================
    a = 1 2 2 3 6
    b = 2 2 4 6
    intersection = 2 2 6

Note the definition: an element appears in the result as many times as it appears
in BOTH arrays - min(count in a, count in b). Each match consumes one occurrence
from each side.
*/

// ---- BRUTE: for each element of a, find and consume a match in b ----
vector<int> intersectionBrute(vector<int> a, vector<int> b){
    vector<int> result;
    for(int i = 0; i < (int)a.size(); i++){
        for(int j = 0; j < (int)b.size(); j++){
            if(a[i] == b[j]){
                result.push_back(a[i]);
                b.erase(b.begin() + j);        // consume it so it can't rematch
                break;
            }
            if(b[j] > a[i]) break;              // sorted -> no match possible
        }
    }
    return result;
}
/*
TC - O(n*m), SC - O(min(n,m)) for the result
`b` is taken BY VALUE deliberately - erasing from it must not damage the
caller's array.

An alternative brute keeps a visited[] array over b instead of erasing, which
avoids the O(m) shift per erase. The original's version of that returned
nothing at all (declared `auto` with no return statement), which does not
compile.
*/

// ---- OPTIMAL: two pointers ----
vector<int> intersectionOptimal(vector<int>& a, vector<int>& b){
    int n = a.size(), m = b.size();
    vector<int> result;
    int i = 0, j = 0;

    while(i < n && j < m){
        if(a[i] < b[j])      i++;              // a's value is too small
        else if(a[i] > b[j]) j++;              // b's value is too small
        else { result.push_back(a[i]); i++; j++; }   // match - consume BOTH
    }
    return result;
}
/*
TC - O(n+m), SC - O(k) where k = size of the result

Advancing BOTH pointers on a match is what produces the min-frequency behaviour:
each occurrence on either side can only be matched once.

VARIANT - if you want NO duplicates in the result, guard the push:
    if(result.empty() || result.back() != a[i]) result.push_back(a[i]);
*/

// ---- Hash-based, for UNSORTED input ----
vector<int> intersectionUnsorted(vector<int>& a, vector<int>& b){
    unordered_set<int> s(a.begin(), a.end());
    vector<int> result;
    for(int v : b)
        if(s.erase(v))                          // erase returns 1 if it removed
            result.push_back(v);
    return result;
}
/*
TC - O(n+m) average, SC - O(n)

erase(v) doubles as "is it present?" and "consume it" in one call, so each value
is reported at most once. This gives DISTINCT common elements, not
min-frequency - a different definition from the two-pointer version, so pick the
one the problem asks for.
*/


/*
================================================================================
COMMON MISTAKES
================================================================================
  [X] Forgetting d %= n              -> pointless work when d > n; O(n*d) blowup
  [X] Bounding one array's loop by   -> silently drops elements. VERIFIED: the
      the OTHER array's length          original union lost 7 of 9 values
  [X] Tracking result size with a    -> can desynchronise from the vector;
      manual counter                    use .back() and .empty() instead
  [X] Modifying a by-value parameter -> harmless, but modifying a by-REFERENCE
      and expecting the caller to see    one when the caller expects its data
      it (or the reverse)                intact is a real bug
  [X] Claiming insert-at-begin is    -> it shifts everything and can reallocate;
      O(1) space                        that is O(n)
  [X] Using j = n as "no zero found" -> a valid-looking out-of-range index;
                                         use -1 and return early
  [X] Returning index+1 from search  -> C++ is 0-based; return the index or -1
  [X] Applying two-pointer union or  -> both REQUIRE sorted input
      intersection to unsorted input
================================================================================
*/


int main(){
    int n, m;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    cin >> m;
    vector<int> b(m);
    for(int i = 0; i < m; i++) cin >> b[i];

    auto u = unionOptimal(a, b);
    cout << "Union:        ";
    for(int v : u) cout << v << " ";
    cout << endl;

    auto in = intersectionOptimal(a, b);
    cout << "Intersection: ";
    for(int v : in) cout << v << " ";
    cout << endl;

    return 0;
}