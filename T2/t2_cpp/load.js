import m from './T2.cjs'

var _bocchi_shut_up, _malloc, HEAP32
await m().then(m => {
    _bocchi_shut_up = m._bocchi_shut_up,
        _malloc = m._malloc, HEAP32 = m.HEAP32
});

export function bocchiShutUp(k, a, n) {
    const p = _malloc(a.length * 4);
    HEAP32.set(new Int32Array(a), p >> 2);
    return _bocchi_shut_up(k, p, n);
}