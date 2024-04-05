#include <iostream>
#include <map>
using namespace std;
int _bocchi_shut_up(int flag, int seq[], int size) {
    map<int, int> mp;
    for (int i = 0; i < size; i++) {
        if (seq[i] / 10 % 10 == flag)
            mp[seq[i]]++;
    }
    int mx = 0, ans = 0;
    for (auto it = mp.begin(); it != mp.end(); it++) {
        if (it->second > mx)
            mx = it->second, ans = it->first;
        else if (it->second == mx)
            ans = 10;
    }
    return ans;
}

extern "C" {
int bocchi_shut_up(int flag, int seq[], int size) {
    return _bocchi_shut_up(flag, seq, size);
}
}
int main() {
    // cout << bocchi_shut_up(1, new int[6]{13, 14, 15, 21, 11, 16}, 10) << endl;
    // //2, [13, 14, 13, 11, 21, 13, 21, 22], 8
    // cout << bocchi_shut_up(2, new int[8]{13, 14, 13, 11, 21, 13, 21, 22}, 8) <<
    // endl;
    return 0;
}