#include <iostream>

using namespace std;

struct Node {
	Node *pNext;
	int data;
	Node(int v){
		this->data = v;
		this->pNext = NULL;
	}
};


class LinkedList {
	
private:
	Node *pRoot;
	
public:
	
	LinkedList(){
		this->pRoot = NULL;
	}
	
	void insert(int v){
		if(this->pRoot==0){
			Node *pNew = new Node(v);
			pRoot = pNew;
			return;
		}
		Node *pLast = this->pRoot;
		while(pLast->pNext!=0){
			pLast = pLast->pNext;
		}
		Node *pNew = new Node(v);
		pLast->pNext = pNew;
		
	}
	
	void print(){
		Node *pCurr = this->pRoot;
		while(pCurr!=0){
			cout << pCurr->data << " ";
			pCurr = pCurr->pNext;
		}
		cout << endl;
	}
	
};



int main(){
	
	LinkedList list;
	list.insert(3);
	list.insert(43);
	list.insert(1);
	list.print();
	
	return 0;
}

