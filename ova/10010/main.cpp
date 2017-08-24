#include <string>
#include <cstring>
#include <array>
#include <tgmath.h>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef enum {
    LEFT2RIGT,
    UP2DOWN,
    LD2UR,
    LU2DR,
} word_direction;

template <class T, size_t ROW, size_t COL>
using Matrix = array<array<T, COL>, ROW>;

unsigned int BASE = 29;

void hash_all(const char m[50][50], unsigned int rows, unsigned int cols, unsigned int len, word_direction dir, unsigned int h[50][50])
{
    int i, j;
    memset(h, 0, 50*50*sizeof(unsigned int));
    switch(dir) {
        case LEFT2RIGT:
            for(i = 0; i < rows; i++) {
                for(j = 0; j < len; j++) {
                    h[i][0] += m[i][j] * pow(BASE, len - j - 1);
                }
                for(j = 1; j + len <= cols; j++) {
                    h[i][j] = BASE * (h[i][j-1] - m[i][j-1] * pow(BASE, len - 1)) + m[i][j + len - 1];
                }
            }
            break;
        case UP2DOWN:
            if(len == 1 or rows == 1) break;
            for(j = 0; j < cols; j++) {
                for(i = 0; i < len; i++) {
                    h[0][j] += m[i][j] * pow(BASE, len - i - 1);
                }
                for(i = 1; i + len <= rows; i++) {
                    h[i][j] = BASE * (h[i - 1][j] - m[i - 1][j] * pow(BASE, len - 1)) + m[i + len - 1][j];
                }
            }
            break;
        case LD2UR:
            if(len == 1 or rows == 1 or cols == 1) break;
            for(i = rows - 1; i >= len - 1; i--) {
                for(j = 0; j < len; j++) {
                    //cout << "LD2UR: " << i - j << " " << j << endl; 
                    h[i][0] += m[i-j][j] * pow(BASE, len - j - 1);
                }
            }
            for(j = 1; j <= cols - len; j++) {
                for(i = rows - 1; i > rows - len - 1; i--) {
                    h[rows - 1][j] += m[i][j + rows - 1 -i] * pow(BASE, len - (rows - 1 - i) - 1);
                }
            }

            for(i = rows - 2; i >= len - 1; i--) {
                for(j = 1; j <= cols - len; j++) {
//                    cout << "pos: " << i << " " << j << endl;
//                    cout << "LD2URr: " << i + 1 << " " << j - 1 <<  " " << m[i+1][j-1] * pow(BASE, len - 1) << endl; 
//                    cout << "LD2URa: " << i - (len - 1) << " " << j + len - 1 << endl; 
                    h[i][j] = BASE * (h[i+1][j-1] - m[i+1][j-1] * pow(BASE, len - 1)) + m[i - (len - 1)][j + len - 1];
                }
            }
            break;
        case LU2DR:
            if(len == 1 or rows == 1 or cols == 1) break;
            for(i = 0; i < rows; i++) {
                for(j = 0; j < len; j++) {
                    //cout << "LU2DR: " << i + j << " " << j << endl;
                    h[i][0] += m[i+j][j] * pow(BASE, len - j - 1);
                }
            }
            for(j = 1; j < cols; j++) {
                for(i = 0; i < len; i++) {
                    //cout << "LU2DR: " << i + j << " " << j << endl;
                    h[0][j] += m[i][j+i] * pow(BASE, len - i - 1);
                }
            }
            for(i = 1; i + len <= rows; i++) {
                for(j = 1; j + len <= cols; j++) {
                    h[i][j] = BASE * (h[i-1][j-1] - m[i-1][j-1] * pow(BASE, len - 1)) + m[i + len - 1][j + len - 1];
                }
            }
    }

}

void print_h(unsigned int h[50][50], size_t rows, size_t cols)
{
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            cout << h[i][j] << " ";
        }
        cout << endl;
    }
}

char alford(char c) {
    return c - 96;
}

int main()
{
    size_t rows,cols;
    char m[50][50] = {0};
    unsigned int h[4][51][50][50] = {0};
    vector<string> words(20);
    string line;
    size_t cases;
    
    cin >> cases >> ws;

    while(cases--) {
        cin >> rows >> cols >> ws;
        size_t nwords;
        for(int i = 0; i < rows; i++) {
            cin >> m[i];
            transform(m[i], m[i] + 50, m[i], ::tolower);
            transform(m[i], m[i] + 50, m[i], alford);
            cin >> ws;
        }
        cin >> nwords;
        for(int i = 0; i < nwords; i++)
        {
            cin >> words[i];
            transform(words[i].begin(), words[i].end(), words[i].begin(), ::tolower);
            transform(words[i].begin(), words[i].end(), words[i].begin(), alford);
        }
        memset(h, 0, 4*50*50*50*sizeof(unsigned int));
        //print_h(h, rows, cols);
        for(auto it = words.begin(); it < words.begin() + nwords; ++it) {
            //cout << *it << endl;
            if(h[LEFT2RIGT][it->size()][0][0] == 0) {
                hash_all(m, rows, cols, it->size(), LEFT2RIGT, h[LEFT2RIGT][it->size()]);
                hash_all(m, rows, cols, it->size(), UP2DOWN, h[UP2DOWN][it->size()]);
                hash_all(m, rows, cols, it->size(), LU2DR, h[LU2DR][it->size()]);
                hash_all(m, rows, cols, it->size(), LD2UR, h[LD2UR][it->size()]);
//                print_h(h[LD2UR][it->size()], rows, cols);
            }
            unsigned int word_hash = 0, r_word_hash = 0;
            for(int j = 0; j < it->size(); j++) {
                word_hash += (*it)[j] * pow(BASE, it->size() - j - 1);
            }
//            cout << "f:" << word_hash << endl;
            int i = 0;
            for(int j = it->size() - 1; j >= 0; j--, i++) {
                r_word_hash += (*it)[j] * pow(BASE, it->size() - i - 1);
            }
//            cout << "r:" << r_word_hash << endl;

            int row = 52, col = 52;
            int o_i, o_j;
#define FOUNDWORD { do { if(row > i or (row == i and j < col) ) { row = i; col = j; } } while(0); };
            for(int i = 0; i < rows; i++) {
                for(int j = 0; j < cols; j++) {
                    if(h[LEFT2RIGT][it->size()][i][j] == word_hash and m[i][j] == (*it)[0]) { FOUNDWORD; }
                    if(h[UP2DOWN][it->size()][i][j] == word_hash and m[i][j] == (*it)[0]) { FOUNDWORD; }
                    if(h[LU2DR][it->size()][i][j] == word_hash and m[i][j] == (*it)[0]) { FOUNDWORD; } 
                    if(h[LD2UR][it->size()][i][j] == word_hash and m[i][j] == (*it)[0]) { FOUNDWORD; } 
                    o_i = i; o_j = j;
                    if(h[LEFT2RIGT][it->size()][i][j] == r_word_hash and m[i][j] == (*it)[it->size()-1]) { j += it->size() - 1; FOUNDWORD; }
                    i = o_i; j = o_j;
                    if(h[UP2DOWN][it->size()][i][j] == r_word_hash and m[i][j] == (*it)[it->size()-1]) { i += it->size() - 1; FOUNDWORD; }
                    i = o_i; j = o_j;
                    if(h[LU2DR][it->size()][i][j] == r_word_hash and m[i][j] == (*it)[it->size()-1]) { j += it->size() -1; i += it->size() - 1; FOUNDWORD; } 
                    i = o_i; j = o_j;
                    if(h[LD2UR][it->size()][i][j] == r_word_hash and m[i][j] == (*it)[it->size()-1]) { j += it->size() -1; i -= it->size() - 1; FOUNDWORD; } 
                    i = o_i; j = o_j;
                }
            }
            cout << row + 1 << " " << col + 1 << endl;

        }
        if(cases != 0) cout << endl;

    }

    return 0;
}

