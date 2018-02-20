// GROUP:   4
// ID:      20150309
// Assign:  02
// Assign:  DisjointSets
// UVA:     10608
// Name:    SHERIF MOHAMED ABDEL-NABY

#include <iostream>
#include <cstring>

using namespace std;
struct DisjointSets
{
    int n;
    int* parent;
    int* num_nodes;
    void Initialize(int _n);
    void Destroy();
    int Find(int i);
    bool Union(int i, int j);
};

void DisjointSets::Initialize(int _n) {
    n = _n;
    parent = new int[n];
    num_nodes = new int[n];
    memset(parent,-1, n * sizeof(int));
    memset(num_nodes,0, n * sizeof(int));
}

void DisjointSets::Destroy() {
    delete[] parent;
    delete[] num_nodes;
}

int DisjointSets::Find(int i) {
    //Iterative
    while(true){
        if(parent[i] == -1)
            return i;
        else
            i = parent[i];
    }
    //TODO PATH-COMPRESSION
}

bool DisjointSets::Union(int i, int j) {
    //Find set roots.
    int iRoot = Find(i);
    int jRoot = Find(j);

    //If they're in the same set return false.
    if (iRoot == jRoot)
        return false;

    //Union the smaller set with the bigger set, if sets are equal union i with j and increment.
    if(num_nodes[iRoot] > num_nodes[jRoot])
        parent[jRoot] = iRoot;
    else if(num_nodes[iRoot] < num_nodes[jRoot])
        parent[iRoot] = jRoot;
    else
        parent[jRoot] = iRoot, ++num_nodes[iRoot];

    return true;
}

int main() {
    DisjointSets x;
    int tc,n,p,i,j,maxi;
    cin >> tc;
    for (int t = 0; t < tc; ++t)
    {
        cin >> n >> p;

        x.Initialize(n);
        maxi = -1;

        for (int k = 0; k < p; ++k) {
            cin >> i >> j;
            x.Union(i-1,j-1);
        }

        //get max
        int* count = new int[n];
        memset(count, 0, n * sizeof(int));

        for (int k = 0; k < n; ++k)
            maxi = max(maxi, ++count[x.Find(k)]);

        delete[] count;

        cout << maxi << endl;

        x.Destroy();
    }
    return 0;
}