#include<bits/stdc++.h>
using namespace std;

/*
================================================================================
                            HASHING - COMPLETE NOTES
================================================================================
CORE IDEA: hashing is PRE-STORING something once, then FETCHING it instantly
whenever it's needed - trading extra memory for a massive speed gain.

The classic problem: given an array and several queries, report the frequency
of a given element. Answering each query by re-scanning the array is wasteful,
because the array never changes. Compute all frequencies ONCE up front, then
every query becomes an O(1) lookup.

TABLE OF CONTENTS
-----------------
  PART 1  : The brute force approach (and why it fails)
  PART 2  : Array hashing (number hashing)
  PART 3  : Memory rules - stack vs global vs heap
  PART 4  : Compile-time vs runtime sizing (and the VLA trap)
  PART 5  : Character hashing
  PART 6  : map and unordered_map hashing
  PART 7  : How hash tables work internally (collisions, chaining)
  PART 8  : Choosing between array / map / unordered_map
  PART 9  : Practical problems
  PART 10 : Common mistakes checklist

================================================================================
PART 1 : THE BRUTE FORCE APPROACH (AND WHY IT FAILS)
================================================================================
For each query, scan the entire array and count matches.
*/

int freqCountBrute(int arr[], int number, int n){
    int count = 0;
    for(int i = 0; i < n; i++){
        if(arr[i] == number){
            count++;
        }
    }
    return count;
}
/*
TC - O(q * n)   where q = number of queries, n = array size
SC - O(1)

WHY THIS IS UNUSABLE AT SCALE:
With n = 10^5 elements and q = 10^5 queries, that's 10^10 operations. At the
standard estimate of ~10^8 operations per second, that's roughly 100 SECONDS -
far beyond any typical 1-2 second time limit.

The waste is obvious once you see it: the array never changes between queries,
yet we recount from scratch every single time. Hashing removes that redundancy.
*/


/*
================================================================================
PART 2 : ARRAY HASHING (NUMBER HASHING)
================================================================================
THE THREE STEPS:
    1. PRE-ALLOCATE a hash array, filled with 0
    2. PRE-COMPUTE  by looping the input once, using each VALUE as an INDEX
                    into the hash array and incrementing that slot
    3. FETCH        answer any query in O(1) by reading hash[query]

The trick is using the value itself as the index. That's what makes lookup O(1).
*/

// ---- BROKEN VERSION - sized by n instead of by the maximum VALUE ----
vector<int> hashingBroken(int arr[], int n){
    vector<int> hsh(n + 1);            // size based on COUNT of elements
    for(int i = 0; i < n; i++){
        hsh[arr[i]]++;                  // but indexed by VALUE of elements
    }
    return hsh;
}
/*
***** THIS IS A REAL BUG, NOT JUST A LIMITATION *****
The hash array is sized n+1, but it is indexed by the element VALUES, which
have nothing to do with n.

    arr = {5, 100, 2},  n = 3  ->  hash has size 4, valid indices 0..3
    hash[100]++  writes far outside the vector -> UNDEFINED BEHAVIOR

VERIFIED BY TESTING: this silently corrupts memory rather than erroring. It
only appears to work when every element happens to be <= n.

The size must be based on the MAXIMUM ELEMENT, not the element count.
*/

// ---- CORRECT VERSION - sized by the maximum value ----
vector<int> hashArray(vector<int>& arr){
    int maxi = *max_element(arr.begin(), arr.end());
    vector<int> hsh(maxi + 1, 0);       // +1 because indices run 0..maxi

    for(int v : arr){
        hsh[v]++;
    }
    return hsh;
}
/*
TC - O(n) to build, O(1) per query
SC - O(max_element)   <-- note: NOT O(n)

THE TRADE-OFF: memory scales with the LARGEST VALUE, not the element count.
An array of just 3 elements {1, 2, 1000000000} needs a hash array of a billion
slots - completely impractical. This is the fundamental limitation of array
hashing, and exactly why map/unordered_map exist (Part 6).

--------------------------------------------------------------------------------
LIMITATION: NEGATIVE NUMBERS
--------------------------------------------------------------------------------
Array indices cannot be negative, so array hashing breaks on negative values.
hash[-5] is undefined behavior.

WORKAROUND - the OFFSET technique. Shift every value up by the minimum:

    int mini = *min_element(arr.begin(), arr.end());
    int maxi = *max_element(arr.begin(), arr.end());
    vector<int> hsh(maxi - mini + 1, 0);
    for(int v : arr) hsh[v - mini]++;      // index 0 now represents `mini`
    // to query x:  hsh[x - mini]

This works, but the array must span (max - min + 1) slots, so a wide range is
still a problem. For sparse or very wide ranges, use a map instead.

--------------------------------------------------------------------------------
RETURNING ARRAYS FROM FUNCTIONS
--------------------------------------------------------------------------------
NEVER return a pointer or reference to a LOCAL C-style array:

    int* bad(){
        int arr[10];
        return arr;        // DANGLING POINTER - arr dies when the function ends
    }

The array lives on the stack and is destroyed the moment the function returns,
so the caller receives a pointer to freed memory - undefined behavior.

CORRECT OPTIONS:
    1. Return a vector (preferred - it manages its own heap memory, RAII)
    2. Pass the destination array in as a parameter and fill it
    3. Allocate on the heap with new (then you must remember to delete)
*/


/*
================================================================================
PART 3 : MEMORY RULES - STACK vs GLOBAL vs HEAP
================================================================================

--------------------------------------------------------------------------------
1. THE STACK (local variables, inside functions)
--------------------------------------------------------------------------------
    Size limit   : SMALL. ~1 MB on Windows, ~8 MB on Linux/macOS.
                   VERIFIED on this machine: ulimit -s reported 8192 KB = 8 MB.
    Lifecycle    : Automatic. Allocated on function entry, destroyed on exit (LIFO).
    Initial value: GARBAGE. Space is reserved but not cleared.
    Safety       : Always initialize manually - int arr[100] = {};
                   Never return a pointer to a local stack array.

--------------------------------------------------------------------------------
2. GLOBAL / STATIC MEMORY (declared outside all functions)
--------------------------------------------------------------------------------
    Size limit   : LARGE. Governed by the OS and available RAM.
    Lifecycle    : Exists for the entire program run.
    Initial value: GUARANTEED ZERO. The loader clears this block at startup, so
                   no manual initialization is needed.
    Capacity     : Comfortably handles ~10^7 elements in competitive programming.
                   VERIFIED: int global_arr[10000000] (40 MB) allocated fine and
                   read back as 0.

--------------------------------------------------------------------------------
3. RAW HEAP (new / malloc)
--------------------------------------------------------------------------------
    Size limit   : MASSIVE. Bounded by physical RAM.
    Lifecycle    : MANUAL. Must be freed with delete / free or you leak memory.
    Initial value: GARBAGE by default.
    Syntax:
        int* bad_heap  = new int[5];      // garbage values
        int* good_heap = new int[5]();    // () forces zero-initialization
        delete[] good_heap;                // required, or it leaks

--------------------------------------------------------------------------------
4. SMART HEAP OBJECTS (std::vector - the recommended default)
--------------------------------------------------------------------------------
    Architecture : Hybrid. The small management object (pointer + size +
                   capacity) lives on the STACK; the actual elements live on
                   the HEAP.
    Lifecycle    : RAII - automatically frees its heap memory when the vector
                   goes out of scope. No manual cleanup, no leaks.
    Initial value: GUARANTEED ZERO when a size is given.
    Syntax       : vector<int> hsh(100);      // 100 zeros, completely safe

--------------------------------------------------------------------------------
INITIALIZATION SUMMARY MATRIX
--------------------------------------------------------------------------------
  Declaration                        | Memory Area   | Default State
  -----------------------------------|---------------|-------------------
  int global_arr[10];                | Global/Static | Guaranteed ZERO
  int main(){ int local_arr[10]; }   | Stack         | GARBAGE
  int* p = new int[10];              | Raw Heap      | GARBAGE
  int* p = new int[10]();            | Raw Heap      | Guaranteed ZERO
  vector<int> v(10);                 | Managed Heap  | Guaranteed ZERO

PRACTICAL SIZE LIMITS FOR COMPETITIVE PROGRAMMING (approximate, platform-dependent):
  int array  : ~10^6 inside main (4 MB)  |  ~10^7 globally (40 MB)
  bool array : ~10^7 inside main (10 MB) |  ~10^8 globally (100 MB)

  Note these are rules of thumb. 10^6 ints = 4 MB fits within Linux's 8 MB
  stack but would already blow a 1 MB Windows stack. When in doubt, declare
  large arrays GLOBALLY or use a vector (heap) - both avoid the stack entirely.
*/


/*
================================================================================
PART 4 : COMPILE-TIME vs RUNTIME SIZING (AND THE VLA TRAP)
================================================================================

--------------------------------------------------------------------------------
1. GLOBAL ARRAYS - size must be a COMPILE-TIME CONSTANT
--------------------------------------------------------------------------------
    const int SIZE = 1e7;
    int arr[SIZE];              // LEGAL - fixed constant

    int n; cin >> n;
    int arr[n];                 // ILLEGAL - n isn't known at compile time

--------------------------------------------------------------------------------
2. STACK ARRAYS - size must ALSO be a compile-time constant in standard C++
--------------------------------------------------------------------------------
The compiler must compute each function's exact stack frame size while
compiling, so it cannot depend on runtime input.

    int n; cin >> n;
    int arr[n];                 // NOT standard C++

***** IMPORTANT: THE VLA TRAP *****
GCC and Clang ACCEPT the above as a non-standard extension called a
VARIABLE LENGTH ARRAY (VLA), inherited from C. So it compiles and appears to
work - which is exactly what makes it dangerous.

VERIFIED BY TESTING:
    g++ file.cpp                     -> compiles silently, runs
    g++ -pedantic-errors file.cpp    -> "error: ISO C++ forbids variable
                                          length array"

WHY IT MATTERS:
    - It is NOT portable - MSVC rejects it outright.
    - It goes on the STACK, so a large n (say 10^7) is an instant stack
      overflow crash, with no warning and no way to check for failure.

The original version of these notes correctly stated VLAs are illegal, but the
code in main() used `char arr[n];` with n read from cin - the notes and the
code contradicted each other. Corrected in Part 9.

--------------------------------------------------------------------------------
3. HEAP (vector or new) - size CAN be a runtime variable
--------------------------------------------------------------------------------
This is precisely what the heap is for. Only a small fixed-size pointer
structure sits on the stack; the actual memory is requested at runtime.

    int n; cin >> n;            // user enters 5,000,000
    vector<int> v(n);           // LEGAL, SAFE, and zero-initialized

--------------------------------------------------------------------------------
COMPILE-TIME vs RUNTIME MATRIX
--------------------------------------------------------------------------------
  Structure Type       | Memory Zone | Size Determined At | Runtime size OK?
  ---------------------|-------------|--------------------|------------------
  Global array         | Static      | Compile-time       | NO (must be const)
  C-style local array  | Stack       | Compile-time       | NO (VLA = non-std)
  new int[n]           | Heap        | Runtime            | YES
  std::vector          | Heap        | Runtime            | YES (recommended)

RULE: if the size comes from input, use vector.
*/


/*
================================================================================
PART 5 : CHARACTER HASHING
================================================================================
Same idea as number hashing, but the "value" is a character. Characters are
just small integers underneath (their ASCII codes), so they can index an array
directly.

SIZING THE HASH ARRAY:
    Only lowercase letters guaranteed  -> size 26, index with  ch - 'a'
    Only uppercase letters guaranteed  -> size 26, index with  ch - 'A'
    Mixed case only                    -> size 52, or just use 256
    Anything at all (digits, symbols)  -> size 256

THE ASCII OFFSET TRICK:
    'a' is 97, 'b' is 98, ... 'z' is 122.
    Subtracting 'a' maps them to 0..25:
        hash['f' - 'a']  =  hash[102 - 97]  =  hash[5]
*/

// ---- Lowercase-only hashing (size 26) ----
vector<int> characterHashLower(char arr[], int n){
    vector<int> hsh(26, 0);
    for(int i = 0; i < n; i++){
        hsh[arr[i] - 'a']++;
    }
    return hsh;
}
// TC - O(n) build, O(1) query.  SC - O(1), since 26 is a fixed constant.
// WARNING: any character outside 'a'..'z' gives an out-of-range index.
// 'A' - 'a' = -32 -> negative index -> undefined behavior.

// ---- Full-ASCII hashing (size 256) ----
vector<int> characterHashFull(char arr[], int n){
    vector<int> hsh(256, 0);            // FIX: was 255
    for(int i = 0; i < n; i++){
        hsh[(unsigned char)arr[i]]++;    // FIX: cast to unsigned char
    }
    return hsh;
}

void characterHash(vector<char>& arr){
    unordered_map<char, int> mp;
    for(auto v:arr){
        mp[v]++;
    }
    for(auto v:mp){
        cout<<v.first<<" : "<<v.second<<endl;
    }
}

void characterHash2(vector<char>& arr){
    int maxi=*(max_element(arr.begin(), arr.end()));
    vector<int> hash_arr(maxi+1, 0);
    for(int v:arr){
        hash_arr[v]++;
    }
    for(int i=0;i<hash_arr.size();i++){
        if(hash_arr[i]>0)
            cout<<char(i)<<" : "<<hash_arr[i]<<endl;
    }
}
/*
TWO BUGS FIXED HERE, both verified by testing:

BUG 1 - SIZE OFF BY ONE. The original used vector<int> hash(255).
    ASCII values run 0..255, which is 256 distinct values.
    A vector of size 255 has valid indices 0..254 ONLY.
    Character 255 would write to index 255 - out of bounds.
    The size must be 256.

BUG 2 - SIGNED CHAR GIVING NEGATIVE INDICES. The original used hash[arr[i]].
    VERIFIED: on this platform plain `char` is SIGNED, with range -128..127.
    So (char)200 has the integer value -56, and hash[-56] is a negative index -
    undefined behavior, silently corrupting memory before the array.

    This only bites on characters above 127 (extended ASCII, or bytes from
    UTF-8 text), which is why it can hide for a long time in testing with
    plain English input.

    THE FIX: cast to unsigned char, which maps 0..255 correctly.
*/


/*
================================================================================
PART 6 : map AND unordered_map HASHING
================================================================================
Array hashing breaks down when values are huge, sparse, or negative - you can't
allocate an array of a billion slots for three elements.

map and unordered_map solve this: they store ONLY the keys that actually
appear, so memory scales with the NUMBER OF DISTINCT ELEMENTS, not the value
range.
*/

map<int, int> freqUsingMap(int arr[], int n){
    map<int, int> freq;
    for(int i = 0; i < n; i++){
        freq[arr[i]]++;
    }
    return freq;
}
/*
WHY NO "does this key exist?" CHECK IS NEEDED HERE:
map's operator[] returns a REFERENCE to the value for that key. If the key is
absent, it CREATES it first with the type's default value (0 for int) and
returns a reference to that. So freq[x]++ on a brand-new key does 0 -> 1
automatically. (In Python you'd need defaultdict or an explicit check.)

***** BUT THIS SAME BEHAVIOR IS A COMMON BUG SOURCE *****
operator[] INSERTS on every access, including when you only meant to READ:

    cout << freq[99];        // if 99 was absent, this ADDS key 99 with value 0
                              // and the map's size grows

That silently pollutes your map. For a pure lookup that must not insert, use:
    freq.count(key)              // returns 0 or 1, never inserts
    freq.find(key) != freq.end() // never inserts
    freq.at(key)                  // throws if missing, never inserts

Use [] when you WANT insert-or-update (like the counting loop above).
Use count/find/at when you only want to look.

TC - O(n log n) to build (n insertions, each O(log n)), O(log n) per query
SC - O(number of distinct elements)
*/

unordered_map<int, int> freqUsingUnorderedMap(int arr[], int n){
    unordered_map<int, int> freq;
    for(int i = 0; i < n; i++){
        freq[arr[i]]++;
    }
    return freq;
}
// TC - O(n) average to build, O(1) average per query
//      O(n) per operation in the WORST case (heavy collisions - see Part 7)
// SC - O(number of distinct elements)

unordered_map<char, int> characterHashMap(char arr[], int n){
    unordered_map<char, int> mpp;
    for(int i = 0; i < n; i++){
        mpp[arr[i]]++;
    }
    return mpp;
}


/*
================================================================================
PART 7 : HOW HASH TABLES WORK INTERNALLY
================================================================================
map is a RED-BLACK TREE (a self-balancing BST). Balance guarantees the height
stays ~log n, so every operation walks one root-to-leaf path: O(log n),
GUARANTEED, regardless of input.

unordered_map is a HASH TABLE. A hash function converts each key directly into
a bucket index, so you jump straight to the right bucket with no comparisons:
O(1) - but only ON AVERAGE.

--------------------------------------------------------------------------------
COMMON HASH FUNCTION FAMILIES
--------------------------------------------------------------------------------
    1. Division hashing    - index = key % table_size    (most common)
    2. Multiplication hashing
    3. Mid-square hashing

--------------------------------------------------------------------------------
DIVISION HASHING WORKED EXAMPLE
--------------------------------------------------------------------------------
The whole point: when values are huge, you cannot size an array by the maximum
value. So you fold them into a small fixed table with  key % table_size.

    Table size 10, hash function x % 10
    Input: 2, 5, 16, 28, 139, 38, 48, 28, 18

    Bucket 0 :
    Bucket 1 :
    Bucket 2 : 2
    Bucket 3 :
    Bucket 4 :
    Bucket 5 : 5
    Bucket 6 : 16
    Bucket 7 :
    Bucket 8 : 18 -> 28 -> 28 -> 38 -> 48      <-- COLLISION CHAIN
    Bucket 9 : 139

--------------------------------------------------------------------------------
COLLISIONS AND CHAINING
--------------------------------------------------------------------------------
A COLLISION is when two different keys hash to the SAME bucket (18, 28, 38, 48
all end in 8, so all give 8 under x % 10).

CHAINING resolves this: the bucket holds a linked list of every entry that
landed there. Searching that bucket means walking its chain - O(k) where k is
the chain length.

  - GOOD hash, well-distributed keys : chains stay ~1 element  -> O(1)
  - WORST CASE, all keys collide     : one chain of length n   -> O(n)

That worst case is exactly why unordered_map is "O(1) AVERAGE", not guaranteed
O(1), while map is O(log n) ALWAYS.

--------------------------------------------------------------------------------
LOAD FACTOR AND REHASHING
--------------------------------------------------------------------------------
LOAD FACTOR = (number of elements) / (number of buckets), i.e. the average
chain length. When it exceeds a threshold (default 1.0), the table REHASHES:
allocates more buckets and redistributes every element. That single operation
costs O(n), which is why insertion is technically "amortized O(1)".

If you know roughly how many elements you'll insert, mp.reserve(n) pre-allocates
the buckets and avoids all intermediate rehashing.

--------------------------------------------------------------------------------
ANTI-HASH TESTS (important in competitive programming)
--------------------------------------------------------------------------------
GCC's std::hash for integers is essentially the identity function, and the
bucket counts are known primes. That means an adversary CAN construct an input
where every key collides, deliberately forcing your O(1) solution to O(n) and
causing a TLE. Some judges (notably Codeforces) have such tests.

DEFENSES:
    - Use map instead (O(log n) guaranteed, immune to this)
    - Call mp.reserve(...) and set a custom max_load_factor
    - Supply a custom hash that mixes in a random/time-based constant

--------------------------------------------------------------------------------
KEY TYPE RESTRICTIONS
--------------------------------------------------------------------------------
map keys need a < comparison. Built-in types, string, and pair all have one,
so map<pair<int,int>, int> works fine.

unordered_map keys need a std::hash specialization. One exists for built-in
types and string, but NOT for pair - so unordered_map<pair<int,int>, int> does
NOT compile.

    OPTION 1 (simplest): use map<pair<int,int>, int> instead.
    OPTION 2: encode the pair into a single integer:
                  long long key = (long long)a * 1000000 + b;
    OPTION 3: supply a custom hash functor:

        struct PairHash {
            size_t operator()(const pair<int,int>& p) const {
                return hash<long long>()((long long)p.first * 1000003 + p.second);
            }
        };
        unordered_map<pair<int,int>, int, PairHash> mp;
*/


/*
================================================================================
PART 8 : CHOOSING BETWEEN ARRAY / map / unordered_map
================================================================================

  METHOD          | BUILD      | QUERY     | SPACE            | WORKS WITH
  ----------------|------------|-----------|------------------|------------------
  Array hashing   | O(n)       | O(1)      | O(max_value)     | small non-negative
                  |            |           |                  | integers only
  map             | O(n log n) | O(log n)  | O(distinct)      | anything orderable,
                  |            |           |                  | keeps keys SORTED
  unordered_map   | O(n) avg   | O(1) avg  | O(distinct)      | anything hashable,
                  | O(n^2)worst| O(n) worst|                  | NO ordering

DECISION GUIDE:
  - Values are small non-negative ints (say <= 10^7)?  -> ARRAY. Fastest by far,
    no hashing overhead, perfect cache behavior.
  - Values huge, sparse, negative, or non-integer?     -> map / unordered_map
  - Need keys in SORTED order, or lower_bound/upper_bound? -> map (the only one
    that provides these)
  - Need raw speed and ordering doesn't matter?        -> unordered_map
  - Worried about worst-case guarantees / anti-hash tests? -> map

DEFAULT ADVICE: prefer unordered_map over map for plain frequency counting,
since O(1) beats O(log n). Switch to map when you need ordering or a guaranteed
worst case.
*/


/*
================================================================================
PART 9 : PRACTICAL PROBLEMS
================================================================================
*/

// ---- PROBLEM: find the highest and lowest frequency characters ----
void highestLowestFrequency(const unordered_map<char,int>& mpp){
    if(mpp.empty()){
        cout << "No elements to analyse" << endl;
        return;
    }

    int maxFreq = 0;
    int minFreq = INT_MAX;              // FIX: was the magic number 999
    vector<char> maxChars, minChars;

    for(auto& v : mpp){
        // track maximum
        if(v.second > maxFreq){
            maxFreq = v.second;
            maxChars.clear();            // new record - discard previous holders
            maxChars.push_back(v.first);
        }
        else if(v.second == maxFreq){
            maxChars.push_back(v.first); // tie - add to the existing list
        }

        // track minimum
        if(v.second < minFreq){
            minFreq = v.second;
            minChars.clear();
            minChars.push_back(v.first);
        }
        else if(v.second == minFreq){
            minChars.push_back(v.first);
        }
    }

    cout << "Highest frequency = " << maxFreq
         << " (" << maxChars.size() << " character(s)): ";
    for(char c : maxChars) cout << c << " ";
    cout << endl;

    cout << "Lowest frequency = " << minFreq
         << " (" << minChars.size() << " character(s)): ";
    for(char c : minChars) cout << c << " ";
    cout << endl;
}
/*
FIX EXPLAINED - the original initialized  int minElem = 999;

VERIFIED BY TESTING with frequencies {x:1500, y:2000}:
    computed min = 999, characters found = 0     <-- COMPLETELY BROKEN

Because every real frequency was above 999, the `v.second < minFreq` branch
never fired, minFreq kept its placeholder value, and minChars stayed empty.

Any hard-coded "large enough" sentinel eventually meets input that exceeds it.
Use INT_MAX (from <climits>) for a minimum-tracker and 0 or INT_MIN for a
maximum-tracker. Alternative that avoids sentinels entirely: seed both from
the first element, then loop over the rest.

TC - O(d) where d = number of distinct characters.  SC - O(d) worst case.
*/


// ---- PROBLEM: check whether two strings are anagrams ----
bool areAnagrams(const string& a, const string& b){
    if(a.size() != b.size()) return false;    // quick reject

    vector<int> hsh(256, 0);
    for(char c : a) hsh[(unsigned char)c]++;   // count characters of a
    for(char c : b) hsh[(unsigned char)c]--;   // uncount characters of b

    for(int count : hsh){
        if(count != 0) return false;            // any imbalance -> not anagrams
    }
    return true;
}
// TC - O(n), SC - O(1) (256 is a fixed constant)
// A neat use of hashing: one pass up, one pass down, everything should cancel.


// ---- PROBLEM: find the first non-repeating character ----
int firstNonRepeating(const string& s){
    vector<int> hsh(256, 0);
    for(char c : s) hsh[(unsigned char)c]++;

    for(int i = 0; i < (int)s.size(); i++){
        if(hsh[(unsigned char)s[i]] == 1) return i;   // first with count 1
    }
    return -1;                                          // none found
}
// TC - O(n), SC - O(1)
// The two-pass pattern (build the hash, then scan in original order) is very
// common - the second pass preserves ordering that the hash itself loses.


/*
================================================================================
PART 10 : COMMON MISTAKES CHECKLIST
================================================================================
  [X] Sizing the hash array by n           -> must be sized by the MAXIMUM
      (element count) instead of max value    VALUE; otherwise out-of-bounds
  [X] Forgetting the +1                    -> indices run 0..maxi, so you need
                                               maxi+1 slots (same reason 256,
                                               not 255, for full ASCII)
  [X] Using signed char as an index        -> chars above 127 become NEGATIVE
                                               indices; cast to unsigned char
  [X] Negative values in array hashing     -> use the offset trick, or a map
  [X] Reading mp[key] for a missing key    -> operator[] INSERTS it; use
                                               count(), find(), or at() to look
  [X] `int arr[n];` with runtime n         -> VLA, non-standard C++; g++ allows
                                               it silently but it's a stack
                                               overflow waiting to happen.
                                               Use vector<int> arr(n).
  [X] Magic sentinel like minElem = 999    -> breaks as soon as real values
                                               exceed it; use INT_MAX
  [X] Returning a local C-array            -> dangling pointer; return a vector
  [X] Large arrays declared inside main    -> stack is only ~1-8 MB; declare
                                               globally or use a vector
  [X] Assuming unordered_map is always     -> O(1) is AVERAGE; collisions make
      O(1)                                    it O(n), and anti-hash tests
                                               exploit this deliberately
  [X] unordered_map<pair<int,int>, T>      -> no std::hash for pair; use map or
                                               a custom hash functor
================================================================================
*/


int main(){
    int n;
    cin >> n;

    // FIX: the original used `char arr[n];` - a non-standard VLA.
    // vector is the correct way to size from runtime input.
    vector<char> arr(n);
    for(int i = 0; i < n; i++){
        cin >> arr[i];
    }

    // Build the frequency map
    unordered_map<char, int> mpp;
    for(char c : arr){
        mpp[c]++;
    }

    cout << "Character frequencies: ";
    for(auto& v : mpp){
        cout << v.first << ":" << v.second << "  ";
    }
    cout << endl;

    highestLowestFrequency(mpp);

    return 0;
}