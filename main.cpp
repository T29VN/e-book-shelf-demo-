#include <bits/stdc++.h>
using namespace std;

struct Node {
    int info;
    int Priority;
    Node* next;
};

typedef Node* Linkedlist;
typedef Node* PNode;

// Hàm tạo danh sách
void Creatlist(Linkedlist& H) {
    H = NULL;
}

// Hàm kiểm tra rỗng
int Isempty(Linkedlist H) {
    return (H == NULL);
}

// Hàm chèn vào danh sách theo thứ tự ưu tiên
void InsertPriority(Linkedlist& H, int k, int priority) {// chính là enqueue
    PNode Q = new Node;
    Q->info = k;
    Q->Priority = priority;

    // Nếu danh sách rỗng hoặc priority của Q cao hơn node đầu tiên
    if (Isempty(H) || H->Priority < priority) {
        Q->next = H;
        H = Q;
    } else {
        PNode P = H;
        // Duyệt danh sách để tìm vị trí chèn
        while (P->next != NULL && P->next->Priority >= priority) {
            P = P->next;
        }
        Q->next = P->next;
        P->next = Q;
    }
}

// Hàm xóa node đầu tiên
void Deletefirstnode(Linkedlist& H) {// chính là dequeue
    if (Isempty(H)) {
        cout << "List is empty, nothing to delete." << endl;
        return;
    }
    PNode P = H;
    H = H->next;
    delete P;
}

// Hàm hiển thị danh sách
void Display(Linkedlist& H) {
    PNode P = H;
    while (P != NULL) {
        cout << "(" << P->info << ", " << P->Priority << ")\t";
        P = P->next;
    }
    cout << endl;
}

int main() {
    Linkedlist S;
    Creatlist(S);

    InsertPriority(S, 9, 2);
    InsertPriority(S, 5, 1);
    InsertPriority(S, 15, 3);
    InsertPriority(S, 7, 2);
    Display(S);

    Deletefirstnode(S);
    Display(S);

    return 0;
}
