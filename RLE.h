#include<iostream>
#include <string.h>
using namespace std;

template<typename T>
class RLE {
private:
    T data;
    int size;

public:
    RLE(T data, int size){
        this->data = data;
        this->size = size;
    }

    T Encode(){
        T output;
        
        for (int i = 0; i < size; i++){
            int count = 1;
            // int s = i;
            while(data[i] == data[i + 1]){
                count++;
                i++;
            }
            
            if (count <= 1){
                output += data[i];
            } else {
                output += to_string(count);
                output += data[i];
            }
        }
        return output;
    }

    T decode(){
        string output;

        int i = 0;
        int dup;
        while (i < size){
            while (isalpha(data[i]) || data[i] == ' ' || data[i] == '$'){
                output.push_back(data[i++]);
            }

            dup = 0;
            while (isdigit(data[i])){
                dup = 10 * dup + (data[i++] - '0');
            }

            auto t = data[i++];
            while(dup--){
                output.push_back(t);
            }
        }

        return output;
    }
};