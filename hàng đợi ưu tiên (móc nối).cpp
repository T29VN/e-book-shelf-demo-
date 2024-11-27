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

// Hàm truy vấn phần tử có độ ưu tiên cao nhất (peek)
void peek(NodePointer head) {
    if (isEmpty(head)) {
        cout << "Queue is empty, no element to peek." << endl;
        return;
    }
    cout << "Top element: (" << head->data << ", " << head->priority << ")" << endl;
}

// Hàm cập nhật độ ưu tiên của một phần tử
void updatePriority(NodePointer& head, int data, int newPriority) {
    if (isEmpty(head)) {
        cout << "Queue is empty, cannot update priority." << endl;
        return;
    }

    // Tìm và xóa node có giá trị `data`
    NodePointer temp = head, prev = nullptr;
    while (temp != nullptr && temp->data != data) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == nullptr) {
        cout << "Element with data " << data << " not found." << endl;
        return;
    }

    // Xóa node tìm thấy
    if (prev == nullptr) {
        head = head->next;
    } else {
        prev->next = temp->next;
    }
    delete temp;

    // Chèn lại node với độ ưu tiên mới
    enqueue(head, data, newPriority);
}

int main() {
    NodePointer priorityQueue;
    createQueue(priorityQueue);

    // Thêm phần tử vào hàng đợi
    enqueue(priorityQueue, 9, 2);
    enqueue(priorityQueue, 5, 1);
    enqueue(priorityQueue, 15, 3);
    enqueue(priorityQueue, 7, 2);
    cout << "Initial queue: ";
    displayQueue(priorityQueue);

    // Truy vấn phần tử có độ ưu tiên cao nhất
    peek(priorityQueue);

    // Cập nhật độ ưu tiên
    cout << "Updating priority of element 9 to 4." << endl;
    updatePriority(priorityQueue, 9, 4);
    displayQueue(priorityQueue);

    // Xóa phần tử
    dequeue(priorityQueue);
    cout << "After dequeue: ";
    displayQueue(priorityQueue);

    // Truy vấn sau khi xóa
    peek(priorityQueue);

    return 0;
}
