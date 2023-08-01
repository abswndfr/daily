#include <vector>
#include <iostream>

using namespace std;

// 8.1 

/*       
// https://github.com/careercup/CtCI-6th-Edition-cpp/blob/master/chapter-8-recursion-and-Dynamic-Programming/8-1-Triple-Step.cpp    
int countWays(int n, vector<int> v) {

	if (n == 0) {
		return 1;
	}

	int sum = 0;

	for (int i = 0; i < v.size(); ++i)
	{
		if (n >= v[i]) {
			sum = sum + countWays((n - v[i]), v);
		}
	}
	return sum;
}

int main(int argc, char const* argv[])
{
	vector<int> v;	// vector to store possible step sizes
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);

	int noOfWays = countWays(6, v);
	cout << noOfWays << endl;	// Total number of stairs = 6

	return 0;
}

// https://github.com/alexhagiopol/cracking-the-coding-interview/blob/master/cpp_solutions/chapter_08_recursion_and_dynamic_programming/problem_08_01_tripleStep.cpp
#if 0
#include "problem_08_01_tripleStep.h"

        #pragma once
        #include <vector>
        
        namespace chapter_08{
            int tripleStep(int n);
        }
#endif
//namespace chapter_08 {
    int tripleStep(int n, std::vector<long> memo) {
        if (n == 0) {
            return 0;
        }
        if (n == 1) {
            return 1;
        }
        if (n == 2) {
            return 2;
        }
        if (n == 3) {
            return 4;
        }
        if (memo[n] == 0) {
            memo[n] = tripleStep(n - 3, memo) + tripleStep(n - 2, memo) + tripleStep(n - 1, memo);
        }
        return memo[n];
    }

    int tripleStep(int n) {
        std::vector<long> memo(n + 1, 0);
        return tripleStep(n, memo);
    }
//}

int main() 
{
    //printf("3->%d\n", tripleStep(3));
    //printf("4->%d\n", tripleStep(4));
    //printf("5->%d\n", tripleStep(5));
    printf("6->%d\n", tripleStep(6));

    return 0;
}*/

/*
#define DP_SIZE 10

int dp[DP_SIZE];

int countWays(int n)
{
    if (dp[n] != 0) {
        return dp[n];
    }
    else {
        dp[n] = countWays(n-1) + countWays(n-2) + countWays(n-3);
        return dp[n];
    }
}*/

#define 	DP_SIZE		10
int dp[DP_SIZE];

int stairCount(int steps)
{
    if (dp[steps] != 0) {
        return dp[steps];
    }
    else {
        return stairCount(steps - 1) + stairCount(steps - 2) + stairCount(steps - 3);
    }
}


//Question 8.2 C++ contrasting solution
// https://github.com/careercup/CtCI-6th-Edition-cpp/blob/master/chapter-8-recursion-and-Dynamic-Programming/8-2-Robot-in-a-Grid.cpp
#include <vector>
#include <iostream>
#include <unordered_set>

using namespace std;

struct Point {
    int row;
    int column;
    Point(int r, int c) : row(r), column(c) {}
};

//////////////////////////////////////////////////////
//Implementation with memoization/caching
//////////////////////////////////////////////////////

//Checks if path is valid and simultaneously adds position to a result vector
//bool getPath(int** matrix, int currRow, int currColumn, vector<Point*>& path, unordered_set<Point*>& duplicateVisits) {
//
//    //if out of bounds or curr position is off limits, return false
//    if (currRow < 0 || currColumn < 0 || matrix[currRow][currColumn] == -1) {
//        return false;
//    }
//
//    Point* currPos = new Point(currRow, currColumn);
//
//    //If we have already visited this position, then return false
//    if (duplicateVisits.find(currPos) != duplicateVisits.end()) {
//        return false;
//    }
//
//
//    bool atOrigin = currRow == 0 && currColumn == 0;
//
//    //Everytime robot moves up or left and it is a valid position, add the point to result vector
//    if (atOrigin || getPath(matrix, currRow - 1, currColumn, path, duplicateVisits) || getPath(matrix, currRow, currColumn - 1, path, duplicateVisits)) {
//        path.push_back(currPos);
//        return true;
//    }
//
//    //Keep track of already visited points
//    duplicateVisits.insert(currPos);
//
//    return false;
//}
//
//vector<Point*> getPath(int** matrix, int rows, int columns) {
//    //create result vector
//    vector<Point*> path;
//
//    //create unordered set to keep track of already visited points
//    unordered_set<Point*> duplicateVisits;
//
//    //Bounds checking
//    if (rows != 0 || matrix != nullptr) {
//        //Start checking positions from bottom right to top left
//        if (getPath(matrix, rows - 1, columns - 1, path, duplicateVisits)) {
//            return path;
//        }
//    }
//    //Return an empty vector indicating path does not exist
//    return path;
//}

//////////////////////////////////////////////////////
//Implementation without memoization/caching
//////////////////////////////////////////////////////
//Checks if path is valid and simultaneously adds position to a result vector
#if 1   
/*7/26/2023
bool getPath(int** matrix, int currRow, int currColumn, vector<Point*>& path) 
{
    if ((currRow < 0) || (currColumn < 0) || !matrix[currRow][currColumn]) {
        return false;
    }
    printf("[+]%d %d\n", currRow, currColumn);
    bool isOrigin = (currRow == 0) && (currColumn == 0);

    if (isOrigin || getPath(matrix, currRow - 1, currColumn, path) || getPath(matrix, currRow, currColumn - 1, path)) {
        Point* pt = new Point(currRow, currColumn);
        printf("[-]%d %d\n", currRow, currColumn);
        path.push_back(pt);
        return true;
    }

    return false;
}

vector<Point*> getPath(int** matrix, int rows, int columns) {
    vector<Point*> path;

    if ((matrix == nullptr) || (rows == 0)) {
        return path;
    } 

    if (getPath(matrix, rows - 1, columns - 1, path)) {
        return path;
    }

    return path;
}
*/
/* 7/27/2023
bool getPath(int **matrix, int row, int col, vector<Point*> &path)
{
    if ((row<0) || (col<0) || (matrix[row][col] == 0)) {
        return false;
    }

    bool isOrigin = (row == 0) && (col == 0);

    if (isOrigin || getPath(matrix, row - 1, col, path) || getPath(matrix, row, col - 1, path)) {

        Point* pt = new Point(row, col);
        path.push_back(pt);

        return true;
    }
   
    return false;
}

vector<Point*> findPath(int** matrix, int row, int col)
{
    vector<Point*> path;

    if ((row == 0) || (col == 0) || (matrix == nullptr)) {
        return path;
    }
    else {
        getPath(matrix, row - 1, col - 1, path);
    }

    return path;
}
*/
// 7/28/2023
bool getPath(int** matrix, int row, int col, vector<Point*>& path)
{
    if ((row < 0) || (col < 0) || (matrix[row][col] == 0)) {
        return false;
    }

    bool isOrigin = (row == 0) && (col == 0);

    if (isOrigin || getPath(matrix, row - 1, col, path) || getPath(matrix, row, col - 1, path)) {
        Point* pt = new Point(row, col);
        path.push_back(pt);
        return true;
    }

    return false;
}

vector<Point*> getPath(int** matrix, int row, int col)
{
    vector<Point*> path;

    if ((matrix == nullptr) || (row == 0) || (col == 0)) {
        return path;
    }

    getPath(matrix, row-1, col-1, path);

    return path;
}
#else   // Careercup org
bool getPath(int** matrix, int currRow, int currColumn, vector<Point*>& path){
    
    //if out of bounds or curr position is off limits, return false
    if (currRow < 0 || currColumn < 0 || matrix[currRow][currColumn] == -1){
        return false;
    }
    
    bool atOrigin = currRow == 0 && currColumn == 0;
    
    //Everytime robot moves up or left and it is a valid position, add the point to result vector
    if (atOrigin || getPath(matrix, currRow-1, currColumn, path) || getPath(matrix, currRow, currColumn-1, path)) {
        Point* currPos = new Point(currRow, currColumn);
        path.push_back(currPos);
        return true;
    }
    return false;
}

vector<Point*> getPath(int** matrix, int rows, int columns){
    //create result vector
    vector<Point*> path;
    
    //Bounds checking
    if (rows != 0 || matrix != nullptr){
        //Start checking positions from bottom-right
        if (getPath(matrix, rows - 1, columns - 1, path)){
            return path;
        }
    }

    //Otherwise return an empty vector indicating path does not exist
    return path;
}
#endif

int** createMatrix(int rows, int columns) {
    //initialize number of rows
    int** matrix = new int* [rows];

    //in each row, add a new column array
    for (int i = 0; i < rows; ++i) {
        matrix[i] = new int[columns];
    }

    //place values (1 indicates position is valid, -1 indicates it is invalid)
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            matrix[i][j] = 1;
        }
    }
    return matrix;

}


/*
// https://github.com/black-shadows/Cracking-the-Coding-Interview/blob/master/Solutions/Chapter%208%20Recursion/8.2.cpp

*Q 8.2 Image a robot sitting on the upper lest corner of an N*N grid.The robot can only move in two directions:
 *right and down.How many possible paths are there for the robot?
 */

#include <iostream>
#include <cstdio>
#include <stack>
using namespace std;

typedef long long ll;
typedef struct point
{
    int x, y;
}point;

stack<point> sp;
const int MAXN = 20;
int g[MAXN][MAXN];
point vp[MAXN + MAXN];

ll path(ll m, ll n)
{
    if (m == 1 || n == 1) return 1; // if m or n == 1, then there's only one way to reach the point from origin.
    else return path(m - 1, n) + path(m, n - 1);
}

ll fact(ll n)
{
    if (n == 0) return 1;
    else return n * fact(n - 1);
}

ll path1(ll m, ll n)
{
    return fact(m - 1 + n - 1) / (fact(m - 1) * fact(n - 1));
}

bool get_path(int m, int n) // backward : M,N -> origin
{
    point p; p.x = n; p.y = m;

    //printf("c:%d, r:%d\n", n, m);
    printf("r:%d, c:%d\n", m, n);

    sp.push(p);
    if (n == 1 && m == 1) return true;

    bool suc = false;

    if (m > 1 && g[m - 1][n])               suc = get_path(m - 1, n);

    if (!suc && n > 1 && g[m][n - 1])       suc = get_path(m, n - 1);

    if (!suc) sp.pop();

    return suc;
}

void print_paths(int m, int n, int M, int N, int len)   // all paths : origin -> M,N.  len points at where to restart !
{
    if (g[m][n] == 0) return;

    point p; p.x = n; p.y = m;

    vp[len++] = p;

    if (m == M && n == N)
    {
        for (int i = 0; i < len; ++i)
            cout << "(" << vp[i].y << "," << vp[i].x << ")" << " ";
        cout << endl;
    }
    else
    {
        print_paths(m, n + 1, M, N, len);
        print_paths(m + 1, n, M, N, len);
    }
}



// 8.3


// 8.4

// https://github.com/careercup/CtCI-6th-Edition-cpp/blob/master/chapter-8-recursion-and-Dynamic-Programming/8.4_Power_Set.cpp
// We use the solution 2 described in the book.
// Namely, for a set with length n, we simply iterate over all binary numbers with n bits.
// For each number, the corresponding set is constrcted as follows:
// if ith position is 1, then we put ith element into the set. 
// otherwise, we do not select ith element.
// Each number corresponds exactly to one set.
#include <stdio.h>
#include <math.h>
#include <iostream>

void printPowerSet(char* set, int set_size)
{
    //set_size of power set of a set with set_size n is 2**n, empty set included
    unsigned int pow_set_size = pow(2, set_size);
    int counter, j;

    // Run from counter 000..0 to 111..1
    for (counter = 0; counter < pow_set_size; counter++)
    {
        printf("%2d:", counter);
        for (j = 0; j < set_size; j++)
        {
            // Check if jth bit in the counter is set If set then print jth element from set 
            if (counter & (1 << j))             //shift 1 to the jth position,

                //counter & (1<<j) extracts the jth element of this binary number
                printf("%c", set[j]);
        }

        printf("\n");
    }
}

/* CtCI Q8.4 1st sol'n : recursive
// https://github.com/alexhagiopol/cracking-the-coding-interview/blob/master/cpp_solutions/chapter_08_recursion_and_dynamic_programming/problem_08_04_powerSet.cpp
void createPowerSet(vector<int> set, vector<int>& powerSet) {

    if (set.size() == 0) {
        vector<int> emptySet = {};
        powerSet.push_back(emptySet);
        return;
    }

    int lastElement = set.back();
    set.pop_back();
    vector<int> newSets = {};
    createPowerSet(set, powerSet);


    for (auto subproblemSet : powerSet) {
        subproblemSet.push_back(lastElement);
        newSets.push_back(subproblemSet);
    }

    powerSet.insert(powerSet.end(), newSets.begin(), newSets.end());
};*/

// Q8.4 Write a method that returns all subsets of a set.
// https://github.com/black-shadows/Cracking-the-Coding-Interview/blob/master/Solutions/Chapter%208%20Recursion/8.3.cpp

#include <iostream>
#include <vector>
using namespace std;

typedef vector<vector<int>> vvi;
typedef vector<int> vi;

void print_subset(vi subset)
{
    cout << "______";
    for (int i = 0; i < subset.size(); ++i)
    {
        cout << subset[i] << " ";
    }
    cout << endl;
}

void print_subsets(vvi subsets)
{
    cout << "=======\n";
    for (int i = 0; i < subsets.size(); ++i)
    {
        vi subset = subsets[i];
        printf(".");
        for (int j = 0; j < subset.size(); ++j)
        {
            cout << subset[j] << " ";
        }
        cout << endl;
    }
}

// CtCI Q8.4 1nd sol'n : recursive
vvi get_subsets1(int a[], int idx, int n)
{
    vvi subsets;                                            // Arraylist<Arraylist<Integer>> allsubsets;
    if (idx == n)                                           // if (set.size()== index) {	//Base case - add empty set
    {                                                       //
        vi subset;                                          // allsubsets = new Arraylist<Arraylist<Integer>>();
        subsets.push_back(subset);//empty set               // allsubsets.add(new Arraylist<Integer>()); 	// Empty set
        printf("%d: sss size:%d ", idx, subsets.size());
        print_subset(subset);
    }
    else
    {
        vvi rsubsets = get_subsets1(a, idx + 1, n);         // allsubsets = getSubsets(set, index+ 1);		// allsubset <- getSubsets	
        printf("%d: sss size:%d ", idx, rsubsets.size());
        print_subsets(rsubsets);
        int v = a[idx];                                     // int item= set.get(index);
        for (int i = 0; i < rsubsets.size(); ++i)           // for (Arraylist<Integer> subset : allsubsets) {// for subset in allsubsets
        {
            vi subset = rsubsets[i];                        // 
            subsets.push_back(subset);  // without v        // newsubset.addAll(subset);
            printf("%d:", idx);
            print_subset(subset);
            subset.push_back(v);                            // newsubset.add(item);	             // newsubset = subset + item
            subsets.push_back(subset);  // with v           // moresubsets.add(newsubset);	     // moresubset += newsubset 
            printf("%d:", idx);
            print_subset(subset);
        }                                                   // allsubsets.addAll(moresubsets);   // allsubset += moresubset
    }
    return subsets;
}

// CtCI Q8.4 2nd sol'n : convert to binary and add elements at the postion of 1 of j.
vvi get_subsets(int a[], int n)
{
    vvi subsets;
    int max = 1 << n;
    for (int i = 0; i < max; ++i)
    {
        vi subset;
        int idx = 0;
        int j = i;
        while (j > 0)
        {
            if (j & 1)
            {
                subset.push_back(a[idx]);
            }
            j >>= 1;
            ++idx;
        }
        subsets.push_back(subset);
    }
    return subsets;
}



// 8.6
#include <stdio.h>

int N;
int count;

void Hanoi(int N, int A, int B, int C) {

    if (N > 0) {                                                 
        Hanoi(N - 1, A, C, B);                                   
        printf("move top disk from %d to %d\n", A, C);      
        Hanoi(N - 1, B, A, C);                                   
    }
}



//Q 8.7 Write a method to compute all permutations of a string.
// https://github.com/black-shadows/Cracking-the-Coding-Interview/blob/master/Solutions/Chapter%208%20Recursion/8.4.cpp
#include <iostream>
#include <string>
#include <vector>

typedef vector<string> vs;

// CtCI approach #1
vs permu(string s)
{
    vs result;                              // set of all permuations
    if (s == "") {
        result.push_back("");
        return result;
    }
    string c = s.substr(0, 1);              // remove first charater
    vs res = permu(s.substr(1));            // call permu with the remainder and get permuations

    for (int i = 0; i < res.size(); ++i)
    {
        string t = res[i];
        for (int j = 0; j <= t.length(); ++j) {   // j <= len not j < l   !!
            string u = t;
            u.insert(j, c);                 // add first chacter to the returned permutation at every possible position
            result.push_back(u);
        }
    }
    return result;//
}

// CtCI approach #2
vs permu1(string s)
{
    vs result;
    if (s == "") {
        result.push_back("");
        return result;
    }

    for (int i = 0; i < s.length(); ++i) {
        string c = s.substr(i, 1);                  // c = charAt(i)
        string t = s;                               // make a copy of the org. string

        vs res = permu1(t.erase(i, 1));             // get all permutations of remainder

        for (int j = 0; j < res.size(); ++j) { 
            result.push_back(c + res[j]);           // c + permutations of remainder
        }
    }
    return result;
}

// 8.8  https://github.com/careercup/CtCI-6th-Edition-cpp/blob/master/chapter-8-recursion-and-Dynamic-Programming/8.8_Permutations_with_Dups.cpp
/* Careercup 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void iter_swap(char* ptr1, char* ptr2) {

    char tmp = *ptr1; *ptr1 = *ptr2;
    *ptr2 = tmp;

}

char* min_element(char* start, char* end) { // end is 1 beyond the last valid element

    if (start == end) return end; // empty range
    char* min_pos = start;
    for (char* iter = start + 1; iter != end; ++iter) {
        if (*iter < *min_pos) min_pos = iter;
    }
    return min_pos;
}

void permute(char* str_start, char* str, int length) {
    int counter = 0;
    if (length == 0) {
        printf("--%s\n\n", str_start);
        ++counter;
        return;
    }
    else {
        // Find the smallest char in the string set it to be the first character. Solve the subproblem for the smaller string.
        char* smallest = min_element(str, str + length);
        printf("%s smallest:%c ->", str, *smallest);
        iter_swap(str, smallest);
        printf("%s smallest:%c\n", str, *smallest);
        
        permute(str_start, str + 1, length - 1);

        // Look for the smallest element strictly greater than the first element of the current string
        char* smallest_greater = str + length;
        for (char* i = str + 1; i != str + length; ++i) {
            if (*i > *str && (smallest_greater == str + length || *i < *smallest_greater))
                smallest_greater = i;
        }

        printf("%s smallest_greater:%c ->", str, *smallest_greater);

        while (smallest_greater != str + length) {
            // If such an element is found, swap it into the first slot and recurse
            iter_swap(str, smallest_greater);
            printf("%s smallest_greater:%c\n", str, *smallest_greater);
            permute(str_start, str + 1, length - 1);

            // Repeat the loop if possible for the next greater character
            smallest_greater = str + length;
            for (char* i = str + 1; i != str + length; ++i)
                if (*i > *str && (smallest_greater == str + length || *i < *smallest_greater))
                    smallest_greater = i;
        }
        printf("\n");
    }
}
*/

// https://github.com/alexhagiopol/cracking-the-coding-interview/blob/master/cpp_solutions/chapter_08_recursion_and_dynamic_programming/problem_08_08_permutationsWithDups.cpp

/*
Chapter 08 - Problem 08 - Permutations With Duplicates

Problem Statement:
Write a method to compute all permutations of a string whose characters are not necessarily unique.
The list of permutations should not have duplicates.


Solution:
See the solution for 8.7 first.
Instead of recursively passing the problem state represented as a string, represent the problem state as a
hash table that maps string characters to their counts in the string. When creating new recursive calls,
create one recursive call for each unique character in the hash table, then decrement that character's count in the table
before passing it on. In this way, each recursive call is spawned with a unique character thus creating only unique permutations
The space and time complexities do not change because in the worst case the recursion tree is still O(N) nodes deep with
O(N!) leaf nodes and O(N) operations required at each node. One such operation is the creation of different copies of the hash
table to be passed down different recursion paths in the tree, each with O(N) entries. Another such operation is the
creation of new strings representing the permutations each with O(N) characters. The additional storage required by the
hash table is O(N) so it does not affect the existing big O analysis of the worst case storage requirement.

Time complexity: O(N!*N^2)
Space complexity: O(N!*N)
*/

//#include "problem_08_08_permutationsWithDups.h"
#include <unordered_map>
#include <iostream>

    void permutationsWithDupsHelper(const std::string& prefix, std::unordered_set<std::string>& permutations, const std::unordered_map<char, int>& hashTable, int d) {
        bool found = false;

        printf("[%d]", d);
        cout << "prefix: " << prefix << endl;
        

        for (auto pair : hashTable) {

            if (pair.second > 0) {
                #if 1
                    printf("[%d]%c:%d <= ", d, pair.first, pair.second);
                    std::unordered_map<char, int> hashTableCopy1 = hashTable;  // each recursive call is passed a different hash table copy
                    for (auto pair : hashTableCopy1) {
                        printf("%c:%d, ", pair.first, pair.second);
                    }
                    printf("      ");
                #endif          
                std::unordered_map<char, int> hashTableCopy = hashTable;  // each recursive call is passed a different hash table copy
                hashTableCopy[pair.first]--;

                std::string prefixCopy = prefix;  // each recursive call is passed a different prefix copy
                prefixCopy += pair.first;

                found = true;
                #if 1
                    cout << "--> prefix:  " << prefixCopy ;
                    for (auto pair : hashTableCopy) {
                        printf(",  %c:%d, ", pair.first, pair.second);
                    }
                    printf("\n");
                #endif
                permutationsWithDupsHelper(prefixCopy, permutations, hashTableCopy, d+1);
                printf("returned to %d\n", d);
            }

        }

        if (!found) {  // when the hash table has been depleted, add prefix to the permutations set
            printf("found == false\n");
            permutations.insert(prefix);

            printf("\n{");
            for (auto i = permutations.begin(); i != permutations.end(); ++i) {
                std::cout << (*i) << ", ";
            }
            printf("}\n\n");
        }
    }

    void permutationsWithDups(const std::string& string, std::unordered_set<std::string>& permutations) {
        if (string.length() == 1) {
            permutations.insert(string);
        }
        else if (string.length() >= 2) {
            // map the characters we've seen so far to their counts in a hash table
            std::unordered_map<char, int> hashTable;

            for (const char& singleChar : string) {
                if (hashTable.count(singleChar)) {
                    hashTable[singleChar]++;
                }
                else {
                    hashTable[singleChar] = 1;
                }
            }

            for (auto pair : hashTable) {
                //printf("%c:%d\n", pair.first, pair.second);
            }

            // pass hash table representation to recursive function that computes permutations
            permutationsWithDupsHelper("", permutations, hashTable, 0);
        }
        // if string.length() <= 0 do nothing
    }


int main()
{
    // 8.1
    for (int i = 0; i < DP_SIZE; i++) {
        dp[i] = 0;
    }

    dp[0] = 1;
    dp[1] = 1;
    dp[2] = 2;
    dp[3] = 4;

    //printf("6 step -> %d ways\n", countWays(6));
    printf("6 step -> %d ways\n", stairCount(6));

    // 8.2  : careercup
    //create a 5x7 matrix (5 rows and 7 columns)
    int** matrix = createMatrix(5, 7);
    //set specific points as off-limits
    matrix[1][3] = -1;
    matrix[2][5] = -1;
    matrix[3][2] = -1;
    matrix[0][1] = -1;

    vector<Point*> route = getPath(matrix, 5, 7);
    if (route.size() == 0) {
        cerr << "Path does not exist!" << endl;
    }
    else {
        for (int i = 0; i < route.size(); ++i) {
            cout << "[" << route[i]->row << "]" << "[" << route[i]->column << "]" << endl;
        }
    }


    // 3 4 :  black-shadows
    // 1 1 1 0
    // 0 1 1 1
    // 1 1 1 1
    freopen("8.2.in", "r", stdin);

    for (int i = 1; i < 10; ++i)
        cout << path(i, i) << endl;
    cout << endl;

    for (int i = 1; i < 10; ++i)
        cout << path1(i, i) << endl;
    cout << endl;

    int M, N;
    cin >> M >> N;
    for (int i = 1; i <= M; ++i)
        for (int j = 1; j <= N; ++j)
            cin >> g[i][j];

    cout << "one of the paths:" << endl;
    get_path(M, N);

    while (!sp.empty())
    {
        point p = sp.top();
        cout << "(" << p.y << "," << p.x << ")" << " ";
        sp.pop();
    }

    cout << endl << "all paths:" << endl;
    print_paths(1, 1, M, N, 0);
    fclose(stdin);


    // 8.3

    // 8.4  sol'n #2    : include elements at bit position of 1
    char set[] = { 'a','b','c','d' };
    printPowerSet(set, 4);

/*
    vector<int> set123 = { 1, 2, 3 };
    vector<int> testPowerSet = {};
    createPowerSet(set123, testPowerSet);*/


    int a[] = { 1,2,3,4 };
    vvi sub = get_subsets(a, 4);        // sol'n #1 : recurvsively P(n-1) + a_n
    vvi sub1 = get_subsets1(a, 0, 4);   // sol'n #2 : include elements at bit position of 1
    print_subsets(sub);
    print_subsets(sub1);
    
    // 8.6

    N = 4;
    Hanoi(N, 1, 2, 3);


    // 8.7
    string s = "abc";
    vs res = permu(s);                  // sol'n #1 : add a_n at every possible spot in P(a_n-1)
    //vs res = permu1(s);                   // sol'n #2 : i + P(before + after) 
    for (int i = 0; i < res.size(); ++i)
        cout << res[i] << endl;

    // 8.8 
    // Careercup
    //char str[] = "ACBB";
    //permute(str, str, strlen(str));

    std::unordered_set<std::string> actual3 = {};
    permutationsWithDups("alaa", actual3);
    
    for (auto i = actual3.begin(); i != actual3.end(); ++i) {
        std::cout << (*i) << std::endl;
    }

    return 0;
}
