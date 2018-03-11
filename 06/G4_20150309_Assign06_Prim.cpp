// GROUP:   4
// ID:      20150309
// Assign:  06
// Assign:  Prim
// UVA:     534
// Name:    SHERIF ABDEL-NABY

#include <cstdio>
#include <cstring>
#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct DisjointSets {
    int n;
    int *parent;
    int *num_nodes;

    void Initialize(int _n);

    void Destroy();

    int Find(int i);

    bool Union(int i, int j);
};

void DisjointSets::Initialize(int _n) {
    n = _n;
    parent = new int[n];
    num_nodes = new int[n];
    memset(parent, -1, n * sizeof(int));
    memset(num_nodes, 0, n * sizeof(int));
}

void DisjointSets::Destroy() {
    delete[] parent;
    delete[] num_nodes;
}

int DisjointSets::Find(int i) {
    int pathCompressionList[n], idx = 0;

    //Iterative
    while (true) {
        if (parent[i] == -1)
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
    if (num_nodes[iRoot] > num_nodes[jRoot])
        parent[jRoot] = iRoot;
    else if (num_nodes[iRoot] < num_nodes[jRoot])
        parent[iRoot] = jRoot;
    else
        parent[jRoot] = iRoot, ++num_nodes[iRoot];

    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Edge {
    int u, v;
    double w;

    friend ostream &operator<<(ostream &os, const Edge &edge) {
        os << "u: " << edge.u << " v: " << edge.v << " w: " << edge.w;
        return os;
    }

    Edge(int u, int v, double w) : u(u), v(v), w(w) {}

    Edge() {}
};

bool IsBeforeEdge(Edge &a, Edge &b) {
    return a.w < b.w;
}

template<class T>
struct Array {
    T *arr;
    int n;      //Capacity
    int size;   //Init Size

    Array(int size = 0, int n = 50) {
        this->size = size;
        this->n = size > n ? size : n;

        arr = new T[this->n];

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
        swap(arr[0], arr[arr.size - 1]);

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

    bool isEmpty() {
        return arr.size;
    }

    int size() {
        return arr.size;
    }
};

struct Node {
    int x, y;
    int prnt;
    double weight;
    Array<Edge> adj;

    void Initialize(int x, int y) {
        this->x = x;
        this->y = y;
    }

    void Destroy() {adj.destroy();}


};
double squareRoot(double x, int n = 100)
{
    if (x == 0 || x == 1)
        return x;

    double start = 1, end = x, mid = start + (end - start) / 2;

    while (n-- ,abs(x - mid*mid) > 1.0E-8)
    {
        if (mid*mid < x)
            start = mid;
        else
            end = mid;

        mid = start + (end - start) / 2;
    }

    return mid;
}

double euclideanDist(int x1, int y1, int x2, int y2) {
    return squareRoot((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main() {
    int V, N = 0;
    cin >> V;
    while (N++, V) {
        Array<Node> NodeList(V);

        for (int i = 0; i < V; ++i) {
            int a, b;
            cin >> a >> b;
            Node newNode;
            newNode.Initialize(a, b);
            NodeList[i] = newNode;
        }

        //Precomputed distance (can be optimized to compute two at a time but fak it not now)
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) {
                if (i == j) continue;
                double weight = euclideanDist(NodeList[i].x, NodeList[i].y, NodeList[j].x, NodeList[j].y);
                NodeList[i].adj.addLast(Edge(i, j, weight));
            }
        }

        int MSTNodes = 0;

        DisjointSets MST;
        MST.Initialize(V);

        Heap<Edge> priorityQueue;
        priorityQueue.initialize(IsBeforeEdge);

        //Add first node
        for (int i = 0; i < NodeList[0].adj.size; ++i) {
            priorityQueue.add(NodeList[0].adj[i]);
            NodeList[NodeList[0].adj[i].v].prnt = 0;
            NodeList[NodeList[0].adj[i].v].weight = NodeList[0].adj[i].w;
        }

        while (MSTNodes < V - 1) {
            Edge e = priorityQueue.retrieveFirst();


            NodeList[e.v].weight = e.w;
            NodeList[e.v].prnt = e.u;


            //if fiona's stone
            if (e.v == 1) {
                int idx = e.v;
                double minimumWeight = 0;
                while (idx != 0)
                {
                    minimumWeight = max(minimumWeight, NodeList[idx].weight);
                    idx = NodeList[idx].prnt;
                }

                cout << "Scenario #" << N << endl;
                cout << "Frog Distance = " << fixed << setprecision(3) << minimumWeight << endl << endl;
                break;
            }


            //If Non Visited node
            if (MST.Union(e.u, e.v)) {
                //add new V nodes edges. (u should've been added by a previous iteration)
                for (int i = 0; i < NodeList[e.v].adj.size; ++i) {
                    //Add if Visited
                    if (MST.Find(e.v) != MST.Find(NodeList[e.v].adj[i].v)) {
                        priorityQueue.add(NodeList[e.v].adj[i]);
                    }
                }
                MSTNodes++;
            }
        }
        cin >> V;
    }
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
