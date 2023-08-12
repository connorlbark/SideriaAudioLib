#include <iostream>

#include "AudioFile.h"
#include <vector>
#include <chrono>

#include "../siderialib/include/siderialib.h"
#include "../siderialib/include/effects/delay/ModulatedDelay.h"
#include "../siderialib/include/effects/Disperse.h"

void apply(std::vector<std::vector<double>> in, std::vector<std::vector<double>>& out);

int main(int argc, char *argv[]) {

	if (argc != 3) {
		std::cout << "Use:\n./spkr <input/file> <output/file>" << std::endl;
		return 0;
	}

	char const* filename = argv[1];
	char const* outfile = argv[2];

	AudioFile<double> file;
	file.load(filename);

	std::vector<std::vector<double>> in = file.samples;

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
    std::cout << "File length: " << file.getLengthInSeconds() << " seconds." << std:: endl;

    file.setAudioBuffer(out);
	file.save(outfile);
	return 0;
}


void applyDelay(std::vector<std::vector<double>> in, std::vector<std::vector<double>>& out) {
	siderialib::ModulatedDelay delay;

    siderialib::LFO lfo;
    lfo.initialize(44100.0f);
	delay.initialize(&lfo, 44100.f, 44100 * 10);

    delay.setDelayMs(2000.0f);
    delay.setFeedback(0.6f);

    delay.enableLpf(false);
    delay.setLpfParams(1000.0f, 1.0f, 0.0f);

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
    float mix = 0.8f;
    float timeMs = 1000.0f;
    float dispersion = 0.8f;
    float spread = 0.0f;
    float feedback = 0.5f;
    float tone = 0.1f;
    float modRateHz = 2.0f;
    float modDepth = 0.1f;
    float position = 0.35f;
    int downsampleFactor = 0;

    siderialib::DisperseArrangement arrangement = siderialib::DisperseArrangement::FULL_PARALLEL;
    disperse.initialize(sampleRate);

    disperse.setAllParams(mix, dispersion, spread, timeMs, feedback, tone, modRateHz, modDepth, position, downsampleFactor, arrangement);

    for (int i = 0; i < in.at(0).size(); i++) {

        siderialib::sfloat L = (siderialib::sfloat)in.at(0).at(i);

        disperse.tick(L, L);

        out.at(0).at(i) = disperse.lastOutL();
        out.at(1).at(i) = disperse.lastOutR();

    }
}

void applyFilter(std::vector<std::vector<double>> in, std::vector<std::vector<double>>& out) {
    siderialib::BiquadFilter filter;

    filter.initialize(44100.0, siderialib::BiquadType::LPF, 1000.0, 1.0);

    for (int i = 0; i < in.at(0).size(); i++) {

        siderialib::sfloat L = (siderialib::sfloat)in.at(0).at(i);

        float filtered = filter.tick(L);

        out.at(0).at(i) = filtered;
        out.at(1).at(i) = filtered;

    }
}