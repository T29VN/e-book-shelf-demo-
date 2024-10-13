#include <iostream>  //xin chào mọi người
#include <string>
#include <vector>
#include <fstream>  	// Thư viện để đọc và ghi file
#include <sstream>   	// thư viện dùng để sử dụng hàm tách các thuộc tính
#include <ctime>     	// Để lấy thời gian hiện tại

using namespace std;


// Cấu trúc Book lưu trữ thông tin của một cuốn sách
struct Book 
{
    string title;		// tên sách
    string author;		// tác giả
    int year;			// năm xuất bản
    string NXB; 		// nhà xuất bản
    string country; 	// quốc gia
    int page; 			// số trang sách
    double costb;		// giá tiền
    int reprint;		// tái bản lần thứ
    int msbook;			// mã số sách
};


//tạo kệ sách
struct Node 
{
    Book info;     // Thông tin cuốn sách
    Node* next;    // truy cập cuốn sách kế tiếp
};


typedef Node* PNode;		// chỉ 1 cuốn sách
typedef Node* LinkedList;	// chỉ nhiều cuốn sách


// tạo kệ sách rỗng
void InitList(LinkedList &H) 
{
    H = NULL;
}


// kiểm tra kệ sách có rỗng không
bool IsEmpty(LinkedList H) 
{
    return (H == NULL);
}


//hàm nhập thông tin sách
void InputBook(Book &b) 
{
    cout << "Nhap ten sach: ";
    cin.ignore(); // Loại bỏ newline còn sót từ các lệnh nhập trước
    getline(cin, b.title);// đọc 1 dòng văn bản từ cin và lưu vào b.title

    cout << "Nhap ten tac gia: ";
    getline(cin, b.author);

    cout << "Nhap nam xuat ban: ";
    cin >> b.year;
    cin.ignore(); // Loại bỏ newline trước khi sử dụng getline

    cout << "Nhap nha xuat ban: ";
    getline(cin, b.NXB);

    cout << "Nhap quoc gia phat hanh: ";
    getline(cin, b.country);

    cout << "Nhap so trang sach: ";
    cin >> b.page;

    cout << "Nhap gia tien: ";
    cin >> b.costb;

    cout << "Nhap so lan tai ban: ";
    cin >> b.reprint;
    
    cout << "Ma so sach: ";
    cin >> b.msbook;
}


// Hàm hiển thị thông tin sách
void ShowBook(const Book &b) 
{
    cout << "--------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "Ten sach       : " << b.title << endl;
    cout << "Tac gia        : " << b.author << endl;
    cout << "Nam xuat ban   : " << b.year << endl;
    cout << "Nha xuat ban   : " << b.NXB << endl;
    cout << "Quoc gia       : " << b.country << endl;
    cout << "Tong so trang  : " << b.page << endl;
    cout << "Gia            : " << b.costb << " VND" << endl;
    cout << "So lan tai ban : " << b.reprint << endl;
    cout << "Ma so sach     : " << b.msbook << endl;
    cout << "--------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
}


// Hàm thêm sách vào đầu kệ sách
void InsertStart(LinkedList &H, const Book &b) // const đảm bảo sách không bị đổi bên trong hàm
{
	
	//tạo chỗ chứa cho cuốn sách mới
    PNode Q = new Node;
    Q->info = b;
    
    // liên kết cuốn sách vào vị trị đầu tiên
    Q->next = H;
    H = Q;// cập nhật nút Q là cuốn sách đầu và H lại trỏ vào Q 
    
    /*         Ví dụ: H --> [Node1] --> [Node2] --> NULL (lúc đầu)
	                  H --> [Q (Node mới)] --> [Node1] --> [Node2] --> NULL(lúc sau)           */
    
}

// Hàm thêm sách vào cuối kệ sách
void InsertEnd(LinkedList &H, const Book &b) 
{
    PNode Q = new Node;
    Q->info = b;
    
    if (H == NULL) {
        Q->next = NULL;
        H = Q;
    } else {
        PNode P = H;
        while (P->next != NULL) {
            P = P->next;
        }
        //hết vòng P -> next đang trỏ tới NULL và P đang ở vị trí cuối
        P->next = Q;// cập nhật P trỏ vào cuốn sách mới
    }
}

// Hàm hiển thị toàn bộ sách hiện có
void ShowList(LinkedList H) 
{
    PNode P = H;
    while (P != NULL) {
        ShowBook(P->info);
        P = P->next;
    }
}

// Hàm hoán đổi vị trí của hai sách trong kệ sách
void SwapBook(LinkedList &H, int index1, int index2) 
{
	//nếu 2 vị trí trùng nhau
    if (index1 == index2) return;
	
	//Xác định các vị trí cần hoán đổi
    PNode P1 = H, P2 = H;
    for (int i = 0; i < index1 && P1 != NULL; ++i) P1 = P1->next;
    for (int i = 0; i < index2 && P2 != NULL; ++i) P2 = P2->next;
	
	// hoán đổi
    if (P1 != NULL && P2 != NULL) {
        Book temp = P1->info;// hoặc viết như này (*P1).info cũng được
        P1->info = P2->info;
        P2->info = temp;
    }
}

// Hàm thêm sách vào vị trí bất kỳ trong danh sách
void AddBook(LinkedList &H, int index, const Book &b) 
{
    //thêm vào đầu danh sách
    if (index == 0) {
        InsertStart(H, b);
        return;
    }
	
	// duyệt 
    PNode P = H;
    for (int i = 0; i < index - 1 && P != NULL; ++i) P = P->next;// kết thúc P đang ở index - 1
    if (P == NULL) return;
	
	//tạo cuốn sách mới và chỗ chứa
    PNode Q = new Node;
    Q->info = b;
    
    //Thêm sách vào vị trí đã chọn
    Q->next = P->next;
    P->next = Q;
}

// Hàm xóa sách có thông tin trống và trả về số sách đã xóa
void DeleteNodeEmpty(LinkedList &H, int &count) {
    PNode P = H, L = NULL;
    count = 0;
    while (P != NULL) {
        if (P->info.title.empty() || P->info.author.empty()) {
            if (L == NULL) {// nếu P là nút đầu tiên của danh sách thỏa mãn điều kiện xóa
                H = P->next;
                delete P;
                P = H;
            } else {
                L->next = P->next;
                delete P;
                P = L->next;
            }
            count++;
        } else {
            L = P;
            P = P->next;
        }
    }
}


// chưa rõ từ đây
// Hàm sắp xếp sách theo thứ tự chữ cái sử dụng sắp xếp nổi bọt
void ExchangeSort(LinkedList &H) {
    if (H == NULL) return;
    bool swapped;// để kiểm tra xem có xảy ra hoán đổi không 	
    PNode P;
    do {
        swapped = false;
        P = H;
        while (P->next != NULL) {
            if (P->info.title > P->next->info.title) {//so sánh từ 2 ký tự đầu chuỗi
                swap(P->info, P->next->info);// lấy ở thư viện
                swapped = true;
            }
            P = P->next;
        }
    } while (swapped);
}

// Hàm tự động sắp xếp sách 
void AutoSort(LinkedList &H) {
    ExchangeSort(H);
}

// Hàm tìm kiếm sách sử dụng thuật toán KMP 
void initNext(const string &pattern, vector<int> &next) {
    int m = pattern.size();
    next[0] = 0;
    int len = 0;
    int i = 1;
    while (i < m) {
        if (pattern[i] == pattern[len]) {
            len++;
            next[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = next[len - 1];
            } else {
                next[i] = 0;
                i++;
            }
        }
    }
}

int KMPSearch(const string &text, const string &pattern) {
    int n = text.size();
    int m = pattern.size();
    vector<in`````` bvbt> next(m);
    initNext(pattern, next);

    int i = 0, j = 0;
    while (i < n) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }
        if (j == m) {
            return i - j;
            j = next[j - 1];
        } else if (i < n && pattern[j] != text[i]) {
            if (j != 0) j = next[j - 1];
            else i++;
        }
    }
    return -1;
}
// đến đây



// Hàm tính tổng só sách
int Sumofbook (LinkedList & H)
{
    PNode P = H;
    int count = 0;
    while (P != NULL){
        count ++;
        P = P -> next;
    }
    cout << "Tong so sach hien co: " << count << endl;
    return count;
}

// hàm xóa một cuốn sách bất kỳ ra khỏi danh sách
void Deletebook(LinkedList &H, const string &title) {
    PNode P = H, prev = NULL;
    while (P != NULL) {
        // Kiểm tra xem tiêu đề của cuốn sách có trùng với tiêu đề cần xóa không
        if (P->info.title == title) {
            if (prev == NULL) {// nếu P là cuốn đầu
                H = P->next;  // Xóa đầu danh sách
                delete P;
                return;
            } else {
                prev->next = P->next;  // Xóa giữa hoặc cuối danh sách
                delete P;
                return;
            }
        }
        prev = P;
        P = P->next;
    }
    cout << "\n[Khong tim thay sach voi ten cua sach '" << title << "'.]\n";
}


// Hàm đọc dữ liệu sách từ file và thêm vào danh sách
void ReadFromFile(LinkedList &H, const string &filename) {
    ifstream file(filename); // Mở file để đọc
    if (!file.is_open()) {
        cout << "\n[Loi: Khong the mo file '" << filename << "'.]\n";
        return;
    }

    string line;
    while (getline(file, line)) {
        Book b;
        stringstream ss(line); // Sử dụng stringstream để tách các thuộc tính
        string temp;

        try {
            // Đọc tên sách
            getline(ss, b.title, ',');

            // Đọc tên tác giả
            getline(ss, b.author, ',');

            // Đọc năm xuất bản
            getline(ss, temp, ',');
            b.year = stoi(temp);// chuyển đổi từ chuỗi sang kiểu số (stoi cho số nguyên)

            // Đọc nhà xuất bản
            getline(ss, b.NXB, ',');

            // Đọc quốc gia
            getline(ss, b.country, ',');

            // Đọc số trang
            getline(ss, temp, ',');
            b.page = stoi(temp);

            // Đọc giá tiền
            getline(ss, temp, ',');
            b.costb = stod(temp);// chuyển đổi từ chuỗi sang kiểu số (stod cho số thực)

            // Đọc số lần tái bản
            getline(ss, temp, ',');
            b.reprint = stoi(temp);

            // Thêm sách vào cuối danh sách
            InsertEnd(H, b);
        }
        catch (const exception &e) {
            cout << "[Loi: Khong the doc dong trong file. Dong khong hop le: " << line << "]\n";
        }
    }

    file.close(); // Đóng file sau khi đọc xong
    cout << "\n[Du lieu sach da duoc doc tu file '" << filename << "' thanh cong.]\n";
}



// hàm viet dữ liệu lên file
void WriteToFile(const string &filename, LinkedList H) {
    ofstream outFile(filename);// mở cái file cần viết
    if (!outFile) {
        cout << "Khon the mo file " << filename << " de ghi." << endl;
        return;
    }

    PNode P = H;
    while (P != NULL) {
        outFile << P->info.title << "," // ghi tưng thông tin bằng outfile và toán tử xuất
                << P->info.author << "," 
                << P->info.year << "," 
                << P->info.NXB << "," 
                << P->info.country << "," 
                << P->info.page << "," 
                << P->info.costb << "," 
                << P->info.reprint << endl;
        P = P->next;
    }

    outFile.close();
    cout << "Da ghi du lieu vào file " << filename << " thanh cong." << endl;
}


// hàm có thể chọn vài cuốn sách sau đó tính tiền số sách đã mua

void buybook(LinkedList &H) {
    cout << "Ban muon mua nhung cuon sach nao?" << endl;
    ShowList(H); // Hiển thị danh sách sách

    int ms;
    double Sum = 0;
    PNode P;

    // Chọn sách muốn mua
    cout << "(sau khi chon xong an 0 de thoat)" << " => " << "Chon mua(theo ma):" << endl;
    
    do {
        cin >> ms;

        P = H;// gán vào ở đây chưa rõ lý do gán ngoài lại ko chạy ^^
        bool found = false;
        
        while (P != NULL) {
            if (P->info.msbook == ms) { 
                Sum += P->info.costb; 
                found = true;
                break;// thoát vòng lặp chứ ko thoát hẳn vì nằm trong do while
            }
            P = P->next;
        }
        
        if (!found) {// nếu while ko tìm đc cuốn nào thì found vẫn bằng false
            cout << "[Khong tim thay sach voi ma: " << ms << "]" << endl;
        }
        
    } while (ms != 0);
    
    cout << "Tong thiet hai: " << Sum << " VND" << endl;
}



// Hàm ghi nhận nhận xét của người dùng vào file
void feedback() {
    string userFeedback;
    string filename = "feedback .txt";// file này đã có trên máy

    // Lấy nhận xét từ người dùng
    cout << "Nhan xet cua ban: ";
    cin.ignore();  // Loại bỏ newline từ các lệnh nhập trước (nếu có)
    getline(cin, userFeedback);

    // Mở file để ghi nhận xét
    ofstream outFile(filename, ios::app);  // Chế độ append để không ghi đè file

    // Kiểm tra xem file có mở thành công không
    if (!outFile) {
        cout << "ERROR" << endl;
        return;
    }

    // Lấy thời gian hiện tại
    time_t now = time(0);
    char* dt = ctime(&now);

    // Ghi thời gian và nhận xét vào file
    outFile << "Thoi gian: " << dt;
    outFile << "Nhan xet: " << userFeedback << endl;
    outFile << "------------------------------------------" << endl;

    // Đóng file
    outFile.close();
    cout << "Cam on ban" << endl;
}

// tìm cuốn sách đắt tiền nhất
void Searchmax (LinkedList &H){
	if (IsEmpty(H)){
		cout << "het sach" << endl;
		return;
	}
	
	PNode P = H;
	PNode maxbook = P;// gán tạm cái này làm cuốn đắt nhất
	while (P != NULL){
		if (P ->info.costb > maxbook->info.costb){
			maxbook = P;
		}
		P = P -> next;
	}
	
	cout << "Cuon sach dat tien nhat la: " << maxbook -> info.title << endl;
	cout << "Gia: " << maxbook -> info.costb << " VND" << endl;
}

//tìm cuốn sách rẻ tiền nhất
void Searchmin (LinkedList & H){
	if (IsEmpty (H)){
		cout << "het sach" << endl;
		return;
	}
	
	PNode P = H;
	PNode Minbook = P;
	while (P != NULL){
		if (P -> info.costb < Minbook -> info.costb){
			Minbook = P;		
		}
		P = P -> next;
	}
	
	cout << "Cuon sach gia re nhat la: " << Minbook -> info.title << endl;
	cout << "Gia: " << Minbook -> info.costb << " VND" << endl;
}



// Menu cho các chức năng
void Menu(LinkedList &H) {
    int choice;
    do {
        
        
        // Giao diện menu
        cout << " _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ " << endl;
        cout << "|                     ~~~~~~ MENU ~~~~~~                     |"<< endl;
        cout << "|------------------------------------------------------------|"<< endl;
        cout << "| 1. Them sach vao dau danh sach                             |"<< endl;
        cout << "| 2. Them sach vao cuoi danh sach                            |"<< endl;
        cout << "| 3. Hien thi danh sach sach                                 |"<< endl;
        cout << "| 4. Hoan doi hai cuon sach                                  |"<< endl;
        cout << "| 5. Them sach vao vi tri tuy chon                           |"<< endl;
        cout << "| 6. Xoa sach rong                                           |"<< endl;
        cout << "| 7. Sap xep sach theo thu tu chu cai                        |"<< endl;
        cout << "| 8. Tim kiem sach theo ten                                  |"<< endl;
        cout << "| 9. Thong ke tong so sach                                   |"<< endl;
        cout << "| 10. Xoa di mot cuon sach bat ky theo ten                   |"<< endl;
        cout << "| 11. Nhap du lieu tu tai lieu co san                        |"<< endl;
        cout << "| 12. Ghi du lieu len tai lieu co san                        |"<< endl;
        cout << "| 13. Tinh tong tien nhung cuon sach ban muon mua            |"<< endl;
        cout << "| 14. Nhan xet cua ban                                       |"<< endl;
        cout << "| 15. Tim kiem cuon sach dat nhat                            |"<< endl;
        cout << "| 16. Tim kiem cuon sach de nhat                             |"<< endl;
        cout << "|------------------------------------------------------------|"<< endl;
        cout << "| 0. Thoat                                                   |"<< endl;
        cout << "|------------------------------------------------------------|"<< endl;
        cout << "| Lua chon cua ban:                                          |"<< endl;
        cout << "|_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ |"<< endl;
        
        // Nhập lựa chọn của người dùng
        cout << " ---> ";
        cin >> choice;

        // Xử lý lựa chọn
        Book b;
        int index1, index2, count, index;
        string title1;
        string filename;

        switch (choice) {
            case 1:
                cout << "\n> Nhap thong tin sach de them vao dau danh sach:\n";
                InputBook(b);
                InsertStart(H, b);
                cout << "\n[Sach da duoc them vao dau danh sach thanh cong!]\n";
                break;
            case 2:
                cout << "\n> Nhap thong tin sach de them vao cuoi danh sach:\n";
                InputBook(b);
                InsertEnd(H, b);
                cout << "\n[Sach da duoc them vao cuoi danh sach thanh cong!]\n";
                break;
            case 3:
                cout << "\n> Danh sach cac sach hien co:\n";
                ShowList(H);
                break;
            case 4:
                cout << "\n> Nhap hai vi tri sach can hoan doi (bat dau tu 0):\n";
                ShowList (H);
                cout << "Vi tri 1: "; cin >> index1;
                cout << "Vi tri 2: "; cin >> index2;
                SwapBook(H, index1, index2);
                cout << "\n[Da hoan doi vi tri cua hai cuon sach thanh cong!]\n";
                break;
            case 5:
                cout << "\n> Nhap vi tri de them sach (bat dau tu 0): ";
                cin >> index;
                cout << "\n> Nhap thong tin sach:\n";
                InputBook(b);
                AddBook(H, index, b);
                cout << "\n[Sach da duoc them vao vi tri " << index << " thanh cong!]\n";
                break;
            case 6:
                DeleteNodeEmpty(H, count);
                cout << "\n[Da xoa " << count << " sach rong khoi danh sach.]\n";
                break;
            case 7:
                AutoSort(H);
                cout << "\n[Sach đa duoc sap xep theo thu tu chu cai.]\n";
                break;
            case 8:
				ShowList (H);
                cout << "\n> Nhap tieu de sach can tim: ";
                cin.ignore();
                index = KMPSearch(title1, title1); // 
                if (index != -1) {
                    cout << "\n[Sach co tieu de '" << title1 << "' dã duoc tim thay!]\n";
                } else {
                    cout << "\n[Khong tim thay sach voi tieu de '" << title1 << "'.]\n";
                }
                break;
            case 9:
                Sumofbook(H);// gọi hàm tính tổng
                break;
            case 10:
            	
            	ShowList (H);
                cout << "\n> Nhap tieu de sach can xoa: ";
                cin.ignore();
                getline(cin, title1);
                
                Deletebook(H, title1);
                cout << "\n[Da xoa cuon sach co tieu de '" << title1 << "' thanh cong (neu co).]\n";
                break;
            case 11:
            
                cout << "\n> Nhap ten file (vi du: books.txt): ";
                cin.ignore();
                getline(cin, filename);
                
                ReadFromFile(H, filename);
                break;
            case 12:
                
                cout << "\n> Nhap ten file de ghi du lieu (vi du: books.txt): ";
                cin.ignore();
                getline(cin, filename);
    			
                WriteToFile(filename, H);
                break;  
    		case 13:
    		    buybook(H);
    		    break;
    		case 14:
    		    feedback();
    		    break;
    		case 15:
    			Searchmax(H);
    			break;
    		case 16:
    			Searchmin(H);
    			break;
            case 0:
                cout << "\n[Thoat chuong trinh...]\n";
                break;
            default:
                cout << "\n[Lua chon khong hop le! Vui long chon lai.]\n";
        }
        if (choice != 0) {
            cout << "\nNhan Enter de tiep tuc...";
            cin.ignore();
            cin.get();
        }

    } while (choice != 0);
}


int main() {
	
	// khai báo danh sách
    LinkedList H;
    
    //khởi tạo danh sách
    InitList(H);
    
    //hàm menu
    Menu(H);
    return 0;
    
}
