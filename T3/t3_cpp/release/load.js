import m from './T3.cjs'

var _mancala_board, _mancala_operator, _malloc, HEAP32, getValue
await m().then(m => {
    _mancala_board = m._mancala_board, _malloc = m._malloc, HEAP32 = m.HEAP32, getValue = m.getValue, _mancala_operator = m._mancala_operator
});

export function mancalaBoard(k, a, n) {
    const p = _malloc(a.length * 4);
    HEAP32.set(new Int32Array(a), p >> 2);
    var offset = _mancala_board(k, p, n);
    var result = [];
    for (var i = 0; i < 15; i++) {
        result[i] = getValue(offset + i * 4, 'i32');
    }
    return result;
}

export function mancalaOperator(k, a) {
    const p = _malloc(a.length * 4);
    HEAP32.set(new Int32Array(a), p >> 2);
    return _mancala_operator(k, p);
}
