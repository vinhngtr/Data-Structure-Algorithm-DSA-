#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
#include <bits/stdc++.h>
#include <sstream>

using namespace std;

// EX1:
/**
 * LLNode* addLinkedList(LLNode* l0, LLNode* l1);
Where l0, l1 are two linked lists represented positive integers, each node is a digit, the head is the least significant digit (the value of each node is between 0 and 9, the length of each linked list is between 0 and 100000). This function returns the linked list representing the sum of the two integers.

Example:
Given l0 = [2, 3] (representing 32) and l1 = [1, 8] (representing 81). The result would be l0 = [3, 1, 1] (representing 32 + 81 = 113).
*/
class LLNode
{
public:
    int val;
    LLNode *next;
    LLNode();
    LLNode(int val, LLNode *next);
};

int ConvertInt(LLNode *head)
{
    string num = "";
    while (head != NULL)
    {
        num += to_string(head->val);
        head = head->next;
    }
    reserve(num.begin(), num.end());
    return stoi(num);
}
LLNode *ConvertLL(int num)
{
    string numStr = to_string(num); //! đảo ngược number truyền vào
    reverse(numStr.begin(), numStr.end());
    if (numStr.length() == 0)
        return NULL;
    LLNode *head = new LLNode(numStr[0] - '0', NULL);
    LLNode *temp = head;
    for (int i = 1; i < numStr.length(); i++)
    {
        temp->next = new LLNode(numStr[i] - '0', NULL);
        temp = temp->next;
    }
    return head;
}
LLNode *addLinkedList(LLNode *l0, LLNode *l1)
{
    int val1 = ConvertInt(l0);
    int val2 = ConvertInt(l1);
    int sumOf = val1 + val2;
    return ConvertLL(sumOf);
}

// EX2:void LinkedList::partition(int k)
void LinkedList::partition(int k)
{
    Node *ptem = this->head;
    LinkedList *Small = new LinkedList();
    LinkedList *Equal = new LinkedList();
    LinkedList *Large = new LinkedList();
    while (ptem != NULL)
    {
        if (ptem->val < k)
        {
            Small->add(ptem->val);
        }
        else if (ptem->val == k)
        {
            Equal->add(ptem->val);
        }
        else
        {
            Large->add(ptem->val);
        }
        ptem = ptem->next;
    }
    LinkedList *result = new LinkedList();
    ptem = Small->head;
    while (ptem != NULL)
    {
        result->add(ptem->val);
        ptem = ptem->next;
    }
    ptem = Equal->head;
    while (ptem != NULL)
    {
        result->add(ptem->val);
        ptem = ptem->next;
    }
    ptem = Large->head;
    while (ptem != NULL)
    {
        result->add(ptem->val);
        ptem = ptem->next;
    }
    ptem = head;
    Node *curr = result->head;
    while (ptem != NULL)
    {
        ptem->val = curr->val;
        ptem = ptem->next;
        curr = curr->next;
    }
    ptem = NULL;
    curr = NULL;
}

// EX4: Cho node root của một danh sách liên kết đơn, hiện thực hàm sau đây:
/**
 * void reduceDuplicate(Node* root);
để giảm các phần tử trùng lặp liên tiếp trong danh sách. Nếu có các phần tử liên tiếp giống nhau, ta chỉ giữ lại 1 phần tử.
Ví dụ, ta có 1 danh sách 122234452, sau khi thực hiện hàm reduceDuplicate ta thu được danh sách 123452. (số 2 cuối cùng giữ nguyên do nó không liên tiếp với dãy 222 phía trước)
*/
void reduceDuplicate(Node *root)
{
    Node *curNode = new Node(0, NULL);
    curNode = root;
    Node *nextNode = new Node(0, NULL);
    if (curNode == NULL)
    {
        return;
    }
    while (curNode->getNext() != NULL)
    {
        if (curNode->getData() == (curNode->getNext())->getData())
        {
            nextNode = (curNode->getNext())->gextNext();
            free(curNode->getNext());
            curNode->setNext(nexNode);
        }
        else
        {
            curNode = curNode->getNext();
        }
    }
}

template <class T>
class SLinkedList
{
public:
    class Node; // Forward declaration
protected:
    Node *head;
    Node *tail;
    int count;

public:
    SLinkedList() : head(NULL), tail(NULL), count(0){};
    ~SLinkedList(){};
    void add(const T &e);
    void add(int index, const T &e);
    int size();
    string toString()
    {
        stringstream ss;
        ss << "[";
        Node *ptr = head;
        while (ptr != tail)
        {
            ss << ptr->data << ",";
            ptr = ptr->next;
        }

        if (count > 0)
            ss << ptr->data << "]";
        else
            ss << "]";
        return ss.str();
    }

public:
    class Node
    {
    private:
        T data;
        Node *next;
        friend class SLinkedList<T>;

    public:
        Node()
        {
            next = 0;
        }
        Node(Node *next)
        {
            this->next = next;
        }
        Node(T data, Node *next = NULL)
        {
            this->data = data;
            this->next = next;
        }
    };
};
// EX5: Method: ADD() - SIZE() of Single LinkList
void SLinkedList<T>::add(const T &e)
{
    // thêm phần tử vào cuối SLL
    Node *newNode = new Node(e);
    if (this->count == 0)
    {
        this->head = this->tail = newNode;
        /**
         * newNode->next = head;
         * this->head = newNode;
         * this->tail = newNode;
         */
    }
    else
    {
        this->tail->next = newNode;
        this->tail = newNode;
    }
    this->count++;
}

void SLinkedList<T>::add(const T &e, int index)
{
    if (this->count == 0 || this->head == NULL)
    {
        Node *p = new Node(e, 0);
        p->next = head;
        this->head = p;
        this->tail = p;
        this->count++;
    }
    else if (index == 0)
    {
        Node *p = new Node(e, 0);
        p->next = head;
        this->head = p;
        this->count++;
    }
    else if (index >= this->count)
    {
        return this->add(e);
    }
    else
    { //! TH CHÈN GIỮA: --> TÌM ĐÊN NODE KỀ NODE CẦN CHÈN <-> while(i<index -1)
        int i = 0;
        Node *ptem = this->head;
        while (i < index - 1)
        {
            ptem = ptem->next;
            i++;
        }
        Node *pnew = new Node(e, 0);
        pnew->next = ptem->next;
        ptem->next = pnew;
        this->count++;
    }
}

int SLList::size()
{
    Node *ptem = this->head;
    int i = 0;
    while (ptem != NULL)
    {
        ptem = ptem->next;
        i++;
    }
    return i;
    // return this->count;
}

T SLinkedList<T>::get(int index)
{
    Node *pnew = this->head;
    if (index >= this->count || index < 0)
    {
        return -1
    }
    int i = 0;
    while (i < index)
    {
        pnew = pnew->next;
        i++;
    }
    return pnew->data;
}

void SLinkedList<T>::set(int index, const T &e)
{
    Node *p1 = this->head;
    int i = 0;
    if (index < 0 || index >= this->count)
    {
        return;
    }
    while (i < index)
    {
        p1 = p1->next;
        i++;
    }
    p1->data = e;
}

bool empty()
{
    return !this->count;
}

int SLinkedList<T>::indexOf(const T &item)
{
    // ! Trả về chỉ số của item đầu tiên có mặt trong list - nếu ko tồn tại -> return -1;
    Node p = this->head;
    int i = 0;
    while (p != NULL)
    {
        if (p->val == item)
        {
            return i;
        }
        else
        {
            p = p->next;
            i++;
        }
    }
    return -1;
}

bool SLinkedList<T>::contains(const T &item)
{
    // if(this->indexOf(item) == -1){
    //     return false;
    // }else{
    //     return true;
    // }
    Node *p = this->head;
    while (p != NULL)
    {
        if (p->data == item)
        {
            return true;
        }
        else
        {
            p = p->next;
        }
    }
    return false;
}

// !----------- REMOVE AT(INDEX) AND: REMOVE ITEM(item)-----------------//
T SLinkedList<T>::removeAt(int index)
{
    int valDel = 0;
    if (this->head == NULL)
    {
        return -1;
    }
    else if (index < 0 || index >= this->count)
    {
        return -1;
    }
    else if (index == 0)
    {
        Node *pdel = this->head;
        head = head->next;
        valDel = pdel->data;
        delete pdel;
        count--;
    }
    else if (index == this->count - 1)
    {
        Node *pdel = this->head;
        for (Node *p = this->head; p != NULL; p = p->next)
        {
            if (p->next == this->tail)
            {
                pdel = p->next;
                valDel = p->next->data;
                tail = p;
                p->next = NULL;
                delete pdel;
                count--;
            }
        }
    }
    else
    {
        Node *p1 = this->head;
        int i = 0;
        // ! DUYỆT ĐẾN NODE KỀ NODE CẦN XÓA LÀ OKE (PDEL -1)
        while (i < index - 1)
        {
            p1 = p1->next;
            i++;
        }
        Node *pdel = p1->next;
        valDel = p1->next->data;
        p1->next = p1->next->next;
        delete pdel;
        // pdel->next = NULL;
        count--;
    }
    return valDel;
}

bool SLinkedList<T>::removeItem(const T &item)
{
    Node *p1 = this->head;
    int i = 0;
    while (p1 != NULL)
    {
        if (p1->data == item)
        {
            removeAt(i);
            return true;
        }
        else
        {
            p1 = p1->next;
            i++;
        }
    }
    return false;
}

void SLinkedList<T>::clear()
{ //! dùng điều kiện size != 0 --> removeAt(0)
    while (size() != 0)
    {
        removeAt(0);
    }
}

// EX6: LLNode* foldLinkedList(LLNode* head) --> //! gập list tại vị trí midd/2
/**
 * int arr[] = {9, 5, 7, 5, 0};
LLNode* head = LLNode::createWithIterators(arr, arr + sizeof(arr) / sizeof(int));
LLNode::printList(head);
cout << "\n";
LLNode* newhead = foldLinkedList(head);
LLNode::printList(newhead);
EXAMPLE:
[9, 5, 7, 5, 0]
[7, 10, 9]
*/
int sizeList(LLNode *head)
{
    int count = 0;
    while (head != NULL)
    {
        head = head->next;
        count++;
    }
    return count;
}
LLNode *foldLinkedList(LLNode *head)
{
    // 1. Tính chiều dài của List - và tạo arr[count]
    // gán các val của list ban đầu vào arr[count]
    // 2. 2TH: node lẻ và chẵn duyệt theo arr để gán val vào list -> return head
    int count = sizeList(head);
    LLNode *ptem = head;
    LLNode *newList = head;
    int arr[count];
    if (count == 0)
    {
        return NULL;
    }
    for (int i = 0; i < count; i++)
    {
        arr[i] = ptem->val;
        ptem = ptem->next;
    }
    if (count % 2 != 0)
    {
        newList->val = arr[(count - 1) / 2];
        for (int i = ((count - 1) / 2) - 1; i >= 0; i--)
        {
            newList->val = arr[i] + arr[count - i - 1];
            if (i == 0)
            {
                newList->next = NULL;
                return head;
            }
            newList = newList->next;
        }
    }
    else
    {
        for (int i = (count / 2) - 1; i >= 0; i--)
        {
            newList->val = arr[i] + arr[count - i - 1];
            if (i == 0)
            {
                newList->next = NULL;
                return head;
            }
            newList = newList->next;
        }
    }
}

// EX7: LLNode* replaceFirstGreater(LLNode* head) --> //! trả về 1 list sau khi thay thế all value của Node bằng giá trị Node BÊN PHẢI GẦN NHẤT LỚN HƠN NÓ (nếu ko tồn tại gán lại 0)
/**
 * EXAMPLE:
 * int arr[] = {0, 3, 2, 1, 5};
 * 1. arr lấy được từ stack = [0 - 5 - 5 - 5 - 3];
 * ! --> [3 - 5 - 5 - 5 - 0]
 */
LLNode *replaceFirstGreater(LLNode *head)
{
    int count = sizeList(head);
    int arr[count];
    LLNode *p = head;
    stack<int> ntv;
    for (LLNode *p1 = head; p1 != NULL; p1 = p1->next)
    {
        int max = 0;
        for (LLNode *p2 = p1->next; p2 != NULL; p2 = p2->next)
        {
            if (p2->val > p1->val)
            {
                max = p2->val;
                break; //! IMPORTANT
            }
        }
        ntv.push(max);
    }
    for (int i = 0; i < count; i++)
    {
        arr[i] = ntv.top();
        ntv.pop();
    }
    for (int i = count - 1; i >= 0; i--)
    {
        p->val = arr[i];
        p = p->next;
    }
    return head;
}

// EX8: LLNode* reverseLinkedList(LLNode* head) --> //! ĐẢO NGƯỢC DSLK
// TƯ TƯỞNG:
/**
 * 1. Tạo ra 3 node để xử lí đảo: curr(head) - next(NULL) - prev(NULL)
 * 2. Thao tác quay node:
 *      + next = cur->next
 *      + cur->next = pre
 *      + pre = cur
 *      + cur = next
 */
LLNode *reverseLinkedList(LLNode *head)
{
    LLNode *cur = head;
    LLNode *pre = NULL;
    LLNode *next = NULL;
    while (cur != NULL)
    {
        next = cur->next;
        cur->next = pre;
        pre = cur;
        cur = next;
    }
    head = pre;
    return head;
}

// EX9: LLNode* rotateLinkedList(LLNode* head, int k) --> //! TRẢ VỀ LIST MỚI SAU KHI DỊCH LL SANG PHẢI (k) VỊ TRÍ
LLNode *rotateLinkedList(LLNode *head, int k)
{
    if (head == NULL || k = 0)
    {
        return head;
    }
    // ! TẠO VÒNG FOR CHẠY TỪ 0 ĐẾN K-1 ĐỂ ĐƯA K PHẦN TỬ CUỐI CÙNG CỦA LIST --> LÊN ĐẦU LIST
    for (int i = 0; i < k; i++)
    {
        LLNode *curr = head;
        while (curr->next->next != NULL){
            curr = curr->next;
        }
        LLNode *end = curr->next;
        curr->next = NULL;
        end->next = head;
        head = end;
    }
    return head;
}

int main()
{
}