#include <bits/stdc++.h>
using namespace std;

struct Node {
    int data;       // Giá trị của phần tử
    int priority;   // Độ ưu tiên của phần tử
    Node* next;     // Con trỏ đến phần tử tiếp theo
};

// Định nghĩa kiểu NodePointer là con trỏ đến Node để tiện thao tác
typedef Node* NodePointer;

// Hàm khởi tạo danh sách hàng đợi ưu tiên (rỗng)
void createQueue(NodePointer& head) {
    head = nullptr;
}

// Hàm kiểm tra hàng đợi có rỗng hay không
bool isEmpty(NodePointer head) {
    return (head == nullptr);
}

// Hàm thêm phần tử vào hàng đợi ưu tiên (enqueue)
void enqueue(NodePointer& head, int data, int priority) {
    // Tạo một node mới với giá trị và độ ưu tiên cho trước
    NodePointer newNode = new Node;
    newNode->data = data;
    newNode->priority = priority;
    newNode->next = nullptr;

    // Nếu hàng đợi rỗng hoặc độ ưu tiên của node mới cao hơn node đầu tiên
    if (isEmpty(head) || head->priority < priority) {
        newNode->next = head;
        head = newNode;
    } else {
        // Duyệt qua các node để tìm vị trí chèn thích hợp
        NodePointer temp = head;
        // Tìm node có độ ưu tiên thấp hơn hoặc bằng để chèn trước nó
        while (temp->next != nullptr && temp->next->priority > priority) {
            temp = temp->next;
        }
        // Chèn node mới trước các node có cùng độ ưu tiên
        newNode->next = temp->next;
        temp->next = newNode;
    }
}

// Hàm xóa phần tử có độ ưu tiên cao nhất (dequeue)
void dequeue(NodePointer& head) {
    if (isEmpty(head)) {
        cout << "Queue is empty, nothing to dequeue." << endl;
        return;
    }
    NodePointer temp = head;
    head = head->next;
    delete temp;
}

// Hàm hiển thị tất cả phần tử trong hàng đợi
void displayQueue(NodePointer head) {
    NodePointer temp = head;
    while (temp != nullptr) {
        cout << "(" << temp->data << ", " << temp->priority << ")\t";
        temp = temp->next;
    }
    cout << endl;
}

int main() {
    NodePointer priorityQueue;
    createQueue(priorityQueue);

    enqueue(priorityQueue, 9, 2);
    enqueue(priorityQueue, 5, 1);
    enqueue(priorityQueue, 15, 3);
    enqueue(priorityQueue, 7, 2);  // Cùng độ ưu tiên với (9, 2) và được chèn trước
    displayQueue(priorityQueue);

    dequeue(priorityQueue);
    displayQueue(priorityQueue);

    dequeue(priorityQueue);
    displayQueue(priorityQueue);
    return 0;
}
