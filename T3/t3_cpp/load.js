import m from './T3.cjs'

var _mancala_result, _malloc, HEAP32
await m().then(m => {
    _mancala_result = m._mancala_result,
        _malloc = m._malloc, HEAP32 = m.HEAP32
});

export function mancalaResult(k, a, n) {
    const p = _malloc(a.length * 4);
    HEAP32.set(new Int32Array(a), p >> 2);
    return _mancala_result(k, p, n);
}