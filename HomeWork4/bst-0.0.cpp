#include <iostream>
#include <iomanip>

using namespace std;

struct Node {
    int data;
    Node *pChild[2];
    bool isblack;

    Node(int x, bool cor):data(x), isblack(cor) {
        pChild[0] = pChild[1] = nullptr;
    }
};

class BST {
protected:
    Node *pRoot;

public:
    BST():pRoot(nullptr) {}

    template<typename... Args>
    BST(Args... args):pRoot(nullptr) {
        insert(args...);
    }

    bool find(int x) {
        Node **p;
        return find(x, p);
    }
    template<typename T>
    void insert(T x) {
        if (!pRoot) 
        {
            pRoot = new Node(x, 1);
            return;
        }
        Node **p;
        if (!find(x, p)) 
        {
            *p = new Node(x, 0);
            recolor(p);
        }
    }

    template<typename T, typename... Args>
    void insert(T x, Args... args) {
        insert(x);
        insert(args...);
    }
    
    void remove(int x) {
        Node **p;
        if(find(x, p))
            remove(*p);
    }

    void print() {
        print(pRoot);
        cout << endl;
    }

private:
    bool find(int x, Node **&p) {
        p = &pRoot;
        while(*p) {
            if ((*p)->data==x) return true;
            p = &((*p)->pChild[(*p)->data < x]);
        }
        return false;
    }

    bool parent(int x, Node **&p) {
        p = &pRoot;
        if ((*p)->data==x) return false;
        while(*p) {
            if ((*p)->pChild[(*p)->data < x]->data==x) return true;
            p = &((*p)->pChild[(*p)->data < x]);
        }
        return false;
    }


    void doubleblack(Node *p){
        Node *s, **pai;
        bool tempai = parent(p->data, pai);
        bool sright = (*pai)->pChild[0]==p;
        s = (*pai)->pChild[sright];

        if(p==this->pRoot){
            return;
        }

        if (s->isblack && (!s->pChild[0]->isblack || !s->pChild[1]->isblack)){
            bool rright = !s->pChild[1]->isblack;
        Node *r = s->pChild[rright];
        if(!sright && !rright){
            right_rotate(pai);
            r->isblack = 1;
        }
        if(sright && !rright){
            Node **points = &s;
            right_rotate(points);
            r->pChild[1]->isblack = 1;
            left_rotate(pai);
        }
        if(!sright && rright){
            Node **points = &s;
            left_rotate(points);
            r->pChild[1]->isblack = 1;
            right_rotate(pai);
        }
        if(sright && rright){
            left_rotate(pai);
            r->isblack = 1;
        }
            return;
        }
        if (!s->isblack){
            if(sright){
                left_rotate(pai);
                s->isblack = 1;
                (*pai)->isblack = 0;
                doubleblack(p);
            }else{
                right_rotate(pai);
                s->isblack = 1;
                (*pai)->isblack = 0;
                doubleblack(p);
            }
            return;
        }
        if (s->isblack && s->pChild[0]->isblack && !s->pChild[1]->isblack){
            if((*pai)->isblack){
                s->isblack = 0;
                doubleblack(*pai);
            }else{
                (*pai)->isblack = 1;
                s->isblack = 0;
            }
            return;
        }
    }

    void remove(Node *&p) {
        Node **succesor;
        if(!p->isblack && (!p->pChild[0] && !p->pChild[1])){
            p = NULL;
            return;
        }
        if(p->isblack && (!p->pChild[0] && !p->pChild[1])){
            Node **pai;
            bool tempai = parent(p->data, pai);
            (*pai)->pChild[p->data==(*pai)->pChild[1]->data]->isblack = 0;
            p = NULL;
            return;
        }
        if (!p->pChild[0] || !p->pChild[1]) {
            succesor = &(p->pChild[p->pChild[1]!=nullptr]);
        } else {
            succesor = &(p->pChild[1]);
            find_min(succesor);
        }
        bool corsuc;
        try{
            corsuc = (*succesor)->isblack;
        } catch(...){
            corsuc = 1;
        }

        if (!p->isblack || !corsuc){
            p->data = (*succesor)->data;
            p->isblack = 1;
            remove(*succesor);
            return;
        }
        p->data = (*succesor)->data;
        remove(*succesor);
        doubleblack(p);
        
    }

    void find_min(Node **&p) {
        while((*p)->pChild[0]){
            p = &((*p)->pChild[0]);
        }
    }

    void print(Node *p, int indent=0) {
        if (p) {
            print(p->pChild[1], indent+6);
            cout << setw(indent) << ' ';
            cout<< p->data << '-' << p->isblack << endl;
            print(p->pChild[0], indent+6);
        }
    }

    void recolor(Node **p){
        // define pai e retorna caso ele seja preto
        bool tempai;
        Node ** pai;
        tempai = parent((*p)->data, pai);
        if(!tempai) 
        {
            (*p)->isblack = 1;
            return;
        }
        if((*pai)->isblack) return;


        // define avo e tio
        Node ** avo, * tio;
        bool paidireita, pdireita;
        tempai = parent((*pai)->data, avo);
        if(*pai == (*avo)->pChild[0])
        {
            tio = (*avo)->pChild[1];
            paidireita = 0;
        }
        else
        {
            tio = (*avo)->pChild[0];
            paidireita = 1;
        }
        if(*p == (*pai)->pChild[0])
        {
            pdireita = 0;
        }
        else
        {
            pdireita = 1;
        }

        // aplica casos
        if(tio)
        {
            if (!(tio->isblack))
            {
                (*pai)->isblack = 1;
                tio->isblack = 1;
                (*avo)->isblack = 0;
                recolor(avo);
                return;
            }
        }
            (*avo)->isblack = 0;
            if(paidireita && pdireita)
            {
                (*pai)->isblack = 1;
                left_rotate(avo);
            }
            else if(!paidireita && !pdireita)
            {
                (*pai)->isblack = 1;
                right_rotate(avo);
            }
            else if(!paidireita && pdireita)
            {
                (*p)->isblack = 1;
                zigzag_left(avo);
            }
            else
            {
                (*p)->isblack = 1;
                zigzag_right(avo);
            }

    }

    void right_rotate(Node ** p){
        Node ** pai;
        bool tempai;
        tempai = parent((*p)->data, pai);
        Node * n = (*p)->pChild[0];
        (*p)->pChild[0] = n->pChild[1];
        n->pChild[1] = *p;
        if(tempai){
            if(*p == (*pai)->pChild[1])
                (*pai)->pChild[1] = n;
            else
                (*pai)->pChild[0] = n;
        } else{
            this->pRoot = n;
        }
    }

    void left_rotate(Node ** p){
        Node ** pai;
        bool tempai;
        tempai = parent((*p)->data, pai);
        Node *n = (*p)->pChild[1];
        (*p)->pChild[1] = n->pChild[0];
        n->pChild[0] = *p;
        if(tempai){
            if(*p == (*pai)->pChild[1])
                (*pai)->pChild[1] = n;
            else
                (*pai)->pChild[0] = n;
        } else{
            this->pRoot = n;
        }
    }

    void zigzag_left(Node **p)
    {
        Node ** pai;
        bool tempai;
        tempai = parent((*p)->data, pai);

        Node * n = (*p)->pChild[0]->pChild[1];
        (*p)->pChild[0]->pChild[1] = n->pChild[0];
        n->pChild[0] = (*p)->pChild[0];
        (*p)->pChild[0] = n->pChild[1];
        n->pChild[1] = *p;

        if(tempai){
            if(*p == (*pai)->pChild[1])
                (*pai)->pChild[1] = n;
            else
                (*pai)->pChild[0] = n;
        } else{
            this->pRoot = n;
        }
    }

    void zigzag_right(Node **p)
    {
        Node ** pai;
        bool tempai;
        tempai = parent((*p)->data, pai);

        Node * n = (*p)->pChild[1]->pChild[0];
        (*p)->pChild[1]->pChild[0] = n->pChild[1];
        n->pChild[1] = (*p)->pChild[1];
        (*p)->pChild[1] = n->pChild[0];
        n->pChild[0] = *p;

        if(tempai){
            if(*p == (*pai)->pChild[1])
                (*pai)->pChild[1] = n;
            else
                (*pai)->pChild[0] = n;
        } else{
            this->pRoot = n;
        }
    }

};

int main() {
    BST bst (41);
    bst.print();
    cout << "-----------------\n";

    bst.insert(38);
    bst.print();
    cout << "-----------------\n";

    bst.insert(31);
    bst.print();
    cout << "-----------------\n";
    
    bst.insert(12);
    bst.print();
    cout << "-----------------\n";

    bst.insert(19);
    bst.print();
    cout << "-----------------\n";

    bst.insert(8);
    bst.print();
    cout << "-----------------\n";

    bst.remove(8);
    bst.print();
    cout << "-----------------\n";

    bst.remove(19);
    bst.print();
    cout << "-----------------\n";

    
    return 0;
}