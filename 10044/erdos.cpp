#include <unordered_map>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char **argv) {
    int scenarios, papers, names;
    unordered_map<string, int> m;
    string input;

    cin >> scenarios;

    for(int i = 0; i < scenarios; ++i) {
        cin >> papers >> names;
        cout << papers << " " << names << endl;
    }
}
