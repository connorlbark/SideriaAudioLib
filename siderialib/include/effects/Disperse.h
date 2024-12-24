#pragma once

#include "../siderialib.h"
#include "delay/ModulatedDelay.h"
#include "effects/resample/VariableResample.h"
#include "effects/disperse/DisperseConstants.h"
#include "effects/disperse/DisperseParallelVoice.h"

namespace siderialib {
    enum class DisperseArrangement {
        FULL_PARALLEL = 0,
        FULL_SERIAL = 1,
    };

    enum class DispersePingPong {
        OFF = 0,
        ON = 1,
        RANDOM = 2
    };

    class Disperse {
    private:
        sfloat _sampleRate;

        // delay lines
        ModulatedDelay _delays[DISPERSE_NUM_VOICES];
        // arrangement of delay lines
        DisperseParallelVoice _voices[DISPERSE_NUM_VOICES];

        VariableResample _resampleL;
        VariableResample _resampleR;
        sfloat _resampleFactor = 1.0;

        sfloat _dispersion = 0.0;
        sfloat _dispersionPosition = 0.4;
        sfloat _spread = 0.0;
        sfloat _spreadPosition = 0.6;
        sfloat _feedback = 0.5;
        sfloat _timeMs = 100.0;
        sfloat _mix = 1.0;
        sfloat _tone = 0.5;

        DispersePingPong _pingPong = DispersePingPong::OFF;

        sfloat _modRateHz = 1.0;
        sfloat _modDepth = 0.0;

        sfloat _lastOutL = 0.f;
        sfloat _lastOutR = 0.f;

        LFO _lfo;
        BiquadFilter _postLpfL;
        BiquadFilter _postLpfR;

        void updateSpread();
        void updateDispersionAndPosition();
        void updateFeedback();
        void updateTone();
        void updateMod();
        void updatePingPong();

        void applyVoices(sfloat L, sfloat R);
        void applyWetFX();

        void clearVoices();
    public:
        void initialize(sfloat *voiceBufs[DISPERSE_NUM_VOICES],
                        int bufLength,
                        sfloat *upsampleBufL,
                        sfloat *upsampleBufR,
                        int upsampleBufLen,
                        sfloat sampleRate);
        void initialize(sfloat sampleRate);

        virtual ~Disperse() = default;

        void tick(sfloat L, sfloat R);

        sfloat lastOutL() const;
        sfloat lastOutR() const;

        void setTimeMs(sfloat timeMs);
        inline sfloat getTimeMs() const { return _timeMs; }
        void setSpread(sfloat spread);
        inline sfloat getSpread() const { return _spread; }
        void setFeedback(sfloat feedback);
        inline sfloat getFeedback() const { return _feedback; }
        void setDispersion(sfloat dispersion);
        inline sfloat getDispersion() const { return _dispersion; }
        void setPosition(sfloat position);
        inline sfloat getPosition() const { return this->_dispersionPosition; }
        void setModRateHz(sfloat modRateHz);
        inline sfloat getModRateHz() const { return this->_modRateHz; }
        void setModDepth(sfloat depth);
        inline sfloat getModDepth() const { return this->_modDepth; }
        void setMix(sfloat mix);
        inline sfloat getMix() const { return this->_mix; }

        void setPingPongType(DispersePingPong pingPong);

        inline sfloat getResampleFactor() const { return _resampleFactor; }
        void setResampleFactor(sfloat ratio);

        void setArrangement(DisperseArrangement arrangement);
    };
}
