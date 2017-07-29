#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define JOLLY {cout << "Jolly" << endl; return;}
#define NOTJOLLY {cout << "Not jolly" << endl; return;}

void isJolly(vector<int> &v, unsigned short size) {
    for(int i = 0; i < size - 1; i++) {
        v[i] = abs(v[i] - v[i+1]);
        if(v[i] > size or v[i] < 1) NOTJOLLY;
    }
    size--;
    sort(v.begin(), v.begin() + size);
    for(int i = 0; i < size; i++) {
        if(v[i] != i + 1) NOTJOLLY;
    }
    JOLLY;

}

int main()
{
    vector<int> sequence(3000);
    unsigned short size, pos = 0;

    while(!(cin >> size >> ws).eof()) {
        while(pos < size) cin >> sequence[pos++] >> ws;
        
        isJolly(sequence, size);        
        
        pos = 0;
    }
    
}

