#pragma once

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


        bool _enableTone = false;
        // 2-stage lpf placed before writing to circular buffer, so in essence, filters delayed sounds many times
        bool useLpf = false;
        BiquadFilter _lpf1L;
        BiquadFilter _lpf1R;
        BiquadFilter _lpf2L;
        BiquadFilter _lpf2R;

        sfloat sampleRate = 0.0;

        bool useHpf = false;
        // 2-stage hpf
        BiquadFilter _hpf1L;
        BiquadFilter _hpf1R;
        BiquadFilter _hpf2L;
        BiquadFilter _hpf2R;

        void applyFilters();
    public:
        DisperseParallelVoice() = default;

        void addVoice(ModulatedDelay* delay);

        void clearVoices();

        void initialize(sfloat samplingRate);

        void tick(sfloat L, sfloat R);

        void setTone(sfloat tone);

        void enableTone(bool enable) {
            _enableTone = enable;
        }

        inline sfloat lastOutL() const {
            return _lastOutL;
        }

        inline sfloat lastOutR() const {
            return _lastOutR;
        }
    };
}

