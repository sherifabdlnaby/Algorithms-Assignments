// GROUP:   X
// ID:      XXXXXXXX
// Assign:  05
// Assign:  Kruskal
// UVA:     11631
// Name:    XXX MY FULL NAME

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
    int pathCompressionList[n], idx = 0;

    //Iterative
    while(true){
        if(parent[i] == -1)
            break;
        else
            pathCompressionList[idx++] = i, i = parent[i];
    }

    //Path Compress
    for (int j = 0; j < idx; ++j)
        parent[pathCompressionList[j]] = i;

    return i;
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class Type>
void Merge(Type* a, int n, bool (*IsBefore)(Type& a, Type& b)){
    Type cpyArr[n];
    int mid = n/2;
    int i = 0;
    int j = mid;

    for (int k = 0; k < n; ++k) {
        if (j > n-1)
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
void MergeSort(Type* a, int n, bool (*IsBefore)(Type& a, Type& b)){
    if (n <= 1)
        return;
    int mid = n/2;
    MergeSort(a, mid, IsBefore);
    MergeSort(a + mid,  mid + (n%2), IsBefore);
    Merge(a, n, IsBefore);
    return;
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Edge
{
	int u, v;
	int w;

    friend ostream &operator<<(ostream &os, const Edge &edge) {
        os << "u: " << edge.u << " v: " << edge.v << " w: " << edge.w;
        return os;
    }

    Edge(int u, int v, int w) : u(u), v(v), w(w) {}
    Edge(){}
};

bool IsBeforeEdge(Edge& a, Edge& b)
{
	return a.w < b.w;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
    int V,E;
    cin >> V >> E;
    while(V != 0 || E != 0) {
        int totalCost = 0, newTotalCost = 0;
        Edge edges[E];
        for (int i = 0; i < E; ++i) {
            int a, b, c;
            cin >> a >> b >> c;
            edges[i] = Edge(a, b, c);
            totalCost += c;
        }

        MergeSort(edges, E, IsBeforeEdge);

        DisjointSets set;
        set.Initialize(V);

        int MSTNodes = 0, idx = 0;
        while (MSTNodes < V - 1) {
            Edge *e = &edges[idx++];

            if (set.Find(e->u) != set.Find(e->v))
                set.Union(e->u, e->v), ++MSTNodes, newTotalCost += e->w;
        }

        cout << totalCost - newTotalCost << endl;

        //NEW TESTCASE
        cin >> V >> E;
    }
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
