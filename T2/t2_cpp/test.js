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

// fin: 同时清零、执子清零（捕获&抵达终点）、对手清零
assert.strictEqual(mancalaResult(1, [13, 16, 22, 21, 12, 25, 13, 26, 11, 13, 23, 13, 22, 15, 25, 22, 11, 23, 16], 19), 14982);
assert.strictEqual(mancalaResult(2, [23, 26, 12, 11, 22, 15, 23, 16, 21, 23, 13, 23, 12, 25, 15, 12, 21, 13, 26], 19), 14982);

// not fin: any
assert.strictEqual(mancalaResult(1, [0], 1), 30000);
assert.strictEqual(mancalaResult(1, [13, 16, 22, 21, 12], 5), 20002);
assert.strictEqual(mancalaResult(1, [13, 16, 22, 21, 12, 25, 13, 26, 11, 13, 23, 13, 22, 15, 25, 22, 11, 23, 12], 19), 30018);


console.log("🎉 You have passed all the tests provided.");
