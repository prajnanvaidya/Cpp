#include<bits/stdc++.h>
using namespace std;

/*
================================================================================
                            C++ BASICS - COMPLETE NOTES
================================================================================
Note on headers: instead of including <iostream>, <math.h>, <string> etc.
individually, competitive programmers use:

    #include<bits/stdc++.h>

which pulls in every standard library header at once. Convenient, but it is a
GCC-specific header (not standard C++), so it won't compile on MSVC or Clang
with libc++. For portable/production code, include only what you need.

TABLE OF CONTENTS
-----------------
  PART 1  : Output - cout
  PART 2  : Input - cin
  PART 3  : Strings and getline (+ the classic cin/getline bug)
  PART 4  : Data types, sizes, and ranges
  PART 5  : Type conversion and the integer division trap
  PART 6  : Operators
  PART 7  : Conditionals - if / else if / else
  PART 8  : Switch statement
  PART 9  : Loops - for, while, do-while
  PART 10 : break and continue
  PART 11 : Arrays (1D and 2D)
  PART 12 : Functions
  PART 13 : Scope, const, and auto
  PART 14 : Fast I/O for competitive programming
  PART 15 : Common mistakes checklist

================================================================================
PART 1 : OUTPUT - cout
================================================================================

    std::cout << "Hello world" << std::endl;

The `std::` prefix is needed unless you wrote `using namespace std;` at the top.

KEY POINTS:
  - You can chain any number of << in a single statement, of any length.
  - There is NO automatic space or separator between << items (unlike Python's
    print, which inserts spaces between arguments). You must add " " yourself.
  - endl vs "\n":
        endl  = newline + FLUSHES the output buffer (forces it to be written
                out immediately)
        "\n"  = newline only, no flush
    "\n" is FASTER. In competitive programming with heavy output, endl in a
    tight loop can be a real performance problem. Prefer "\n" unless you
    specifically need the flush.

USEFUL ESCAPE SEQUENCES:
    \n   newline          \t   tab           \\   backslash
    \"   double quote     \'   single quote
*/

void demo_output(){
    cout << "Hello world" << endl;
    cout << "Hi Ray" << "\n";
    cout << "Good to meet u" << endl << "How is your day going" << "\n" << "Bye" << "\n";

    // No default space between items - compare:
    int x = 5, y = 7;
    cout << x << y << "\n";           // prints "57"  - jammed together
    cout << x << " " << y << "\n";     // prints "5 7" - space added manually
}


/*
================================================================================
PART 2 : INPUT - cin
================================================================================

    int x, y;
    cin >> x >> y;

KEY POINTS:
  - Multiple values can be read in one statement by chaining >>.
  - When entering them, separate with spaces OR newlines - cin treats ANY
    whitespace (space, tab, newline) as a separator, so both work identically.
  - cin >> SKIPS leading whitespace automatically, then reads until it hits
    the next whitespace.
  - cin >> stops at whitespace. This is why it cannot read a full sentence
    into a string - see Part 3.
*/

void demo_input(){
    int x, y;
    cin >> x >> y;
    cout << x << " and " << y << "\n";
}


/*
================================================================================
PART 3 : STRINGS AND getline
================================================================================

    string s;
    cin >> s;             // reads ONE WORD only - stops at the first space
    getline(cin, s);      // reads an ENTIRE LINE, spaces included

getline reads up to (and consumes) the newline character, but does not store
the newline in the string. It reads exactly one line - not more.

--------------------------------------------------------------------------------
THE CLASSIC BUG: MIXING  cin >>  AND  getline
--------------------------------------------------------------------------------
This is the single most common beginner trap in C++ input handling.

    int age;
    string name;
    cin >> age;              // input: "25\nPrajnan Vaidya\n"
    getline(cin, name);      // name comes out EMPTY!

WHY: `cin >> age` reads the digits "25" and stops - but it LEAVES the newline
character sitting in the input buffer. getline then immediately hits that
leftover newline, concludes "this line is over", and returns an empty string
without ever reading the actual name.

VERIFIED BY TESTING - the above really does produce:
    age=[25]  name=[]

THE FIX - discard the leftover newline before calling getline:

    cin >> age;
    cin.ignore();            // discards the leftover newline
    getline(cin, name);      // now works correctly

A more robust form that clears everything remaining on the line:

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

RULE OF THUMB: any time you follow a `cin >>` with a `getline`, you need
cin.ignore() in between.
*/

void demo_strings(){
    // Reading two separate words
    string s1, s2;
    cin >> s1 >> s2;
    cout << s1 << " " << s2 << endl;    // space added manually

    // Reading a full line
    cin.ignore();                        // clear the leftover newline first
    string str;
    getline(cin, str);
    cout << str << endl;
}


/*
================================================================================
PART 4 : DATA TYPES, SIZES, AND RANGES
================================================================================

INTEGER TYPES:
    TYPE            TYPICAL SIZE    APPROXIMATE RANGE
    ---------------------------------------------------------------------------
    bool            1 byte          true / false
    char            1 byte          256 distinct values
                                    (-128..127 signed, or 0..255 unsigned -
                                     plain `char`'s signedness is
                                     implementation-defined)
    short           2 bytes         -32,768 .. 32,767
    int             4 bytes         -2,147,483,648 .. 2,147,483,647  (~2*10^9)
    long            8 bytes*        same as long long on 64-bit Linux
    long long       8 bytes         ~ +/- 9.2 * 10^18

FLOATING POINT TYPES:
    float           4 bytes         ~7 decimal digits of precision
    double          8 bytes         ~15-16 decimal digits of precision
    long double     16 bytes*       ~18-19 decimal digits of precision

*IMPORTANT CORRECTION - SIZES ARE PLATFORM-DEPENDENT:
The C++ standard only specifies MINIMUM sizes and relative ordering, not exact
byte counts. VERIFIED BY TESTING on x86-64 Linux with g++:

    long double  =  16 bytes    (NOT 10 - a common claim, because the x87
                                 extended format uses 80 bits = 10 bytes of
                                 actual PRECISION, but it is padded to 16 bytes
                                 for memory alignment)
    long         =  8 bytes     (but only 4 bytes on 64-bit Windows/MSVC!)

Always use sizeof(type) to check on your own system rather than memorising
numbers. The one thing you can rely on:
    sizeof(char) <= sizeof(short) <= sizeof(int) <= sizeof(long) <= sizeof(long long)

--------------------------------------------------------------------------------
WHICH TYPE TO PICK
--------------------------------------------------------------------------------
"If a char fits in a string, or an int fits in a long long, why not just always
use the bigger type?" - because memory adds up. One extra variable is
irrelevant; an array of 10 million long longs instead of ints wastes 40 MB and
will be slower (worse cache utilisation - more bytes to move for the same
number of elements).

PRACTICAL RULE FOR CP:
    - Use int by default.
    - Switch to long long the moment a value could exceed ~2 * 10^9.
    - Watch for OVERFLOW in intermediate calculations, not just final answers:
          int a = 100000, b = 100000;
          int   bad  = a * b;                 // OVERFLOWS - a*b done as int
          long long good = (long long)a * b;   // cast FIRST, then multiply

INTEGER OVERFLOW BEHAVIOR - VERIFIED BY TESTING:
    int big = 2147483647;   // INT_MAX
    big + 1  ->  -2147483648   // wraps around to the minimum, silently

No error, no warning at runtime - it just silently produces a wrong answer.
This is why overflow bugs are so hard to spot.

USEFUL CONSTANTS (from <climits> / <cfloat>, included in bits/stdc++.h):
    INT_MAX, INT_MIN, LLONG_MAX, LLONG_MIN
*/

void demo_types(){
    // char uses SINGLE quotes; string uses DOUBLE quotes
    char ch2 = 'b';
    cout << ch2 << endl;

    // A char IS a small integer underneath - VERIFIED BY TESTING:
    char c = 'A';
    cout << c << " " << (int)c << endl;    // prints: A 65
    // This is why 'A' + 1 == 'B', and why (ch - 'a') gives a letter's index.

    cout << "int is " << sizeof(int) << " bytes on this machine\n";
}


/*
================================================================================
PART 5 : TYPE CONVERSION AND THE INTEGER DIVISION TRAP
================================================================================

THE #1 ARITHMETIC BUG IN C++:

    cout << 5/2;      // prints 2, NOT 2.5     <-- VERIFIED BY TESTING
    cout << 5/2.0;    // prints 2.5

WHY: if BOTH operands are integers, C++ performs INTEGER DIVISION - the result
is an integer and the fractional part is TRUNCATED (chopped off, not rounded).
5/2 = 2.5 -> truncated to 2. Note truncation always goes toward zero, so
-5/2 gives -2, not -3.

HOW TO GET A REAL DIVISION - make at least one operand floating point:
    5 / 2.0            // literal as double
    (double)5 / 2      // explicit cast
    double a=5, b=2; a/b;

--------------------------------------------------------------------------------
IMPLICIT CONVERSION (automatic)
--------------------------------------------------------------------------------
C++ silently promotes the "smaller" type to the "bigger" one in mixed
expressions:  int + double -> double.

    int x = 3.99;      // truncates to 3 (no rounding, no warning by default)
    double d = 5;       // becomes 5.0 - safe, no loss

--------------------------------------------------------------------------------
EXPLICIT CONVERSION (casting)
--------------------------------------------------------------------------------
    (int)3.99                 // C-style cast -> 3
    static_cast<int>(3.99)    // C++ style - preferred, safer, easier to spot

To ROUND rather than truncate, use round(), floor(), or ceil() from <cmath>:
    (int)(3.7)          -> 3      (truncates)
    round(3.7)          -> 4      (rounds to nearest)
*/


/*
================================================================================
PART 6 : OPERATORS
================================================================================

ARITHMETIC:  +   -   *   /   %
    %  is MODULO (remainder). Works only on INTEGER types, not float/double.
       7 % 3 = 1.  Very common for "is even" (n % 2 == 0), extracting digits
       (n % 10), and wrapping indices.

RELATIONAL (produce true/false):   ==   !=   <   >   <=   >=

LOGICAL:   &&  (AND)     ||  (OR)     !  (NOT)
    SHORT-CIRCUIT EVALUATION: in `A && B`, if A is false, B is NEVER evaluated
    (the result is already known). Same for `A || B` when A is true.
    This is not just an optimization - it's a guarantee you can rely on:
        if (i < n && arr[i] == x)      // safe: arr[i] is only touched if i<n
        if (arr[i] == x && i < n)      // UNSAFE: may read out of bounds first

ASSIGNMENT:  =   +=   -=   *=   /=   %=
    x += 3   is shorthand for   x = x + 3

INCREMENT / DECREMENT:  ++   --
    PRE-increment  (++i): increments FIRST, then yields the new value
    POST-increment (i++): yields the OLD value first, then increments

    int i = 5;
    cout << ++i;    // prints 6, i is now 6
    int j = 5;
    cout << j++;    // prints 5, j is now 6

    In a standalone statement (i++; on its own line) they are identical.
    The difference only matters when the value is USED in the same expression.

TERNARY (conditional) OPERATOR:   condition ? valueIfTrue : valueIfFalse
    int maxVal = (a > b) ? a : b;
    A compact if/else that produces a VALUE. Good for short choices; avoid
    nesting them deeply, as readability collapses fast.

BITWISE:   &  (AND)   |  (OR)   ^  (XOR)   ~  (NOT)   <<  (left shift)   >>  (right shift)
    Operate on the individual bits of an integer.
        n << 1   is  n * 2        n >> 1   is  n / 2  (for non-negative n)
        n & 1    is  1 if n is odd, 0 if even  (faster idiom than n % 2)
    Note: << and >> are the SAME symbols as stream insertion/extraction - C++
    tells them apart by context (cout << x vs 5 << 1).

OPERATOR PRECEDENCE: when unsure, use parentheses. They cost nothing and
remove all ambiguity for both the compiler and the next person reading it.
*/


/*
================================================================================
PART 7 : CONDITIONALS - if / else if / else
================================================================================

Only ONE branch of an if/else-if/else chain ever executes - the FIRST one whose
condition is true. This is why ordering matters, and why you can write
`marks < 45` without also writing `marks >= 25`: if the chain reached that
branch, everything above it was already false.

Braces {} are optional for a SINGLE statement, but always using them prevents a
whole class of bugs when you later add a second line.
*/

// TASK 1: Grade from marks
//   below 25 -> F | 25-44 -> E | 45-49 -> D | 50-59 -> C | 60-79 -> B | 80-100 -> A
void gradeFromMarks(){
    int marks;
    cin >> marks;

    if(marks < 0 || marks > 100){
        cout << "Invalid marks entered!" << endl;
    }
    else{
        if(marks < 25)        cout << "Grade: F" << endl;
        else if(marks < 45)   cout << "Grade: E" << endl;
        else if(marks < 50)   cout << "Grade: D" << endl;
        else if(marks < 60)   cout << "Grade: C" << endl;
        else if(marks < 80)   cout << "Grade: B" << endl;
        else                  cout << "Grade: A" << endl;
    }
}
// Note the input VALIDATION first - checking for impossible input before
// processing is a good habit that avoids nonsense output.

// TASK 2: Job eligibility from age
//   age < 18            -> not eligible for job
//   age >= 18           -> eligible for job
//   age 55..57          -> eligible for job, but retirement soon
//   age > 57            -> retirement time
void jobEligibility(){
    int age;
    cin >> age;

    if(age < 18){
        cout << "not eligible for job";
    }
    else if(age <= 57){
        cout << "Eligible for job";
        if(age >= 55){                  // FIX: was age>54, which is the same
            cout << " but retirement soon";   // thing numerically for ints, but
        }                                      // age>=55 states the intent
    }                                           // directly and matches the spec
    else{
        cout << "retirement time";
    }
    cout << endl;
}
// NESTED IF: the inner `if` only runs when the outer condition already held,
// letting you add a refinement without repeating the outer test.


/*
================================================================================
PART 8 : SWITCH STATEMENT
================================================================================
An alternative to a long if/else-if chain when you are comparing ONE variable
against several CONSTANT values.

RULES AND GOTCHAS:
  - `break` is MANDATORY at the end of each case. Without it, execution FALLS
    THROUGH into the next case and keeps running - a classic bug source.
    (Deliberate fall-through is occasionally useful, e.g. grouping several
    cases that share the same action, but it must be intentional.)
  - `default:` handles everything not matched - like a final `else`.
  - Case labels must be COMPILE-TIME CONSTANTS (integers, chars, enums).
    You cannot switch on a string, a double, or use ranges/conditions.

WHEN TO USE: discrete, fixed values (menu choices, day numbers, operators).
WHEN NOT TO: ranges or conditions (like the marks->grade task) - use if/else.
*/

void dayOfWeek(){
    int day;
    cin >> day;
    switch(day){
        case 1: cout << "Monday";    break;
        case 2: cout << "Tuesday";   break;
        case 3: cout << "Wednesday"; break;    // FIX: was "Wednesdday" (typo)
        case 4: cout << "Thursday";  break;
        case 5: cout << "Friday";    break;
        case 6: cout << "Saturday";  break;
        case 7: cout << "Sunday";    break;
        default: cout << "Invalid day";
    }
    cout << endl;
}


/*
================================================================================
PART 9 : LOOPS
================================================================================

FOR LOOP - use when the number of iterations is known upfront:

    for(initialization; condition; update){ body }
    for(int i = 0; i < n; i++){ ... }

    Execution order:
      1. init runs ONCE at the start
      2. condition is checked - if false, loop ends
      3. body runs
      4. update runs
      5. back to step 2

WHILE LOOP - use when you loop until something becomes true, count unknown:

    while(condition){ body }

    int n = 7789;
    while(n > 0){ cout << n%10; n /= 10; }    // extract digits

DO-WHILE LOOP - like while, but the body ALWAYS runs at least once, because
the condition is checked at the END:

    do{ body } while(condition);

    Useful for input validation / menus, where you must prompt at least once:
        do{ cin >> choice; } while(choice < 1 || choice > 5);

RANGE-BASED FOR (C++11) - iterate over every element without index arithmetic:

    int arr[5] = {1,2,3,4,5};
    for(int x : arr){ cout << x << " "; }        // read-only copy
    for(int &x : arr){ x *= 2; }                  // reference - modifies arr

    Use `auto` to avoid writing out the type:  for(auto x : arr)

INFINITE LOOPS: while(true) or for(;;) - must contain a break somewhere,
otherwise the program hangs.
*/


/*
================================================================================
PART 10 : break AND continue
================================================================================

    break     - exits the ENTIRE loop immediately
    continue  - skips the REST of the current iteration, jumps to the next one

    for(int i=1; i<=10; i++){
        if(i == 5) continue;      // skips printing 5, keeps looping
        if(i == 8) break;          // stops the loop entirely at 8
        cout << i << " ";
    }
    // prints: 1 2 3 4 6 7

IMPORTANT: in NESTED loops, break exits only the INNERMOST loop it is inside -
not all of them. To exit multiple levels you need a flag variable, or to
restructure the code into a function and `return` out of it.

Note: `break` in a switch exits the SWITCH, not any surrounding loop - which
is why using break inside a switch that's inside a loop needs care.
*/


/*
================================================================================
PART 11 : ARRAYS
================================================================================
An ARRAY is a collection of HOMOGENEOUS data - every element is the same type,
stored in one CONTIGUOUS block of memory.

WHY: if you need 100 related values, declaring 100 separate variables is
unmanageable. An array gives you one name plus an index.

    int arr[3];                   // declared, values are GARBAGE (uninitialized)
    int arr[3] = {10, 20, 30};    // declared and initialized
    int arr[]  = {10, 20, 30};    // size inferred as 3
    int arr[5] = {};              // ALL elements set to 0
    int arr[5] = {1, 2};          // {1, 2, 0, 0, 0} - rest zero-filled

You must give either a SIZE or an INITIALIZER LIST - the compiler needs to know
how much memory to reserve at compile time.

INDEXING IS 0-BASED: valid indices for int arr[3] are 0, 1, 2 - NOT 3.

    ** C++ DOES NOT CHECK ARRAY BOUNDS. **
    arr[5] on a 3-element array compiles fine and silently reads/writes whatever
    memory happens to sit there. No error is raised. This is undefined behavior
    and a top source of crashes and mystery bugs. Guarding your indices is
    entirely YOUR job.

RANDOM ACCESS: arr[i] is O(1) - it jumps straight to the element by computing
(start address + i * element size), which works precisely because the memory
is contiguous.
*/

void demo_arrays(){
    int arr[3];
    cin >> arr[0] >> arr[1] >> arr[2];

    // CORRECTION on printing an array:
    // The original comment said "one cannot print arr with just arr name".
    // That is not quite right - `cout << arr` COMPILES AND RUNS, it just
    // doesn't do what you want. VERIFIED BY TESTING, it prints something like:
    //     0x7fff12097aac
    // which is the MEMORY ADDRESS of the first element, not the contents.
    //
    // WHY: an array name used in most expressions DECAYS into a pointer to its
    // first element. cout receives a pointer and prints the address.
    //
    // So the accurate statement is: printing an array by name gives you its
    // ADDRESS, not its elements. To print the contents you must traverse it.
    //
    // (Exception worth knowing: `char` arrays DO print as text, because cout
    //  has a special overload treating char* as a C-style string.)

    for(int i = 0; i < 3; i++){
        cout << arr[i] << " ";     // space added, else digits jam together
    }
    cout << endl;
}

/*
--------------------------------------------------------------------------------
ARRAY SIZE AND THE sizeof TRAP
--------------------------------------------------------------------------------
INSIDE main (or wherever the array is DECLARED), this works:

    int arr[5];
    int n = sizeof(arr) / sizeof(arr[0]);     // = 5, correct

But once an array is PASSED TO A FUNCTION, it decays to a pointer, and sizeof
gives the POINTER's size (8 bytes on 64-bit), not the array's:

    void f(int arr[]){
        int n = sizeof(arr)/sizeof(arr[0]);   // WRONG - gives 8/4 = 2, always
    }

RULE: always pass the size explicitly as a separate parameter:

    void f(int arr[], int n){ ... }

--------------------------------------------------------------------------------
2D ARRAYS
--------------------------------------------------------------------------------
    int grid[3][4];                    // 3 rows, 4 columns
    int grid[2][3] = {{1,2,3},{4,5,6}};

    for(int i=0; i<3; i++){
        for(int j=0; j<4; j++){
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }

Stored in ROW-MAJOR order: all of row 0 sits contiguously, then all of row 1,
and so on. Looping rows-outer / columns-inner therefore walks memory in order,
which is measurably faster than the reverse on large grids (better cache use).
*/


/*
================================================================================
PART 12 : FUNCTIONS
================================================================================
A named, reusable block of code.

    returnType functionName(parameters){
        body
        return value;      // omit for void functions
    }

    int add(int a, int b){ return a + b; }
    void greet(){ cout << "Hello\n"; }        // void = returns nothing

DECLARATION BEFORE USE: C++ reads top to bottom, so a function must be declared
above where it is called. Either define it earlier in the file, or write a
PROTOTYPE near the top and define it later:

    int add(int a, int b);        // prototype (note the semicolon)
    int main(){ cout << add(2,3); }
    int add(int a, int b){ return a + b; }     // definition below

--------------------------------------------------------------------------------
PASS BY VALUE vs PASS BY REFERENCE
--------------------------------------------------------------------------------
BY VALUE (default) - the function gets a COPY. Changes do NOT affect the original:

    void f(int x){ x = 100; }
    int a = 5;  f(a);  // a is still 5

BY REFERENCE (&) - the function works on the ORIGINAL. Changes DO stick:

    void f(int &x){ x = 100; }
    int a = 5;  f(a);  // a is now 100

CONST REFERENCE (const &) - no copy made, but modification is forbidden.
Use this for large objects you only need to READ - it avoids the cost of
copying without the risk of accidental changes:

    void f(const string &s){ cout << s; }

QUICK RULE:
    small built-in types (int, char, bool, double)  -> pass by value
    large objects you only read                      -> const Type&
    anything you need to modify in place             -> Type&

Arrays are a special case: they always effectively pass by reference (they
decay to a pointer), so a function CAN modify the caller's array even without
an explicit &.

--------------------------------------------------------------------------------
DEFAULT ARGUMENTS
--------------------------------------------------------------------------------
    int power(int base, int exp = 2){ ... }
    power(5);        // exp defaults to 2
    power(5, 3);     // exp is 3

Defaults must be the RIGHTMOST parameters - you can't default a middle one.
*/


/*
================================================================================
PART 13 : SCOPE, const, AND auto
================================================================================

SCOPE - where a variable is visible and how long it lives.

    LOCAL     : declared inside {} - exists only within those braces.
                Two different functions can both have their own `i`.
    GLOBAL    : declared outside all functions - visible everywhere, lives for
                the whole program. Use sparingly; global state makes bugs
                harder to trace.
    BLOCK     : any {} creates a scope, including loop bodies and if blocks.
                `for(int i...)` - i exists only inside that loop.

SHADOWING: an inner variable with the same name HIDES the outer one within its
scope. Legal, but confusing - avoid deliberately.

--------------------------------------------------------------------------------
const
--------------------------------------------------------------------------------
    const int MAX = 100;
    MAX = 50;              // COMPILER ERROR - cannot modify a const

Use it for values that must never change. It documents intent AND lets the
compiler catch accidental modification.

--------------------------------------------------------------------------------
auto  (C++11)
--------------------------------------------------------------------------------
Lets the compiler deduce the type from the initializer:

    auto x = 5;          // int
    auto y = 3.14;       // double
    auto c = 'a';        // char

Handy for long type names, and required-ish for lambdas. But `auto x;` alone is
illegal - there must be an initializer to deduce FROM. Don't overuse it for
simple types where writing `int` is clearer.
*/


/*
================================================================================
PART 14 : FAST I/O FOR COMPETITIVE PROGRAMMING
================================================================================
cin/cout are synchronized with C's stdio (scanf/printf) by default, which makes
them noticeably slow for large input. With 10^5+ lines of I/O this alone can
cause a Time Limit Exceeded.

Add these two lines as the FIRST thing inside main():

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

  - sync_with_stdio(false) : unlinks cin/cout from C's stdio buffers
  - cin.tie(NULL)          : stops cout from being flushed before every cin

CAVEATS:
  - After this, do NOT mix cin/cout with scanf/printf in the same program -
    the buffers are no longer synchronized and output can come out interleaved
    incorrectly.
  - Also prefer "\n" over endl, since endl forces a flush every single time,
    which undoes much of the benefit in an output-heavy loop.
*/


/*
================================================================================
PART 15 : COMMON MISTAKES CHECKLIST
================================================================================
    [X] Using = instead of ==       -> `if(x = 5)` ASSIGNS 5 and is always true
    [X] 5/2 expecting 2.5           -> integer division truncates; use 5/2.0
    [X] Forgetting break in switch  -> silent fall-through into the next case
    [X] Array index out of bounds   -> C++ does NOT check; silent corruption
    [X] cout << arr to print array  -> prints the ADDRESS, not the contents
    [X] sizeof(arr) inside a func   -> array decayed to a pointer; pass n instead
    [X] getline right after cin >>  -> reads an empty line; need cin.ignore()
    [X] Integer overflow            -> cast to long long BEFORE multiplying
    [X] Using uninitialized vars    -> contains garbage, not 0
    [X] Missing semicolon after     -> `do{...}while(cond);` needs the final ;
        do-while
    [X] endl inside a hot loop      -> forces a flush every time; use "\n"
================================================================================
*/


int main(){
    // Fast I/O - recommended for competitive programming
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // Uncomment whichever demo you want to run:
    // demo_output();
    // demo_input();
    // demo_strings();
    // demo_types();
    // gradeFromMarks();
    // jobEligibility();
    // dayOfWeek();
    demo_arrays();

    return 0;
}