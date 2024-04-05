import assert from "assert";
import { mancalaResult } from './load.js'

assert.strictEqual(mancalaResult(1, [0], 1), 30000);

console.log("🎉 You have passed all the tests provided.");
