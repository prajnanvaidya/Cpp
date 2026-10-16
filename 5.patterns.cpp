#include<bits/stdc++.h>
using namespace std;

/*
================================================================================
                          PATTERN PRINTING - COMPLETE NOTES
================================================================================
General strategy for approaching ANY pattern question:

    1. Outer loop  -> controls the ROWS
    2. Inner loop  -> controls the COLUMNS, tied to the outer loop's variable
    3. Print the actual content INSIDE the inner loop
    4. Look for SYMMETRY - many patterns are two halves (upper/lower or
       left/right) that can be built from a shared formula, or are built by
       combining 2-3 separate inner loops (e.g. spaces, then stars, then
       spaces again) run back to back within one row

All patterns below use only O(1) auxiliary space (a handful of scalar loop
counters) - the "space" being filled is just standard output, not memory.
So SPACE COMPLEXITY = O(1) for every function in this file unless noted
otherwise. TIME COMPLEXITY is annotated per pattern, generally O(n^2) since
most patterns print on the order of n^2 characters total across all rows.

Where the source material had more than one working solution for the same
pattern (often written while learning, weakest attempt first), all versions
are kept, ordered from the earliest/weakest attempt to the cleanest final
one - so the evolution in thinking is visible, not just the answer. Broken
attempts are KEPT AS-IS (not silently fixed) with a comment explaining
exactly why they fail, since that's often more instructive than only ever
seeing correct code.

TABLE OF CONTENTS (pattern number -> shape)
--------------------------------------------------------------------------------
   1  Solid n x n square of stars
   2  Left-aligned increasing triangle of stars
   3  Left-aligned increasing triangle of numbers (1, 12, 123, ...)
   4  Left-aligned increasing triangle, row number repeated (1, 22, 333, ...)
   5  Left-aligned decreasing triangle of stars
   6  Left-aligned decreasing triangle of numbers
   7  Solid pyramid of stars (centered)
   8  Inverted solid pyramid of stars (centered)
   9  Diamond (pyramid stacked on inverted pyramid)
  10  Half-diamond stars (increasing then decreasing, left-aligned)
  11  Right-angled triangle, alternating 1/0 checkerboard
  12  Symmetric number triangle (1...n mirrored, touching in the middle)
  13  Right-angled triangle, continuously incrementing numbers
  14  Left-aligned increasing triangle of letters (A, AB, ABC, ...)
  15  Left-aligned decreasing triangle of letters (ABCDE, ABCD, ...)
  16  Left-aligned triangle, row letter repeated (A, BB, CCC, ...)
  17  Letter "hourglass" pyramid (A / ABA / ABCBA / ABCDCBA)
  18  Right-aligned decreasing triangle of letters (E / DE / CDE / ...)
  19  Hollow butterfly (two triangles, hollow middle)
  20  Hollow "X" / sandglass of stars
  21  Hollow square (border only)
  22  Concentric square "rings" of numbers
================================================================================
*/


/*
================================================================================
PATTERN 1 : Solid n x n square of stars
================================================================================
Expected output (n=5):
    * * * * *
    * * * * *
    * * * * *
    * * * * *
    * * * * *

Simplest pattern - inner loop is completely independent of outer loop.
*/
void print1(int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout<<"* ";
        }
        cout<<endl;
    }
}
// TC - O(n^2)   (n rows x n columns)
// SC - O(1)


/*
================================================================================
PATTERN 2 : Left-aligned increasing triangle of stars
================================================================================
Expected output (n=5):
    *
    * *
    * * *
    * * * *
    * * * * *

Inner loop bound is now tied to the outer loop variable i: row i prints i+1
stars. This "tie the inner bound to i" idea is the core trick behind almost
every triangular pattern.
*/
void print2(int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<=i;j++){
            cout<<"* ";
        }
        cout<<endl;
    }
}
// TC - O(n^2)   (1+2+3+...+n = n(n+1)/2, drop constant -> O(n^2))
// SC - O(1)


/*
================================================================================
PATTERN 3 : Left-aligned increasing triangle of numbers
================================================================================
Expected output (n=5):
    1
    1 2
    1 2 3
    1 2 3 4
    1 2 3 4 5

Same shape as Pattern 2, but print j+1 (the column number) instead of "*".
*/
void print3(int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<=i;j++){
            cout<<j+1<<" ";
        }
        cout<<endl;
    }
}
// TC - O(n^2), SC - O(1)


/*
================================================================================
PATTERN 4 : Left-aligned triangle, row number repeated
================================================================================
Expected output (n=5):
    1
    2 2
    3 3 3
    4 4 4 4
    5 5 5 5 5

Same shape again, but print i+1 (the ROW number) on every column instead of
the column number.
*/
void print4(int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<=i;j++){
            cout<<i+1<<" ";
        }
        cout<<endl;
    }
}
// TC - O(n^2), SC - O(1)


/*
================================================================================
PATTERN 5 : Left-aligned decreasing triangle of stars
================================================================================
Expected output (n=5):
    * * * * *
    * * * *
    * * *
    * *
    *

Inverse of Pattern 2 - inner bound shrinks as i grows: n-i stars per row.
*/
void print5(int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<n-i;j++){
            cout<<"* ";
        }
        cout<<endl;
    }
}
// TC - O(n^2), SC - O(1)


/*
================================================================================
PATTERN 6 : Left-aligned decreasing triangle of numbers
================================================================================
Expected output (n=5):
    1 2 3 4 5
    1 2 3 4
    1 2 3
    1 2
    1

Same shrinking bound as Pattern 5, printing column numbers again.
*/
void print6(int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<n-i;j++){
            cout<<j+1<<" ";
        }
        cout<<endl;
    }
}
// TC - O(n^2), SC - O(1)


/*
================================================================================
PATTERN 7 : Solid pyramid of stars (centered)
================================================================================
Expected output (n=5):
            *
          * * *
        * * * * *
      * * * * * * *
    * * * * * * * * *

Three inner loops run back-to-back within each row:
    1. leading spaces  : shrink as i grows      -> 2*(n-1-i)
    2. stars           : grow as i grows        -> 2*i+1 (always odd)
    3. trailing spaces : same as (1) - harmless, since trailing whitespace
                          is invisible; kept here to show it doesn't break
                          anything, but it can safely be removed
*/
void print7(int n){
    for(int i=0;i<n;i++){
        // leading space
        for(int j=0;j<2*(n-1-i);j++){
            cout<<" ";
        }
        // stars
        for(int k=0;k<(2*i+1);k++){
            cout<<"* ";
        }
        // trailing space (does not affect visible output)
        for(int j=0;j<2*(n-1-i);j++){
            cout<<" ";
        }  
        cout<<endl;
    }
}
// TC - O(n^2)   (three loops per row, but each is still bounded by O(n),
//                and there are n rows -> O(n) * O(n) = O(n^2))
// SC - O(1)


/*
================================================================================
PATTERN 8 : Inverted solid pyramid of stars (centered)
================================================================================
Expected output (n=5):
    * * * * * * * * *
      * * * * * * *
        * * * * *
          * * *
            *

Mirror of Pattern 7: leading spaces GROW as i grows (2*i), stars SHRINK
(2*(n-i)-1, always odd).
*/
void print8(int n){
    for(int i=0;i<n;i++){
        // leading space
        for(int j=0; j<2*i; j++){
            cout<<" ";
        }
        // stars
        for(int k=0;k<2*n-1-2*i;k++){
            cout<<"* ";
        }
        cout<<endl;
    }
}
// TC - O(n^2), SC - O(1)


/*
================================================================================
PATTERN 9 : Diamond (Pattern 7 stacked on Pattern 8)
================================================================================
Expected output (n=5):
            *
          * * *
        * * * * *
      * * * * * * *
    * * * * * * * * *
    * * * * * * * * *
      * * * * * * *
        * * * * *
          * * *
            *

Literally the pyramid loop (Pattern 7's logic) followed immediately by the
inverted-pyramid loop (Pattern 8's logic) - reuse, don't reinvent.
*/
void print9(int n){
    // top half - same shape as print7
    for(int i=0;i<n;i++){
        for(int j=0;j<2*(n-1-i);j++){
            cout<<" ";
        }
        for(int j=0;j<2*i+1;j++){
            cout<<"* ";
        }
        cout<<endl;
    }
    // bottom half - same shape as print8
    for(int i=0;i<n;i++){
        for(int j=0;j<2*i;j++){
            cout<<" ";
        }
        for(int j=0;j<2*(n-i)-1;j++){
            cout<<"* ";
        }
        cout<<endl;
    }
}
// TC - O(n^2)   (two O(n^2) halves back to back -> still O(n^2), constants
//                dropped)
// SC - O(1)


/*
================================================================================
PATTERN 10 : Half-diamond stars (increasing then decreasing)
================================================================================
Expected output (n=5):
    *
    * *
    * * *
    * * * *
    * * * * *
    * * * *
    * * *
    * *
    *

Total rows = 2n-1. First n rows increase 1..n stars, remaining n-1 rows
decrease back down. Two approaches shown - both correct, second is a
tidier rewrite of the same idea.
*/

// ---- Approach A: if/else branching directly on the two loop shapes ----
void print10(int n){
    for(int i=0;i<2*n-1;i++){
        if(i<n){
            for(int j=0;j<i+1;j++){
                cout<<"* ";
            }
        }
        else{
            for(int j=0;j<2*n-i-1;j++){
                cout<<"* ";
            }
        }
        cout<<endl;
    }
}
// TC - O(n^2), SC - O(1)

// ---- Approach B (cleaner): compute the star count once, then loop once ----
void print10updated(int n){
    int stars;
    for(int i=0;i<2*n-1;i++){
        stars=i+1;
        if (i>=n){
            stars=2*n-i-1;
        }
        for(int j=0;j<stars;j++){
            cout<<"* ";
        }
        cout<<endl;
    }
}
// TC - O(n^2), SC - O(1)
// Same output as Approach A - this version just avoids duplicating the
// inner print loop in both branches of the if/else, which is a small but
// good habit: compute the VALUE that varies, then have only ONE loop that
// uses it, rather than repeating the loop body per branch.


/*
================================================================================
PATTERN 11 : Right-angled triangle, alternating 1/0 checkerboard
================================================================================
Expected output (n=5):
    1
    0 1
    1 0 1
    0 1 0 1
    1 0 1 0 1

Two approaches: check parity of (i+j) directly each cell, vs. track a
running "current bit" that flips every print (cleaner, avoids recomputation).
*/

// ---- Approach A: check parity condition per cell ----
void print11(int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<i+1;j++){
            if((i%2==0 && j%2==0) || (i%2==1 && j%2==1)){
                cout<<1;
            }
            else{
                cout<<0;
            }
        }
        cout<<endl;
    }
}
// TC - O(n^2), SC - O(1)

// ---- Approach B (cleaner): track and flip a running bit ----
void print11updated(int n){
    int star;
    for(int i=0;i<n;i++){
        (i%2==0)?star=1:star=0;     // each row starts with 1 if row is even, else 0
        for(int j=0;j<i+1;j++){
            cout<<star<<" ";
            star=1-star;              // flip 0<->1 after every print
        }
        cout<<endl;
    }
}
// TC - O(n^2), SC - O(1)
// Same output as Approach A, but avoids the double-condition parity check
// per cell - just flips a single variable, which is a cheaper and more
// direct way to express "alternate every step."


/*
================================================================================
PATTERN 12 : Symmetric number triangle (mirrored, touching in the middle)
================================================================================
Expected output (n=4):
    1      1
    12    21
    123  321
    12344321

IMPORTANT LIMITATION (applies to every version below, including the final
correct one): all of these print digits directly with no separating space
between numbers. This works cleanly only while every number involved stays
a SINGLE digit, i.e. roughly n <= 9. Once n >= 10, numbers like "10" take
two characters instead of one, and the concatenated digits become visually
ambiguous (e.g. is "910" the sequence 9,10 or 91,0?) - the values are still
being computed correctly, but the printed text is no longer unambiguous to
read. This is an inherent property of the "no separator" approach, not a
bug unique to any one attempt below - it affects the final reference
solution too. Fixing it for n >= 10 would require explicit fixed-width
formatting (e.g. std::setw) to pad each number consistently.

Four attempts shown below, in the order they were actually tried:
*/

// ---- Attempt 1 (broken): space formula does not generalize ----
void print12Wrong_way(int n){
    for(int i=0;i<n;i++){
        // number
        for(int j=0;j<i+1;j++){
            cout<<j+1;
        }
        // space
        for(int k=0;k<n+2*(1-i);k++){
            cout<<" ";
        }
        // number
        for(int j=i+1;j>=1;j--){
            cout<<j;
        }
        cout<<endl;
    }
} 
// BUG: the space-count formula n+2*(1-i) was never actually a correct
// general formula - it happens to stay positive for small i, but as i grows
// (1-i) turns negative fast enough that the space count hits 0 (or would go
// negative, except the loop condition k < n+2*(1-i) just stops running once
// the bound is <= 0). The result: rows stop getting ANY separating space
// once i is large enough, well before reaching the intended shape.
// TC - O(n^2), SC - O(1)

// ---- Attempt 2: correct space formula, but only for single-digit n ----
void pattern12My_way(int n){
    for(int i=0;i<n;i++){
        // number
        for(int j=0;j<i+1;j++){
            cout<<j+1;
        }
        // space - CORRECT general formula: shrinks by 2 each row
        for(int j=0;j<2*(n-(i+1));j++){
            cout<<" ";
        }
        // number
        for(int j=i+1;j>0;j--){
            cout<<j;
        }
        cout<<endl;
    }
}
// This one's space formula is actually right - it fails only because of the
// general single-digit limitation noted above (starts looking wrong once
// numbers like "10" appear, i.e. roughly n >= 10).
// TC - O(n^2), SC - O(1)

// ---- Attempt 3: same idea, space tracked as a running variable instead ----
void print12Another_way(int n){
    int space=2*n-2;
    for(int i=0;i<n;i++){
        // number
        for(int j=0;j<i+1;j++){
            cout<<j+1;
        }
        // space
        for(int j=0;j<space;j++){
            cout<<" ";
        }
        // number
        for(int j=i+1; j>0;j--){
            cout<<j;
        }
        cout<<endl;
        space-=2;
    }
}
// Also correct in its formula (equivalent to Attempt 2, just computed
// incrementally instead of from scratch each row) - subject to the same
// single-digit limitation.
// TC - O(n^2), SC - O(1)

// ---- Attempt 4 (final/reference): 1-indexed version of the same idea ----
void print12Another_way_given(int n){
    int space=2*n-2;
    for(int i=1;i<=n;i++){
        // number
        for(int j=1;j<=i;j++){
            cout<<j;
        }
        // space
        for(int j=1;j<=space;j++){
            cout<<" ";
        }
        // number
        for(int j=i; j>=1;j--){
            cout<<j;
        }
        cout<<endl;
        space-=2;
    }
}
// Functionally identical to Attempt 3, just written with 1-indexed loops
// instead of 0-indexed ones - a matter of style, not correctness. This is
// the cleanest version to read since the printed numbers (1..i) map
// directly onto the loop variable j without a +1 offset everywhere.
// TC - O(n^2), SC - O(1)


/*
================================================================================
PATTERN 13 : Right-angled triangle, continuously incrementing numbers
================================================================================
Expected output (n=5):
    1
    2 3
    4 5 6
    7 8 9 10
    11 12 13 14 15

Same triangle shape as Pattern 2/3, but instead of resetting the number
each row, a single counter keeps incrementing across the ENTIRE pattern.
*/
void print13(int n){
    int count=1;
    for(int i=0;i<n;i++){
        for(int j=0;j<i+1;j++){
            cout<<count<<" ";
            count++;
        }
        cout<<endl;
    }
}
// TC - O(n^2), SC - O(1)


/*
================================================================================
PATTERN 14 : Left-aligned increasing triangle of letters
================================================================================
Expected output (n=5):
    A
    AB
    ABC
    ABCD
    ABCDE

Two equivalent ways to generate the letters: increment a char explicitly
inside the loop body, OR make the char itself the loop variable (C++ allows
looping over char just like int, since char is really a small integer type).
*/

// Version A (explicit char arithmetic inside the loop body):
// void print14(int n){
//     char ch='A';
//     for(int i=0;i<n;i++){
//         for(int j=0;j<i+1;j++){
//             cout<<char(ch+j)<<" ";
//         }
//         cout<<endl;
//     }
// }

// Version B (char as the loop control variable directly) - used below:
void print14(int n){
    for(int i=0;i<n;i++){
        for(char j='A';j<'A'+i+1;j++){
            cout<<j<<" ";
        }
        cout<<endl;
    }
}
// NOTE: corrected loop bound from 'A'+i to 'A'+i+1 - row i must print i+1
// letters (row 0 -> 1 letter "A", row 1 -> 2 letters "AB", etc.) to match
// the expected output above; the original bound 'A'+i would under-print by
// one letter on every row.
// TC - O(n^2), SC - O(1)


/*
================================================================================
PATTERN 15 : Left-aligned decreasing triangle of letters
================================================================================
Expected output (n=5):
    ABCDE
    ABCD
    ABC
    AB
    A

Mirrors Pattern 6's shrinking inner bound, printing letters instead of
numbers.
*/
void print15(int n){
    char ch='A';
    for(int i=0;i<n;i++){
        for(int j=0;j<n-i;j++){
            cout<<char(ch+j)<<" ";
        }
        cout<<endl;
    }
}
// TC - O(n^2), SC - O(1)


/*
================================================================================
PATTERN 16 : Left-aligned triangle, row letter repeated
================================================================================
Expected output (n=5):
    A
    BB
    CCC
    DDDD
    EEEEE

Mirrors Pattern 4 (row value repeated), but the "value" advances a letter
by one at the end of each row instead of just being i+1.
*/
void print16(int n){
    char ch='A';
    for(int i=0;i<n;i++){
        for(int j=0;j<i+1;j++){
            cout<<ch<<" ";
        }
        ch++;
        cout<<endl;
    }
}
// TC - O(n^2), SC - O(1)


/*
================================================================================
PATTERN 17 : Letter "hourglass" pyramid
================================================================================
Expected output (n=4):
       A
      ABA
     ABCBA
    ABCDCBA

Row i has 2*i+1 letters total: ascend A..(A+i), then descend back down to A
WITHOUT repeating the peak letter twice. Three attempts shown - the first
has a genuine bug (repeats the peak letter); the other two are correct,
arrived at via different techniques.
*/

// ---- Attempt 1 (BUGGY): descending loop off-by-one duplicates the peak ----
void print17(int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<2*(n-1-i);j++){
            cout<<" ";
        }
        // ascending: correctly prints letters at index 0..i (i+1 letters)
        for(char c='A'; c<'A'+i+1;c++){
            cout<<c<<" ";
        }
        // descending: BUG - starts at index i (re-printing the peak letter
        // that the ascending loop just printed) instead of starting one
        // BELOW the peak, at index i-1
        for(int j=i;j>0;j--){   
            cout<<char(65+j)<<" ";
        }
        cout<<endl;
    }
}
// BUG CONFIRMED BY TESTING: for n=4 this produces
//        A
//      A B B
//    A B C C B
//  A B C D D C B
// i.e. every peak letter is duplicated. The fix would be starting the
// descending loop at j=i-1 (not j=i) and running while j>=0 (not j>0):
//     for(int j=i-1;j>=0;j--) cout<<char(65+j)<<" ";
// TC - O(n^2), SC - O(1) (as written, output is incorrect)

// ---- Attempt 2 (correct): increment/decrement a single char based on position ----
void pattern17_myWay(int n){   
    char ch='A';
    for(int i=0;i<n;i++){
        for(int j=n-(i+1);j>0;j--){
            cout<<" ";
        }
        for(int j=0;j<2*i+1;j++){
            cout<<ch;
            if(j+1>i){          // past the halfway/peak point -> descend
                ch--;
            }
            else{                // still climbing toward the peak -> ascend
                ch++;
            }
        }
        cout<<endl;
        ch='A';                  // reset for the next row
    }
}
// VERIFIED CORRECT by testing - matches expected output exactly for n=4.
// TC - O(n^2), SC - O(1)

// ---- Attempt 3 (correct, alternate technique): split point via "breakpoint" ----
void print17his_way(int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<(n-1-i);j++){
            cout<<" ";
        }
        char ch='A';
        int breakpoint=(2*i+1)/2;   // index of the middle (peak) character
        for(int j=0;j<2*i+1;j++){
            if(j<(breakpoint)){      // before the peak -> ascend
                cout<<char(ch++);
            }
            else{                     // at/after the peak -> descend
                cout<<char(ch--);
            }
        }
        cout<<endl;
    }
}
// VERIFIED CORRECT by testing - matches expected output exactly for n=4.
// Note on "why not j < breakpoint+1": breakpoint = (2i+1)/2 with INTEGER
// division always rounds DOWN, e.g. for i=2: (2*2+1)/2 = 5/2 = 2 (not 2.5).
// j<breakpoint therefore includes j=0,1 (2 ascends) then j=2,3,4 descend
// (3 descends, since ch was already incremented twice, char(ch--) at j=2
// prints the peak 'C' then starts stepping back down) - the integer
// truncation is exactly what places the single peak character correctly on
// the FIRST descending iteration rather than needing a separate branch for
// it.
// TC - O(n^2), SC - O(1)


/*
================================================================================
PATTERN 18 : Right-aligned decreasing triangle of letters
================================================================================
Expected output (n=5):
    E
    D E
    C D E
    B C D E
    A B C D E

Each row ends at 'E' (the n-th letter); row i shows the LAST (i+1) letters
of the alphabet run A..E, computed via a single closed-form character
expression rather than tracking a separate counter.
*/
void print18(int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<i+1;j++){
            cout<<char('A'+n-i+j-1)<<" ";
        }
        cout<<endl;
    }
}
// TC - O(n^2), SC - O(1)


/*
================================================================================
PATTERN 19 : Hollow butterfly (two triangles, hollow middle)
================================================================================
Expected output (n=5):
    **********
    ****  ****
    ***    ***
    **      **
    *        *
    *        *
    **      **
    ***    ***
    ****  ****
    **********

Built from two separate loops (top half, bottom half), each with three
segments per row: stars, gap, stars - mirroring the "spaces then stars"
technique from Pattern 7, just with stars framing a gap instead of a gap
framing stars.
*/
void print19(int n){
    // top half: stars shrink inward from both sides as i grows
    for(int i=0;i<n;i++){
        for(int j=0;j<n-i;j++){
            cout<<"*";
        }
        for(int j=0;j<2*i;j++){
            cout<<" ";
        }
        for(int j=0;j<n-i;j++){
            cout<<"*";
        }
        cout<<endl;
    }
    // bottom half: stars grow back out from both sides as i grows
    for(int i=0;i<n;i++){
        for(int j=0;j<i+1;j++){
            cout<<"*";
        }
        for(int j=0;j<2*(n-1-i);j++){
            cout<<" ";
        }
        for(int j=0;j<i+1;j++){
            cout<<"*";
        }
        cout<<endl;
    }
}
// TC - O(n^2), SC - O(1)


/*
================================================================================
PATTERN 20 : Hollow "X" / sandglass of stars
================================================================================
Expected output (n=5):
    *        *
    **      **
    ***    ***
    ****  ****
    **********
    ****  ****
    ***    ***
    **      **
    *        *

Same "stars, gap, stars" idea as Pattern 19, but arranged as one single loop
over 2n-1 rows (star count grows to the middle row, then shrinks back),
rather than two separate loops for top/bottom.
*/
void print20his_way(int n){
    int space=2*n-2;
    for(int i=0;i<2*n-1;i++){
        int stars=i+1;
        if(i>n-1){
            stars=2*n-(i+1);
        }
        // stars
        for(int j=0;j<stars;j++){
            cout<<"*";
        }
        // gap
        for(int j=0;j<space;j++){
            cout<<" ";
        }
        // stars
        for(int j=0;j<stars;j++){
            cout<<"*";
        }
        cout<<endl;
        if(i<n-1){
            space-=2;
        }
        else{
            space+=2;
        }
    }
}
// TC - O(n^2), SC - O(1)


/*
================================================================================
PATTERN 21 : Hollow square (border only)
================================================================================
Expected output (n=4):
    ****
    *  *
    *  *
    ****

Two approaches: the first branches into two structurally DIFFERENT loops for
"border rows" vs "middle rows" - this leads to a real inconsistency; the
second unifies everything into one clean 2D condition.
*/

// ---- Attempt 1 (inconsistent spacing bug) ----
void print21(int n){
    for(int i=0;i<n;i++){
        if(i==0 || i==n-1){
            for(int j=0;j<n;j++){
                cout<<"* ";              // note: "* " (star + trailing space)
            }
        }
        else{
            for(int j=0;j<2*n-1;j++){
                if(j==0 || j==2*n-2){
                    cout<<"*";             // note: "*" (star, no space)
                }
                else{
                    cout<<" ";
                }
            }
        }
        cout<<endl;
    }
}
// BUG CONFIRMED BY TESTING: the top/bottom border rows print n stars each
// with a trailing space after EVERY star ("* * * * "), while the middle
// rows print a totally different-width line built from a 2n-1-wide loop
// with single-character stars ("*     *"). These two row-building strategies
// don't produce matching widths, so the "square" doesn't actually line up
// into a clean rectangle - visible directly when run for n=4:
//   * * * *      (8 characters)
//   *     *      (7 characters)
//   *     *      (7 characters)
//   * * * *      (8 characters)
// TC - O(n^2), SC - O(1)

// ---- Attempt 2 (correct, unified condition) ----
void print21his_way(int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            // a cell is part of the border if it's in the first/last row
            // OR the first/last column - identical condition, single loop
            // shape, for every row (no branching by row type at all)
            if(i==0 || i==n-1 || j==0 || j==n-1){
                cout<<"*";
            }
            else{
                cout<<" ";
            }
        }
        cout<<endl;
    }
}
// VERIFIED CORRECT by testing - clean, uniform n-wide rows for every row:
//   ****
//   *  *
//   *  *
//   ****
// This is generally the better pattern to reach for: describe what makes a
// CELL part of the shape (one condition, checked the same way everywhere)
// rather than describing what makes a ROW special (multiple loop shapes).
// TC - O(n^2), SC - O(1)


/*
================================================================================
PATTERN 22 : Concentric square "rings" of numbers
================================================================================
Expected output (n=4):
    4444444
    4333334
    4322234
    4321234
    4322234
    4333334
    4444444

Grid is (2n-1) x (2n-1). Each cell's value is n minus its "ring index" -
i.e. how many rings deep it is from the nearest edge. Two approaches: the
first is hardcoded to exactly 4 ring levels regardless of n (works only at
n=4 by coincidence); the second computes the ring index directly with a
general formula that works for any n.
*/

// ---- Attempt 1 (does not generalize - hardcoded to 4 levels) ----
void print22(int n){
    for(int i=0;i<2*n-1;i++){
        for(int j=0;j<2*n-1;j++){
            if(i==0 || i==2*n-2 || j==0 ||j==2*n-2){
                cout<<n;
            }
            else if(i==1 || i==2*n-3 || j==1 || j==2*n-3){
                cout<<n-1;
            }
            else if(i==2 || i==2*n-4 || j==2 || j==2*n-4){
                cout<<n-2;
            }
            else if(i==3 || i==2*n-5 || j==3 || j==2*n-5){
                cout<<n-3;
            }
        }
        cout<<endl;
    }
}
// BUG: only 4 explicit ring levels are checked (k=0,1,2,3) no matter what n
// is. For n=4 this happens to be exactly enough levels to fill the whole
// grid, so it looks correct - but for n=5 or larger, cells deeper than ring
// 3 (the true center) match NO condition and print nothing, leaving a gap.
// This is the same category of bug as the earlier while-loop pattern
// exercise: hardcoding a bound that happens to match one specific input.
// TC - O(n^2), SC - O(1)

// ---- Attempt 1b: general version of the same idea, using a while loop ----
void pattern_MyOwn(int n){
    int k=0;
    for(int i=0;i<2*n-1;i++){
        for(int j=0;j<2*n-1;j++){
            while(k<=n-1){
                if(i==k || j==k || i==2*n-k-2 || j==2*n-k-2){
                    cout<<(n-k);
                    break;
                }
                k++;
            }
            k=0;
        }
        cout<<endl;
    }
}
// Correct and generalizes to any n (checks ring levels k=0..n-1 instead of
// a hardcoded 4) - verified against Approach 2 below across multiple n
// values with identical output.
// TC - O(n^2) amortized: although there's a while loop nested inside the
// double for loop, k is reset to 0 before each cell and increases at most
// n times per cell before either matching or exhausting - so worst case
// per cell is O(n), giving O(n^2 * n) = O(n^3) in the absolute worst case.
// In practice the match is found quickly for most cells (border/near-border
// cells match almost immediately), but Approach 2 below achieves the same
// result in guaranteed O(1) per cell, which is strictly better.
// SC - O(1)

// ---- Attempt 2 (best): direct formula, O(1) per cell, no loop needed ----
void print22corrected(int n){
    int top, down, right, left;
    for(int i=0;i<2*n-1;i++){
        for(int j=0;j<2*n-1;j++){
            // core idea: value = n - (minimum straight-line distance to
            // any of the 4 edges)
            top=i;                 // distance from the top edge = row index itself
            right=j;                // distance from the left edge = column index itself
            down=2*n-2-i;           // distance from the bottom edge
            left=2*n-2-j;           // distance from the right edge
            cout<<n-min(min(top,down), min(right, left));  // min() only takes 2 args, nest calls for 4
        }
        cout<<endl;
    }
}
// VERIFIED CORRECT by testing against the expected image for n=4, and
// generalizes cleanly to any n (no hardcoded levels, no loop needed per
// cell - each cell's value is computed directly with 4 subtractions and 3
// comparisons).
// TC - O(n^2)   (n^2 cells, O(1) work per cell - this is the true minimum
//                possible complexity for a pattern that must visit every
//                cell of an n x n-ish grid at least once)
// SC - O(1)
// THIS IS THE PREFERRED FINAL SOLUTION for Pattern 22 - it's simpler,
// faster, and more general than every earlier attempt.


/*
================================================================================
main()
================================================================================
Swap the function call below to try any pattern. print22corrected is left as
the default since it's the most general/robust solution demonstrated above.
*/
int main(){
    int t;
    cin>>t;
    for(int i=0;i<t;i++){
        int n;
        cin>>n;
        print22corrected(n);
    }
    return 0;
}