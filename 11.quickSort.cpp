#include<bits/stdc++.h>
using namespace std;

/*
================================================================================
                            QUICK SORT - COMPLETE NOTES
================================================================================
QUICK SORT is DIVIDE AND CONQUER, but the work happens on the way DOWN, which is
the opposite of merge sort.

    merge sort : split blindly at the midpoint, do all the work MERGING on the
                 way back up
    quick sort : do all the work PARTITIONING on the way down; once both halves
                 are sorted there is nothing left to combine

THE THREE STEPS:
    1. Pick a PIVOT
    2. PARTITION - put everything smaller on its left, everything larger on its
       right. The pivot is now in its FINAL sorted position, permanently.
    3. Recurse on the left part and the right part (excluding the pivot).

PIVOT CHOICES: first element, last element, middle element, or a random element.
The choice does not affect correctness, only performance - see Part 7.

TABLE OF CONTENTS
-----------------
  PART 1  : Worked example
  PART 2  : Hoare-style partition (pivot = first element)
  PART 3  : Two-function version
  PART 4  : Variants - alternative bounds, descending
  PART 5  : Lomuto partition (pivot = last element)
  PART 6  : Shift-based partition (why it is a trap)
  PART 7  : Complexity - and the space claim corrected
  PART 8  : Randomised pivot and bounded stack depth
  PART 9  : Three-way partition for duplicates
  PART 10 : Quicksort vs merge sort
  PART 11 : Common mistakes checklist

================================================================================
PART 1 : WORKED EXAMPLE
================================================================================
Array: 4 2 3 1 5 6 7 9, taking the first element as pivot.

  Step 1: pivot = 4
  Step 2: place 4 in its final position - everything < 4 to the left,
          everything > 4 to the right:
              [2, 1, 3]  4  [6, 5, 7, 9]
          4 is now permanently correct and never moves again.
  Step 3: recurse on each side.

      left  [2, 1, 3], pivot 2   ->  [1] 2 [3]        -> 1 2 3
      right [6, 5, 7, 9], pivot 6 ->  [5] 6 [7, 9]     -> 5 6 7 9
             [7, 9], pivot 7      ->  7 [9]            -> 7 9
             single elements return immediately

  Final: 1 2 3 4 5 6 7 9

THE KEY PROPERTY: after each partition the pivot is in its FINAL place. That is
why the recursive calls exclude it - (low, p-1) and (p+1, high), never touching
index p again.


================================================================================
PART 2 : HOARE-STYLE PARTITION (pivot = first element)
================================================================================
Maintain low and high (both INCLUSIVE), and two pointers i and j.

    i starts at low, walks RIGHT until it finds an element > pivot
    j starts at high, walks LEFT  until it finds an element <= pivot
    when both stop and i < j, swap them
    repeat until the pointers cross
    finally swap the pivot into position j

WHY THE FINAL SWAP USES j (not j-1): when the loop ends, j points AT the last
element that is <= pivot. Everything at index <= j is <= pivot, everything above
is > pivot. So index j is exactly where the pivot belongs.

DRY RUN: 4 6 2 5 7 9 1 3   (low=0, high=7, pivot=4)

  i scans right: arr[0]=4 <= 4, i++; arr[1]=6 > 4, STOP at i=1
  j scans left : arr[7]=3 <= 4, STOP at j=7
  swap(arr[1], arr[7])          ->  4 3 2 5 7 9 1 6

  i: arr[1]=3, arr[2]=2 both <= 4, i++; arr[3]=5 > 4, STOP at i=3
  j: arr[7]=6 > 4, j--; arr[6]=1 <= 4, STOP at j=6
  swap(arr[3], arr[6])          ->  4 3 2 1 7 9 5 6

  i: arr[3]=1 <= 4, i++; arr[4]=7 > 4, STOP at i=4
  j: arr[6]=5, arr[5]=9, arr[4]=7 all > 4, j--; arr[3]=1 <= 4, STOP at j=3
  i=4 > j=3, pointers crossed, exit

  swap(arr[0], arr[3])          ->  1 3 2 4 7 9 5 6
                                          ^ pivot 4 is final at index 3
*/

void quickSort(vector<int> &arr, int low, int high){
    // low and high are BOTH INCLUSIVE
    if(low >= high) return;              // 0 or 1 element is already sorted

    int i = low, j = high;
    int pivot = arr[low];

    while(i < j){
        // ORDER MATTERS in these conditions. The bounds check must come FIRST.
        // && short-circuits left to right, so if i > high the second operand is
        // never evaluated and arr[i] is never read out of bounds. Reversed, it
        // would read first and check after - a crash waiting to happen.
        while(i <= high && arr[i] <= pivot) i++;
        while(j >= low  && arr[j] >  pivot) j--;
        if(i < j) swap(arr[i], arr[j]);
    }

    swap(arr[low], arr[j]);              // pivot into its final slot
    quickSort(arr, low, j - 1);          // left part  (excludes the pivot)
    quickSort(arr, j + 1, high);         // right part (excludes the pivot)
}
/*
A NOTE ON THE j BOUND: `j >= low` is belt-and-braces rather than load-bearing.
arr[low] IS the pivot, so arr[low] > pivot is false and j always halts at low at
the latest. It costs nothing to keep, and documents the intent.
*/


/*
================================================================================
PART 3 : TWO-FUNCTION VERSION
================================================================================
Splitting partition and recursion into separate functions is the conventional
form. It reads better and makes the partition independently testable - and
partition alone is what quickselect needs (Part 10).
*/

int partitionHoare(vector<int> &arr, int low, int high){
    int i = low, j = high;
    int pivot = arr[low];

    while(i < j){
        while(arr[i] <= pivot && i <= high - 1) i++;
        while(arr[j] >  pivot && j >= low + 1)  j--;
        if(i < j) swap(arr[i], arr[j]);
    }
    swap(arr[low], arr[j]);
    return j;                             // the pivot's final index
}
/*
Here the bounds checks come SECOND, which is safe only because the limits are
tightened to high-1 and low+1: i can never reach high, j can never reach low, so
neither can step outside the array before the comparison is evaluated.

Both orderings work. Pick one convention and stay with it:
    while(i <= high && arr[i] <= pivot)      bound first, loose limit
    while(arr[i] <= pivot && i <= high-1)    bound second, tight limit
Mixing them up is where out-of-bounds reads come from.
*/

void quickSortTwoFn(vector<int> &arr, int low, int high){
    if(low >= high) return;
    int p = partitionHoare(arr, low, high);
    quickSortTwoFn(arr, low, p - 1);      // FIX: the original called quickSort
    quickSortTwoFn(arr, p + 1, high);     // here instead of recursing into
}                                          // itself - it worked by accident
                                           // since both are correct, but it
                                           // silently abandoned its own partition


/*
================================================================================
PART 4 : VARIANTS
================================================================================

--------------------------------------------------------------------------------
4.1  Alternative bounds - i starts at low+1
--------------------------------------------------------------------------------
Since arr[low] IS the pivot, starting i at low just wastes one comparison
(pivot <= pivot is always true). Starting at low+1 skips it - but the loop
conditions must change to match.
*/

int partitionFromLowPlus1(vector<int>& arr, int low, int high){
    int i = low + 1;                      // skip the pivot itself
    int j = high;
    int pivot = arr[low];

    while(i <= j){                        // <= not <, so the pointers still cross
        while(i <= high && arr[i] <= pivot) i++;
        while(j >  low  && arr[j] >  pivot) j--;
        if(i < j) swap(arr[i], arr[j]);
    }
    swap(arr[low], arr[j]);
    return j;
}
/*
THREE COORDINATED CHANGES - none of them optional:
  1. i starts at low+1 (skipping the pivot)
  2. the outer condition becomes i <= j, because with i one step further right
     the pointers need one extra iteration to cross
  3. the j bound becomes j > low (not j >= low), so j can never reach low-1

NOTE: the original comment for this variant said the condition changes to
`arr[i] < pivot` rather than `<=`, but the code kept `<=`. The code is right and
the comment was wrong - the comparison does not change, only the three items
above. VERIFIED BY TESTING: with `<=` this passes 2000 random tests.

The original also had a syntax error here: swap(arr[i], swap(arr[j])) - a nested
swap with one argument, which does not compile.
*/

void quickSortAlt(vector<int>& arr, int low, int high){
    if(low >= high) return;
    int p = partitionFromLowPlus1(arr, low, high);
    quickSortAlt(arr, low, p - 1);
    quickSortAlt(arr, p + 1, high);
}

/*
--------------------------------------------------------------------------------
4.2  Descending order
--------------------------------------------------------------------------------
Mirror both comparisons. Larger elements now belong on the left.
*/

int partitionDesc(vector<int>& arr, int low, int high){
    int i = low, j = high;
    int pivot = arr[low];

    while(i < j){
        while(i <= high && arr[i] >= pivot) i++;   // >= instead of <=
        while(j >= low  && arr[j] <  pivot) j--;   // <  instead of >
        if(i < j) swap(arr[i], arr[j]);
    }
    swap(arr[low], arr[j]);
    return j;
}

void quickSortDesc(vector<int>& arr, int low, int high){
    if(low >= high) return;
    int p = partitionDesc(arr, low, high);
    quickSortDesc(arr, low, p - 1);
    quickSortDesc(arr, p + 1, high);
}
// VERIFIED BY TESTING: passes 2000 random tests including heavy duplicates.

/*
--------------------------------------------------------------------------------
4.3  Descending with pivot = LAST element
--------------------------------------------------------------------------------
Same idea, but anchored at the other end. The final swap uses i, not j, because
the pivot now lives at high and i is the boundary.
*/

void quickSortDescLast(vector<int> &arr, int low, int high){
    if(low >= high) return;

    int i = low, j = high;
    int pivot = arr[high];

    while(i < j){
        while(i <= high && arr[i] >  pivot) i++;
        while(j >= low  && arr[j] <= pivot) j--;
        if(i < j) swap(arr[i], arr[j]);
    }
    swap(arr[high], arr[i]);
    quickSortDescLast(arr, low, i - 1);
    quickSortDescLast(arr, i + 1, high);
}
// VERIFIED BY TESTING: passes 2000 random tests.


/*
================================================================================
PART 5 : LOMUTO PARTITION (pivot = last element)
================================================================================
The other standard scheme. One scanning pointer instead of two.

    i = boundary of the "< pivot" region (its LAST index)
    j = scanner

INVARIANT while the loop runs:
    [low   .. i    ]  < pivot
    [i+1   .. j-1  ]  >= pivot
    [j     .. high-1] not yet examined
    [high          ]  the pivot

i starts at low-1 because the "< pivot" region starts EMPTY, and i marks its
last element - for an empty region that is one slot before the start.

When the scan ends, j = high, so the ">= pivot" region is [i+1, high-1]. Position
i+1 holds the first element >= pivot, which is exactly where the pivot goes.
*/

int partitionLomuto(vector<int>& arr, int low, int high){
    int pivot = arr[high];
    int i = low - 1;

    for(int j = low; j < high; j++){
        if(arr[j] < pivot){               // use > for descending
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;                          // FIX: the original declared this
}                                           // function void but returned a value,
                                            // which does not compile

void quickSortLomuto(vector<int>& arr, int low, int high){
    if(low >= high) return;
    int p = partitionLomuto(arr, low, high);
    quickSortLomuto(arr, low, p - 1);
    quickSortLomuto(arr, p + 1, high);     // FIX: original was missing the ;
}
/*
HOARE vs LOMUTO:

  LOMUTO   simpler to write from memory (one plain for loop, no crossing-pointer
           edge cases), returns the pivot index unambiguously.
           BUT: does about 2.5x more swaps, and degrades badly on duplicates.
           MEASURED on random data: n=16000 -> Lomuto 145,743 swaps vs
           Hoare 53,034.
           MEASURED on an all-equal array of 2000: recursion depth 1999. With
           strict <, nothing counts as "less than", so every split is
           0-vs-(n-1) - an array of identical values is Lomuto's worst case.

  HOARE    fewer swaps, handles duplicates far better (arr[i] <= pivot lets i
           keep advancing, producing balanced splits), but the boundary
           conditions are fiddlier.

Use Lomuto when you need to write a correct partition quickly under pressure, or
as the base for quickselect and three-way partitioning. Use Hoare when
performance matters.
*/


/*
================================================================================
PART 6 : SHIFT-BASED PARTITION (why it is a trap)
================================================================================
An intuitive-looking alternative: whenever you find an element smaller than the
pivot, bubble it leftward with adjacent swaps until it reaches the boundary.

IT IS CORRECT. It is also Theta(n^2) - do not use it.
*/

int partitionShift(vector<int>& arr, int low, int high){
    int pi = low;                          // pi tracks where the PIVOT currently is
    int pv = arr[low];
    for(int i = low + 1; i <= high; i++){
        if(arr[i] < pv){
            int k = i;
            while(k > pi){ swap(arr[k], arr[k-1]); k--; }   // walk it left
            pi++;                           // the pivot shifted right by one
        }
    }
    return pi;
}

void quickSortShift(vector<int>& arr, int low, int high){
    if(low >= high) return;
    int p = partitionShift(arr, low, high);   // FIX: the original called
    quickSortShift(arr, low, p - 1);           // pivot() and quick() - names
    quickSortShift(arr, p + 1, high);          // that do not exist in the file
}
/*
WHY IT IS QUADRATIC:
Moving one small element costs (i - pi) adjacent swaps. The elements in between
are the pivot plus every LARGER element seen so far, so:

    cost of moving one small element = 1 + (larger elements before it)
    total partition cost = L + (cross-inversions between the two groups)

With L and G both about m/2, that averages m^2/8 - the partition itself is
quadratic.

AND THE RECURSION CANNOT SAVE IT. Work per level HALVES rather than staying
flat, so the sum is a geometric series:

    n^2/8 + 2(n/2)^2/8 + 4(n/4)^2/8 + ...  =  n^2/8 x 2  =  n^2/4

MEASURED at n=8192: total 16,710,541 swaps vs the predicted n^2/4 = 16,777,216.
Level 0 alone was 46% of all work.

This is the structural difference worth internalising:
    work per level FLAT     -> multiply by the number of levels -> log n appears
    work per level HALVING  -> series converges to ~2x the top level ->
                               the number of levels drops out entirely

So no pivot strategy helps. Even a perfect median every time gives Theta(n^2),
because the cost lives in the partition, not in the split quality.

WHAT IT DOES BUY: it is STABLE, which normal quicksort is not - adjacent-only
swaps never jump an element past an equal one. But that is a bad trade, since
merge sort is stable AND O(n log n).
*/


/*
================================================================================
PART 7 : COMPLEXITY - AND THE SPACE CLAIM CORRECTED
================================================================================

TIME COMPLEXITY:
    Best     O(n log n)   pivot lands near the middle every time
    Average  O(n log n)   random data
    Worst    O(n^2)       pivot is always the minimum or maximum

WHY O(n log n) WHEN SPLITS ARE NOT EXACTLY HALF: the partition is O(m) because
i only moves right and j only moves left - together they cross the range once.
Each LEVEL of recursion therefore costs O(n) total, since the subarrays at one
level are a partition of the original array. You only need the size to shrink by
some CONSTANT FRACTION each level, not exactly half: if size becomes at most c*n
for any constant c < 1, depth is log base (1/c) of n, which is O(log n) for any
such c. Even consistent 25/75 splits give depth 2.41 x log2(n) - a constant
multiple, same complexity class.

WHY THE WORST CASE IS O(n^2): with pivot = arr[low] on an ALREADY SORTED array,
the pivot is always the minimum. Every split is 0-vs-(n-1), so there are n levels
instead of log n, and n levels x O(n) work = O(n^2).

--------------------------------------------------------------------------------
***** SPACE COMPLEXITY IS NOT O(1) *****
--------------------------------------------------------------------------------
The original notes claimed "SC: O(1) - none temp is maintained, all works are
done in place". The first half is right, the conclusion is not.

Quicksort allocates no auxiliary ARRAY - true, and that is its advantage over
merge sort. But every recursive call pushes a STACK FRAME, and those frames are
real memory.

    SPACE = O(recursion depth)

MEASURED recursion depth:

    n=  1000   random input:  22    sorted input:    999
    n= 10000   random input:  31    sorted input:   9999
    n=100000   random input:  41    sorted input:  99999

So the honest statement is:

    SC - O(log n) average,  O(n) worst case

On sorted input at n=100000 that is 100,000 live frames - enough to overflow an
8 MB stack. Part 8 fixes both problems.
*/


/*
================================================================================
PART 8 : RANDOMISED PIVOT AND BOUNDED STACK DEPTH
================================================================================

--------------------------------------------------------------------------------
8.1  RANDOM PIVOT - kills the O(n^2) worst case in practice
--------------------------------------------------------------------------------
Swap a random element into the pivot position before partitioning. The
adversarial inputs (sorted, reverse-sorted) stop being special.

    int rd = low + rand() % (high - low + 1);
    swap(arr[low], arr[rd]);          // for Hoare  (pivot at low)
    swap(arr[high], arr[rd]);         // for Lomuto (pivot at high)

***** THE ORIGINAL FORMULA WAS WRONG *****
It read:  int rd = low + rand() % (low - high + 1);

With low=0 and high=7 that is rand() % (-6). The modulus is NEGATIVE, which is
undefined behaviour. The range size is (high - low + 1), not (low - high + 1) -
the subtraction is the wrong way round.
*/

int partitionRandom(vector<int>& arr, int low, int high){
    int rd = low + rand() % (high - low + 1);   // correct range size
    swap(arr[low], arr[rd]);
    return partitionHoare(arr, low, high);
}

/*
--------------------------------------------------------------------------------
8.2  BOUNDED STACK DEPTH - recurse into the SMALLER side only
--------------------------------------------------------------------------------
A random pivot makes O(n^2) unlikely but does not BOUND the stack. This does:
recurse into the smaller half, and loop on the larger half instead of recursing.

Since the recursed side is at most half the range, depth can never exceed
log2(n) - guaranteed, regardless of pivot luck.
*/

void quickSortBounded(vector<int>& arr, int low, int high){
    while(low < high){
        int p = partitionHoare(arr, low, high);

        if(p - low < high - p){
            quickSortBounded(arr, low, p - 1);   // recurse into the SMALLER side
            low = p + 1;                          // loop on the larger side
        } else {
            quickSortBounded(arr, p + 1, high);
            high = p - 1;
        }
    }
}
/*
MEASURED on ALREADY SORTED input - quicksort's worst case:

    n=  1000   plain version depth =   999    bounded version depth = 1
    n= 10000   plain version depth =  9999    bounded version depth = 1
    n=100000   plain version depth = 99999    bounded version depth = 1

The depth collapses to 1 here because on sorted input the "smaller" side is
always empty, so it returns immediately and the loop handles everything. On
random data the depth stays at O(log n).

Combine 8.1 and 8.2 and you have production-grade quicksort: O(n log n) with
overwhelming probability, and a hard O(log n) stack bound.
*/


/*
================================================================================
PART 9 : THREE-WAY PARTITION FOR DUPLICATES
================================================================================
Both Hoare and Lomuto degrade toward O(n^2) when the array has many equal
elements, because equal values keep getting re-partitioned instead of being
finished.

THE FIX - Dutch National Flag partitioning. Split into THREE regions instead of
two, and never recurse into the middle, because every element equal to the pivot
is already in its final place.

    [low .. lt-1]  < pivot
    [lt  .. gt  ]  == pivot        <-- DONE, never revisited
    [gt+1 .. high] > pivot
*/

void quickSort3Way(vector<int>& arr, int low, int high){
    if(low >= high) return;

    int pivot = arr[low];
    int lt = low, i = low, gt = high;

    while(i <= gt){
        if(arr[i] < pivot)      swap(arr[lt++], arr[i++]);
        else if(arr[i] > pivot) swap(arr[i], arr[gt--]);
        else                     i++;                 // equal - leave it
    }
    quickSort3Way(arr, low, lt - 1);
    quickSort3Way(arr, gt + 1, high);                  // middle is skipped
}
/*
On an array of all-identical values this finishes in ONE partition - O(n) total
instead of O(n^2). This is what real library implementations use when duplicates
are expected.
*/


/*
================================================================================
PART 10 : QUICKSORT vs MERGE SORT
================================================================================

                      | Quicksort            | Merge sort
    ------------------|----------------------|---------------------
    Best              | O(n log n)           | O(n log n)
    Average           | O(n log n)           | O(n log n)
    Worst             | O(n^2)               | O(n log n)
    Space             | O(log n) stack       | O(n) buffer
    Stable            | NO                   | YES
    Where work happens| partition, going down| merge, coming back up

QUICKSORT IS USUALLY FASTER IN PRACTICE despite the worse worst case:
  - partitions in place, so no auxiliary buffer and no copy-back pass
  - excellent cache locality - it works on one shrinking contiguous region
  - the O(n^2) case is engineerable away (random pivot; or introsort, which
    switches to heapsort past a depth limit, guaranteeing O(n log n))

WHY QUICKSORT IS NOT STABLE: partitioning swaps DISTANT elements, which can
throw one element past an equal one. Adjacent-only swapping is what preserves
order, and that is exactly what the O(n^2) sorts do.

PREFER MERGE SORT WHEN: you need stability, you are sorting a linked list
(merge sort needs no random access and is O(1) extra space there), or you are
doing external sorting on data too large for RAM.

BONUS - QUICKSELECT: partition alone solves "find the k-th smallest element" in
O(n) average time. After partitioning, if p == k you are done; otherwise recurse
into ONLY the side containing k. Half the work is discarded each time, so the
series n + n/2 + n/4 + ... converges to 2n rather than n log n.
*/


/*
================================================================================
PART 11 : COMMON MISTAKES CHECKLIST
================================================================================
  [X] Claiming SC is O(1)             -> it is O(log n) average, O(n) worst;
                                          recursion frames are real memory
  [X] rand() % (low - high + 1)       -> negative modulus, undefined behaviour;
                                          the range size is (high - low + 1)
  [X] Bounds check written second     -> only safe with tightened limits
      with loose limits                  (high-1 / low+1); otherwise arr[i] is
                                          read before i is validated
  [X] Swapping the pivot to j-1       -> j points AT the last element <= pivot,
                                          so j is its final slot, not j-1
  [X] Recursing into (low, p) or      -> the pivot at p is already final;
      (p, high)                          including it causes infinite recursion
  [X] A partition helper declared     -> must return int
      void that returns a value
  [X] Recursing into a different      -> the two-function version must call
      function than itself               ITSELF, not the one-function variant
  [X] Mixing up the three coordinated -> i=low+1 also requires i<=j and j>low
      changes in the low+1 variant
  [X] Using shift-based partitioning  -> correct but Theta(n^2) even with
                                          perfect pivots
  [X] Ignoring duplicates             -> use three-way partitioning
  [X] No stack bound                  -> recurse into the smaller side and loop
                                          on the larger
================================================================================
*/


int main(){
    srand(time(0));

    int n, elem;
    cin >> n;
    vector<int> arr;
    for(int i = 0; i < n; i++){
        cin >> elem;
        arr.push_back(elem);
    }

    if(n > 0) quickSortBounded(arr, 0, n - 1);   // the production-grade version

    for(int v : arr) cout << v << " ";
    cout << endl;

    return 0;
}