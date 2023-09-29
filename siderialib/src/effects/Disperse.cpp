#include "../../include/effects/Disperse.h"
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

void Disperse::setDownsampleFactor(int ratio) {
    this->_downsampleFactor = ratio;
}

sfloat Disperse::lastOutR() const {
    return _lastOutR;
}

sfloat Disperse::lastOutL() const {
    return _lastOutL;
}

inline sfloat calcVoicePosition(sfloat harmonic, sfloat position, sfloat depth) {
    sfloat pos = harmonic * position;
    return triangleWave(pos - (sfloat)((int)pos)) * depth;
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

void Disperse::updatePingPong() {
    _voice1.enablePingPong(_enablePingPong);
    _voice2.enablePingPong(_enablePingPong);
    _voice3.enablePingPong(_enablePingPong);
    _voice4.enablePingPong(_enablePingPong);
    _voice5.enablePingPong(_enablePingPong);
    _voice6.enablePingPong(_enablePingPong);

}


void Disperse::updateSpread() {
    // todo
}


void Disperse::updateMod() {
    this->_lfo.setRateHz(this->_modRateHz);
    this->_lfo.setDepth(this->_modDepth);
}

void Disperse::initialize(sfloat sampleRate) {
    this->_sampleRate = sampleRate;
    _lfo.initialize(sampleRate);
    _postLpfL.initialize(_sampleRate, BiquadType::LPF, 8000.0, 0.7);
    _postLpfR.initialize(_sampleRate, BiquadType::LPF, 8000.0, 0.7);

    int maxDelaySamps = std::ceil((maxDelayMs/1000.0) * _sampleRate);
    this->_voice1.initialize(&_lfo, _sampleRate, maxDelaySamps);
    this->_voice1.enableLpf(false);
    this->_voice2.initialize(&_lfo, _sampleRate, maxDelaySamps);
    this->_voice2.enableLpf(false);
    this->_voice3.initialize(&_lfo, _sampleRate, maxDelaySamps);
    this->_voice3.enableLpf(false);
    this->_voice4.initialize(&_lfo, _sampleRate, maxDelaySamps);
    this->_voice4.enableLpf(false);
    this->_voice5.initialize(&_lfo, _sampleRate, maxDelaySamps);
    this->_voice5.enableLpf(false);
    this->_voice6.initialize(&_lfo, _sampleRate, maxDelaySamps);
    this->_voice6.enableLpf(false);

    this->setMix(_mix);
    this->setDispersion(_dispersion);
    this->setSpread(_spread);
    this->setTimeMs(_timeMs);
    this->setFeedback(_feedback);
    this->setModRateHz(_modRateHz);
    this->setModDepth(_modDepth);
    this->setPosition(_position);
    this->setDownsampleFactor(_downsampleFactor);

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
    _postLpfL.initialize(_sampleRate, BiquadType::LPF, 8000.0f, 0.7f);
    _postLpfR.initialize(_sampleRate, BiquadType::LPF, 8000.0f, 0.7f);

    this->_voice1.initialize(&_lfo, _sampleRate, voice1Buf, bufLength);
    this->_voice1.enableLpf(false);
    this->_voice2.initialize(&_lfo, _sampleRate, voice2Buf, bufLength);
    this->_voice2.enableLpf(false);
    this->_voice3.initialize(&_lfo, _sampleRate, voice3Buf, bufLength);
    this->_voice3.enableLpf(false);
    this->_voice4.initialize(&_lfo, _sampleRate, voice4Buf, bufLength);
    this->_voice4.enableLpf(false);
    this->_voice5.initialize(&_lfo, _sampleRate, voice5Buf, bufLength);
    this->_voice5.enableLpf(false);
    this->_voice6.initialize(&_lfo, _sampleRate, voice6Buf, bufLength);
    this->_voice6.enableLpf(false);

    this->setMix(_mix);
    this->setDispersion(_dispersion);
    this->setSpread(_spread);
    this->setTimeMs(_timeMs);
    this->setFeedback(_feedback);
    this->setModRateHz(_modRateHz);
    this->setModDepth(_modDepth);
    this->setPosition(_position);
    this->setDownsampleFactor(_downsampleFactor);

}



