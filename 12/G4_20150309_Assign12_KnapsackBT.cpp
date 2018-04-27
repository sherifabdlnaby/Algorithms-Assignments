// GROUP:   4
// ID:      20150309
// Assign:  12
// Assign:  KnapsackBT
// UVA:     10130
// Name:    Sherif Abdel-Naby
// UVA Username: sherifabdlnaby

#include <cstdio>
#include <iostream>

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class Type>
void Merge(Type *a, int n, bool (*IsBefore)(Type &a, Type &b)) {
    Type cpyArr[n];
    int mid = n / 2;
    int i = 0;
    int j = mid;

    for (int k = 0; k < n; ++k) {
        if (j > n - 1)
            cpyArr[k] = a[i++];
        else if (i >= mid)
            cpyArr[k] = a[j++];
        else if (IsBefore(a[i], a[j]))
            cpyArr[k] = a[i++];
        else
            cpyArr[k] = a[j++];
    }

    //Copying back to Original Array...
    int x = 0;
    for (int l = 0; l < n; ++l) {
        a[x++] = cpyArr[l];
    }

    return;
}

template<class Type>
void MergeSort(Type *a, int n, bool (*IsBefore)(Type &a, Type &b)) {
    if (n <= 1)
        return;
    int mid = n / 2;
    MergeSort(a, mid, IsBefore);
    MergeSort(a + mid, mid + (n % 2), IsBefore);
    Merge(a, n, IsBefore);
    return;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Obj {
    int v;
    int w;
};

int n;       // number of objects (input)
Obj a[1000]; // objects (input)

/*bool cur_sol[1000];
bool best_sol[1000];*/

////////////////////////////////////////////////////////////////////////////////////////////////////////////

// return true if unit value of a is greater than unit value of b
bool IsBefore(Obj &a, Obj &b) { return (float)a.v / a.w > (float)b.v / b.w; };

////////////////////////////////////////////////////////////////////////////////////////////////////////////

// the best total value found until now
int best_val = 0;

// upper bound on the total value of items [i..n-1] that can fit in w
int Bound(int i, int w){
    int value = 0;
    for (int j = i; j < n; ++j)
    {
        if(a[j].w <= w)
        {
            value += a[j].v;
            w -= a[j].w;
        }
        else
        {
            // the '+ a[j].w - 1' to ceil the result without casting or std:ceil.
            value +=  (w * a[j].v + a[j].w - 1) / a[j].w;
            break;
        }
    }
    return value;
};

// starting from item i, remaining weight w, cur_value of objects[0..i-1]
void BackTrack(int i, int w, int cur_val) {

    // Base Case
    if (i == n)
    {
        if(cur_val > best_val)
        {
            best_val = cur_val;
            /*for (int j = 0; j < n; ++j)
                best_sol[j] = cur_sol[j];*/
        }
        return;
    }

    if(cur_val +  Bound(i,w) > best_val)
    {
        if (a[i].w <= w)
            BackTrack(i + 1, w - a[i].w, cur_val + a[i].v);

        BackTrack(i + 1, w, cur_val);
    }

    return;
}

// solve knapsack of N objects and W weight
int ComputeKnapsack(int N, int W){
    //Sort by Unit weight value.
    //(redundant sorting is happening due to the nature of the problem input, but I'm stickin' to the skeleton)
    MergeSort(a, N, IsBefore);

    //Start Algorithm
    best_val = 0;
    BackTrack(0, W, 0);

    return best_val;
}

void Compute(){
    int T;
    cin >> T;
    while (T--) {
        int W, G;
        int v, w;
        cin >> n;
        for (int i = 0; i < n; ++i)
        {
            cin >> v >> w;
            a[i] = {v, w};
        }
        cin >> G;
        int total = 0;
        for (int i = 0; i < G; ++i)
        {
            cin >> W;
            total += ComputeKnapsack(n, W);;
        }
        cout << total << endl;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
    //freopen("input_assign12_10130.txt", "r", stdin);
    Compute();
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
