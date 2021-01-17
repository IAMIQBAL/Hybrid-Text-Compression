#include <iostream>
using namespace std;

template <typename T>
class Stack {
private:
    int top, size;
    T* myStack;

public:
    Stack(int size){
        this->size = size;
        myStack = new T[size];
        top = -1;
    }

    bool push(T item){
        if (isFull()){
            cout << "Stack Overflow" << endl;
            return false;
        } else {
            top++;
            myStack[top] = item;
            return true;
        }
    }

    T pop(){
        if (isEmpty()){
            cout << "Stack Underflow" << endl;
            // return 0;
        } else {
            T item = myStack[top];
            top--;
            return item;
        }
    }

    bool isFull(){
        return top >= (size-1);
    }

    bool isEmpty(){
        return (top < 0);
    }

    T getTop(){
        return myStack[top];
    }

    int getSize(){
        return size;
    }
};