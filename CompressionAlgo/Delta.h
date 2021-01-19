#include <iostream>
#include "../DataStructures/Queue.h"
using namespace std;

template <typename T>
class Delta {
private:

    T* data;
    int size;
    T* output;

public:
    Delta(T *d, int size){
        data = d;
        this->size = size;
    }

    T* encode(){
        int last = 0;
        output = new T[size];
        for (int i = 0; i < size; i++){
            int current = data[i];
            output[i] = current - last;
            last = current;
        }
        return output;
    }

    T* decode(){
        int last = 0;
        output = new T[size];
        for (int i = 0; i < size; i++){
            int delta = data[i];
            output[i] = delta + last;
            last = output[i];
        }
        return output;
    }

    void printData(){
        for (int i = 0; i < size; i++){
            cout << (T)data[i] << " ";
        }
        cout << endl;
    }

    void printOutput(){
        for (int i = 0; i < size; i++){
            cout << (T)output[i] << " ";
        }
        cout << endl;
    }
};