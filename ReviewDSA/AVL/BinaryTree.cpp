#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <stack>
#include <queue>
using namespace std;
class Node
{
    int val;
    Node *pLeft;
    Node *pRight;
    Node()
    {
        this->pLeft = this->pRight = nullptr;
    }
    Node(data)
    {
        this->val = data;
        this->pLeft = nullptr;
        this->pRight = nullptr;
    }
};
int Height(Node *root)
{
    if (root == nullptr)
    {
        return 0;
    }
    else
    {
        int hleft = Height(root->pLeft);
        int hright = Height(root->pRight);
        return 1 + max(hleft, hright);
    }
}
/**
 *      4
 *    /    \
 *   4
 */
// ========================= CĐ1: BINARY TREE ==========================//
// ! EX1: GET DIAMETER() in Binary Tree():
int getdiameter()
{
    if (this->root == nullptr)
    {
        return 0;
    }
    else
    {
        return 1 + max(Height(this->root->pLeft), Height(this->root->pRight));
    }
}
// ! EX2: TRAVESAL BFS in Binary Tree():
// + Sử dụng queue để chứa các node được duyệt qua:
void BFS(Node *root)
{
    if (root == nullptr)
    {
        return;
    }
    else
    {
        queue<Node *> bfs;
        bfs.push(this->root);
        while (!bfs.empty())
        {
            // Tạo 1  con trỏ để get data node được duyệt qua -> pop ra ngoài: --> PUSH: LEFT -> RIGHT
            Node *curr = bfs.front();
            bfs.pop();
            cout << curr->val << " ";
            if (curr->pLeft != nullptr)
            {
                bfs.push(curr->pLeft);
            }
            if (curr->pRight != nullptr)
            {
                bfs.push(curr->pRight);
            }
        }
    }
}
// ! EX3: DFS: PreInOrder - InOrder - PostOrder
// * Travesal: PreInOrder():
void PreInOrder(Node *pNode)
{
    if (pNode == nullptr)
    {
        return;
    }
    cout << pNode->val << " ";
    PreInOrder(pNode->pLeft);
    PreInOrder(pNode->pRight);
}
// * Travesal InOrder:
void InOrder(Node *pNode)
{
    if (pNode == nullptr)
    {
        return;
    }
    InOrder(pNode->pLeft);
    cout << pNode->val << " ";
    InOrder(pNode->pRight);
}
string PrintInOrder()
{
    PreInOrder(root);
    return "";
}

// ! EX4: TÍNH TỔNG SỐ P-Node() in Binary Tree()
// * Tính tổng giá trị các Node trên cây nhị phân:
int SumOfTree(Node *root)
{
    if (root == nullptr)
    {
        return 0;
    }
    else
    {
        return root->val + SumOfTree(root->pLeft) + SumOfTree(root->pRight);
    }
}
int distinctParities(Node *root)
{
    if (root == nullptr)
    {
        return 0;
    }
    int count = 0;
    if (root->pLeft && root->pRight)
    {
        if ((SumOfTree(root->pLeft) + SumOfTree(root->pRight)) % 2 == 1)
        {
            count++;
        }
    }
    count += distinctParities(root->pLeft);
    count += distinctParities(root->pRight);
    return count;
}

// ! EX5:

// =============================== CĐ2: BINARY SEARCH TREE() ====================//
// ? CẢ ADD VÀ DELETE ĐỀU PHẢI TRẢ VỀ ROOT SAU KHI THỰC HIỆN (TRÊN HÀM HELP)

// !EX1: Thêm 1 Node vào cây BST():
// Tìm node nhỏ nhất cây BST:
Node *SPMinNode(Node *pnode)
{
    Node *curr = pnode;
    while (curr && curr->pLeft != nullptr)
    {
        curr = curr->pLeft;
    }
    return curr;
}
// Help function add Node(): có giá trị data
Node *addNode(Node *root, int data)
{
    // ! TH CÂY BST KHÔNG CÓ GÌ -> NODE THÊM = ROOT
    if (root == nullptr)
    {
        root = new Node(data);
        return root;
    }
    if (data > root->val)
    {
        root->pRight = addNode(root->pRight, data);
    }
    else
    {
        root->pLeft = addNode(root->pLeft, data);
    }
    return root;
}

void add(int data)
{
    root = addNode(root, data);
}
// !EX2: XÓA 1 NODE CÓ GIÁ TRỊ VALUE KHỎI CÂY BST:
// help function:
// Có 4 TH: data cần xóa: [LỚN HƠN ROOT] - [BÉ HƠN ROOT] - [TÌM ĐƯỢC - 1 CON] - [TÌM ĐƯỢC - 2 CON]
Node deleteSP(Node *root, int data)
{
    if (root == nullptr)
    {
        return root;
    }
    if (root->val > data)
    {
        root->pLeft = deleteSP(root->pLeft, data);
    }
    else if (root->val < data)
    {
        root->pRight = deleteSP(root->pRight, data);
    }
    else
    { //! TÌM ĐƯỢC Node có val = data
        if (root->pLeft == nullptr)
        { // node tìm được chỉ có con phải
            Node *ptem = root->pRight;
            delete root;
            return ptem;
        }
        else if (root->pRight == nullptr)
        {
            Node *ptem = root->pLeft;
            delete root;
            return ptem;
        }
        else
        { //! TH: NODE TÌM ĐƯỢC CÓ 2 CON: Chọn Node LN THUỘC LeftTree || Node BÉ NHẤT THUỘC RIGHT TREE để thay vào Node cần xóa.
            Node *ptem = SPMinNode(root->pRight);
            root->val = ptem->val;
            // ĐI XÓA NODE THẾ MẠNG vào root THUỘC pRight
            root->pRight = deleteSP(root->pRight, ptem->val);
        }
    }
    return root;
}
void deleteNode(int data)
{
    root = deleteSP(root, data);
}

// !EX3: ---------

// =========================== CĐ3: CÂY AVL ========================//
//! EX1: hiện thực cây AVL:
/**
 * Class AVL{
 *  int data
 *  Node *pLeft;
 *  Node *pRight;
 *  BalanceValue: [RH/EH/LH];
 * }
 */
// * Functionn RotateNode sang phải (LỆCH TRÁI)
Node *rotateRight(Node *root){
    Node *ptem = root->pLeft;
    root->pLeft = ptem->pRight;
    ptem->pRight = root;
    return ptem;
}
Node *rotateLeft(Node *root){
    Node *ptem = root->pRight;
    root->pRight = ptem->pLeft;
    ptem->pLeft = root;
    return ptem;
}
// !SpFunction: Hàm: deleteRightBalance(root, shorter) --> cân bằng khi cây LỆCH PHẢI - sau khi xóa TRÁI --> XOAY TRÁI (NẾU CẦN);

Node *deleteRightBalance(Node *root, bool &shorter) //! CẦN BẰNG CÂY SAU KHI CÂY--> REMOVE LEFT
{
    if (root->balance == BalanceValue::LH)
    {
        root->balance = BalanceValue::EH;
    }
    else if (root->balance == BalanceValue::EH)
    {
        root->balance = BalanceValue::RH;
        shorter = false; //! phát hiện chiều cao cây bị lệch > |1|
    }
    else
    { //? TH cây chưa xóa nhưng đã lệch PHẢI (RH): root->RH --> xóa trái thì mất CB
        Node *Rtree = root->pRight;
        if (Rtree->balance == LH) //!LEFT OR RIGHT
        {
            Node *Ltree = Rtree->pLeft;
            if (Ltree->balance == LH)
            {
                Rtree->balance = RH;
                root->balance = EH;
            }else if(Ltree->balance == EH){
                Rtree->balance = EH;
                root->balance = LH;
            }else{ //Ltree == RH
                root->balance = LH;
                Rtree->balance = EH;
            }
            Ltree->balance = EH;
            root->pRight = rotateRight(Rtree);
        } else { //!Rtree = RH || EH -> RIGHT OF RIGHT
            // ! ?????
            if (Rtree->balance!=EH) { //RH
                root->balance=EH;
                Rtree->balance=EH;
            }
            else { //Rtree = EH
                root->balance=RH;
                Rtree->balance=LH;
                shorter=false;
            }
            root=rotateLeft(root);
        }
    }
    return root;
}

Node *deleteLeftBalance(Node *root, bool &shorter){ //!--xóa PHẢI làm AVL lệch trái->CB
    if(root->balance == RH){
        root->balance = EH;
    }else if(root->balance == EH){
        root->balance = LH;
        shorter = false;
    }else{ //* TH CÂY ĐANG LỆCH TRÁI:----/// LH   ///--> XÓA PHẢI - MẤT CB
        Node *Ltree = root->pLeft;
        if(Ltree->balance == RH){ //!RIGHT OF LEFT
            Node *Rtree = Ltree->pRight;
            if(Rtree->balance == LH){ 
                Ltree->balance = EH;
                root->balance = RH;
            }else if(Rtree->balance == EH){
                Ltree->balance = EH;
                root->balance = RH;
            }else{ //! Rtree = RH
                Ltree->balance = LH;
                root->balance = EH;
            }
            Rtree->balance = EH;
            root->pLeft = rotateLeft(Ltree);
        }else{ //! LEFT OF LEFT 
            if(Ltree->balance != EH){ //LH
                root->balance = EH;
                Ltree->balance = EH;
            }else{
                root->balance = LH;
                Ltree->balance = RH;
                shorter = false;
            }
        }
    }
}

//! --------------EX2: REMOVE NODE TRÊN CÂY AVL :
Node AVLDelete(Node *root, int keyDel, bool &shorter, bool &succes){
    if (root == NULL){
        shorter = false;
        succes = false;
        return NULL;
    }
    if(keyDel < root->val){
        root->pLeft = AVLDelete(root->pLeft, keyDel, shorter, succes);
        if(shorter){
            root = deleteRightBalance(root, shorter);
        }
    }else if(keyDel > root->val){
        root->pRight = AVLDelete(root->pRight, keyDel, shorter, succes);
        if(shorter){
            root = deleteLeftBalance(root, shorter);
        }
    }else{ // keydel === root truyền vào
        Node *pdel = root;
        // * TH Node xóa chỉ có 1 Node con
        if(root->pLeft == NULL){
            Node *newNode = root->pRight;
            succes = true;
            shorter = true;
            delete (pdel);
            return newNode;
        }else if(root->pRight == NULL){
            Node *newNode = root->pLeft;
            succes = true;
            shorter = true;
            delete (pdel);
            return newNode;
        }else{ //! TH Node xóa có 2 Node con -> tìm Node LN CỦA CON TRÁI -. THAY THẾ VÀO ROOT
            Node *ptem = root->pLeft;
            while(ptem && ptem->pRight!= NULL){
                ptem = ptem->pRight;
            }
            root->data = ptem->data;
            root->pLeft = AVLDelete(root->pLeft, ptem->data, shorter, succes);
            if(shorter){
                root = deleteRightBalance(root, shorter);
            }
        }
    }
    return root;
}
void remove(const int &value){
    bool shorter, success;
    root = AVLDelete(root, value, shorter, success);
}

//! ---------EX3: INSERT NODE VÀO CÂY AVL:----------------
int getHeightRec(Node *node)
    {
        if (node == NULL)
            return 0;
        int lh = this->getHeightRec(node->pLeft);
        int rh = this->getHeightRec(node->pRight);
        return (lh > rh ? lh : rh) + 1;
    }
// * SỬ DỤNG LẠI HÀM ROTATE Ở PHẦN REMOVE:
Node *insertNode(Node *root, int value){
    if(root == NULL){
        return new Node(value);
    }
    if(root->val > value){
        root->pLeft = insertNode(root->pLeft, value);
    }else{
        root->pRight = insertNode(root->pRight, value);
    }
    // ! CÂN BẰNG LẠI CÂY AVL SAU KHI THÊM NODE
    int balance = getHeightRec(root->pLeft) - getHeightRec(root->pRight);
    if(balance > 1){ //!---> LỆCH TRÁI(đã chèn val vào pleft)
        if(value > root->pLeft->val){ // TH: RIGHT OF LEFT
            root->pLeft = rotateLeft(root->pLeft);
        }
        return rotateRight(root); // TH: LEFT OF LEFT
    }else if(balance < -1){ //!LỆCH PHẢI - (ĐÃ CHÈN VALUE VÀO BÊN PHẢI)
        if(value < root->pRight->val){
            root->pRight = rotateRight(root->pRight);
        }
        return rotateLeft(root);
    }
    return root;
}
void insert(const int &value){
    this->root = insert(this->root, value);
}

//!---------- EX4: PrintInOrder - SearchValue() -------------//
// * Hàm support cho hàm In theo TRUNG TỰ
void InOrder(Node *root){
    if(root == NULL){
        return;
    }
    InOrder(root->pLeft);
    cout << root->val << " ";
    InOrder(root->pRight);
}
void PrintInOrder(){
    InOrder(root);
}

// * TÌM KIẾM NODE CHỨA GIÁ TRỊ VALUE ---------//
// !----------HÀM HỖ TRỢ TÌM KIẾM NODE
bool search(Node *r, int data){
    if(r == NULL){
        return false;
    }
    if(r->val > data){
        return search(r->pLeft, data);
    }else if(r->val < data){
        return search(r->pRight, data);
    }else{
        return true;
    }
}
int main()
{
    
}