// GROUP:   4
// ID:      20150309
// Assign:  10
// Assign:  MatChain
// UVA:     348
// Name:    Sherif Abdel-Naby
// UVA Username: sherifabdlnaby
#include <cstdio>
#include <iostream>

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int p[11];// the dimensions of matrices
int T[11][11]; // T[a][b]=the optimal number of multiplication of p[a]...p[b]
int D[11][11]; // D[a][b]=the decision (value of k) that gets T[a][b]

// Top down version
// Recursive, cost of multiplying the b-a matrices with indexes: a...b-1
int MatChain(int a, int b) {
    //base case
    if (a + 1 == b)
        return 0;

    //check memoization
    if (T[a][b] != -1)
        return T[a][b];

    int operation = 0;
    int minOperation = 0x7FFFFFFF;  //initial max value
    //int minOperation = 2147000000;

    for (int k = a + 1; k < b; k++) {
        //             -left-           -right-            -left * right-
        operation = MatChain(a, k) + MatChain(k, b) + (p[a] * p[k] * p[b]);

        if (operation < minOperation) {
            minOperation = operation;
            D[a][b] = k;
        }
    }

    //return and save memoization.
    return T[a][b] = minOperation;
}

// Initialize T then call MatChain(0,n)
void MatChainTopDown(int n) {
    //reset values;
    for (int i = 0; i <= n; ++i)
        for (int j = 0; j <= n; ++j)
            T[i][j] = D[i][j] = -1;

    //recurse
    MatChain(0, n);

    return;
}

// BottomUp version
void MatChainBottomUp(int n) {
    int operation = 0;
    int minOperation = 0x7FFFFFFF;  //initial max value
    //int minOperation = 2147000000;

    for (int s = 1; s <= n; s++) {
        for (int a = 0; a + s <= n; a++) {

            int b = a + s;

            //reset minimum.
            minOperation = 0x7FFFFFFF;
            //minOperation = 2147000000;

            for (int k = a + 1; k < b; k++)
            {
                //           -left-   -right-       -left * right-
                operation = T[a][k] + T[k][b] + ( p[a] * p[k] * p[b] );
                if (operation < minOperation)
                {
                    T[a][b] = minOperation = operation;
                    D[a][b] = k;
                }
            }
        }
    }
}

// Recursive to output the solution for both versions
void MatChainSol(int a, int b) {
    int k = D[a][b];

    //base case
    if (a + 1 == b)
        cout << "A" << b;
    else {
        cout << "(";
        MatChainSol(a, k);
        cout << " x ";
        MatChainSol(k, b);
        cout << ")";
    }

}

void Compute() {
    int t, caseNum = 0;
    cin >> t;
    while (t != 0) {
        //take input
        for (int i = 1; i <= t; ++i)
            cin >> p[i - 1] >> p[i];

        //compute case
        //MatChainTopDown(t);
        MatChainBottomUp(t);

        //output
        cout << "Case " << ++caseNum << ": ";
        MatChainSol(0, t);
        cout << endl;

        //new test-case
        cin >> t;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
    //freopen("input_assign10_00348.txt", "r", stdin);
    Compute();
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
