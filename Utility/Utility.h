#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <string.h>
#include <algorithm>
#include "../DataStructures/Queue.h"
#include "../DataStructures/LinkedList.h"
using namespace std;

vector<int> extractIntegersFromBin(string s){

    char tmp;
    vector<int> nums;

    for (int i = 0; s[i]; i++ ){
        nums.push_back(s[i] - '0');
    }

    return nums;
}

vector<int> extractIntegers(string s){
    stringstream stream;
    stream << s;

    string tmp;
    int flag;
    vector<int> nums;

    while (!stream.eof()){
        stream >> tmp;
        if (stringstream(tmp) >> flag){
            nums.push_back(flag);
        }
        tmp = "";
    }
    return nums;
}

vector<string> split(string input, string del){
    int start = 0, end;
    int delLen = del.length();
    string token;

    // Queue<string> s((input.length() * 2)-1);
    vector<string> s;
    while ((end = input.find(del, start)) != string::npos){
        token = input.substr(start, end - start);
        start = end + delLen;
        s.push_back(token);
    }
    s.push_back(input.substr(start));
    return s;
}

vector<int> splitNum(string input){
    stringstream iss(input);
    int number;
    std::vector<int> myNumbers;
    while ( iss >> number )
        myNumbers.push_back( number );
    
    return myNumbers;
}

int strCmp(string a, string b){
    int i = 0;
    while (a[i] != '\0' && (a[i] == b[i])){
        i++;
    }
    return a[i] - b[i];
}

string readFile(string name){

    ifstream t(name);
    string text;

    stringstream buffer;
    buffer << t.rdbuf();
    text = buffer.str();
    // t.seekg(0, ios::end);
    // text.reserve(t.tellg());
    // t.seekg(0, ios::beg);

    // text.assign((istreambuf_iterator<char>(t)),
    //             istreambuf_iterator<char>());
    // string text((istreambuf_iterator<char>(t)),
    //     istreambuf_iterator<char>());

    return text;
}

void swap(string *a, string *b){
    string tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

void maxHeapify(string &obj, int size, int i){
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    while (left < size && strcmp(&obj[left], &obj[largest]) > 0){
        largest = left;
    }

    while (right < size && strcmp(&obj[right], &obj[largest]) > 0){
        largest = right;
    }

    if (largest != i){
        swap(obj[i], obj[largest]);
        maxHeapify(obj, size, largest);
    }
}

void heapSort(string &obj, int size){
    for (int i = size/2-1; i >= 0; i--){
        maxHeapify(obj, size, i);
    }

    for (int i = size-1; i > 0; i--){
        swap(obj[0], obj[i]);
        maxHeapify(obj, i, 0);
    }
}

int linearSearch(string input){
    int index = 0;

    for (int i = 0; i < input.length(); i++){
        if (input[i] == '$'){
            return i;
        }
    }
    return 0;
}

int getMax(vector<int> input){
    int max = input[0];
    for (int i = 0; i < input.size(); i++){
        if (max < input[i]){
            max = input[i];
        }
    }
    return max;
}

void addAtLast(Node<int>** head, Node<int>* nn){ 
    if (*head == NULL) { 
        *head = nn; 
        return; 
    } 
    Node<int>* temp = *head; 
    while (temp->next != NULL) 
        temp = temp->next; 
    temp->next = nn; 
} 

void* computeLShift(Node<int>** head, int index, 
                int* l_shift){ 
    l_shift[index] = (*head)->data; 
    (*head) = (*head)->next;
} 

Node<int>* getNode(int i) 
{ 
	Node<int>* nn = new Node<int>();
	nn->data = i; 
	nn->next = NULL; 
	return nn; 
}

int* invert(string sorted, string input, int* shift){
    Node<int>* arr[128] = {NULL};
    for (int i = 0; i < input.length(); i++){
        Node<int> *nn = getNode(i);
        addAtLast(&arr[input[i]], nn);
    }

    for (int i = 0; i < input.length(); i++){
        computeLShift(&arr[sorted[i]], i, shift);
    }

    return shift;
}

string remove(string input){
    string out;
    for (int i = 0; i < input.length();){
        if(input[i] >= 'A' && input[i] <= 'z' || input[i] == ' '){
            out += input[i];
            i++;
        } else {
            i++;
        }
    }
    return out;
}

double getFileSize(string content){
    return content.length() * 8;
}

stringstream toBinary(int n, int bitSize = 0) {
    vector<int> bin, bin2;
    int i = 0;
    while (n > 0) {
        bin.push_back(n % 2);
        n /= 2;
        i++;
    }

    while (bin.size() < bitSize) {
        bin.push_back(0);
    }

    reverse(bin.begin(), bin.end());
    stringstream s;
    for (int i = 0; i < bin.size(); i++) {
        s << bin[i];
    }

    return s;
}

int binaryToDecimal(string n){
    string num = n;
    int dec_value = 0;
 
    // Initializing base value to 1, i.e 2^0
    int base = 1;
 
    int len = num.length();
    for (int i = len - 1; i >= 0; i--) {
        if (num[i] == '1')
            dec_value += base;
        base = base * 2;
    }
 
    return dec_value;
}