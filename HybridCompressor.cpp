#include <iostream>
#include <vector>
#include "CompressionAlgo/BWT.h"
#include "CompressionAlgo/RLE.h"
#include "CompressionAlgo/Huffman.h"
using namespace std;

void printAlgos();

int main(){

    // Compress = 'C'

    // Decompress = 'D'

    // Huffman = 'H'

    char choice;
    string fileName;
    cout << "Press C for Compressing a file and D for Decompressing Hybrid LZW or H for Huffman: ";

    cin >> choice;
    cin.ignore();

    cout << "Enter file name: ";
    getline(cin, fileName);

    // LZW = 0

    // RLE + LZW = 1

    // BWT + RLE + LZW = 2
    
    if (choice == 'C' || choice == 'c'){
        printAlgos();
        int algo = 0;
        cin >> algo;
        cin.clear();

        string encoded;
        string input = readFile(fileName);
        int length = input.length();

        if (algo == 0){

            LZW<string> lzwE(input, length);
            encoded = lzwE.encode();
        } else if (algo == 1){

            RLE<string> rleE(input, length);
            string rleEncoded = rleE.Encode();

            LZW<string> lzwE(rleEncoded, rleEncoded.length());
            encoded = lzwE.encode();
        } else if (algo == 2){

            input = remove(input);
            input += "$";

            BWT bE(input, input.length());
            string bwtEncoded = bE.bwt();

            RLE<string> rleE(bwtEncoded, bwtEncoded.length());
            string rleEncoded = rleE.Encode();

            LZW<string> lzwE(rleEncoded, rleEncoded.length());
            encoded = lzwE.encode();

        } else {
            cout << "Something went wrong" << endl;
        }

        vector<int> lzwNums = splitNum(encoded);
        int max = getMax(lzwNums);
        string m = toBinary(max).str().c_str();
        string ss;
        stringstream sd;
        for (int i = 0; i < lzwNums.size(); i++){
            sd = toBinary(lzwNums[i], m.length());
            ss += sd.str().c_str();
        }
        BitOperations<string> b(ss, "Compressed.bin", m.length());
        b.writeToFile();

        writeFile(max, "max.txt");

    } else if (choice == 'D' || choice == 'd'){
        printAlgos();
        int algo, max = 0;
        cin >> algo;
        cin.clear();

        max = read("max.txt", 0);
        cout << "Max: " << max << endl;

        string m = toBinary(max).str().c_str();

        string decoded;
        dynamic_bitset<unsigned char> bits;
        BitOperations<string> bdec(m.length(), fileName);
        bits = bdec.readFromFile();
        
        to_string(bits, decoded);
        reverse(decoded.begin(), decoded.end());

        int spl = 1;
        vector<int> recovered;
        string holder;
        for (int i = 0; i < decoded.length(); i++){
            holder += decoded[i];
            spl++;
            if (spl == m.length()+1){
                // cout << holder << endl;
                recovered.push_back(binaryToDecimal(holder));
                holder = "";
                spl = 1;
            }
        }

        stringstream lzwDD;
        cout << "Recovered: ";
        for (int i = 0; i < recovered.size(); i++){
            lzwDD << recovered[i] << " ";
        }

        string lzwDec = lzwDD.str().c_str();

        if (algo == 0){
            LZW<string> lzwD(lzwDec, lzwDec.length());
            string lzwDecode = lzwD.decode();
            cout << lzwDecode << endl;

        } else if (algo == 1){
            LZW<string> lzwD(lzwDec, lzwDec.length());
            string lzwDecode = lzwD.decode();

            RLE<string> rleD(lzwDecode, lzwDecode.length());
            string rleDecode = rleD.decode();
            cout << rleDecode << endl;
        } else if (algo == 2){
            LZW<string> lzwD(lzwDec, lzwDec.length());
            string lzwDecode = lzwD.decode();

            RLE<string> rleD(lzwDecode, lzwDecode.length());
            string rleDecode = rleD.decode();
            
            BWT bD(rleDecode, rleDecode.length());
            cout << bD.inverse() << endl;
        } else {
            cout << "Something went wrong" << endl;
        }
    } else if (choice == 'H' || choice == 'h'){
        string data = remove(readFile(fileName));

        HuffmanCoding H(data);
        string encoded = H.run(0);
        BitOperations<string> bits(encoded, "Compressed.bin");
        bits.writeToFile();
    } else {
        cout << "Something went wrong" << endl;
    }
}

void printAlgos(){
    cout << "\nPress\n";
    cout << "LZW = 0" << endl;
    cout << "RLE + LZW = 1" << endl;
    cout << "BWT + RLE + LZW = 2" << endl;
}