#include <bits/stdc++.h>
using namespace std;

/*
    IBM CIO BPT SOFTWARE DEVELOPER OA - DSA PRACTICE FILE
    C++17 | Questions 01-30

    HOW TO PRACTISE
    1. Read the numbered question and its scenario, constraints, input/output
       format, and sample below.
    2. Implement ONLY the function/class marked TODO for that question.
    3. Change ACTIVE_QUESTION to the question number you want to test.
    4. Compile with: g++ -std=c++17 -O2 -Wall practice.cpp -o practice
    5. Run the program and compare its output with the expected output.

    The main() function and sample test blocks are already prepared.
    No solution logic has been filled in. The placeholder returns only allow
    the file to compile before you start practising.

    IMPORTANT:
    - Question headings intentionally show only their numbers. No technique or
      solution-pattern names are exposed as headings.
    - The original preparation document did not specify formal constraints for
      every question. The limits below are practice constraints added to make
      each task precise. Follow an actual OA statement if its limits differ.
    - Indices are 0-based unless stated otherwise.
*/

// Change this number to practise a different question (1 to 30).
#define ACTIVE_QUESTION 1

// ============================================================
// Common helpers used only by the ready-made test runner
// ============================================================

template <typename T>
void printVector(const vector<T>& values) {
    cout << "[";
    for (int i = 0; i < (int)values.size(); i++) {
        if (i) cout << ", ";
        cout << values[i];
    }
    cout << "]";
}

void printIntMatrix(vector<vector<int>> values) {
    for (auto& row : values) sort(row.begin(), row.end());
    sort(values.begin(), values.end());
    cout << "[";
    for (int i = 0; i < (int)values.size(); i++) {
        if (i) cout << ", ";
        printVector(values[i]);
    }
    cout << "]";
}

void printStringGroups(vector<vector<string>> groups) {
    for (auto& group : groups) sort(group.begin(), group.end());
    sort(groups.begin(), groups.end());
    cout << "[";
    for (int i = 0; i < (int)groups.size(); i++) {
        if (i) cout << ", ";
        cout << "[";
        for (int j = 0; j < (int)groups[i].size(); j++) {
            if (j) cout << ", ";
            cout << groups[i][j];
        }
        cout << "]";
    }
    cout << "]";
}

void printIntervals(const vector<vector<int>>& intervals) {
    cout << "[";
    for (int i = 0; i < (int)intervals.size(); i++) {
        if (i) cout << ", ";
        printVector(intervals[i]);
    }
    cout << "]";
}

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int value) : val(value), next(nullptr) {}
};

ListNode* buildList(const vector<int>& values) {
    ListNode* head = nullptr;
    ListNode* tail = nullptr;
    for (int value : values) {
        ListNode* node = new ListNode(value);
        if (!head) head = tail = node;
        else {
            tail->next = node;
            tail = node;
        }
    }
    return head;
}

ListNode* buildListWithCycle(const vector<int>& values, int pos) {
    ListNode* head = buildList(values);
    if (head == nullptr || pos < 0) return head;

    ListNode* cycleNode = nullptr;
    ListNode* tail = head;
    int index = 0;
    while (tail->next != nullptr) {
        if (index == pos) cycleNode = tail;
        tail = tail->next;
        index++;
    }
    if (index == pos) cycleNode = tail;
    if (cycleNode != nullptr) tail->next = cycleNode;
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

void deletePossiblyCyclicList(ListNode* head) {
    vector<ListNode*> nodes;
    unordered_set<ListNode*> seen;
    while (head != nullptr && !seen.count(head)) {
        seen.insert(head);
        nodes.push_back(head);
        head = head->next;
    }
    for (ListNode* node : nodes) delete node;
}

// ============================================================
// QUESTION 01
// ============================================================
/*
Difficulty: Easy

Scenario:
A billing service receives a list of line-item amounts and a target total.
Find the two different positions whose values add up to the target.

Constraints:
- 2 <= n <= 200000
- -1000000000 <= nums[i], target <= 1000000000
- At most one valid pair is required. Return an empty vector if no pair exists.
- The same array position cannot be used twice.

Input format:
Line 1: n
Line 2: n space-separated integers
Line 3: target

Output format:
Two 0-based indices in one line, or -1 -1 if no pair exists.

Sample input:
4
2 7 11 15
9

Sample output:
0 1
*/
vector<int> solveQ01(const vector<int>& nums, int target) {
    // TODO: Write your code here.
    return {};
}

// ============================================================
// QUESTION 02
// ============================================================
/*
Difficulty: Easy

Scenario:
A log parser needs to identify the first character in an identifier that
appears exactly once. Return its 0-based index.

Constraints:
- 1 <= length of s <= 200000
- s contains standard ASCII characters.
- Return -1 when every character appears more than once.

Input format:
One string s (without spaces).

Output format:
The 0-based index of the first non-repeating character, or -1.

Sample input:
aabbcdeff

Sample output:
4
*/
int solveQ02(const string& s) {
    // TODO: Write your code here.
    return -1;
}

// ============================================================
// QUESTION 03
// ============================================================
/*
Difficulty: Easy

Scenario:
A transaction reference is considered symmetric when its digits read the
same from left to right and right to left. Determine whether x is symmetric.

Constraints:
- -2147483648 <= x <= 2147483647
- Negative numbers are not considered symmetric.

Input format:
One integer x.

Output format:
Print true or false.

Sample input:
12321

Sample output:
true
*/
bool solveQ03(int x) {
    // TODO: Write your code here.
    return false;
}

// ============================================================
// QUESTION 04
// ============================================================
/*
Difficulty: Easy

Scenario:
A code editor checks whether brackets in a configuration expression are
correctly nested. The expression contains only (, ), [, ], { and }.

Constraints:
- 0 <= length of s <= 100000
- Every opening bracket must have the correct closing bracket.
- Brackets must close in the correct order.

Input format:
One string s. An empty string may be represented by an empty line.

Output format:
Print true if the expression is valid; otherwise print false.

Sample input:
{[()]}

Sample output:
true
*/
bool solveQ04(const string& s) {
    // TODO: Write your code here.
    return false;
}

// ============================================================
// QUESTION 05
// ============================================================
/*
Difficulty: Easy

Scenario:
Two inventory lists are already sorted in non-decreasing order. The first
list has enough extra space at its end to hold every value from the second.
Combine the second list into the first list in sorted order.

Constraints:
- 0 <= m, n <= 200000
- m + n <= 200000
- The first vector has exactly m + n positions; only its first m positions
  contain valid values initially.
- Both input lists are sorted in non-decreasing order.

Input format:
Line 1: m n
Line 2: m valid values followed by n placeholder values in the first list
Line 3: n values of the second list

Output format:
The merged first list, containing m + n values.

Sample input:
3 3
1 2 3 0 0 0
2 5 6

Sample output:
1 2 2 3 5 6
*/
void solveQ05(vector<int>& first, int m, const vector<int>& second, int n) {
    // TODO: Write your code here.
}

// ============================================================
// QUESTION 06
// ============================================================
/*
Difficulty: Easy

Scenario:
A feature-flag array contains zeroes followed by ones. Find the first array
position at which a feature is enabled.

Constraints:
- 0 <= n <= 200000
- Each element is either 0 or 1.
- The array is sorted: all zeroes appear before all ones.
- Return -1 if the array contains no one.

Input format:
Line 1: n
Line 2: n space-separated values (may be empty when n = 0)

Output format:
The 0-based index of the first 1, or -1.

Sample input:
5
0 0 0 1 1

Sample output:
3
*/
int solveQ06(const vector<int>& nums) {
    // TODO: Write your code here.
    return -1;
}

// ============================================================
// QUESTION 07
// ============================================================
/*
Difficulty: Easy

Scenario:
A monitoring dashboard receives daily profit/loss values. Find the largest
sum obtainable from one non-empty contiguous period of days.

Constraints:
- 1 <= n <= 200000
- -10000 <= nums[i] <= 10000
- The selected subarray must contain at least one element.

Input format:
Line 1: n
Line 2: n space-separated integers

Output format:
The maximum contiguous subarray sum.

Sample input:
9
-2 1 -3 4 -1 2 1 -5 4

Sample output:
6
*/
long long solveQ07(const vector<int>& nums) {
    // TODO: Write your code here.
    return 0;
}

// ============================================================
// QUESTION 08
// ============================================================
/*
Difficulty: Easy

Scenario:
A trader is given the share price for each day. Choose one day to buy and a
later day to sell. Find the maximum possible profit. If no profitable trade
exists, return zero.

Constraints:
- 1 <= n <= 200000
- 0 <= prices[i] <= 1000000000
- The buy day must be strictly earlier than the sell day.
- At most one buy and one sell are allowed.

Input format:
Line 1: n
Line 2: n space-separated daily prices

Output format:
The maximum achievable profit.

Sample input:
6
7 1 5 3 6 4

Sample output:
5
*/
long long solveQ08(const vector<int>& prices) {
    // TODO: Write your code here.
    return 0;
}

// ============================================================
// QUESTION 09
// ============================================================
/*
Difficulty: Easy

Scenario:
A data-cleaning step must move all zero readings to the end of an array while
keeping the relative order of every non-zero reading unchanged. Modify the
array in place.

Constraints:
- 0 <= n <= 200000
- -1000000000 <= nums[i] <= 1000000000
- Preserve the relative order of non-zero elements.
- Do not create another array for the result.

Input format:
Line 1: n
Line 2: n space-separated integers

Output format:
The modified array.

Sample input:
5
0 1 0 3 12

Sample output:
1 3 12 0 0
*/
void solveQ09(vector<int>& nums) {
    // TODO: Write your code here.
}

// ============================================================
// QUESTION 10
// ============================================================
/*
Difficulty: Medium

Scenario:
A monitoring system has n sensors. For each sensor, calculate the product of
all readings except that sensor's own reading. Division is not allowed.

Constraints:
- 2 <= n <= 100000
- -30 <= nums[i] <= 30
- Every required output product fits in a signed 64-bit integer.
- Do not use division.

Input format:
Line 1: n
Line 2: n space-separated integers

Output format:
The n resulting products in order.

Sample input:
4
1 2 3 4

Sample output:
24 12 8 6
*/
vector<long long> solveQ10(const vector<int>& nums) {
    // TODO: Write your code here.
    return {};
}

// ============================================================
// QUESTION 11
// ============================================================
/*
Difficulty: Medium

Scenario:
A service receives event sequence numbers in arbitrary order. Find the
length of the longest run of consecutive integer values, even if the values
are not next to each other in the input.

Constraints:
- 0 <= n <= 200000
- -1000000000 <= nums[i] <= 1000000000
- Duplicate values may occur.

Input format:
Line 1: n
Line 2: n space-separated integers

Output format:
The length of the longest consecutive run. Print 0 for an empty array.

Sample input:
6
100 4 200 1 3 2

Sample output:
4
*/
int solveQ11(const vector<int>& nums) {
    // TODO: Write your code here.
    return 0;
}

// ============================================================
// QUESTION 12
// ============================================================
/*
Difficulty: Medium

Scenario:
A transaction stream contains positive and negative adjustments. Count the
number of contiguous ranges whose total adjustment is exactly k.

Constraints:
- 1 <= n <= 200000
- -1000000000 <= nums[i] <= 1000000000
- -1000000000000 <= k <= 1000000000000
- The answer can exceed the range of a 32-bit integer.

Input format:
Line 1: n k
Line 2: n space-separated integers

Output format:
The number of contiguous subarrays with sum exactly k.

Sample input:
3 2
1 1 1

Sample output:
2
*/
long long solveQ12(const vector<int>& nums, long long k) {
    // TODO: Write your code here.
    return 0;
}

// ============================================================
// QUESTION 13
// ============================================================
/*
Difficulty: Medium

Scenario:
A finance system stores signed adjustments. Find every unique group of three
different array positions whose values add up to zero. The same value may be
used more than once only when it occurs at different positions.

Constraints:
- 3 <= n <= 3000
- -100000 <= nums[i] <= 100000
- Each returned triplet must be in non-decreasing order.
- Do not return duplicate triplets.

Input format:
Line 1: n
Line 2: n space-separated integers

Output format:
Print each unique triplet on its own line. Print - if none exist.

Sample input:
6
-1 0 1 2 -1 -4

Sample output (order of triplets may differ):
-1 -1 2
-1 0 1
*/
vector<vector<int>> solveQ13(const vector<int>& nums) {
    // TODO: Write your code here.
    return {};
}

// ============================================================
// QUESTION 14
// ============================================================
/*
Difficulty: Medium

Scenario:
A user token is a string. Find the length of its longest contiguous portion
in which no character appears more than once.

Constraints:
- 0 <= length of s <= 200000
- s contains standard ASCII characters.
- The answer is 0 for an empty string.

Input format:
One string s (without spaces; an empty line represents an empty string).

Output format:
The maximum length of a substring with all distinct characters.

Sample input:
abcabcbb

Sample output:
3
*/
int solveQ14(const string& s) {
    // TODO: Write your code here.
    return 0;
}

// ============================================================
// QUESTION 15
// ============================================================
/*
Difficulty: Medium

Scenario:
A workflow consists of tasks with positive durations. Find the shortest
contiguous group of tasks whose total duration is at least the target.
Return zero if no such group exists.

Constraints:
- 1 <= n <= 200000
- 1 <= nums[i] <= 10000
- 1 <= target <= 1000000000
- All array values are positive, as required by this problem's expected
  approach.

Input format:
Line 1: target n
Line 2: n space-separated positive integers

Output format:
The minimum length of a valid contiguous group, or 0 if none exists.

Sample input:
7 6
2 3 1 2 4 3

Sample output:
2
*/
int solveQ15(int target, const vector<int>& nums) {
    // TODO: Write your code here.
    return 0;
}

// ============================================================
// QUESTION 16
// ============================================================
/*
Difficulty: Medium

Scenario:
A monitoring service records system load every minute. For every consecutive
window of k minutes, report the highest load in that window.

Constraints:
- 1 <= n <= 200000
- 1 <= k <= n
- -1000000000 <= nums[i] <= 1000000000

Input format:
Line 1: n k
Line 2: n space-separated integers

Output format:
The maximum value from each window, from left to right.

Sample input:
8 3
1 3 -1 -3 5 3 6 7

Sample output:
3 3 5 5 6 7
*/
vector<int> solveQ16(const vector<int>& nums, int k) {
    // TODO: Write your code here.
    return {};
}

// ============================================================
// QUESTION 17
// ============================================================
/*
Difficulty: Medium

Scenario:
A registration system receives usernames. Usernames that contain exactly
the same letters, with the same counts but in a different order, belong in
the same group.

Constraints:
- 1 <= number of words <= 10000
- 0 <= length of each word <= 100
- Each word contains lowercase English letters only.
- The order of groups in the output does not matter.

Input format:
Line 1: n
Next n lines: one word per line

Output format:
Print each group on a separate line. Words within a group may be printed
in any order. Groups may also be printed in any order.

Sample input:
6
eat
tea
tan
ate
nat
bat

Sample output (group order may differ):
eat tea ate
tan nat
bat
*/
vector<vector<string>> solveQ17(const vector<string>& words) {
    // TODO: Write your code here.
    return {};
}

// ============================================================
// QUESTION 18
// ============================================================
/*
Difficulty: Medium

Scenario:
A log-analysis service must report the k error codes that occur most often.
If multiple values have the same frequency at the cutoff, any valid selection
among those tied values is acceptable.

Constraints:
- 1 <= n <= 200000
- 1 <= k <= number of distinct values in nums
- -1000000000 <= nums[i] <= 1000000000

Input format:
Line 1: n k
Line 2: n space-separated integers

Output format:
The k most frequent values in any valid order.

Sample input:
6 2
1 1 1 2 2 3

Sample output:
1 2
*/
vector<int> solveQ18(const vector<int>& nums, int k) {
    // TODO: Write your code here.
    return {};
}

// ============================================================
// QUESTION 19
// ============================================================
/*
Difficulty: Medium

Scenario:
A trading platform stores transaction amounts. Find the kth largest amount
without requiring the full list to be sorted.

Constraints:
- 1 <= n <= 200000
- 1 <= k <= n
- -1000000000 <= nums[i] <= 1000000000
- Duplicate values count as separate positions when determining the rank.

Input format:
Line 1: n k
Line 2: n space-separated integers

Output format:
The kth largest value.

Sample input:
6 2
3 2 1 5 6 4

Sample output:
5
*/
int solveQ19(const vector<int>& nums, int k) {
    // TODO: Write your code here.
    return 0;
}

// ============================================================
// QUESTION 20
// ============================================================
/*
Difficulty: Medium

Scenario:
A deployment planner receives time intervals. Combine every interval that
overlaps another interval. Intervals that touch at an endpoint are treated
as overlapping for this question.

Constraints:
- 0 <= number of intervals <= 200000
- Each interval is [start, end], where start <= end.
- Input intervals need not be sorted.

Input format:
Line 1: n
Next n lines: start end

Output format:
Print the merged intervals in increasing order of start time.

Sample input:
4
1 3
2 6
8 10
15 18

Sample output:
1 6
8 10
15 18
*/
vector<vector<int>> solveQ20(const vector<vector<int>>& intervals) {
    // TODO: Write your code here.
    return {};
}

// ============================================================
// QUESTION 21
// ============================================================
/*
Difficulty: Medium

Scenario:
A company schedules meetings with start and end times. Determine the minimum
number of rooms needed so that no two meetings assigned to the same room
conflict.

Constraints:
- 0 <= number of meetings <= 200000
- Each meeting is [start, end], with start < end.
- Meetings are treated as half-open intervals [start, end). A room can be
  reused when one meeting ends exactly as another begins.

Input format:
Line 1: n
Next n lines: start end

Output format:
The minimum number of rooms required.

Sample input:
3
0 30
5 10
15 20

Sample output:
2
*/
int solveQ21(const vector<vector<int>>& meetings) {
    // TODO: Write your code here.
    return 0;
}

// ============================================================
// QUESTION 22
// ============================================================
/*
Difficulty: Medium

Scenario:
A release manager has deployment windows that may overlap. Find the minimum
number of windows that must be removed so that the remaining windows do not
overlap.

Constraints:
- 0 <= number of intervals <= 200000
- Each interval is [start, end], with start < end.
- Intervals that touch at an endpoint do not overlap.

Input format:
Line 1: n
Next n lines: start end

Output format:
The minimum number of intervals to remove.

Sample input:
4
1 2
2 3
3 4
1 3

Sample output:
1
*/
int solveQ22(const vector<vector<int>>& intervals) {
    // TODO: Write your code here.
    return 0;
}

// ============================================================
// QUESTION 23
// ============================================================
/*
Difficulty: Medium

Scenario:
A sorted list of device identifiers has been rotated at an unknown position.
Find the index of a requested identifier, or report that it is absent.

Constraints:
- 0 <= n <= 100000
- Values are distinct.
- The original array was sorted in strictly increasing order before rotation.

Input format:
Line 1: n target
Line 2: n space-separated integers

Output format:
The 0-based index of target, or -1 if it is absent.

Sample input:
7 0
4 5 6 7 0 1 2

Sample output:
4
*/
int solveQ23(const vector<int>& nums, int target) {
    // TODO: Write your code here.
    return -1;
}

// ============================================================
// QUESTION 24
// ============================================================
/*
Difficulty: Medium

Scenario:
A product catalogue stores product IDs in sorted order, including duplicates.
For a requested ID, return the first and last positions where it appears.

Constraints:
- 0 <= n <= 200000
- The array is sorted in non-decreasing order.
- -1000000000 <= nums[i], target <= 1000000000
- Return [-1, -1] if target is absent.

Input format:
Line 1: n target
Line 2: n space-separated integers

Output format:
Two 0-based indices: first position and last position.

Sample input:
6 8
5 7 7 8 8 10

Sample output:
3 4
*/
vector<int> solveQ24(const vector<int>& nums, int target) {
    // TODO: Write your code here.
    return {-1, -1};
}

// ============================================================
// QUESTION 25
// ============================================================
/*
Difficulty: Medium

Scenario:
A processing system has several batches. A worker processes one batch at a
time at a fixed positive rate. Find the minimum rate that allows all batches
to be completed within h hours. A partially processed batch still consumes
one full hour.

Constraints:
- 1 <= number of batches <= 100000
- 1 <= piles[i] <= 1000000000
- number of available hours h >= number of batches
- h <= 1000000000

Input format:
Line 1: n h
Line 2: n space-separated batch sizes

Output format:
The minimum feasible positive processing rate.

Sample input:
4 8
3 6 7 11

Sample output:
4
*/
int solveQ25(const vector<int>& piles, int h) {
    // TODO: Write your code here.
    return 0;
}

// ============================================================
// QUESTION 26
// ============================================================
/*
Difficulty: Medium

Scenario:
A weather service records the temperature each day. For every day, find how
many days must pass until a strictly warmer temperature occurs. Return zero
when no warmer day appears later in the recorded data.

Constraints:
- 1 <= n <= 100000
- 30 <= temperatures[i] <= 100

Input format:
Line 1: n
Line 2: n space-separated temperatures

Output format:
The number of days to wait for each day, in the original order.

Sample input:
8
73 74 75 71 69 72 76 73

Sample output:
1 1 4 2 1 1 0 0
*/
vector<int> solveQ26(const vector<int>& temperatures) {
    // TODO: Write your code here.
    return {};
}

// ============================================================
// QUESTION 27
// ============================================================
/*
Difficulty: Medium

Scenario:
Sensor readings are arranged in a circle. For each reading, move forward
through the circular order and find the first value that is strictly greater.
If no greater value exists, return -1 for that position.

Constraints:
- 1 <= n <= 200000
- -1000000000 <= nums[i] <= 1000000000
- The scan may wrap around to the beginning, but it must not inspect more than
  one full cycle after the starting position.

Input format:
Line 1: n
Line 2: n space-separated integers

Output format:
The next strictly greater value for each position, or -1.

Sample input:
3
1 2 1

Sample output:
2 -1 2
*/
vector<int> solveQ27(const vector<int>& nums) {
    // TODO: Write your code here.
    return {};
}

// ============================================================
// QUESTION 28
// ============================================================
/*
Difficulty: Medium

Scenario:
Implement a stack for a monitoring application. It must support push, pop,
reading the top value, and retrieving the minimum value currently stored.
Each operation must be efficient.

Constraints:
- 1 <= number of operations <= 200000
- -1000000000 <= pushed value <= 1000000000
- pop, top and getMin are called only when the stack is non-empty.

Input format:
Line 1: q, the number of operations
Next q lines: one of the following:
    push x
    pop
    top
    getMin

Output format:
Print one line for every top or getMin operation. Print nothing for push
and pop operations.

Sample input:
7
push -2
push 0
push -3
getMin
pop
top
getMin

Sample output:
-3
0
-2
*/
class Question28 {
public:
    void push(int x) {
        // TODO: Write your code here.
    }

    void pop() {
        // TODO: Write your code here.
    }

    int top() {
        // TODO: Write your code here.
        return 0;
    }

    int getMin() {
        // TODO: Write your code here.
        return 0;
    }
};

// ============================================================
// QUESTION 29
// ============================================================
/*
Difficulty: Medium

Scenario:
A singly linked list stores processing tasks in sequence. Reverse the list
in place and return the new head, without creating a second list.

Constraints:
- 0 <= number of nodes <= 100000
- -1000000000 <= node value <= 1000000000
- The list contains no cycle.

Input format:
Line 1: n
Line 2: n space-separated node values (may be empty when n = 0)

Output format:
Print the node values from the new head to the end.

Sample input:
4
1 2 3 4

Sample output:
4 3 2 1
*/
ListNode* solveQ29(ListNode* head) {
    // TODO: Write your code here.
    return nullptr;
}

// ============================================================
// QUESTION 30
// ============================================================
/*
Difficulty: Medium

Scenario:
An event-processing chain is expected to move forward and eventually end.
Due to a data corruption issue, the last node may point back to an earlier
node. Determine whether the linked list contains a cycle.

Constraints:
- 0 <= number of nodes <= 100000
- -1000000000 <= node value <= 1000000000
- pos is -1 when there is no cycle; otherwise 0 <= pos < n and the tail points
  to the node at index pos.
- Do not modify the linked list while checking it.

Input format:
Line 1: n pos
Line 2: n space-separated node values

Output format:
Print true if the list contains a cycle; otherwise print false.

Sample input:
3 1
1 2 3

Sample output:
true
*/
bool solveQ30(ListNode* head) {
    // TODO: Write your code here.
    return false;
}

// ============================================================
// READY-MADE MAIN: CHANGE ACTIVE_QUESTION TO 1..30
// ============================================================

int main() {
    cout << boolalpha;

    if constexpr (ACTIVE_QUESTION == 1) {
    {
        vector<int> nums = {2, 7, 11, 15};
        printVector(solveQ01(nums, 9));
        cout << "\nExpected: [0, 1]\n";
    }
    } else if constexpr (ACTIVE_QUESTION == 2) {
    cout << solveQ02("aabbcdeff") << "\nExpected: 4\n";
    } else if constexpr (ACTIVE_QUESTION == 3) {
    cout << solveQ03(12321) << "\nExpected: true\n";
    } else if constexpr (ACTIVE_QUESTION == 4) {
    cout << solveQ04("{[()]}") << "\nExpected: true\n";
    } else if constexpr (ACTIVE_QUESTION == 5) {
    {
        vector<int> first = {1, 2, 3, 0, 0, 0};
        vector<int> second = {2, 5, 6};
        solveQ05(first, 3, second, 3);
        printVector(first);
        cout << "\nExpected: [1, 2, 2, 3, 5, 6]\n";
    }
    } else if constexpr (ACTIVE_QUESTION == 6) {
    cout << solveQ06({0, 0, 0, 1, 1}) << "\nExpected: 3\n";
    } else if constexpr (ACTIVE_QUESTION == 7) {
    cout << solveQ07({-2, 1, -3, 4, -1, 2, 1, -5, 4})
         << "\nExpected: 6\n";
    } else if constexpr (ACTIVE_QUESTION == 8) {
    cout << solveQ08({7, 1, 5, 3, 6, 4}) << "\nExpected: 5\n";
    } else if constexpr (ACTIVE_QUESTION == 9) {
    {
        vector<int> nums = {0, 1, 0, 3, 12};
        solveQ09(nums);
        printVector(nums);
        cout << "\nExpected: [1, 3, 12, 0, 0]\n";
    }
    } else if constexpr (ACTIVE_QUESTION == 10) {
    printVector(solveQ10({1, 2, 3, 4}));
    cout << "\nExpected: [24, 12, 8, 6]\n";
    } else if constexpr (ACTIVE_QUESTION == 11) {
    cout << solveQ11({100, 4, 200, 1, 3, 2}) << "\nExpected: 4\n";
    } else if constexpr (ACTIVE_QUESTION == 12) {
    cout << solveQ12({1, 1, 1}, 2) << "\nExpected: 2\n";
    } else if constexpr (ACTIVE_QUESTION == 13) {
    printIntMatrix(solveQ13({-1, 0, 1, 2, -1, -4}));
    cout << "\nExpected: [[-1, -1, 2], [-1, 0, 1]]\n";
    } else if constexpr (ACTIVE_QUESTION == 14) {
    cout << solveQ14("abcabcbb") << "\nExpected: 3\n";
    } else if constexpr (ACTIVE_QUESTION == 15) {
    cout << solveQ15(7, {2, 3, 1, 2, 4, 3}) << "\nExpected: 2\n";
    } else if constexpr (ACTIVE_QUESTION == 16) {
    printVector(solveQ16({1, 3, -1, -3, 5, 3, 6, 7}, 3));
    cout << "\nExpected: [3, 3, 5, 5, 6, 7]\n";
    } else if constexpr (ACTIVE_QUESTION == 17) {
    printStringGroups(solveQ17({"eat", "tea", "tan", "ate", "nat", "bat"}));
    cout << "\nExpected: [[ate, eat, tea], [bat], [nat, tan]]\n";
    } else if constexpr (ACTIVE_QUESTION == 18) {
    {
        vector<int> answer = solveQ18({1, 1, 1, 2, 2, 3}, 2);
        sort(answer.begin(), answer.end());
        printVector(answer);
        cout << "\nExpected: [1, 2]\n";
    }
    } else if constexpr (ACTIVE_QUESTION == 19) {
    cout << solveQ19({3, 2, 1, 5, 6, 4}, 2) << "\nExpected: 5\n";
    } else if constexpr (ACTIVE_QUESTION == 20) {
    printIntervals(solveQ20({{1, 3}, {2, 6}, {8, 10}, {15, 18}}));
    cout << "\nExpected: [[1, 6], [8, 10], [15, 18]]\n";
    } else if constexpr (ACTIVE_QUESTION == 21) {
    cout << solveQ21({{0, 30}, {5, 10}, {15, 20}}) << "\nExpected: 2\n";
    } else if constexpr (ACTIVE_QUESTION == 22) {
    cout << solveQ22({{1, 2}, {2, 3}, {3, 4}, {1, 3}})
         << "\nExpected: 1\n";
    } else if constexpr (ACTIVE_QUESTION == 23) {
    cout << solveQ23({4, 5, 6, 7, 0, 1, 2}, 0) << "\nExpected: 4\n";
    } else if constexpr (ACTIVE_QUESTION == 24) {
    printVector(solveQ24({5, 7, 7, 8, 8, 10}, 8));
    cout << "\nExpected: [3, 4]\n";
    } else if constexpr (ACTIVE_QUESTION == 25) {
    cout << solveQ25({3, 6, 7, 11}, 8) << "\nExpected: 4\n";
    } else if constexpr (ACTIVE_QUESTION == 26) {
    printVector(solveQ26({73, 74, 75, 71, 69, 72, 76, 73}));
    cout << "\nExpected: [1, 1, 4, 2, 1, 1, 0, 0]\n";
    } else if constexpr (ACTIVE_QUESTION == 27) {
    printVector(solveQ27({1, 2, 1}));
    cout << "\nExpected: [2, -1, 2]\n";
    } else if constexpr (ACTIVE_QUESTION == 28) {
    {
        Question28 st;
        st.push(-2);
        st.push(0);
        st.push(-3);
        cout << st.getMin() << "\n";
        st.pop();
        cout << st.top() << "\n";
        cout << st.getMin() << "\n";
        cout << "Expected: -3, 0, -2 (one value per line)\n";
    }
    } else if constexpr (ACTIVE_QUESTION == 29) {
    {
        ListNode* head = buildList({1, 2, 3, 4});
        ListNode* answer = solveQ29(head);
        printList(answer);
        cout << "\nExpected: [4 -> 3 -> 2 -> 1]\n";
        deletePossiblyCyclicList(answer);
    }
    } else if constexpr (ACTIVE_QUESTION == 30) {
    {
        ListNode* head = buildListWithCycle({1, 2, 3}, 1);
        cout << solveQ30(head) << "\nExpected: true\n";
        deletePossiblyCyclicList(head);
    }
    } else {
    }

    return 0;
}
