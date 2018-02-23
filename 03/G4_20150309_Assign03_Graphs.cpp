// GROUP:   4
// ID:      20150309
// Assign:  03
// Assign:  Graphs
// UVA:     924
// Name:    SHERIF MOHAMED ABDEL-NABY

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
    void initialize(int size, int n = 50) {
        this->size = size;
        this->n = max(n, size);


        arr = new T[n];

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

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Node {
    int id;

    Array<int> adj;

    void Initialize(int id);

    void Destroy();
};

void Node::Initialize(int id) {
    this->id = id;
    adj.initialize(0);
}

void Node::Destroy() {
    adj.destroy();
}

struct Graph {
    int n;
    Node *nodes;

    void Initialize(int _n);

    void Destroy();
};

void Graph::Initialize(int _n) {
    n = _n;
    nodes = new Node[n];
}

void Graph::Destroy() {
    delete[] nodes;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class Type>
//this is like the worst queue implementation evar ? :'D
struct Queue {
    int f, n;
    Type *elems;

    void Initialize(int size);

    void Destroy();

    void Add(Type t);

    Type Pop();

    Type Peek();

    int Num();
};

template<class Type>
void Queue<Type>::Initialize(int size) {
    elems = new Type[size];
    n = 0;
    f = 0;
}

template<class Type>
void Queue<Type>::Destroy() {
    delete[] elems;
}

template<class Type>
void Queue<Type>::Add(Type t) {
    elems[n++] = t;
}

template<class Type>
Type Queue<Type>::Pop() {
    return elems[f++];
}

template<class Type>
Type Queue<Type>::Peek() {
    return elems[f];
}

template<class Type>
//Not Sure what should Num() do. Assume return n-f aka size.
int Queue<Type>::Num() {
    return n - f;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int BFS(int nodeIdx, Graph &graph, int E, int &firstMax) {
    //Visited array ( where positive value = day knew )
    int visited[graph.n];
    memset(visited, 0, graph.n * sizeof(int));

    //Variables
    int currDay = 0;
    int maxi = 0;
    int newNews = 0;

    //Queue
    Queue<Node> queue;
    queue.Initialize(E * 15);   //This is Dirty and I hate to do it  :'/

    ///Add First Node to Queue
    queue.Add(graph.nodes[nodeIdx]);
    visited[nodeIdx] = true;


    while (queue.Num()) {
        //Pick from queue and mark as visited.
        Node picked = queue.Pop();

        //If we're in a new currDay -> calculate past currDay's total new news.
        if (visited[picked.id] != currDay) {
            if (maxi < newNews) {
                firstMax = currDay;
                maxi = newNews;
            }
            ++currDay;
            newNews = 0;
        }

        //Add Adjacent non visited nodes
        for (int i = 0; i < picked.adj.size; ++i) {
            if (!visited[picked.adj[i]]) {
                queue.Add((graph.nodes[picked.adj[i]]));
                visited[picked.adj[i]] = currDay + 1;
                ++newNews;
            }
        }
    }
    return maxi;
}

int main() {
    int E, N, A, TC, T;
    cin >> E;

    Graph network;
    network.Initialize(E);

    for (int i = 0; i < E; ++i) {
        network.nodes[i].Initialize(i);
        cin >> N;
        for (int j = 0; j < N; ++j) {
            cin >> A;
            network.nodes[i].adj.addLast(A);
        }
    }
    cin >> TC;
    for (int i = 0; i < TC; ++i) {
        cin >> T;
        int firstMax = 0;
        int maxHeard = BFS(T, network, E, firstMax);
        if (maxHeard == 0)
            cout << 0 << endl;
        else
            cout << maxHeard << " " << firstMax << endl;
    }

    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
