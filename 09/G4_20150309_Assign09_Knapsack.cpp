// GROUP:   4
// ID:      20150309
// Assign:  09
// Assign:  Knapsack
// UVA:     10130
// Name:    SHERIF ABDEL-NABY
// UVA Username: sherifabdlnaby

#include <cstdio>
#include <iostream>

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Obj {
    int v; // value (price) of object
    int w; // weight of object
};

Obj a[1000];

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T1[1001][31];

int Knapsack1(int n, int w) {
    //base case.
    if (w == 0 || n == -1)
        return 0;

    //check if precomputed
    if (T1[n][w] != -1)
        return T1[n][w];

    int ret1 = 0, ret2 = -1;

    //0
    ret1 = Knapsack1(n - 1, w);

    //1
    if (a[n].w <= w)
        ret2 = Knapsack1(n - 1, w - a[n].w);

    if (ret2 == -1)
        return T1[n][w] = ret1;

    return T1[n][w] = max(ret1, ret2 + a[n].v);
}

// Recursive - memoization - initialize T then call Knapsack1(N,W);
int ComputeKnapsack1(int N, int W) {
    for (int i = 0; i < N; ++i)
        for (int j = 0; j <= W; ++j)
            T1[i][j] = -1;

    return Knapsack1(N - 1, W);
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T2[1001][31];

// Bottom-up, do not save space
int ComputeKnapsack2(int N, int W) {
    //Initialize ( <= cause we're using 1-indexed items in T2)
    for (int i = 0; i <= N; ++i)
        for (int j = 0; j <= W; ++j)
            T2[i][j] = 0;

    //Start Algorithm (note: in T2, item i matches item i-1 in array -> a)
    for (int n = 1; n <= N; ++n)
    {
        for (int w = 1; w <= W; ++w)
        {
            /* if we can't take this item, escape it.
                (escaping it mean picking the best result from the previous sub-problem at the same weight. */
            if (a[n - 1].w > w)
                T2[n][w] = T2[n - 1][w];
                /* if we can take this item, compare if not taking this item led to better value.
                    1. not taking it -same idea as above- Vs.  2. taking it + the best sub-problem with the remaining weight if taken. */
            else
                T2[n][w] = max(T2[n - 1][w], a[n - 1].v + T2[n - 1][w - a[n - 1].w]);
        }
    }

    return T2[N][W];
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T3[2][31];

// Bottom-up, use two rows only
int ComputeKnapsack3(int N, int W) {
    for (int i = 0; i <= W; ++i)
    {
        T3[0][i] = 0;
        T3[1][i] = 0;
    }
    /* Since every iteration access only last iteration's row, this switch will alternate between 1 / 0 to only use only 2 rows
     * ( I hope this doesn't violate clean code :') )*/
    bool swtch = 0;

    //Start Algorithm (note: in T2, item i matches item i-1 in array -> a)
    for (int n = 1; n <= N; ++n)
    {
        for (int w = 1; w <= W; ++w)
        {
            /* if we can't take this item, escape it.
               (escaping it mean picking the best result from the previous sub-problem at the same weight. */
            if (a[n - 1].w > w)
                T3[!swtch][w] = T3[swtch][w];
                /* if we can take this item, compare if not taking this item led to better value.
                   1. not taking it -same idea as above- Vs.  2. taking it + the best sub-problem with the remaining weight if taken. */
            else
                T3[!swtch][w] = max(T3[swtch][w], a[n - 1].v + T3[swtch][w - a[n - 1].w]);
        }
        swtch = !swtch;
    }

    return T3[swtch][W];
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T4[31];

// Bottom-up, save maximum space
int ComputeKnapsack4(int N, int W) {
    for (int i = 0; i <= W; ++i)
        T4[i] = 0;

    for (int n = 1; n <= N; ++n)
    {
        for (int w = W; w >= 0; --w)
        {
            if (a[n - 1].w > w)
                continue;
            else
                T4[w] = max(T4[w], a[n - 1].v + T4[w - a[n - 1].w]);
        }
    }
    return T4[W];
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Here we can choose the method
int ComputeKnapsack(int N, int W) {
    //return ComputeKnapsack1(N, W);
    //return ComputeKnapsack2(N,W);
    //return ComputeKnapsack3(N,W);
    return ComputeKnapsack4(N, W);
}

// Get input and call ComputeKnapsack() whenever needed
void Compute() {
    int T;
    cin >> T;
    while (T--) {
        int N, W, G;
        int v, w;
        cin >> N;
        for (int i = 0; i < N; ++i)
        {
            cin >> v >> w;
            a[i] = {v, w};
        }
        cin >> G;
        int total = 0;
        for (int i = 0; i < G; ++i) 
        {
            cin >> W;
            total += ComputeKnapsack(N, W);
        }
        cout << total << endl;
    }
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
    //freopen("input_assign09_10130.txt", "r", stdin);
    Compute();
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
