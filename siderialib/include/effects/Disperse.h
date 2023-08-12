#pragma once

#include "../siderialib.h"
#include "delay/ModulatedDelay.h"

namespace siderialib {
    enum class DisperseArrangement {
        FULL_PARALLEL = 0,
    };

    // maximum dispersion, as a function of the time param
    constexpr sfloat maxTimeDisperse = 0.5f;
    constexpr sfloat maxModRateDisperse = 0.2f;
    constexpr sfloat maxDelayMs = 5000.0f;
    constexpr sfloat minDelayMs = 100.0f;

    class Disperse {
    private:
        sfloat _sampleRate;

        // voice1: special, always-centered voice
        ModulatedDelay _voice1;
        ModulatedDelay _voice2;
        ModulatedDelay _voice3;
        ModulatedDelay _voice4;
        ModulatedDelay _voice5;
        ModulatedDelay _voice6;


        sfloat _dispersion = 0.0;
        sfloat _spread = 0.0;
        sfloat _feedback = 0.5;
        sfloat _timeMs = 100.0;
        sfloat _mix = 1.0;
        sfloat _tone = 0.5;
        sfloat _position = 0.0;
        int _downsampleFactor = 0;
        DisperseArrangement _arrangement = DisperseArrangement::FULL_PARALLEL;

        sfloat _modRateHz = 1.0;
        sfloat _modDepth = 0.0;

        int _clockTick = 0;

        sfloat _lastOutL = 0.f;
        sfloat _lastOutR = 0.f;

        LFO _lfo;
        BiquadFilter _postLpfL;
        BiquadFilter _postLpfR;

        void updateSpread();
        void updateDispersionAndPosition();
        void updateFeedback();
        void updateTone();
        void updateAllParams();
        void updateMod();

    public:
        void initialize(sfloat *voice1Buf,
                        sfloat *voice2Buf,
                        sfloat *voice3Buf,
                        sfloat *voice4Buf,
                        sfloat *voice5Buf,
                        sfloat *voice6Buf,
                        int bufLength,
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
        void setTone(sfloat tone);
        inline sfloat getTone() const { return _tone; }
        void setArrangement(DisperseArrangement arrangement);
        inline DisperseArrangement getArrangement() const { return _arrangement; }
        void setPosition(sfloat position);
        inline sfloat getPosition() const { return this->_position; }
        void setModRateHz(sfloat modRateHz);
        inline sfloat getModRateHz() const { return this->_modRateHz; }
        void setModDepth(sfloat depth);
        inline sfloat getModDepth() const { return this->_modDepth; }
        void setMix(sfloat mix);
        inline sfloat getMix() const { return this->_mix; }
        void setDownsampleFactor(int factor);
        inline int getDownsampleFactor() const { return _downsampleFactor; }

        void setAllParams(sfloat mix,
                          sfloat dispersion,
                          sfloat spread,
                          sfloat time,
                          sfloat feedback,
                          sfloat tone,
                          sfloat modRateHz,
                          sfloat modDepth,
                          sfloat position,
                          int downsampleFactor,
                          DisperseArrangement arrangement);

    };
}
