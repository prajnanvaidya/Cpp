#include<bits/stdc++.h>
using namespace std;

/*
================================================================================
                            RECURSION - COMPLETE NOTES
================================================================================
RECURSION = when a function calls itself until a stopping condition is met.

TABLE OF CONTENTS
-----------------
  PART 1  : What recursion is, the call stack, stack overflow
  PART 2  : Base condition - the thing that stops it
  PART 3  : Tracing recursion (stack trace vs recursion tree)
  PART 4  : Basic problems - printing n times, 1..n, n..1
  PART 5  : Backtracking (doing work on the way BACK up)
  PART 6  : Parameterised vs Functional recursion
  PART 7  : Tail vs Non-tail recursion (and the truth about TCO in C++)
  PART 8  : What `return` actually does + the return-in-recursion rules
  PART 9  : Classic problems - factorial, fibonacci, power, sum of digits
  PART 10 : Array problems - reversal (1 pointer, 2 pointer)
  PART 11 : String problems - palindrome check
  PART 12 : Multiple recursive calls & exponential blowup
  PART 13 : Memoization - fixing the exponential blowup
  PART 14 : PASSING PARAMETERS CORRECTLY (critical for performance)
  PART 15 : Recursion vs Iteration - when to use which
  PART 16 : Common mistakes checklist

================================================================================
PART 1 : WHAT RECURSION IS, THE CALL STACK, STACK OVERFLOW
================================================================================

Every time a function is called, a STACK FRAME is pushed onto the CALL STACK,
holding that call's local variables, parameters, and the address to return to.
The frame is popped off only when that call finishes.

With recursion, a function calls itself BEFORE finishing - so the original call
is still incomplete and its frame stays on the stack while the new call runs.
Frames therefore pile up.

The stack is a LIMITED region of memory (typically a few MB). If frames pile up
faster than they pop - or never pop at all - you exhaust it and the program
crashes with STACK OVERFLOW (usually seen as a segmentation fault).
*/

// Infinite recursion - no stopping condition, guaranteed stack overflow
void f(){
    cout<<1<<endl;
    f();                      // never returns -> frames pile up forever -> CRASH
}


/*
================================================================================
PART 2 : BASE CONDITION - THE THING THAT STOPS IT
================================================================================
The BASE CONDITION (or base case) is the check that stops further recursive
calls. Without it, recursion is infinite.

Every recursive function needs TWO things:
    1. A BASE CASE   - when to stop
    2. A RECURSIVE CASE - how to move CLOSER to the base case each call

If the recursive case doesn't move toward the base case, the base case is never
reached and you still get infinite recursion even though a base case exists.
*/

void g(int n){
    cout<<n<<endl;
    n++;
    if(n==20)
        return;               // base condition
    g(n);                      // recursive case - n grows, moving toward 20
}


/*
================================================================================
PART 3 : TRACING RECURSION (STACK TRACE vs RECURSION TREE)
================================================================================

METHOD 1 - Track the stack manually (accurate but tedious).
Using g(n) above, starting at n=0:

    Initially:  Stack empty
    n=0 -> prints 0, n becomes 1, calls g(1).  Stack: [g(n=0)]
    n=1 -> prints 1, n becomes 2, calls g(2).  Stack: [g(n=0), g(n=1)]
    n=2 -> prints 2, n becomes 3, calls g(3).  Stack: [g(n=0), g(n=1), g(n=2)]
    n=3 -> prints 3, n becomes 4, calls g(4).  ... and so on

    Once the base case returns, frames pop in LIFO order (Last In First Out) -
    the most recent pending call resumes first, and each frame resumes at the
    line right after its own recursive call.

METHOD 2 - Recursion tree (faster, standard in practice).
Same function drawn as a tree - each level is one deeper call:

    g(0)
     └── g(1)
          └── g(2)
               └── g(3)
                    └── g(4) -> returns
                    ^
               g(3) resumes
          ^
     g(2) resumes
    ^
    g(1) resumes

Reading a recursion tree:
    - Going DOWN   = making calls (work done BEFORE the recursive call)
    - Going UP     = returning    (work done AFTER the recursive call)

That down/up distinction is the entire idea behind backtracking (Part 5).
*/


/*
================================================================================
PART 4 : BASIC PROBLEMS
================================================================================
*/

// ---- 4.1 Print a name n times ----
void printFruit(int cnt, int n){
    if(cnt>n){
        return;                          // base case
    }
    cout<<"Name: Orange"<<endl;          // work done on the way DOWN
    printFruit(cnt+1, n);                 // recursive case
}
// Recursion tree for n=3, starting cnt=1:
//    printFruit(1,3) -> printFruit(2,3) -> printFruit(3,3) -> printFruit(4,3) -> return
// TC - O(n)   (n calls, O(1) work each)
// SC - O(n)   (n frames alive on the stack at the deepest point)
//
// NOTE: the original used printFruit(++cnt, n). That works (cnt is a local
// copy, so modifying it is harmless), but cnt+1 is clearer - it expresses
// "call with one more" without also mutating the current frame's variable.


// ---- 4.2 Print linearly from 1 to n ----
void linearN(int cont,int n){
    cout<<cont<<endl;
    cont++;
    if(cont>n){
        return;
    }
    linearN(cont, n);
}
// TC - O(n), SC - O(n)


// ---- 4.3 Print backward from n to 1 ----
void backLinear(int cnt){
    cout<<cnt<<endl;
    cnt--;
    if(cnt<1){
        return;
    }
    backLinear(cnt);
}
// TC - O(n), SC - O(n)


/*
================================================================================
PART 5 : BACKTRACKING - DOING WORK ON THE WAY BACK UP
================================================================================
BACKTRACKING here means: make the recursive call FIRST, and do your actual work
AFTER it returns - i.e. while the stack is unwinding.

This flips the order of output for free, without changing what you pass down.
The key insight: statements placed BEFORE the recursive call execute on the way
DOWN; statements placed AFTER it execute on the way UP (in reverse order).
*/

// ---- 5.1 Print 1 to n WITHOUT passing an incrementing counter ----
void backtrackLinear(int cnt){
    if(cnt<1){
        return;
    }
    backtrackLinear(cnt-1);        // go all the way down FIRST
    cout<<cnt<<endl;                // then print on the way back UP
}
// Recursion tree for n=3:
//     backtrackLinear(3)      then prints 3   (last)
//        |                        ^
//     backtrackLinear(2)      then prints 2
//        |                        ^
//     backtrackLinear(1)      then prints 1   (first)
//        |                        ^
//     backtrackLinear(0)  -> returns
//
// Output: 1 2 3   (ascending, even though we counted DOWN)
// TC - O(n), SC - O(n)


// ---- 5.2 Print n to 1 using backtracking ----
void BacktrackNonLinear(int cnt, int n){
    if(cnt>n){
        return;
    }
    BacktrackNonLinear(cnt+1, n);   // go all the way down first
    cout<<cnt<<endl;                 // print on the way back up
}
// Counting UP but printing on the way back gives DESCENDING output.
// TC - O(n), SC - O(n)


/*
================================================================================
PART 6 : PARAMETERISED vs FUNCTIONAL RECURSION
================================================================================
Two distinct styles of writing the same logic:

PARAMETERISED RECURSION
    The intermediate result is carried DOWN as an extra parameter (often called
    an "accumulator"). The base case simply reports/returns the finished value.
    Nothing needs to be computed on the way back up.

FUNCTIONAL RECURSION
    The recursive call RETURNS a value, and the current frame does computation
    on that returned value before returning its own result up the chain.
    Work happens on the way back UP.

Neither is "better" universally - but parameterised style is what makes tail
recursion possible (Part 7), and functional style is often more natural to read
for mathematical definitions.
*/

// ---- Parameterised: sum of first n numbers ----
void SumToNModified(int i, int sum){
    if(i<1){
        cout<<sum<<endl;              // base case reports the finished answer
        return;
    }
    SumToNModified(i-1, sum+i);       // accumulate on the way DOWN
}
// Trace for i=4, sum=0:
//    f(4, 0) -> f(3, 4) -> f(2, 7) -> f(1, 9) -> f(0, 10) -> prints 10
// TC - O(n), SC - O(n) frames (see Part 7 re: whether TCO can reduce this)


// ---- Functional: sum of first n numbers ----
int SumToNFunc(int n){
    if(n<=0){                          // FIX: original used n==1, which infinite-
        return 0;                       // loops for n=0 or negative input. n<=0
    }                                    // returning 0 is safe and still correct
    return n+SumToNFunc(n-1);           // compute on the way back UP
}
// TC - O(n), SC - O(n)


/*
================================================================================
PART 7 : TAIL vs NON-TAIL RECURSION (AND THE TRUTH ABOUT TCO IN C++)
================================================================================
A function is TAIL RECURSIVE if the recursive call is the VERY LAST operation -
nothing at all happens after it returns.

WHY IT MATTERS: if nothing remains to be done after the call, the current frame
is useless once the call is made. A compiler can therefore REUSE the current
frame instead of pushing a new one - turning the recursion into a loop
internally. This is TAIL CALL OPTIMIZATION (TCO), and it drops space from
O(n) to O(1).
*/

// ---- Non-tail recursion that LOOKS tail recursive ----
int NonTailFactorial(int n){
    if(n<1){
        return 1;
    }
    return n * NonTailFactorial(n-1);
}
// NOT tail recursive: the last operation is the MULTIPLICATION (n * ...), not
// the call itself. The frame must survive to receive the returned value and
// multiply it by its own n - so the stack cannot be collapsed.
// TC - O(n), SC - O(n)


// ---- Genuinely tail recursive: factorial with an accumulator ----
void TailFactorial(int i, long long acc){
    if(i<1){
        cout<<acc<<endl;
        return;
    }
    TailFactorial(i-1, acc*i);         // truly the last operation
}
// TC - O(n)
// SC - O(n) frames normally, O(1) IF the compiler applies TCO - see below.
// NOTE: acc changed from int to long long, since factorials overflow a 32-bit
// int very fast (13! already exceeds INT_MAX).

/*
--------------------------------------------------------------------------------
IMPORTANT CORRECTION ABOUT TCO IN C++
--------------------------------------------------------------------------------
It is commonly claimed that tail recursion "gives O(1) space in C++."
That is CONDITIONAL, not guaranteed. The C++ standard does NOT require tail
call optimization. Whether it happens depends on your compiler AND your
optimization flags.

VERIFIED BY ACTUAL TESTING with the TailFactorial function above, called at
depth 5,000,000 on the same machine with the same compiler:

    g++ -O0 (the DEFAULT if you just run `g++ file.cpp`)  ->  SEGMENTATION FAULT
    g++ -O2                                                 ->  ran fine, no crash

So the correct statement is:
    - Tail recursion MAKES the O(1) optimization POSSIBLE.
    - Whether you actually GET it depends on compiling with optimization on.
    - Without -O2 (or similar), a tail-recursive function still uses O(n) stack
      and will still overflow on deep recursion.

Practical takeaway: write tail-recursive form when it's natural, but never
RELY on TCO for correctness. If you need guaranteed O(1) space, write a loop.
*/


/*
================================================================================
PART 8 : WHAT `return` ACTUALLY DOES + RETURN-IN-RECURSION RULES
================================================================================

WHAT A RETURN STATEMENT DOES (two separate jobs at once):
    1. It IMMEDIATELY EXITS the current function. Any code below it in that
       function never runs - execution jumps back to whoever called it.
    2. It optionally HANDS A VALUE back to the caller (if the return type isn't
       void).

Job (1) applies always. Job (2) only when there's a value.

--------------------------------------------------------------------------------
CALLING A FUNCTION WITH vs WITHOUT `return` IN FRONT OF IT
--------------------------------------------------------------------------------

    void a() { helper(); }            // just CALLS helper, then continues
    int  b() { return helper(); }     // calls helper AND passes its result up,
                                       // AND exits b() immediately

Concretely, inside a recursive function:

    recurse(n-1);              // "go do that, then COME BACK and continue here"
    return recurse(n-1);       // "go do that, and whatever it gives, that's my
                                //  answer - I'm done, don't come back to me"

The second form discards the current frame's remaining work entirely.

--------------------------------------------------------------------------------
RULE A (NON-TAIL / FUNCTIONAL RECURSION):
Do NOT put `return` directly in front of the recursive call if you have lines
below it that must execute on the way back up. Doing so exits the function
instantly and makes everything below it DEAD CODE that never runs.

    // BROKEN - the cout never executes
    int bad(int n){
        if(n==0) return 0;
        return bad(n-1);       // exits here!
        cout<<n<<endl;          // DEAD CODE - unreachable
    }

--------------------------------------------------------------------------------
RULE B (VALUE PASSING):
ALWAYS use `return` when your function is declared to hand a value back
(int, string, bool, etc.) - regardless of whether it's tail or non-tail. A
non-void function that reaches its end without returning is undefined behavior.

--------------------------------------------------------------------------------
"CAN A FUNCTION DO WORK AFTER A RECURSIVE CALL AND STILL RETURN A VALUE?"
YES - this is a very common point of confusion. You can absolutely do both.
The trick: CAPTURE the recursive result in a temporary variable first, do your
remaining work, then return at the very end.
*/

int sumAndPrint(int n) {
    if (n == 0) return 0;                  // base case

    // 1. Pause and recurse - STORE the result instead of returning it directly
    int subTotal = sumAndPrint(n - 1);

    // 2. This runs AFTER the recursive call returns (on the way back UP)
    cout << "Resuming frame n = " << n << ", subTotal = " << subTotal << endl;

    // 3. Now hand the finished value up to the parent frame
    return n + subTotal; 
}
/*
Trace for sumAndPrint(3):

    main calls s(3)
      s(3): subTotal = s(2) ... pauses here
        s(2): subTotal = s(1) ... pauses here
          s(1): subTotal = s(0) ... pauses here
            s(0): returns 0 immediately (base case)
          s(1) resumes: subTotal=0, prints "n=1, subTotal=0", returns 1+0 = 1
        s(2) resumes: subTotal=1, prints "n=2, subTotal=1", returns 2+1 = 3
      s(3) resumes: subTotal=3, prints "n=3, subTotal=3", returns 3+3 = 6

Output:
    Resuming frame n = 1, subTotal = 0
    Resuming frame n = 2, subTotal = 1
    Resuming frame n = 3, subTotal = 3
    Final answer: 6

Notice the prints come out in ASCENDING order even though the calls were made
in DESCENDING order - that's the stack unwinding (Part 5's backtracking idea).
TC - O(n), SC - O(n)
*/


/*
================================================================================
PART 9 : CLASSIC PROBLEMS
================================================================================
*/

// ---- 9.1 Fibonacci (functional / non-tail) ----
// Sequence: 0, 1, 1, 2, 3, 5, 8, 13, ...  with fib(0)=0, fib(1)=1
int fibonacci(int n){
    if(n<=1){
        return n;                    // FIX: original returned 1 for BOTH n==0
    }                                 // and n==1, producing 1,1,2,3,5,... which
                                       // contradicts the 0,1,1,2,3,5 sequence its
                                       // own comment claimed. n<=1 -> return n
                                       // gives the standard definition correctly.
    return fibonacci(n-1)+fibonacci(n-2);
}
// TC - O(2^n)  - see Part 12 for why
// SC - O(n)    - CORRECTION: the original notes said SC was O(2^n). That is
//                WRONG. O(2^n) is the number of CALLS MADE overall, but calls
//                do not all live at once - recursion is depth-first, so a
//                branch's frames are freed before the next branch runs. Space
//                = MAXIMUM DEPTH of the stack = O(n), not total call count.


// ---- 9.2 Fibonacci (parameterised / tail recursive) ----
int fib_tail(int n, int acc1=0, int acc2=1){
    if(n==0){
        return acc1;
    }
    return fib_tail(n-1, acc2, acc1+acc2);
}
// FIX: the original was fib_tail(int n, int acc1=1, int acc2=1) with base case
// n==1. VERIFIED BY TESTING, that version did NOT match its own non-tail
// fibonacci() - it was off by one index (fib_tail(n) equalled fibonacci(n-1)).
// With acc1=0, acc2=1 and base n==0, both functions now produce identical
// output: 0 1 1 2 3 5 8 13 21 for n=0..8.
//
// TC - O(n)   <-- dramatically better than the O(2^n) non-tail version, because
//                 each value is computed exactly once instead of being
//                 recomputed across overlapping branches
// SC - O(n) frames, O(1) if TCO applies (see Part 7 caveat)


// ---- 9.3 Power of a number (functional / non-tail) ----
int PowerDig(int x, int n){
    if(n==0){
        return 1;
    }
    return x*PowerDig(x, n-1);
}
// TC - O(n), SC - O(n)


// ---- 9.4 Power of a number (parameterised / tail recursive) ----
int power_tail(int x, int n, int acc=1){
    if(n==0){
        return acc;
    }
    return power_tail(x, n-1, acc*x);
}
// FIX: the original "tail" power was:
//        int powern_tail(int n, int m){
//            if (m==0) return n;
//            return powern_tail(n*n, m-1);
//        }
// VERIFIED BY TESTING, that computes n^(2^m), NOT n^m:
//        powern_tail(2,3) returned 256   (correct answer is 2^3 = 8)
//        powern_tail(2,2) returned 16    (correct answer is 2^2 = 4)
//        powern_tail(3,2) returned 81    (correct answer is 3^2 = 9)
// The repeated SQUARING (n*n) is the bug - a correct tail-recursive power needs
// a separate accumulator that multiplies by x once per step, leaving x itself
// unchanged. The version above is verified to match PowerDig exactly.
//
// TC - O(n), SC - O(n) frames / O(1) with TCO


// ---- 9.5 Sum of digits (parameterised) ----
int SumDig(int n, int sum){
    if(n/10==0){
        return sum+n;                 // last digit reached
    }
    return SumDig((n/10), sum+(n%10));
}
// TC - O(log10(n))  (one call per digit, and digit count ~ log10(n))
// SC - O(log10(n))


/*
================================================================================
PART 10 : ARRAY PROBLEMS - REVERSAL
================================================================================
*/

// ---- 10.1 Iterative baseline (for comparison) ----
void reverseArrayIterative(int arr[], int n){
    // NOTE: you CANNOT compute an array's size inside a function using
    // sizeof(arr)/sizeof(arr[0]). When an array is passed to a function it
    // DECAYS TO A POINTER, and sizeof on a pointer gives the pointer's own
    // size (8 bytes on 64-bit), not the array's. Always pass the size
    // explicitly as a parameter - or use vector, which knows its own size.
    int temp;
    for(int i=0;i<n/2;i++){
        temp=arr[i];
        arr[i]=arr[n-1-i];
        arr[n-1-i]=temp;
    }
}
// TC - O(n), SC - O(1)


// ---- 10.2 Recursive, single pointer ----
void reverseSinglePointer(int arr[], int point, int n){
    if(point>=n/2){                    // base case: reached the middle
        return;
    }
    swap(arr[point], arr[n-1-point]);   // std::swap - cleaner than a temp var
    reverseSinglePointer(arr, point+1, n);
}
// TC - O(n), SC - O(n)
//
// FIX vs the original `reverserecNoob`, which had base case `if(i > int(n/2))`.
// VERIFIED BY TESTING, that off-by-one BREAKS EVEN-LENGTH arrays:
//     {1,2,3,4}   gave  4 2 3 1   (expected 4 3 2 1)   <-- WRONG
//     {1,2,3,4,5} gave  5 4 3 2 1 (expected 5 4 3 2 1) <-- happened to work
// Why: for n=4, `i > 2` lets i reach 2, which swaps arr[2] with arr[4-1-2]=arr[1]
// - re-swapping a pair that was ALREADY swapped at i=1, undoing it. Odd lengths
// escaped this because the extra iteration swapped the middle element with
// itself (a harmless no-op). The correct condition is `>=`, not `>`.


// ---- 10.3 Recursive, two pointers (the standard idiom) ----
void reverseTwoPointers(int arr[], int left, int right){
    if(left>=right){                   // base case: pointers met or crossed
        return;
    }
    swap(arr[left], arr[right]);
    reverseTwoPointers(arr, left+1, right-1);
}
// TC - O(n), SC - O(n)
// Start it with left=0, right=n-1. This generalises better than the single
// pointer version (works unchanged on sub-ranges), and reads more clearly.


/*
================================================================================
PART 11 : STRING PROBLEMS - PALINDROME CHECK
================================================================================
*/

bool PalRec(const string& str, int point, int n){
    if(point>=n/2){
        return true;                    // reached the middle, all matched
    }
    if(str[point]!=str[n-1-point]){
        return false;                    // mismatch found, stop immediately
    }
    return PalRec(str, point+1, n);
}
// TC - O(n), SC - O(n)
//
// TWO FIXES vs the original:
//
// 1. PARAMETER TYPE: the original took `string str` BY VALUE. That copies the
//    ENTIRE string on every single recursive call - n calls x O(n) copy each =
//    O(n^2) time and O(n^2) space. Changed to `const string&`, which passes
//    only a lightweight reference: no copying at all. (This is exactly the
//    mistake Part 14 warns about - the original file documented the rule at
//    the bottom but the code above it violated it.)
//
// 2. COMPLEXITY NOTATION: the original said "TC, SC: O(n/2)". There is no such
//    thing as O(n/2) - constants are always dropped in Big-O. It is O(n).


/*
================================================================================
PART 12 : MULTIPLE RECURSIVE CALLS & EXPONENTIAL BLOWUP
================================================================================
When ONE call spawns TWO (or more) further calls, the number of calls grows
exponentially instead of linearly.

Recursion tree for fibonacci(4) using the standard fib(0)=0, fib(1)=1:

    f(4)
    |-- f(3)
    |   |-- f(2)
    |   |   |-- f(1) = 1
    |   |   +-- f(0) = 0
    |   |   -> f(2) = 1
    |   +-- f(1) = 1
    |   -> f(3) = 2
    +-- f(2)                <-- NOTE: f(2) is computed AGAIN from scratch here
        |-- f(1) = 1
        +-- f(0) = 0
        -> f(2) = 1
    -> f(4) = 3

TIME COMPLEXITY: O(2^n)
    Each call branches into at most 2 children, and the deepest path has length
    at most n, so the tree has at most ~2^n nodes.
    The EXACT count is smaller - it grows like phi^n (phi = golden ratio ~1.618),
    e.g. fibonacci(4) makes 9 calls, not 16. O(2^n) is a simple, safe UPPER
    BOUND rather than the exact count, and it correctly captures the key fact:
    this is EXPONENTIAL and therefore catastrophic.

SPACE COMPLEXITY: O(n)   -- NOT O(2^n)
    Frames do not all live simultaneously. Recursion is depth-first: it dives
    down one branch completely, and those frames POP and free their memory
    before the next branch starts. At the single deepest moment only ~n frames
    are alive. Total CALLS = O(2^n); maximum simultaneous DEPTH = O(n).

THE ROOT PROBLEM: overlapping subproblems. f(2) above is computed twice, f(1)
three times. As n grows this redundancy explodes. Part 13 fixes it.
*/


/*
================================================================================
PART 13 : MEMOIZATION - FIXING THE EXPONENTIAL BLOWUP
================================================================================
MEMOIZATION = cache the result of each distinct subproblem the first time it is
computed, then reuse the cached answer instead of recomputing.

IMPORTANT: C++ does NOT do this automatically. Plain recursion has zero memory
of past calls - every call runs the full function body from scratch. You must
write the caching yourself.

(Do not confuse this with CPU/hardware caching, which speeds up MEMORY ACCESS
and is automatic and invisible. Memoization avoids REPEATED COMPUTATION and is
something you code explicitly. Unrelated concepts, same English word.)
*/

vector<int> memo;                        // shared across all recursive calls

int fibMemo(int n){
    if(n<=1) return n;
    if(memo[n]!=-1) return memo[n];      // already computed -> O(1) lookup
    return memo[n] = fibMemo(n-1)+fibMemo(n-2);   // compute once, then store
}
// Call setup:  memo.assign(n+1, -1);  then  fibMemo(n);
//
// TC - O(n)   - there are only n+1 distinct subproblems (fib(0)..fib(n)), each
//               solved exactly once with O(1) work. Every repeat request is a
//               cache hit that does NOT branch further.
// SC - O(n)   - O(n) for the memo array + O(n) recursion depth

/*
--------------------------------------------------------------------------------
WHY THE CACHE MUST LIVE OUTSIDE THE FUNCTION
--------------------------------------------------------------------------------
If memo were declared as a plain LOCAL variable inside fibMemo, it would be
created fresh and destroyed on EVERY call - so every recursive call would get
its own empty cache and see nothing that any other call computed. That defeats
the entire purpose (and adds allocation overhead on top).

Three valid ways to give all calls ONE shared cache:

    A. Global / outer scope       (what's used above - simplest for CP)
    B. static local variable      static vector<int> memo(1000, -1);
                                   `static` = initialized ONCE on first use and
                                   persists across calls, instead of being
                                   recreated each time
    C. Pass by reference          int fibMemo(int n, vector<int>& memo)

All three work. What never works is a plain non-static local vector.
*/


/*
================================================================================
PART 14 : PASSING PARAMETERS CORRECTLY (CRITICAL FOR PERFORMANCE)
================================================================================
THE PROBLEM:
If you pass a container (vector, string, list, or a custom struct/class) BY
VALUE, a full DEEP COPY of every element is made for EVERY SINGLE recursive
call. With N elements and N levels of recursion, that's O(N^2) copying work and
O(N^2) memory - which will destroy performance and can exhaust memory outright.

THE THREE PARAMETER RULES:

--------------------------------------------------------------------------------
RULE 1 - READ-ONLY OBJECTS -> pass as  const Type&
--------------------------------------------------------------------------------
If the function only READS the data (checking elements, printing), pass a const
reference. The compiler passes a lightweight address instead of copying, and
const protects you from accidental modification.

    void readOnly(const vector<int>& arr) {      // zero copying overhead
        // arr[0] = 5;   // COMPILER ERROR - protected against accidental writes
    }

--------------------------------------------------------------------------------
RULE 2 - READ-AND-MODIFY OBJECTS -> pass as  Type&
--------------------------------------------------------------------------------
If the recursion should actively modify the ORIGINAL data (sorting in place,
backtracking a path, marking visited cells), pass a non-const reference.

    void modifyOriginal(vector<int>& arr) {      // changes the caller's vector
        arr.push_back(100); 
    }

--------------------------------------------------------------------------------
RULE 3 - PRIMITIVES -> pass BY VALUE  (int, char, bool, double)
--------------------------------------------------------------------------------
For small built-in types, copying is FASTER than referencing. They're 1-8 bytes,
so copying is a single cheap register operation, whereas a reference forces an
extra pointer dereference on every access.

    void process(const vector<int>& arr, int index) {   // ref for the container,
        if (index < 0) return;                            // value for the int
    }

--------------------------------------------------------------------------------
SUMMARY TABLE
--------------------------------------------------------------------------------
    DATA TYPE                    DEEP COPY PENALTY?      BEST PRACTICE
    ---------------------------------------------------------------------------
    int, char, bool, double      No                      pass by value (int x)
    vector, string, list, map    YES (severe)            const vector<int>&
    custom structs / classes     YES                     const MyClass&
    (needs modifying)            -                       vector<int>&  (no const)

This is not a micro-optimization - it's the difference between O(n) and O(n^2).
See Part 11 for a real example of this exact mistake and its cost.
*/


/*
================================================================================
PART 15 : RECURSION vs ITERATION - WHEN TO USE WHICH
================================================================================

ANYTHING recursive can be written iteratively and vice versa. The choice is
about clarity and cost, not capability.

USE RECURSION WHEN:
    - The problem is naturally self-similar (trees, graphs, divide & conquer)
    - The recursive form is dramatically clearer (tree traversal, backtracking,
      merge sort, DFS, generating permutations/subsets)
    - Depth is bounded and safely small

USE ITERATION WHEN:
    - The recursion would be deep enough to risk stack overflow
    - A simple loop expresses it just as clearly (summing 1..n, factorial,
      linear scans)
    - You need guaranteed O(1) space (remember: TCO is not guaranteed - Part 7)

THE COSTS OF RECURSION:
    - O(depth) stack space, always (unless TCO actually applies)
    - Function-call overhead per step (pushing/popping frames) - small but real
    - Risk of stack overflow on deep input

THE COST OF ITERATION:
    - Some algorithms become significantly harder to read and write (try writing
      a tree traversal iteratively - you end up manually simulating the exact
      call stack recursion gave you for free)

RULE OF THUMB: if you find yourself manually maintaining an explicit stack to
avoid recursion, the recursive version was probably the right call.
*/


/*
================================================================================
PART 16 : COMMON MISTAKES CHECKLIST
================================================================================
    [X] No base case                    -> infinite recursion, stack overflow
    [X] Base case exists but is never   -> recursive case must MOVE TOWARD the
        reachable                          base case every call
    [X] Off-by-one in the base case     -> e.g. `i > n/2` vs `i >= n/2` in array
                                            reversal silently breaks EVEN-length
                                            arrays only (see Part 10.2)
    [X] `return` before code that must  -> everything after it becomes dead code
        run on the way back up             (Part 8, Rule A)
    [X] Non-void function with a path   -> undefined behavior (Part 8, Rule B)
        that returns nothing
    [X] Passing containers by value     -> silent O(n^2) blowup (Part 14)
    [X] Writing SC as O(2^n) for        -> space is MAX DEPTH O(n), not total
        fibonacci                          call count (Part 12)
    [X] Writing O(n/2)                  -> constants are always dropped -> O(n)
    [X] Assuming tail recursion always  -> only with optimization enabled;
        gives O(1) space in C++            NOT guaranteed by the standard (Part 7)
    [X] Assuming results are cached     -> plain recursion has NO memory of past
        automatically                      calls; write memoization yourself
                                            (Part 13)
    [X] sizeof(arr)/sizeof(arr[0])      -> arrays decay to pointers when passed
        inside a function                  to a function; always pass size
                                            explicitly (Part 10.1)
================================================================================
*/


//Problems


//------------------------------------------------------------------------------------------------------

//1.Print all subsequences

// Subsequence - a contigous or non contigous elements of a arr which follows the order
// Here order is the elem on left of a elem should be at left and elem at right of a particulart arr should be at right

//Note: Subarr - contigous elem following the order
// Ex: 3 1 2
// 3      - subseq / subarr
// 1      - subseq / subarr
// 2      - subseq / subarr
// 3 1    - subseq / subarr
// 3 2    - subseq
// 1 3    - neither
// 1 2    - subseq / subarr
// 2 1    - neither
// 1 2 3  - neither
// 3 1 2  - subseq / subarr
// 3 2 1  - neither



void printSubarr(vector<int>& arr){ 
    int flag=0;
    for(int i=0;i<arr.size();i++){
        for(int j=arr.size()-1;j>=0;j--){
            for(int k=i;k<=j;k++){
                flag=1;
                cout<<arr[k]<<" ";
            }
            if(flag){
                cout<<endl;
                flag=0;
            }
        }
    }
}
//Tc - O(n^3), SC - O(1)


void printSubSeqOpt(int index, vector<int> temp, vector<int> arr){
    if(index>=arr.size()){
        for(auto v:temp)
            cout<<v<<" ";
        cout<<endl;
        return;
    }
    temp.push_back(arr[index]);
    printSubSeqOpt(index+1, temp, arr);
    
    temp.pop_back();
    printSubSeqOpt(index+1, temp, arr);
}
//TC - O(n.2^n)}{as 2^n no of subseq for n elems and each time printing it goes through temp elems to print taking roughly n steps(usually less then that)}, Sc - O(n){since depth of recursion tree is max n}

//------------------------------------------------------------------------------------------------------

//2.Print subsequence whose sum is k 

//Brute doing same thing just checking sum of elems of temp to be = to k in stop condition
void printSubSeqK(int index, vector<int> temp, vector<int> arr, int intermediate_sum, int k){
    if(index >= arr.size()){
        if(intermediate_sum == k){
            for(auto v:temp)
                cout<<v<<" ";
            cout<<endl;
        }
        return;
    }
    temp.push_back(arr[index]);
    intermediate_sum+=arr[index];
    printSubSeqK(index+1, temp, arr, intermediate_sum, k);

    temp.pop_back();
    intermediate_sum-=arr[index];
    printSubSeqK(index+1, temp, arr, intermediate_sum, k);
}
//TC - O(n.2^n), Sc - o(n)

//------------------------------------------------------------------------------------------------------
//3. Print only one or first subseq of a arr whose sum is k
//To make it wok we need a technique to return a function call when base case is met rather then simply keeping a boolean flag or function parameter which is set true when stop case satisfied and first subsec is printed and to based on that have another base case at top to return if flag is set.


//Using global flag or just another parameter
void printFSubSeqK(int index, vector<int>& temp, vector<int>& arr, int intermediate_sum, int k, bool& flag){
    
    if(flag)
        return;

    else if(index>=arr.size()){
        if(intermediate_sum==k){
            flag=true;
            for(auto v:temp)
                cout<<v<<" ";
        }
        cout<<endl;
        return;
    }

    temp.push_back(arr[index]);
    intermediate_sum+=arr[index];
    printFSubSeqK(index+1, temp, arr, intermediate_sum, k, flag);

    temp.pop_back();
    intermediate_sum-=arr[index];
    printFSubSeqK(index+1, temp, arr, intermediate_sum, k, flag);

}

//But this way is not recomended so u should use
//Technique to print 1 asnwer in recursion: without using global var or separate param flag

auto printFSubSeqKT(vector<int>& arr, int k, vector<int>& temp, int index=0, int inter_sum=0){
    if(index >= arr.size()){
        if(inter_sum==k){
            for(auto v:temp)
                cout<<v<<" ";
            cout<<endl;
            return true;
        }
        return false;
    }

    temp.push_back(arr[index]);
    inter_sum+=arr[index];
    if(printFSubSeqKT(arr, k, temp, index+1, inter_sum)){
        return true;
    }

    temp.pop_back();
    inter_sum-=arr[index];
    if(printFSubSeqKT(arr, k, temp, index+1, inter_sum)){
        return true;
    }
    return false;
}

//-----------------------------------------------------------------------------------------------------
//4. Print the no of subseq with sum k in an arr
int printSubSeqNoK(vector<int>& arr, int k, int& cnt, int index=0, int inter_sum=0){
    if(index >= arr.size()){
        if(inter_sum==k){
            cnt++;
        }
        return cnt;
    }

    inter_sum+=arr[index];
    printSubSeqNoK(arr, k, cnt, index+1, inter_sum);

    inter_sum-=arr[index];
    printSubSeqNoK(arr, k, cnt, index+1, inter_sum);

    return cnt;
}

//Without using a referenced or global parameter
int printSubSeqNoKOpt(vector<int>& arr, int k, int index=0, int inter_sum=0){
    if(inter_sum>k){  //just optimize TC further , only if arr contains positives
        return 0;
    }
    if(index >= arr.size()){
        if(inter_sum==k){
            return 1;
        }
    return 0;
    }

    inter_sum+=arr[index];
    int l=printSubSeqNoKOpt(arr, k, index+1, inter_sum);

    inter_sum-=arr[index];
    int r=printSubSeqNoKOpt(arr, k, index+1, inter_sum);

    return l+r;
}
//Tc - O(2^n), Sc - o(n)
//---------------------------------------------------------------------------------------------------
//5. Combination sum 1
/*
Given an array of distinct integers `candidates` and a target integer `target`,
return a list of all unique combinations of `candidates` where the chosen
numbers sum to `target`.

You may return the combinations in any order.

The same number may be chosen from `candidates` an unlimited number of times.

Two combinations are unique if the frequency of at least one of the chosen
numbers is different.

It is guaranteed that the number of unique combinations that sum up to
`target` is less than 150 for the given input.


Example 1:

Input:
    candidates = [2, 3, 6, 7]
    target = 7

Output:
    [[2, 2, 3], [7]]

Explanation:
    2 and 3 are candidates, and 2 + 2 + 3 = 7.
    Note that 2 can be used multiple times.

    7 is a candidate, and 7 = 7.

    These are the only two combinations.


Example 2:

Input:
    candidates = [2, 3, 5]
    target = 8

Output:
    [[2, 2, 2, 2], [2, 3, 3], [3, 5]]
*/

void printCombinationSum1(int index, int tar_rem, vector<int>& temp, int target, vector<int>& arr){
    //Only if arr is of positives
    if(target>0 && tar_rem<0){
        return;
    }
    if(index >= arr.size()){
        if(tar_rem == 0){
            for(auto v:temp)
                cout<<v<<" ";
            cout<<endl;
        }
        return;
    }

    temp.push_back(arr[index]);
    tar_rem-=arr[index];
    printCombinationSum1(index, tar_rem, temp, target, arr);

    temp.pop_back();
    tar_rem+=arr[index];
    printCombinationSum1(index+1, tar_rem, temp, target, arr);
}
//Tc - O(2^t) where t is target, SC - O(k . x), where k is average length of combinations and x is no of combinations
// Tc - O(2^t . k) if trying to put every found combinations into a data structure and send it as result, this ds to store all combination is passed as referenced parameter

//-----------------------------------------------------------------------------------------------------------------------------

//6. Combination Sum 2: Same as above but each elem supposedly used only once and not multile times
void printCombinationSum2(vector<int>& arr, vector<int>& temp, int index, int target, int rem_target){
    if(rem_target<0){
        return;
    }

    if(index >= arr.size()){
        if(rem_target == 0){
            for(auto v:temp)
                cout<<v<<" ";
            cout<<endl;
        }
        return;
    }
    temp.push_back(arr[index]);
    rem_target-=arr[index];

    printCombinationSum2(arr, temp, index+1, target, rem_target);

    temp.pop_back();
    rem_target+=arr[index];
    printCombinationSum2(arr, temp, index+1, target, rem_target); 
}
//Tc - O(2^n), SC - O(k.x)

//Give the result stored in a data structure
//We make 2 functions


void StoreAns(vector<int>& arr, vector<int>& temp, set<vector<int>>& ans, int index, int target){
    if(index >= arr.size()){
        if(target == 0){
            ans.insert(temp);
        }
        return;
    }
    if(arr[index] <= target){
        temp.push_back(arr[index]);
        target-=arr[index];
        StoreAns(arr, temp, ans, index+1, target);

        temp.pop_back();
        target+=arr[index];
    }
    StoreAns(arr, temp, ans, index+1, target);
}

auto printCombSum2DS(vector<int>& arr, int target){
    vector<int> temp;
    set<vector<int>> ans;
    StoreAns(arr, temp, ans, 0, target);
    return ans;
}
//Tc - O(2^n . k . logn), where k is average length combinations possible, (logn) due to set inserting of elements, n is no f elems in arr as each elem has 2 options either take or not take, SC - O(n + k.x), where x is no of combination arr possible, n for depth of stack frame 

//In above inorder to avoid duplicate combination we used set or unordered set it introduces extra complexity, We can avoid that by looping through every possible index to include and selecting which is different from previous and going deep into it, possible by sorting the arr and each index if the elem came out greater then target then break the loop as no further elem can be less then the current


void printCombSum2Opt(vector<int>& arr, vector<int>& temp, vector<vector<int>>& ans, int index, int target){
    if(target == 0){
        ans.push_back(temp);
        return;
    }
    for(int i=index;i<arr.size();i++){
        if(i>index && arr[i-1]==arr[i]) continue;

        if(arr[i]>target) break;
        temp.push_back(arr[i]);
        printCombSum2Opt(arr, temp, ans, i+1, target-arr[i]);
        temp.pop_back();
    }
}

auto SetCombSum2(vector<int>& arr, int target){
    sort(arr.begin(), arr.end());
    vector<int> temp;
    vector<vector<int>> ans;
    printCombSum2Opt(arr, temp, ans, 0, target);
    return ans;
}
//------------------------------------------------------------------------------------------------------------------------------

//7. Given a list(Arr) of N integers, print Ssums of all subsets in it. Output should be printed in increasing order of sums
//Ex: {3, 1, 2}
// {}     - 0
// {3}    - 3
// {1}    - 1
// {2}    - 2
// {3,1}  - 4
// {3,2}  - 5 
// {1,2}  - 3
// {3,1,2}- 6
// ans - {0, 1, 2, 3, 4, 5, 6}

void printSubSum(vector<int>& arr, vector<int>& temp, int index, set<int>& ans){
    if(index >= arr.size()){
        ans.insert(reduce(temp.begin(), temp.end()));
        return;
    }
    
    temp.push_back(arr[index]);
    printSubSum(arr, temp, index+1, ans);

    temp.pop_back();
    printSubSum(arr, temp, index+1, ans);
}
//TC - O(2^n . k. logn), where n-no of elem in arr, k-average length of subseq{time taken to get sum of each temp}, 2^n-no of subseq possible for a arr of n elem, logn - time to insert into set
//Sc - O(n + m + k), m-no of unique sum of subarr

void printSubSumBet(vector<int>& arr, int subsum, int index, set<int>& ans){
    if(index >= arr.size()){
        ans.insert(subsum);
        return;
    }
    
    subsum+=arr[index];
    printSubSumBet(arr, subsum, index+1, ans);

    subsum-=arr[index];
    printSubSumBet(arr, subsum, index+1, ans);
}
//TC - O(2^n . log(2^n)), SC - O(m), where m-no of unique sub sum

//------------------------------------------------------------------------------------------------------------------------
//8. Subset Sum 2
//Given an integer arr nums that may contain duplicate, return all possible subsets (power set)
// The solution set must not contain duplicate subsets, return solution in any order

void printSubset2(vector<int>& arr, vector<int>& temp, set<vector<int>>& subset, int index){
    if(index >= arr.size()){
        subset.insert(temp);
        return;
    }
    temp.push_back(arr[index]);
    printSubset2(arr, temp, subset, index+1);

    temp.pop_back();
    printSubset2(arr, temp, subset, index+1);
}
//TC - O(2^n log(2^n)), SC-O(2^n . k), where k is avg length of subsets{multiplication as here ans stores 2^n subsets and each on average has k length}


void printSubset2Opt(vector<int>& arr, vector<int>& temp, vector<vector<int>>& ans, int index){

    ans.push_back(temp);  //add temp to ans every single call not only when index reaches arr.size()

    for(int i=index;i<arr.size();i++){
        if(i!=index && arr[i]==arr[i-1]) continue;
        temp.push_back(arr[i]);
        printSubset2Opt(arr, temp, ans, i+1); //only 1 call since every call temp corresponds to a subset here
        temp.pop_back();
    }
}


auto setSubsetOpt(vector<int>& arr){
    sort(arr.begin(), arr.end());
    vector<int> temp;
    vector<vector<int>> ans;
    printSubset2Opt(arr, temp, ans, 0);
    return ans;
}

//TC - O(2^n . n) - 2^n subsets and each time pushing a subset to result DS costs on worst case n as no of elems
//SC - O(n + n . k), k-average len of subsets, n.k represents resultant space

//----------------------------------------------------------------------------------------------------------------------------- 

//9. Print all permutation of string/array
// Given an arr of distinct integers, return all the possible permutation. Answer can be in any order(may not be in lexicographic order)

//Ex1. [1, 2, 3]
// 1 2 3
// 1 3 2
// 2 1 3
// 2 3 1
// 3 1 2
// 3 2 1

//Ex2. [0,1]
// 0 1
// 1 0

// Ex3. [1]
// 1

//Note: there exist 2! permutations

void printPermutation(map<int, int>& mpp, vector<int>& temp, vector<vector<int>>& ans, int n){
    if(temp.size() == n){
        ans.push_back(temp);
        return;  
    }

    for(auto v:mpp){
        if(v.second>0){
            temp.push_back(v.first);
            mpp[v.first]--;

            printPermutation(mpp, temp, ans, n);
            temp.pop_back();
            mpp[v.first]++;
        }
    }
}

auto setPermutation(vector<int>& arr){
    map<int, int> mpp;
    for(auto v:arr){
        mpp[v]++;
    }

    vector<vector<int>> ans;
    vector<int> temp;
    printPermutation(mpp, temp, ans, arr.size());
    return ans;
}
//TC - O(n . n!){worst case when arr contains all unique}, SC - O(n! . n + n){n for map arr, n-auxillary space, n!-output space}, if removed output space = Sc-O(n+n)

//Approach 2: where we wont use extra map for finding permutation

void printPermutationOpt(vector<int>& arr, int index, vector<vector<int>>& ans){
    if(index >= arr.size()){
        ans.push_back(arr);
        return;
    }
    for(int i=index;i<arr.size();i++){
        swap(arr[index], arr[i]);
        printPermutationOpt(arr, index+1, ans);
        swap(arr[index], arr[i]);
    }
}
//Tc - O(n!.n), SC - O(n)

auto setPermutationOpt(vector<int>& arr){
    vector<vector<int>> ans;
    printPermutationOpt(arr, 0, ans);
    return ans;
}
//-----------------------------------------------------------------------------------------------------

//10.N-Queens Problem
//Place n queens in nxn chessboard such that no 2 queens attack each other
// Given an integer n, return all distinct solution to the n-queens puzzle 


void NQueen(vector<pair<int, int>>& temp, int col, int n, vector<vector<pair<int, int>>>& ans){
    if(col >= n){
        if(temp.size() == n){
            ans.push_back(temp);
        }
        return;
    }
    bool flag;
    for(int i=0;i<n;i++){
        flag=false;
        for(auto v:temp){
            if(v.first == i) flag=true;
            else{
                for(int j=1;j<n;j++){
                    if(i == v.first+j && col == v.second+j){
                        flag=true;
                        break;
                    }
                    if(i == v.first-j && col == v.second-j){
                        flag=true;
                        break;
                    }
                    if(i == v.first-j && col == v.second+j){
                        flag=true;
                        break;
                    }
                    if(i == v.first+j && col == v.second-j){
                        flag=true;
                        break;
                    }
                }
            }
            if(flag) break;
        }
        if(flag) continue;
        temp.push_back({i, col});
        NQueen(temp, col+1, n, ans);
        temp.pop_back();
    }
}

auto setNQueen(int n){
    vector<pair<int, int>> temp;
    vector<vector<pair<int, int>>> ans;
    NQueen(temp, 0, n, ans);
    return ans;
}

bool safePlace(int row, int col, vector<string>& board, int n){
    int duprow=row, dupcol=col;
    while(row>=0 && col>=0){
        if(board[col][row]=='Q') return false;
        row--;
        col--;
    }

    row=duprow;
    col=dupcol;
    while(row<n && col>=0){
        if(board[col][row]=='Q') return false;
        row++;
        col--;
    }

    row=duprow;
    col=dupcol;
    while(col>=0){
        if(board[col][row]=='Q') return false;
        col--;
    }
    return true;
}
//Tc - O(n!.n^2), SC - O(S.n)



//Better one:
void NQueenClean(vector<string>& board, int col, vector<vector<string>>& ans, int n){
    if(col == n){
        ans.push_back(board);
        return;
    }

    for(int row=0;row<n;row++){
        if(safePlace(row, col, board, n)){
            board[col][row] = 'Q';
            NQueenClean(board, col+1, ans, n);
            board[col][row] = '.';
        }
    }
}

auto setNQueenClean(int n){     
    vector<vector<string>> ans;
    vector<string> board(n);
    string s(n, '.');
    for(int i=0;i<n;i++){
        board[i]=s;
    }
    NQueenClean(board, 0, ans, n);
    return ans;
}
//Tc - O(n!.n^2)-worst case but commmonly said as O(n.n!), Sc - O(S.n^2){where O(n^2)-auxillary space and O(S.n^2) is output space}

//Can reduce time complexity by using hashmap
void NQueenOpt(int col, vector<vector<string>>& ans, vector<string>& board, int n, vector<int>& rowHash, vector<int>& upperDiagonal, vector<int>& lowerDiagonal){
    if(col == n){
        ans.push_back(board);
        return;
    }
    for(int row=0;row<n;row++){
        if(rowHash[row] == 0 && upperDiagonal[n-1 + col-row] == 0 && lowerDiagonal[row+col] == 0){
            board[col][row]='Q';
            rowHash[row]=1;
            upperDiagonal[n-1 + col-row]=1;
            lowerDiagonal[row+col]=1;

            NQueenOpt(col+1, ans, board, n, rowHash, upperDiagonal, lowerDiagonal);

            board[col][row]='.';
            rowHash[row]=0;
            upperDiagonal[n-1 + col-row]=0;
            lowerDiagonal[row+col]=0;
        }
    }
}

auto setNQueenOpt(int n){
    vector<string> board;
    string s(n, '.');
    for(int i=0;i<n;i++)
        board.push_back(s);
    vector<vector<string>> ans;
    vector<int> rowHash(n, 0);
    vector<int> upperDiagonal(2*(n-1)+1, 0);
    vector<int> lowerDiagonal(2*(n-1)+1, 0);

    NQueenOpt(0, ans, board, n, rowHash, upperDiagonal, lowerDiagonal);
    return ans;
}
//TC - O(n!){considering for each col the no of possible safe place decreases by 1 making n.(n-1).(n-2)...}, SC - O(n)-auxillary space(from hash arrs),(including output) O(n + S.n^2)-where S is no of possible solution, all n! answers do not make up as final olution so


//------------------------------------------------------------------------------------------------------
//11.Suduku Solver

bool validSud(vector<vector<char>>& board, int row, int col, char c){
    for(int i=0;i<9;i++){
        if(board[row][i]==c)
            return false;
        if(board[i][col]==c)
            return false;
        if(board[3*(row/3) + (i/3)][3*(col/3) + (i%3)]==c)
            return false;
    }
    return true;
}

bool solveSuduku(vector<vector<char>>& board){
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            if(board[i][j] == '.'){
                for(char c='1';c<='9';c++){
                    if(validSud(board, i, j, c)){
                        board[i][j] = c;
                        if(solveSuduku(board) == true){
                            return true;
                        }
                        else{
                            board[i][j] = '.';
                        }
                    }
                }
                return false;
            }
        }
    }
    return true;
}
//TC - O(9^E), SC - O(E)

//-----------------------------------------------------------------------------------------------------



int main(){
    string str;
    cin>>str;                          // use getline(cin, str) if input has spaces
    int n=str.size();
    bool res=PalRec(str, 0, n);
    cout<<str<<" :: Palindrome: "<<(res ? "true" : "false")<<endl;

    // vector<int> temp;

    // vector<int> arr={1,2,3};
    // auto ans = setNQueenOpt(6);
    // for(auto v:ans){
    //     if(v.empty())
    //         cout<<"{}";
    //     else
    //         for(auto i:v)
    //             cout<<i<<" ";
    //     cout<<endl;
    // }
    // int cnt=1;
    // for(auto v:ans){
    //     cout<<"Possibility "<<cnt++<<":";
    //     for(auto i:v){
    //         cout<<"("<<i.first<<","<<i.second<<")"<<" ";
    //     }
    //     cout<<endl;
    // }
    // for(auto v:ans){
    //     cout<<"Possibility "<<cnt++<<":"<<endl;
    //     for(auto s:v){
    //         cout<<s<<endl;
    //     }
    //     cout<<endl<<endl;
    // }


    //Suduku
    vector<vector<char>> board = {
    {'5', '3', '.', '.', '7', '.', '.', '.', '.'},
    {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
    {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
    {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
    {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
    {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
    {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
    {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
    {'.', '.', '.', '.', '8', '.', '.', '7', '9'}
    };
    solveSuduku(board);

    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++)
            cout<<board[i][j]<<" ";
        cout<<endl;
    }

    return 0;
}