#include <iostream>
#include <map>
using namespace std;

class Nodes {
public:
    char c;
    int f;
    Nodes *left;
    Nodes *right;
    bool operator<(const Nodes &other) const {
        return f < other.f;
    }
};

template <typename T>
class MinHeap {
private:
    T *arr;
    int used;
    int const size;
    static std::pair<int, int> children(int parent) {
        return {2 * parent + 1, 2 * parent + 2};
    }
    static int parent(int child) {
        return (child - 1) / 2;
    }
    int minChild(int i) {
        int j = children(i).first, k = children(i).second;
        return k == used || arr[j] < arr[k] ? j : k;
    }

public:
    MinHeap(int size) : arr(new T[size]), used(0), size(size) {}
    void push(T const &data) {
        arr[used++] = data;
        for (int cur = used - 1; cur != 0 && arr[cur] < arr[parent(cur)];
             cur = parent(cur)) {
            std::swap(arr[cur], arr[parent(cur)]);
        }
    }

    void pop() {
        arr[0] = arr[--used];
        for (int i = 0;
            children(i).first < used && arr[minChild(i)] < arr[i];) {
            int m = minChild(i);
            swap(arr[m], arr[i]);
            i = m;
        }
    }

    T const &top() const {
        return arr[0];
    }

    bool empty() const {
        return used == 0;
    }

    int count() const {
        return used;
    }

    ~MinHeap() {
        delete[] arr;
    }
};

class HuffmanCoding {
private:
    string str;
    string copy;
    string encoded;

    map<char, string>encode;
    int current;

    MinHeap<Nodes> *minheap;

    int freq[52];
    int heapsize;
    Nodes *root;
    int codes[100];
    int outLen;

public:
    HuffmanCoding(string str) {
        encoded="";
        heapsize = 0;
        current = 0;
        for (int i = 0; i < 52; i++) {
            freq[i] = 0;
        }
        this->str = str;
    }

    bool sizeNotOne() {
        if (current > 1) {
            return true;
        } else {
            return false;
        }
    }

    void removeduplicate() { // this function also counts frequnecy and store it in freq[]
        int findex = 0;
        copy = str;
        // cout << copy;
        int len = str.length();
        int index = 0;
        for (int i = 0; i < len; i++) {
            if (str[i] != '*') {
                int j;

                for (j = i + 1; j < len; j++) {
                    if (str[i] == str[j]) {
                        freq[heapsize]++;
                        str[j] = '*';
                    }
                }
                heapsize = heapsize + 1;
            }
        }
        
        for (int x = 0; x < heapsize; x++) {
            freq[x]++;
            
        }
    }

    void input() {
        int freqIndex = 0;
        removeduplicate();
        int len = str.length();
        minheapAllocation(len + 1);
        for (int i = 0; i < len; i++) {
            if (str[i] != '*') {
                Nodes *t = new Nodes;
                t->left = NULL;
                t->right = NULL;
                t->c = str[i];
                t->f = freq[freqIndex++];

                minheapInsertion(t);
            }
        }
        hTreeCreation();
    }

    void minheapAllocation(int sizeofheap) { // allocating 5 spaces for nodes in array
        minheap = new MinHeap<Nodes>(sizeofheap);
    }

    void minheapInsertion(Nodes *temp) {
        minheap->push(*temp);
    }

    Nodes *extractMinheap() { // extracting nodes and reducing the size of
                             // minheap array. size is yet to be reduced
        Nodes *t = new Nodes(minheap->top());
        minheap->pop();
        return t;
    }

    void hTreeCreation() {
        Nodes *l;
        Nodes *r;
        Nodes *top;
        while (minheap->count() > 1) {
            l = extractMinheap();
            r = extractMinheap();

            top = new Nodes;
            top->c = '$';
            top->f = l->f + r->f;
            top->left = l;
            top->right = r;
            minheapInsertion(top);
        }

        root = extractMinheap();
        cout << root->f;
    }

    void callPrint() {
        Nodes *pri = root;
        printHuffman(pri, 0);
    }

    void printHuffman(Nodes *pri, int index) {
        if (pri->left) {
            codes[index] = 0;
            printHuffman(pri->left, index + 1);
        }

        if (pri->right) {
            codes[index] = 1;
            printHuffman(pri->right, index + 1);
        }

        if (pri->right == NULL && pri->left == NULL) {
            cout << "\n" << pri->c << "     ";
            for (int i = 0; i < index; i++) {
                cout << codes[i];
            }
        }
    }

    void display() {
        Nodes *p = NULL;
        cout << "\nElements in the array :\n";

        for (int i = 1; i <= current; i++) // current index if filled
        {
            // cout << minheap[i]->c << "   " << minheap[i]->f << "\n";
        }
        cout << "\nElements extracted fromthe array:\n";
        int y = current;
        for (int x = 1; x <= y; x++) {
            p = extractMinheap();
            cout << p->c << "     " << p->f << "\n";
        }
    }
    
    string codeStorage(){
       
        Nodes* temp=root;
      
        storeCodes(temp,"");
        
        for (auto i: copy) {
            encoded += encode[i];
        }
        return encoded;
    }

    int getOutputLength(){
        outLen = encoded.length();
        return outLen;
    }
    
    void storeCodes(Nodes* root,string ser) { 
        if (root==NULL) 
            return; 
        if (root->c != '$') 
            encode[root->c]=ser; 
        storeCodes(root->left,ser + "0" ); 
        storeCodes(root->right,ser + "1"); 
    }

    string decode_file() 
    { 
        string ans = ""; 
        Nodes* curr = root; 
        for (int i=0;i<encoded.size();i++) { 
            if (encoded[i] == '0') 
            curr = curr->left; 
            else
            curr = curr->right; 
    
            // reached leaf node 
            if (curr->left==NULL and curr->right==NULL) 
            { 
                ans += curr->c; 
                curr = root; 
            } 
        }
        return ans; 
    }

    string run(int mode){
        input();
        callPrint();
        string enc = codeStorage();
        if (mode == 0){
            cout << decode_file() << endl;
        }
        
        return enc;
    }
};