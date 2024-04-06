import assert from "assert";
import { mancalaResult } from './load.js'

// err: 越界、错手、 0 位、结束后继续
assert.strictEqual(mancalaResult(2, [20], 1), 30000);
assert.strictEqual(mancalaResult(2, [27], 1), 30000);
assert.strictEqual(mancalaResult(2, [0], 1), 30000);
assert.strictEqual(mancalaResult(2, [14], 1), 30000);
assert.strictEqual(mancalaResult(2, [22, 21], 2), 30001);
assert.strictEqual(mancalaResult(2, [22, 10], 2), 30001);
assert.strictEqual(mancalaResult(2, [22, 17], 2), 30001);
assert.strictEqual(mancalaResult(2, [22, 0], 2), 30001);
assert.strictEqual(mancalaResult(1, [13, 11, 22, 11], 4), 30003);
assert.strictEqual(mancalaResult(1, [13, 15, 22, 13], 4), 30003);
assert.strictEqual(mancalaResult(1, [13, 16, 22, 21, 12, 25, 13, 26, 11, 13, 23, 13, 22, 15, 25, 22, 11, 23, 16, 26, 11], 21), 30019);

// fin: 交换先后手、同时清零、执子清零（捕获&抵达终点）、对手清零
assert.strictEqual(mancalaResult(1, [13, 16, 22, 21, 12, 25, 13, 26, 11, 13, 23, 13, 22, 15, 25, 22, 11, 23, 16], 19), 14982);
assert.strictEqual(mancalaResult(2, [23, 26, 12, 11, 22, 15, 23, 16, 21, 23, 13, 23, 12, 25, 15, 12, 21, 13, 26], 19), 14982);
assert.strictEqual(mancalaResult(1, [16, 26, 15, 23, 11, 12, 26, 25, 12, 22, 11, 21, 12, 25, 24, 14, 25, 12, 21, 11, 26, 14, 24, 13, 26, 23, 24, 11, 26, 11, 21, 15, 24, 12, 25, 12, 23, 16, 25, 14, 11, 26, 16, 15, 23, 11, 22, 12, 24, 13, 26, 25, 14, 26], 54), 14998)
assert.strictEqual(mancalaResult(1, [11, 22, 13, 24, 11, 25, 13, 21, 12, 21, 15, 21, 14, 25, 16, 23, 11, 22, 16, 12, 25, 14, 16, 13, 14, 24, 11, 25, 15, 25, 16, 23, 12, 21, 13, 22, 14, 24, 11, 23, 15, 16], 42), 14988)
assert.strictEqual(mancalaResult(1, [12, 24, 16, 23, 11, 16, 15, 23, 16, 12, 26, 14, 23, 16, 13, 21, 14, 26, 22, 14, 24, 11, 23, 13, 25, 13, 26, 14, 21, 11, 24, 15, 23, 16], 34), 14972)
assert.strictEqual(mancalaResult(1, [12, 23, 25, 12, 26, 15, 24, 16, 25, 23, 13, 25, 14, 26, 16, 22, 12, 24, 13, 21, 13, 24, 11, 23, 14, 15, 26, 13, 22, 11, 23, 12, 14, 24, 11, 21, 13, 22, 15, 16], 40), 15008)
assert.strictEqual(mancalaResult(2, [23, 22, 11, 23, 14, 21, 13, 24, 16, 21, 15, 25, 13, 26, 11, 21, 13, 23, 15, 26, 21, 14, 25, 12, 21, 14, 25, 13, 24, 15, 22, 14, 23, 12, 25, 24, 13, 21, 11, 26, 11, 22, 13, 25, 15, 21, 14, 26], 48), 14992)
assert.strictEqual(mancalaResult(1, [13, 15, 21, 14, 23, 15, 22, 11, 14, 25, 15, 21, 16, 24, 13, 16, 11, 21, 14, 22, 16, 13, 25, 11, 21, 12, 22, 13, 24, 15, 21, 14, 23, 16, 26, 25, 11, 21, 15, 22, 16], 41), 15014)

// not fin: any
assert.strictEqual(mancalaResult(1, [13, 16, 22, 21, 12], 5), 20002);
assert.strictEqual(mancalaResult(1, [13, 16, 22, 21, 12, 25, 13, 26, 11, 13, 23, 13, 22, 15, 25, 22, 11, 23, 12], 19), 30018);
assert.strictEqual(mancalaResult(1, [], 0), 20000)
assert.strictEqual(mancalaResult(2, [26, 11, 25, 16, 22, 23, 11, 21], 8), 20004)
assert.strictEqual(mancalaResult(1, [13], 1), 20001)
assert.strictEqual(mancalaResult(1, [12, 25, 11, 22, 15, 24, 13, 22, 14, 25, 26, 14, 22], 13), 20003)
assert.strictEqual(mancalaResult(2, [24, 16, 23, 14, 25, 12, 11, 26, 15], 9), 20004)
assert.strictEqual(mancalaResult(2, [25, 16, 22, 24], 4), 20003)

console.log("🎉 You have passed all the tests provided.");
