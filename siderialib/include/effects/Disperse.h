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

    class Disperse : public StereoEffect {
    private:
        ModulatedDelay voice1;
        sfloat voice1Pan = 0.f;
        ModulatedDelay voice2;
        sfloat voice2Pan = 0.f;

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
        void initialize(sfloat mix, sfloat dispersion, sfloat spread, sfloat feedback, sfloat tone, DisperseArrangement arrangement);

        void tick(Buffer& buf) override final;
        void tick(Buffer& in, Buffer& out) override final;

        void tick(sfloat L, sfloat R) override final;

        sfloat lastOutL() override final;
        sfloat lastOutR() override final;

        void setTimeMs(sfloat timeMs);
        void setSpread(sfloat spread);
        void setFeedback(sfloat feedback);
        void setDispersion(sfloat dispersion);
        void setTone(sfloat tone);
        void setArrangement(DisperseArrangement arrangement);

    };
}
