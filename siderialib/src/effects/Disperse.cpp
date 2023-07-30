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

        _lastOutL /= 2.f;
        _lastOutR /= 2.f;
    }

    // at this point, _lastOutL/R are purely wet, so we need to mix in the dry
    _lastOutL = L * (1.f - mix) + _lastOutL * mix;
    _lastOutR = R * (1.f - mix) + _lastOutR * mix;
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

void Disperse::updateDispersion() {
    random::s[0] = 123452346;
    random::s[1] = 567892346;
    random::s[2] = 2345672456;
    random::s[3] = 4567890212;

    sfloat maxDispersionTimeMs = this->dispersion * maxTimeDisperse * this->timeMs;

    sfloat voice1TimeDisperseMs = (random::nextUniform() * 2 - 1) * maxDispersionTimeMs;
    sfloat voice2TimeDisperseMs = (random::nextUniform() * 2 - 1) * maxDispersionTimeMs;
    sfloat voice1ModRateDisperse = (random::nextUniform() * 2 - 1) * maxModRateDisperse;
    sfloat voice2ModRateDisperse = (random::nextUniform() * 2 - 1) * maxModRateDisperse;

    voice1.setDelayMs(this->timeMs + voice1TimeDisperseMs);
    voice2.setDelayMs(this->timeMs + voice2TimeDisperseMs);

    voice1.mod().setRateHz(this->modRateHz + voice1ModRateDisperse);
    voice2.mod().setRateHz(this->modRateHz + voice2ModRateDisperse);
}

void Disperse::updateFeedback() {
    voice1.setFeedback(feedback);
    voice2.setFeedback(feedback);
}

void Disperse::updateTone() {
    // todo
}

void Disperse::updateSpread() {
    random::s[0] = 4684568345;
    random::s[1] = 23462346;
    random::s[2] = 293486720394;
    random::s[3] = 7345734562;

    voice1Pan = (random::nextUniform() * 2 - 1) * this->spread;
    voice2Pan = (random::nextUniform() * 2 - 1) * this->spread;
}
