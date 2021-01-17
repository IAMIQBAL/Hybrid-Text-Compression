#include <iostream>
#include <string>
#include "Utility/BitOps.h"
using namespace std;

class Dictionary {
public:
    int index;
    string data;
public:

    Dictionary(int index = 0, string data = ""){
        this->index = index;
        this->data = data;
    }

    Dictionary(string data){
        this->data = data;
    }

    void setIndex(int index){
        this->index = index;
    }

    void setData(string data){
        this->data = data;
    }

    void sort(Dictionary *obj, int size);
    void maxHeapify(Dictionary *obj, int size, int i);
    void heapSort(Dictionary *obj, int size);
    int Partition(Dictionary *obj, int start, int end);
    void quickSort(Dictionary *obj, int size, int start, int end);

    void operator=(const Dictionary & obj){ index = obj.index; data = obj.data; }

    void print(){
        cout << index << "-" << data << endl;
    }

    friend bool operator== (const Dictionary &d1, const Dictionary &d2);
    friend bool operator!= (const Dictionary &d1, const Dictionary &d2);
    friend bool operator== (const Dictionary &d1, int d2);

};

bool operator== (const Dictionary &d1, const Dictionary &d2){
    return (d1.data.compare(d2.data) == 0);
}

bool operator== (const Dictionary &d1, int d2){
    return (d1.index == d2);
}

bool operator!= (const Dictionary &d1, const Dictionary &d2){
    return !(d1 == d2);
}


void Dictionary::sort(Dictionary *obj, int size){
    Dictionary tmp;
    for (int i = 0; i < size; i++){
        for (int j = size -1; j > i; j--){
            if (strCmp(obj[j].data, obj[j-1].data) < 0){
                tmp = obj[j];
                obj[j] = obj[j-1];
                obj[j-1] = tmp;
            }
        }
    }
}

void Dictionary::maxHeapify(Dictionary *obj, int size, int i){
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    Dictionary tmp;

    while (left < size && strCmp(obj[left].data, obj[largest].data) > 0){
        largest = left;
    }

    while (right < size && strCmp(obj[right].data, obj[largest].data) > 0){
        largest = right;
    }

    if (largest != i){
        tmp = obj[i];
        obj[i] = obj[largest];
        obj[largest] = tmp;
        maxHeapify(obj, size, largest);
    }
}

void Dictionary::heapSort(Dictionary *obj, int size){
    Dictionary tmp;
    for (int i = size/2-1; i >= 0; i--){
        maxHeapify(obj, size, i);
    }

    for (int i = size-1; i > 0; i--){
        // Swap
        tmp = obj[0];
        obj[0] = obj[i];
        obj[i] = tmp;
        maxHeapify(obj, i, 0);
    }
}

int Dictionary::Partition(Dictionary *obj, int start, int end){
    int l = start;
    Dictionary pivot = obj[start];
    Dictionary tmp;
    while (start < end){
        while (strCmp(obj[start].data, pivot.data) <= 0){
            start++;
        }

        while (strCmp(obj[end].data, pivot.data) > 0){
            end--;
        }

        if (start < end){
            tmp = obj[start];
            obj[start] = obj[end];
            obj[end] = tmp;
        }
    }
    tmp = obj[l];
    obj[l] = obj[end];
    obj[end] = tmp;
    return end;
}

void Dictionary::quickSort(Dictionary *obj, int size, int start, int end){
    if (start < end){
        int loc = Partition(obj, start, end);
        quickSort(obj, size, start, loc-1);
        quickSort(obj, size, loc+1, end);
    }
}