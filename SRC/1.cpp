#include <iostream>
#include <stdexcept>
using namespace std;

template <class T>
class MinPQ {
public:
    virtual ~MinPQ() {}
    virtual bool IsEmpty() const = 0;
    virtual const T& Top() const = 0;
    virtual void Push(const T&) = 0;
    virtual void Pop() = 0;
};

template <class T>
class MinHeap : public MinPQ<T> {
private:
    T* heap;
    int capacity;
    int heapSize;

    void HeapifyUp(int i) {
        while (i > 0 && heap[i] < heap[(i - 1) / 2]) {
            swap(heap[i], heap[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }

    void HeapifyDown(int i) {
        while (true) {
            int left = 2 * i + 1;
            int right = 2 * i + 2;
            int smallest = i;

            if (left < heapSize && heap[left] < heap[smallest]) smallest = left;
            if (right < heapSize && heap[right] < heap[smallest]) smallest = right;

            if (smallest != i) {
                swap(heap[i], heap[smallest]);
                i = smallest;
            } else break;
        }
    }

    void Resize() {
        int newCapacity = capacity * 2;
        T* newHeap = new T[newCapacity];
        for (int i = 0; i < heapSize; i++) newHeap[i] = heap[i];
        delete[] heap;
        heap = newHeap;
        capacity = newCapacity;
    }

public:
    MinHeap(int cap = 10) : capacity(cap), heapSize(0) {
        heap = new T[capacity];
    }

    ~MinHeap() {
        delete[] heap;
    }

    bool IsEmpty() const override {
        return heapSize == 0;
    }

    const T& Top() const override {
        if (IsEmpty()) throw runtime_error("Heap is empty");
        return heap[0];
    }

    void Push(const T& x) override {
        if (heapSize == capacity) Resize();
        heap[heapSize] = x;
        HeapifyUp(heapSize);
        heapSize++;
    }

    void Pop() override {
        if (IsEmpty()) throw runtime_error("Heap is empty");
        heap[0] = heap[heapSize - 1];
        heapSize--;
        if (!IsEmpty()) HeapifyDown(0);
    }
};

int main() {
    MinHeap<int> h(5);
    h.Push(10);
    h.Push(3);
    h.Push(7);
    h.Push(1);

    cout << "MinHeap Top = " << h.Top() << endl; 
    h.Pop();
    cout << "MinHeap Top after Pop = " << h.Top() << endl; 

    return 0;
}