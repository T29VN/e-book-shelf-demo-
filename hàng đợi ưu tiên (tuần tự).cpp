#include <iostream>
using namespace std;
#define MAX 100

struct Element {
    int value;
    int priority;
};

struct PriorityQueue {
    Element infor[MAX];
    int size;
};

bool isfull(PriorityQueue* pq) {
    return (pq->size == MAX);
}

bool isempty(PriorityQueue* pq) {
    return (pq->size == 0);
}

void enPriorityQueue(PriorityQueue* pq, Element e) {
    if (isfull(pq)) {
        cout << "\nHàng đợi đầy";
        return;
    }

    int i;
    for (i = pq->size - 1; i >= 0; i--) {
        if (e.priority >= pq->infor[i].priority) {
            pq->infor[i + 1] = pq->infor[i];
        } else {
            break;
        }
    }
    pq->infor[i + 1] = e;
    pq->size++;
}

Element dePriorityQueue(PriorityQueue* pq) {
    if (isempty(pq)) {
        cout << "Hàng đợi rỗng\n";
        return {-1, -1};
    }
    Element e = pq->infor[0];
    for (int i = 0; i < pq->size - 1; i++) {
        pq->infor[i] = pq->infor[i + 1];
    }
    pq->size--;
    return e;
}

void display(PriorityQueue* pq) {
    if (isempty(pq)) {
        cout << "\nHàng đợi rỗng";
        return;
    }
    cout << "\nCác phần tử trong hàng đợi: ";
    for (int i = 0; i < pq->size; i++) {
        cout << "(" << pq->infor[i].value << ", " << pq->infor[i].priority << ") ";
    }
    cout << endl;
}

int main() {
    PriorityQueue pq;
    pq.size = 0;

    Element e1 = {3, 2};
    Element e2 = {5, 1};
    Element e3 = {9, 3};

    enPriorityQueue(&pq, e1);
    enPriorityQueue(&pq, e2);
    enPriorityQueue(&pq, e3);

    display(&pq);

    Element e_ = {4, 2};
    enPriorityQueue(&pq, e_);
    display(&pq);

    Element e = dePriorityQueue(&pq);
    cout << "\nPhần tử được lấy ra: (" << e.value << ", " << e.priority << ")" << endl;

    display(&pq);

    Element eA = dePriorityQueue(&pq);
    cout << "\nPhần tử được lấy ra: (" << eA.value << ", " << eA.priority << ")" << endl;

    display(&pq);
    return 0;
}
