#include "../../include/effects/Disperse.h"
#include "../../include/dsp/Math.h"

using namespace siderialib;

void Disperse::tick(siderialib::sfloat L, siderialib::sfloat R) {
    _lfo.tick();

    _lastOutL = 0.f;
    _lastOutR = 0.f;

    applyVoices(L, R);
    applyWetFX();

    // at this point, _lastOutL/R are purely wet, so we need to mix in the dry
    _lastOutL = L * (1.f - _mix) + _lastOutL * _mix;
    _lastOutR = R * (1.f - _mix) + _lastOutR * _mix;
}

void Disperse::applyVoices(sfloat L, sfloat R) {
    for (int i = 0; i < DISPERSE_NUM_VOICES; i++) {
        _voices[i].tick(L, R);
        _lastOutL += _voices[i].lastOutL();
        _lastOutR += _voices[i].lastOutR();
    }
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

void Disperse::updateTone() {
    for (int i = 0; i < DISPERSE_NUM_VOICES; i++) {
        _voices[i].setTone(_tone);
    }
}

void Disperse::setTone(sfloat tone) {
    this->_tone = tone;
    updateTone();
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
    sfloat depth = (this->_timeMs * DISPERSE_MAX_TIME) * this->_dispersion;

    for (int i = 0; i < DISPERSE_NUM_VOICES; i++) {
        _delays[i].setDelayMs(this->_timeMs + calcRandomPosition((sfloat)i * 2.f, this->_dispersionPosition, depth));
    }
}

void Disperse::updateFeedback() {
    for (int i = 0; i < DISPERSE_NUM_VOICES; i++) {
        _delays[i].setFeedback(_feedback);
    }
}

PingPongDirection randPingPongDirection(unsigned long *seed) {
    return siderialib::randBool(seed)
            ? siderialib::PingPongDirection::LEFT
            : siderialib::PingPongDirection::RIGHT;
}

void Disperse::updatePingPong() {
    bool enable = this->_pingPong != DispersePingPong::OFF;

    for (int i = 0; i < DISPERSE_NUM_VOICES; i++) {
        _delays[i].enablePingPong(enable);
    }

    if (this->_pingPong == DispersePingPong::RANDOM) {
        // make pseudorandom seed
        auto seed = (unsigned long)(this->_spreadPosition * this->_timeMs * this->_dispersionPosition * 1234);

        for (int i = 0; i < DISPERSE_NUM_VOICES; i++) {
            _delays[i].setPingPongDirection(randPingPongDirection(&seed));
        }
    } else {
        PingPongDirection direction = PingPongDirection::LEFT;

        for (int i = 0; i < DISPERSE_NUM_VOICES; i++) {
            _delays[i].setPingPongDirection(direction);
        }
    }

}


void Disperse::updateSpread() {
    for (int i = 0; i < DISPERSE_NUM_VOICES; i++) {
        _delays[i].setPan(calcRandomUniformPosition((sfloat)i, this->_spreadPosition, this->_spread));
    }
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
}

void Disperse::initialize(sfloat sampleRate) {
    this->_sampleRate = sampleRate;
    _lfo.initialize(sampleRate);

    int maxDelaySamps = std::ceil((DISPERSE_MAX_DELAY_MS/1000.0) * _sampleRate);
    for (int i = 0; i < DISPERSE_NUM_VOICES; i++) {
        _delays[i].initialize(&_lfo, _sampleRate, maxDelaySamps);
        _voices[i].initialize(_sampleRate);
        _voices[i].enableTone(false);
    }

    setArrangement(DisperseArrangement::FULL_PARALLEL);

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

void Disperse::initialize(sfloat *voiceBufs[DISPERSE_NUM_VOICES],
                          int bufLength,
                          sfloat *upsampleBufL,
                          sfloat *upsampleBufR,
                          int upsampleBufLen,
                          sfloat sampleRate) {
    this->_sampleRate = sampleRate;
    _lfo.initialize(sampleRate);

    for (int i = 0; i < DISPERSE_NUM_VOICES; i++) {
        _delays[i].initialize(&_lfo, _sampleRate, voiceBufs[i], bufLength);
        _voices[i].initialize(_sampleRate);
        _voices[i].enableTone(false);
    }

    setArrangement(DisperseArrangement::FULL_PARALLEL);

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

void Disperse::setArrangement(DisperseArrangement arrangement) {
    // removes delays from all voices
    clearVoices();

    switch (arrangement) {
        case DisperseArrangement::FULL_PARALLEL:
            for (int i = 0; i < DISPERSE_NUM_VOICES; i++) {
                _voices[i].addVoice(&_delays[i]);
            }
            break;

        case DisperseArrangement::FULL_SERIAL:
            for (int i = 0; i < DISPERSE_NUM_VOICES; i++) {
                _voices[0].addVoice(&_delays[i]);
            }
            break;
    }

}

void Disperse::clearVoices() {
    for (int i = 0; i < DISPERSE_NUM_VOICES; i++) {
        _voices[i].clearVoices();
    }
}
