#include "../../include/effects/Disperse.h"
#include "../../include/util/Random.h"


using namespace siderialib;

void Disperse::tick(siderialib::sfloat L, siderialib::sfloat R) {

    _lastOutL = 0.f;
    _lastOutR = 0.f;

    if (arrangement == DisperseArrangement::FULL_PARALLEL) {
        voice1.tick(L, R);

        _lastOutL += voice1.lastOutL();
        _lastOutR += voice1.lastOutR();

        voice2.tick(L, R);

        _lastOutL += voice2.lastOutL();
        _lastOutR += voice2.lastOutR();

        voice3.tick(L, R);

        _lastOutL += voice3.lastOutL();
        _lastOutR += voice3.lastOutR();

        voice4.tick(L, R);

        _lastOutL += voice4.lastOutL();
        _lastOutR += voice4.lastOutR();

        voice5.tick(L, R);

        _lastOutL += voice5.lastOutL();
        _lastOutR += voice5.lastOutR();

        voice6.tick(L, R);

        _lastOutL += voice6.lastOutL();
        _lastOutR += voice6.lastOutR();

//        _lastOutL /= 2.f;
//        _lastOutR /= 2.f;
    }

    // at this point, _lastOutL/R are purely wet, so we need to mix in the dry
//    _lastOutL = L * (1.f - mix) + _lastOutL * mix;
//    _lastOutR = R * (1.f - mix) + _lastOutR * mix;
}

void Disperse::setTimeMs(sfloat timeMs) {
    this->timeMs = timeMs;
    updateDispersion();
}

void Disperse::setSpread(sfloat spread) {
    this->spread = spread;
    updateSpread();
}

void Disperse::setFeedback(sfloat feedback) {
    this->feedback = feedback;
    updateFeedback();
}

void Disperse::setDispersion(sfloat dispersion) {
    this->dispersion = dispersion;
    updateDispersion();
}

void Disperse::setTone(sfloat tone) {
    this->tone = tone;
    updateTone();
}

void Disperse::setArrangement(DisperseArrangement arrangement) {
    this->arrangement = arrangement;
}

sfloat Disperse::lastOutR() {
    return _lastOutR;
}

sfloat Disperse::lastOutL() {
    return _lastOutL;
}

//static sfloat speedMs = 2000.0;
//static sfloat randPhasePerCallback = 0.f;
//static sfloat randPhase = 0.f;
//static sfloat invertedRandPhase = 1.f;
//
//static sfloat voice1StartTimeDisperseMs = 0.f;
//static sfloat voice1EndTimeDisperseMs = 0.f;
//static sfloat voice2TimeDisperseMs = 0.f;
//static sfloat voice3TimeDisperseMs = 0.f;
//static sfloat voice4TimeDisperseMs = 0.f;
//static sfloat voice5TimeDisperseMs = 0.f;
//static sfloat voice6TimeDisperseMs = 0.f;
//static sfloat voice1ModRateDisperse = 0.f;
//static sfloat voice2ModRateDisperse = 0.f;
//static sfloat voice3ModRateDisperse = 0.f;
//static sfloat voice4ModRateDisperse = 0.f;
//static sfloat voice5ModRateDisperse = 0.f;
//static sfloat voice6ModRateDisperse = 0.f;

static float baseHz = 0.2;
inline void Disperse::initializeRandomState() {
//    randPhase += randPhasePerCallback;
//
//    if (randPhase > 1.f) {
//        randPhase -= 1.f;
//        initializeRandomValues();
//    }
//
//    invertedRandPhase = 1.f - randPhase;

    random::s[0] = 123452346;
    random::s[1] = 567892346;
    random::s[2] = 2345672456;
    random::s[3] = 4567890212;

    this->voice1.mod2().setRateHz(baseHz + random::nextOscillatory() * baseHz / .02f);
    this->voice1.mod2().setPhase(random::nextUniform());

    this->voice2.mod2().setRateHz(baseHz + random::nextOscillatory() * baseHz / .02f);
    this->voice1.mod2().setPhase(random::nextUniform());

    this->voice3.mod2().setRateHz(baseHz + random::nextOscillatory() * baseHz / .02f);
    this->voice1.mod2().setPhase(random::nextUniform());

    this->voice4.mod2().setRateHz(baseHz + random::nextOscillatory() * baseHz / .02f);
    this->voice1.mod2().setPhase(random::nextUniform());

    this->voice5.mod2().setRateHz(baseHz + random::nextOscillatory() * baseHz / .02f);
    this->voice1.mod2().setPhase(random::nextUniform());

}

inline void Disperse::updateTime() {
    voice1.setDelayMs(this->timeMs);// + dispersionMs(voice1StartTimeDisperseMs, voice1EndTimeDisperseMs) * this->dispersion);
    voice2.setDelayMs(this->timeMs);// + voice2TimeDisperseMs * scalar);
    voice3.setDelayMs(this->timeMs);// + voice3TimeDisperseMs * scalar);
    voice4.setDelayMs(this->timeMs);// + voice4TimeDisperseMs * scalar);
    voice5.setDelayMs(this->timeMs);// + voice5TimeDisperseMs * scalar);
    voice6.setDelayMs(this->timeMs);// + voice6TimeDisperseMs * scalar);
}

inline void Disperse::updateDispersion() {

    voice1.mod2().setDepth(this->dispersion * maxTimeDisperse * this->timeMs * sampleRate);
    voice1.mod2().setDepth(this->dispersion * maxTimeDisperse * this->timeMs * sampleRate);
    voice1.mod2().setDepth(this->dispersion * maxTimeDisperse * this->timeMs * sampleRate);
    voice1.mod2().setDepth(this->dispersion * maxTimeDisperse * this->timeMs * sampleRate);
    voice1.mod2().setDepth(this->dispersion * maxTimeDisperse * this->timeMs * sampleRate);
    voice1.mod2().setDepth(this->dispersion * maxTimeDisperse * this->timeMs * sampleRate);

}

inline void Disperse::updateFeedback() {
    voice1.setFeedback(feedback);
    voice2.setFeedback(feedback);
}

inline void Disperse::updateTone() {
    // todo
}

inline void Disperse::updateSpread() {
    random::s[0] = 4684568345;
    random::s[1] = 23462346;
    random::s[2] = 293486720394;
    random::s[3] = 7345734562;

    voice1Pan = random::nextOscillatory() * this->spread;
    voice2Pan = random::nextOscillatory() * this->spread;
}

inline void Disperse::updateAllParams() {
    updateDispersion();
    updateSpread();
    updateTone();
    updateFeedback();
    updateTime();
}

void Disperse::initialize(sfloat sampleRate,
                          sfloat mix,
                          sfloat dispersion,
                          sfloat spread,
                          sfloat timeMs,
                          sfloat feedback,
                          sfloat tone,
                          sfloat modRateHz,
                          sfloat modDepth,
                          DisperseArrangement arrangement) {

    this->sampleRate = sampleRate;

    int maxDelaySamps = std::ceil((maxDelayMs/1000.0) * sampleRate);
    this->voice1.initialize(sampleRate, maxDelaySamps);
    this->voice2.initialize(sampleRate, maxDelaySamps);
    this->voice3.initialize(sampleRate, maxDelaySamps);
    this->voice4.initialize(sampleRate, maxDelaySamps);
    this->voice5.initialize(sampleRate, maxDelaySamps);
    this->voice6.initialize(sampleRate, maxDelaySamps);

    this->initializeParams(mix, dispersion, spread, timeMs, feedback, tone, modRateHz, modDepth, arrangement);

}

void Disperse::initialize(sfloat *voice1Buf,
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
                          sfloat timeMs,
                          sfloat feedback,
                          sfloat tone,
                          sfloat modRateHz,
                          sfloat modDepth,
                          DisperseArrangement arrangement) {
    this->sampleRate = sampleRate;

    this->voice1.initialize(sampleRate, voice1Buf, bufLength);
    this->voice2.initialize(sampleRate, voice2Buf, bufLength);
    this->voice3.initialize(sampleRate, voice3Buf, bufLength);
    this->voice4.initialize(sampleRate, voice4Buf, bufLength);
    this->voice5.initialize(sampleRate, voice5Buf, bufLength);
    this->voice6.initialize(sampleRate, voice6Buf, bufLength);

    this->initializeParams(mix, dispersion, spread, timeMs, feedback, tone, modRateHz, modDepth, arrangement);
}

inline void Disperse::initializeParams(sfloat mix, sfloat dispersion, sfloat spread, sfloat timeMs, sfloat feedback,
                                       sfloat tone, sfloat modRateHz, sfloat modDepth, DisperseArrangement arrangement) {

    this->initializeRandomState();

    this->setAllParams(mix, dispersion, spread, timeMs, feedback, tone, modRateHz, modDepth, arrangement);

}

inline void Disperse::setAllParams(sfloat mix, sfloat dispersion, sfloat spread, sfloat timeMs, sfloat feedback,
                       sfloat tone, sfloat modRateHz, sfloat modDepth, DisperseArrangement arrangement) {
    this->timeMs = timeMs;
    this->mix = mix;
    this->dispersion = dispersion;
    this->spread = spread;
    this->feedback = feedback;
    this->tone = tone;
    this->modRateHz = modRateHz;
    this->modDepth = modDepth;

    this->arrangement = arrangement;

    this->updateAllParams();
}
