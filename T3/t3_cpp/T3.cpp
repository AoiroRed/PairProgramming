#include <algorithm>
#include <array>
#include <iostream>
#include <numeric>
#include <unordered_map>
#include <vector>
#ifndef LOCAL
#define cerr                                                                             \
    if (0)                                                                               \
    cerr
#endif
using namespace std;
using ll = long long;
const int MAX_DEPTH = 10;
namespace board {
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
        end = all_of(cur.begin(), cur.end(), [](int x) { return x == 0; }) ||
              all_of(oppo.begin(), oppo.end(), [](int x) { return x == 0; });
        if (end) {
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
        dat = board.turn + 1;
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
} // namespace board
namespace op {
const int inf = 0x3f3f3f3f;
const int hole = 6, seed = 4;
template <int N, int M>
class Board {
public:
    array<int, N> cur, oppo;
    int turn;
    int score[2];
    bool end;
    Board(int turn) : turn(turn), score{0, 0}, end(false) {
        for (int i = 0; i < N; i++)
            cur[i] = oppo[i] = M;
    }
    bool move(int loc) {
        int cnt = cur[loc];
        cur[loc] = 0;
        while (cnt--) {
            loc = (loc + 1) % (2 * N + 1);
            if (loc < N)
                cur[loc]++;
            else if (loc == N)
                score[turn] += 1;
            else
                oppo[loc - N - 1]++;
        }
        if (loc < N && cur[loc] == 1 && oppo[N - loc - 1] > 0) {
            score[turn] += oppo[N - loc - 1] + 1;
            cur[loc] = oppo[N - loc - 1] = 0;
            end |= all_of(oppo.begin(), oppo.end(), [](int x) { return x == 0; });
        }
        end |= all_of(cur.begin(), cur.end(), [](int x) { return x == 0; });
        if (end) {
            score[turn] += accumulate(cur.begin(), cur.end(), 0);
            score[turn ^ 1] += accumulate(oppo.begin(), oppo.end(), 0);
        }
        if (loc != N) {
            turn ^= 1;
            swap(cur, oppo);
            return false;
        }
        return !end;
    }
    bool operator==(const Board &b) const {
        return cur == b.cur && oppo == b.oppo;
    }
};
class MyHash {
public:
    size_t operator()(const Board<hole, seed> &board) const {
        size_t seed = 0;
        for (int i = 0; i < hole; i++) {
            seed ^= board.cur[i] + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            seed ^= board.oppo[i] + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
        return seed;
    }
};
int cur_score;
// turn == 0 if max_depth is even
int evaluate(const Board<hole, seed> &board, int reps) {
    if (board.end) {
        int score = board.score[0] - board.score[1];
        return (cur_score > 0 ? 20 : 5) * (score);
    }
    int score = 10 * (board.score[0] - board.score[1]);
    score += reps * 2;
    auto &cur = MAX_DEPTH & 1 ? board.oppo : board.cur;
    score += 5 * (cur[5] == 0);
    score += 3 * (!!cur[1] + !!cur[2] + !!cur[3] > 1);
    return score;
}
int alpha_beta(const Board<hole, seed> &board, int alpha, int beta, bool is_max = true,
               int max_depth = MAX_DEPTH, int rep = 0, bool top = true) {
    if (max_depth == 0 || board.end)
        return evaluate(board, rep);
    int score = is_max ? -inf : inf;
    vector<Board<hole, seed>> bd;
    vector<tuple<Board<hole, seed>, int, int>> bds;
    bd.push_back(board);
    auto dfs = [&](auto &&self, int rep = 0, int op = -1) -> void {
        vector<tuple<Board<hole, seed>, int, int>> tmp;
        for (int i = 0; i < hole; i++) {
            if (!bd.back().cur[i])
                continue;
            Board next = bd.back();
            if (next.move(i)) {
                bd.push_back(next);
                self(self, rep + 1, op == -1 ? i : op);
                bd.pop_back();
            } else {
                tmp.emplace_back(next, rep, op == -1 ? i : op);
            }
        }
        for (auto &next : tmp)
            bds.push_back(next);
    };
    dfs(dfs);
    int best = -1;
    for (auto &[next, reps, op] : bds) {
        int v = alpha_beta(next, alpha, beta, !is_max, max_depth - 1, rep + reps, false);
        if (is_max) {
            if (v > score) {
                score = v;
                best = op;
                alpha = max(alpha, score);
            }
        } else {
            if (v < score) {
                score = v;
                best = op;
                beta = min(beta, score);
            }
        }
        if (alpha >= beta)
            break;
    }
    return top ? best : score;
}
unordered_map<Board<hole, seed>, int, MyHash> mp;
Board<hole, seed> board = Board<hole, seed>(0);
int _mancala_operator(int flag, int status[]) {
    for (int i = 0; i < hole; i++)
        if (flag == 1)
            board.cur[i] = status[i], board.oppo[i] = status[hole + 1 + i];
        else
            board.cur[i] = status[hole + 1 + i], board.oppo[i] = status[i];
    if (mp.count(board))
        return mp[board] + flag * 10 + 1;
    cur_score = (flag == 1 ? 1 : -1) * (status[hole] - status[2 * hole + 1]);
    return alpha_beta(board, -inf, inf) + flag * 10 + 1;
}
extern "C" {
int mancala_operator(int flag, int status[]) {
    return _mancala_operator(flag, status);
}
}
void memorize(vector<int> &&pre, vector<int> &&op) {
    Board<hole, seed> b = Board<hole, seed>(0);
    for (auto &i : pre)
        b.move(i);
    for (auto &i : op) {
        mp[b] = i;
        b.move(i);
    }
}
auto init = []() -> int {
    memorize({}, {2, 5, 1, 0}); // 2, 5, 1, 0, 1, 4, 5, 4, 3, 5, 0, 5, 4
    memorize({5}, {1});
    memorize({2, 5, 5}, {1, 5, 3});
    memorize({2, 5, 4}, {1, 5, 3});
    memorize({2, 5, 3}, {1, 5, 0});
    return 0;
}();
} // namespace op

int main() {
    int n;
    cin >> n;
    op::Board<op::hole, op::seed> board = op::Board<op::hole, op::seed>(0);
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        board.move(x);
    }
    int *b = new int[14];
    if (board.turn)
        swap(board.cur, board.oppo);
    for (int i = 0; i < 6; i++)
        b[i] = board.cur[i], b[i + 7] = board.oppo[i];
    b[6] = board.score[0], b[13] = board.score[1];
    cout << op::_mancala_operator(board.turn + 1, b) - board.turn * 10 - 11 << endl;
    return 0;
}
