#include <iostream>
#include <vector>
#include <string.h>
#include "LZW.h"
using namespace std;

struct node {
    int data; 
    struct node* next; 
}; 

class Pair {
public:
    Pair(){};

    Pair(const string& data, size_t index): inData(data), ind(index){
    }

    string inData = "";
    size_t ind = 0;

    void swap(Pair *a, Pair *b){
        Pair tmp;
        tmp = *a;
        *a = *b;
        *b = tmp;
    }

    void maxHeapify(vector<Pair> &obj, int size, int i){
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        while (left < size && strcmp(obj[left].inData.c_str(), obj[largest].inData.c_str()) > 0){
            largest = left;
        }

        while (right < size && strcmp(obj[right].inData.c_str(), obj[largest].inData.c_str()) > 0){
            largest = right;
        }

        if (largest != i){
            swap(&obj[i], &obj[largest]);
            maxHeapify(obj, size, largest);
        }
    }

    void heapSort(vector<Pair> &obj, int size){
        for (int i = size/2-1; i >= 0; i--){
            maxHeapify(obj, size, i);
        }

        for (int i = size-1; i > 0; i--){
            swap(&obj[0], &obj[i]);
            maxHeapify(obj, i, 0);
        }
    }
};

class BWT {
private:

    string input;
    int size;

public:

    BWT(string input, int size){
        this->input = input;
        this->size = size;
    }

    string bwt(){
        Pair *a = new Pair;
        
        vector<Pair> dictionary;
        for (size_t in = 0; in < input.length(); ++in){
            dictionary.emplace_back(input.substr(in, input.size() - in), in);
        }

        LOG("Sorting...");

        // Heap sort performs 90% better than normal sort        
        // Heap sort performs well on large texts
        a->heapSort(dictionary, dictionary.size());
        delete a;

        LOG("Generating BWT...");

        // Quick sort shows std::bad_alloc for large texts
        // because of space complexity of O(n) maybe
        // a.quickSort(suff, size, 0, size-1);
        
        string bwt;
        for (int i = 0; i < size; i++){
            int x = dictionary[i].ind - 1;
            if (x < 0){
                x += size;
            }
            bwt += input[x];
        }
        return bwt;
    }

    string inverse(){
        string sorted = input;
        string inverseBWT;
        int* shift = new int[size];

        int pointer = linearSearch(input);
        cout << "Pointer at: " << pointer << endl;

        cout << "Sorting..." << endl;
        heapSort(sorted, sorted.length());

        LOG("Rotating...");

        shift = invert(sorted, input, shift);

        for (int i = 0; i < size; i++){
            pointer = shift[pointer];
            inverseBWT += input[pointer];
        }
        return inverseBWT;
    }

    ~BWT(){};
};