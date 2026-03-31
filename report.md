#41343146
# 作業一 problem1

## 解題說明

本題要求實作 Min Priority Queue (MinPQ)，並使用 Min Heap
來完成其功能。需要支援基本操作如 Push、Pop、Top 以及 IsEmpty。

## 解題策略

1.  先定義一個抽象類別 MinPQ，作為最小優先佇列的介面。
2.  使用陣列實作 Min Heap，維持完全二元樹結構。
3.  插入元素時使用 HeapifyUp 維持最小堆性質。
4.  刪除最小元素時使用 HeapifyDown 調整結構。
5.  若陣列空間不足則進行動態擴充。

## 程式實作

``` cpp
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
```

## 效能分析

  操作      時間複雜度
  --------- ------------
  Push      O(log n)
  Pop       O(log n)
  Top       O(1)
  IsEmpty   O(1)

空間複雜度：O(n)

## 測試與驗證

  測試項目   操作             預期結果   實際結果
  ---------- ---------------- ---------- ----------
  測試一     Push(10,3,7,1)   Top = 1    正確
  測試二     Pop()            Top = 3    正確

## 結論

1.  本程式成功實作 Min Heap 作為 Min Priority Queue。
2.  所有操作皆符合預期時間複雜度。
3.  可以正確維持最小堆的性質。

## 討論

優點：- 結構簡單

缺點： - 使用動態陣列需手動管理記憶體 - 未處理拷貝問題（可能造成問題）
