#include<bits/stdc++.h>
using namespace std;

/*
================================================================================
        ARRAYS - PART 3 : MISSING NUMBERS, COUNTING, AND THE XOR TRICK
================================================================================
This file is where XOR earns its place. Three properties do all the work:

    a ^ a = 0          anything XORed with itself cancels
    a ^ 0 = a          XOR with zero changes nothing
    XOR is commutative and associative - order does not matter

Together: XOR everything, and any value appearing an EVEN number of times
vanishes, leaving only what appeared an odd number of times.

TABLE OF CONTENTS
-----------------
  PROBLEM 1 : Find the missing number (one missing from 1..n)
  PROBLEM 2 : Find a whole missing sequence
  PROBLEM 3 : Maximum consecutive 1s
  PROBLEM 4 : Element appearing once (all others twice)
  PROBLEM 5 : Elements appearing once vs twice
  PROBLEM 6 : TWO elements appearing once (all others twice)
  NOTES     : Common mistakes

================================================================================
PROBLEM 1 : FIND THE MISSING NUMBER
================================================================================
The array holds n distinct numbers from the range 1..n+1, with exactly one
missing.
    [1, 2, 4, 5]  ->  3     (n=4, range 1..5)
*/

// ---- BRUTE 1: sort, then find the first index that does not match ----
int missingSortBrute(vector<int> arr){
    sort(arr.begin(), arr.end());
    for(int i = 0; i < (int)arr.size(); i++)
        if(arr[i] != i + 1) return i + 1;
    return arr.size() + 1;                    // the missing one is the last
}
// TC - O(n log n), SC - O(1)
// arr taken BY VALUE so the caller's array is not reordered.

// ---- BRUTE 2: for each candidate, linear-search the array ----
int missingSearchBrute(vector<int>& arr){
    int n = arr.size();
    for(int target = 1; target <= n + 1; target++){
        bool found = false;
        for(int v : arr) if(v == target){ found = true; break; }
        if(!found) return target;
    }
    return -1;
}
// TC - O(n^2) worst case, O(n) best (when 1 is the missing one).  SC - O(1)

// ---- BETTER: hashing ----
int missingHash(vector<int>& arr){
    int n = arr.size();
    vector<int> hash(n + 2, 0);               // indices 0..n+1
    for(int v : arr) hash[v] = 1;
    for(int i = 1; i <= n + 1; i++)
        if(hash[i] == 0) return i;
    return -1;
}
// TC - O(2n) = O(n), SC - O(n)
// Note the size is n+2, not n+1: the largest possible value is n+1, and indices
// run 0..n+1, which is n+2 slots.

// ---- OPTIMAL 1: sum formula ----
int missingSum(vector<int>& arr){
    int n = arr.size();
    long long expected = (long long)(n + 1) * (n + 2) / 2;   // sum of 1..n+1
    long long actual = 0;
    for(int v : arr) actual += v;
    return (int)(expected - actual);
}
/*
TC - O(n), SC - O(1)

USE long long FOR THE SUMS. With n = 10^5 the expected sum is about 5*10^9,
which overflows a 32-bit int (max ~2.1*10^9). This is the practical weakness of
the sum method and the reason XOR is often preferred.
*/

// ---- OPTIMAL 2: XOR (no overflow risk) ----
int missingXor(vector<int>& arr){
    int n = arr.size();
    int xorArr = 0, xorRange = 0;

    for(int v : arr) xorArr ^= v;             // XOR of what IS present
    for(int i = 1; i <= n + 1; i++) xorRange ^= i;   // XOR of 1..n+1

    return xorArr ^ xorRange;
}
/*
TC - O(n), SC - O(1)

WHY IT WORKS - array {2,3,4,5}, range 1..5:
    xorArr   = 2^3^4^5
    xorRange = 1^2^3^4^5
    result   = (2^2)^(3^3)^(4^4)^(5^5)^1 = 0^0^0^0^1 = 1

Every value present in BOTH cancels itself out. Only the missing one survives.

XOR BEATS THE SUM METHOD because intermediate values never grow - XOR of numbers
up to n stays bounded by n, so there is no overflow to worry about at any size.

***** AN OPERATOR-PRECEDENCE BUG WORTH KNOWING *****
The original wrote a guard as:

        if(a^b == (arr.size()+1)) return -1;

In C++, == binds TIGHTER than ^, so this parses as  a ^ (b == size+1)  - it
compares b to the size, gets 0 or 1, and XORs that into a. The result is an
arbitrary number, and it is used as a condition.
VERIFIED BY TESTING with a=6, b=3, x=5:
    (a^b)==x  ->  1     (true, correct)
     a^b==x   ->  6     (parsed as a^(b==x))
ALWAYS parenthesise: (a ^ b) == x.
Most bitwise operators sit LOWER than comparison in C++'s precedence table -
this catches people constantly.
*/


/*
================================================================================
PROBLEM 2 : FIND A WHOLE MISSING SEQUENCE
================================================================================
Generalisation: more than one number may be missing. Report all of them.
    [1, 2, 3, 6, 7, 8]  ->  4, 5
*/

vector<int> missingSequence(vector<int> arr){
    sort(arr.begin(), arr.end());
    vector<int> missing;
    int expected = 1;

    for(int v : arr){
        while(expected < v) missing.push_back(expected++);   // fill the gap
        expected = v + 1;
    }
    return missing;
}
/*
TC - O(n log n + k) where k = how many numbers are missing.  SC - O(k)

The while loop is what handles a RUN of missing values rather than just one.
`expected = v + 1` (rather than expected++) also makes it safe against
duplicates in the input.
*/


/*
================================================================================
PROBLEM 3 : MAXIMUM CONSECUTIVE 1s
================================================================================
    1 1 0 1 1 1 0   ->   3

There is no brute/better/optimal ladder here - one pass is already optimal.
*/

int maxConsecutiveOnes(vector<int>& arr){
    int count = 0, maxCount = 0;
    for(int v : arr){
        if(v == 1){
            count++;
            maxCount = max(maxCount, count);
        } else {
            count = 0;                         // the run is broken - reset
        }
    }
    return maxCount;
}
/*
TC - O(n), SC - O(1)

The pattern: a running counter that RESETS on a break, and a separate maximum
that only ever grows. Updating maxCount inside the if (rather than after the
loop) means you never miss a run that ends at the last element.
*/


/*
================================================================================
PROBLEM 4 : ELEMENT APPEARING ONCE, ALL OTHERS TWICE
================================================================================
    [4, 1, 2, 1, 2]  ->  4

This is XOR's showcase problem.
*/

int appearsOnce(vector<int>& arr){
    int result = 0;                            // MUST be initialised to 0
    for(int v : arr) result ^= v;
    return result;
}
/*
TC - O(n), SC - O(1)

Every value that appears twice XORs itself to 0. Everything cancels except the
lone element. Order does not matter, so the array need not be sorted.

***** A REAL BUG IN THE ORIGINAL *****
It declared `int xor1;` with no initialiser, then did `xor1 ^= arr[i]`.
Reading an uninitialised variable is UNDEFINED BEHAVIOUR - the starting value is
whatever garbage was on the stack, and the answer is silently wrong.
VERIFIED BY TESTING on {4,1,2,1,2}: returned 1 instead of 4.
It must start at 0, because 0 is XOR's identity element (0 ^ a = a).
*/


/*
================================================================================
PROBLEM 5 : ELEMENTS APPEARING ONCE vs TWICE
================================================================================
Report every element that appears exactly once, and every element that appears
exactly twice. (More general than Problem 4, so XOR alone is not enough.)
*/

// ---- BRUTE: count each element by scanning the whole array ----
pair<vector<int>, vector<int>> onceAndTwiceBrute(vector<int>& arr){
    int n = arr.size();
    set<int> once, twice;                      // set avoids reporting a value
                                                // twice; also keeps output sorted
    for(int i = 0; i < n; i++){
        int count = 0;
        for(int j = 0; j < n; j++) if(arr[i] == arr[j]) count++;
        if(count == 1)      once.insert(arr[i]);
        else if(count == 2) twice.insert(arr[i]);
    }
    return {vector<int>(once.begin(), once.end()),
            vector<int>(twice.begin(), twice.end())};
}
/*
TC - O(n^2), SC - O(k)

USING A SET, NOT A VECTOR: an element appearing twice is found twice by the
outer loop, so a vector would list it twice. The original worked around this
with an extra hash array - a set expresses the intent directly.

The original's hash-array workaround also had an out-of-bounds bug:
    vector<int> hashArr(maxi);      // indices 0..maxi-1
    ...
    hashArr[arr[i]] = 1;             // writes at index maxi when arr[i]==maxi
Sizing by max VALUE always needs maxi+1 slots, because indices start at 0.
*/

// ---- BETTER: frequency map ----
pair<vector<int>, vector<int>> onceAndTwiceMap(vector<int>& arr){
    map<int,int> freq;                         // map = sorted output for free
    for(int v : arr) freq[v]++;

    vector<int> once, twice;
    for(auto& [value, count] : freq){
        if(count == 1)      once.push_back(value);
        else if(count == 2) twice.push_back(value);
    }
    return {once, twice};
}
/*
TC - O(n log n) with map, O(n) average with unordered_map.  SC - O(k)

`freq[v]++` needs no "does the key exist" check: operator[] default-constructs
the value to 0 for a missing key, then ++ makes it 1. That is exactly the
insert-or-update behaviour you want here.

But be careful with the same operator elsewhere - a plain READ like
`cout << freq[x];` also INSERTS x with value 0 if it was absent, silently
growing the map. Use freq.count(x) or freq.find(x) when you only mean to look.
*/

// ---- Frequency by hash array, when values are small ----
pair<vector<int>, vector<int>> onceAndTwiceHash(vector<int>& arr){
    int maxi = *max_element(arr.begin(), arr.end());
    vector<int> hash(maxi + 1, 0);             // +1 - indices run 0..maxi
    for(int v : arr) hash[v]++;

    vector<int> once, twice;
    for(int i = 0; i <= maxi; i++){            // <=, not <
        if(hash[i] == 1)      once.push_back(i);
        else if(hash[i] == 2) twice.push_back(i);
    }
    return {once, twice};
}
/*
TC - O(n + maxi), SC - O(maxi)

CHOOSING BETWEEN HASH ARRAY AND MAP: the hash array is faster but its memory
scales with the largest VALUE, not the element count. {1, 5, 1000000000} would
need a billion slots. Use it when values are small and dense; use a map when
they are large or sparse.

Two off-by-ones fixed here, both from the original: the array must be maxi+1
long, and the output loop must run to i <= maxi to inspect the last slot.
*/


/*
================================================================================
PROBLEM 6 : TWO ELEMENTS APPEAR ONCE, ALL OTHERS TWICE
================================================================================
    [1, 2, 1, 3, 2, 5]  ->  3 and 5

XORing everything gives  a ^ b  (the two loners combined) - but that does not
separate them. The trick is to SPLIT the array into two groups such that a and b
land in different groups, then XOR each group independently.
*/

pair<int,int> twoAppearOnce(vector<int>& arr){
    long long xorAll = 0;
    for(int v : arr) xorAll ^= v;              // = a ^ b

    // isolate the RIGHTMOST set bit of (a^b)
    int bit = xorAll & (-xorAll);

    int groupA = 0, groupB = 0;
    for(int v : arr){
        if(v & bit) groupA ^= v;               // bit is set
        else        groupB ^= v;               // bit is clear
    }
    return {groupA, groupB};
}
/*
TC - O(n), SC - O(1)

WHY IT WORKS, step by step:

  1. xorAll = a ^ b. Every twice-appearing value cancels.
  2. a != b, so xorAll != 0, so it has at least one set bit. A set bit in a^b
     means a and b DIFFER at that bit position - one has 0 there, the other 1.
  3. Partition the array by that bit. a and b are guaranteed to land in
     different groups. Every duplicate pair lands in the SAME group (identical
     values have identical bits), so each group cancels down to exactly one
     loner.

WHY  x & (-x)  ISOLATES THE RIGHTMOST SET BIT: in two's complement, -x is
~x + 1. Flipping all bits and adding one leaves every bit below the rightmost
set bit as 0, that bit as 1, and inverts everything above it. ANDing with the
original therefore keeps only that one bit.

    x  = 0b101100
    -x = 0b010100
    x & -x = 0b000100      <- the rightmost set bit, isolated

Any set bit would work; the rightmost is just the cheapest to extract.
*/


/*
================================================================================
COMMON MISTAKES
================================================================================
  [X] int x;  then  x ^= ...          -> uninitialised read = undefined
                                          behaviour. VERIFIED to give the wrong
                                          answer. XOR accumulators start at 0
  [X] a ^ b == c                       -> parses as a ^ (b == c). == binds
                                          tighter than ^. Parenthesise: (a^b)==c
  [X] Sum formula in int               -> n=10^5 gives ~5*10^9, overflowing a
                                          32-bit int; use long long, or XOR
  [X] Hash array sized maxi            -> needs maxi+1 slots; indices are 0..maxi
  [X] Loop to i < maxi                 -> misses the last slot; use i <= maxi
  [X] Sizing a value-indexed hash by n -> size by the maximum VALUE, not the
                                          element count
  [X] Vector output for "appears twice"-> each such element is found twice by an
                                          O(n^2) scan; use a set
  [X] Reading map[key] just to check    -> operator[] INSERTS missing keys; use
      presence                            count() or find() for a pure lookup
  [X] Expecting plain XOR to solve the  -> XOR alone gives a^b; you must split
      two-loners case                     by a differing bit first
================================================================================
*/


int main(){
    int n;
    cin >> n;
    vector<int> arr(n);
    for(int i = 0; i < n; i++) cin >> arr[i];

    cout << "Max consecutive 1s: " << maxConsecutiveOnes(arr) << endl;

    auto [once, twice] = onceAndTwiceMap(arr);
    cout << "Appears once:  ";
    for(int v : once) cout << v << " ";
    cout << endl;
    cout << "Appears twice: ";
    for(int v : twice) cout << v << " ";
    cout << endl;

    return 0;
}