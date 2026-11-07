#include <bits/stdc++.h>
using namespace std;

/*
    C++17 PRACTICE FILE
    ------------------
    How to use:
    1. Implement the function for the question you are practising.
    2. Go to main() and uncomment ONLY that question's test block.
    3. Compile and run. Compare the printed result with the expected result.
    4. Comment the block again before practising another question, if preferred.

    All function bodies below are intentionally incomplete.
    The placeholder return values are only there so this file compiles before
    you start implementing the functions.

    Numbering is preserved from the supplied questions. Questions 4-9 were not
    present in the supplied material, so they have not been invented here.
*/

// ============================================================
// Helper functions for displaying test results
// ============================================================

template <typename T>
void printVector(const vector<T>& values) {
    cout << "[";
    for (int i = 0; i < (int)values.size(); i++) {
        if (i > 0) cout << ", ";
        cout << values[i];
    }
    cout << "]";
}

void printIntervals(const vector<vector<int>>& intervals) {
    cout << "[";
    for (int i = 0; i < (int)intervals.size(); i++) {
        if (i > 0) cout << ", ";
        printVector(intervals[i]);
    }
    cout << "]";
}

struct ListNode {
    int val;
    ListNode* next;

    ListNode(int x) : val(x), next(nullptr) {}
};

ListNode* buildList(initializer_list<int> values) {
    ListNode* head = nullptr;
    ListNode* tail = nullptr;

    for (int value : values) {
        ListNode* node = new ListNode(value);

        if (head == nullptr) {
            head = node;
            tail = node;
        } else {
            tail->next = node;
            tail = node;
        }
    }

    return head;
}

void printList(ListNode* head) {
    cout << "[";
    while (head != nullptr) {
        cout << head->val;
        head = head->next;
        if (head != nullptr) cout << " -> ";
    }
    cout << "]";
}

void deleteList(ListNode* head) {
    while (head != nullptr) {
        ListNode* nextNode = head->next;
        delete head;
        head = nextNode;
    }
}

// ============================================================
// 1. SUM OF ELEMENTS GREATER THAN K
// ============================================================
/*
    Question:
    Given an array and an integer K, return the sum of all elements
    strictly greater than K.

    Examples:
    1) arr = {10, 20, 5, 15, 30}, K = 12  ->  65
    2) arr = {1, 2, 3, 4}, K = 10        ->  0
    3) arr = {-2, 8, 12, 15}, K = 8      ->  27

    Return type: long long
    Parameters: const vector<int>& arr, int k
*/
long long sumGreaterThanK(const vector<int>& arr, int k) {
    // TODO: Write your solution here.
    return 0;
}

// ============================================================
// 2. TOGGLE CASE
// ============================================================
/*
    Question:
    Flip the case of every alphabetic character. Uppercase letters become
    lowercase and lowercase letters become uppercase. Digits, spaces and
    symbols must remain unchanged.

    Examples:
    1) s = "Hello World1"  ->  "hELLO wORLD1"
    2) s = "AbC-123!"       ->  "aBc-123!"
    3) s = "A z"            ->  "a Z"

    Return type: string
    Parameters: string s
*/
string toggleCase(string s) {
    // TODO: Write your solution here.
    return "";
}

// ============================================================
// 3. VALID PASSWORD
// ============================================================
/*
    Question:
    Check whether a password satisfies ALL the following rules:
    - At least 8 characters.
    - At least one uppercase letter.
    - At least one lowercase letter.
    - At least one digit.
    - At least one special character.
    - No spaces.

    Examples:
    1) s = "Hello@123"     ->  true
    2) s = "NoSpecial123"  ->  false
    3) s = "Good Pass1!"   ->  false

    Return type: bool
    Parameters: const string& s
*/
bool isValidPassword(const string& s) {
    // TODO: Write your solution here.
    return false;
}

// Questions 4-9 were not included in the supplied question list.

// ============================================================
// 10. NUMBER OF SUBARRAYS WITH SUM K
// ============================================================
/*
    Question:
    Given an integer array (which may contain negative numbers) and an
    integer K, count the number of contiguous subarrays whose sum is K.

    Examples:
    1) nums = {1, 1, 1}, K = 2       ->  2
    2) nums = {1, 2, 3}, K = 3       ->  2
    3) nums = {1, -1, 0}, K = 0      ->  3

    Return type: long long
    Parameters: const vector<int>& nums, long long k
*/

long long subarrSumHelper(const vector<int>& nums, long long k){
    int i=0, j=0;
    int n = nums.size();
    long long sum=0, res=0;
    while(i<=j && j<n){
        sum += nums[j];
        while(i<=j && sum>k){
            sum-=nums[i];
            i++;
        }
        res += j-i+1;
        j++;
    }
    return res;
}
long long subarraySumK(const vector<int>& nums, long long k) {
    return (subarrSumHelper(nums, k) - subarrSumHelper(nums, k-1));
}

// ============================================================
// 11. MERGE OVERLAPPING INTERVALS
// ============================================================
/*
    Question:
    Given a list of intervals, merge all overlapping intervals.
    Treat intervals that touch at an endpoint as overlapping.

    Examples:
    1) {{1,3}, {2,6}, {8,10}, {15,18}}  ->  {{1,6}, {8,10}, {15,18}}
    2) {{1,4}, {4,5}}                   ->  {{1,5}}
    3) {{1,2}, {5,6}}                   ->  {{1,2}, {5,6}}

    Return type: vector<vector<int>>
    Parameters: const vector<vector<int>>& intervals
*/
vector<vector<int>> mergeIntervals(const vector<vector<int>>& intervals) {
    // TODO: Write your solution here.
    return {};
}

// ============================================================
// 12. COMMON OVERLAPPING TIME BETWEEN TWO SCHEDULES
// ============================================================
/*
    Question:
    Given two sorted, non-overlapping interval lists, return their common
    overlapping intervals.

    Note: The supplied example returns intersections (overlapping time),
    not the gaps/free periods between appointments.

    Examples:
    1) a = {{1,3}, {5,9}}, b = {{2,6}, {8,10}}
       -> {{2,3}, {5,6}, {8,9}}
    2) a = {{1,5}}, b = {{2,4}}         -> {{2,4}}
    3) a = {{1,2}, {4,6}}, b = {{2,4}, {5,7}}
       -> {{5,6}}

    Return type: vector<vector<int>>
    Parameters: const vector<vector<int>>& a,
                const vector<vector<int>>& b
*/
vector<vector<int>> commonIntervals(const vector<vector<int>>& a,
                                    const vector<vector<int>>& b) {
    // TODO: Write your solution here.
    return {};
}

// ============================================================
// 13. IP ADDRESSES SEEN MORE THAN K TIMES IN ANY T-SECOND WINDOW
// ============================================================
/*
    Question:
    Given parallel arrays of IP addresses and timestamps, return the IP
    addresses that occur MORE THAN K times within at least one T-second
    window. A timestamp difference exactly equal to T is considered inside
    the window, following the supplied version. Return sorted IP addresses.

    Examples:
    1) ips = {"A", "A", "A", "B", "B"}
       times = {1, 3, 5, 2, 10}, K = 2, T = 4  ->  {"A"}
    2) ips = {"A", "A", "A"}
       times = {1, 10, 20}, K = 2, T = 5      ->  {}
    3) ips = {"A", "A", "A", "B", "B", "B"}
       times = {1, 2, 3, 10, 11, 12}, K = 2, T = 2
       -> {"A", "B"}

    Return type: vector<string>
    Parameters: const vector<string>& ips,
                const vector<int>& times, int k, int t
*/
vector<string> frequentIPs(const vector<string>& ips,
                           const vector<int>& times,
                           int k, int t) {
    // TODO: Write your solution here.
    return {};
}

// ============================================================
// 14. LONGEST SUBSTRING WITHOUT REPEATING CHARACTERS
// ============================================================
/*
    Question:
    Return the length of the longest substring that contains no repeated
    characters.

    Examples:
    1) s = "abcabcbb"  ->  3
    2) s = "bbbbb"     ->  1
    3) s = ""          ->  0

    Return type: int
    Parameters: const string& s
*/
int lengthOfLongestSubstring(const string& s) {
    // TODO: Write your solution here.
    return 0;
}

// ============================================================
// 15. MAXIMUM SUM OF A SUBARRAY OF SIZE K
// ============================================================
/*
    Question:
    Given an array and K, return the maximum sum among all contiguous
    subarrays of exactly K elements.

    Examples:
    1) nums = {2, 1, 5, 1, 3, 2}, K = 3  ->  9
    2) nums = {-5, -2, -3}, K = 2        ->  -5
    3) nums = {1, 2}, K = 1              ->  2

    Return type: long long
    Parameters: const vector<int>& nums, int k
    Precondition: 1 <= k <= nums.size().
*/
long long maxSumWindow(const vector<int>& nums, int k) {
    // TODO: Write your solution here.
    return 0;
}

// ============================================================
// 16. SHORTEST SUBARRAY WITH EXACTLY K DISTINCT INTEGERS
// ============================================================
/*
    Question:
    Return the minimum length of a contiguous subarray containing exactly
    K distinct integers. Return -1 if no such subarray exists.

    Examples:
    1) nums = {1, 2, 1, 2, 3}, K = 2  ->  2
    2) nums = {1, 2, 3}, K = 4        ->  -1
    3) nums = {1, 2, 1, 3, 4}, K = 3  ->  3

    Return type: int
    Parameters: const vector<int>& nums, int k
*/
int minLenKDistinct(const vector<int>& nums, int k) {
    // TODO: Write your solution here.
    return -1;
}

// ============================================================
// 17. SLIDING WINDOW MAXIMUM
// ============================================================
/*
    Question:
    Given an array and window size K, return the maximum element from every
    contiguous window of size K.

    Examples:
    1) nums = {1,3,-1,-3,5,3,6,7}, K = 3  ->  {3,3,5,5,6,7}
    2) nums = {1}, K = 1                   ->  {1}
    3) nums = {-4,-2,-5,-1}, K = 2        ->  {-2,-2,-1}

    Return type: vector<int>
    Parameters: const vector<int>& nums, int k
*/
vector<int> maxSlidingWindow(const vector<int>& nums, int k) {
    // TODO: Write your solution here.
    return {};
}

// ============================================================
// 18. PAIR WITH A TARGET SUM IN A SORTED ARRAY
// ============================================================
/*
    Question:
    Given a sorted array and a target, return the 0-based indices of two
    elements whose sum equals the target. Return an empty vector if no pair
    exists. Assume exactly one pair at most is required.

    Examples:
    1) nums = {1,2,4,7,11}, target = 9  ->  {1,3}
    2) nums = {2,3,5,8}, target = 10    ->  {0,3}
    3) nums = {1,2,3}, target = 10     ->  {}

    Return type: vector<int>
    Parameters: const vector<int>& nums, int target
*/
vector<int> twoSumSorted(const vector<int>& nums, int target) {
    // TODO: Write your solution here.
    return {};
}

// ============================================================
// 19. STOCK BUY AND SELL WITH MULTIPLE TRANSACTIONS
// ============================================================
/*
    Question:
    Given daily stock prices, return the maximum profit possible when
    multiple buy-and-sell transactions are allowed. You must sell before
    buying again.

    Examples:
    1) prices = {7,1,5,3,6,4}  ->  7
    2) prices = {1,2,3,4,5}    ->  4
    3) prices = {7,6,4,3,1}    ->  0

    Return type: long long
    Parameters: const vector<int>& prices
*/
long long maxProfit(const vector<int>& prices) {
    // TODO: Write your solution here.
    return 0;
}

// ============================================================
// 20. MAXIMUM NUMBER OF NON-OVERLAPPING INTERVALS
// ============================================================
/*
    Question:
    Given intervals, select the maximum number of mutually non-overlapping
    intervals. An interval can start exactly when the previous one ends.

    Examples:
    1) {{1,2}, {2,3}, {3,4}, {1,3}}  ->  3
    2) {{1,4}, {2,3}, {3,5}, {6,7}}  ->  3
    3) {}                            ->  0

    Return type: int
    Parameters: const vector<vector<int>>& intervals
*/
int maxNonOverlappingIntervals(const vector<vector<int>>& intervals) {
    // TODO: Write your solution here.
    return 0;
}

// ============================================================
// 21. ORDER TASKS WITH DEPENDENCIES (TOPOLOGICAL SORT)
// ============================================================
/*
    Question:
    There are N tasks numbered 0 to N-1. Each pair [a,b] means task b must
    be completed before task a. Return any valid task order. If dependencies
    contain a cycle, return an empty vector.

    Examples:
    1) n = 4, prerequisites = {{1,0}, {2,1}, {3,2}}
       -> {0,1,2,3}
    2) n = 2, prerequisites = {{1,0}}       -> {0,1}
    3) n = 2, prerequisites = {{1,0}, {0,1}} -> {}

    Return type: vector<int>
    Parameters: int n, const vector<vector<int>>& prerequisites
*/
vector<int> courseOrder(int n,
                        const vector<vector<int>>& prerequisites) {
    // TODO: Write your solution here.
    return {};
}

// ============================================================
// 22. NUMBER OF CONNECTED COMPONENTS
// ============================================================
/*
    Question:
    Given an undirected graph with N vertices numbered 0 to N-1 and its
    edge list, return the number of connected components.

    Examples:
    1) n = 5, edges = {{0,1}, {1,2}, {3,4}}  ->  2
    2) n = 3, edges = {}                     ->  3
    3) n = 4, edges = {{0,1}, {1,2}, {2,3}}  ->  1

    Return type: int
    Parameters: int n, const vector<vector<int>>& edges
*/
int countComponents(int n, const vector<vector<int>>& edges) {
    // TODO: Write your solution here.
    return 0;
}

// ============================================================
// 23. EARLIEST TIME TO REACH A TARGET ON A GRID
// ============================================================
/*
    Question:
    Start at (sx, sy) and reach (ex, ey). At each second, you may move one
    step in the direction given by the corresponding character in the
    directions string, or stay still. Return the earliest time at which the
    target can be reached, or -1 if it cannot be reached.

    Direction convention from the supplied question:
    R increases x, L decreases x, U increases y, D decreases y.

    Examples:
    1) start = (0,0), target = (1,1), directions = "RU"  ->  2
    2) start = (2,3), target = (2,3), directions = ""    ->  0
    3) start = (0,0), target = (0,2), directions = "RDL" -> -1

    Return type: int
    Parameters: int sx, int sy, int ex, int ey, const string& directions
*/
int earliestTime(int sx, int sy, int ex, int ey,
                 const string& directions) {
    // TODO: Write your solution here.
    return -1;
}

// ============================================================
// 24. NUMBER OF WAYS TO MAKE CHANGE (COIN CHANGE II)
// ============================================================
/*
    Question:
    Given coin denominations and a target amount, return the number of
    combinations that make the amount. Each coin can be used unlimited
    times, and different orders of the same combination are not counted
    separately. Assume coin denominations are distinct positive integers.

    Examples:
    1) coins = {1,2,5}, amount = 5  ->  4
    2) coins = {2}, amount = 3      ->  0
    3) coins = {1,2,3}, amount = 4  ->  4

    Return type: long long
    Parameters: const vector<int>& coins, int amount
*/
long long coinWays(const vector<int>& coins, int amount) {
    // TODO: Write your solution here.
    return 0;
}

// ============================================================
// 25. WORD BREAK
// ============================================================
/*
    Question:
    Given a string and a dictionary of words, determine whether the string
    can be segmented into one or more dictionary words.

    Examples:
    1) s = "leetcode", words = {"leet", "code"} -> true
    2) s = "applepenapple", words = {"apple", "pen"} -> true
    3) s = "catsandog", words = {"cats", "dog", "sand", "and", "cat"}
       -> false

    Return type: bool
    Parameters: const string& s, const vector<string>& words
*/
bool wordBreak(const string& s, const vector<string>& words) {
    // TODO: Write your solution here.
    return false;
}

// ============================================================
// 26. REVERSE A LINKED LIST
// ============================================================
/*
    Question:
    Given the head of a singly linked list, reverse the list and return the
    new head.

    Examples:
    1) 1 -> 2 -> 3 -> nullptr  ->  3 -> 2 -> 1 -> nullptr
    2) 7 -> nullptr            ->  7 -> nullptr
    3) nullptr                 ->  nullptr

    Return type: ListNode*
    Parameters: ListNode* head
*/
ListNode* reverseList(ListNode* head) {
    // TODO: Write your solution here.
    return nullptr;
}

// ============================================================
// 27. SHUFFLE AN ARRAY (FISHER-YATES)
// ============================================================
/*
    Question:
    Shuffle the array in-place so that every permutation has an equal
    probability of occurring. Use the supplied random-number generator.

    Examples (the exact output is intentionally not fixed):
    1) {1,2,3,4}       -> one possible result: {3,1,4,2}
    2) {10,20,30}      -> any permutation of these three values
    3) {5}             -> {5}

    Return type: void
    Parameters: vector<int>& arr, mt19937& rng
*/
void shuffleArray(vector<int>& arr, mt19937& rng) {
    // TODO: Write your solution here.
}

// ============================================================
// MAIN: UNCOMMENT ONLY THE TEST BLOCK YOU WANT TO RUN
// ============================================================

int main() {

    // --------------------------------------------------------
    // TESTS FOR QUESTION 1: SUM OF ELEMENTS GREATER THAN K
    // --------------------------------------------------------
    /*
    {
        vector<int> arr = {10, 20, 5, 15, 30};
        cout << "Q1 - Test 1: " << sumGreaterThanK(arr, 12)
             << " | Expected: 65\n";

        vector<int> arr2 = {1, 2, 3, 4};
        cout << "Q1 - Test 2: " << sumGreaterThanK(arr2, 10)
             << " | Expected: 0\n";

        vector<int> arr3 = {-2, 8, 12, 15};
        cout << "Q1 - Test 3: " << sumGreaterThanK(arr3, 8)
             << " | Expected: 27\n";
    }
    */

    // --------------------------------------------------------
    // TESTS FOR QUESTION 2: TOGGLE CASE
    // --------------------------------------------------------
    /*
    {
        cout << "Q2 - Test 1: " << toggleCase("Hello World1")
             << " | Expected: hELLO wORLD1\n";
        cout << "Q2 - Test 2: " << toggleCase("AbC-123!")
             << " | Expected: aBc-123!\n";
        cout << "Q2 - Test 3: " << toggleCase("A z")
             << " | Expected: a Z\n";
    }
    */

    // --------------------------------------------------------
    // TESTS FOR QUESTION 3: VALID PASSWORD
    // --------------------------------------------------------
    /*
    {
        cout << boolalpha;
        cout << "Q3 - Test 1: " << isValidPassword("Hello@123")
             << " | Expected: true\n";
        cout << "Q3 - Test 2: " << isValidPassword("NoSpecial123")
             << " | Expected: false\n";
        cout << "Q3 - Test 3: " << isValidPassword("Good Pass1!")
             << " | Expected: false\n";
    }
    */

    // Questions 4-9 were not supplied.

    // --------------------------------------------------------
    // TESTS FOR QUESTION 10: NUMBER OF SUBARRAYS WITH SUM K
    // --------------------------------------------------------
    {
        vector<int> a = {1, 1, 1};
        cout << "Q10 - Test 1: " << subarraySumK(a, 2)
             << " | Expected: 2\n";

        vector<int> b = {1, 2, 3};
        cout << "Q10 - Test 2: " << subarraySumK(b, 3)
             << " | Expected: 2\n";

        vector<int> c = {1, -1, 0};
        cout << "Q10 - Test 3: " << subarraySumK(c, 0)
             << " | Expected: 3\n";
    }

    // --------------------------------------------------------
    // TESTS FOR QUESTION 11: MERGE OVERLAPPING INTERVALS
    // --------------------------------------------------------
    /*
    {
        vector<vector<int>> a = {{1,3}, {2,6}, {8,10}, {15,18}};
        cout << "Q11 - Test 1: ";
        printIntervals(mergeIntervals(a));
        cout << " | Expected: [[1, 6], [8, 10], [15, 18]]\n";

        vector<vector<int>> b = {{1,4}, {4,5}};
        cout << "Q11 - Test 2: ";
        printIntervals(mergeIntervals(b));
        cout << " | Expected: [[1, 5]]\n";

        vector<vector<int>> c = {{1,2}, {5,6}};
        cout << "Q11 - Test 3: ";
        printIntervals(mergeIntervals(c));
        cout << " | Expected: [[1, 2], [5, 6]]\n";
    }
    */

    // --------------------------------------------------------
    // TESTS FOR QUESTION 12: COMMON OVERLAPPING INTERVALS
    // --------------------------------------------------------
    /*
    {
        vector<vector<int>> a = {{1,3}, {5,9}};
        vector<vector<int>> b = {{2,6}, {8,10}};
        cout << "Q12 - Test 1: ";
        printIntervals(commonIntervals(a, b));
        cout << " | Expected: [[2, 3], [5, 6], [8, 9]]\n";

        vector<vector<int>> c = {{1,5}};
        vector<vector<int>> d = {{2,4}};
        cout << "Q12 - Test 2: ";
        printIntervals(commonIntervals(c, d));
        cout << " | Expected: [[2, 4]]\n";

        vector<vector<int>> e = {{1,2}, {4,6}};
        vector<vector<int>> f = {{2,4}, {5,7}};
        cout << "Q12 - Test 3: ";
        printIntervals(commonIntervals(e, f));
        cout << " | Expected: [[5, 6]]\n";
    }
    */

    // --------------------------------------------------------
    // TESTS FOR QUESTION 13: FREQUENT IP ADDRESSES
    // --------------------------------------------------------
    /*
    {
        vector<string> ips1 = {"A", "A", "A", "B", "B"};
        vector<int> times1 = {1, 3, 5, 2, 10};
        cout << "Q13 - Test 1: ";
        printVector(frequentIPs(ips1, times1, 2, 4));
        cout << " | Expected: [A]\n";

        vector<string> ips2 = {"A", "A", "A"};
        vector<int> times2 = {1, 10, 20};
        cout << "Q13 - Test 2: ";
        printVector(frequentIPs(ips2, times2, 2, 5));
        cout << " | Expected: []\n";

        vector<string> ips3 = {"A", "A", "A", "B", "B", "B"};
        vector<int> times3 = {1, 2, 3, 10, 11, 12};
        cout << "Q13 - Test 3: ";
        printVector(frequentIPs(ips3, times3, 2, 2));
        cout << " | Expected: [A, B]\n";
    }
    */

    // --------------------------------------------------------
    // TESTS FOR QUESTION 14: LONGEST SUBSTRING WITHOUT REPEATS
    // --------------------------------------------------------
    /*
    {
        cout << "Q14 - Test 1: " << lengthOfLongestSubstring("abcabcbb")
             << " | Expected: 3\n";
        cout << "Q14 - Test 2: " << lengthOfLongestSubstring("bbbbb")
             << " | Expected: 1\n";
        cout << "Q14 - Test 3: " << lengthOfLongestSubstring("")
             << " | Expected: 0\n";
    }
    */

    // --------------------------------------------------------
    // TESTS FOR QUESTION 15: MAXIMUM SUM SUBARRAY OF SIZE K
    // --------------------------------------------------------
    /*
    {
        vector<int> a = {2, 1, 5, 1, 3, 2};
        cout << "Q15 - Test 1: " << maxSumWindow(a, 3)
             << " | Expected: 9\n";

        vector<int> b = {-5, -2, -3};
        cout << "Q15 - Test 2: " << maxSumWindow(b, 2)
             << " | Expected: -5\n";

        vector<int> c = {1, 2};
        cout << "Q15 - Test 3: " << maxSumWindow(c, 1)
             << " | Expected: 2\n";
    }
    */

    // --------------------------------------------------------
    // TESTS FOR QUESTION 16: SHORTEST SUBARRAY WITH K DISTINCT
    // --------------------------------------------------------
    /*
    {
        vector<int> a = {1, 2, 1, 2, 3};
        cout << "Q16 - Test 1: " << minLenKDistinct(a, 2)
             << " | Expected: 2\n";

        vector<int> b = {1, 2, 3};
        cout << "Q16 - Test 2: " << minLenKDistinct(b, 4)
             << " | Expected: -1\n";

        vector<int> c = {1, 2, 1, 3, 4};
        cout << "Q16 - Test 3: " << minLenKDistinct(c, 3)
             << " | Expected: 3\n";
    }
    */

    // --------------------------------------------------------
    // TESTS FOR QUESTION 17: SLIDING WINDOW MAXIMUM
    // --------------------------------------------------------
    /*
    {
        vector<int> a = {1, 3, -1, -3, 5, 3, 6, 7};
        cout << "Q17 - Test 1: ";
        printVector(maxSlidingWindow(a, 3));
        cout << " | Expected: [3, 3, 5, 5, 6, 7]\n";

        vector<int> b = {1};
        cout << "Q17 - Test 2: ";
        printVector(maxSlidingWindow(b, 1));
        cout << " | Expected: [1]\n";

        vector<int> c = {-4, -2, -5, -1};
        cout << "Q17 - Test 3: ";
        printVector(maxSlidingWindow(c, 2));
        cout << " | Expected: [-2, -2, -1]\n";
    }
    */

    // --------------------------------------------------------
    // TESTS FOR QUESTION 18: PAIR WITH TARGET SUM IN SORTED ARRAY
    // --------------------------------------------------------
    /*
    {
        vector<int> a = {1, 2, 4, 7, 11};
        cout << "Q18 - Test 1: ";
        printVector(twoSumSorted(a, 9));
        cout << " | Expected: [1, 3]\n";

        vector<int> b = {2, 3, 5, 8};
        cout << "Q18 - Test 2: ";
        printVector(twoSumSorted(b, 10));
        cout << " | Expected: [0, 3]\n";

        vector<int> c = {1, 2, 3};
        cout << "Q18 - Test 3: ";
        printVector(twoSumSorted(c, 10));
        cout << " | Expected: []\n";
    }
    */

    // --------------------------------------------------------
    // TESTS FOR QUESTION 19: STOCK BUY AND SELL MULTIPLE TIMES
    // --------------------------------------------------------
    /*
    {
        vector<int> a = {7, 1, 5, 3, 6, 4};
        cout << "Q19 - Test 1: " << maxProfit(a)
             << " | Expected: 7\n";

        vector<int> b = {1, 2, 3, 4, 5};
        cout << "Q19 - Test 2: " << maxProfit(b)
             << " | Expected: 4\n";

        vector<int> c = {7, 6, 4, 3, 1};
        cout << "Q19 - Test 3: " << maxProfit(c)
             << " | Expected: 0\n";
    }
    */

    // --------------------------------------------------------
    // TESTS FOR QUESTION 20: MAXIMUM NON-OVERLAPPING INTERVALS
    // --------------------------------------------------------
    /*
    {
        vector<vector<int>> a = {{1,2}, {2,3}, {3,4}, {1,3}};
        cout << "Q20 - Test 1: " << maxNonOverlappingIntervals(a)
             << " | Expected: 3\n";

        vector<vector<int>> b = {{1,4}, {2,3}, {3,5}, {6,7}};
        cout << "Q20 - Test 2: " << maxNonOverlappingIntervals(b)
             << " | Expected: 3\n";

        vector<vector<int>> c;
        cout << "Q20 - Test 3: " << maxNonOverlappingIntervals(c)
             << " | Expected: 0\n";
    }
    */

    // --------------------------------------------------------
    // TESTS FOR QUESTION 21: TASK ORDER / TOPOLOGICAL SORT
    // --------------------------------------------------------
    /*
    {
        vector<vector<int>> a = {{1,0}, {2,1}, {3,2}};
        cout << "Q21 - Test 1: ";
        printVector(courseOrder(4, a));
        cout << " | Expected: [0, 1, 2, 3]\n";

        vector<vector<int>> b = {{1,0}};
        cout << "Q21 - Test 2: ";
        printVector(courseOrder(2, b));
        cout << " | Expected: [0, 1]\n";

        vector<vector<int>> c = {{1,0}, {0,1}};
        cout << "Q21 - Test 3: ";
        printVector(courseOrder(2, c));
        cout << " | Expected: []\n";
    }
    */

    // --------------------------------------------------------
    // TESTS FOR QUESTION 22: NUMBER OF CONNECTED COMPONENTS
    // --------------------------------------------------------
    /*
    {
        vector<vector<int>> a = {{0,1}, {1,2}, {3,4}};
        cout << "Q22 - Test 1: " << countComponents(5, a)
             << " | Expected: 2\n";

        vector<vector<int>> b;
        cout << "Q22 - Test 2: " << countComponents(3, b)
             << " | Expected: 3\n";

        vector<vector<int>> c = {{0,1}, {1,2}, {2,3}};
        cout << "Q22 - Test 3: " << countComponents(4, c)
             << " | Expected: 1\n";
    }
    */

    // --------------------------------------------------------
    // TESTS FOR QUESTION 23: EARLIEST TIME TO REACH GRID TARGET
    // --------------------------------------------------------
    /*
    {
        cout << "Q23 - Test 1: "
             << earliestTime(0, 0, 1, 1, "RU")
             << " | Expected: 2\n";

        cout << "Q23 - Test 2: "
             << earliestTime(2, 3, 2, 3, "")
             << " | Expected: 0\n";

        cout << "Q23 - Test 3: "
             << earliestTime(0, 0, 0, 2, "RDL")
             << " | Expected: -1\n";
    }
    */

    // --------------------------------------------------------
    // TESTS FOR QUESTION 24: NUMBER OF WAYS TO MAKE CHANGE
    // --------------------------------------------------------
    /*
    {
        vector<int> coins1 = {1, 2, 5};
        cout << "Q24 - Test 1: " << coinWays(coins1, 5)
             << " | Expected: 4\n";

        vector<int> coins2 = {2};
        cout << "Q24 - Test 2: " << coinWays(coins2, 3)
             << " | Expected: 0\n";

        vector<int> coins3 = {1, 2, 3};
        cout << "Q24 - Test 3: " << coinWays(coins3, 4)
             << " | Expected: 4\n";
    }
    */

    // --------------------------------------------------------
    // TESTS FOR QUESTION 25: WORD BREAK
    // --------------------------------------------------------
    /*
    {
        cout << boolalpha;

        vector<string> words1 = {"leet", "code"};
        cout << "Q25 - Test 1: " << wordBreak("leetcode", words1)
             << " | Expected: true\n";

        vector<string> words2 = {"apple", "pen"};
        cout << "Q25 - Test 2: " << wordBreak("applepenapple", words2)
             << " | Expected: true\n";

        vector<string> words3 = {"cats", "dog", "sand", "and", "cat"};
        cout << "Q25 - Test 3: " << wordBreak("catsandog", words3)
             << " | Expected: false\n";
    }
    */

    // --------------------------------------------------------
    // TESTS FOR QUESTION 26: REVERSE A LINKED LIST
    // --------------------------------------------------------
    /*
    {
        ListNode* head1 = buildList({1, 2, 3});
        ListNode* result1 = reverseList(head1);
        cout << "Q26 - Test 1: ";
        printList(result1);
        cout << " | Expected: [3 -> 2 -> 1]\n";
        deleteList(result1);

        ListNode* head2 = buildList({7});
        ListNode* result2 = reverseList(head2);
        cout << "Q26 - Test 2: ";
        printList(result2);
        cout << " | Expected: [7]\n";
        deleteList(result2);

        ListNode* head3 = buildList({});
        ListNode* result3 = reverseList(head3);
        cout << "Q26 - Test 3: ";
        printList(result3);
        cout << " | Expected: []\n";
        deleteList(result3);
    }
    */

    // --------------------------------------------------------
    // TESTS FOR QUESTION 27: SHUFFLE AN ARRAY
    // --------------------------------------------------------
    /*
    {
        mt19937 rng1(42);
        vector<int> a = {1, 2, 3, 4};
        shuffleArray(a, rng1);
        cout << "Q27 - Test 1: ";
        printVector(a);
        cout << " | Expected: any permutation of [1, 2, 3, 4]\n";

        mt19937 rng2(123);
        vector<int> b = {10, 20, 30};
        shuffleArray(b, rng2);
        cout << "Q27 - Test 2: ";
        printVector(b);
        cout << " | Expected: any permutation of [10, 20, 30]\n";

        mt19937 rng3(7);
        vector<int> c = {5};
        shuffleArray(c, rng3);
        cout << "Q27 - Test 3: ";
        printVector(c);
        cout << " | Expected: [5]\n";
    }
    */

    return 0;
}
