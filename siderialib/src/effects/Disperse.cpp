#include "../../include/effects/Disperse.h"
#include "../../include/dsp/Math.h"

using namespace siderialib;

void Disperse::tick(siderialib::sfloat L, siderialib::sfloat R) {
    _lfo.tick();

    if (_arrangement == DisperseArrangement::FULL_PARALLEL) {
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

    applyWetFX();

    // at this point, _lastOutL/R are purely wet, so we need to mix in the dry
    _lastOutL = L * (1.f - _mix) + _lastOutL * _mix;
    _lastOutR = R * (1.f - _mix) + _lastOutR * _mix;
}

void Disperse::applyWetFX() {
    _lastOutL = _resampleL.tick(_lastOutL);
    _lastOutR = _resampleR.tick(_lastOutR);
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
    this->_dispersionPosition = position;
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

void Disperse::setPingPongType(siderialib::DispersePingPong pingPong) {
    this->_pingPong = pingPong;
    this->updatePingPong();
}

sfloat Disperse::lastOutR() const {
    return _lastOutR;
}

sfloat Disperse::lastOutL() const {
    return _lastOutL;
}

inline sfloat calcRandomPosition(sfloat harmonic, sfloat position, sfloat depth) {
    sfloat pos = harmonic * position;
    sfloat pan = triangleWave(pos - (sfloat)((int)pos)) * depth;
    return pan;
}

inline sfloat calcRandomUniformPosition(sfloat harmonic, sfloat position, sfloat depth) {
    return (calcRandomPosition(harmonic, position, depth) + 1.0f) / 2.0f;
}

void Disperse::updateDispersionAndPosition() {
    sfloat depth = (this->_timeMs * maxTimeDisperse) * this->_dispersion;

    _voice1.setDelayMs(this->_timeMs);
    _voice2.setDelayMs(this->_timeMs + calcRandomPosition(2.f, this->_dispersionPosition, depth));
    _voice3.setDelayMs(this->_timeMs + calcRandomPosition(4.f, this->_dispersionPosition, depth));
    _voice4.setDelayMs(this->_timeMs + calcRandomPosition(6.f, this->_dispersionPosition, depth));
    _voice5.setDelayMs(this->_timeMs + calcRandomPosition(8.f, this->_dispersionPosition, depth));
    _voice6.setDelayMs(this->_timeMs + calcRandomPosition(10.f, this->_dispersionPosition, depth));

}

void Disperse::updateFeedback() {
    _voice1.setFeedback(_feedback);
    _voice2.setFeedback(_feedback);
    _voice3.setFeedback(_feedback);
    _voice4.setFeedback(_feedback);
    _voice5.setFeedback(_feedback);
    _voice6.setFeedback(_feedback);
}

PingPongDirection randPingPongDirection(unsigned long *seed) {
    return siderialib::randBool(seed)
            ? siderialib::PingPongDirection::LEFT
            : siderialib::PingPongDirection::RIGHT;
}

void Disperse::updatePingPong() {
    bool enable = this->_pingPong != DispersePingPong::OFF;

    _voice1.enablePingPong(enable);
    _voice2.enablePingPong(enable);
    _voice3.enablePingPong(enable);
    _voice4.enablePingPong(enable);
    _voice5.enablePingPong(enable);
    _voice6.enablePingPong(enable);

    if (this->_pingPong == DispersePingPong::RANDOM) {
        // make pseudorandom seed
        auto seed = (unsigned long)(this->_spreadPosition * this->_timeMs * this->_dispersionPosition * 1234);

        _voice1.setPingPongDirection(randPingPongDirection(&seed));
        _voice2.setPingPongDirection(randPingPongDirection(&seed));
        _voice3.setPingPongDirection(randPingPongDirection(&seed));
        _voice4.setPingPongDirection(randPingPongDirection(&seed));
        _voice5.setPingPongDirection(randPingPongDirection(&seed));
        _voice6.setPingPongDirection(randPingPongDirection(&seed));
    } else {
        PingPongDirection direction = PingPongDirection::LEFT;

        _voice1.setPingPongDirection(direction);
        _voice2.setPingPongDirection(direction);
        _voice3.setPingPongDirection(direction);
        _voice4.setPingPongDirection(direction);
        _voice5.setPingPongDirection(direction);
        _voice6.setPingPongDirection(direction);
    }

}


void Disperse::updateSpread() {
    _voice1.setPan(calcRandomUniformPosition(1.f, this->_spreadPosition, this->_spread));
    _voice2.setPan(calcRandomUniformPosition(2.f, this->_spreadPosition, this->_spread));
    _voice3.setPan(calcRandomUniformPosition(3.f, this->_spreadPosition, this->_spread));
    _voice4.setPan(calcRandomUniformPosition(4.f, this->_spreadPosition, this->_spread));
    _voice5.setPan(calcRandomUniformPosition(5.f, this->_spreadPosition, this->_spread));
    _voice6.setPan(calcRandomUniformPosition(6.f, this->_spreadPosition, this->_spread));
}


void Disperse::updateMod() {
    this->_lfo.setRateHz(this->_modRateHz);
    this->_lfo.setDepth(this->_modDepth);
}

void Disperse::setResampleFactor(siderialib::sfloat ratio) {
    this->_resampleFactor = ratio;
    this->_resampleL.setResampleFactor(ratio);
    // don't need to recompute the up/downsample factors for the right channel, just use same as L
    this->_resampleR.setResampleFactor(_resampleL.getUpsampleFactor(),
                                       _resampleL.getDecimateFactor());

    printf("Resample factor: %f\n", ratio);
    printf("up: %d, down: %d\n", _resampleL.getUpsampleFactor(), _resampleL.getDecimateFactor());
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

    this->_resampleL.initialize();
    this->_resampleR.initialize();

    this->setMix(_mix);
    this->setDispersion(_dispersion);
    this->setSpread(_spread);
    this->setTimeMs(_timeMs);
    this->setFeedback(_feedback);
    this->setModRateHz(_modRateHz);
    this->setModDepth(_modDepth);
    this->setPosition(_dispersionPosition);
    this->setResampleFactor(_resampleFactor);
}

void Disperse::initialize(sfloat *voice1Buf,
                          sfloat *voice2Buf,
                          sfloat *voice3Buf,
                          sfloat *voice4Buf,
                          sfloat *voice5Buf,
                          sfloat *voice6Buf,
                          int bufLength,
                          sfloat *upsampleBufL,
                          sfloat *upsampleBufR,
                          int upsampleBufLen,
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

    this->_resampleL.initialize(upsampleBufL, upsampleBufLen);
    this->_resampleR.initialize(upsampleBufR, upsampleBufLen);

    this->setMix(_mix);
    this->setDispersion(_dispersion);
    this->setSpread(_spread);
    this->setTimeMs(_timeMs);
    this->setFeedback(_feedback);
    this->setModRateHz(_modRateHz);
    this->setModDepth(_modDepth);
    this->setPosition(_dispersionPosition);
    this->setResampleFactor(_resampleFactor);
    this->setPingPongType(_pingPong);
    //TODO: add tone control; above 0.5, HPF sweep, below 0.5 LPF sweep.
}
