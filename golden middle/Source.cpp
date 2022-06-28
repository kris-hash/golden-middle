#include <fstream>
#include <vector>

using namespace std;

bool compMax(int left, int right) {
    if (left < right) {
        return true;
    }
    return false;
}

bool compMin(int left, int right) {
    if (left > right) {
        return true;
    }
    return false;
}

class Heap {
public:
    vector<int> heap_data;
    bool (*comp)(int left, int right);
    Heap(bool (*comp)(int left, int right)) {
        heap_data.push_back(0);
        this->comp = comp;
    }

    /*int size() {
        return heap_data.size();
    }*/

    void push(int el) {
        heap_data.push_back(el);
        sift_up(heap_data.size() - 1);
    }

    void pop() {
        if (heap_data.size() > 1) {
            heap_data[1] = heap_data.back();
            heap_data.pop_back();
            heapify(1);
        }
        else {
            return;
        }
    }

    /*void swap(int a, int b) {
        int temp = heap_data[a];
        heap_data[a] = heap_data[b];
        heap_data[b] = temp;
    }*/

    int getMax() {
        if (heap_data.size() > 1) {
            return heap_data[1];
        }
        else {
            return INT_MIN;
        }
    }

    void heapify(int vertex) {
        if (vertex * 2 >= heap_data.size()) {
            return;
        }
        int max_idx;
        if (vertex * 2 + 1 == heap_data.size()) {
            max_idx = vertex * 2;
        }
        else if (!comp(heap_data[vertex * 2], heap_data[vertex * 2 + 1])) {
            max_idx = vertex * 2;
        }
        else {
            max_idx = vertex * 2 + 1;
        }

        if (comp(heap_data[vertex], heap_data[max_idx])) {
            swap(heap_data[vertex], heap_data[max_idx]);
            heapify(max_idx);
        }
    }

    void sift_up(int vertex) {
        if (vertex == 1) {
            return;
        }

        if (comp(heap_data[vertex >> 1], heap_data[vertex])) {
            swap(heap_data[vertex], heap_data[vertex >> 1]);
            sift_up(vertex >> 1);
        }
    }
};

int main() {
    ifstream f1("input.txt");
    ofstream f2("output.txt");

    Heap* min_Heap = new Heap(compMin);
    Heap* max_Heap = new Heap(compMax);

    int n, c;
    f1 >> n >> c;
    f2 << c << ' ';

    int count_max = 0;
    int count_min = 0;

    for (int i = 1; i < n; i++) {
        int idx_next;
        f1 >> idx_next;

        if (idx_next > c) {
            min_Heap->push(idx_next);
            count_min += 1;


            if (count_min - count_max >= 2) {
                max_Heap->push(c);
                count_max += 1;

                c = min_Heap->getMax();
                min_Heap->pop();
                count_min -= 1;
            }
        }

        else {
            max_Heap->push(idx_next);
            count_max += 1;

            if (count_max - count_min >= 2) {
                min_Heap->push(c);
                count_min++;

                c = max_Heap->getMax();
                max_Heap->pop();
                count_max--;
            }
            else if (count_max - count_min == 1) {
                min_Heap->push(c);
                count_min++;

                c = max_Heap->getMax();
                max_Heap->pop();
                count_max--;
            }
        }
        f2 << c << ' ';
    }
    return 0;
}
