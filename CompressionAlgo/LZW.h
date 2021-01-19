#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include "../Dictionary.h"
using namespace std;

#define LOG(X) cout << X << endl

template <typename T>
class LZW {
private:

    LinkedList<Dictionary> dict;
    T input, result;
    int len, index, seen;

public:
    LZW (T input, int len = 0){
        this->input = input;
        this->len = len;
        index = 128;
    }

    T encode(){
        Dictionary d(32, " ");
        dict.insertHead(d);

        for (int i = 33; i < index; i++){
            string s;
            s = i;
            d.setIndex(i);
            d.setData(s);
            dict.insertNext(d);
        }
        
        for (int i = 0; i < len; i++){
            Node<Dictionary> *finder;
            string search;
            search = input[i];
            while (i != len){
                d.setData(search);
                finder = dict.find(d);
                if (finder != nullptr){
                    i++;
                    search += input[i];
                    seen = finder->data.index;
                    if (i == len){
                        result += to_string(seen) + " ";
                        i--;
                        break;
                    }
                } else {
                    d.setIndex(index);
                    d.setData(search);
                    dict.insertNext(d);
                    index++;
                    result += to_string(seen) + " ";
                    i--;
                    break;
                }
            }
        }
        return result;
    }

    T decode(){
        Dictionary d(32, " ");
        dict.insertHead(d);

        for (int i = 33; i < index; i++){
            string s;
            s = i;
            d.setIndex(i);
            d.setData(s);
            dict.insertNext(d);
        }

        vector<int> output = splitNum(input);

        for (int i = 0; i < output.size(); i++){
            Node<Dictionary> *finder;
            int search;
            search = output[i];
            d.setIndex(search);
            finder = dict.find(d, search);

            Dictionary cur, prev;
            string data;
            if (finder != nullptr){
                d.setIndex(output[i]);
                cur = dict.find(d, d.index)->data.data;
            }
            if (i != 0){
                d.setIndex(output[i-1]);
                prev = dict.find(d, d.index)->data.data;
            } else {
                prev.data = cur.data;
            }

            int show = 0;
            if (finder != nullptr){
                result += finder->data.data;
                if (i != 0){
                    data = prev.data + cur.data[0];
                    if (show != 1){
                        d.setIndex(index);
                        d.setData(data);
                        dict.insertNext(d);
                        index++;
                    }
                }
                show = 0;
            } else {
                data = prev.data + prev.data[0];
                d.setData(data);
                d.setIndex(index);
                dict.insertNext(d);
                index++;
                show = 1;
                result += data;
            }
        }
        return result;
    }
};