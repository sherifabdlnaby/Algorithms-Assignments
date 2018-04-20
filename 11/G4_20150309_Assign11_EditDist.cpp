// GROUP:   4
// ID:      20150309
// Assign:  11
// Assign:  EditDist
// UVA:     526
// Name:    SHERIF ABDEL-NABY
// UVA Username: sherifabdlnaby

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

char a[82];
char b[82];
int D[81][81]; // D[][] is the same for all versions (no memory reduction)

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T1[81][81];

int EditDist1(int n, int m)
{

    // memoization
    if (T1[n][m] != -1)
        return T1[n][m];

    // base cases
    if (n == 0 && m == 0)
        return 0;

    if (n == 0) {
        /*
          * if the first string 'a' (the one to be edited to string 'b') is empty, this means there is only one
          * way, by inserting all of string 'b' into 'a'.
        */

        // recursion 1 : less recursion + less memoization.
        /*
        for (int i = 0; i <= m; ++i)
            D[0][i] = 0; // INSERT

        return T1[n][m] = m;
        */

        // recursion 2 : more recursive calls, but better utilizing for memoization.
        D[0][m] = 0;
        return T1[n][m] = 1 + EditDist1(n, m - 1);

    }
    if (m == 0)
    {
        /* if the second string 'b' is empty, this means there is only one wat to make a -> b
        *  by deleting all of string 'a'.
        */

        // recursion 1 : less recursion + less memoization.
        /*
        for (int i = 0; i <= n; ++i)
            D[i][0] = 1; // DELETE

        return T1[n][m] = n;
         */

        // recursion 2 : more recursive calls, but better utilizing for memoization.
        D[n][0] = 1;
        return T1[n][m] = 1 + EditDist1(n - 1, m);
    }

    // if equal, we do no operations and escape the char in both strings
    if (a[n - 1] == b[m - 1])
    {
        D[n][m] = -1;
        return T1[n][m] = EditDist1(n - 1, m - 1);
    }

    // Try performing the 3 different operation >> pick min.

    int testOperation = EditDist1(n, m - 1);
    int minCost = testOperation;    // initial min
    int minOperation = 0;           // 0 for insert.

    testOperation = EditDist1(n - 1, m);
    if (testOperation < minCost)
    {
        minCost = testOperation;
        minOperation = 1;           // 1 for delete.
    }

    testOperation = EditDist1(n - 1, m - 1);
    if (testOperation < minCost)
    {
        minCost = testOperation;
        minOperation = 2;           // 1 for delete.
    }

    // Save final Decision
    D[n][m] = minOperation;

    return T1[n][m] = minCost + 1;
}

// Recursive - memoization - initialize T then call EditDist1(N,M);
int ComputeEditDist1(int N, int M)
{
    //INITIALIZE
    for (int i = 0; i <= N; ++i)
    {
        memset(T1[i], -1, (M + 1) * sizeof(int));
    }

    return EditDist1(N, M);;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Bottom-up, do not save space
int T2[81][81];

int ComputeEditDist2(int N, int M)
{
    // INITIALIZE DP TABLE 1st row & col.
    for (int j = 0; j <= M; ++j)
    {
        T2[0][j] = j;
        D[0][j] = 0;    // 0 for insert.
    }

    for (int i = 0; i <= N; ++i)
    {
        T2[i][0] = i;
        D[i][0] = 1;    // 1 for delete.
    }

    //START DP
    for (int n = 1; n <= N; ++n)
    {
        for (int m = 1; m <= M; ++m)
        {
            //NO DECISION - ESCAPE
            if (a[n - 1] == b[m - 1])
            {
                T2[n][m] = T2[n - 1][m - 1];
                D[n][m] = -1;       // -1 for no operation. (goes to diagonal)
            }
            else
            {
                int minCost = min(T2[n][m - 1], min(T2[n - 1][m - 1], T2[n - 1][m]));

                T2[n][m] = 1 + minCost;

                //Save Decision
                if (minCost == T2[n][m - 1])
                    D[n][m] = 0;    //  0 for insert
                else if (minCost == T2[n - 1][m])
                    D[n][m] = 1;    //  1 for delete
                else
                    D[n][m] = 2;    //  2 for replace.

                // -1 for no operation. (goes to diagonal)
            }
        }
    }
    return T2[N][M];
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T3[2][81];

// Bottom-up, use two rows only
int ComputeEditDist3(int N, int M)
{
    // INITIALIZE DP TABLE 1st row & col.
    for (int j = 0; j <= M; ++j)
    {
        T3[0][j] = j;
        D[0][j] = 0;    // 0 for insert.
    }
    T3[0][0] = 0;
    D[0][0] = 1;

    bool swtch = 1;

    //START DP
    for (int n = 1; n <= N; ++n)
    {
        //Initialize row most-left according to iteration (n).
        T3[swtch][0] = n;
        D[n][0] = 1;    // 1 for delete.

        for (int m = 1; m <= M; ++m)
        {
            //NO DECISION - ESCAPE
            if (a[n - 1] == b[m - 1])
            {
                T3[swtch][m] = T3[!swtch][m - 1];
                D[n][m] = -1;       // -1 for no operation. (goes to diagonal)
            }
            else
            {
                int minCost = min(T3[swtch][m - 1], min(T3[!swtch][m - 1], T3[!swtch][m]));

                T3[swtch][m] = 1 + minCost;

                //Save Decision
                if (minCost == T3[swtch][m - 1])
                    D[n][m] = 0;    //  0 for insert
                else if (minCost == T3[!swtch][m])
                    D[n][m] = 1;    //  1 for delete
                else
                    D[n][m] = 2;    //  2 for replace.

                // -1 for no operation. (goes to diagonal)
            }
        }
        swtch = !swtch;
    }

    return T3[!swtch][M];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T4[81];

// Bottom-up, save maximum space
int ComputeEditDist4(int N, int M) {
    // INITIALIZE DP TABLE 1st row & col.
    for (int j = 0; j <= M; ++j)
    {
        T4[j] = j;
        D[0][j] = 0;    // 0 for insert.
    }

    //START DP
    int T4LastItrDiagonal = 0;
    for (int n = 1; n <= N; ++n) {
        // initialize first col in each row.
        T4LastItrDiagonal = T4[0];
        T4[0] = n;
        D[n][0] = 1;
        for (int m = 1; m <= M; ++m)
        {
            /* used to save current Iteration before it being updated
             * and copied to T4LastItrDiagonal after iteration so that it be the diagonal value in next itr.
             * (b save- elly fo2eya abl aye update, 3shan dah el diagonal fe el next iteration) */
            int tmpDiagonal = T4[m];

            //NO DECISION - ESCAPE
            if (a[n - 1] == b[m - 1])
            {
                T4[m] = T4LastItrDiagonal;
                D[n][m] = -1;
            }
            else
            {
                int minCost = min(T4[m - 1], min(T4LastItrDiagonal, T4[m]));

                //Save Decision
                if (minCost == T4[m - 1])
                    D[n][m] = 0;    //  0 for insert
                else if (minCost == T4[m])
                    D[n][m] = 1;    //  1 for delete
                else
                    D[n][m] = 2;    //  2 for replace.

                T4[m] = 1 + minCost;
            }
            T4LastItrDiagonal = tmpDiagonal;
        }
    }
    return T4[M];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Oper
{
    int n, m;
    int oper;
};

Oper opers[81];

// Print the solution using D[][]
int EditDistSol(int N, int M)
{

    int n = N, m = M, op = 0;

    while (n != 0 || m != 0)
    {
        // add to list if it's an operation.
        if (D[n][m] != -1)
        {
            Oper newOperation;

            // get operation.
            newOperation.oper = D[n][m];

            // get operation index
            newOperation.n = n;

            // save operation char if insert or replace.
            if (newOperation.oper == 0 || newOperation.oper == 2)
                newOperation.m = b[m - 1];

            // add to list.
            opers[op++] = newOperation;
        }

        // iterate.
        if (D[n][m] == 0)
            --m;
        else if (D[n][m] == 1)
            --n;
        else
            --n, --m;
    }

    //used to offset indexes after insert/delete .
    int deleteCount = 0;
    int insertCount = 0;

    // print and
    cout << op << endl;
    for (int i = op - 1; i >= 0; --i)
    {
        cout << op - i << " ";

        if (opers[i].oper == 0)
            cout << "Insert " << opers[i].n + 1 - deleteCount + insertCount++ << "," << (char) opers[i].m << endl;
        else if (opers[i].oper == 1)
            cout << "Delete " << opers[i].n - deleteCount++ + insertCount << endl;
        else
            cout << "Replace " << opers[i].n - deleteCount + insertCount << "," << (char) opers[i].m << endl;

    }
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int ComputeEditDist(int N, int M) // Here we can choose the method
{
    return ComputeEditDist1(N, M);
    //ComputeEditDist2(N,M);
    //return ComputeEditDist3(N, M);
    //return ComputeEditDist4(N, M);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

// This function does not need any modification:
void Compute() // Get input and call ComputeEditDist() whenever needed
{
    int cas = 0;
    while (true) {
        a[0] = 0;
        b[0] = 0;
        if (!fgets(a, 82, stdin)) break;
        fgets(b, 82, stdin);
        a[strlen(a) - 1] = 0;
        b[strlen(b) - 1] = 0;
        if (cas) cout << endl; // print an empty line between test cases
        int N = strlen(a), M = strlen(b);
        ComputeEditDist(N, M);
        EditDistSol(N, M);
        cas++;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
    //freopen("input_assign11_00526.txt", "r", stdin);
    Compute();
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
