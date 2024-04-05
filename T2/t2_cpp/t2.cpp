#include <iostream>

// flag: 1/2先手，seq行动序列，n行动数
// 返回值
// 游戏结束 15000 + 先手的净胜棋数
// 未结束 20000 + 先手的计分洞中的棋数
// 不合法 30000 + 第一个不合法操作所在的步数
int _mancala_result(int flag, int seq[], int n) {}

extern "C" {
int mancala_result(int flag, int seq[], int n) {
    return _mancala_result(flag, seq, n);
}
}