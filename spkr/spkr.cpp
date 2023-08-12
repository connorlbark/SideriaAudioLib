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

    delay.setDelayMs(500.0f);
    delay.setFeedback(0.0f);

    delay.enableLpf(true);
    delay.setLpfParams(4000.0f, 0.7f, 12.0f);

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
    float mix = 1.0f;
    float timeMs = 500.0f;
    float dispersion = 0.0f;
    float spread = 0.0f;
    float feedback = 0.8f;
    float tone = 1.0f;
    float modRateHz = 2.0f;
    float modDepth = 0.0f;
    float position = 0.f;
    int downsampleFactor = 0;

    siderialib::DisperseArrangement arrangement = siderialib::DisperseArrangement::FULL_PARALLEL;
    disperse.initialize(sampleRate);

    disperse.setAllParams(mix, dispersion, spread, timeMs, feedback, tone, modRateHz, modDepth, position, downsampleFactor, arrangement);

    disperse.enablePingPong(true);

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