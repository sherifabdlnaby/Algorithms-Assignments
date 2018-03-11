// GROUP:   4
// ID:      20150309
// Assign:  07
// Assign:  Dijkstra
// UVA:     10986
// Name1:   Sherif Abdel-Naby
// UVA Username: sherifabdlnaby

#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
        return arr.size <= 0;
    }

    int size() {
        return arr.size;
    }
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Edge
{
    int		v;
    int		w;
};

struct Node
{
    Array<Edge> adj;
    void Initialize(){}
    void Destroy(){adj.destroy();}
};

struct Graph
{
    int n;
    Node* nodes;

    void Initialize(int _n){
        n = _n;
        nodes = new Node[n];
    }
    void Destroy(){
        for (int i = 0; i < n; ++i) {
            nodes[i].adj.destroy();
        }
        delete[] nodes;
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool IsBefore(Edge& a, Edge& b)
{
    return a.w<b.w;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    int N, n, m, S, T;
    cin >> N;

    for (int t = 0; t < N; ++t) {
        cin >> n >> m >> S >> T;
        Graph graph;
        graph.Initialize(n);
        int u,v,w;
        for (int i = 0; i < m; ++i) {
            cin >> u >> v >> w;
            graph.nodes[u].adj.addLast({.v = v, .w = w});
            graph.nodes[v].adj.addLast({.v = u, .w = w});
        }

        bool visited[n];
        memset(visited,0, sizeof(bool)*n);

        Heap<Edge> priorityQueue;
        priorityQueue.initialize(IsBefore);

        //Add Initial
        for (int i = 0; i < graph.nodes[S].adj.size; ++i)
            priorityQueue.add(graph.nodes[S].adj[i]);
        visited[S] = true;

        Edge e; e.w = 0; e.v = -1;
        while(!priorityQueue.isEmpty() && e.v != T){
            e = priorityQueue.retrieveFirst();
            visited[e.v] = true;
            //Add Adjacent
            for (int i = 0; i < graph.nodes[e.v].adj.size; ++i) {
                if(!visited[graph.nodes[e.v].adj[i].v]) {
                    graph.nodes[e.v].adj[i].w += e.w;
                    priorityQueue.add(graph.nodes[e.v].adj[i]);
                }
            }
        }

        if (e.v == T) {
            cout << "Case #" << t + 1 << ": " << e.w << endl;
        } else {
            cout << "Case #" << t + 1 << ": " << "unreachable" << endl;
        }

    }
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
