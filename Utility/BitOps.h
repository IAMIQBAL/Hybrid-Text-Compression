#include <iostream>
#include <boost/dynamic_bitset.hpp>
#include <fstream>
#include <streambuf>
#include "Utility.h"
using namespace std;
using namespace boost;

template <typename T>
class BitOperations {
private:
    T data;
    int size;
    dynamic_bitset<unsigned char> Bits;
    string fName;
    size_t bitSize;

public:
    BitOperations(dynamic_bitset<unsigned char> b){
        Bits = b;
        Bits.reserve(bitSize);
        size = b.size();
    }

    BitOperations(dynamic_bitset<unsigned char> b, string fName){
        Bits = b;
        Bits.reserve(bitSize);
        this->fName = fName;
        size = b.size();
    }

    BitOperations(T data, string fName, int bitSize = 0){
        this->data = data;
        this->fName = fName;
        this->bitSize = bitSize;
    }

    BitOperations(int bitSize, string fName){
        this->bitSize = bitSize;
        this->fName = fName;
    }

    void writeToFile(){
        if (data != ""){
            vector<int> bitTemp = extractIntegersFromBin(data);
            for (int i = 0; i < bitTemp.size(); i++){
                Bits.push_back(bitTemp[i]);
            }
        }
        ofstream output(fName, ios::binary| ios::app);
        ostream_iterator<char> osit(output);
        // cout << "Before: " << Bits << endl;
        to_block_range(Bits, osit);
        output.close();
        cout << "File Successfully modified" << endl;
    }

    dynamic_bitset<unsigned char> readFromFile() {
        ifstream input(fName);
        stringstream strStream;
        strStream << input.rdbuf();
        T str = strStream.str();

        dynamic_bitset<unsigned char> b;
        size_t bitCount = (str.length()*8) / bitSize * bitSize;
        size_t bitsPerByte = 8;

        for (int i = 0; i < bitCount; i++) {
            size_t index = (i / bitsPerByte);
            size_t offset = (i % bitsPerByte);

            bool isSet = (str[index] & ( 1 << offset));
            b.push_back(isSet);
        }
        return b;
    }
};