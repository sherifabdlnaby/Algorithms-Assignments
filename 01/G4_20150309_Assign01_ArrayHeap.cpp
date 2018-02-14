// GROUP:   4
// ID:      20150309
// Assign:  01
// Assign:  ArrayHeap
// UVA:     10954
// Name:    Sherif Abdel-Naby

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

template<class T>
struct Array {
    T *arr;
    int n;      //Capacity
    int size;   //Init Size
    void initialize(int size, int n) {
        this->size = size;
        this->n = n;


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

template<class T>
struct Heap {
    Array<T> arr;

    bool (*isBefore)(T &a, T &b);

    void initialize(bool (*__isBefore)(T &a, T &b)) {
        arr.initialize(0,1);
        isBefore = __isBefore;
    }

    void destroy() {
        arr.destroy();

    }

    void print() {

        arr.print();

        int levels = (int) log2(arr.size);
        int spaces = (int) pow(2, levels) / 2;
        int l = 0;
        int levelBeginIdx = 0;
        int n = arr.size;
        while (l <= levels) {


            for (int i = levelBeginIdx; i <= levelBeginIdx * 2 && i < n; ++i) {

                //print spaces
                for (int j = 0; j < spaces; ++j) {
                    cout << " ";
                }


                cout << arr[i] << " ";

            }

            cout << endl;

            spaces /= 2;
            ++l;
            levelBeginIdx = (int) pow(2, l) - 1;

            if (l > levels)
                break;


            for (int i = levelBeginIdx; i <= levelBeginIdx * 2 && i < n; ++i) {
                //print spaces
                for (int j = 0; j < spaces; ++j) {
                    cout << " ";
                }

                cout << (i % 2 ? "/" : "\\") << " ";
            }

            cout << endl;
        }
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

bool cmp1(int &X, int &Y) {
    return X < Y;
}

int main() {
    int n = -1;
    int tmp;
    while(true)
    {
        cin >> n;
         if(n == 0)
             break;

        Heap<int> heap;
        heap.initialize(cmp1);
        for (int i = 0; i < n; ++i) {
            cin >> tmp;
            heap.add(tmp);
        }

        //begin pairing
        int sum = 0;
        while(heap.size() > 1)
        {
            int addition = heap.retrieveFirst() + heap.retrieveFirst();
            heap.add(addition);
            sum += addition;
        }

        cout << sum << endl;
    }
}