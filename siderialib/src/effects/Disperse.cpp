#include "../../include/effects/Disperse.h"
#include "../../include/util/Random.h"
#include "../../include/dsp/Math.h"

using namespace siderialib;

void Disperse::tick(siderialib::sfloat L, siderialib::sfloat R) {
    _lfo.tick();



    if (_arrangement == DisperseArrangement::FULL_PARALLEL && _clockTick == 0) {
        _lastOutL = 0.f;
        _lastOutR = 0.f;

        _voice1.tick(L, R);

        _lastOutL += _voice1.lastOutL();
        _lastOutR += _voice1.lastOutR();

        _voice2.tick(L, R);

        _lastOutL += _voice2.lastOutL();
        _lastOutR += _voice2.lastOutR();

        _voice3.tick(L, R);

        _lastOutL += _voice3.lastOutL();
        _lastOutR += _voice3.lastOutR();

        _voice4.tick(L, R);

        _lastOutL += _voice4.lastOutL();
        _lastOutR += _voice4.lastOutR();

        _voice5.tick(L, R);

        _lastOutL += _voice5.lastOutL();
        _lastOutR += _voice5.lastOutR();

        _voice6.tick(L, R);

        _lastOutL += _voice6.lastOutL();
        _lastOutR += _voice6.lastOutR();

        _lastOutL /= 6.f;
        _lastOutR /= 6.f;
    }

    if (_clockTick == 0) {
        _clockTick = _downsampleFactor;
    } else {
        _clockTick--;
    }

    // at this point, _lastOutL/R are purely wet, so we need to mix in the dry
    _lastOutL = L * (1.f - _mix) + _lastOutL * _mix;
    _lastOutR = R * (1.f - _mix) + _lastOutR * _mix;
}

void Disperse::setTimeMs(sfloat timeMs) {
    this->_timeMs = timeMs;
    updateDispersionAndPosition();
}

void Disperse::setSpread(sfloat spread) {
    this->_spread = spread;
    updateSpread();
}

void Disperse::setFeedback(sfloat feedback) {
    this->_feedback = feedback;
    updateFeedback();
}

void Disperse::setDispersion(sfloat dispersion) {
    this->_dispersion = dispersion;
    updateDispersionAndPosition();
}

void Disperse::setPosition(sfloat position) {
    this->_position = position;
    updateDispersionAndPosition();
}

void Disperse::setMix(sfloat mix) {
    this->_mix = mix;
}

void Disperse::setModDepth(sfloat depth) {
    this->_modDepth = depth;
    this->updateMod();
}

void Disperse::setModRateHz(sfloat modRateHz) {
    this->_modRateHz = modRateHz;
    this->updateMod();
}


void Disperse::setTone(sfloat tone) {
    this->_tone = tone;
    updateTone();
}

void Disperse::setDownsampleFactor(int ratio) {
    this->_downsampleFactor = ratio;
}

void Disperse::setArrangement(DisperseArrangement arrangement) {
    this->_arrangement = arrangement;
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

    sfloat depth = this->_timeMs * this->_dispersion / 2.f;

    _voice1.setDelayMs(this->_timeMs);
    _voice2.setDelayMs(this->_timeMs + calcVoicePosition(2.f, this->_position, depth));
    _voice3.setDelayMs(this->_timeMs + calcVoicePosition(4.f, this->_position, depth));
    _voice4.setDelayMs(this->_timeMs + calcVoicePosition(6.f, this->_position, depth));
    _voice5.setDelayMs(this->_timeMs + calcVoicePosition(8.f, this->_position, depth));
    _voice6.setDelayMs(this->_timeMs + calcVoicePosition(10.f, this->_position, depth));

}

void Disperse::updateFeedback() {
    _voice1.setFeedback(_feedback);
    _voice2.setFeedback(_feedback);
    _voice3.setFeedback(_feedback);
    _voice4.setFeedback(_feedback);
    _voice5.setFeedback(_feedback);
    _voice6.setFeedback(_feedback);
}

void Disperse::updateTone() {
    _voice1.setLpfParams(_tone * _sampleRate * 0.5, 1.0, 0.0);
    _voice2.setLpfParams(_tone * _sampleRate * 0.5, 1.0, 0.0);
    _voice3.setLpfParams(_tone * _sampleRate * 0.5, 1.0, 0.0);
    _voice4.setLpfParams(_tone * _sampleRate * 0.5, 1.0, 0.0);
    _voice5.setLpfParams(_tone * _sampleRate * 0.5, 1.0, 0.0);
    _voice6.setLpfParams(_tone * _sampleRate * 0.5, 1.0, 0.0);
}

void Disperse::updateSpread() {
    // todo
}


void Disperse::updateMod() {
    this->_lfo.setRateHz(this->_modRateHz);
    this->_lfo.setDepth(this->_modDepth);
//    _voice1.mod().setRateHz(this->_modRateHz);
//    _voice1.mod().setDepth(this->_modDepth * modDepthSamps);
//    _voice2.mod().setRateHz(this->_modRateHz);
//    _voice2.mod().setDepth(this->_modDepth * modDepthSamps);
//    _voice3.mod().setRateHz(this->_modRateHz);
//    _voice3.mod().setDepth(this->_modDepth * modDepthSamps);
//    _voice4.mod().setRateHz(this->_modRateHz);
//    _voice4.mod().setDepth(this->_modDepth * modDepthSamps);
//    _voice5.mod().setRateHz(this->_modRateHz);
//    _voice5.mod().setDepth(this->_modDepth * modDepthSamps);
//    _voice6.mod().setRateHz(this->_modRateHz);
//    _voice6.mod().setDepth(this->_modDepth * modDepthSamps);

}

void Disperse::updateAllParams() {
    updateDispersionAndPosition();
    updateMod();
    updateSpread();
    updateTone();
    updateFeedback();
}

void Disperse::initialize(sfloat sampleRate) {
    this->_sampleRate = sampleRate;
    _lfo.initialize(sampleRate);

    int maxDelaySamps = std::ceil((maxDelayMs/1000.0) * _sampleRate);
    this->_voice1.initialize(&_lfo, _sampleRate, maxDelaySamps);
    this->_voice1.enableLpf(true);
    this->_voice2.initialize(&_lfo, _sampleRate, maxDelaySamps);
    this->_voice2.enableLpf(true);
    this->_voice3.initialize(&_lfo, _sampleRate, maxDelaySamps);
    this->_voice3.enableLpf(true);
    this->_voice4.initialize(&_lfo, _sampleRate, maxDelaySamps);
    this->_voice4.enableLpf(true);
    this->_voice5.initialize(&_lfo, _sampleRate, maxDelaySamps);
    this->_voice5.enableLpf(true);
    this->_voice6.initialize(&_lfo, _sampleRate, maxDelaySamps);
    this->_voice6.enableLpf(true);

    this->setAllParams(_mix, _dispersion, _spread, _timeMs, _feedback, _tone, _modRateHz, _modDepth, _position, _downsampleFactor, _arrangement);

}

void Disperse::initialize(sfloat *voice1Buf,
                          sfloat *voice2Buf,
                          sfloat *voice3Buf,
                          sfloat *voice4Buf,
                          sfloat *voice5Buf,
                          sfloat *voice6Buf,
                          int bufLength,
                          sfloat sampleRate) {
    this->_sampleRate = sampleRate;
    _lfo.initialize(sampleRate);

    this->_voice1.initialize(&_lfo, _sampleRate, voice1Buf, bufLength);
    this->_voice1.enableLpf(true);
    this->_voice2.initialize(&_lfo, _sampleRate, voice2Buf, bufLength);
    this->_voice2.enableLpf(true);
    this->_voice3.initialize(&_lfo, _sampleRate, voice3Buf, bufLength);
    this->_voice3.enableLpf(true);
    this->_voice4.initialize(&_lfo, _sampleRate, voice4Buf, bufLength);
    this->_voice4.enableLpf(true);
    this->_voice5.initialize(&_lfo, _sampleRate, voice5Buf, bufLength);
    this->_voice5.enableLpf(true);
    this->_voice6.initialize(&_lfo, _sampleRate, voice6Buf, bufLength);
    this->_voice6.enableLpf(true);

    this->setAllParams(_mix, _dispersion, _spread, _timeMs, _feedback, _tone, _modRateHz, _modDepth, _position, _downsampleFactor, _arrangement);

}


void Disperse::setAllParams(sfloat mix, sfloat dispersion, sfloat spread, sfloat timeMs, sfloat feedback,
                       sfloat tone, sfloat modRateHz, sfloat modDepth, sfloat position, int downsampleFactor, DisperseArrangement arrangement) {

    this->_timeMs = timeMs;
    this->_mix = mix;
    this->_dispersion = dispersion;
    this->_spread = spread;
    this->_feedback = feedback;
    this->_tone = tone;
    this->_modRateHz = modRateHz;
    this->_modDepth = modDepth;
    this->_position = position;
    this->_downsampleFactor = downsampleFactor;

    this->_arrangement = arrangement;

    this->updateAllParams();
}
