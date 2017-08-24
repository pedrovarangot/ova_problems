#include <iostream>
#include <vector>
#include <string>

using namespace std;

void fill_up_decimal(vector<int> &v, const string &s)
{
    v.clear();
    for(auto it = s.begin(); it != s.end(); ++it) {
        v.push_back(*it - '0'); 
    }
}

int sum_and_carry(vector<int> &u, const vector<int> &d)
{
    int rv = 0;

    auto itd = d.rbegin(); 
    auto itu = u.rbegin();
    for(; itd != d.rend(); ++itd, ++itu) {
        //cout << "u: " << *itu << endl;
        //cout << "d: " << *itd << endl;
        int sum = *itd + *itu;
        if(sum > 9) {
            //cout << "carry with " << sum << endl;
            rv++;
            if(itu + 1 != u.rend()) *(itu + 1) += 1;
        }
    }

    while(itu != u.rend()) {
        //cout << "carry with " << *itu << endl;
        if(*itu > 9) {
            rv++;
            if(itu + 1 != u.rend()) *(itu + 1) += 1;
        }

        ++itu;
    }

    return rv;
}

int main() 
{
    vector<int> n1, n2;
    string n1s, n2s;
    bool lastline = false;
    int carries;

    cin >> n1s >> n2s >> ws;
    lastline = (cin.peek() == EOF);
    while(not lastline) {
        fill_up_decimal(n1, n1s);
        fill_up_decimal(n2, n2s);

        if(n1.size() > n2.size()) {
            carries = sum_and_carry(n1, n2);
        } else {
            carries = sum_and_carry(n2, n1);
        }

        n1s.clear(); n2s.clear();
        cin >> n1s >> n2s >> ws; 
        lastline = (cin.peek() == EOF);

        switch(carries) {
            case 0:
                cout << "No carry operation.";
                break;
            case 1:
                cout << "1 carry operation.";
                break;
            default:
                cout << carries << " carry operations.";
        }

        cout << endl;

    }

    return 0;
}
