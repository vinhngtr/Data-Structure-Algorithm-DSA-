#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
#include <bits/stdc++.h>
#include <sstream>


class Deque {
private:
    class Node {
    private:
        int value;
        Node* left;
        Node* right;
        friend class Deque;
    public:
        Node(int val = 0, Node* l = nullptr, Node* r = nullptr) : value(val), left(l), right(r) { }
    };

private:
    Node* head;
    Node* tail;
    int curSize;

public:
    Deque();
    ~Deque();
    int getSize();
    void pushFront(int item);
    void pushBack(int item);
    int popFront();
    int popBack();
    void clear();
    void printDequeReverse();
    void printDeque();
};
using namespace std;
// EX1: KHỞI TẠO 1 DEQUEUE DỰA TRÊN STACK QUEUE:
Deque::Deque(){
    head = NULL;
    tail = NULL;
    curSize = 0;
}
Deque::~Deque(){
    clear();
}
void Deque::clear() {
    while(head!=NULL){
        Node *pdel = head;
        head = head->right;
        delete pdel;
    }
    head = tail = NULL;
    curSize = 0;
}

int Deque::getSize() {
    return this->curSize;
}

void Deque::pushFront(int i) { // THÊM TRÁI
    Node *pnew = new Node(i, nullptr, head);
    if (head != NULL)
    {
        head->left = pnew;
    }
    head = pnew;
    if(tail == NULL){
        tail = head;
    }
    curSize++;
}

void Deque::pushBack(int i) { // THÊM PHẢI
    Node *pnew = new Node(i, tail, NULL);
    if(tail != NULL){
        tail->right = pnew;
    }
    tail = pnew;
    if(head == nullptr){
        head = tail;
    }
    curSize++;
}

int Deque::popFront() { //remove và trả về giá trị ở bên TRÁI CÙNG
    if(head == NULL){
        return -1;
    }
    int val = head->value;
    head = head->right;
    curSize--;
    if(curSize == 0){
        tail = nullptr;
    }else{
        head->left = nullptr;
    }
    return val;
}

int Deque::popBack() {
    // !Note: sau khi chuyển tail:
    /**
     * xét size = 0 -> head = null
     * size != 0 -> tai-> right = null
    */
    int val = tail->value;
    tail = tail->left;
    curSize--;
    if(curSize == 0){
        head = nullptr;
    }else{
        tail->right = nullptr;
    }
    return val;
}

void Deque::printQueueReverse() {
    Node *cur = tail;
    while(cur != NULL){
        cout << cur->value << " ";
        cur = cur->left;
    }
    cout << end;
}

void Deque::printQueue() {  //DUYỆT TỪ LEFT -> RIGHT CỦA  DEQUEUE
    // !Note: xuống dòng sau khi duyệt xog.
    Node *cur = head;
    while(cur != NULL){
        cout << cur->value << " ";
        cur = cur->right;
    }
    cout << end;
}

// EX2: Implement methods [ADD - SIZE] in template class DLinkedList
void DLinkedList<T>::add(const T& e) {  //! thêm vào cuối DoubleLL
    Node *p = new Node(e);
    if(this->head == NULL){
        this->head = this->tail = p;
    }else{
        this->tail->next = p;
        p->prev = this->tail;
        this->tail = p;
    }
    this->count++;
}

void DLinkedList<T>::add(int index, const T& e) {
    if(index == 0){
        Node *p = new Node(e);
        p->next = head;
        this->count++;
        if(count == 0){
            this->head = this->tail = p;
        }else{
            head->pre = p;
        }
        head = p;
    
    }else if(index >= this->count){
        add(e);
        return;
    }else{
        Node *ptem = this->head;
        int i = 0;
        while(i<index-1){
            ptem = ptem->next;
            i++;
        }
        Node *padd = new Node(e);
        padd->next = ptem->next;
        padd->pre = ptem;
        ptem->next = padd;
        padd->next->pre = padd;
        this->count++;
    }
}

T DLinkedList<T>::removeAt(int index){
    if(index < 0 || index >=this->count){
        return -1;
    }
    if (this->count == 0 || this->head == NULL){
        return -1;
    }
    int res;
    Node *pdel = this->head;
    if(this->count == 1){
        res = this->head->data;
        delete this->head;
        head = tail = nullptr;
    }else if(index == 0){
        res = this->head->data;
        head = head->next;
        delete pdel;
        head->pre = NULL;
    }else if(index  == this->count -1){
        Node *ptem = this->head;
        while(ptem->next != this->tail){
            ptem = ptem->next;
        }
        pdel = ptem->next;
        res = ptem->next->data;
        this->tail = ptem;
        delete pdel;
        this->tail->next = NULL;
    }else{
        int i = 0;
        while(i<index){
            pdel = pdel->next;
        }
        res = pdel->data;
        pdel->pre->next = pdel->next;
        pdel->next->pre = pdel->pre;
        delete pdel;
        pdel = NULL
    }
}

void DataLog::undo() //!-----> chuyen state ve truoc 1 buoc 
{
    /*
     * TODO: Switch to the previous state of the data
     *       If this is the oldest state in the log, nothing changes
     */
     if (currentState == logList.begin()) return;
     currentState--;
}

void DataLog::redo()
{
    /*
     * TODO: Switch to the latter state of the data
     *       If this is the latest state in the log, nothing changes
     */
     if (next(currentState, 1) == logList.end()) return;
     currentState++;
}
DataLog::DataLog(const int &data)
{
    /*
     * TODO:  add the first state with data
     */
    logList.push_back(data);
    currentState = logList.begin();
}

void DataLog::save()
{
    // ! xoa trang thai cux: logList.erase(next(currState,1), logList.end())
    // ! logList.push_back(*currState);
    // ! curState++;
    /*
     * TODO: This function will create a new state, copy the data of the currentState
     *       and move the currentState Iterator to this new state. If there are other states behind the
     *       currentState Iterator, we delete them all before creating a new state.
     */
    logList.erase(next(currentState,1), logList.end());
    logList.push_back(*currentState);
    currentState++;
}
class Node{
    string str;
    Node *pre;
    Node *next;
    Node(string data){
        str = data;
        pre = NULL;
        next = NULL;
    }
};
class LineStreet{
    public:
    Node *curr;
    LineStreet(string homepage) {
       curr = new Node(homepage);
    }
    void addNewItem(string url){
       Node *p = new Node(url);
       p->pre = curr;
       curr->next = p;
       curr = p;
    }
    string back(int step){
        while(step-- && curr->pre){
            curr = curr->pre;
        }
        return curr->str;
    }                                
    string forward(int step){
        while(step-- && curr->next){
            curr = curr->next;
        }
        return curr->str;
    }
};
int main(){

}