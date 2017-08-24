#include <iostream>
#include <list>
#include <vector>
#include <set>
#include <queue>

using namespace std;

int main()
{
    int edges, lines;
    int n1, n2;
    bool paint_black, bicolorable;


    while(true) {
        cin >> edges;
        if(edges == 0) return 0;
        vector<list<int> > G(edges);
        set<int> reds, blacks;
        queue<int> q;

        cin >> lines;
        for(int i = 0; i < lines; ++i) {
            cin >> n1 >> n2;
            G[n1].push_back(n2);
            G[n2].push_back(n1);
        }

        bicolorable = true;
        reds.insert(0);
        q.push(0);
        while(!q.empty() and bicolorable) {
            auto node = q.front();
            q.pop();
            paint_black = reds.find(node) != reds.end();
            for(auto it = G[node].begin(); it != G[node].end(); ++it) {
                if(paint_black) {
                    if(reds.find(*it) != reds.end()) {
                        cout << "NOT BICOLORABLE." << endl;
                        bicolorable = false;
                        break;
                    } else {
                        auto new_elem = blacks.insert(*it);
                        if(new_elem.second == true) q.push(*it); 
                    }
                } else {
                     if(blacks.find(*it) != blacks.end()) {
                        cout << "NOT BICOLORABLE." << endl;
                        bicolorable = false;
                        break;
                    } else {
                        auto new_elem = reds.insert(*it);
                        if(new_elem.second == true) q.push(*it); 
                    }
                }
            }
        }
        if(bicolorable) cout << "BICOLORABLE." << endl;
    }

    return 0;
}
