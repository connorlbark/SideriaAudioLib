#pragma once

#include "../siderialib.h"
#include "delay/ModulatedDelay.h"

namespace siderialib {
    enum DisperseArrangement {
        FULL_PARALLEL = 0,
    };

    // maximum dispersion, as a function of the time param
    constexpr sfloat maxTimeDisperse = 0.2;
    constexpr sfloat maxModRateDisperse = 0.2;
    constexpr sfloat maxDelayMs = 5000.0;

    class Disperse {
    private:
        sfloat sampleRate;

        ModulatedDelay voice1;
        sfloat voice1Pan = 0.f;
        ModulatedDelay voice2;
        sfloat voice2Pan = 0.f;
        ModulatedDelay voice3;
        sfloat voice3Pan = 0.f;
        ModulatedDelay voice4;
        sfloat voice4Pan = 0.f;
        ModulatedDelay voice5;
        sfloat voice5Pan = 0.f;
        ModulatedDelay voice6;
        sfloat voice6Pan = 0.f;

        sfloat dispersion;
        sfloat spread;
        sfloat feedback;
        sfloat timeMs;
        sfloat mix;
        sfloat tone;
        DisperseArrangement arrangement;

        sfloat modRateHz;
        sfloat modDepth;

        sfloat _lastOutL;
        sfloat _lastOutR;

        inline void updateSpread();
        inline void updateDispersion();
        inline void updateFeedback();
        inline void updateTone();
        inline void updateAllParams();
    public:
        void initialize(sfloat sampleRate,
                        sfloat mix,
                        sfloat dispersion,
                        sfloat spread,
                        sfloat time,
                        sfloat feedback,
                        sfloat tone,
                        sfloat modRateHz,
                        sfloat modDepth,
                        DisperseArrangement arrangement);

        virtual ~Disperse() {}

        void tick(sfloat L, sfloat R);

        sfloat lastOutL();
        sfloat lastOutR();

        void setTimeMs(sfloat timeMs);
        void setSpread(sfloat spread);
        void setFeedback(sfloat feedback);
        void setDispersion(sfloat dispersion);
        void setTone(sfloat tone);
        void setArrangement(DisperseArrangement arrangement);

    };
}
