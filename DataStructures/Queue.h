#include <iostream>
using namespace std;

template <typename T>
class Queue {
private:
    T *data;
    int front;
    int rear;
    int capacity;
    int count;

public:
    Queue(int capacity){
        data = new T[capacity];
        front = 0;
        rear = -1;
        count = 0;
        this->capacity = capacity;
    }

    void enqueue(T item){
        if (isFull()){
            cout << "Queue is Full" << endl;
        } else {
            rear = (rear + 1) % capacity;
            data[rear] = item;
            count++;
        }
    }

    T dequeue(){
        T d;
        if (isEmpty()){
            cout << "Queue is Empty" << endl;
            return d;
        } else {
            d = data[front];
            front = (front + 1) % capacity;
            count--;
            return d;
        }
    }

    bool isEmpty(){
        return (count == 0);
    }

    bool isFull(){
        return (count == capacity);
    }

    T peek(){
        if (isEmpty()){
            cout << "Queue is Empty" << endl;
        } else {
            return data[front];
        }
    }

    int getSize(){
        return capacity;
    }

    // void operator=(const Queue & obj){
    //     for (int i = 0; i < capacity; i++){
    //         data[i] = obj[i];
    //     }
    // }

    ~Queue(){
        delete[] data;
    }
};