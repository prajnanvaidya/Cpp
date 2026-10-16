#include<bits/stdc++.h>
using namespace std;

/*
================================================================================
                    RECURSIVE SORTING - BUBBLE & INSERTION
================================================================================
Bubble sort and insertion sort are naturally ITERATIVE - two nested loops. This
file converts them to RECURSIVE form.

THE CONVERSION RECIPE (it is the same for both):

    The OUTER loop becomes the RECURSION.
    The INNER loop stays exactly as it is.
    The loop variable becomes a PARAMETER.
    The loop's exit condition becomes the BASE CASE.

That is the whole trick. A loop like  for(i = 0; i < n; i++) { body }  becomes
a function taking i as a parameter, with  if(i >= n) return;  at the top, the
body in the middle, and a call with i+1 at the bottom.

IMPORTANT UP FRONT: recursion here buys you NOTHING in performance. It is the
same algorithm with the same O(n^2) time, but it costs O(n) STACK SPACE instead
of O(1), and it can crash on large inputs (Part 5). This is a teaching exercise
about converting loops to recursion, not an optimisation.

TABLE OF CONTENTS
-----------------
  PART 1  : Iterative bubble sort (the starting point)
  PART 2  : Recursive bubble sort
  PART 3  : Iterative insertion sort
  PART 4  : Recursive insertion sort
  PART 5  : Recursion cost - why these are worse than the loops
  PART 6  : Two real bugs found in the original
  PART 7  : Bonus - recursive selection sort
  PART 8  : Common mistakes checklist

================================================================================
PART 1 : ITERATIVE BUBBLE SORT (THE STARTING POINT)
================================================================================
Compare ADJACENT pairs and swap them if out of order. Each pass pushes the
largest remaining element to the end - it "bubbles" up.

After pass i, the last i elements are in their final positions, so the inner
loop only needs to go up to n-i.
*/

void bubbleIterative(int arr[], int n){
    for(int i = 0; i < n - 1; i++){        // n-1 passes are enough: once n-1
        for(int j = 1; j < n - i; j++){    // elements are placed, the last one
            if(arr[j-1] > arr[j]){          // has nowhere else to be
                swap(arr[j-1], arr[j]);
            }
        }
    }
}
// TC - O(n^2) always.  SC - O(1).
// NOTE: the original used i < n, which runs one extra pass. On that final pass
// the inner condition is j < n-(n-1) = 1, and j starts at 1, so the loop body
// never executes. Harmless, but n-1 states the intent correctly.

/*
--------------------------------------------------------------------------------
THE OPTIMISATION: EARLY EXIT
--------------------------------------------------------------------------------
KEY INSIGHT: if a full pass makes ZERO swaps, the array is already sorted -
and every later pass would also make zero swaps. So stop immediately.

This makes bubble sort ADAPTIVE, giving it an O(n) best case.
*/

void bubbleIterativeOptimal(int arr[], int n){
    for(int i = 0; i < n - 1; i++){
        bool swapped = false;               // RESET at the start of EVERY pass
        for(int j = 1; j < n - i; j++){
            if(arr[j-1] > arr[j]){
                swap(arr[j-1], arr[j]);
                swapped = true;
            }
        }
        if(!swapped) break;                 // nothing moved -> fully sorted
    }
}
// TC - O(n) best case, O(n^2) average and worst.  SC - O(1).
//
// The reset inside the outer loop is the entire point of the flag. It must
// answer "did anything swap during THIS pass?", not "has anything ever
// swapped?". Forgetting the reset is exactly what broke the original recursive
// version - see Part 6, Bug 2.


/*
================================================================================
PART 2 : RECURSIVE BUBBLE SORT
================================================================================
Apply the recipe: the outer loop's variable becomes a parameter, its exit
condition becomes the base case, the inner loop is untouched.

    for(int i = 0; i < n-1; i++){ inner loop }

becomes

    if(cnt >= n-1) return;        // base case
    inner loop
    recurse with cnt+1
*/

void bubbleRecursive(int arr[], int n, int cnt = 0){
    if(cnt >= n - 1) return;                // base case: all passes done

    for(int j = 1; j < n - cnt; j++){       // one full pass - unchanged
        if(arr[j-1] > arr[j]){
            swap(arr[j-1], arr[j]);
        }
    }
    bubbleRecursive(arr, n, cnt + 1);       // next pass
}
// TC - O(n^2).  SC - O(n) for the call stack (vs O(1) iterative).
//
// NOTE on cnt+1 vs ++cnt: the original wrote bubbleRecursive(arr, n, ++cnt).
// That works, since cnt is a local copy, but it mutates the current frame's
// variable as a side effect of building the argument. cnt+1 says "call with one
// more" without touching anything, which is clearer and avoids a habit that
// causes real bugs when the variable is used again after the call.

/*
--------------------------------------------------------------------------------
RECURSIVE VERSION WITH THE EARLY EXIT
--------------------------------------------------------------------------------
The flag must be a LOCAL variable, freshly created on every call - because each
call IS one pass, and the question is always "did anything swap during THIS
pass?"

If instead you thread the flag through as a parameter carrying the previous
call's value, it can never go back to false, and the optimisation silently dies.
That is exactly what happened in the original - see Part 6, Bug 2.
*/

void bubbleRecursiveOptimal(int arr[], int n, int cnt = 0){
    if(cnt >= n - 1) return;

    bool swapped = false;                   // LOCAL - fresh every call
    for(int j = 1; j < n - cnt; j++){
        if(arr[j-1] > arr[j]){
            swap(arr[j-1], arr[j]);
            swapped = true;
        }
    }
    if(!swapped) return;                     // no swaps -> sorted -> stop

    bubbleRecursiveOptimal(arr, n, cnt + 1);
}
/*
TC - O(n) best case, O(n^2) worst.  SC - O(n) worst case stack, O(1) best case
     (it returns after a single call).

VERIFIED BY TESTING on an already-sorted array of 8 elements:
    original version : 9 recursive calls   (optimisation never fired)
    this version     : 1 recursive call    (exits after one clean pass)

Note this is TAIL RECURSIVE - the recursive call is the last operation, nothing
happens after it returns. A compiler with optimisation enabled (-O2) can
therefore collapse it into a loop and use O(1) stack. But that is NOT guaranteed
by the C++ standard, so do not rely on it - see Part 5.
*/


/*
================================================================================
PART 3 : ITERATIVE INSERTION SORT (THE STARTING POINT)
================================================================================
Maintain a SORTED region at the front of the array. Each pass takes the next
element from the unsorted region and slides it LEFT into its correct place
within the sorted region.

This is how people sort a hand of playing cards.

    [ sorted so far | element to insert | still unsorted ]
                      ^ slide this one left until it fits

The sorted region starts as just element 0 (one element is trivially sorted),
which is why the outer loop starts at i = 1, not 0.
*/

void insertionIterative(int arr[], int n){
    for(int i = 1; i < n; i++){             // element 0 is already "sorted"
        int j = i;
        while(j > 0 && arr[j-1] > arr[j]){  // slide left while out of order
            swap(arr[j-1], arr[j]);
            j--;                             // MOVE the pointer left
        }
    }
}
/*
TC - O(n) best case, O(n^2) average and worst.  SC - O(1).

WHY THE BEST CASE IS O(n): the condition arr[j-1] > arr[j] fails immediately on
already-sorted input, so the while loop exits after one comparison per element.
The region to the left is already sorted, so once the element fits, everything
further left is smaller still and there is nothing left to check.

Insertion sort needs no separate "optimisation" like bubble sort's flag - the
early exit is built into the while condition itself.

THE j-- IS ESSENTIAL. It is what makes the element travel. Without it, the loop
swaps one pair, the condition immediately becomes false, and the element stops
after moving a single position. See Part 6, Bug 1.
*/


/*
================================================================================
PART 4 : RECURSIVE INSERTION SORT
================================================================================
Same recipe: the outer loop becomes recursion, the inner while loop stays.
*/

void insertionRecursive(int arr[], int n, int cnt = 1){
    if(cnt >= n) return;                    // base case: past the last element

    int j = cnt;
    while(j > 0 && arr[j-1] > arr[j]){
        swap(arr[j-1], arr[j]);
        j--;                                 // <-- the line the original omitted
    }

    insertionRecursive(arr, n, cnt + 1);
}
/*
TC - O(n) best, O(n^2) worst.  SC - O(n) call stack.

The default cnt = 1 mirrors the iterative version starting at i = 1. Starting at
0 also works (j=0 makes the while condition false immediately, so it is just a
wasted call), but 1 states the invariant properly: "elements 0..cnt-1 are
already sorted".

Like the recursive bubble version, this is tail recursive.
*/


/*
================================================================================
PART 5 : RECURSION COST - WHY THESE ARE WORSE THAN THE LOOPS
================================================================================
Converting a loop to recursion does not make it faster. It costs real memory.

    ITERATIVE:  O(1) space - a couple of loop counters
    RECURSIVE:  O(n) space - one stack frame per pass, all alive at once

Each recursive call pushes a frame holding arr, n, cnt and a return address.
The call at depth n-1 only returns after everything below it has, so ALL n
frames are alive simultaneously at the deepest point.

The stack is small - typically ~1 MB on Windows, ~8 MB on Linux. Overflowing it
is not a slowdown, it is a hard crash.

VERIFIED BY TESTING (8 MB stack, compiled without optimisation):

    RECURSIVE insertion, n =  10,000  ->  fine
    RECURSIVE insertion, n = 100,000  ->  fine
    RECURSIVE insertion, n = 200,000  ->  SEGMENTATION FAULT
    ITERATIVE insertion, n = 200,000  ->  fine

Same algorithm, same complexity, same output - one crashes and one does not.

--------------------------------------------------------------------------------
A NOTE ON TAIL CALL OPTIMISATION
--------------------------------------------------------------------------------
Both recursive sorts here are TAIL RECURSIVE: the recursive call is the very
last thing that happens, so the current frame is useless afterwards. A compiler
MAY reuse the frame instead of pushing a new one, turning the recursion into a
loop and dropping space to O(1).

But the C++ standard does NOT require this. Whether you get it depends on the
compiler AND the optimisation level - g++ generally does it at -O2 but not at
-O0. So write tail-recursive form when it is natural, but never RELY on it for
correctness. If you need a guarantee, write the loop.

WHEN RECURSION IS ACTUALLY THE RIGHT CHOICE: when the problem is genuinely
self-similar and branches - merge sort, quicksort, tree traversal, backtracking.
Those recurse to depth O(log n), not O(n), and expressing them iteratively means
hand-building the exact stack recursion gave you for free. Bubble and insertion
sort are neither self-similar nor branching, which is why the recursive versions
are strictly a downgrade.
*/


/*
================================================================================
PART 6 : TWO REAL BUGS FOUND IN THE ORIGINAL
================================================================================

--------------------------------------------------------------------------------
BUG 1 : MISSING j-- IN THE RECURSIVE INSERTION SORT  (CORRECTNESS - severe)
--------------------------------------------------------------------------------
The original read:

        void insertionRec(int arr[], int n, int cnt=0){
            if(cnt>=n) return;
            int j=cnt;
            while(j>0 && arr[j-1]>arr[j]){
                swap(arr[j-1], arr[j]);
                                              // <-- j-- is MISSING
            }
            insertionRec(arr, n, ++cnt);
        }

WHY IT BREAKS: after swapping arr[j-1] and arr[j], those two values have traded
places, so arr[j-1] < arr[j] is now true and the loop condition FAILS. The loop
exits after exactly ONE swap. The element moves a single position instead of
sliding all the way to where it belongs.

Interestingly the loop does not spin forever - it exits immediately - which is
why the bug produces silently wrong output rather than a hang.

VERIFIED BY TESTING:
        input : 5 2 9 1 7 3
        output: 2 5 1 7 3 9        <-- NOT SORTED
        expect: 1 2 3 5 7 9

Note this bug exists ONLY in the recursive version. The iterative insertionSort
in the same file has the j-- and works correctly - the line was simply dropped
during the conversion.

--------------------------------------------------------------------------------
BUG 2 : is_swapped NEVER RESET  (PERFORMANCE - the optimisation is dead)
--------------------------------------------------------------------------------
The original read:

        void BubbleRecOptimal(int arr[], int n, int cnt=0, int is_swapped=1){
            if(cnt>=n || !is_swapped) return;
            for(int j=1;j<n-cnt;j++){
                if(arr[j-1]>arr[j]){
                    swap(arr[j-1], arr[j]);
                    is_swapped=1;              // only ever SET to 1
                }
            }
            BubbleRecOptimal(arr, n, ++cnt, is_swapped);
        }

WHY IT BREAKS: is_swapped arrives as 1 (the default), and inside the function it
is only ever assigned 1 - never reset to 0. So it is 1 forever, !is_swapped is
never true, and the early exit NEVER FIRES. The function still sorts correctly,
it just does all n passes every time, exactly like the unoptimised version.

VERIFIED BY TESTING on an already-sorted array of 8 elements:
        original version : 9 recursive calls    <-- optimisation never fired
        corrected version: 1 recursive call

THE FIX: make the flag a LOCAL variable, created fresh on each call and set to
false before the pass begins. Each call is ONE pass, so the flag must answer
"did anything swap during THIS pass?" - a value threaded in from the previous
call cannot answer that.

This is a good illustration of a general principle when converting loops to
recursion: anything RESET at the top of the loop body must become a LOCAL
variable in the function, not a parameter. Only things that CARRY FORWARD
between iterations (like cnt) should be parameters.
*/


/*
================================================================================
PART 7 : BONUS - RECURSIVE SELECTION SORT
================================================================================
Completing the set. Same recipe: outer loop -> recursion, inner loop unchanged.

Selection sort repeatedly finds the MINIMUM of the unsorted region and swaps it
into place at the front.
*/

void selectionRecursive(int arr[], int n, int cnt = 0){
    if(cnt >= n - 1) return;

    int mini = cnt;
    for(int j = cnt + 1; j < n; j++){        // find the minimum - unchanged
        if(arr[j] < arr[mini]) mini = j;
    }
    swap(arr[mini], arr[cnt]);

    selectionRecursive(arr, n, cnt + 1);
}
/*
TC - O(n^2) in ALL cases.  SC - O(n) call stack.

Selection sort has NO early-exit optimisation available, iterative or recursive.
It cannot detect that the array is already sorted, because it must scan the
entire remaining region every pass just to confirm where the minimum is. So
unlike bubble and insertion, its best case is still O(n^2).

It is also NOT STABLE - it swaps distant elements, which can jump one equal
element past another. Bubble and insertion are both stable, since they only ever
swap ADJACENT elements that are strictly out of order.
*/


/*
================================================================================
PART 8 : COMMON MISTAKES CHECKLIST
================================================================================
  [X] Dropping j-- when converting the      -> the element moves one position
      inner loop to recursion                  and stops; silently wrong output
  [X] Passing the "swapped" flag as a       -> it can never go back to false, so
      parameter instead of a local             the early exit never fires
  [X] Forgetting to reset the flag each     -> same effect: the optimisation is
      pass                                     dead but the code still "works"
  [X] Base case cnt >= n instead of n-1     -> one wasted pass (harmless, but
                                               it hides the real invariant)
  [X] Using ++cnt in the recursive call     -> works, but mutates the current
                                               frame as a side effect; cnt+1 is
                                               clearer and safer
  [X] Assuming recursion is faster          -> same O(n^2) time, but O(n) space
                                               instead of O(1)
  [X] Relying on tail call optimisation     -> not guaranteed by the standard;
                                               depends on compiler and -O level
  [X] Recursing once per element on large   -> stack overflow; VERIFIED to
      input                                    segfault at n = 200,000 where the
                                               iterative version is fine
  [X] int arr[n] with runtime n             -> non-standard VLA; use vector
================================================================================
*/


int main(){
    int n;
    cin >> n;

    // FIX: the original used `int arr[n];` - a non-standard variable length
    // array that lives on the small stack. vector is the correct way to size
    // from runtime input.
    vector<int> arr(n);
    for(int i = 0; i < n; i++){
        cin >> arr[i];
    }

    insertionRecursive(arr.data(), n);      // .data() gives the raw int*

    for(int i = 0; i < n; i++){
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}