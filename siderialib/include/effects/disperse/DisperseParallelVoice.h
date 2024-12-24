#pragma once


#include <cstdarg>
#include "effects/delay/ModulatedDelay.h"
#include "DisperseConstants.h"

namespace siderialib {
    class DisperseParallelVoice {
    private:
        ModulatedDelay* _delays[DISPERSE_NUM_VOICES] = {
                nullptr, nullptr, nullptr, nullptr, nullptr, nullptr
        };
        int _numActiveVoices = 0;

        sfloat _lastOutL = 0.0;
        sfloat _lastOutR = 0.0;
    public:
        DisperseParallelVoice() = default;

        void addVoice(ModulatedDelay* delay) {
            if (_numActiveVoices >= DISPERSE_NUM_VOICES) {
                return;
            }

            _delays[_numActiveVoices] = delay;
            _numActiveVoices++;
        }

        void clearVoices() {
            for (int i = 0; i < _numActiveVoices; i++) {
                _delays[i] = nullptr;
            }

            _numActiveVoices = 0;
        }

        void initialize() {
        }

        void tick(sfloat L, sfloat R) {
            sfloat parallelL = L;
            sfloat parallelR = R;

            for (int i = 0; i < _numActiveVoices; i++) {
                _delays[i]->tick(L, R);
                parallelL = _delays[i]->lastOutL();
                parallelR = _delays[i]->lastOutR();
            }

            _lastOutL = parallelL;
            _lastOutR = parallelR;
        }

        sfloat lastOutL() const {
            return _lastOutL;
        }

        sfloat lastOutR() const {
            return _lastOutR;
        }
    };
}

