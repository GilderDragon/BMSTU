#include <iostream>
#include <string>
#include <vector>

using namespace std;


void csort(string* from, string* to) {

    vector<string> splited = {""};

    for (char i : *from) {
        if (i != ' ') {
            splited.back() += i;
        } else if (!splited.back().empty()){
            splited.emplace_back("");
        }
    }

    int n = splited.size();

    int max_len = 0;
    for (string i : splited) {
        if (i.length() > max_len) max_len = i.length();
    }

    vector<int> length_of_words(max_len + 1, 0);
    for (string i : splited) {
        length_of_words[i.length()]++;
    }

    for (int i = 1; i <= max_len; i++) {
        length_of_words[i] += length_of_words[i - 1];
    }

    vector<string> sorted_by_len_words(n);
    for (int i = n - 1; i >= 0; i--) {
        int len = splited[i].length();
        sorted_by_len_words[length_of_words[len] - 1] = splited[i];
        length_of_words[len]--;
    }

    string result;
    for (int i = 0; i < splited.size(); i++) {
        if (i > 0) result += " ";
        result += sorted_by_len_words[i];
    }

    *to = result;
}


int main() {
    string from = "tgrt      se          sdd  d";
    string to;

    csort(&from, &to);

    cout << to;
}
