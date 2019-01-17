#include "List.h"

List::~List()
{
    clear();
}
void List::push_front(Car var)
{
    if(Size == 0){
        head = tail = new Node(var, head, tail);
        Size++;
    }
    else if (Size == 1) {
        head = new Node(var, head, nullptr);
        tail->pPrev = head;
        tail->pNext = nullptr;
        Size++;
    }
    else {
        Node *temp = head;
        head = new Node(var, head, nullptr);
        temp->pPrev = head;
        Size++;
    }
}

void List::push_back(Car var) {
    if(Size == 0){
        head = tail = new Node(var, head, tail);
        Size++;
    }
    else if (Size == 1) {
        tail = new Node(var, nullptr, head);
        head->pNext = tail;
        head->pPrev = nullptr;
        Size++;
    }
    else
    {
        Node *temp = tail;
        tail = new Node(var, nullptr, temp);
        head->pPrev = tail;
        temp->pNext = tail;
        Size++;
    }
}
void List::pop_front() {
    if (Size == 1) {
        Node* temp = head;
        delete temp;
        Size--;
    }
    else{
    Node *temp = head;
    head = head->pNext;
    delete temp;
    Size--;
}
}
void List::pop_back() {
    if (Size > 2) {
        Node *temp = tail;
        tail = tail->pPrev;
        delete temp;
        Size--;
    }
    else if (Size == 2) {
        Node *temp = tail;
        tail = head;
        delete temp;
        Size--;
    }
    else
    {
        pop_front();
    }
}
void List::clear() {
    while (Size) {
        pop_front();
    }
}
int List::GetSize()const {
    return Size;
}
void List::erase(Iterator it)
{

    if (it == tail) {
        pop_back();
    }
    else if (it == head) {
        pop_front();
    }
    else {
        Node *next = it.GetHead()->pNext;
        Node *prev = it.GetHead()->pPrev;
        delete it.GetHead();
        Size--;
        prev->pNext = next;
        next->pPrev = prev;
    }
}
void List::setCar(int indexr, int indexc, QString data)
{
    if (indexr == 0) {
        switch (indexc) {
        case 0: head->data.SetMake(data); break;
        case 1: head->data.SetModel(data); break;
        case 2: head->data.SetPower(data); break;
        case 3: head->data.SetEngine(data); break;
        case 4: head->data.SetYear(data); break;
        case 5: head->data.SetPlay(data); break;
        }
        return;
    }
    if (indexr <= Size / 2) {
        int count = 0;
        Node *temp = head;
        while (count != indexr) {
            temp = temp->pNext;
            count++;
        }
        switch (indexc) {
        case 0: temp->data.SetMake(data); break;
        case 1: temp->data.SetModel(data); break;
        case 2: temp->data.SetPower(data); break;
        case 3:temp->data.SetEngine(data); break;
        case 4: temp->data.SetYear(data); break;
        case 5: temp->data.SetPlay(data); break;
        }
        return;
    }
    else {
        int count = Size - 1;
        Node *temp = tail;
        while (count != indexr) {
            temp = temp->pPrev;
            count--;
        }
        switch (indexc) {
        case 0: temp->data.SetMake(data); break;
        case 1: temp->data.SetModel(data); break;
        case 2: temp->data.SetPower(data); break;
        case 3:temp->data.SetEngine(data); break;
        case 4: temp->data.SetYear(data); break;
        case 5: temp->data.SetPlay(data); break;
        }
        return;
    }
}
