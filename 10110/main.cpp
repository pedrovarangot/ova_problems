#include <iostream>
#include <cmath>

using namespace std;

int main() {
    unsigned long nbulbs, sqrtl;

    while(!(cin >> nbulbs >> ws).eof()) {
        if(nbulbs == 1) {
            cout << "yes" << endl;
            continue;
        }
        if(nbulbs == 0) break;

        sqrtl = sqrt(nbulbs);

        if(sqrtl*sqrtl == nbulbs) {
            cout << "yes" << endl;
        } else {
            cout << "no" << endl;
        }

        /*
        divs = 1;
        
        sqrtl = sqrt(nbulbs);
        for(int i = 2; i <= sqrtl + 1; i++)  {
            if(nbulbs % i == 0) {
                //cout << i << endl;
                if(nbulbs / i != i) {
                    divs += 2;
                } else {
                    divs += 1;
                }
            }
        }
        divs += 1;

        if(divs % 2 == 0) {
            cout << "no" << endl;
        } else {
            cout << "yes" << endl;
        }
        */

    }        

    return 0;
}
