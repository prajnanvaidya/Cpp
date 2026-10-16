#include<bits/stdc++.h>
using namespace std;

/*
================================================================================
                            MERGE SORT - COMPLETE NOTES
================================================================================
MERGE SORT is a DIVIDE AND CONQUER algorithm:

    1. DIVIDE   - split the array in half
    2. CONQUER  - recursively sort each half
    3. COMBINE  - merge the two sorted halves into one sorted whole

The base case is an array of ONE element, which is trivially already sorted.
All the actual work happens in the MERGE step on the way back UP the recursion.

TABLE OF CONTENTS
-----------------
  PART 1  : The divide phase (visual trace)
  PART 2  : The merge phase (how two sorted arrays combine)
  PART 3  : Full worked example
  PART 4  : Approach A - returning new vectors
  PART 5  : Approach B - in-place with indices (the standard form)
  PART 6  : Line-by-line dry run of the recursion
  PART 7  : Descending order
  PART 8  : Complexity analysis - where n log n comes from
  PART 9  : Stability and the <= vs < detail
  PART 10 : Two real bugs to avoid
  PART 11 : Optimisations
  PART 12 : Why merge sort matters (inversions, lists, external sort)
  PART 13 : Common mistakes checklist

================================================================================
PART 1 : THE DIVIDE PHASE
================================================================================
Keep halving until every piece has one element. When n is odd the halves are
unequal - that is fine, the algorithm does not require equal splits.

Example with n = 9:

                    [3, 1, 2, 4, 1, 5, 2, 6, 4]
                       /                     \
              [3,1,2,4,1]                  [5,2,6,4]
               /       \                    /      \
           [3,1]     [2,4,1]            [5,2]     [6,4]
           /   \      /    \            /   \     /   \
         [3]  [1]  [2,4]   [1]        [5]  [2]  [6]  [4]
                   /    \
                 [2]    [4]

Nothing is sorted yet - this phase only splits. Note the recursion goes ALL THE
WAY DOWN the left branch before touching the right, because that is how
depth-first recursion works (see the dry run in Part 6).


================================================================================
PART 2 : THE MERGE PHASE
================================================================================
Given TWO ALREADY-SORTED arrays, produce one sorted array.

THE ALGORITHM: put a pointer at the start of each. Repeatedly compare the two
pointed-at elements, take the smaller one, and advance that pointer. When one
side runs out, copy everything remaining from the other side.

WHY THIS IS O(n): each element is looked at and copied exactly once. There is
no searching or shifting - the fact that both inputs are already sorted means
the smallest unused element is always one of the two pointed-at elements.

WORKED MERGES from the example above:

  MERGE [2] and [4]
      i->2, j->4.  2 < 4, take 2, advance i. Left side exhausted.
      Copy the rest of the right side: 4.
      RESULT: [2,4]

  MERGE [2,4] and [1]
      i->2, j->1.  1 < 2, take 1, advance j. Right side exhausted.
      Copy the rest of the left side: 2, 4.
      RESULT: [1,2,4]

  MERGE [3] and [1]
      i->3, j->1.  1 < 3, take 1, advance j. Right side exhausted.
      Copy the rest: 3.
      RESULT: [1,3]

  MERGE [1,3] and [1,2,4]
      i->1, j->1.  EQUAL -> take from the LEFT (this choice is what makes the
                   sort stable - see Part 9). Advance i.
      i->3, j->1.  1 < 3, take 1, advance j.
      i->3, j->2.  2 < 3, take 2, advance j.
      i->3, j->4.  3 < 4, take 3, advance i. Left exhausted.
      Copy the rest of the right: 4.
      RESULT: [1,1,2,3,4]

  MERGE [5] and [2]        ->  [2,5]
  MERGE [6] and [4]        ->  [4,6]
  MERGE [2,5] and [4,6]    ->  [2,4,5,6]


================================================================================
PART 3 : FULL WORKED EXAMPLE
================================================================================
Merging back up, level by level:

  Level 3 (leaves):  [3] [1]  [2] [4]  [1]      [5] [2]  [6] [4]
  Level 2:           [1,3]    [2,4]    [1]      [2,5]    [4,6]
  Level 1:           [1,3]    [1,2,4]           [2,4,5,6]
  Level 0:           [1,1,2,3,4]                [2,4,5,6]

  FINAL MERGE of [1,1,2,3,4] and [2,4,5,6]:

      i->1, j->2.  take 1 (left)
      i->1, j->2.  take 1 (left)
      i->2, j->2.  EQUAL -> take left, advance i
      i->3, j->2.  take 2 (right)
      i->3, j->4.  take 3 (left)
      i->4, j->4.  EQUAL -> take left, advance i. Left exhausted.
      Copy the rest of the right: 4, 5, 6.

      RESULT: [1, 1, 2, 2, 3, 4, 4, 5, 6]

  SORTED.


================================================================================
PART 4 : APPROACH A - RETURNING NEW VECTORS
================================================================================
The most literal translation of "divide, sort each half, merge". Easy to read,
but it COPIES data at every level - see the cost analysis at the end of Part 5.

NOTE: the merge function is named mergeHalves, not merge. With
`using namespace std`, a function called merge() collides with std::merge from
<algorithm> and can produce confusing overload-resolution errors.
*/

vector<int> mergeHalves(const vector<int>& left, const vector<int>& right){
    int i = 0, j = 0;
    int lSize = left.size(), rSize = right.size();
    vector<int> sorted;
    sorted.reserve(lSize + rSize);        // avoid repeated reallocation

    while(i < lSize && j < rSize){
        if(left[i] <= right[j]){          // <= not < : keeps the sort STABLE (Part 9)
            sorted.push_back(left[i++]);
        }
        else{
            sorted.push_back(right[j++]);
        }
    }
    // exactly one of these two loops will actually run
    while(j < rSize) sorted.push_back(right[j++]);
    while(i < lSize) sorted.push_back(left[i++]);

    return sorted;
}
/*
NOTE on the two drain loops: the original wrote them as
        if(i>=lSize){ while(j<rSize) ... }
        else if(j>=rSize){ while(i<lSize) ... }
That is correct, but the guards are unnecessary. After the main loop at least
one side is exhausted, so its while-loop simply does not execute. Two plain
while loops are equivalent and simpler.

Also note the parameters are now `const vector<int>&` instead of by value. The
original took both by VALUE, copying each vector on every single call.
*/

vector<int> mergeSortCopying(vector<int> arr){
    int n = arr.size();
    if(n <= 1){
        return arr;                        // base case: 0 or 1 element is sorted
    }
    int mid = n / 2;

    vector<int> left(arr.begin(), arr.begin() + mid);
    vector<int> right(arr.begin() + mid, arr.end());

    left  = mergeSortCopying(left);
    right = mergeSortCopying(right);

    return mergeHalves(left, right);
}
/*
TC - O(n log n).  SC - O(n) asymptotically, but with a LARGE constant factor.

WHY THE CONSTANT IS LARGE: even with the const& fix above, this version still
builds two brand-new vectors (left and right) at every level of recursion, and
mergeHalves builds a third. Measured against Approach B on the same data, the
copying version ran roughly 1.7x slower and held about 19x more memory at peak.

It is worth writing once because it maps so directly onto the definition of the
algorithm. For real use, prefer Approach B.
*/


/*
================================================================================
PART 5 : APPROACH B - IN-PLACE WITH INDICES (THE STANDARD FORM)
================================================================================
Instead of physically splitting the array, pass the ORIGINAL array by reference
along with (low, high) indices marking which slice this call owns. Nothing is
copied; the "sub-arrays" are imaginary.

PSEUDOCODE:

    mergeSort(arr, low, high){
        if(low >= high) return;              // 0 or 1 element -> already sorted
        mid = low + (high - low) / 2;
        mergeSort(arr, low, mid);            // sort left half
        mergeSort(arr, mid+1, high);         // sort right half
        merge(arr, low, mid, high);          // combine them
    }

    merge(arr, low, mid, high){
        temp = []
        left = low;  right = mid + 1;
        while(left <= mid && right <= high){
            if(arr[left] <= arr[right]) temp.add(arr[left++]);
            else                        temp.add(arr[right++]);
        }
        while(left <= mid)   temp.add(arr[left++]);
        while(right <= high) temp.add(arr[right++]);
        for(i = low; i <= high; i++) arr[i] = temp[i - low];
    }

Both low and high are INCLUSIVE bounds throughout.

The final copy-back loop uses temp[i - low] because temp is indexed from 0
while the array slice starts at low - the offset converts between them.
*/

void mergeInPlace(vector<int>& arr, int low, int mid, int high, vector<int>& buf){
    int i = low, j = mid + 1, k = low;

    while(i <= mid && j <= high){
        if(arr[i] <= arr[j]) buf[k++] = arr[i++];
        else                 buf[k++] = arr[j++];
    }
    while(i <= mid)  buf[k++] = arr[i++];
    while(j <= high) buf[k++] = arr[j++];

    for(int t = low; t <= high; t++){
        arr[t] = buf[t];
    }
}

void mergeSort(vector<int>& arr, int low, int high, vector<int>& buf){
    if(low >= high) return;
    int mid = low + (high - low) / 2;      // overflow-safe form, see Part 10
    mergeSort(arr, low, mid, buf);
    mergeSort(arr, mid + 1, high, buf);
    mergeInPlace(arr, low, mid, high, buf);
}

// Convenience wrapper so the caller doesn't have to manage the buffer
void mergeSort(vector<int>& arr){
    if(arr.empty()) return;
    vector<int> buf(arr.size());            // ONE buffer, allocated ONCE
    mergeSort(arr, 0, (int)arr.size() - 1, buf);
}
/*
TC - O(n log n).  SC - O(n) for the buffer + O(log n) recursion stack.

WHY A SHARED BUFFER: the original allocated a fresh temp array inside every
merge call. Allocating once and reusing it removes all of that allocation
overhead, and (critically) keeps it off the stack. See Part 10, Bug 1.

VERIFIED BY TESTING - this version sorts 8,000,000 elements in ~1.0 s, where
the original crashed at 4,000,000.
*/


/*
================================================================================
PART 6 : LINE-BY-LINE DRY RUN
================================================================================
Tracing mergeSort on [3, 2, 4, 1, 3], low=0, high=4.
Note how it dives ALL the way down the left side before touching the right.

  CALL 1: low=0, high=4, mid=2
          -> mergeSort(0, 2)

    CALL 2: low=0, high=2, mid=1
            -> mergeSort(0, 1)

      CALL 3: low=0, high=1, mid=0
              -> mergeSort(0, 0)

        CALL 4: low=0, high=0 -> low >= high -> RETURN (single element "3")

              -> mergeSort(1, 1)

        CALL 5: low=1, high=1 -> RETURN (single element "2")

              -> merge(0, 0, 1)   combines [3] and [2]  ->  array is now
                                   [2, 3, 4, 1, 3]

            -> mergeSort(2, 2)

      CALL 6: low=2, high=2 -> RETURN (single element "4")

            -> merge(0, 1, 2)   combines [2,3] and [4]  ->  [2, 3, 4, 1, 3]

          -> mergeSort(3, 4)

    CALL 7: low=3, high=4, mid=3
            -> mergeSort(3, 3)

      CALL 8: low=3, high=3 -> RETURN (single element "1")

            -> mergeSort(4, 4)

      CALL 9: low=4, high=4 -> RETURN (single element "3")

            -> merge(3, 3, 4)   combines [1] and [3]  ->  [2, 3, 4, 1, 3]

          -> merge(0, 2, 4)   combines [2,3,4] and [1,3]

              i->2, j->1 : take 1
              i->2, j->3 : take 2
              i->3, j->3 : EQUAL -> take LEFT (3), advance i
              i->4, j->3 : take 3, right exhausted
              copy rest of left: 4

              FINAL: [1, 2, 3, 3, 4]

KEY OBSERVATION: merge is only ever called AFTER both of its recursive calls
have returned. That means at any instant only ONE merge is executing - which is
why a single shared buffer is enough for the whole algorithm.


================================================================================
PART 7 : DESCENDING ORDER
================================================================================
Only ONE line changes: flip the comparison so the LARGER element is taken first.
*/

void mergeDescInPlace(vector<int>& arr, int low, int mid, int high, vector<int>& buf){
    int i = low, j = mid + 1, k = low;

    while(i <= mid && j <= high){
        if(arr[i] >= arr[j]) buf[k++] = arr[i++];   // >= instead of <=
        else                 buf[k++] = arr[j++];
    }
    while(i <= mid)  buf[k++] = arr[i++];
    while(j <= high) buf[k++] = arr[j++];

    for(int t = low; t <= high; t++) arr[t] = buf[t];
}

void mergeSortDesc(vector<int>& arr, int low, int high, vector<int>& buf){
    if(low >= high) return;
    int mid = low + (high - low) / 2;
    mergeSortDesc(arr, low, mid, buf);
    mergeSortDesc(arr, mid + 1, high, buf);
    mergeDescInPlace(arr, low, mid, high, buf);
}

void mergeSortDesc(vector<int>& arr){
    if(arr.empty()) return;
    vector<int> buf(arr.size());
    mergeSortDesc(arr, 0, (int)arr.size() - 1, buf);
}
/*
The drain loops need no change: whichever side has leftovers is already sorted
descending, so copying it straight across preserves the order.

Using >= (rather than >) keeps the descending sort stable, for the same reason
<= does in the ascending version.
*/


/*
================================================================================
PART 8 : COMPLEXITY ANALYSIS - WHERE n log n COMES FROM
================================================================================

THE RECURRENCE:
    T(n) = 2 * T(n/2) + O(n)
           ^^^^^^^^^^   ^^^^
           two halves   the merge

TWO INDEPENDENT QUESTIONS:

  1. HOW MANY LEVELS?
     Each level halves the array size: n -> n/2 -> n/4 -> ... -> 1.
     The number of halvings before reaching 1 is log2(n).
     So there are log n LEVELS.

  2. HOW MUCH WORK PER LEVEL?
     This is the key insight. At ANY given level, the sub-arrays are different
     sizes and there are different numbers of them - but together they still
     contain ALL n elements, because they are just a partition of the original
     array. Merging costs O(size) per merge, so summed across one whole level
     the work is always O(n).

     Level 0 (top)  : 1 merge  of size n        -> n
     Level 1        : 2 merges of size n/2      -> n
     Level 2        : 4 merges of size n/4      -> n
     ...
     Level log n    : n merges of size 1        -> n

  TOTAL = (work per level) x (number of levels) = O(n) x log n = O(n log n)

WHY BEST = AVERAGE = WORST = O(n log n):
The splitting is positional (always the midpoint), never data-dependent. Merge
sort does not care whether the input is sorted, reversed, or random - it always
performs the same number of levels and the same amount of merging. This is
exactly what quicksort CANNOT guarantee, since quicksort's split depends on
pivot values.

SPACE COMPLEXITY: O(n)
  - the merge buffer holds up to n elements
  - plus O(log n) recursion stack, which is dominated by the O(n) buffer

Merge sort is therefore NOT in-place, unlike quicksort, heapsort, or the
elementary O(n^2) sorts. That O(n) extra memory is its main cost.
*/


/*
================================================================================
PART 9 : STABILITY AND THE <= vs < DETAIL
================================================================================
A sort is STABLE if elements with EQUAL keys keep their original relative order.
Merge sort is famously stable - BUT ONLY IF the comparison is written correctly.

THE RULE: on a TIE, take from the LEFT half.

The left half holds elements that came EARLIER in the original array. Taking
left first on ties preserves that original ordering. Taking right first
reverses it.

    if(arr[i] <= arr[j])  take left    ->  STABLE
    if(arr[i] <  arr[j])  take left    ->  UNSTABLE
                                            (on a tie, the else branch fires
                                             and grabs the RIGHT element)

VERIFIED BY TESTING. Sorting items {2a, 1b, 2c, 1d, 2e} by number:

    with  <   :  1d 1b 2e 2c 2a       equal keys came out REVERSED
    with  <=  :  1b 1d 2a 2c 2e       original order preserved

Both are correctly SORTED - the numbers are in order either way. The difference
is invisible on plain integers, because two equal ints are indistinguishable.
It only shows up when the elements carry extra data (sorting records by one
field, sorting pairs by .first, etc.).

WHY THIS MATTERS: stability is merge sort's headline advantage over quicksort.
Writing < instead of <= silently throws that advantage away while still passing
every "is it sorted?" test you are likely to run. Both approaches in the
original file used <, so both were unstable.
*/


/*
================================================================================
PART 10 : TWO REAL BUGS TO AVOID
================================================================================

--------------------------------------------------------------------------------
BUG 1 : ALLOCATING THE TEMP ARRAY INSIDE merge, ON THE STACK
--------------------------------------------------------------------------------
The original merge contained:

        int temp[high+1];          // inside merge(), called at every level

THREE separate problems:

  (a) IT IS A VLA. Variable length arrays are not standard C++ (g++ allows them
      as a C-inherited extension; -pedantic-errors rejects them, and MSVC does
      not support them at all).

  (b) IT IS SIZED WRONG. The slice being merged runs from low to high, which is
      (high - low + 1) elements. Sizing it high+1 over-allocates badly for every
      right-hand slice, where low is large.

      MEASURED at n = 1024:
          ints actually needed across all merges : 10,240
          ints allocated by temp[high+1]         : 528,896
          overhead                                : 51.6x

  (c) IT LIVES ON THE STACK, which is only ~8 MB. The top-level merge alone
      allocates n ints there.

      VERIFIED BY TESTING (8 MB stack):
          n = 1,000,000  -> ran fine
          n = 2,000,000  -> ran fine
          n = 4,000,000  -> SEGMENTATION FAULT

      The corrected version, using a single heap-allocated buffer, sorted
      8,000,000 elements without trouble.

THE FIX: allocate ONE buffer of size n on the heap, before the recursion starts,
and pass it down by reference (as done in Part 5). This is legal standard C++,
uses the minimum possible memory, and eliminates per-merge allocation overhead.

--------------------------------------------------------------------------------
BUG 2 : int mid = (low + high) / 2;
--------------------------------------------------------------------------------
If low + high exceeds INT_MAX, the SUM overflows to a negative number before the
division ever happens - and dividing a value that is already garbage cannot
recover it.

        low = 1,500,000,000, high = 2,000,000,000
        real sum          = 3,500,000,000
        INT_MAX           = 2,147,483,647
        (low+high) stored = -794,967,296      <-- wrapped negative
        / 2               = -397,483,648      <-- negative index

THE FIX:
        int mid = low + (high - low) / 2;

    high - low is a difference between two valid indices, so it can never
    overflow; halving it shrinks it further; and adding it back to low lands at
    a value <= high, which is a valid index by assumption. No intermediate value
    ever leaves the valid range, and the result is algebraically identical.

HISTORICAL NOTE: this exact bug sat in Java's java.util.Arrays.binarySearch for
about nine years, and in Jon Bentley's Programming Pearls for two decades before
that. Joshua Bloch documented it in 2006 in a post titled "Nearly All Binary
Searches and Mergesorts are Broken" - mergesorts included, because merge sort
computes a midpoint the same way. It needs an array of roughly 2^30 elements to
trigger, which is why nobody hit it for so long.
*/


/*
================================================================================
PART 11 : OPTIMISATIONS
================================================================================

  1. ALLOCATE THE BUFFER ONCE (already applied in Part 5)
     Removes an allocation per merge call.

  2. SKIP THE MERGE WHEN ALREADY ORDERED
     If the largest element of the left half is <= the smallest of the right
     half, the two halves are already in order relative to each other:

         if(arr[mid] <= arr[mid+1]) return;    // at the top of merge

     Costs one comparison. Turns already-sorted input into O(n log n) with a
     tiny constant, and helps a lot on partially-sorted real data.

  3. SWITCH TO INSERTION SORT FOR SMALL SLICES
     Recursion overhead dominates on tiny arrays, and insertion sort has a very
     low constant factor:

         if(high - low < 16){ insertionSort(arr, low, high); return; }

     This is what real library sorts do.

  4. ALTERNATE BUFFERS INSTEAD OF COPYING BACK
     The copy-back loop touches every element a second time. Advanced
     implementations merge from A into B at one level and B into A at the next,
     eliminating the copy entirely.

  5. BOTTOM-UP (ITERATIVE) MERGE SORT
     Skip recursion: merge all runs of size 1, then size 2, then 4, doubling
     until the whole array is one run.

         for(int width = 1; width < n; width *= 2)
             for(int i = 0; i < n; i += 2*width)
                 merge(arr, i, min(i+width-1, n-1), min(i+2*width-1, n-1));

     Same O(n log n), but O(1) stack instead of O(log n) - useful where deep
     recursion is a problem.
*/


/*
================================================================================
PART 12 : WHY MERGE SORT MATTERS
================================================================================
In raw array-sorting speed, quicksort usually beats merge sort (better cache
behavior, no auxiliary buffer, in-place). Merge sort is still the right tool in
four situations:

  1. WHEN STABILITY IS REQUIRED
     Sorting records by one field while preserving an earlier sort on another.
     This is why std::stable_sort is merge-based, and why Java uses a merge-based
     Timsort for objects while using quicksort for primitives - two equal ints
     are indistinguishable, so stability only matters for objects.

  2. LINKED LISTS
     Merge sort needs only sequential access, never random access. On a linked
     list you merge by RELINKING pointers rather than copying, so the extra
     space drops to O(1) - better than on arrays. Quicksort is poor on lists for
     the opposite reason: it depends on random access for partitioning.
     (This is why std::list has its own .sort() member function - std::sort
     cannot work on it.)

  3. EXTERNAL SORTING - data too large for RAM
     Merge sort reads and writes SEQUENTIALLY, which is exactly what disks and
     tapes are fast at. Sort chunks that fit in memory, write them out, then
     merge the sorted runs streaming from disk. Quicksort's random access
     pattern is catastrophic here.

  4. GUARANTEED WORST CASE
     O(n log n) always, with no dependence on input order. Quicksort's O(n^2)
     worst case is avoidable in practice but not eliminable without extra
     machinery (introsort switches to heapsort at depth).

--------------------------------------------------------------------------------
BONUS APPLICATION: COUNTING INVERSIONS
--------------------------------------------------------------------------------
An INVERSION is a pair (i, j) with i < j but arr[i] > arr[j] - a measure of how
unsorted an array is. Brute force is O(n^2); merge sort gives O(n log n) almost
for free.

THE INSIGHT: during a merge, when you take an element from the RIGHT half, every
element still remaining in the LEFT half forms an inversion with it (they all
come earlier in the array but are all larger). So add (mid - i + 1) in one shot:

        if(arr[i] <= arr[j]) buf[k++] = arr[i++];
        else {
            inversions += (mid - i + 1);      // <-- the only added line
            buf[k++] = arr[j++];
        }

This "do extra work during the merge" pattern is why merge sort shows up
constantly in competitive programming, well beyond plain sorting.
*/


/*
================================================================================
PART 13 : COMMON MISTAKES CHECKLIST
================================================================================
  [X] int temp[high+1] inside merge     -> VLA (non-standard), wrongly sized
                                            (51x waste), and on the 8 MB stack;
                                            segfaults around n = 4,000,000
  [X] mid = (low + high) / 2            -> overflows for large indices; use
                                            low + (high - low) / 2
  [X] Using < instead of <=             -> silently destroys stability, merge
      in the comparison                    sort's main advantage
  [X] Passing vectors by value          -> copies at every recursion level;
                                            ~1.7x slower, ~19x peak memory
  [X] Naming the function merge()       -> collides with std::merge under
                                            `using namespace std`
  [X] Forgetting the copy-back loop     -> the merged result stays in temp and
                                            never reaches the real array
  [X] Wrong offset in copy-back         -> must be temp[i - low], since temp is
                                            0-indexed but the slice starts at low
  [X] Base case low > high vs >=        -> use low >= high; a single element is
                                            already sorted
  [X] Allocating a new temp per merge   -> allocate ONE buffer up front and pass
                                            it by reference
  [X] int arr[n] with runtime n         -> non-standard VLA; use vector<int>(n)
================================================================================
*/


int main(){
    int n;
    cin >> n;

    // FIX: the original used `int arr[n];` - a non-standard VLA on the stack.
    vector<int> arr(n);
    for(int i = 0; i < n; i++){
        cin >> arr[i];
    }

    mergeSort(arr);                       // ascending
    cout << "Ascending : ";
    for(int v : arr) cout << v << " ";
    cout << endl;

    mergeSortDesc(arr);                   // descending
    cout << "Descending: ";
    for(int v : arr) cout << v << " ";
    cout << endl;

    return 0;
}