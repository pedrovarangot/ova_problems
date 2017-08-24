#include <unordered_set>
#include <unordered_map>
#include <set>
#include <iostream>

using namespace std;

long int build_all_roads(unordered_map<int, unordered_set<int> > &G, int node, unordered_set<int> &library, unordered_set<int> &no_library, int croad);

int main() {
    int q;
    cin >> q;
    for(int a0 = 0; a0 < q; a0++){
        int n;
        int m;
        long clib;
        long croad;
        cin >> n >> m >> clib >> croad;
        unordered_map<int, unordered_set<int> > G(n);
        if(croad > clib) {
            for(int a1 = 0; a1 < m; a1++){
                int city_1;
                int city_2;
                cin >> city_1 >> city_2;
            }
        } else {            
            for(int a1 = 0; a1 < m; a1++){
                int city_1;
                int city_2;
                cin >> city_1 >> city_2;
                G[city_1].insert(city_2);
                G[city_2].insert(city_1);
            }
        }
        unordered_set<int> no_library(n);
        unordered_set<int> library(n);
        long int cost = 0;
        if(croad > clib) {
            cout << clib*n << endl;
            continue;
        }
        for(int i = 1; i <= n; ++i) no_library.insert(i);
        while(!no_library.empty()) {
            int node = *no_library.begin();
            cost += clib;
            //cout << "built library at " << node << endl;
            library.insert(node);
            no_library.erase(no_library.find(node));
            cost += build_all_roads(G, node, library, no_library, croad);
        }
        cout << cost << endl;
    }
    return 0;
}

long int build_all_roads(unordered_map<int, unordered_set<int> > &G, int node, unordered_set<int> &library, unordered_set<int> &no_library, int croad) {
    long int cost = 0;
    for(auto it = G[node].begin(); it != G[node].end(); ++it) {
        if(library.find(*it) == library.end()) {
            library.insert(*it);
            no_library.erase(no_library.find(*it));
            //cout << "connected " << *it << "with road" << endl;
            cost += croad;
            for(auto jt = G[*it].begin(); jt != G[*it].end(); ++jt) {
                if(library.find(*jt) == library.end()) {
                    library.insert(*jt);
                    no_library.erase(*jt);    
                    cost += croad + build_all_roads(G, *jt, library, no_library, croad);
                    //cout << "connected " << *jt << "with road" << endl;
                }
                
            }
        }
    }
    
    return cost;
}
