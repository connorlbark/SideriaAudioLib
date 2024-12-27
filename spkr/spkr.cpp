#include <iostream>

#include "AudioFile.h"
#include <vector>

#include "../siderialib/include/siderialib.h"
#include "../siderialib/include/effects/delay/ModulatedDelay.h"
#include "../siderialib/include/effects/Disperse.h"

void applyDelay(std::vector<std::vector<double>> in, std::vector<std::vector<double>>& out) {
	siderialib::ModulatedDelay delay;

    siderialib::LFO lfo;
    lfo.initialize(44100.0f);
	delay.initialize(&lfo, 44100.f, 44100 * 10);

    delay.setDelayMs(500.0f);
    delay.setFeedback(0.0f);

    delay.setMix(1.0f);

	for (int i = 0; i < in.at(0).size(); i++) {

        siderialib::sfloat L = (float)in.at(0).at(i);

        delay.tick(L, L);

		out.at(0).at(i) = delay.lastOutL();
		out.at(1).at(i) = delay.lastOutR();

	}
}


void apply(std::vector<std::vector<double>> in, std::vector<std::vector<double>>& out) {
    siderialib::Disperse disperse;

    float sampleRate = 44100.f;
    float mix = .2f;
    float timeMs = 300.0f;
    float dispersion = 0.5f;
    float spread = 1.0f;
    float feedback = 0.8f;
    float tone = 0.1f;
    float modRateHz = 2.0f;
    float modDepth = 0.3f;
    float position = .323f;
    float resampleFactor = .2;

    siderialib::DisperseArrangement arrangement = siderialib::DisperseArrangement::FULL_PARALLEL;
    disperse.initialize(sampleRate);

    disperse.setMix(mix);
    disperse.setDispersion(dispersion);
    disperse.setSpread(spread);
    disperse.setTimeMs(timeMs);
    disperse.setFeedback(feedback);
    disperse.setModRateHz(modRateHz);
    disperse.setModDepth(modDepth);
    disperse.setPosition(position);
    disperse.setResampleFactor(resampleFactor);
    disperse.setTone(tone);

    disperse.setPingPongType(siderialib::DispersePingPong::OFF);

    // otherwise there will be a weird sound at the start
    for (int i = 0; i < sampleRate; i++) {
        disperse.tick(0.0f, 0.0f);
    }

    for (int i = 0; i < in.at(0).size(); i++) {

        float L = (float)in.at(0).at(i);

        disperse.tick(L, L);

        out.at(0).at(i) = disperse.lastOutL();
        out.at(1).at(i) = disperse.lastOutR();

    }
}

void applyFilter(std::vector<std::vector<double>> in, std::vector<std::vector<double>>& out) {
    siderialib::BiquadFilter filter1;
    siderialib::BiquadFilter filter2;

    filter1.initialize(44100.0, siderialib::BiquadType::LPF, 1000.0, 0.5);
    filter1.setParams(8000.0, 0.7, 12.0);

    filter2.initialize(44100.0, siderialib::BiquadType::LPF, 1000.0, 0.5);
    filter2.setParams(8000.0, 0.7, 12.0);
    for (int i = 0; i < in.at(0).size(); i++) {

        siderialib::sfloat L = (siderialib::sfloat)in.at(0).at(i);

        float filtered = filter1.tick(filter2.tick(L));

        out.at(0).at(i) = filtered;
        out.at(1).at(i) = filtered;

    }
}

void applyResample(std::vector<std::vector<double>> in, std::vector<std::vector<double>>& out) {
    siderialib::VariableResample resample;
    resample.initialize();
    resample.setResampleFactor(0.28);

    for (int i = 0; i < in.at(0).size(); i++) {

        siderialib::sfloat L = (siderialib::sfloat)in.at(0).at(i);

        float val = resample.tick(L);

        out.at(0).at(i) = val;
        out.at(1).at(i) = val;

    }
}

std::vector<std::vector<double>> sinWave(int samplingRate, int samples, double frequency) {

    std::vector<std::vector<double>> out = std::vector<std::vector<double>>(2, std::vector<double>(samples));
    for (int i = 0; i < samples; i++) {
        out.at(0).at(i) = sin(2.0 * M_PI * frequency * i / samplingRate);
        out.at(1).at(i) = sin(2.0 * M_PI * frequency * i / samplingRate);
    }
    return out;


}


int main(int argc, char *argv[]) {

    if (argc != 3) {
        std::cout << "Use:\n./spkr <input/file> <output/file>" << std::endl;
        return 0;
    }

    char const* filename = argv[1];
    char const* outfilename = argv[2];

    int sampleRate = 44100;

    std::vector<std::vector<double>> in;

    if (strcmp(filename, "sin") == 0) {
        in = sinWave(44100, 44100 * 10, 440.0);
    } else {
        AudioFile<double> file;
        file.load(filename);
        in = file.samples;
        sampleRate = file.getSampleRate();
    }


    AudioFile<double> outfile;
    std::vector<std::vector<double>> out = std::vector < std::vector<double >>(2, std::vector<double > (in.at(0).size()));

    std::chrono::time_point start = std::chrono::high_resolution_clock::now();
    try {
        apply(in, out);
    }
    catch (std::exception &e) {
        printf("Exception: %s\n", e.what());
    }
    std::chrono::time_point end = std::chrono::high_resolution_clock::now();

    auto duration = duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "Time to execute: " << duration.count() / 1000000.0L << " seconds." << std::endl;
    std::cout << "File length: " << (float)out.at(0).size() / (float)sampleRate  << " seconds." << std:: endl;

    outfile.setAudioBuffer(out);
    outfile.save(outfilename);
    return 0;
};