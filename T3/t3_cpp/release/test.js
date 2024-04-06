import assert from "assert";
import { mancalaBoard } from './load.js'

console.log(mancalaBoard(1, [13, 16, 22, 21, 12], 5), 20002);
console.log(mancalaBoard(1, [13, 16, 22, 21, 12, 25, 13, 26, 11, 13, 23, 13, 22, 15, 25, 22, 11, 23, 12], 19), 30018);
console.log(mancalaBoard(1, [], 0), 20000)
console.log(mancalaBoard(2, [26, 11, 25, 16, 22, 23, 11, 21], 8), 20004)
console.log(mancalaBoard(1, [13], 1), 20001)
console.log(mancalaBoard(1, [12, 25, 11, 22, 15, 24, 13, 22, 14, 25, 26, 14, 22], 13), 20003)
console.log(mancalaBoard(2, [24, 16, 23, 14, 25, 12, 11, 26, 15], 9), 20004)
console.log(mancalaBoard(2, [25, 16, 22, 24], 4), 20003)

