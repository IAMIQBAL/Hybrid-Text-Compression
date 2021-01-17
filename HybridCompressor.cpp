#include <iostream>
#include "BWT.h"
#include "RLE.h"
using namespace std;

int main(){
    string input = remove(readFile("../Data/AliBaba.txt"));
    input += "$";
    int len = input.length();

    BWT bE(input, len);
    string bwtEncoded = bE.bwt();
    // cout << "BWT: " << bwtEncoded << endl;
    
    RLE<string> rleE(bwtEncoded, bwtEncoded.length());
    string rleEncoded = rleE.Encode();
    // cout << "RLE: " << rleEncoded << endl;

    LZW<string> lzwE(rleEncoded, rleEncoded.length());
    string lzwEncoded = lzwE.encode();
    cout << "LZW: " << lzwEncoded << endl;
    
    vector<int> lzwNums = splitNum(lzwEncoded);
    int max = getMax(lzwNums);
    string m = toBinary(max).str().c_str();
    string ss;
    stringstream sd;
    for (int i = 0; i < lzwNums.size(); i++){
        sd = toBinary(lzwNums[i], m.length());
        ss += sd.str().c_str();
    }
    BitOperations<string> b(ss, "bits.bin", m.length());
    b.writeToFile();
    cout << "Comp: " << ss.size() << endl;

    int x = m.length() * lzwNums.size();
    cout << "MAX: " << m << " | " << m.length() << endl;

    cout << "----Benchmark----" << endl;
    cout << "Original Length: " << input.length()*8 << endl;
    cout << "BWT Length: " << bwtEncoded.length() << endl;
    cout << "RLE Length: " << rleEncoded.length() << endl;
    cout << "LZW Numbers: " << lzwNums.size() << endl;
    cout << "LZW Max: " << getMax(lzwNums) << endl;

    string dec;
    dynamic_bitset<unsigned char> bits;
    BitOperations<string> bdec(m.length(), "bits.bin");
    bits = bdec.readFromFile();
    cout << "OUTPUT BIT SIZE: " << bits.size() << endl;
    int sp = 0;
    to_string(bits, dec);
    reverse(dec.begin(), dec.end());

    // cout << "TO DEC: " << stoul("10111011011011", 0, 2) << endl;

    // cout << "Compressed: " << dec << endl;
    int spl = 1;
    vector<int> recovered;
    string holder;
    for (int i = 0; i < dec.length(); i++){
        holder += dec[i];
        spl++;
        if (spl == m.length()+1){
            // cout << holder << endl;
            recovered.push_back(binaryToDecimal(holder));
            holder = "";
            spl = 1;
        }
    }

    // for (int i = 0; i < recovered.size(); i++){
    //     cout << recovered[i] << " ";
    // }
    // cout << endl;

    stringstream lzwDD;
    // string lzwDD;
    cout << "Recovered: ";
    for (int i = 0; i < recovered.size(); i++){
        // cout << recovered[i] << " ";
        lzwDD << recovered[i] << " ";
        // lzwDD += recovered[i];
        // lzwDD += " ";
    }

    string lzwDec = lzwDD.str().c_str();
    // cout << lzwDD << endl;

    LZW<string> lzwD(lzwDec, lzwDec.length());
    string lzwDecode = lzwD.decode();
    cout << lzwDecode << endl;

    RLE<string> rleD(lzwDecode, lzwDecode.length());
    string rleDecode = rleD.decode();
    // cout << rleDecode << endl;

    BWT bD(rleDecode, rleDecode.length());
    cout << bD.inverse() << endl;
}

