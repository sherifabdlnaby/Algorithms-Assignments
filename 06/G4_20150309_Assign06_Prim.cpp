// GROUP:   4
// ID:      20150309
// Assign:  06
// Assign:  Prim
// UVA:     11631
// Name:    SHERIF ABDEL-NABY

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <cmath>

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

template<class T>
struct Array {
    T *arr;
    int n;      //Capacity
    int size;   //Init Size

    Array(int size = 0, int n = 50){
        this -> size = size;
        this -> n = size > n ? size : n;

        arr = new T[this -> n];

        //init
        for (int i = 0; i < size; ++i) {
            arr[i] = T();
        }
    }

    void destroy() {
        delete[] arr;
    }

    void addLast(T v) {
        if (size < n) {
            arr[size++] = v;
        } else {
            // Create new Array double the size
            T *newArr = new T[n *= 2];

            // Copy Array
            for (int i = 0; i < size; ++i) {
                newArr[i] = arr[i];
            }

            // Add new value and Increment
            newArr[size++] = v;

            // delete old arr (won't use destroy as we can extend dstry ltr)
            delete[] arr;

            // set new arr
            arr = newArr;
        }
    }

    void removeLast() {
        --size;
    }

    T &operator[](int i) {
        return arr[i];
    }

    void print() {
        for (int i = 0; i < size; ++i) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
};

template<class T>
struct Heap {
    Array<T> arr;

    bool (*isBefore)(T &a, T &b);

    void initialize(bool (*__isBefore)(T &a, T &b)) {
        isBefore = __isBefore;
    }

    void destroy() {
        arr.destroy();

    }

    int child(int i) {
        return i * 2 + 1;
    }

    int parent(int i) {
        return (i - 1) / 2;
    }

    T getFirst() {
        return arr[0];
    }

    T retrieveFirst() {
        T tmp = arr[0];

        //Swap
        swap(arr[0], arr[arr.size-1]);

        //Erase
        arr.removeLast();

        //Heapify
        moveDown(0);

        return tmp;
    }

    void add(T e) {
        arr.addLast(e);
        moveUp(arr.size - 1);
    }

    void moveUp(int i) {
        int parentIdx = parent(i);

        //Bubble Upwards.
        while (isBefore(arr[i], arr[parentIdx]) && i) {
            swap(arr[i], arr[parentIdx]);
            i = parentIdx;
            parentIdx = parent(i);
        }
    }

    void moveDown(int i) {
        int parent = i;
        int left = (i << 1) + 1;
        int right = (i << 1) + 2;
        if (left < arr.size && isBefore(arr[left], arr[parent]))
            parent = left;
        if (right < arr.size && isBefore(arr[right], arr[parent]))
            parent = right;
        if (parent != i) {
            swap(arr[i], arr[parent]);
            moveDown(parent);
        }
    }

    bool isEmpty()
    {
        return arr.size;
    }

    int size(){
        return arr.size;
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
    int V,E;
    cin >> V >> E;
    while(V != 0 || E != 0) {
        Array<Array<Edge>> adjList(V);
        for (int i = 0; i < E; ++i) {
            int a, b, c;
            cin >> a >> b >> c;
            adjList[a].addLast(Edge(a,b,c));
        }

        int idx = 0, MSTNodes = 0;

        DisjointSets MST;
        MST.Initialize(V);

        Heap<Edge> priorityQueue;
        priorityQueue.initialize(IsBeforeEdge);

        //Add first node
        for (int i = 0; i < adjList[0].size; ++i) {
            priorityQueue.add(adjList[0][i]);
        }

        while(MSTNodes < V - 1)
        {
            Edge e = priorityQueue.retrieveFirst();

            //If Non Visited node
            if(MST.Union(e.u, e.v))
            {
                //dbg
                cout << e.u << " - " << e.v << "  W(" << e.w << ")\n";

                //add new V nodes edges. (u should've been added by a previous iteration)
                for (int i = 0; i < adjList[e.v].size; ++i)
                    priorityQueue.add(adjList[e.v][i]);

                MSTNodes++;
            }
        }

        //NEW TESTCASE
        cin >> V >> E;
    }
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
