#include <algorithm>
#include <array>
#include <iostream>
#include <numeric>
#ifndef LOCAL
#define cerr                                                                             \
    if (0)                                                                               \
    cerr
#endif
using namespace std;
template <int N, int M>
class Board {
public:
    array<int, N> cur, oppo;
    int turn;
    int score[2];
    bool end, err;
    Board(int turn) : turn(turn), score{0, 0}, end(false), err(false) {
        for (int i = 0; i < N; i++)
            cur[i] = oppo[i] = M;
    }
    void move(int loc) {
        loc -= turn * 10 + 11;
        if (loc < 0 || loc >= N || cur[loc] == 0 || end) {
            err = true;
            return;
        }
        int cnt = cur[loc];
        cur[loc] = 0;
        int i = loc;
        while (cnt--) {
            i = (i + 1) % (2 * N + 1);
            if (i < N)
                cur[i]++;
            else if (i == N)
                score[turn] += 1;
            else
                oppo[i - N - 1]++;
        }
        if (i < N && cur[i] == 1 && oppo[N - i - 1] > 0) {
            score[turn] += oppo[N - i - 1] + 1;
            cur[i] = oppo[N - i - 1] = 0;
        }
        if (end = all_of(cur.begin(), cur.end(), [](int x) { return x == 0; }) ||
                  all_of(oppo.begin(), oppo.end(), [](int x) { return x == 0; })) {
            score[turn] += accumulate(cur.begin(), cur.end(), 0);
            score[turn ^ 1] += accumulate(oppo.begin(), oppo.end(), 0);
        }
        if (i != N) {
            turn ^= 1;
            swap(cur, oppo);
        }
    }
};
// flag: 1/2先手，seq行动序列，n行动数
// 返回值
// 游戏结束 15000 + 先手的净胜棋数
// 未结束 20000 + 先手的计分洞中的棋数
// 不合法 30000 + 第一个不合法操作所在的步数
int _mancala_result(int flag, int seq[], int n) {
    Board board = Board<6, 4>(flag - 1);
    for (int i = 0; i < n; i++) {
        board.move(seq[i]);
        if (board.err)
            return 30000 + i;
    }
    cerr << board.score[0] << " " << board.score[1] << endl;
    for (int i = 0; i < 6; i++) {
        cerr << board.cur[i] << " " << board.oppo[i] << endl;
    }
    cerr << board.turn + 1 << endl;
    if (board.end) {
        return 15000 + board.score[flag - 1] - board.score[2 - flag];
    } else {
        return 20000 + board.score[flag - 1];
    }
}

extern "C" {
int mancala_result(int flag, int seq[], int n) {
    return _mancala_result(flag, seq, n);
}
}

int main() {
    int flag, n;
    cin >> flag >> n;
    int seq[n];
    for (int i = 0; i < n; i++) {
        cin >> seq[i];
    }
    cout << mancala_result(flag, seq, n) << endl;
    return 0;
}