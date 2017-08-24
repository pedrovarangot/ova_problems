#include <unordered_map>
#include <climits>
#include <map>
#include <set>
#include <iostream>
#include <string>
#include <queue>

using namespace std;

void do_erdos(unordered_map<string, int> &m, map<string, set<string> > &G, int current_erdos, set<string> current_authors);

int main(int argc, char **argv) {
    int scenarios, papers, names;
    unordered_map<string, int> m;
    map<string, set<string> > G;
    string input;

    cin >> scenarios;

    for(int i = 0; i < scenarios; ++i) {
        cin >> papers >> names;
        m.erase(m.begin(), m.end());
        G.erase(G.begin(), G.end());
        
        for(int j = 0; j <= papers; j++) {
            getline(cin, input);
            input = input.substr(0, input.find(": "));
            set<string> authors;
            
            size_t comma;
            while((comma = input.find("., ")) != string::npos) {
                authors.insert(input.substr(0, comma + 1));
                m[input.substr(0, comma + 1)] = INT_MAX;
                input = input.substr(comma + 3, input.size());
            }
            authors.insert(input);
            m[input] = INT_MAX;

            for(auto it = authors.begin(); it != authors.end(); it++) {
                G[*it].insert(authors.begin(), authors.end());
            }
        }

        cout << "Scenario " << i + 1 << endl;

        m["Erdos, P."] = 0;
        if(names > 0) do_erdos(m, G, 1, G["Erdos, P."]);
        for(int j = 0; j < names; j++) {
            getline(cin, input);
            if(m.find(input) != m.end() && m[input] < INT_MAX && m[input] >= 0) {
                cout << input << " " << m[input] << endl;
            } else {
                cout << input << " infinity" << endl;
            }
        }
    }
}

void do_erdos(unordered_map<string, int> &m, map<string, set<string> > &G, int current_erdos, set<string> current_authors)
{
    set<string> next_authors;

    for(auto it = current_authors.begin(); it != current_authors.end(); ++it) {
        if(m[*it] > current_erdos) m[*it] = current_erdos;
        for(auto jt = G[*it].begin(); jt != G[*it].end(); ++jt) {
            if(m[*jt] > current_erdos) next_authors.insert(*jt);
        }
    }

    if(!current_authors.empty()) do_erdos(m, G, current_erdos + 1, next_authors);

    return;
}
