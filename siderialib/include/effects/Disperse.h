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

        inline void updateRandomValues();
    public:
        void initialize(sfloat *voice1Buf,
                        sfloat *voice2Buf,
                        sfloat *voice3Buf,
                        sfloat *voice4Buf,
                        sfloat *voice5Buf,
                        sfloat *voice6Buf,
                        int bufLength,
                        sfloat sampleRate,
                        sfloat mix,
                        sfloat dispersion,
                        sfloat spread,
                        sfloat time,
                        sfloat feedback,
                        sfloat tone,
                        sfloat modRateHz,
                        sfloat modDepth,
                        DisperseArrangement arrangement);
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
        inline sfloat getTimeMs() { return timeMs; };
        void setSpread(sfloat spread);
        inline sfloat getSpread() { return spread; };
        void setFeedback(sfloat feedback);
        inline sfloat getFeedback() { return feedback; };
        void setDispersion(sfloat dispersion);
        inline sfloat getDispersion() { return dispersion; };
        void setTone(sfloat tone);
        inline sfloat getTone() { return tone; };
        void setArrangement(DisperseArrangement arrangement);
        inline DisperseArrangement getArrangement() { return arrangement; };

        inline void setAllParams(sfloat mix,
                          sfloat dispersion,
                          sfloat spread,
                          sfloat time,
                          sfloat feedback,
                          sfloat tone,
                          sfloat modRateHz,
                          sfloat modDepth,
                          DisperseArrangement arrangement);

    };
}
