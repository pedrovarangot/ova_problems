#include <iostream>
#include <map>
#include <tuple>
#include <algorithm>

using namespace std;

int distance(long);
int solve(const std::tuple<int,int> &);

#define MAXM 100000000
int distances[MAXM + 1] = {0};
std::map<std::tuple<int,int>, int> mdistances;

int main()
{
    long i,j,i_orig,j_orig;
    int max = 0, d;

    while(!(std::cin >> i >> j).eof()) {
        i_orig = i; j_orig = j;
        if(i > j) std::swap(i,j);
        std::tuple<int, int> range = std::make_tuple(i,j);
        std::cout << i_orig << " " << j_orig << " " << solve(range) << std::endl;
    }

    return 0;
}

int solve(const std::tuple<int,int> &range)
{
    int i,j; 
    std::tie(i,j) = range;
    if(i == j) return distance(i);
    /*
    for(auto it = mdistances.begin(); it != mdistances.end(); ++it) {
        if(range == it->first) return mdistances[range];
        int k,l;
        std::tie(k,l) = it->first;
        if(k > i and l < j) {
            int r1 = solve(make_tuple(i, k));
            int r2 = solve(make_tuple(l, j));
            return std::max({r1, r2, it->second});
        }
    }*/

    int max = 1, d;

    for(int iit = i; iit <= j;++iit) {
        d = distance(iit);
        if(d > max) max = d; 
    }

    return max; 
}

int distance(long num)
{
    if(num < MAXM and distances[num] != 0) return distances[num];

    long orignum = num;
    int accum = 1;

    while(num != 1)
    {
        if(num % 2 == 0) {
            num = num >> 1;
        } else {
            num = num * 3 + 1;
        }
        if(num < MAXM and distances[num] != 0) {
            accum += distances[num];
            break;
        }
        ++accum;
    }

    if(orignum < MAXM) distances[orignum] = accum;
    return accum;
}

