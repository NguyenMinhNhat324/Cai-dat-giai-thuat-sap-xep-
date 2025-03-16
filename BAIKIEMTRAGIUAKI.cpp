#include <iostream>
#include <cstring>
using namespace std;

struct hocsinh {
    char id[10];
    char ten[50];
    int sinhnam;
    float trungbinhdiem;

    hocsinh(const char* id, const char* ten, int sinhnam, float trungbinhdiem) {
        strcpy(this->id, id);
        strcpy(this->ten, ten);
        this->sinhnam = sinhnam;
        this->trungbinhdiem = trungbinhdiem;
    }
};

struct Node {
    hocsinh data;
    Node* trai;
    Node* phai;

    Node(hocsinh data) : data(data), trai(NULL), phai(NULL) {}
};

class timkiemnhiphan {
private:
    Node* root;

    Node* insert(Node* node, hocsinh hs) {
        if (node == NULL) {
            return new Node(hs);
        }
        if (strcmp(hs.id, node->data.id) < 0) {
            node->trai = insert(node->trai, hs);
        } else {
            node->phai = insert(node->phai, hs);
        }
        return node;
    }

    void Duyettheothutu(Node* node) {
        if (node) {
            Duyettheothutu(node->trai);
            cout << node->data.id << " - " << node->data.ten << " - "
                 << node->data.sinhnam << " - " << node->data.trungbinhdiem << endl;
            Duyettheothutu(node->phai);
        }
    }

    int Demsonode(Node* node) {
        if (node == NULL) return 0;
        if (node->trai == NULL && node->phai == NULL) return 1;
        return Demsonode(node->trai) + Demsonode(node->phai);
    }

    Node* Timidhocsinh(Node* node, const char* id) {
        if (node == NULL || strcmp(node->data.id, id) == 0) return node;
        if (strcmp(id, node->data.id) < 0) return Timidhocsinh(node->trai, id);
        return Timidhocsinh(node->phai, id);
    }

public:
    timkiemnhiphan() : root(NULL) {}

    void insert(hocsinh hs) {
        root = insert(root, hs);
    }

    void Duyettheothutu() {
        Duyettheothutu(root);
    }

    int Demsonode() {
        return Demsonode(root);
    }

    hocsinh* Timidhocsinh(const char* id) {
        Node* result = Timidhocsinh(root, id);
        return result ? &result->data : NULL;
    }
};

int main() {
    timkiemnhiphan tree;

    tree.insert(hocsinh("001", "Nguyenvankhanh", 2000, 8.5));
    tree.insert(hocsinh("002", "Tranthiha", 1999, 7.2));
    tree.insert(hocsinh("003", "Levandung", 2001, 9.0));
    tree.insert(hocsinh("004", "Phamthihue", 2002, 8.8));
    tree.insert(hocsinh("005", "Hoangvanphan", 2003, 7.5));

    cout << "nhap duyet cay theo thu tu giua (LNR):" << endl;
    tree.Duyettheothutu();

    cout << "So luong node cua sinh vien la: " << tree.Demsonode() << endl;

    char id[10];
    cout << "Nhap ma sinh vien can tim: ";
    cin >> id;
    hocsinh* result = tree.Timidhocsinh(id);
    if (result) {
        cout << "Thong tin sinh vien da duoc tim thay: "
             << result->id << " - " << result->ten << " - "
             << result->sinhnam << " - " << result->trungbinhdiem << endl;
    } else {
        cout << "Khong tim thay hoc sinh." << endl;
    }

    return 0;
}
