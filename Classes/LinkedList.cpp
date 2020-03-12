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
	
	int size=0;
	
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
		size++;
	}
	
	void print(){
		Node *pCurr = this->pRoot;
		while(pCurr!=0){
			cout << pCurr->data << " ";
			pCurr = pCurr->pNext;
		}
		cout << endl;
	}
	
	Node* find(int v){
		Node *pLast = this->pRoot;
		while(pLast!=NULL && pLast->data!=v){
			pLast = pLast->pNext;
		}
		
		if (pLast!=0){
			return pLast;
		}else{
			return NULL;
		}
		
	}
	
	void dumb_sort(){
		Node *sec = this->pRoot->pNext, *first = this->pRoot, *ant, *aux;
		while(sec!=NULL){
			ant->pNext = sec;
			aux = sec->pNext;
			sec->pNext = first;
			first->pNext=aux;
			
			while(sec!=NULL && sec->data >= first->data){
				ant = first;
				first = sec;
				sec = sec->pNext;
			}
			
		}	
	}
	
};



int main(){
	
	Node *p;
	
	LinkedList list;
	list.insert(3);
	list.insert(43);
	list.insert(1);
	list.print();
	
	p = list.find(3);
	
	if(p!=0) cout << p->data << endl; else cout << "ponteiro nulo" << endl;
	
	list.dumb_sort();
	list.print();
	
	return 0;
}

