#include <iostream>
#include <chrono>
#include <string>
#include "BWT.h"
#include "RLE.h"
#include "matplotlibcpp.h"
using namespace std;
namespace plt = matplotlibcpp;

class Data {
private:
    string name;
    double time;
    double orgFileSize;
    double compRatio;
    string type;

public:
    Data(){};

    Data(string name, double time, double orgFileSize, double compRatio, string type){
        this->name = name;
        this->time = time;
        this->orgFileSize = orgFileSize;
        this->compRatio = compRatio;
        this->type = type;
    }

    void setName(string name){
        this->name = name;
    }

    void setTime(double time){
        this->time = time;
    }

    void setOrgFileSize(double orgFileSize){
        this->orgFileSize = orgFileSize;
    }

    void setCompRatio(double compRatio){
        this->compRatio = compRatio;
    }

    void setType(string type){
        this->type = type;
    }

    string getName(){
        return name;
    }

    double getTime(){
        return time;
    }

    double getOrgFileSize(){
        return orgFileSize;
    }

    double getCompRatio(){
        return compRatio;
    }

    string getType(){
        return type;
    }
};

class Test {
private:
    Data d;
    vector<double> x;
    vector<double> y;
    vector<double> z;

    int size;
public:
    Test (int s){
        size = s;
    }

    void run(string *files, int alg){

        Queue<string> *f = new Queue<string>(size);
        for (int i = 0; i < size; i++){
            f->enqueue(files[i]);
        }

        // Test for LZW
        for (int i = 0; i < size; ++i){
            string t = remove(readFile(f->dequeue()));
            t += "$";
            cout << "Loaded" << endl;
            d.setType(files[i].substr(files[i].length() - 4));
            d.setOrgFileSize(getFileSize(t));
            string c;
            auto start = chrono::high_resolution_clock::now();  
            if (alg == 0){
                d.setName("LZW");
                LZW<string> lzw(t, t.length());
                c = lzw.encode();
            } else if (alg == 1){
                d.setName("RLE + LZW");
                RLE<string> rle(t, t.length());
                c = rle.Encode();
                LZW<string> lzw(c, c.length());
                c = lzw.encode();
            } else if (alg == 2){
                string tmp;
                d.setName("BWT + RLE + LZW");
                BWT bwt(t, t.length());
                c = bwt.bwt();
                RLE<string> rle(c, c.length());
                tmp = rle.Encode();
                LZW<string> lzw(tmp, tmp.length());
                c = lzw.encode();
            }
            auto end = chrono::high_resolution_clock::now();
            
            vector<int> lzwNums = splitNum(c);
            cout << "LZW NUMS: " << lzwNums.size() << endl;
            int max = getMax(lzwNums);
            cout << "Max: " << max << endl;
            stringstream ss = toBinary(max);
            string bin = ss.str().c_str();
            for (int i = 0; i < bin.size(); i++){
                cout << bin[i];
            }
            cout << endl;

            auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
            d.setCompRatio(100 - (((lzwNums.size() * bin.size()) / getFileSize(t)) * 100));
            d.setTime(duration.count());

            x.push_back(d.getOrgFileSize()/ 8192);
            y.push_back(d.getCompRatio());
            z.push_back(d.getTime());

            if (d.getType() == "json"){
                json.push_back(d.getCompRatio());
                jsonTime.push_back(d.getTime());
            } else if (d.getType() == ".txt"){
                txt.push_back(d.getCompRatio());
                txtTime.push_back(d.getTime());
            } else {
                xml.push_back(d.getCompRatio());
                xmlTime.push_back(d.getTime());
            }
            getData();
            cout << "--------------------------" << endl;
        }

        // plt::xlabel("File Size");
        // plt::ylabel("Compression %");
        // plt::title(d.getName());
        // // plt::bar(y);
        // // plt::xticks(z, x);
        // plt::scatter(x, y, 300);
        // plt::show();
    }

    vector<double> getX(){
        return x;
    }

    vector<double> getY(){
        return y;
    }

    vector<double> getZ(){
        return z;
    }

    void plot(){
        plt::xlabel("File Size");
        plt::ylabel("Compression %");
        plt::title(d.getName());
        plt::scatter(x, y, 300);
        plt::show();
    }

    void getData(){
        cout << "Algorithm: " << d.getName() << endl;
        cout << "File Type: " << d.getType() << endl;
        cout << "Original File Size: " << d.getOrgFileSize() << endl;
        cout << "Time: " << d.getTime() << endl;
        cout << "Compression Ratio: " << d.getCompRatio() << endl;
    }

    vector<double> txt;
    vector<double> json;
    vector<double> xml;
    vector<double> txtTime;
    vector<double> jsonTime;
    vector<double> xmlTime;
};

int main(){

    int size = 12;
    string *files = new string[size];
    files[0] = "../Data/agatha.txt";
    files[1] = "../Data/AliBaba.txt";
    files[2] = ("../Data/sherlock.txt");
    files[3] = ("../Data/sample_log_file.txt");
    files[4] = ("../Data/Wolvesand7Kids.txt");
    files[5] = ("../Data/all2.json");
    files[6] = ("../Data/jsonFile.json");
    files[7] = ("../Data/NY.json");
    files[8] = ("../Data/auction.xml");
    files[9] = ("../Data/xmlFile.xml");
    files[10] = ("../Data/cp.html");
    files[11] = ("../Data/datasets.xml");

    // Test for LZW = 0

    // Test for RLE + LZW = 1

    // Test for BWT + RLE + LZW = 2

    // Test for BWT + RLE + LZW + DELTA = 3

    Test t(size);
    t.run(files, 0);
    vector<double> z1 = t.getZ();
    vector<double> y1 = t.getY();

    map<string, string> m, n, o;
    m.insert({"color", "red"});
    n.insert({"color", "green"});
    o.insert({"color", "blue"});
    plt::xlabel("Time");
    plt::ylabel("Compression %");
    plt::title("LZW");
    plt::scatter(t.jsonTime, t.json, 75, m);
    plt::scatter(t.txtTime, t.txt, 75, n);
    plt::scatter(t.xmlTime, t.xml, 75, o);
    plt::show();

    Test u(size);
    u.run(files, 1);
    vector<double> z2 = u.getZ();
    vector<double> y2 = u.getY();
    plt::xlabel("Time");
    plt::ylabel("Compression %");
    plt::title("RLE + LZW");
    plt::scatter(u.jsonTime, u.json, 75, m);
    plt::scatter(u.txtTime, u.txt, 75, n);
    plt::scatter(u.xmlTime, u.xml, 75, o);
    plt::show();

    Test v(size);
    v.run(files, 2);
    vector<double> z3 = v.getZ();
    vector<double> y3 = v.getY();
    plt::xlabel("Time");
    plt::ylabel("Compression %");
    plt::title("BWT + RLE + LZW");
    plt::scatter(v.jsonTime, v.json, 75, m);
    plt::scatter(v.txtTime, v.txt, 75, n);
    plt::scatter(v.xmlTime, v.xml, 75, o);
    plt::show();

    plt::xlabel("Time");
    plt::ylabel("Compression %");
    plt::title("Tests");
    plt::scatter(z1, y1, 75, m);
    plt::scatter(z2, y2, 75, n);
    plt::scatter(z3, y3, 75, o);

    plt::show();


}