#pragma once

extern "C" {
    void Disperse_initialize(float sampleRate);
    void Disperse_tick(float L, float R);
    float Disperse_lastOutL();
    float Disperse_lastOutR();
}