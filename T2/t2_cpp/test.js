import assert from "assert";
import { mancalaResult } from './load.js'

// err: 越界、错手、 0 位、结束后继续
// fin: 同时清零、执子清零（捕获&抵达终点）、对手清零
// not fin: any
assert.strictEqual(mancalaResult(1, [0], 1), 30000);
assert.strictEqual(mancalaResult(1, [13, 16, 22, 21, 12, 25, 13, 26, 11, 13, 23, 13, 22, 15, 25, 22, 11, 23, 16], 19), 14982);
assert.strictEqual(mancalaResult(1, [13, 16, 22, 21, 12, 25, 13, 26, 11, 13, 23, 13, 22, 15, 25, 22, 11, 23, 16, 26, 11], 21), 30019);
assert.strictEqual(mancalaResult(1, [13, 16, 22, 21, 12, 25, 13, 26, 11, 13, 23, 13, 22, 15, 25, 22, 11, 23, 12], 19), 30018);
assert.strictEqual(mancalaResult(1, [13, 16, 22, 21, 12], 5), 20002);

console.log("🎉 You have passed all the tests provided.");
