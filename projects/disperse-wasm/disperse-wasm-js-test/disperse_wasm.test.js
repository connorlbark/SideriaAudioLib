const disperse = require("../../../cmake-build-wasm-debug/projects/disperse-wasm/disperse_wasm.js");
describe('disperseTests', () => {
    beforeAll(() => {
        return new Promise((resolve) => {
            disperse['onRuntimeInitialized'] = () => {
                resolve();
            };
        });
    }, 10000); // Optional timeout, adjust as needed


    test('disperse loads', () => {
        expect(disperse).toBeDefined();
        expect(disperse._Disperse_initialize).toBeDefined();
        expect(disperse._Disperse_tick).toBeDefined();
        expect(disperse._Disperse_lastOutL).toBeDefined();
        expect(disperse._Disperse_lastOutR).toBeDefined();
    })


    test('disperse runs no sound', () => {
        disperse._Disperse_initialize(44100.0);
        for (let i = 0; i < 100; i++) {
            disperse._Disperse_tick(0.0,0.0);
            expect(disperse._Disperse_lastOutL()).toBe(0.0);
            expect(disperse._Disperse_lastOutR()).toBe(0.0);
        }
    })



})
