#include <vector>
#include <iostream>
#include <unordered_set>

using namespace std;

// 8.1 
#define 	DP_SIZE		10
int dp[DP_SIZE];

int stairCount(int steps)
{
    return 0;
}


// 8.2
struct Point {
    int row;
    int column;
    Point(int r, int c) : row(r), column(c) {}
};


//int** matrix = new int* [rows];
//for (int i = 0; i < rows; ++i) 
//  matrix[i] = new int[columns];
int** createMatrix(int rows, int columns) {
    return nullptr;
}

#if 1 // w/ memoization
bool getPath(int** matrix, int currRow, int currColumn, vector<Point*>& path, unordered_set<Point*>& duplicateVisits)
{
    return false;
}

vector<Point*> getPath(int** matrix, int rows, int columns) {
    vector<Point*> path;

    return path;
}
#else // w/o memoization 
bool getPath(int** matrix, int row, int col, vector<Point*>& path)
{
    return false;
}

vector<Point*> getPath(int** matrix, int row, int col)
{
    vector<Point*> path;

    return path;
}
#endif

// 8.4

// g4g - backtracking
// 1. push sub at the beginning of call
// 2. loop index should start from the upper depth, not from 0
// 3. foo(int a) vs. foo(int &a)
vector<int> arr = { 1, 2, 3 };

void print_subsets(vector<vector<int>> result)
{
}

void subsetsUtil(vector<vector<int>>& result, vector<int>& subset, int index)
{
}

// CtCI - #2
vector<vector<int>> get_subsets1(int* arr, int size)
{
    vector<vector<int>> result;

    return result;
}

// CtCI - #1
// it all starts w/ empty set
// base cond'n : return not empty set but resutl with empty set
vector<vector<int>> get_subsets(int* arr, int idx, int size)
{
    vector<vector<int>> result;

    return result;
}


// 8.6
#include <stdio.h>
/*

    N   +  N-1 ~
    N-1 +  N-2 ~
    ...
*/

// A: src, B: des, C: buf
void Hanoi(int N, int A, int B, int C) {
}

// 8.7
typedef vector<string> vs;

// keep s till end
vs permu(string s)
{
    vs result;

    return result;
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

    //printf("6 step -> %d ways\n", countWays(6));

    int steps = 6;
    printf("%d step -> %d ways\n", steps, stairCount(steps));

    for (int i = 1;i < DP_SIZE;i++)
        printf("dp[%d] = %3d\n", i, dp[i]);

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

#if 0
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
#endif

    // 8.3

    // 8.4
    // g4g
    cout << "-------- g4g ----------" << endl;
    vector<int> subset;
    vector<vector<int>> result;
    subsetsUtil(result, subset, 0);
    print_subsets(result);

    /*
    vector<int> set123 = { 1, 2, 3 };
    vector<int> testPowerSet = {};
    createPowerSet(set123, testPowerSet);

    for (int i = 0; i < result.size(); i++) {
        for (int j = 0; j < result[i].size(); j++)
            cout << result[i][j] << " ";
        cout << "_" << endl;
    }*/

    cout << "-------- CtCI 1----------" << endl;
    int a[] = { 1,2,3/*,4*/ };
    vector<vector<int>> sub1 = get_subsets1(a, sizeof(a) / sizeof(int));    // sol'n #2 : include elements at bit position of 1    
    print_subsets(sub1);

    cout << "-------- CtCI 2----------" << endl;
    vector<vector<int>> subs = get_subsets(a, 0, sizeof(a) / sizeof(int));        // sol'n #1 : recurvsively P(n-1) + a_n
    print_subsets(subs);


    // 8.6
    N = 3;
    Hanoi(N, 1, 2, 3);


    // 8.7
    string s = "abc";
    vs res = permu(s);                  // sol'n #1 : add a_n at every possible spot in P(a_n-1)
    //vs res = permu1(s);                   // sol'n #2 : i + P(before + after) 
    for (int i = 0; i < res.size(); ++i)
        cout << res[i] << endl;

#if 0
    // 8.8 
    // Careercup
    //char str[] = "ACBB";
    //permute(str, str, strlen(str));

    std::unordered_set<std::string> actual3 = {};
    permutationsWithDups("alaa", actual3);

    for (auto i = actual3.begin(); i != actual3.end(); ++i) {
        std::cout << (*i) << std::endl;
    }
#endif
    return 0;
}
