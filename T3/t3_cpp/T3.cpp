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
            cur.fill(0), oppo.fill(0);
        }
        if (i != N) {
            turn ^= 1;
            swap(cur, oppo);
        }
    }
};

int *_mancala_board(int flag, int seq[], int n) {
    Board board = Board<6, 4>(seq[0] / 10 - 1);
    for (int i = 0; i < n - 1; i++)
        board.move(seq[i]);
    int dat;
    if (board.turn != flag - 1)
        board.err = true;
    board.move(seq[n - 1]);
    if (board.end)
        dat = 200 + board.score[0] - board.score[1];
    else if (board.err)
        dat = 200 + (flag == 1 ? 2 * board.score[0] - 48 : 48 - 2 * board.score[1]);
    else
        dat = board.turn;
    int *b = new int[15];
    if (board.turn)
        swap(board.cur, board.oppo);
    for (int i = 0; i < 6; i++)
        b[i] = board.cur[i], b[i + 7] = board.oppo[i];
    b[6] = board.score[0], b[13] = board.score[1];
    b[14] = dat;
    return b;
}

extern "C" {
int *mancala_board(int flag, int seq[], int n) {
    return _mancala_board(flag, seq, n);
}
}

int main() {
    int flag, n;
    cin >> flag >> n;
    int seq[n];
    for (int i = 0; i < n; i++)
        cin >> seq[i];
    auto b = mancala_board(flag, seq, n);
    for (int i = 0; i < 15; i++)
        cout << b[i] << " ";
    return 0;
}