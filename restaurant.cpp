#include "main.h"

/* Khởi tạo thông tin cho 1 bàn được đặt*/
class Table
{
public:
	int ID, result;
	string name;
	Table(int ID = 0, string name = "", int result = 0)
	{
		this->ID = ID;
		this->result = result;
		this->name = name;
	}
	~Table()
	{
		ID = 0;
		result = 0;
		name = "";
	}

	bool comparation(const int &ID, const int &result)
	{
		return (this->ID == ID) && (this->result == result);
	}

	bool comparation(const int &ID, const int &result, const string &name)
	{
		return (this->ID == ID) && (this->result == result) && (this->name == name);
	}
	void SetTable(const Table &table)
	{
		this->ID = table.ID;
		this->result = table.result;
		this->name = table.name;
	}
	void SetTable(const int &ID, const int &result, const string &name)
	{
		this->ID = ID;
		this->result = result;
		this->name = name;
	}

	void ResetTable()
	{
		ID = 0;
		result = 0;
		name = "";
	}

	bool IsEmpty()
	{
		return ID == 0;
	}
};

class HashTable
{
private:
	const int capacity = MAXSIZE / 2;
	Table key[MAXSIZE / 2];
	int size;
	// Được gọi khi gặp đụng độ trong hashTable
	int nextAddress(int addr)
	{
		int index = addr;

		// tìm bàn trống tiếp theo kề ID đang bận
		while (key[index % capacity].IsEmpty() == false)
			++index;
		return (index % capacity);
	}

	void removeAll()
	{
		for (int i = 0; i < capacity; ++i)
			key[i].ResetTable();
	}

public:
	HashTable()
	{
		this->size = 0;
		for (int i = 0; i < capacity; ++i)
			key[i].ResetTable();
	}

	~HashTable()
	{
		Clear();
	}

	int getCapa()
	{
		return this->capacity;
	}
	int getSize()
	{
		return this->size;
	}

	bool fullSize()
	{
		return (this->size >= capacity);
	}

	bool searchTable(int ID, int result, string name)
	{
		for (int i = 0; i < capacity; ++i)
		{
			if (key[i].comparation(ID, result, name))
				return true;
		}
		return false;
	}

	void AddTable(Table table, int addr)
	{
		if (fullSize() || addr < 0 || addr >= capacity)
			return;
		if (key[addr].IsEmpty() == false)
			addr = nextAddress(addr);
		key[addr].SetTable(table);
		++size;
	}
	Table keyTable(int address)
	{
		return key[address];
	}

	void Clear()
	{
		removeAll();
		this->size = 0;
	}

	// xóa bàn với id đã biết
	void RemoveTable(int ID)
	{
		for (int i = 0; i < capacity; ++i)
		{
			if (ID == key[i].ID)
			{
				key[i].ResetTable();
				return;
			}
		}
	}
};
//* END

class BuilHuff
{
private:
	char val;
	int freq;
	BuilHuff *pLeft;
	BuilHuff *pRight;

public:
	BuilHuff(char value = 0, int frequent = 0)
	{
		this->val = value;
		this->freq = frequent;
		this->pLeft = NULL;
		this->pRight = NULL;
	}

	~BuilHuff()
	{
		this->val = 0;
		this->freq = 0;
		pLeft = 0;
		pRight = 0;
	}

	char toValue()
	{
		return this->val;
	}

	int toFreq()
	{
		return this->freq;
	}
	BuilHuff *Right() const
	{
		return this->pRight;
	}

	void getBranRight(BuilHuff *branRight)
	{
		this->pRight = branRight;
	}
	BuilHuff *Left() const
	{
		return this->pLeft;
	}

	void setBranLeft(BuilHuff *branLeft)
	{
		this->pLeft = branLeft;
	}
	void HuffEnCode(BuilHuff *node, unordered_map<char, string> &HuffCode, string str)
	{
		if (node == nullptr)
		{
			return;
		}
		if (!node->Left() && !node->Right())
		{
			HuffCode[node->toValue()] = str;
		}

		HuffEnCode(node->Left(), HuffCode, str + "0");
		HuffEnCode(node->Right(), HuffCode, str + "1");
	}
};

void removeHuff(BuilHuff *ptr)
{
	if (!ptr)
		return;
	if (ptr->Left())
		removeHuff(ptr->Left());
	if (ptr->Right())
		removeHuff(ptr->Right());
	delete ptr;
	ptr = NULL;
}

void add(list<BuilHuff *> &listNode, BuilHuff *node)
{
	if (listNode.empty())
	{
		listNode.push_back(node);
		return;
	}
	for (auto huffNode = listNode.begin(); huffNode != listNode.end(); ++huffNode)
	{
		if ((*huffNode)->toFreq() > node->toFreq())
		{
			listNode.insert(huffNode, node);
			return;
		}
	}
	listNode.push_back(node);
}

BuilHuff *BuilHuffTree(list<BuilHuff *> listItem)
{
	while (listItem.size() > 1)
	{
		//! Chọn node có tần số xuất hiện nhỏ nhất để làm con trái
		BuilHuff *branLeft = listItem.front();
		listItem.pop_front();

		//! Node có tần số nhỏ kề làm child-Right
		BuilHuff *branRight = listItem.front();
		listItem.pop_front();

		// Khơi tạo một nút mới
		BuilHuff *newNode = new BuilHuff('.', branLeft->toFreq() + branRight->toFreq());
		newNode->setBranLeft(branLeft);
		newNode->getBranRight(branRight);

		// Thêm node vừa tạo vào heap
		add(listItem, newNode);
	}
	return listItem.front();
}

int EnCoding(string name)
{
	// số bit Max có thể lấy từ phải
	const int MAXBIT = 15;

	// Tạo mảng để lưu trữ kí tự thuộc string Huff
	unordered_map<char, int> freq;
	for (char ch : name)
		freq[ch]++;
	if (freq.size() == 1)
		return (1 << min(freq[name[0]], MAXBIT)) - 1;

	// Khởi tạo cấu trúc min-heap để lưu huffman
	list<BuilHuff *> listNode;
	for (char ch = 'A'; ch <= 'Z'; ++ch)
	{
		if (!freq[ch])
			continue;
		BuilHuff *newNode = new BuilHuff(ch, freq[ch]);
		add(listNode, newNode);
	}
	for (char ch = 'a'; ch <= 'z'; ++ch)
	{
		if (!freq[ch])
			continue;
		BuilHuff *newNode = new BuilHuff(ch, freq[ch]);
		add(listNode, newNode);
	}

	// tạo cây Huffman gán vào root
	BuilHuff *root = BuilHuffTree(listNode);

	//! Huffman convert
	unordered_map<char, string> huffCode;
	root->HuffEnCode(root, huffCode, "");
	removeHuff(root);

	//! Khởi tạo chuỗi để lưu trữ huffman
	string strHuffman = "";

	for (int i = (int)name.length() - 1; i >= 0; --i)
	{
		// ! Duyệt qa từng kí tự trong chuỗi và convert
		char c = name[i];
		strHuffman = huffCode[c] + strHuffman;

		if (strHuffman.length() >= MAXBIT)
			break;
	}

	int sizeBit = strHuffman.length();
	// ! CONVER CHUỖI NHỊ PHÂN THU ĐC SANG Decimal
	int huffmanToDec = 0;
	if (sizeBit <= MAXBIT)
	{
		for (int i = 0; i < sizeBit; ++i)
			huffmanToDec = (huffmanToDec << 1) + (strHuffman[i] - '0');
		return huffmanToDec;
	}

	for (int i = sizeBit - MAXBIT; i < sizeBit; ++i)
		huffmanToDec = (huffmanToDec << 1) + (strHuffman[i] - '0');
	return huffmanToDec;
}

//!-------- AVL
class AVLNode
{
public:
	Table TB;
	AVLNode *pLeft, *pRight;

	AVLNode(Table table)
	{
		this->TB.SetTable(table);
		this->pLeft = NULL;
		this->pRight = NULL;
	}
	~AVLNode()
	{
		this->TB.ResetTable();
		this->pLeft = NULL;
		this->pRight = NULL;
	}
};

class AVLTree
{
private:
	const int capacity = MAXSIZE / 2;
	AVLNode *root;
	int size;

	// Cân bằng khi cây lệch trái
	AVLNode *rightRotate(AVLNode *n)
	{
		AVLNode *x = n->pLeft;
		AVLNode *y = x->pRight;
		x->pRight = n;
		n->pLeft = y;
		return x;
	}
	// Cân bằng khi cây lệch phải
	AVLNode *leftRotate(AVLNode *n)
	{
		AVLNode *x = n->pRight;
		AVLNode *y = x->pLeft;
		x->pLeft = n;
		n->pRight = y;
		return x;
	}

	// INSERT Node
	AVLNode *InsertNode(AVLNode *root, Table table)
	{
		if (!root)
		{
			AVLNode *node = new AVLNode(table);
			return node;
		}
		if (table.result < root->TB.result)
			root->pLeft = InsertNode(root->pLeft, table);
		if (table.result >= root->TB.result)
			root->pRight = InsertNode(root->pRight, table);

		int balance = toBalance(root);
		if (balance > 1)
		{
			if (table.result < root->pRight->TB.result)
			{ // When too much right node
				root->pRight = rightRotate(root->pRight);
			}
			return leftRotate(root);
		}

		// LEFT ORIENTED -> ROTATE RIGHT
		if (balance < -1)
		{
			if (table.result > root->pLeft->TB.result)
			{
				// ! LỆCH TRÁI
				root->pLeft = leftRotate(root->pLeft);
			}
			return rightRotate(root);
		}
		return root;
	}

	// DELETE node which matchs Table table
	AVLNode *removeTBofAVL(AVLNode *root, Table table)
	{
		if (!root)
			return root;

		// tìm xóa bàn thuộc nháh phải AVL với result > root
		if (table.result > root->TB.result || table.ID != root->TB.ID)
			root->pRight = removeTBofAVL(root->pRight, table);
		// tìm xóa bàn thuộc nháh trái AVL với result <root
		if (table.result < root->TB.result || table.ID != root->TB.ID)
			root->pLeft = removeTBofAVL(root->pLeft, table);

		// Tìm thấy bàn cần xóa
		else
		{
			if (!root->pLeft || !root->pRight)
			{
				// !TH NODE XÓA CHỈ CÓ 1 CON
				AVLNode *temp = (root->pLeft) ? root->pLeft : root->pRight;

				if (temp == NULL)
				{ // ROOT is LEAF
					temp = root;
					root = NULL;
				}
				else
					root->TB.SetTable(temp->TB);

				delete temp;
				if (root)
				{
					// ! reset root
					root->pLeft = NULL;
					root->pRight = NULL;
				}
			}
			else
			{ //! TH node có 2 con
				Table newTable = MinTB(root->pRight);
				root->TB.SetTable(newTable);
				root->pRight = removeTBofAVL(root->pRight, newTable);
			}
		}
		// ktra node đã xóa có fai là lá ko??
		if (!root)
			return root;
		int balance = toBalance(root);
		// lệch PHẢI

		if (balance > 1)
		{
			if (toBalance(root->pRight) < -1)
			{ // When too much left node on right child
				root->pRight = rightRotate(root->pRight);
			}
			return leftRotate(root);
		}

		// LỆCH TRÁI
		if (balance < -1)
		{
			if (toBalance(root->pLeft) > 1)
			{ // When too much right node on left child
				root->pLeft = leftRotate(root->pLeft);
			}
			return rightRotate(root);
		}
		return root;
	}

	void removeAll(AVLNode *node)
	{
		if (!node)
			return;
		if (node->pLeft)
			removeAll(node->pLeft);
		if (node->pRight)
			removeAll(node->pRight);
		delete node;
		node = NULL;
	}

	bool find(AVLNode *node, int &ID, int &result, string &name)
	{
		if (!node)
			return false;
		Table curr = node->TB;
		if (curr.comparation(ID, result, name))
			return true;
		if (curr.result > result)
			return find(node->pLeft, ID, result, name);
		else if (curr.result < result)
			return find(node->pRight, ID, result, name);
		else
		{
			if (curr.ID != ID)
				return find(node->pLeft, ID, result, name) || find(node->pRight, ID, result, name);
		}
		return false;
	}

protected:
	int toHeightTree(AVLNode *node)
	{
		if (!node)
			return 0;
		int LH = (node->pLeft) ? this->toHeightTree(node->pLeft) : 0;
		int RH = (node->pRight) ? this->toHeightTree(node->pRight) : 0;
		return ((LH > RH) ? LH : RH) + 1;
	}

	Table MinTB(AVLNode *root)
	{
		while (root->pLeft)
			root = root->pLeft;
		return root->TB;
	}

	int toBalance(AVLNode *root)
	{
		if (root == nullptr)
			return 0;
		return toHeightTree(root->pRight) - toHeightTree(root->pLeft);
	}

public:
	AVLTree()
	{
		this->root = NULL;
		size = 0;
	}
	~AVLTree()
	{
		Clear();
	}
	int getHeight()
	{
		return toHeightTree(root);
	}

	AVLNode *getRoot()
	{
		return this->root;
	}
	void InsertTable(Table table)
	{
		if (size < capacity)
		{
			root = InsertNode(root, table);
			++size;
		}
	}
	bool fullSize()
	{
		return (this->size >= capacity);
	}
	bool searchTable(int id, int result, string name)
	{
		return find(this->root, id, result, name);
	}

	void DeleteTable(Table table)
	{
		if (size > 0)
		{
			root = removeTBofAVL(root, table);
			--size;
		}
	}
	void Clear()
	{
		removeAll(root);
		root = NULL;
		size = 0;
	}
};

//* -----------BUILD MIN HEAP
struct booking
{
	int id;
	int count;
	void reset()
	{
		id = 0;
		count = 0;
	}
};

class MinHeap
{
private:
	int capacity = MAXSIZE;
	booking countBook[MAXSIZE];
	int size;
	vector<int> flagTime;
	/**
	 *  if (position <= 0 || position >= count) return;
	int parent = (position - 1) / 2;
	if (elements[parent] < elements[position]){
		int temp = elements[parent];
		elements[parent] = elements[position];
		elements[position] = temp;
		reheapUp(parent);
	}
	return;
	*/

	void ReheapDown(int position)
	{
		int left = 2 * position + 1;
		int right = 2 * position + 2;
		int smaller = -1;
		if (left < size)
		{
			if (right < size)
			{
				if (countBook[right].count < countBook[left].count)
					smaller = right;
				else if (countBook[right].count == countBook[left].count)
				{
					int step = find(flagTime.begin(), flagTime.end(), countBook[right].id) -
							   find(flagTime.begin(), flagTime.end(), countBook[left].id);
					if (step < 0)
						smaller = right;
					else
						smaller = left;
				}
				else
					smaller = left;
			}
			else
				smaller = left;
			if (countBook[position].count > countBook[smaller].count)
			{
				swap(countBook[position], countBook[smaller]);
				ReheapDown(smaller);
			}
			else if (countBook[position].count == countBook[smaller].count)
			{
				int step = find(flagTime.begin(), flagTime.end(), countBook[position].id) -
						   find(flagTime.begin(), flagTime.end(), countBook[smaller].id);
				if (step > 0)
				{
					swap(countBook[position], countBook[smaller]);
					ReheapDown(smaller);
				}
			}
		}
	}
	void ReheapUP(int position)
	{
		if (position > 0)
		{
			int parent = (position - 1) / 2;
			if (countBook[position].count < countBook[parent].count)
			{
				swap(countBook[position], countBook[parent]);
				ReheapUP(parent);
			}
			else if (countBook[position].count == countBook[parent].count)
			{
				int step = find(flagTime.begin(), flagTime.end(), countBook[position].id) -
						   find(flagTime.begin(), flagTime.end(), countBook[parent].id);
				if (step < 0)
				{
					swap(countBook[position], countBook[parent]);
					ReheapUP(parent);
				}
			}
		}
	}

	//! được gọi khi 1 khách mới được thêm vào min heap
	void heapPush(int id, int count)
	{
		if (fullSize())
			return;
		countBook[size].id = id;
		countBook[size].count = count;
		ReheapUP(size);
		++size;
	}

	void heapPop(int id)
	{
		if (size <= 0)
			return;
		int idx = 0;
		while (countBook[idx].id != id)
			++idx;
		countBook[idx] = countBook[size - 1];
		countBook[size - 1].reset();
		--size;
		ReheapDown(idx);
	}

	void Show(int position)
	{
		if (position >= size)
			return;
		// in ID - NUM số lượng đặt bàn
		cout << countBook[position].id << "-" << countBook[position].count << "\n";
		// duyệt trái
		Show(2 * position + 1);
		// duyệt phải
		Show(2 * position + 2);
	}

	int NumberBooking(int id)
	{
		for (int i = 0; i < size; ++i)
		{
			if (countBook[i].id == id)
				return countBook[i].count;
		}
		return 0;
	}

public:
	MinHeap()
	{
		size = 0;
		for (int i = 0; i < MAXSIZE; ++i)
		{
			countBook[i].count = 0;
			countBook[i].id = 0;
		}
	}

	~MinHeap() {}

	bool fullSize()
	{
		return (size >= capacity);
	}

	// Checking ID xem người dùng push vào min-heap đã từng Order chưa -->
	void Push(int id)
	{
		for (int i = 0; i < size; ++i)
		{
			if (countBook[i].id == id)
			{
				//! đã tưng order món trước đó --> tăng count +1
				int booking_id = countBook[i].id;
				int booking_count = countBook[i].count + 1;
				heapPop(booking_id);
				heapPush(booking_id, booking_count);
				return;
			}
		}
		// !
		flagTime.push_back(id);
		heapPush(id, 1);
	}

	// !
	void Pop(int id)
	{
		flagTime.erase(find(flagTime.begin(), flagTime.end(), id));
		heapPop(id);
	}
	// !
	int IdOrderFist()
	{
		if (size <= 0)
			return -1;
		return countBook[0].id;
	}

	int getOrder(int id)
	{
		return NumberBooking(id);
	}

	void printInfor()
	{
		Show(0);
	}
};
// !REG
// ĐẶT BÀN CHO KHÁCH HÀNG THEO TÊN
void IncreaUser(const Table &customer, vector<int> &SuccessKQ, vector<bool> &isHash,
				HashTable &StructerHashTable,
				AVLTree *&StructerAVL);
// 	REMOVE khách hàng
void DeleteUser(const Table &customer, vector<int> &SuccessKQ, vector<bool> &isHash,
				HashTable &StructerHashTable,
				AVLTree *&StructerAVL);
void PrintAVL(AVLTree *&StructerAVL, MinHeap &LFCO_Heap);
void PrintHT(HashTable &StructerHashTable, MinHeap &LFCO_Heap);
void PrintMH(MinHeap &LFCO_Heap);

void simulate(string filename)
{
	ifstream myfile(filename);
	if (!myfile)
		return;

	list<int> FIFO_Queue;
	list<int> LRCO_List;
	MinHeap LFCO_Heap;

	vector<int> SuccessKQ(MAXSIZE + 1, -1);
	vector<bool> IsHash(MAXSIZE + 1, true);
	// Hash-Table
	HashTable StructerHashTable;
	// AVL Tree
	AVLTree *StructerAVL = new AVLTree();

	string line = "";
	while (getline(myfile, line))
	{
		int index = 0;
		string request = "";

		for (int i = 0; i < (int)line.length() and line[i] != ' '; ++i)
			request += line[i];

		index += ((int)request.length() + 1);

		if (request == "REG")
		{
			bool fullSize = StructerAVL->fullSize() && StructerHashTable.fullSize();
			bool booking = false;
			string name = "";
			for (int i = index; i < (int)line.length() and line[i] != ' '; ++i)
			{
				char c = line[i];
				if (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z'))
					name += c;
				else
					break;
			}
			index += ((int)name.length());

			if (index < (int)line.length())
				continue;
			int customerResult = EnCoding(name);
			int customerID = customerResult % MAXSIZE + 1;

			for (int id = 1; id <= MAXSIZE; ++id)
			{
				if (SuccessKQ[id] == customerResult)
				{
					int result = customerResult;
					if (IsHash[id])
					{
						if (StructerHashTable.searchTable(id, result, name))
							booking = true;
					}
					else
					{
						if (StructerAVL->searchTable(id, result, name))
							booking = true;
					}
				}
				if (booking)
				{
					customerID = (id - 1) % MAXSIZE + 1;
					break;
				}
			}
			if (!booking)
			{

				// ! Nếu khách gặp TH ko có bàn->>
				if (fullSize)
				{
					int IdPeopleDEL = -1;
					int OPT = customerResult % 3;
					Table TbDelete;
					// !OPT = 0
					if (OPT == 0)
					{
						IdPeopleDEL = FIFO_Queue.front();
						FIFO_Queue.pop_front();
					}

					// ! OPT = 1
					if (OPT == 1)
					{
						IdPeopleDEL = LRCO_List.front();
						LRCO_List.pop_front();
					}

					// ! OPT = 2
					if (OPT == 2)
					{
						IdPeopleDEL = LFCO_Heap.IdOrderFist();
						LFCO_Heap.Pop(IdPeopleDEL);
					}
					//  Delete Table tại user bị loại ra
					TbDelete.SetTable(IdPeopleDEL, SuccessKQ[IdPeopleDEL], "");
					DeleteUser(TbDelete, SuccessKQ, IsHash, StructerHashTable, StructerAVL);
				}
				while ((customerID <= 2 * MAXSIZE) && SuccessKQ[(customerID - 1) % MAXSIZE + 1] != -1)
				{
					++customerID;
				}
				customerID = (customerID - 1) % MAXSIZE + 1;

				Table customer;
				customer.SetTable(customerID, customerResult, name);

				IncreaUser(customer, SuccessKQ, IsHash, StructerHashTable, StructerAVL);

				FIFO_Queue.push_back(customerID);
				LRCO_List.push_back(customerID);
				LFCO_Heap.Push(customerID);
			}
			else
			{
				LRCO_List.remove(customerID);
				LRCO_List.push_back(customerID);
				LFCO_Heap.Push(customerID);
			}
		}

		// ! ĐUỔI KHÁCH THEO YÊU CẦU KHỎI BÀN
		else if (request == "CLE")
		{
			bool isPresent = false;
			string temp = "";
			if (line[index] == '-')
			{
				isPresent = true;
				++index;
			}

			for (int i = index; i < (int)line.length() && line[i] != ' '; ++i)
			{
				char c = line[i];
				if ('0' <= c && c <= '9')
					temp += c;
				else
					break;
			}
			index += temp.length();
			if (index < (int)line.length())
				continue;
			int number = stoi(temp) * (isPresent ? -1 : 1);

			if (number < 1)
			{
				for (auto begin = FIFO_Queue.begin(); begin != FIFO_Queue.end(); ++begin)
				{
					if (IsHash[*begin])
					{
						int id = *begin;
						SuccessKQ[id] = -1;
						LRCO_List.remove(id);
						LFCO_Heap.Pop(id);
						auto newbegin = --begin;
						FIFO_Queue.remove(id);
						begin = newbegin;
					}
				}
				StructerHashTable.Clear();
			}

			else if (number > MAXSIZE)
			{
				for (auto begin = FIFO_Queue.begin(); begin != FIFO_Queue.end(); ++begin)
				{
					if (!IsHash[*begin])
					{
						cout << *begin << endl;
						int id = *begin;
						SuccessKQ[id] = -1;
						LRCO_List.remove(id);
						LFCO_Heap.Pop(id);
						auto newBegin = --begin;
						FIFO_Queue.remove(id);
						begin = newBegin;
					}
				}
				StructerAVL->Clear();
			}
			else
			{
				if (SuccessKQ[number] == -1)
					continue;
				Table customer;
				customer.SetTable(number, SuccessKQ[number], "");
				DeleteUser(customer, SuccessKQ, IsHash, StructerHashTable, StructerAVL);
				FIFO_Queue.remove(customer.ID);
				LFCO_Heap.Pop(customer.ID);
				LRCO_List.remove(customer.ID);
			}
		}
		else if (request == "PrintMH")
		{
			PrintMH(LFCO_Heap);
		}
		else if (request == "PrintHT")
		{
			PrintHT(StructerHashTable, LFCO_Heap);
		}

		else if (request == "PrintAVL")
		{
			PrintAVL(StructerAVL, LFCO_Heap);
		}
		else
		{
			continue;
		}
	}
	delete StructerAVL;
}

void DeleteUser(const Table &customer, vector<int> &SuccessKQ, vector<bool> &isHash,
				HashTable &StructerHashTable,
				AVLTree *&StructerAVL)
{
	int customerID = customer.ID;
	if (isHash[customerID])
	{
		StructerHashTable.RemoveTable(customerID);
	}
	else
	{
		StructerAVL->DeleteTable(customer);
		isHash[customerID] = true;
	}
	SuccessKQ[customerID] = -1;
}
void IncreaUser(const Table &customer, vector<int> &SuccessKQ, vector<bool> &isHash,
				HashTable &StructerHashTable,
				AVLTree *&StructerAVL)
{

	int customerResult = customer.result;
	int customerID = customer.ID;
	SuccessKQ[customerID] = customerResult;

	if (customerResult % 2 == 0 || StructerHashTable.fullSize())
	{
		StructerAVL->InsertTable(customer);
		isHash[customerID] = false;
	}
	else if (customerResult % 2 == 1 || StructerAVL->fullSize())
	{
		StructerHashTable.AddTable(customer, customerResult % (MAXSIZE >> 1));
		isHash[customerID] = true;
	}
}
void PrintMH(MinHeap &LFCO_Heap)
{
	LFCO_Heap.printInfor();
}

void PrintAVL(AVLTree *&StructerAVL, MinHeap &LFCO_Heap)
{
	queue<AVLNode *> q;
	q.push(StructerAVL->getRoot());

	while (!q.empty())
	{
		AVLNode *curr = q.front();
		q.pop();
		if (curr->pLeft)
			q.push(curr->pLeft);
		if (curr->pRight)
			q.push(curr->pRight);

		int orderCount = LFCO_Heap.getOrder(curr->TB.ID);
		cout << curr->TB.ID << "-" << curr->TB.result << "-" << orderCount << "\n";
	}
}
void PrintHT(HashTable &StructerHashTable, MinHeap &LFCO_Heap)
{
	for (int i = 0; i < StructerHashTable.getCapa(); ++i)
	{
		Table table = StructerHashTable.keyTable(i);
		if (table.IsEmpty())
			continue;
		int orderCount = LFCO_Heap.getOrder(table.ID);
		cout << table.ID << "-" << table.result << "-" << orderCount << "\n";
	}
}
