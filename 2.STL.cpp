#include<bits/stdc++.h>
using namespace std;

/*
================================================================================
                          C++ STL - COMPLETE NOTES
================================================================================
STL = STANDARD TEMPLATE LIBRARY.

It is a ready-made collection of containers, algorithms, iterators and function
objects. Without it you would have to hand-write a dynamic array, a linked list,
a balanced tree, a sorting routine, etc. for every project. STL gives you tested,
optimised versions you can use directly.

STL IS DIVIDED INTO 4 PARTS:
    1. Containers  - data structures that hold your data
    2. Algorithms  - operations that work ON containers (sort, find, reverse...)
    3. Iterators   - the "glue"; a generic way to point at / walk through data
    4. Functors    - function objects (greater<int>(), custom comparators...)

SKELETON:
    #include<bits/stdc++.h>
    using namespace std;
    int main(){
        return 0;
    }

TABLE OF CONTENTS
-----------------
  PART 1  : Pairs
  PART 2  : Vector
  PART 3  : List
  PART 4  : Deque
  PART 5  : Vector vs List vs Deque (internals & cache locality)
  PART 6  : Stack
  PART 7  : Queue
  PART 8  : Priority Queue
  PART 9  : Set
  PART 10 : Multiset
  PART 11 : Unordered Set
  PART 12 : Map
  PART 13 : Multimap
  PART 14 : Unordered Map
  PART 15 : Container complexity reference table
  PART 16 : Algorithms
  PART 17 : Common mistakes checklist

================================================================================
PART 1 : PAIRS
================================================================================
A pair stores exactly TWO values, which may be of different types.
Lives in <utility> (included by bits/stdc++.h).

    SYNTAX:  pair<type1, type2> name = {val1, val2};
    ACCESS:  name.first  and  name.second
*/

void explainPair(){
    pair<int, int> p = {3, 4};
    cout << p.first << " " << p.second << endl;

    p.first = 9;                        // values are modifiable after creation
    cout << p.first << " " << p.second << endl;

    // cout << p << endl;   // COMPILER ERROR - there is no operator<< for pair.
                             // You must print .first and .second separately.

    pair<int, float> p2 = {2, 3.14};     // the two types can differ
    cout << p2.second << endl;

    // NESTED PAIR - to hold more than 2 things
    pair<int, pair<int, int>> np = {2, {5, 7}};
    cout << np.second.first << " " << np.second.second << endl;

    // Array of pairs
    pair<int, char> arr[] = { {1,'A'}, {2,'B'}, {3,'C'}, {4,'D'} };
    cout << arr[2].first << ":" << arr[2].second << endl;

    // OTHER WAYS TO BUILD A PAIR (all equivalent):
    pair<int,int> a = {1, 2};            // brace init - shortest, preferred
    pair<int,int> b = make_pair(1, 2);   // helper function (older style)
    pair<int,int> c(1, 2);               // constructor syntax
    cout << a.first << b.first << c.first << endl;

    // USEFUL: tie() to unpack a pair into existing variables
    int x, y;
    tie(x, y) = a;                        // x=1, y=2
    // C++17 structured bindings - cleaner:
    auto [m, n] = a;                      // m=1, n=2
    cout << x << y << m << n << endl;
}


/*
================================================================================
PART 2 : VECTOR
================================================================================
THE PROBLEM WITH ARRAYS: `int arr[5];` is FIXED in size. If you later need 7
elements, you cannot grow it - the size is baked in at compile time.

VECTOR is a DYNAMIC ARRAY - it can grow and shrink at runtime. Use it whenever
you don't know the size upfront or it may change.

INTERNALLY: a vector stores its elements in ONE CONTIGUOUS block of memory,
exactly like a C array. It does NOT use node pointers. It keeps raw pointers to
the start and end of that flat block, plus a capacity. When it runs out of
capacity it allocates a bigger block (usually double) and copies everything over.
*/

void explainVector(){
    // ---- DECLARING ----
    vector<int> v;                     // empty vector

    // ---- INSERTING AT THE BACK ----
    v.push_back(2);
    v.emplace_back(3);
    v.emplace_back(7);
    v.emplace_back(-4);

    /* push_back vs emplace_back - a common oversimplification:
       "emplace_back is faster" is only sometimes true, and worth understanding:
         push_back(x)     : takes an already-built object, then copies/moves it in
         emplace_back(a,b): takes the CONSTRUCTOR ARGUMENTS and builds the object
                            directly in place, skipping the copy/move
       For simple types like int, they are effectively IDENTICAL - there is no
       copy to save. The difference matters for objects that are expensive to
       copy, and for the convenience shown just below with pairs. */

    // cout << v << endl;   // COMPILER ERROR - no operator<< for vector

    // ---- VECTOR OF PAIRS - where push_back/emplace_back genuinely differ ----
    vector<pair<int, int>> v2;
    v2.push_back({5, 6});               // must build the pair yourself with {}
    v2.emplace_back(7, 8);               // pass the 2 values, pair built in place

    // ---- SIZED / PRE-FILLED CONSTRUCTION ----
    vector<int> v3(5);                   // 5 elements
    /* CORRECTION: the original notes said this fills with "garbage value or 0".
       VERIFIED BY TESTING - it is ALWAYS 0, never garbage. vector VALUE-
       INITIALIZES its elements, which zero-initializes built-in types. This
       is a guarantee, unlike a raw C array `int arr[5];` which really IS
       uninitialized garbage. */
    vector<int> v4(5, 20);               // 5 elements, all set to 20
    vector<int> v5(v);                    // copy of v (deep copy, same type only)

    cout << "v3[0] = " << v3[0] << " (guaranteed 0, not garbage)" << endl;
    cout << v4[0] << " " << v5[0] << endl;

    // ---- ACCESSING ----
    cout << v[0] << " " << v.at(1) << " " << *(v.begin()) << endl;
    /* NOTE on .at() - the original said "we do not use v.at()". Worth keeping
       in mind why it exists: v[i] does NO bounds checking (out-of-range is
       silent undefined behavior), while v.at(i) DOES check and throws
       std::out_of_range. .at() is slightly slower, so competitive programmers
       prefer [], but .at() is genuinely useful while debugging. */

    // ---- ITERATORS ----
    vector<int>::iterator it = v.begin();
    cout << "1st value of v: " << *(it) << endl;
    it++;
    cout << "2nd value of v: " << *(it) << endl;
    it += 2;                              // vector iterators are RANDOM ACCESS,
    cout << "4th value of v: " << *(it) << endl;   // so jumping like this works

    /* THE FOUR ITERATOR ENDPOINTS:
         v.begin()   -> first element
         v.end()     -> ONE PAST the last element (NOT the last element!)
         v.rbegin()  -> last element, and ++ moves BACKWARD
         v.rend()    -> one BEFORE the first, the reverse "end" marker

       v.end() is a marker, not a real element. Dereferencing it is UNDEFINED
       BEHAVIOR - see the warning in Part 9. */

    vector<pair<char, int>> pair_vector;
    pair_vector.emplace_back('A', 97);
    pair_vector.emplace_back('B', 98);
    pair_vector.emplace_back('C', 99);
    pair_vector.emplace_back('D', 100);
    pair_vector.emplace_back('E', 101);

    vector<pair<char,int>>::iterator itend = pair_vector.end();
    cout << "Last value: " << (*(--itend)).second << endl;   // or (--itend)->second
    itend -= 2;
    cout << "3rd from end: " << (*(itend)).first << endl;

    cout << "Back: " << v.back() << "  Front: " << v.front() << endl;
    // .front() is cleaner than *(v.begin()) for getting the first element

    // ---- THREE WAYS TO LOOP (worst to best) ----
    cout << "Explicit iterator type: ";
    for(vector<int>::iterator i = v.begin(); i != v.end(); i++){
        cout << *(i) << " ";
    }
    cout << endl;

    cout << "Using auto: ";               // auto deduces the type for you
    for(auto i = v.begin(); i != v.end(); i++){
        cout << *(i) << " ";
    }
    cout << endl;

    cout << "Range-based for (best): ";   // like for..of in JavaScript
    for(auto val : v){                     // syntax: for(auto x : iterable)
        cout << val << " ";
    }
    cout << endl;
    /* NOTE: `for(auto val : v)` copies each element. For large objects use
       `for(auto &val : v)` (reference, also lets you MODIFY elements) or
       `for(const auto &val : v)` (reference, read-only). For ints the copy
       is free, so plain `auto` is fine. */

    // ---- ERASING ----
    // v.erase(iterator)              - removes ONE element
    // v.erase(start_it, stop_it)     - removes a RANGE [start, stop)
    //                                  stop is EXCLUDED
    vector<char> name = {'S','h','a','b','n','a','m'};

    name.erase(name.begin() + 6);                      // removes 'm'
    for(auto val : name) cout << val;
    cout << endl;

    name.erase(name.begin() + 1, name.begin() + 4);    // removes indices 1,2,3
    for(auto val : name) cout << val;
    cout << endl;

    // ---- INSERTING ----
    // v.insert(pos, value)         - inserts value BEFORE pos (shifts, not overwrites)
    // v.insert(pos, count, value)  - inserts value `count` times
    // v.insert(pos, first, last)   - inserts a whole range from another container
    vector<int> phone_no(7, 8);

    phone_no.insert(phone_no.begin(), 9);
    cout << "After inserting 9 at the start: ";
    for(auto x : phone_no) cout << x;
    cout << endl;

    phone_no.insert(phone_no.begin() + 3, 2, 6);
    cout << "After inserting 6 twice at index 3: ";
    for(auto x : phone_no) cout << x;
    cout << endl;

    /* WHY INSERT IS COSTLY IN A VECTOR: memory is contiguous, so inserting in
       the middle means every element after that point must be SHIFTED one slot
       to the right. That is O(n). Only push_back at the very end avoids this
       (and even that occasionally triggers a full reallocation + copy). */

    // ---- OTHER USEFUL METHODS ----
    cout << "Size: " << phone_no.size() << endl;
    phone_no.pop_back();                 // removes last element; returns NOTHING
    // (to get the value first: int x = v.back(); v.pop_back();)

    vector<char> proj1 = {'C','a','m','p','u','s','H','i','r','e'};
    vector<char> proj2 = {'C','r','y','s','t','l'};
    proj1.swap(proj2);                    // O(1) - just swaps internal pointers
    cout << "After swap, proj1: ";
    for(auto x : proj1) cout << x;
    cout << endl;

    proj1.clear();                        // removes all elements, size becomes 0
    cout << "Is proj1 empty? " << proj1.empty() << endl;   // 1 = true

    // ---- RESIZE ----
    // v.resize(n)         - changes size to n; truncates if smaller,
    //                       pads with 0 (default value) if larger
    // v.resize(n, value)  - pads with `value` instead of the default
    vector<int> r = {1,2,3};
    r.resize(5);                          // {1,2,3,0,0}
    r.resize(7, 9);                       // {1,2,3,0,0,9,9}
    cout << "After resize: ";
    for(auto x : r) cout << x << " ";
    cout << endl;

    /* SIZE vs CAPACITY (worth knowing):
         size()     = how many elements are actually IN the vector
         capacity() = how much room is currently allocated before it must grow
       When size hits capacity, the vector allocates a bigger block (typically
       double) and copies everything. This is why push_back is "AMORTIZED O(1)"
       rather than plain O(1) - most pushes are instant, occasional ones are
       O(n), and the doubling makes those rare enough that the average stays
       constant.
       If you know the final size in advance, v.reserve(n) pre-allocates and
       avoids all the intermediate reallocations. */
}


/*
================================================================================
PART 3 : LIST
================================================================================
Internally a DOUBLY LINKED LIST - each node holds a value plus pointers to the
previous and next node. Nodes are SCATTERED in memory, not contiguous.

CONSEQUENCES:
  + push_front / emplace_front exist and are O(1) (vector has no such thing)
  + insert / erase anywhere is O(1) IF you already hold an iterator there,
    because nothing needs shifting - just relink a couple of pointers
  - NO random access: ls[3] does not compile, and reaching index i costs O(i)
  - Iterators are BIDIRECTIONAL, not random access: ++ and -- work,
    but it+=2 / it+3 do NOT compile
  - Worse cache performance (see Part 5)
*/

void explainList(){
    list<int> ls;

    ls.push_back(2);
    ls.emplace_back(4);
    ls.push_front(5);                     // <-- vector cannot do this
    ls.emplace_front(6);

    for(auto v : ls) cout << v << " ";
    cout << endl;
    // NOTE: the original file had a stray `=` after this loop's closing brace,
    // which is a SYNTAX ERROR that stopped the whole file from compiling.

    // ---- ITERATORS ARE BIDIRECTIONAL ONLY ----
    list<int>::iterator it = ls.begin();
    it++;                                  // OK
    // it += 1;    // COMPILER ERROR - list iterators are not random access
    // it + 3;     // COMPILER ERROR - same reason

    list<int>::iterator ite = ls.end();
    cout << "2nd: "  << *(it)     << endl;
    cout << "Last: " << *(--ite)  << endl;

    ls.insert(++ls.begin(), 4);
    for(auto v : ls) cout << v << " ";
    cout << endl;

    // ---- advance() - move an iterator n steps, works for ANY iterator type ----
    // For a list this internally just does ++ n times, so it costs O(n) -
    // it does not magically give random access, it only saves you writing a loop.
    auto it_ls = ls.begin();
    advance(it_ls, 2);
    ls.insert(it_ls, 2, 9);                // insert 9 twice at that position
    for(auto v : ls) cout << v << " ";
    cout << endl;
    /* Related helpers that work on any iterator:
         next(it, n)  - returns an iterator n steps forward (doesn't modify it)
         prev(it, n)  - returns an iterator n steps back
         distance(a,b)- number of steps from a to b                          */

    cout << "List size: " << ls.size() << endl;

    list<char> char_ls(4, 'A');
    list<char> char2_ls(4, 'B');
    char_ls.swap(char2_ls);
    for(auto v : char_ls) cout << v;
    cout << endl;

    cout << char_ls.empty() << endl;

    // ---- list has its OWN sort() member function ----
    // std::sort(ls.begin(), ls.end()) does NOT compile - it needs random access
    // iterators. list therefore provides its own merge-sort based version:
    ls.sort();                             // ascending (uses less<> by default)
    ls.sort(greater<int>());               // descending
    // Unlike std::sort, it takes NO range - it always sorts the whole list.
    // TC - O(n log n)

    // Other list-specific members worth knowing: reverse(), unique(), merge(),
    // remove(value), splice()
}


/*
================================================================================
PART 4 : DEQUE
================================================================================
DEQUE = Double Ended QUEue. Insert and delete efficiently at BOTH ends
(unlike a plain queue, which is insert-at-back / delete-from-front only).

INTERNALLY: many fixed-size BLOCKS (chunks), each holding several elements,
tracked by an array of pointers to those blocks. Each block is contiguous
internally, but the blocks themselves are separate allocations.

This gives O(1) random access (via index math across the block table) AND O(1)
push/pop at both ends - but it is NOT one flat contiguous array, so it has no
.data() and slightly worse cache behavior than vector.
*/

void explainDeque(){
    deque<int> dq;

    dq.push_back(1);
    dq.emplace_back(2);
    dq.push_front(3);
    dq.emplace_front(4);

    for(auto v : dq) cout << v << " ";
    cout << endl;

    auto it = dq.begin();
    it += 2;                               // random access iterator - this works
    cout << "3rd element: " << *(it) << endl;

    dq.insert(dq.begin() + 2, 2, 9);
    for(auto v : dq) cout << v << " ";
    cout << endl;
    cout << "Size: " << dq.size() << endl;

    deque<int> dq2 = {9,8,7,6,5};
    dq2.swap(dq);
    cout << "dq2 after swap: ";
    for(auto v : dq2) cout << v << " ";
    cout << endl;

    dq2.clear();
    cout << "dq empty? " << dq.empty() << endl;

    // Also available: pop_front(), pop_back(), front(), back(), at(), []
}


/*
================================================================================
PART 5 : VECTOR vs LIST vs DEQUE - INTERNALS AND CACHE LOCALITY
================================================================================

    | Feature               | vector        | list      | deque          |
    | --------------------- | ------------- | --------- | -------------- |
    | Random access (a[i])  | Fast O(1)     | NO        | Fast O(1)      |
    | Insert at front       | Very slow O(n)| Fast O(1) | Fast O(1)      |
    | Insert at back        | Fast O(1)*    | Fast O(1) | Fast O(1)      |
    | Insert in middle      | Slow O(n)     | Fast O(1)^| Slow O(n)      |
    | Memory layout         | Contiguous    | Scattered | Chunked blocks |
    | Iterator category     | Random access | Bidirect. | Random access  |

      * amortized - occasional reallocation costs O(n)
      ^ O(1) only if you ALREADY hold an iterator to the position; FINDING that
        position still costs O(n) since you must walk there

--------------------------------------------------------------------------------
MEMORY LAYOUT
--------------------------------------------------------------------------------
    vector:   [1][2][3][4][5]                  one continuous block

    list:     [1] -> [2] -> [3] -> [4]         nodes scattered across RAM,
                                                connected only by pointers

    deque:    Block1: [1][2][3]
              Block2: [4][5][6]                blocks contiguous INTERNALLY,
              Block3: [7][8]                   but separate from each other
              [ptr]->Block1  [ptr]->Block2  [ptr]->Block3

    So deque is a HYBRID: not fully contiguous, not fully scattered.

--------------------------------------------------------------------------------
WHY RANDOM ACCESS WORKS FOR VECTOR
--------------------------------------------------------------------------------
    address = base_address + index * sizeof(T)

One multiplication and one addition - O(1), no searching. This ONLY works
because elements sit back-to-back. A list cannot do this: its nodes are at
arbitrary addresses, so reaching index i means following i pointers - O(i).

--------------------------------------------------------------------------------
CACHE LOCALITY - the hidden performance factor
--------------------------------------------------------------------------------
When the CPU reads a memory address, it doesn't fetch just that one value - it
pulls an entire CACHE LINE (typically 64 bytes) into fast on-chip cache. If the
next values you need happen to be in that same line, they're already there -
essentially free.

    vector:  [10][20][30][40]
             Accessing 10 loads 20, 30, 40 into cache too.
             The next few accesses are nearly instant.

    list:    10 -> 20 -> 30 -> 40   (each node elsewhere in RAM)
             Every step is a fresh memory fetch. Cache can't help.

    deque:   Blocks are contiguous internally -> better than list,
             but block boundaries break the streak -> worse than vector.

This is why vector often BEATS list in practice even for workloads where list
has better big-O on paper. Big-O ignores constant factors, and a cache miss is
roughly 100x slower than a cache hit.

--------------------------------------------------------------------------------
WHEN TO USE WHAT
--------------------------------------------------------------------------------
    Fast indexing, mostly appending          -> vector   (the default choice)
    Frequent insert/delete in the middle,
      and you already have iterators there   -> list
    Heavy operations at BOTH ends + indexing -> deque

DEFAULT TO VECTOR unless you have a specific reason not to.
*/


/*
================================================================================
PART 6 : STACK
================================================================================
LIFO - Last In, First Out. Insert and remove only from ONE end (the "top").

A CONTAINER ADAPTER: not a standalone data structure, but a restricted
interface wrapped around another container (deque by default). You cannot
iterate a stack, and there is no [] access - only the top is reachable.
*/

void explainStack(){
    stack<int> st;
    st.push(1);
    st.push(2);
    st.push(3);
    st.push(4);
    st.emplace(5);                        // like push, builds in place

    cout << st.top() << endl;             // 5 - look at the top, doesn't remove
    st.pop();                              // removes the top; returns NOTHING
    cout << st.top() << endl;             // 4
    cout << st.size() << endl;

    stack<int> st1, st2;
    st1.swap(st2);

    // ALL stack operations are O(1): push, pop, top, size, empty
    // NOTE: pop() does not return the removed value. To get it:
    //     int x = st.top();  st.pop();
}


/*
================================================================================
PART 7 : QUEUE
================================================================================
FIFO - First In, First Out. Insert at the BACK, remove from the FRONT.
Also a container adapter (deque by default).
*/

void explainQueue(){
    queue<int> q1;
    q1.push(1);
    q1.push(2);
    q1.push(3);
    q1.push(4);
    q1.push(5);

    cout << q1.back() << endl;            // 5 - last element
    q1.back() += 2;                        // front()/back() return REFERENCES,
    cout << q1.back() << endl;            // so you can modify through them -> 7

    cout << q1.front() << endl;           // 1 - next one to be removed
    cout << q1.size() << endl;

    q1.pop();                              // removes from the FRONT
    cout << q1.front() << endl;           // 2

    // All operations O(1). swap() works the same as for stack.
}


/*
================================================================================
PART 8 : PRIORITY QUEUE
================================================================================
Elements come out in order of PRIORITY (value), not arrival order.
Also a container adapter - internally a BINARY HEAP stored in a vector.

WHY IT EXISTS ALONGSIDE queue: a plain queue is strictly FIFO and has no notion
of "bigger" or "smaller". A priority_queue always hands you the most important
element - essential for Dijkstra, task schedulers, top-K problems.

TEMPLATE: priority_queue<T, Container, Compare>
    T         = element type
    Container = underlying container (vector by default)
    Compare   = ordering rule (less<T> by default -> MAX heap)
*/

void explainPQ(){
    // ---- MAX HEAP (default) - largest element on top ----
    priority_queue<int> pq;
    pq.push(5);
    pq.push(2);
    pq.push(8);
    pq.push(10);
    pq.pop();                              // removes 10 (the largest)
    cout << pq.top() << endl;             // 8

    // ---- MIN HEAP - smallest element on top ----
    priority_queue<int, vector<int>, greater<int>> pq2;
    pq2.push(5);
    pq2.push(2);
    pq2.push(8);
    pq2.push(10);
    cout << pq2.top() << endl;            // 2

    /* WHY less<int> GIVES A MAX HEAP (a common confusion):
       Read the comparator as "does a rank BELOW b?"
         less<int>(a,b)    is true when a < b  -> small values rank low
                           -> the LARGEST bubbles to the top -> MAX heap
         greater<int>(a,b) is true when a > b  -> large values rank low
                           -> the SMALLEST bubbles to the top -> MIN heap

       IMPORTANT: a priority_queue is a HEAP, not a sorted list. Only the TOP
       is guaranteed correct - the rest is partially ordered. You cannot iterate
       it, and internal order is not sequential. */

    // ---- CUSTOM COMPARATOR (for pairs / structs) ----
    // e.g. min-heap of pairs, ordered by second element:
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq3;
    pq3.push({3, 100});
    pq3.push({1, 200});
    cout << pq3.top().first << endl;      // 1

    /* TIME COMPLEXITY:
         top()  - O(1)      just reads index 0
         push() - O(log n)  append, then bubble UP one path (height = log n)
         pop()  - O(log n)  move last to root, then bubble DOWN one path

       top() is O(1) because READING costs nothing. push/pop are O(log n)
       because MAINTAINING the heap property after a change requires walking
       one root-to-leaf path. Different operations, different costs. */
}


/*
================================================================================
PART 9 : SET
================================================================================
Stores UNIQUE elements in SORTED (ascending) order.
Internally a RED-BLACK TREE (a self-balancing binary search tree), which is why
every operation is a guaranteed O(log n) - the tree's height never degrades.
*/

void explainSet(){
    set<int> st;
    st.insert(7);
    st.insert(1);
    st.insert(7);                          // duplicate - silently IGNORED
    st.insert(4);
    st.insert(9);

    for(auto v : st) cout << v << " ";     // prints 1 4 7 9 - always sorted
    cout << endl;

    // NOTE: there is no push_back / emplace_back - position is decided by the
    // sort order, not by you. Use insert() or emplace().

    // ---- find() ----
    auto it = st.find(4);                  // returns an iterator to the element
    it++;                                   // set iterators are BIDIRECTIONAL:
    // it += 2;   // COMPILER ERROR         // ++ and -- only, no jumping
    cout << *(it) << endl;

    /* ***** CRITICAL: ALWAYS CHECK find() AGAINST end() *****
       If the element is NOT present, find() returns st.end() - a marker that
       is NOT a real element. Dereferencing it is UNDEFINED BEHAVIOR.

       The original notes did exactly this:
             auto it2 = st.find(6);        // 6 is not in the set
             cout << *(it2);                // <-- UNDEFINED BEHAVIOR

       VERIFIED BY TESTING: this printed a meaningless value (3) rather than
       crashing, which is the dangerous part - UB often "works" by accident
       and then fails unpredictably later.

       CORRECT PATTERN: */
    auto it2 = st.find(6);
    if(it2 != st.end()){
        cout << "Found: " << *(it2) << endl;
    } else {
        cout << "6 is not in the set" << endl;
    }

    // ---- erase() ----
    st.erase(7);                           // by VALUE
    for(auto v : st) cout << v << " ";
    cout << endl;

    auto it3 = st.find(4);
    if(it3 != st.end()) st.erase(it3);      // by ITERATOR (guard it first!)
    for(auto v : st) cout << v << " ";
    cout << endl;

    // ---- erase a RANGE [start, stop) ----
    set<char> st_char = {'P','R','A','J','N','A','N'};   // duplicates dropped
    for(auto v : st_char) cout << v;
    cout << endl;      // A J N P R

    auto st_it = st_char.find('J');
    auto ed_it = st_char.find('R');
    st_char.erase(st_it, ed_it);            // removes J, N, P (R excluded)
    for(auto v : st_char) cout << v;
    cout << endl;      // A R

    st_char.erase('A');
    for(auto v : st_char) cout << v;
    cout << endl;      // R

    // ---- count() ----
    cout << st.count(2) << endl;
    // For a set this is only ever 0 or 1 (elements are unique), which makes it
    // a convenient "does this exist?" check without needing an end() guard.

    // ---- lower_bound / upper_bound ----
    // st.lower_bound(x) -> first element >= x
    // st.upper_bound(x) -> first element >  x
    // Both return st.end() if no such element exists - GUARD BEFORE DEREFERENCING.
    st.insert(2); st.insert(6); st.insert(8); st.insert(3); st.insert(12);
    for(auto v : st) cout << v << " ";
    cout << endl;

    auto set_it = st.lower_bound(6);
    if(set_it != st.end()) cout << *(set_it) << endl;     // 6 (>= 6)

    auto set_it2 = st.upper_bound(6);
    if(set_it2 != st.end()) cout << *(set_it2) << endl;   // 8 (> 6)

    // Everything else (empty, swap, size, begin, end, rbegin, rend) works as usual.
    // TC - insert / erase / find / count / lower_bound / upper_bound: O(log n)
}


/*
================================================================================
PART 10 : MULTISET
================================================================================
Like set, but ALLOWS DUPLICATES. Still sorted, still a Red-Black tree, still
O(log n) per operation.
*/

void explainMultiset(){
    multiset<int> mset;
    mset.insert(5);  mset.insert(4);  mset.insert(5);
    mset.insert(1);  mset.insert(5);  mset.emplace(6);
    mset.emplace(5); mset.emplace(1); mset.emplace(1);

    for(auto v : mset) cout << v << " ";
    cout << endl;   // 1 1 1 4 5 5 5 5 6

    cout << "Count of 5: " << mset.count(5) << endl;       // 4 (can exceed 1!)

    // ---- erase(value) removes ALL copies ----
    mset.erase(1);
    for(auto v : mset) cout << v << " ";
    cout << endl;   // 4 5 5 5 5 6

    // ---- erase(iterator) removes exactly ONE copy ----
    mset.erase(mset.find(5));
    for(auto v : mset) cout << v << " ";
    cout << endl;   // 4 5 5 5 6

    // ---- erase(start, stop) removes a range ----
    auto it = mset.find(5);
    advance(it, 2);
    mset.erase(mset.find(5), it);          // removes 2 copies of 5
    for(auto v : mset) cout << v << " ";
    cout << endl;   // 4 5 6

    /* THE KEY DISTINCTION, worth memorising:
         mset.erase(5)             -> removes EVERY 5
         mset.erase(mset.find(5))  -> removes exactly ONE 5
       Getting these mixed up is a classic silent bug. */

    // ---- equal_range: get ALL copies of a key at once ----
    // Returns a pair {lower_bound(k), upper_bound(k)} - the full range of k.
    multiset<int> m2 = {2,2,2,5};
    auto range = m2.equal_range(2);
    for(auto i = range.first; i != range.second; ++i) cout << *i << " ";
    cout << endl;                                          // 2 2 2
}


/*
================================================================================
PART 11 : UNORDERED SET
================================================================================
Stores UNIQUE elements with NO ordering at all.
Internally a HASH TABLE, not a tree.

HOW A HASH TABLE WORKS: a hash function converts each key into a bucket index
(index = hash(key) % bucket_count), so you jump straight to the right bucket -
no searching, no comparisons down a tree. That's the O(1).

COLLISION: two different keys hashing to the SAME bucket. That bucket then holds
a small chained list of entries, which must be scanned. With a good hash the
chains stay ~1 element long. In the worst case (bad hash, or adversarial input)
EVERY key lands in one bucket, the chain becomes length n, and operations
degrade to O(n).

So unordered_set is O(1) AVERAGE, O(n) WORST - an expectation, not a guarantee.
Compare: set is O(log n) ALWAYS, guaranteed.

NO lower_bound / upper_bound - those require sorted data, which a hash table
has none of. They do not compile.
*/

void explainUnorderedset(){
    unordered_set<int> uset;
    uset.insert(3);
    uset.insert(4);
    uset.insert(1);
    uset.insert(3);                        // duplicate ignored
    uset.insert(7);
    uset.emplace(8);

    // Output order is arbitrary and does NOT reflect insertion order
    for(auto v : uset) cout << v << " ";
    cout << endl;

    // find / count / erase / size / empty all work the same as set.
    // Iterators are FORWARD only - ++ works, -- does NOT.

    /* WHICH TO CHOOSE:
         Need sorted order, or lower_bound/upper_bound?  -> set
         Only need existence checks, want max speed?     -> unordered_set
         Worried about worst-case guarantees?            -> set             */
}


/*
================================================================================
PART 12 : MAP
================================================================================
Stores KEY -> VALUE pairs. Keys are UNIQUE and kept in SORTED order.
Internally a Red-Black tree, so all operations are O(log n).

Think of it as a dictionary. Both key and value can be any type, including pairs.
*/

void explainMap(){
    map<int, int> mp1;
    map<int, pair<int, int>> mp2;          // value can be a pair
    map<pair<int, int>, int> mp3;          // key can be a pair too

    // ---- FOUR WAYS TO INSERT ----
    mp1.insert({1, 12});                   // insert takes ONE pair -> use {}
    mp1.emplace(2, 24);                     // emplace takes key and value separately
    mp1[3] = 36;                             // operator[] - see the warning below
    mp1.emplace(4, 48);
    mp1.emplace(5, 60);
    mp1.emplace(6, 72);

    /* CORRECTION: the original notes claimed "u cannot directly pass pair as
       {12,1} should use make_pair(a,b)". That is NOT TRUE.
       VERIFIED BY TESTING - all three of these work identically: */
    mp2.insert({12, {12, 1}});              // nested braces - works fine
    mp2.insert({24, make_pair(12, 2)});     // make_pair - also works
    mp2[36] = {12, 3};                       // operator[] with braces - works
    mp2.emplace(48, make_pair(12, 4));
    /* make_pair is a legacy helper from before brace-initialization existed.
       In modern C++ it is rarely necessary - {} figures out the type from
       context. Use whichever reads more clearly to you. */

    mp3.insert({{13,1}, 13});               // insert: one arg, so outer braces
    mp3.emplace(make_pair(13,2), 26);        // emplace: key and value separately
    mp3[{13,3}] = 39;
    mp3.emplace(make_pair(13,4), 52);
    mp3.emplace(make_pair(13,5), 65);
    mp3.emplace(make_pair(13,6), 78);

    for(auto v : mp1) cout << v.first << ":" << v.second << " ";
    cout << endl;

    for(auto v : mp2)
        cout << v.first << ":{" << v.second.first << "," << v.second.second << "} ";
    cout << endl;

    for(auto v : mp3)
        cout << "{" << v.first.first << "," << v.first.second << "}:" << v.second << " ";
    cout << endl;

    // C++17 structured bindings make map iteration much more readable:
    for(auto& [key, value] : mp1) cout << key << "->" << value << " ";
    cout << endl;

    // ---- ACCESSING BY KEY ----
    cout << mp1[1] << endl;                 // 12

    /* ***** MAJOR GOTCHA: operator[] INSERTS MISSING KEYS *****
       The original notes said "if doesnt exist prints 0" - true, but it omits
       the crucial side effect: reading a missing key with [] does not just
       return 0, it CREATES that key with a default value.

       VERIFIED BY TESTING:
           map size before reading mp[9] : 2
           mp[9] returns                 : 0
           map size AFTER reading mp[9]  : 3     <-- the map GREW

       This silently pollutes your map and is a very common bug source
       (especially in frequency counting, where a lookup accidentally adds keys).

       SAFE ALTERNATIVES for read-only checking:
           if(mp.count(key))            ...     // 0 or 1, no insertion
           if(mp.find(key) != mp.end()) ...     // no insertion
           mp.at(key)                            // throws if missing, no insertion

       Use [] when you WANT insert-or-update; use count/find/at to just look. */

    // ---- find() ----
    auto it = mp1.find(4);
    if(it != mp1.end())                     // always guard before dereferencing
        cout << it->first << ":" << it->second << endl;

    cout << "Size of mp3: " << mp3.size() << endl;

    // ---- erase ----
    mp1.erase(3);                            // by key
    for(auto v : mp1) cout << v.first << ":" << v.second << "  ";
    cout << endl;

    auto it2 = mp2.find(24);
    auto it3 = mp2.find(48);
    mp2.erase(it2, it3);                     // by iterator range [it2, it3)
    for(auto v : mp2)
        cout << v.first << ":{" << v.second.first << "," << v.second.second << "} ";
    cout << endl;

    // ---- swap (both maps must have identical types) ----
    map<int, int> mp4;
    mp4.insert({3, 42});
    mp4.emplace(4, 56);
    mp4.emplace(1, 14);
    mp4.emplace(2, 28);
    mp4.swap(mp1);
    cout << "mp1 after swapping with mp4: ";
    for(auto v : mp1) cout << v.first << ":" << v.second << "  ";
    cout << endl;

    cout << "mp2 empty? " << mp2.empty() << endl;

    // ---- lower_bound / upper_bound (on KEYS) ----
    auto it5 = mp1.lower_bound(2);           // first entry with key >= 2
    if(it5 != mp1.end())
        cout << it5->first << ":" << it5->second << endl;

    auto it6 = mp3.upper_bound({13,2});      // first entry with key > {13,2}
    if(it6 != mp3.end())
        cout << "{" << it6->first.first << "," << it6->first.second
             << "}:" << it6->second << endl;

    // TC - insert / erase / find / [] / lower_bound / upper_bound: O(log n)
}


/*
================================================================================
PART 13 : MULTIMAP
================================================================================
Like map, but the SAME KEY CAN REPEAT. Still sorted by key, still O(log n).
*/

void explainMultimap(){
    multimap<int, int> mulmap;
    mulmap.insert({1, 3});
    mulmap.emplace(0, 5);
    mulmap.emplace(4, 7);
    mulmap.emplace(9, 65);
    mulmap.emplace(0, 76);                   // key 0 again - allowed here

    for(auto v : mulmap) cout << v.first << ":" << v.second << "  ";
    cout << endl;

    // ***** multimap has NO operator[] *****
    // cout << mulmap[0];    // COMPILER ERROR
    // It cannot exist: with duplicate keys, which value would [] return?

    // To get all values for one key, use equal_range (or lower/upper_bound):
    auto range = mulmap.equal_range(0);
    cout << "All values for key 0: ";
    for(auto i = range.first; i != range.second; ++i) cout << i->second << " ";
    cout << endl;

    cout << "Count of key 0: " << mulmap.count(0) << endl;   // 2
    // erase(key) removes ALL entries with that key;
    // erase(iterator) removes just one - same distinction as multiset.
}


/*
================================================================================
PART 14 : UNORDERED MAP
================================================================================
Like map, but keys are UNORDERED (hash table instead of tree).
O(1) average, O(n) worst case on heavy collisions.

NO lower_bound / upper_bound (no sorted order to bound against).
*/

void explainUnorderedMap(){
    unordered_map<int, int> unmap;
    unmap.emplace(1, 3);
    unmap.emplace(4, 5);
    unmap.emplace(5, 9);
    unmap.emplace(5, 7);                     // key 5 exists -> IGNORED
    unmap.emplace(1, 8);                     // key 1 exists -> IGNORED

    /* IMPORTANT: emplace/insert do NOT overwrite an existing key - the FIRST
       insertion wins and later ones are silently discarded.
       To OVERWRITE, use operator[] instead:
             unmap[5] = 7;      // sets key 5 to 7 regardless of what was there
       This same behavior applies to map, set, and unordered_set. */

    for(auto v : unmap) cout << v.first << ":" << v.second << "  ";
    cout << endl;

    // Note: unordered_map keys must be HASHABLE. Built-in types and string work
    // out of the box, but pair<int,int> does NOT - there is no std::hash for
    // pair. Use map<pair<int,int>, T> instead, or supply a custom hash functor.
}


/*
================================================================================
PART 15 : CONTAINER COMPLEXITY REFERENCE
================================================================================

  CONTAINER          ACCESS      SEARCH        INSERT        ERASE
  ---------------------------------------------------------------------------
  vector             O(1)        O(n)          O(1) amort*   O(n)
  deque              O(1)        O(n)          O(1) at ends  O(n) middle
  list               O(n)        O(n)          O(1)**        O(1)**
  set / map          -           O(log n)      O(log n)      O(log n)
  multiset/multimap  -           O(log n)      O(log n)      O(log n)
  unordered_set/map  -           O(1) avg      O(1) avg      O(1) avg
                                 O(n) worst    O(n) worst    O(n) worst
  priority_queue     O(1) top    -             O(log n)      O(log n) pop
  stack / queue      O(1) top    -             O(1)          O(1)

    *  push_back only; insert in the middle is O(n)
    ** only if you already hold an iterator to the position

  WHY THESE NUMBERS:
    vector O(1) access     - contiguous memory, direct index arithmetic
    vector O(n) erase      - all following elements must shift down
    list O(n) access       - must walk node by node from the start
    list O(1) insert       - just relink pointers, nothing shifts
    set/map O(log n)       - Red-Black tree stays balanced, so every operation
                             walks one root-to-leaf path of height log n.
                             GUARANTEED regardless of insertion order.
    unordered O(1) average - hash jumps straight to a bucket
    unordered O(n) worst   - all keys collide into one bucket -> linear scan
    priority_queue O(log n)- binary heap; bubble up/down one path = height
*/


/*
================================================================================
PART 16 : ALGORITHMS
================================================================================
Generic functions that operate on iterator RANGES, so the same algorithm works
across vector, array, deque, etc. Range convention is always [start, end) -
the end iterator is EXCLUDED.
*/

// ---- CUSTOM COMPARATOR ----
// A comparator takes two elements and returns TRUE if the first must come
// BEFORE the second in the final order.
//
// Goal here: sort by .second ASCENDING; when .second ties, sort by .first
// DESCENDING.
bool comp(pair<int,int> a, pair<int,int> b){
    if(a.second < b.second) return true;    // smaller second -> comes first
    if(a.second > b.second) return false;   // larger second  -> comes later
    return a.first > b.first;                // tie on second -> bigger first wins
}
/* CORRECTION - the original comparator was:
       if(a.second<b.second)      return true;
       else if(a.second==b.second){
           if(a.first>b.first)    return false;    // <-- BUG: should be true
       }
       return false;

   VERIFIED BY TESTING on {1,2},{2,1},{4,1}:
       original version produced : {2,1} {4,1} {1,2}    <-- WRONG
       corrected version produces: {4,1} {2,1} {1,2}    <-- matches the intent

   The tie-breaking branch returned false when a.first > b.first, which tells
   sort "a does NOT come before b" - the exact opposite of descending order.

   RULE FOR WRITING COMPARATORS: it must define a STRICT WEAK ORDERING.
   In particular comp(a,a) must be FALSE (never use <= or >=), otherwise
   std::sort can read out of bounds and crash. */

void explainAlgo(){
    // ---- SORTING AN ARRAY ----
    int arr[] = {3, 45, 21, 1, 23, 14, 9};
    // int n = len(arr);   // no such thing in C++ (that's Python)
    int n = sizeof(arr) / sizeof(arr[0]);
    /* This works HERE because arr is a real array in this scope. Passed into a
       function it would decay to a pointer and this trick would break - see
       the basics notes. */

    sort(arr, arr + n);                      // ascending
    for(int v : arr) cout << v << " ";
    cout << endl;

    // ---- SORTING A VECTOR ----
    vector<int> vect = {2, 56, 43, 13, 37, 9};
    sort(vect.begin(), vect.end());
    for(auto v : vect) cout << v << " ";
    cout << endl;

    // ---- DESCENDING ----
    sort(arr, arr + n, greater<int>());
    for(auto v : arr) cout << v << " ";
    cout << endl;

    // ---- SORT A SUB-RANGE ----
    sort(vect.begin() + 1, vect.begin() + 4);   // only indices 1,2,3

    // ---- CUSTOM COMPARATOR ----
    vector<pair<int, int>> vect2;
    vect2.emplace_back(1, 2);
    vect2.emplace_back(2, 1);
    vect2.emplace_back(4, 1);

    cout << "Before: ";
    for(auto v : vect2) cout << "{" << v.first << "," << v.second << "}  ";
    cout << endl;

    sort(vect2.begin(), vect2.end(), comp);
    cout << "After custom sort: ";
    for(auto v : vect2) cout << "{" << v.first << "," << v.second << "}  ";
    cout << endl;

    // A LAMBDA is often cleaner than a named function for one-off comparators:
    sort(vect2.begin(), vect2.end(), [](pair<int,int> a, pair<int,int> b){
        return a.first < b.first;
    });

    // ---- __builtin_popcount : count the SET BITS (1s) in binary ----
    // GCC/Clang built-in (not standard C++), compiles to a single CPU instruction.
    cout << __builtin_popcount(7) << endl;    // 7 = 111  -> 3
    cout << __builtin_popcount(12) << endl;   // 12 = 1100 -> 2

    /* ***** CORRECTION - PICK THE RIGHT VARIANT FOR THE TYPE *****
       The original notes listed:
             __builtin_popcountl  -- for unsigned long (32 bits)
       That is wrong on two counts: `long` is 64 bits on 64-bit Linux (only 32
       on Windows), and the original CODE then passed long and long long values
       to plain __builtin_popcount, which takes a 32-bit unsigned int.

       Doing so TRUNCATES the value - any bits above bit 31 are simply lost.
       VERIFIED BY TESTING with 2^40 (which has exactly one set bit):
             __builtin_popcount(2^40)   returned 0     <-- WRONG, bits discarded
             __builtin_popcountll(2^40) returned 1     <-- correct

       It only appeared to work in the original because the test values were
       small enough to fit in 32 bits.

       CORRECT USAGE:
             __builtin_popcount(x)    - unsigned int       (32-bit)
             __builtin_popcountl(x)   - unsigned long      (64-bit on Linux)
             __builtin_popcountll(x)  - unsigned long long (64-bit, always)
       When in doubt for a wide type, use the ll version. */

    long long big = 1LL << 40;
    cout << __builtin_popcountll(big) << endl;   // 1 - correct

    /* WHERE POPCOUNT IS USED: bitmask DP (counting selected items), parity
       checks, Hamming distance via popcount(a ^ b), and power-of-2 checks
       via popcount(x) == 1. */

    // ---- next_permutation ----
    // Rearranges the range IN PLACE into the next lexicographically greater
    // permutation. Returns true if one existed, false if the range was already
    // the largest (fully descending) - in which case it wraps to the smallest.
    // Total permutations of n distinct items = n!
    string str = "432";
    sort(str.begin(), str.end());            // MUST sort first to get them ALL
    do{
        cout << str << endl;
    } while(next_permutation(str.begin(), str.end()));
    // prev_permutation() exists too, moving the other direction.

    // ---- max_element / min_element ----
    // Return an ITERATOR (or pointer for arrays), so dereference with *
    int maxi = *max_element(arr, arr + n);
    int mini = *min_element(arr, arr + n);
    cout << "Max: " << maxi << "  Min: " << mini << endl;
    // TC - O(n) each

    /* ============================================================
       OTHER ALGORITHMS WORTH KNOWING
       ============================================================ */

    vector<int> a = {5, 3, 8, 1, 9, 3};

    // reverse - flips a range in place                       TC O(n)
    reverse(a.begin(), a.end());

    // accumulate - sums a range (needs <numeric>)            TC O(n)
    // The third argument is the STARTING value AND fixes the return type -
    // use 0LL to avoid overflow when summing large numbers.
    long long total = accumulate(a.begin(), a.end(), 0LL);
    cout << "Sum: " << total << endl;

    // count - how many times a value appears                 TC O(n)
    cout << "Count of 3: " << count(a.begin(), a.end(), 3) << endl;

    // find - returns an iterator to the first match, or end() TC O(n)
    auto f = find(a.begin(), a.end(), 8);
    if(f != a.end()) cout << "Found 8 at index " << (f - a.begin()) << endl;

    // binary_search - true/false, requires a SORTED range    TC O(log n)
    sort(a.begin(), a.end());
    cout << "Is 8 present? " << binary_search(a.begin(), a.end(), 8) << endl;

    // lower_bound / upper_bound on a sorted vector           TC O(log n)
    // (the free-function versions, distinct from the set/map member functions)
    auto lb = lower_bound(a.begin(), a.end(), 3);   // first element >= 3
    auto ub = upper_bound(a.begin(), a.end(), 3);   // first element >  3
    cout << "Number of 3s: " << (ub - lb) << endl;

    // unique - moves duplicates to the end, returns the new logical end.
    // It does NOT shrink the container - the standard "erase-remove" idiom:
    sort(a.begin(), a.end());
    a.erase(unique(a.begin(), a.end()), a.end());   // now truly deduplicated

    // max / min / swap on plain values
    cout << max(3, 7) << " " << min(3, 7) << endl;
    int p = 1, q = 2;  swap(p, q);

    // __gcd - GCD via the Euclidean algorithm (GCC built-in)  TC O(log min(a,b))
    cout << "GCD(12,18) = " << __gcd(12, 18) << endl;
    // LCM: (a / __gcd(a,b)) * b   - divide BEFORE multiplying to avoid overflow
}


/*
================================================================================
PART 17 : COMMON MISTAKES CHECKLIST
================================================================================
  [X] Dereferencing find()'s result     -> if not found it returns end(); *end()
      without checking end()               is UNDEFINED BEHAVIOR. Always guard.
  [X] Reading mp[key] for a missing key -> operator[] INSERTS it. Use count(),
                                            find(), or at() for a pure lookup.
  [X] Expecting emplace/insert to       -> they do NOT. First insertion wins.
      overwrite an existing key            Use operator[] to overwrite.
  [X] multiset.erase(value)             -> removes ALL copies. Use
      when you wanted one copy              erase(find(value)) for just one.
  [X] Using it += 2 on set/map/list     -> those are bidirectional iterators;
      iterators                             use advance(), next(), or ++ in a loop.
  [X] std::sort on a list               -> needs random access; use ls.sort()
  [X] lower_bound/upper_bound on an     -> they don't exist; hash tables have
      unordered container                   no ordering
  [X] Comparator using <= or >=         -> must be a STRICT weak ordering;
                                            comp(a,a) must be false or sort
                                            can crash
  [X] __builtin_popcount on a 64-bit    -> silently truncates the top 32 bits;
      value                                 use __builtin_popcountll
  [X] Assuming unordered_* is always    -> O(1) is AVERAGE; worst case is O(n)
      O(1)                                  on heavy collisions
  [X] cout << vector / cout << pair     -> no operator<< exists; loop instead
  [X] Forgetting range end is EXCLUDED  -> [start, stop) everywhere in STL
  [X] pair<int,int> as unordered_map    -> no std::hash for pair; use map or a
      key                                   custom hash functor
================================================================================
*/


int main(){
    // Uncomment whichever section you want to run:
    // explainPair();
    // explainVector();
    // explainList();
    // explainDeque();
    // explainStack();
    // explainQueue();
    // explainPQ();
    // explainSet();
    // explainMultiset();
    // explainUnorderedset();
    // explainMap();
    // explainMultimap();
    // explainUnorderedMap();
    explainAlgo();
    return 0;
}