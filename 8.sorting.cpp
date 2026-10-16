#include<bits/stdc++.h>
using namespace std;

/*
================================================================================
                    SORTING - SELECTION, BUBBLE, INSERTION
================================================================================
This file covers the three elementary O(n^2) comparison sorts.
Merge sort and quick sort are covered in a separate file.

TABLE OF CONTENTS
-----------------
  PART 1  : Key vocabulary (stable, in-place, adaptive)
  PART 2  : Selection Sort
  PART 3  : Bubble Sort
  PART 4  : Insertion Sort
  PART 5  : Comparison summary
  PART 6  : Two traps these algorithms expose
  PART 7  : Where the O(n^2) barrier ends
  PART 8  : Common mistakes checklist

================================================================================
PART 1 : KEY VOCABULARY
================================================================================
Four properties describe every sorting algorithm. Interviewers ask about these
constantly, and they decide which algorithm you actually want.

--------------------------------------------------------------------------------
STABLE
--------------------------------------------------------------------------------
A sort is STABLE if elements with EQUAL keys keep their ORIGINAL relative order.

Why it matters: sorting records by one field while preserving an earlier sort on
another field. Sort employees by name, then by department - with a stable sort
each department's employees are still in name order. With an unstable sort that
earlier ordering is destroyed.

DEMONSTRATED BY TESTING with items {4a, 2b, 4c, 1d, 4e} sorted by number
(the three 4s start in the order a, c, e):

    insertion sort ->  1d 2b 4a 4c 4e      a, c, e preserved  -> STABLE
    selection sort ->  1d 2b 4c 4a 4e      order scrambled    -> NOT STABLE

Selection sort breaks stability because it SWAPS distant elements - moving the
minimum to the front can jump an equal element over another one.

--------------------------------------------------------------------------------
IN-PLACE
--------------------------------------------------------------------------------
Uses only O(1) extra memory - it rearranges the existing array rather than
building a new one. All three sorts here are in-place. (Merge sort is not - it
needs an O(n) buffer.)

--------------------------------------------------------------------------------
ADAPTIVE
--------------------------------------------------------------------------------
Runs FASTER on data that is already partly sorted. Bubble (optimised) and
insertion are adaptive - both hit O(n) on already-sorted input. Selection sort
is NOT adaptive: it does the same work regardless of input.

--------------------------------------------------------------------------------
COMPARISONS vs SWAPS
--------------------------------------------------------------------------------
These are counted separately and can differ enormously. Selection sort does
O(n^2) comparisons but only O(n) SWAPS - the fewest of any of these three.
That is its one genuine advantage: if writing is far more expensive than
reading (e.g. flash memory with limited write cycles), minimising swaps wins.


================================================================================
PART 2 : SELECTION SORT
================================================================================
IDEA: repeatedly SELECT the minimum from the unsorted portion and swap it into
its final position at the front.

An array of size n is sorted in n-1 passes - after n-1 elements are placed, the
single remaining element is necessarily already in the right place.
*/

void selectionSort(int arr[], int n){
    for(int i = 0; i < n - 1; i++){
        int mini = i;                     // assume the current position holds the min
        for(int j = i + 1; j < n; j++){   // scan the rest of the unsorted part
            if(arr[j] < arr[mini]){
                mini = j;                  // track only the INDEX, not the value -
            }                               // the value is always arr[mini]
        }
        swap(arr[mini], arr[i]);           // place the minimum at position i
    }
}
/*
NOTE: the inner loop starts at i+1, not i. Starting at i compares arr[i] with
itself on the first iteration - harmless but pointless.

WORKED EXAMPLE: 13, 46, 24, 52, 20, 9   (n = 6)

  Pass 1: i=0, scan [0..5], min = 9   ->  9, 46, 24, 52, 20, 13
  Pass 2: i=1, scan [1..5], min = 13  ->  9, 13, 24, 52, 20, 46
  Pass 3: i=2, scan [2..5], min = 20  ->  9, 13, 20, 52, 24, 46
  Pass 4: i=3, scan [3..5], min = 24  ->  9, 13, 20, 24, 52, 46
  Pass 5: i=4, scan [4..5], min = 46  ->  9, 13, 20, 24, 46, 52
                                                              ^ was written as 56
                                                                in the original
                                                                notes - typo, the
                                                                value is 52
  Sorted after n-1 = 5 passes.

TIME COMPLEXITY:
    Comparisons = (n-1) + (n-2) + ... + 1 = n(n-1)/2 = n^2/2 - n/2
    Drop the constant (1/2) and the lower term (n/2):

    Best    O(n^2)
    Average O(n^2)
    Worst   O(n^2)      <-- IDENTICAL in all three cases

WHY BEST CASE IS ALSO O(n^2): the algorithm has no way to detect that the array
is already sorted. It must scan the entire remaining subarray every pass just to
confirm the minimum. There is no early-exit to add - unlike bubble sort.

SPACE: O(1).  SWAPS: exactly n-1 - the fewest of the three.
STABLE: NO (see Part 1).
*/


/*
================================================================================
PART 3 : BUBBLE SORT
================================================================================
IDEA: repeatedly compare ADJACENT pairs and swap them if out of order. Each
pass "bubbles" the largest remaining element to the end.

Where selection sort pulls the MINIMUM to the front, bubble sort pushes the
MAXIMUM to the back.

WORKED EXAMPLE: 6, 5, 4, 3, 2, 1

  Pass 1 (5 comparisons):  5,6,4,3,2,1 -> 5,4,6,3,2,1 -> 5,4,3,6,2,1
                        -> 5,4,3,2,6,1 -> 5,4,3,2,1,6        6 is now final
  Pass 2 (4 comparisons):  4,5,3,2,1,6 -> 4,3,5,2,1,6
                        -> 4,3,2,5,1,6 -> 4,3,2,1,5,6        5 is now final
  Pass 3 (3 comparisons):  3,4,2,1,5,6 -> 3,2,4,1,5,6 -> 3,2,1,4,5,6
  Pass 4 (2 comparisons):  2,3,1,4,5,6 -> 2,1,3,4,5,6
  Pass 5 (1 comparison) :  1,2,3,4,5,6                       sorted

LOOP BOUNDS:
    Outer loop: n-1 passes
    Inner loop: n-1-i comparisons (the last i elements are already final, so
                there is no point re-checking them)
*/

// ---- Basic version, ascending ----
void bubbleAsc(int arr[], int n){
    for(int i = 0; i < n - 1; i++){
        for(int j = 0; j < n - 1 - i; j++){
            if(arr[j] > arr[j+1]){
                swap(arr[j], arr[j+1]);
            }
        }
    }
}
// TC - O(n^2) in ALL cases, including already-sorted input. SC - O(1).

// ---- Basic version, descending (just flip the comparison) ----
void bubbleDesc(int arr[], int n){
    for(int i = 0; i < n - 1; i++){
        for(int j = 0; j < n - 1 - i; j++){
            if(arr[j] < arr[j+1]){       // < instead of > - the ONLY change
                swap(arr[j], arr[j+1]);
            }
        }
    }
}

// ---- Equivalent formulation counting the outer loop downward ----
void bubbleCountingDown(int arr[], int n){
    for(int i = n - 1; i > 0; i--){
        for(int j = 0; j <= i - 1; j++){
            if(arr[j] > arr[j+1]){
                swap(arr[j], arr[j+1]);
            }
        }
    }
}
// Identical behavior to bubbleAsc - i just represents "the boundary of the
// unsorted region" directly instead of "how many passes are done".

/*
--------------------------------------------------------------------------------
OPTIMISATION: EARLY EXIT
--------------------------------------------------------------------------------
The basic version runs O(n^2) even on an already-sorted array, which is wasted
work. Key insight: IF A FULL PASS MAKES NO SWAPS, THE ARRAY IS ALREADY SORTED
and every remaining pass would also make no swaps. So we can stop.

This makes bubble sort ADAPTIVE, with a best case of O(n) - a single clean pass.
*/

void bubbleOptimal(int arr[], int n){
    for(int i = n - 1; i > 0; i--){
        bool swapped = false;
        for(int j = 0; j <= i - 1; j++){
            if(arr[j] > arr[j+1]){
                swap(arr[j], arr[j+1]);
                swapped = true;
            }
        }
        if(!swapped){
            break;                        // no swaps this pass -> fully sorted
        }
    }
}
/*
TRACE OF THE EARLY EXIT:

  1. [1,2,3,4]      already sorted
     i=3: j=0,1,2 - no swaps, swapped=false -> BREAK immediately
     Total: 1 pass = O(n)

  2. [1,3,2,4]
     i=3: swaps 3 and 2 -> [1,2,3,4], swapped=true -> continue
     i=2: no swaps -> BREAK
     Total: 2 passes

  3. [1,2,4,5,3]
     i=4: -> [1,2,4,3,5], swapped=true
     i=3: -> [1,2,3,4,5], swapped=true
     i=2: no swaps -> BREAK
     Total: 3 passes

TIME COMPLEXITY:
    Best    O(n)      already sorted - one pass, no swaps, exit
    Average O(n^2)
    Worst   O(n^2)    reverse sorted - every comparison swaps

SPACE: O(1).  STABLE: YES - it only ever swaps ADJACENT elements, and only when
strictly out of order, so equal elements are never swapped past each other.
*/

// ---- Descending, with early exit, on a vector ----
void bubbleDescOptimal(vector<int>& arr){
    int n = (int)arr.size();               // cast ONCE - see the warning below
    for(int i = 0; i < n - 1; i++){
        bool swapped = false;
        for(int j = 0; j < n - 1 - i; j++){
            if(arr[j] < arr[j+1]){
                swap(arr[j], arr[j+1]);
                swapped = true;
            }
        }
        if(!swapped){                       // FIX: the original had if(flag==true)
            break;                           // which is INVERTED
        }
    }
}
/*
***** BUG FIXED HERE - THE INVERTED EARLY EXIT *****
The original descending version read:

        if(flag==true)
            break;

That breaks out of the loop as soon as ANY swap happens - the exact opposite of
the intended "stop when nothing needed swapping". The result is that it does
one partial pass and quits, leaving the array unsorted.

VERIFIED BY TESTING on {3,1,4,1,5,9,2,6}:
    original version produced : 3 4 1 5 9 2 6 1     <-- not sorted at all
    corrected version produces: 9 6 5 4 3 2 1 1     <-- correct

The ascending version in the original had the correct `if(flag==false) break;`,
so this was a copy-paste slip in the descending variant - and one that a quick
eyeball test on a small already-nearly-sorted array could easily miss.
*/


/*
================================================================================
PART 4 : INSERTION SORT
================================================================================
IDEA: maintain a SORTED subarray at the front. Take the next element from the
unsorted portion and INSERT it into its correct position within the sorted part
by shifting larger elements right.

This is how most people sort a hand of playing cards.

The sorted region starts as just element 0 (a single element is trivially
sorted), and grows by one each pass.

WORKED EXAMPLE: 14, 9, 15, 12, 6, 8, 13   (n = 7)

  Pass 1: sorted = [14]
  Pass 2: insert 9   -> 9,14              sorted = [9,14]
  Pass 3: insert 15  -> 9,14,15           sorted = [9,14,15]   (no shift needed)
  Pass 4: insert 12  -> 9,12,14,15        sorted = [9,12,14,15]
  Pass 5: insert 6   -> 6,9,12,14,15      sorted = [6,9,12,14,15]
  Pass 6: insert 8   -> 6,8,9,12,14,15    sorted = [6,8,9,12,14,15]
  Pass 7: insert 13  -> 6,8,9,12,13,14,15 sorted, done
*/

// ---- Naive version: always walks all the way down ----
void insertionNaive(int arr[], int n){
    for(int i = 1; i < n; i++){            // start at 1 - element 0 is already "sorted"
        for(int j = i; j > 0; j--){
            if(arr[j] < arr[j-1]){
                swap(arr[j], arr[j-1]);
            }
            // no early exit - keeps looping even once the element has landed
        }
    }
}
/*
TC - O(n^2) in ALL cases, including already-sorted input.
     Comparisons = 1 + 2 + ... + (n-1) = n(n-1)/2

The inner loop runs to completion every time, even after the element has
already reached its correct spot. That wasted work is what the next version
removes.
*/

// ---- Optimised version: stop as soon as the element has landed ----
void insertionSort(int arr[], int n){
    for(int i = 1; i < n; i++){
        for(int j = i; j > 0 && arr[j] < arr[j-1]; j--){
            swap(arr[j], arr[j-1]);
        }
    }
}
/*
THE OPTIMISATION: the condition arr[j] < arr[j-1] moved INTO the loop header.

WHY THIS WORKS: the region to the left is already sorted. The moment
arr[j] >= arr[j-1], the element has found its place, and everything further
left is smaller still - so there is nothing left to check. Stop immediately.

Note this is a DIFFERENT technique from bubble sort's early exit. Bubble sort
uses a "did anything swap this whole pass?" flag to skip remaining PASSES.
Insertion sort exits the INNER loop early on each pass. The bubble-sort flag
trick does not apply here, which is what the original notes were getting at.

TIME COMPLEXITY:
    Best    O(n)      already sorted - the inner condition fails immediately
                       every time, so it's one comparison per element
    Average O(n^2)
    Worst   O(n^2)    reverse sorted - every element shifts all the way down

SPACE: O(1).  STABLE: YES - the strict < means equal elements never swap past
each other, so their original order survives.

WHY INSERTION SORT IS ACTUALLY USEFUL: it is genuinely fast on SMALL arrays
(roughly n < 20) and on NEARLY-SORTED data. Real-world library sorts exploit
this - std::sort uses introsort, which switches to insertion sort once
subarrays get small enough, because the low constant factor beats the overhead
of a smarter algorithm at that size.
*/

// ---- Vector version, descending ----
void insertionDesc(vector<int>& arr){
    int n = (int)arr.size();
    for(int i = 1; i < n; i++){
        for(int j = i; j > 0 && arr[j] > arr[j-1]; j--){   // > instead of <
            swap(arr[j], arr[j-1]);
        }
    }
}

/*
--------------------------------------------------------------------------------
***** BUG FIXED: THE OUT-OF-BOUNDS "while" FORMULATION *****
--------------------------------------------------------------------------------
The original file contained this variant:

        void insertion_sort_HisWay(int arr[], int n){
            int i, j;
            for(i = 0; i < n; i++){
                j = i + 1;                         // <-- the problem
                while(j > 0 && arr[j] < arr[j-1]){
                    swap(arr[j], arr[j-1]);
                    j--;
                }
            }
        }

With i running to n-1, j starts at n on the final pass - so arr[n] is read on
an array whose last valid index is n-1. That is a BUFFER OVERRUN, and it does
not merely read junk: it can SWAP that junk into the array.

VERIFIED BY TESTING. Sorting {5,4,3,2,1} with a sentinel value -999 placed
immediately after the array in memory:

    before : array = 5 4 3 2 1,  sentinel = -999
    after  : array = -999 1 2 3 4,  sentinel = 5

The out-of-bounds -999 was pulled INTO the array and the real value 5 was
pushed OUT past the end. The array is corrupted and an unrelated memory
location was overwritten.

THE FIX is either of these (both used above):
    for(int i = 1; i < n; i++){ int j = i; ... }     // j starts at i, max n-1
    for(int i = 0; i < n-1; i++){ int j = i+1; ... } // i stops one earlier

The bug hides easily because the value at arr[n] is often harmless in small
tests, and the array frequently still comes out looking sorted.
*/


/*
================================================================================
PART 5 : COMPARISON SUMMARY
================================================================================

  ALGORITHM        | BEST   | AVERAGE | WORST  | SPACE | STABLE | ADAPTIVE | SWAPS
  -----------------|--------|---------|--------|-------|--------|----------|-------
  Selection Sort   | O(n^2) | O(n^2)  | O(n^2) | O(1)  | NO     | NO       | O(n)
  Bubble (basic)   | O(n^2) | O(n^2)  | O(n^2) | O(1)  | YES    | NO       | O(n^2)
  Bubble (optimal) | O(n)   | O(n^2)  | O(n^2) | O(1)  | YES    | YES      | O(n^2)
  Insertion Sort   | O(n)   | O(n^2)  | O(n^2) | O(1)  | YES    | YES      | O(n^2)

KEY OBSERVATIONS:

  - All three are O(n^2) on average and in the worst case. None is usable for
    large n: at n = 10^5 that is 10^10 operations, roughly 100 seconds.

  - Bubble (optimised) and insertion reach O(n) on already-sorted input.
    Selection sort CANNOT - it has no way to detect sortedness.

  - Selection sort is the only one that is NOT stable, but it makes the FEWEST
    swaps (exactly n-1). If writes are expensive, that matters.

  - Of the three, INSERTION SORT is the one worth actually knowing well: it is
    stable, adaptive, has a low constant factor, and is used inside real
    library sorts for small subarrays.

PRACTICAL GUIDANCE: for anything real, use std::sort - it is O(n log n).
These three are worth learning because they teach loop invariants, in-place
manipulation, and the stable/adaptive concepts, not because you will deploy them.
*/


/*
================================================================================
PART 6 : TWO TRAPS THESE ALGORITHMS EXPOSE
================================================================================

--------------------------------------------------------------------------------
TRAP 1 : arr.size() IS UNSIGNED
--------------------------------------------------------------------------------
vector::size() returns size_t, which is UNSIGNED. So on an EMPTY vector:

    arr.size() - 1   ->   0 - 1   ->   WRAPS AROUND to the maximum value

VERIFIED BY TESTING:
    empty.size()     = 0
    empty.size() - 1 = 18446744073709551615

A loop written as  for(size_t i = 0; i < arr.size()-1; i++)  therefore does NOT
skip the body on an empty vector - it runs essentially forever, indexing far
out of bounds.

Every vector-based sort in the original file used this pattern, so all of them
would break on an empty input.

THREE SAFE FIXES:
    int n = (int)arr.size();                  // cast once, then use n  (used above)
    for(int i = 0; i + 1 < (int)arr.size(); i++)   // rearrange to avoid subtracting
    if(arr.empty()) return;                    // guard at the top

Comparing a signed int against an unsigned size() also triggers
-Wsign-compare warnings, which the cast-once approach removes.

--------------------------------------------------------------------------------
TRAP 2 : LEFTOVER DEBUG OUTPUT
--------------------------------------------------------------------------------
The original bubbleOptimal contained  cout << "ran" << endl;  inside the outer
loop, and several sorts printed a comparison counter. Useful while tracing by
hand - but a sort function should SORT, not print. On a judge, stray output is
an instant Wrong Answer.

If you want to count operations while learning, pass a counter by reference or
return it, so the printing stays in main() where you control it:

    void insertionSort(int arr[], int n, int& comparisons);
*/


/*
================================================================================
PART 7 : WHERE THE O(n^2) BARRIER ENDS
================================================================================
These three sorts all work by COMPARING pairs of elements. There is a proven
lower bound for that entire class:

    ANY comparison-based sort needs at least Omega(n log n) comparisons
    in the worst case.

Reasoning sketch: there are n! possible orderings, and each comparison yields
one bit of information (yes/no), so you need at least log2(n!) comparisons to
distinguish them all - and log2(n!) is approximately n log n.

So O(n log n) is the BEST any comparison sort can do, and merge sort / quick
sort / heap sort achieve it. (Covered separately.)

BEATING n log n IS POSSIBLE ONLY BY NOT COMPARING:
Counting sort, radix sort and bucket sort achieve O(n) or O(n + k) by using the
VALUES themselves as array indices - the same hashing idea from the hashing
notes. The catch is that they only work on restricted inputs (small integer
ranges) and use O(k) extra space, where k is the value range.

    Counting sort sketch, for values in 0..k:
        1. Count occurrences of each value into a hash array of size k+1
        2. Walk the hash array in order, emitting each value count times
    TC - O(n + k), SC - O(k), and it is stable if implemented carefully.
*/


/*
================================================================================
PART 8 : COMMON MISTAKES CHECKLIST
================================================================================
  [X] j = i+1 with i running to n-1     -> reads arr[n], out of bounds; it can
                                            swap junk INTO the array
  [X] Inverted early-exit flag          -> if(swapped) break  stops on the FIRST
                                            swap; it must be if(!swapped) break
  [X] arr.size()-1 on an empty vector   -> unsigned underflow to a huge number;
                                            cast to int or guard with empty()
  [X] Claiming best case is O(1)        -> the best case for insertion/bubble is
                                            O(n): you still must inspect every
                                            element once to confirm sortedness
  [X] Expecting selection sort to have  -> it cannot detect sorted input; it is
      an O(n) best case                     O(n^2) always
  [X] Assuming all simple sorts are     -> selection sort is NOT stable
      stable
  [X] Debug cout left inside a sort     -> Wrong Answer on a judge
  [X] Off-by-one in the inner bound     -> use n-1-i (not n-i); j+1 must stay
                                            within the array
  [X] int arr[n] with runtime n         -> non-standard VLA; use vector<int>(n)
================================================================================
*/


int main(){
    int n;
    cin >> n;

    // FIX: the original used `int arr[n];` - a non-standard variable length
    // array. It compiles on g++ as an extension but is rejected by
    // -pedantic-errors and by MSVC, and it lives on the small stack.
    vector<int> arr(n);
    for(int i = 0; i < n; i++){
        cin >> arr[i];
    }

    insertionSort(arr.data(), n);        // .data() gives the raw int* the
                                          // array-based functions expect

    for(int i = 0; i < n; i++){
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}