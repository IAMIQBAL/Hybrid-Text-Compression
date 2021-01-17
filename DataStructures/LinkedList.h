#include <iostream>
using namespace std;

template <typename T>
class Node {
public:
    T data;
    Node *next;
    Node *prev;

    Node(){};
};

template <typename T>
class LinkedList {
public:
    Node<T> *head;
    Node<T> *tail;

public:
    LinkedList(){
        head = NULL;
        tail = NULL;
    }

    void initHead(T item){
        head = new Node<T>();
        head->next = NULL;
        head->prev = NULL;
        head->data = item;
    }

    void insertHead(T item){
        Node<T> *tmp = new Node<T>();
        if (head == nullptr){
            head = tmp;
            head->prev = nullptr;
            head->data = item;
            head->next = nullptr;
            tail = tmp;
        } else {
            tmp->next = head;
            tmp->data = item;
            tmp->prev = nullptr;
            head->prev = tmp;
            head = tmp;
        }
    }

    void insertLast(T item){
        Node<T> *tmp = new Node<T>();
        tmp->data = item;
        if (head == nullptr){
            head = tmp;
            head->prev = nullptr;
            head->next = nullptr;
            tail = tmp;
        } else {
            tmp->prev = tail;
            tail->next = tmp;
            tmp->next = nullptr;
            tail = tmp;
        }
    }

    void insertNext(T item){
        Node<T> *tmp = new Node<T>();
        tmp->next = nullptr;
        tmp->data = item;
        tmp->prev = nullptr;

        Node<T> *iter = head;
        while (iter != nullptr){
            if (iter->next == nullptr){
                iter->next = tmp;
                tmp->prev = iter;
                return;
            }
            iter = iter->next;
        }
    }

    // Returns 0 if Not found. Always add a check
    // for 0 before accessing the tmp->data

    Node<T>* find(T item){
        Node<T> *tmp = head;
        while(tmp != nullptr){
            if (tmp->data == item){
                return tmp;
            }
            tmp = tmp->next;
        }
        return nullptr;
    }

    Node<T>* find(T item, int x){
        Node<T> *tmp = head;
        while(tmp != nullptr){
            if (tmp->data == x){
                return tmp;
            }
            tmp = tmp->next;
        }
        return nullptr;
    }

    bool deleteNode(Node<T>* node){
        if (node == nullptr){
            return false;
        } else if (node == head){
            head = node->next;
            delete node;
            return true;
        } else {
            Node<T> *tmp = head;
            while (tmp){
                if (tmp->next == node){
                    tmp->next = node->next;
                    delete node;
                    return true;
                }
                tmp = tmp->next;
            }
        }
        return false;
    }

    void print(){
        Node<T> *tmp;
        tmp = head;
        while (tmp != nullptr){
            cout << tmp->data << "->";
            tmp = tmp->next;
        }
        cout << endl;
    }
};