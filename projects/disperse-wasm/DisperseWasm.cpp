#include "DisperseWasm.h"

#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#else
#define EMSCRIPTEN_KEEPALIVE
#endif

#include "effects/Disperse.h"

siderialib::Disperse disperse;
siderialib::StaticMemoryAllocation staticMemoryAllocation;
extern "C" {
    EMSCRIPTEN_KEEPALIVE void Disperse_initialize(float sampleRate)
    {
        staticMemoryAllocation.initialize((int)sampleRate * 10 * 6 + 500);
        disperse.initialize(staticMemoryAllocation, sampleRate);
    }
    EMSCRIPTEN_KEEPALIVE void Disperse_tick(float L, float R)
    {
        disperse.tick(L, R);
    }

    EMSCRIPTEN_KEEPALIVE float Disperse_lastOutL()
    {
        return disperse.lastOutL();
    }

    EMSCRIPTEN_KEEPALIVE float Disperse_lastOutR()
    {
        return disperse.lastOutR();
    }
}