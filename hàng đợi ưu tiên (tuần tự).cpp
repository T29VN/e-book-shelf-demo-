#include <iostream>
using namespace std;
#define MAX 100 // Định nghĩa kích thước tối đa của hàng đợi

// Định nghĩa cấu trúc của một phần tử trong hàng đợi
struct Element {
    int value;    // Giá trị của phần tử
    int priority; // Độ ưu tiên của phần tử
};

// Định nghĩa cấu trúc hàng đợi ưu tiên
struct PriorityQueue {
    Element infor[MAX]; // Mảng lưu các phần tử trong hàng đợi
    int size;           // Số lượng phần tử hiện tại trong hàng đợi
};

// Hàm khởi tạo PriorityQueue
PriorityQueue createPriorityQueue() {
    PriorityQueue pq;
    pq.size = 0; // Gán kích thước ban đầu là 0
    return pq;
}

// Hàm kiểm tra hàng đợi có đầy hay không
bool isfull(PriorityQueue* pq) {
    return (pq->size == MAX); // Trả về true nếu số phần tử bằng MAX
}

// Hàm kiểm tra hàng đợi có rỗng hay không
bool isempty(PriorityQueue* pq) {
    return (pq->size == 0); // Trả về true nếu không có phần tử nào
}

// Hàm thêm một phần tử vào hàng đợi ưu tiên
void enPriorityQueue(PriorityQueue* pq, Element e) {
    if (isfull(pq)) { // Kiểm tra nếu hàng đợi đầy
        cout << "\nHàng đợi đầy";
        return;
    }

    int i;
    // Duyệt từ cuối danh sách để tìm vị trí chèn phần tử theo độ ưu tiên
    for (i = pq->size - 1; i >= 0; i--) {
        if (e.priority >= pq->infor[i].priority) {
            pq->infor[i + 1] = pq->infor[i]; // Dịch phần tử về sau
        } else {
            break; // Tìm thấy vị trí thích hợp
        }
    }
    pq->infor[i + 1] = e; // Chèn phần tử vào vị trí đã tìm
    pq->size++; // Tăng số lượng phần tử
}

// Hàm lấy phần tử có độ ưu tiên cao nhất ra khỏi hàng đợi
Element dePriorityQueue(PriorityQueue* pq) {
    if (isempty(pq)) { // Kiểm tra nếu hàng đợi rỗng
        cout << "Hàng đợi rỗng\n";
        return {-1, -1}; // Trả về phần tử mặc định
    }
    Element e = pq->infor[0]; // Lấy phần tử đầu tiên (cao nhất)
    // Dịch chuyển các phần tử còn lại lên trước
    for (int i = 0; i < pq->size - 1; i++) {
        pq->infor[i] = pq->infor[i + 1];
    }
    pq->size--; // Giảm số lượng phần tử
    return e; // Trả về phần tử vừa lấy ra
}

// Hàm hiển thị tất cả các phần tử trong hàng đợi
void display(PriorityQueue* pq) {
    if (isempty(pq)) { // Kiểm tra nếu hàng đợi rỗng
        cout << "\nHàng đợi rỗng";
        return;
    }
    cout << "\nCác phần tử trong hàng đợi: ";
    // Duyệt qua tất cả các phần tử và in ra giá trị, độ ưu tiên
    for (int i = 0; i < pq->size; i++) {
        cout << "(" << pq->infor[i].value << ", " << pq->infor[i].priority << ") ";
    }
    cout << endl;
}

// Hàm truy vấn phần tử có độ ưu tiên cao nhất (peek)
Element peek(PriorityQueue* pq) {
    if (isempty(pq)) {
        cout << "\nHàng đợi rỗng, không thể truy vấn.";
        return {-1, -1}; // Trả về phần tử mặc định
    }
    return pq->infor[0]; // Trả về phần tử đầu tiên (cao nhất)
}

// Hàm cập nhật độ ưu tiên của một phần tử
void updatePriority(PriorityQueue* pq, int value, int newPriority) {
    if (isempty(pq)) {
        cout << "\nHàng đợi rỗng, không thể cập nhật độ ưu tiên.";
        return;
    }

    // Tìm phần tử có giá trị `value`
    int index = -1;
    for (int i = 0; i < pq->size; i++) {
        if (pq->infor[i].value == value) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "\nKhông tìm thấy phần tử có giá trị " << value << ".";
        return;
    }

    // Xóa phần tử khỏi hàng đợi
    Element temp = pq->infor[index];
    for (int i = index; i < pq->size - 1; i++) {
        pq->infor[i] = pq->infor[i + 1];
    }
    pq->size--;

    // Cập nhật độ ưu tiên và chèn lại
    temp.priority = newPriority;
    enPriorityQueue(pq, temp);
}

int main() {
    PriorityQueue pq = createPriorityQueue();

    // Thêm các phần tử vào hàng đợi
    enPriorityQueue(&pq, {3, 2});
    enPriorityQueue(&pq, {0, 2});
    enPriorityQueue(&pq, {5, 1});
    enPriorityQueue(&pq, {9, 3});
    display(&pq);

    // Truy vấn phần tử có độ ưu tiên cao nhất
    Element top = peek(&pq);
    cout << "\nPhần tử có độ ưu tiên cao nhất: (" << top.value << ", " << top.priority << ")" << endl;

    // Cập nhật độ ưu tiên của phần tử
    cout << "\nCập nhật độ ưu tiên của phần tử 3 thành 4.";
    updatePriority(&pq, 3, 4);
    display(&pq);

    // Lấy ra phần tử có độ ưu tiên cao nhất
    Element e = dePriorityQueue(&pq);
    cout << "\nPhần tử được lấy ra: (" << e.value << ", " << e.priority << ")" << endl;
    display(&pq);

    return 0;
}
