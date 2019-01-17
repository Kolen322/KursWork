#ifndef LIST_H
#define LIST_H

#include "Cars.h"
class List
{
private:
    class Node {
    public:
        Node * pNext;
        Node * pPrev;
        Car data;
        Node(Car data = Car(), Node *pNext = nullptr, Node *pPrev = nullptr) {
            this->data = data;
            this->pNext = pNext;
            this->pPrev = pPrev;
        }
    };
    int Size;
    Node * head;
    Node * tail;
public:
    class Iterator {
    private:
        Node * head;
    public:
        Iterator(Node *head) {
            this->head = head;
        }
        Iterator operator++(int) { Iterator itr = head;
        head = head->pNext;
        return itr; }
        Iterator operator--(int) {
            Iterator it = head;
            head = head->pPrev;
            return it;
        }
        Car& operator*() { return head->data; }
        bool operator ==(Iterator const rhs) const {
            return head == rhs.head;
        }

        bool operator !=(Iterator const rhs) const {
            return !(*this == rhs);
        }
        Node *GetHead() {
            return head;
        }
    };
    List():head(nullptr),tail(nullptr),Size(0){}
    ~List();
    void push_back(Car var);
    void pop_back();
    void push_front(Car var);
    void pop_front();
    void clear();
    Iterator begin() const {  return Iterator(head); }
    Iterator end() const { return Iterator(tail); }

    Car operator[](int index) const {
        if (index == 0) {
                    return head->data;
                }
            if (index <= Size / 2) {
                int count = 0;
                Node *temp = head;
                while (count != index) {
                    temp = temp->pNext;
                    count++;
                }
                return temp->data;
            }
            else {
                int count = Size-1;
                Node *temp = tail;
                while (count != index) {
                    temp = temp->pPrev;
                    count--;
                }
                return temp->data;
            }
        }
    int GetSize() const;
    void setCar(int indexr, int indexc, QString data);
    void erase(Iterator it);
};
#endif // LIST_H
