#include <iostream>
#include <exception>

using namespace std;

struct NotFoundException : public exception
{
   const char* what() const throw () 
   {
      return "Element not found.";
   }
};

template <typename T>
struct Node{
    T data;
    Node<T> *pNext;

    Node(T x):data(x), pNext(NULL){}

    ~Node()
    {
        cout << "deletou " << data << endl;
    }
};

template <typename T>
class LinkedList{
private:
    Node<T> *pRoot;
    int length;

public:
    class Iterator
    {
    public:
        Node<T> *pNodo;
    public:
        Iterator()
        {
            this->pNodo = NULL;
        }
        Iterator(Node<T> *p)
        {
            this->pNodo = p;
        }
        bool operator!=(Iterator  it)
        {
            return it.pNodo != this->pNodo;
        }
        Iterator& operator++()
        {
            this->pNodo = this->pNodo->pNext;
            return *this;
        }
        T& operator*()
        {
            T *p = &(this->pNodo->data);
            return *p;
        }
    };

public:
    LinkedList(): pRoot(NULL), length(0) {}

    
    LinkedList(initializer_list<T> list): pRoot(NULL), length(0)
    {
        for( auto elem : list )
        {
            insert(elem);
        }
    }

    ~LinkedList()
    {
        Node<T> *obj = pRoot;
        Node<T> *aux;
        while(obj) 
        {
            aux = obj-> pNext;
            delete obj;
            obj = aux;
        }
    }


    bool find(T x, Node<T> **&pNode) {
        pNode = &pRoot;
        while(*pNode && ((*pNode)->data <= x)){
            if ((*pNode)->data==x) return true;
            pNode = &((*pNode)->pNext);
        }
        return false;
    }


    void insert(T x) {
        // STEPS:
        // 1. Use the find function to check if the value `x` exists
        Node<T> **auxNode;
        bool exists = find(x, auxNode);
        // 2. If it exists, then return
        if(exists) return; 
        // 3. Else create a new node (using dinamic memory)
        Node<T> *newNode = new Node<T>(x);
        // 4. Set pointers (Hint: you need to set 2 pointers)
        Node<T> *aux = *auxNode;
        *auxNode = newNode;
        (*auxNode)->pNext = aux;
        // 5. Increase the `length` attribute 
        length++;
    }

    void print() {
        Node<T> *obj = pRoot;
        while(obj) {
            cout << obj->data << " ";
            obj=obj->pNext;
        }
        cout << endl;

    }

    void remove(T x) {
        // STEPS: 
        // 1. Use the find function to check if the value `x` exists
        Node<T> **auxNode;
        bool exists = find(x, auxNode);
        // 2. If it does not exist, then return
        if(!exists) {
            throw NotFoundException();
            return;
        } 
        // 3. Else set pointers (Hint: just one pointer)
        Node<T> *trash = *auxNode;
        *auxNode = (*auxNode)->pNext;
        // 4. Release memory
        delete trash;
        // 5. Decrease the `length` attribute 
        length--;
    }

    Iterator begin()
    {
        Iterator it(pRoot);
        return it;
    }
    Iterator end()
    {
        Iterator it;
        for (it = (*this).begin(); it.pNodo!=NULL; ++it) {}
        return it;
    }
};


int main() {

// test insert and remove
    cout << "Test Insert and Remove" << endl;
    LinkedList<int> list;
    list.insert(1);
    list.insert(10);
    list.insert(5);
    list.insert(-1);
    list.insert(1);
    list.insert(1000);
    list.print();

    list.remove(5);
    list.print();


// test Constructor
    cout << "Test Constructor" << endl;
    // Option  2: Initialization List
    LinkedList<int> list2({1, 2, 10, 2, 3});
    list2.print();
    cout<<endl;

// test Destructor
    LinkedList<int> *listdel = new LinkedList<int>({1,4,5,2,3,4,8,9});
    (*listdel).print();
    delete listdel;
    cout<<endl;

// test Template
    cout << "Test Template" << endl;
    // create a linked list for three data types

    LinkedList<int> ilist({1, 10, 2});
    ilist.print();
    // output: 1 10 2

    LinkedList<float> flist({1.2, 1.4, 100000.0});
    flist.print();
    // output: 1.2 1.4 100000

    LinkedList<string> slist({"one", "two", "three"});
    slist.print();
    //  output: one three two
    cout<<endl;

// test Iterator
    cout << "Test Iterator" << endl;
    LinkedList<int> ilist2({1, 2, 10, 2, 3});
    LinkedList<int>::Iterator  it;
    for(it=ilist2.begin(); it!=ilist2.end(); ++it)
    {
        cout<< *it << " " ;
    }
    cout << endl;
    cout << endl;

// test Exception
    cout << "Test Exception" << endl;
    LinkedList<int> ilist3({1, 2, 10, 2, 3});
    /*
    // if we remove an item that doesn't exist it should throw an error
    ilist3.remove(20);
    // output: lib c++abi.dylib: terminating with uncaught
    //exception of type NotFoundException: Element not found
    cout << endl;
    */

    // Correct way to handle exceptions
    try
    {
        ilist3.remove(20);
    }
    catch (const NotFoundException& e)
    {
        cerr << e.what() << endl;
    }
    // output: Element not found
    cout<<endl;

    return 0;
}
