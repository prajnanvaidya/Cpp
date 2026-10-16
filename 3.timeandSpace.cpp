#include <bits/stdc++.h>

/*
================================================================================
                    TIME AND SPACE COMPLEXITY - COMPLETE NOTES
================================================================================

TABLE OF CONTENTS
-----------------
  PART 1  : What complexity is (and is not)
  PART 2  : Big O rules - why we drop constants and lower terms
  PART 3  : Best / Average / Worst case
  PART 4  : Big O vs Theta vs Omega (the real definitions)
  PART 5  : The complexity hierarchy
  PART 6  : Where log n comes from
  PART 7  : Worked examples - loops
  PART 8  : Multiple input variables (N and M)
  PART 9  : Recursive time complexity
  PART 10 : Amortized complexity
  PART 11 : Space complexity
  PART 12 : Space complexity of recursion
  PART 13 : Constraints -> required complexity (CP cheat sheet)
  PART 14 : STL container complexity reference
  PART 15 : Common mistakes checklist

================================================================================
PART 1 : WHAT COMPLEXITY IS (AND IS NOT)
================================================================================

Time complexity != time taken.

The number of seconds a program runs depends on the machine, the compiler, the
CPU load, the language, etc. That is NOT what we measure.

    TIME COMPLEXITY = the RATE at which the running time grows
                      as the input size grows.

It answers: "if I double the input, what happens to the work done?"
    - stays the same        -> O(1)
    - doubles               -> O(n)
    - squares               -> O(n^2)
    - adds one more step    -> O(log n)

This is why complexity is machine-independent. It describes the SHAPE of growth,
not the absolute cost.

--------------------------------------------------------------------------------
Example A:

    for (int i = 1; i <= 5; i++) {
        cout << "Raj";
    }

If you count individual steps (init, compare, increment, print) you might arrive
at some number like 15. But that number is FIXED - it does not depend on any
input size at all. No matter what data you feed the program, it does 15 steps.

    Time complexity = O(1)      <-- NOT O(15). Constants are dropped.

--------------------------------------------------------------------------------
Example B:

    for (int i = 1; i <= N; i++) {
        cout << "Raj";
    }

Now the work depends on N. If each iteration costs ~3 elementary steps, the raw
count is 3N.

    Raw count      = 3N
    Time complexity = O(N)      <-- NOT O(3N). Constants are dropped.

The point of Example A vs B: what matters is whether the count is TIED to the
input size, not how big the count happens to be.


================================================================================
PART 2 : BIG O RULES - WHY WE DROP CONSTANTS AND LOWER TERMS
================================================================================

Big O follows three rules:
    1. Consider the worst case (by convention, in practice)
    2. Drop constant factors
    3. Drop lower-order terms

--------------------------------------------------------------------------------
WHY DROP LOWER-ORDER TERMS?

Take f(N) = 4N^3 + 3N^2 + 8, with N = 10^5.

    4 * N^3 = 4 * (10^5)^3 = 4 * 10^15     <-- dominant
    3 * N^2 = 3 * (10^5)^2 = 3 * 10^10     <-- 100,000x smaller
    8                      = 8             <-- utterly negligible

The N^3 term is 100,000 times larger than the N^2 term, and 10^14 times larger
than the constant. As N grows, the gap only widens. The smaller terms contribute
essentially nothing to the growth behaviour.

    O(4N^3 + 3N^2 + 8)  ==>  O(N^3)

--------------------------------------------------------------------------------
WHY DROP CONSTANT FACTORS?

Because the constant depends on things Big O deliberately ignores: how many
machine instructions your compiler emits, how fast the CPU is, cache behaviour.
An O(2N) algorithm and an O(5N) algorithm both scale linearly - that is the
information Big O is designed to convey.

    O(4N^3)  ==>  O(N^3)

NOTE: constants DO matter in real-world performance. Two O(N) algorithms can
differ 10x in wall-clock time. Big O just is not the tool for capturing that.


================================================================================
PART 3 : BEST / AVERAGE / WORST CASE
================================================================================

    if (marks < 25)       cout << "grade D";
    else if (marks < 45)  cout << "grade C";
    else if (marks < 65)  cout << "grade B";
    else                  cout << "grade A";

    marks = 10  -> 1 comparison   (best case)
    marks = 70  -> 3 comparisons  (worst case)

All of these are O(1) since none of them depend on an input SIZE - but the
best/worst distinction is still visible in the raw step count.

--------------------------------------------------------------------------------
A better example - LINEAR SEARCH in an array of n elements:

    Best case    : target is at index 0            -> 1 comparison    -> O(1)
    Worst case   : target is at the last index,
                   or absent entirely              -> n comparisons   -> O(n)
    Average case : target equally likely at any
                   position                        -> ~n/2 comparisons -> O(n)

--------------------------------------------------------------------------------
IMPORTANT CORRECTION:

    Average case IS NOT (best + worst) / 2.

Average case = the EXPECTED number of operations across all possible inputs,
weighted by how likely each input is. It is a probability-weighted mean over
the entire input space.

For linear search with a uniform distribution:
    average = (1 + 2 + 3 + ... + n) / n = (n+1)/2

That happens to look like (best+worst)/2 here, but only by coincidence of the
uniform distribution. For other algorithms it breaks completely:

    QUICKSORT:
        Best    : O(n log n)
        Worst   : O(n^2)
        Average : O(n log n)     <-- NOT (n log n + n^2)/2

Quicksort's average is O(n log n) because bad pivot choices are rare, not
because you average the two extremes.

--------------------------------------------------------------------------------
WHY DO WE USUALLY REPORT THE WORST CASE?

Because engineering means guaranteeing behaviour. "It is usually fast" is not a
promise you can build a system on. The worst case is the only number that says
"this will NEVER be slower than X", which is what you need when a server has a
1-second timeout or a user is waiting on a response.


================================================================================
PART 4 : BIG O vs THETA vs OMEGA (THE REAL DEFINITIONS)
================================================================================

A very common (but wrong) shortcut says:
    Big O    = worst case
    Theta    = average case
    Omega    = best case

That is NOT what they mean. They are about BOUNDING A FUNCTION, not about cases.

    O(f(n))      Upper bound.  "grows no FASTER than f(n)"
    Omega(f(n))  Lower bound.  "grows no SLOWER than f(n)"
    Theta(f(n))  Tight bound.  "grows EXACTLY like f(n)" (both O and Omega)

You can apply any of the three to any of the cases. All of these are valid:

    "Linear search worst case is Theta(n)"       <-- tight bound on worst case
    "Linear search best case is Theta(1)"        <-- tight bound on best case
    "Quicksort average case is O(n log n)"       <-- upper bound on average case
    "Any comparison sort is Omega(n log n)"      <-- lower bound on ALL sorts

WHY THE CONFUSION EXISTS: in practice we almost always state the WORST case
using BIG O, so the two got glued together in people's heads. Know the real
definition - it comes up in interviews.


================================================================================
PART 5 : THE COMPLEXITY HIERARCHY
================================================================================

From fastest (best) to slowest (worst). Memorise this ordering.

    O(1)         Constant      - array index access, hash lookup (avg)
    O(log n)     Logarithmic   - binary search, heap push/pop, map find
    O(sqrt n)    Root          - trial division primality check
    O(n)         Linear        - single loop over data, linear search
    O(n log n)   Linearithmic  - efficient sorting (sort, merge sort, heapsort)
    O(n^2)       Quadratic     - nested loop, bubble/selection/insertion sort
    O(n^3)       Cubic         - triple nested loop, naive matrix multiply
    O(2^n)       Exponential   - subsets of a set, naive recursive fibonacci
    O(n!)        Factorial     - all permutations, brute-force TSP

Concrete feel for how brutal the difference is, at n = 1,000,000:

    O(1)         ->                    1 operation
    O(log n)     ->                   20 operations
    O(n)         ->            1,000,000 operations
    O(n log n)   ->           20,000,000 operations
    O(n^2)       ->    1,000,000,000,000 operations   (would take ~hours)
    O(2^n)       ->    more operations than atoms in the universe


================================================================================
PART 6 : WHERE log n COMES FROM
================================================================================

log2(n) answers: "how many times can I halve n before reaching 1?"
Equivalently:    "how many levels does a binary tree need to hold n nodes?"

    n = 8        -> 3 halvings   (8 -> 4 -> 2 -> 1)
    n = 16       -> 4
    n = 1024     -> 10
    n = 1,000,000-> ~20

The defining property: DOUBLING n only adds ONE more step. That is what makes
logarithmic algorithms feel almost free at any realistic scale.

Whenever an algorithm repeatedly HALVES the problem, or walks the height of a
BALANCED tree, you get log n:

    - Binary search       : halves the search range each step
    - Heap push/pop       : walks one root-to-leaf path (height = log n)
    - map / set find      : walks one path down a balanced BST (Red-Black tree)
    - Binary exponentiation: halves the exponent each step

--------------------------------------------------------------------------------
WHERE n log n COMES FROM

You do O(log n) work, n times over - or you split into log n levels and do O(n)
work per level.

    MERGE SORT:
        levels of splitting        = log n
        merging work per level     = n
        total                      = n * log n

    SORTING BY INSERTING INTO A SET:
        n insertions, each O(log n) = n log n


================================================================================
PART 7 : WORKED EXAMPLES - LOOPS
================================================================================

--------------------------------------------------------------------------------
Q1. Nested loops, both bounded by N

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            // constant time work
        }
    }

    Inner loop runs N times, for each of N outer iterations.
    Total = N * N = N^2

    Time complexity = O(N^2)

Note: we treat the constant-time body as ONE unit. Even if the body contains
9 statements, that gives 9*N^2, and the 9 is dropped.

--------------------------------------------------------------------------------
Q2. Triangular nested loop

    for (int i = 0; i < N; i++) {
        for (int j = 0; j <= i; j++) {
            // constant time work
        }
    }

    Trace (note: i stops at N-1, since the condition is i < N):

        i = 0      -> j runs 1 time
        i = 1      -> j runs 2 times
        i = 2      -> j runs 3 times
        ...
        i = N-1    -> j runs N times

    Total = 1 + 2 + 3 + ... + N
          = N(N+1)/2
          = N^2/2 + N/2

    Drop the constant (1/2) and the lower term (N/2):

    Time complexity = O(N^2)

KEY INSIGHT: doing "only half the work" of a full double loop does NOT improve
the complexity class. O(N^2/2) is still O(N^2).

--------------------------------------------------------------------------------
Q3. Sequential (not nested) loops

    for (int i = 0; i < N; i++) { /* work */ }     // O(N)
    for (int j = 0; j < N; j++) { /* work */ }     // O(N)

    Total = N + N = 2N

    Time complexity = O(N)

Sequential loops ADD. Nested loops MULTIPLY.

--------------------------------------------------------------------------------
Q4. Loop with multiplicative step

    for (int i = 1; i < N; i = i * 2) { /* work */ }

    i takes values: 1, 2, 4, 8, 16, ... up to N
    Number of iterations = log2(N)

    Time complexity = O(log N)

--------------------------------------------------------------------------------
Q5. Outer linear, inner logarithmic

    for (int i = 0; i < N; i++) {
        for (int j = 1; j < N; j = j * 2) { /* work */ }
    }

    Time complexity = O(N log N)

--------------------------------------------------------------------------------
Q6. Loop bound independent of N

    for (int i = 0; i < 1000; i++) { /* work */ }

    Time complexity = O(1)

1000 is a constant. It never grows with input, so it is dropped entirely.


================================================================================
PART 8 : MULTIPLE INPUT VARIABLES (N AND M)
================================================================================

A very common beginner error is collapsing two independent sizes into one.

    for (int i = 0; i < N; i++) { /* work */ }
    for (int j = 0; j < M; j++) { /* work */ }

    Time complexity = O(N + M)          <-- NOT O(N) and NOT O(2N)

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) { /* work */ }
    }

    Time complexity = O(N * M)          <-- NOT O(N^2)

You CANNOT simplify O(N+M) to O(N) unless you know that M is bounded by N.
If N = 10^5 and M = 10^9, calling it O(N) would be a serious mis-statement.

Real example - iterating a 2D grid with R rows and C columns:

    Time complexity = O(R * C)

If the grid happens to be square (R == C == n), then and only then is it O(n^2).


================================================================================
PART 9 : RECURSIVE TIME COMPLEXITY
================================================================================

For recursion, count the total number of function calls made (the size of the
"recursion tree").

--------------------------------------------------------------------------------
Example 1 - linear recursion

    int factorial(int n) {
        if (n == 0) return 1;
        return n * factorial(n - 1);
    }

    Calls: factorial(n) -> factorial(n-1) -> ... -> factorial(0)
    Total calls = n + 1

    Time complexity = O(n)

--------------------------------------------------------------------------------
Example 2 - binary recursion (exponential blowup)

    int fib(int n) {
        if (n <= 1) return n;
        return fib(n - 1) + fib(n - 2);
    }

    Each call spawns TWO more calls. The recursion tree roughly doubles in width
    at every level, and its depth is n:

                        fib(5)
                     /          \
                fib(4)          fib(3)
               /     \          /     \
           fib(3)   fib(2)  fib(2)   fib(1)
           ...

    Number of nodes ~ 2^n

    Time complexity = O(2^n)          <-- catastrophic
    Space complexity = O(n)           <-- max depth of the call stack

    With memoization (caching results), each fib(k) is computed once:
    Time complexity = O(n), Space complexity = O(n)

--------------------------------------------------------------------------------
Example 3 - divide and conquer

    Merge sort splits into 2 halves and does O(n) merging work:

        T(n) = 2 * T(n/2) + O(n)

        Depth of splitting  = log n
        Work per level      = n
        Time complexity     = O(n log n)

--------------------------------------------------------------------------------
Example 4 - binary search (recursive)

    Halves the range, does no per-level linear work:

        T(n) = T(n/2) + O(1)

        Time complexity = O(log n)


================================================================================
PART 10 : AMORTIZED COMPLEXITY
================================================================================

Some operations are usually cheap but occasionally expensive. Amortized
complexity = the AVERAGE cost per operation over a long sequence of operations.

    vector<int> v;
    v.push_back(x);       // amortized O(1)

WHY: a vector holds a fixed-capacity array. Most push_backs just write into the
next free slot - O(1). But when capacity fills up, the vector allocates a NEW
array of DOUBLE the size and copies everything over - that single push_back
costs O(n).

Because the capacity DOUBLES each time, resizes become exponentially rarer:

    resize at size 1, 2, 4, 8, 16, 32, ... n

    total copy work across n push_backs = 1 + 2 + 4 + ... + n ~= 2n
    cost per push_back                  = 2n / n = 2 = O(1)

So the expensive resizes are spread thin enough that the average stays constant.
That is why push_back is quoted as "amortized O(1)" rather than plain O(1).

Same idea applies to unordered_map insertion (rehashing when load factor grows).


================================================================================
PART 11 : SPACE COMPLEXITY
================================================================================

    SPACE COMPLEXITY = the RATE at which memory usage grows with input size.

Exactly like time complexity, this is about GROWTH, not exact bytes. An int may
be 4 bytes and a long long 8 bytes, and this varies by machine and compiler -
all of that is a constant factor and gets dropped.

    SPACE COMPLEXITY = Input space + Auxiliary space

        Input space     : memory holding the input itself
        Auxiliary space : EXTRA memory your algorithm allocates to do its work

In interviews and CP, "space complexity" almost always means AUXILIARY space,
because you had no choice about the input's size.

--------------------------------------------------------------------------------
Example 1:

    input : a, b
    code  : int c = a + b;

    Input space     = 2 variables  -> O(1)
    Auxiliary space = 1 variable   -> O(1)
    Space complexity = O(1)         <-- NOT O(3). Constants are dropped.

--------------------------------------------------------------------------------
Example 2:

    int arr[N];                          // O(N) space
    vector<vector<int>> mat(N,
                 vector<int>(N));        // O(N^2) space

--------------------------------------------------------------------------------
Example 3 - O(1) auxiliary space:

    int sumArray(vector<int>& arr) {
        int sum = 0;                     // one variable, never grows
        for (int x : arr) sum += x;
        return sum;
    }

    Auxiliary space = O(1)

The array itself is O(N), but it is INPUT - the algorithm did not allocate it.

--------------------------------------------------------------------------------
Example 4 - O(N) auxiliary space:

    vector<int> doubleAll(vector<int>& arr) {
        vector<int> result;
        for (int x : arr) result.push_back(x * 2);   // NEW array of size N
        return result;
    }

    Auxiliary space = O(N)

--------------------------------------------------------------------------------
THERE IS NO O(0)

Even if an algorithm allocates literally nothing extra, the space complexity is
still written O(1), never O(0).

O(1) does not mean "exactly one unit". It means "does not grow with n" - the
usage stays FLAT, whether that flat constant is 0, 1, or 500. The smallest
complexity class that exists is O(1). This applies to time complexity too.

--------------------------------------------------------------------------------
ON MODIFYING THE INPUT

    input : a, b
    code  : b = a + b;      // reusing input to save space

This is NOT automatically wrong. In-place algorithms are a legitimate and often
REQUIRED technique:

    - reverse(v.begin(), v.end())     modifies in place
    - sort(v.begin(), v.end())        modifies in place
    - two-pointer techniques          modify in place
    - many problems explicitly demand O(1) auxiliary space, which FORCES you
      to modify the input

The real rules are:
    1. Do not destroy input you still need later in the program.
    2. Do not modify a caller's data when the caller does not expect it
       (pass by const reference, or take a copy, if you must preserve it).
    3. If the problem asks for in-place, modifying the input is the goal.


================================================================================
PART 12 : SPACE COMPLEXITY OF RECURSION
================================================================================

A commonly missed cost: every pending recursive call occupies a frame on the
CALL STACK, and that counts as space.

    int factorial(int n) {
        if (n == 0) return 1;
        return n * factorial(n - 1);
    }

This allocates no arrays and no data structures - yet:

    factorial(n) calls factorial(n-1) calls ... calls factorial(0)

At the deepest moment, n+1 frames are simultaneously alive on the stack.

    Space complexity = O(n)          <-- NOT O(1)

RULE: recursion space = MAXIMUM DEPTH of the recursion, not total call count.

    fib(n)  : makes O(2^n) calls, but max depth is only n  ->  O(n) space
    merge sort : recursion depth log n, plus O(n) merge buffer -> O(n) space
    binary search (recursive) : depth log n -> O(log n) space
    binary search (iterative) : no recursion -> O(1) space

This is also why very deep recursion causes STACK OVERFLOW - the stack is a
limited region of memory (typically a few MB).


================================================================================
PART 13 : CONSTRAINTS -> REQUIRED COMPLEXITY (CP CHEAT SHEET)
================================================================================

Competitive programming runs on a judge server, not your machine. A rough,
widely used rule of thumb:

    ~10^8 simple operations per second

(Modern judges often handle a bit more, closer to 10^8 - 10^9 for very simple
operations, but 10^8 is the safe planning figure.)

    Time limit 1 sec  -> aim for <= 10^8 total operations
    Time limit 2 sec  -> aim for <= 2 * 10^8 total operations

--------------------------------------------------------------------------------
READ THE CONSTRAINTS FIRST. They tell you the intended complexity:

    n <= 10          ->  O(n!) or O(2^n * n)   (permutations / brute force)
    n <= 20-25       ->  O(2^n)                (subsets, bitmask DP)
    n <= 100         ->  O(n^4) / O(n^3)       (Floyd-Warshall, heavy DP)
    n <= 500         ->  O(n^3)
    n <= 2,000       ->  O(n^2)                (2D DP, all pairs)
    n <= 10^5        ->  O(n log n)            (sorting, set/map, binary search)
    n <= 10^6        ->  O(n) or O(n log n)
    n <= 10^8        ->  O(n) with a very small constant
    n > 10^8         ->  O(log n) or O(1)      (math/formula solution)

This mapping is the single most practically useful thing to memorise. If n is
10^5 and you have written an O(n^2) solution, that is 10^10 operations - you do
not need to submit it to know it will time out.


================================================================================
PART 14 : STL CONTAINER COMPLEXITY REFERENCE
================================================================================

    CONTAINER          ACCESS      SEARCH        INSERT        ERASE
    -------------------------------------------------------------------------
    vector             O(1)        O(n)          O(1) amort*   O(n)
    deque              O(1)        O(n)          O(1) at ends  O(n) middle
    list               O(n)        O(n)          O(1)**        O(1)**
    forward_list       O(n)        O(n)          O(1)**        O(1)**
    set / map          -           O(log n)      O(log n)      O(log n)
    multiset/multimap  -           O(log n)      O(log n)      O(log n)
    unordered_set/map  -           O(1) avg      O(1) avg      O(1) avg
                                   O(n) worst    O(n) worst    O(n) worst
    priority_queue     O(1) top    -             O(log n)      O(log n) pop
    stack / queue      O(1) top    -             O(1)          O(1)

      *  push_back is amortized O(1); insert in the middle is O(n)
      ** given you already hold an iterator to the position

--------------------------------------------------------------------------------
WHY THESE NUMBERS:

    vector O(1) access      : contiguous memory, direct index arithmetic
    vector O(n) erase       : all following elements must shift down
    list O(n) access        : must walk node by node from the start
    list O(1) insert/erase  : just relink a few pointers, nothing shifts

    map/set O(log n)        : internally a Red-Black tree (BALANCED BST).
                              Balance guarantees height stays ~log n, so every
                              operation walks one root-to-leaf path. This is
                              a HARD GUARANTEE regardless of insertion order.

    unordered O(1) average  : hash function jumps straight to a bucket. With a
                              good hash, each bucket holds ~1 element.
    unordered O(n) worst    : if all keys collide into ONE bucket, that bucket
                              degenerates into a linked list of n elements, and
                              you must scan all of it. NOT a guarantee, only an
                              expectation.

    priority_queue O(log n) : a BINARY HEAP stored in a vector. push bubbles the
                              new element UP one path; pop moves the last element
                              to the root and bubbles it DOWN one path. Both are
                              bounded by the tree height = log n.
    priority_queue O(1) top : the max/min is always at index 0 - just read it.
                              Reading is free; MAINTAINING order after a change
                              is what costs log n.

--------------------------------------------------------------------------------
COMMON ALGORITHM COMPLEXITIES:

    sort(v.begin(), v.end())          O(n log n)
    stable_sort(...)                  O(n log n)
    list.sort()                       O(n log n)   (merge sort, member function)
    binary_search / lower_bound
        on a random-access range      O(log n)
        on a set/map (member fn)      O(log n)
        on a list (via std::)         O(n)   <-- no random access, walks linearly
    reverse(...)                      O(n)
    next_permutation(...)             O(n) per call
    max_element / min_element         O(n)
    accumulate(...)                   O(n)
    __builtin_popcount(x)             O(1)   (single CPU instruction)


================================================================================
PART 15 : COMMON MISTAKES CHECKLIST
================================================================================

    [X] Writing O(15), O(3), O(2N)         -> constants are ALWAYS dropped
    [X] Writing O(0)                       -> does not exist; smallest is O(1)
    [X] Average = (best + worst) / 2       -> it is a probability-weighted mean
    [X] "Big O means worst case"           -> O is an upper BOUND on a function
    [X] Collapsing O(N+M) into O(N)        -> only valid if M is bounded by N
    [X] Forgetting recursion stack space   -> depth of recursion counts as space
    [X] Assuming O(N^2/2) beats O(N^2)     -> same complexity class
    [X] Quoting unordered_map as guaranteed O(1) -> it is O(1) AVERAGE, O(n) worst
    [X] Ignoring the constraints           -> they tell you the intended solution
    [X] "Never modify the input"           -> in-place is often required; the
                                              real rule is do not destroy data
                                              you still need

================================================================================
*/

int main() {
    // Notes file - no executable content.
    return 0;
}