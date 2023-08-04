#include "../../include/effects/Disperse.h"
#include "../../include/util/Random.h"
#include "../../include/dsp/Math.h"

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

        _lastOutL /= 6.f;
        _lastOutR /= 6.f;
    }

    // at this point, _lastOutL/R are purely wet, so we need to mix in the dry
//    _lastOutL = L * (1.f - mix) + _lastOutL * mix;
//    _lastOutR = R * (1.f - mix) + _lastOutR * mix;
}

void Disperse::setTimeMs(sfloat timeMs) {
    this->timeMs = timeMs;
    updateDispersionAndPosition();
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
    updateDispersionAndPosition();
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

inline sfloat calcVoicePosition(sfloat harmonic, sfloat position, sfloat depth) {
    return triangleWave(fmod(harmonic * position, 1.f)) * depth;
}

void Disperse::updateDispersionAndPosition() {

    sfloat depth = this->timeMs * this->dispersion / 2.f;

    printf("%f\n", this->timeMs);
    printf("%f\n", this->timeMs + calcVoicePosition(2.f, this->position, depth));
    printf("%f\n", this->timeMs + calcVoicePosition(4.f, this->position, depth));
    printf("%f\n", this->timeMs + calcVoicePosition(6.f, this->position, depth));
    printf("%f\n", this->timeMs + calcVoicePosition(8.f, this->position, depth));
    printf("%f\n", this->timeMs + calcVoicePosition(10.f, this->position, depth));
    voice1.setDelayMs(this->timeMs);
    voice2.setDelayMs(this->timeMs + calcVoicePosition(2.f, this->position, depth));
    voice3.setDelayMs(this->timeMs + calcVoicePosition(4.f, this->position, depth));
    voice4.setDelayMs(this->timeMs + calcVoicePosition(6.f, this->position, depth));
    voice5.setDelayMs(this->timeMs + calcVoicePosition(8.f, this->position, depth));
    voice6.setDelayMs(this->timeMs + calcVoicePosition(10.f, this->position, depth));

}

void Disperse::updateFeedback() {
    voice1.setFeedback(feedback);
    voice2.setFeedback(feedback);
    voice3.setFeedback(feedback);
    voice4.setFeedback(feedback);
    voice5.setFeedback(feedback);
    voice6.setFeedback(feedback);
}

void Disperse::updateTone() {
    // todo
}

void Disperse::updateSpread() {
    // todo
}

void Disperse::updateAllParams() {
    updateDispersionAndPosition();
    updateSpread();
    updateTone();
    updateFeedback();
}

void Disperse::initialize(sfloat sampleRate) {

    int maxDelaySamps = std::ceil((maxDelayMs/1000.0) * sampleRate);
    this->voice1.initialize(sampleRate, maxDelaySamps);
    this->voice2.initialize(sampleRate, maxDelaySamps);
    this->voice3.initialize(sampleRate, maxDelaySamps);
    this->voice4.initialize(sampleRate, maxDelaySamps);
    this->voice5.initialize(sampleRate, maxDelaySamps);
    this->voice6.initialize(sampleRate, maxDelaySamps);

    this->_initialize();
    this->setAllParams(mix, dispersion, spread, timeMs, feedback, tone, modRateHz, modDepth, position, arrangement);

}

void Disperse::initialize(sfloat *voice1Buf,
                          sfloat *voice2Buf,
                          sfloat *voice3Buf,
                          sfloat *voice4Buf,
                          sfloat *voice5Buf,
                          sfloat *voice6Buf,
                          int bufLength,
                          sfloat sampleRate) {
    this->sampleRate = sampleRate;

    this->voice1.initialize(sampleRate, voice1Buf, bufLength);
    this->voice2.initialize(sampleRate, voice2Buf, bufLength);
    this->voice3.initialize(sampleRate, voice3Buf, bufLength);
    this->voice4.initialize(sampleRate, voice4Buf, bufLength);
    this->voice5.initialize(sampleRate, voice5Buf, bufLength);
    this->voice6.initialize(sampleRate, voice6Buf, bufLength);

    this->_initialize();
    this->setAllParams(mix, dispersion, spread, timeMs, feedback, tone, modRateHz, modDepth, position, arrangement);

}

void Disperse::_initialize() {
}


void Disperse::setAllParams(sfloat mix, sfloat dispersion, sfloat spread, sfloat timeMs, sfloat feedback,
                       sfloat tone, sfloat modRateHz, sfloat modDepth, sfloat position, DisperseArrangement arrangement) {

    this->timeMs = timeMs;
    this->mix = mix;
    this->dispersion = dispersion;
    this->spread = spread;
    this->feedback = feedback;
    this->tone = tone;
    this->modRateHz = modRateHz;
    this->modDepth = modDepth;
    this->position = position;

    this->arrangement = arrangement;

    this->updateAllParams();
}
