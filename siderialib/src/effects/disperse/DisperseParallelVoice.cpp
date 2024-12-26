#include "effects/disperse/DisperseParallelVoice.h"

using namespace siderialib;

void DisperseParallelVoice::addVoice(siderialib::ModulatedDelay *delay) {
    if (_numActiveVoices >= DISPERSE_NUM_VOICES) {
        return;
    }

    _delays[_numActiveVoices] = delay;
    _numActiveVoices++;
}

void DisperseParallelVoice::clearVoices() {
    for (int i = 0; i < _numActiveVoices; i++) {
        _delays[i] = nullptr;
    }

    _numActiveVoices = 0;
}

void DisperseParallelVoice::initialize(sfloat samplingRate) {
    _lpf1L.initialize(samplingRate, BiquadType::LPF, samplingRate / 2.f, 1.0);
    _lpf1R.initialize(samplingRate, BiquadType::LPF, samplingRate / 2.f, 1.0);
    _lpf2L.initialize(samplingRate, BiquadType::LPF, samplingRate / 2.f, 1.0);
    _lpf2R.initialize(samplingRate, BiquadType::LPF, samplingRate / 2.f, 1.0);

    _hpf1L.initialize(samplingRate, BiquadType::HPF, 0.0, 1.0);
    _hpf1R.initialize(samplingRate, BiquadType::HPF, 0.0, 1.0);
    _hpf2L.initialize(samplingRate, BiquadType::HPF, 0.0, 1.0);
    _hpf2R.initialize(samplingRate, BiquadType::HPF, 0.0, 1.0);

    this->sampleRate = samplingRate;
}


void DisperseParallelVoice::tick(siderialib::sfloat L, siderialib::sfloat R) {
    sfloat parallelL = L;
    sfloat parallelR = R;

    for (int i = 0; i < _numActiveVoices; i++) {
        _delays[i]->tick(L, R);
        parallelL = _delays[i]->lastOutL();
        parallelR = _delays[i]->lastOutR();
    }

    _lastOutL = parallelL;
    _lastOutR = parallelR;

    if (_enableTone) {
        applyFilters();
    }
}

void DisperseParallelVoice::applyFilters() {
    if (useLpf) {
        _lastOutL = _lpf1L.tick(_lastOutL);
        _lastOutR = _lpf1R.tick(_lastOutR);
        _lastOutL = _lpf2L.tick(_lastOutL);
        _lastOutR = _lpf2R.tick(_lastOutR);
    }

    if (useHpf) {
        _lastOutL = _hpf1L.tick(_lastOutL);
        _lastOutR = _hpf1R.tick(_lastOutR);
        _lastOutL = _hpf2L.tick(_lastOutL);
        _lastOutR = _hpf2R.tick(_lastOutR);
    }
}

void DisperseParallelVoice::setTone(siderialib::sfloat tone) {
    if (tone > 0.5) {
        useHpf = true;
        useLpf = false;

        sfloat cutoff = (sampleRate / 2.f) * (tone - 0.5f) * 2.f;
        _hpf1L.setCutoff(cutoff);
        _hpf1R.setCutoff(cutoff);
        _hpf2L.setCutoff(cutoff);
        _hpf2R.setCutoff(cutoff);
    } else {
        useHpf = false;
        useLpf = true;

        sfloat cutoff = (sampleRate / 2.f) * tone * 2.f;
        _lpf1L.setCutoff(cutoff);
        _lpf1R.setCutoff(cutoff);
        _lpf2L.setCutoff(cutoff);
        _lpf2R.setCutoff(cutoff);
    }
}