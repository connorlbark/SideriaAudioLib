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

	char* filename = argv[1];
	char* outfile = argv[2];

	AudioFile<double> file;
	file.load(filename);

	std::vector<std::vector<double>> in = file.samples;

	std::vector<std::vector<double>> out = std::vector < std::vector<double >>(2, std::vector<double > (in.at(0).size()));



    std::chrono::time_point start = std::chrono::high_resolution_clock::now();
	try {
		apply(in, out);
	}
	catch (std::exception e) {
		printf("Exception: %s\n", e.what());
	}
    std::chrono::time_point end = std::chrono::high_resolution_clock::now();

    auto duration = duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "Time to execute: " << duration.count() / 1000000.f << " seconds." << std::endl;
    std::cout << "File length: " << file.getLengthInSeconds() << " seconds." << std:: endl;

    file.setAudioBuffer(out);
	file.save(outfile);
	return 0;
}


void applyDelay(std::vector<std::vector<double>> in, std::vector<std::vector<double>>& out) {
	siderialib::ModulatedDelay delay;

	delay.initialize(44100, 44100 * 10);

    delay.setDelayMs(2000.0);
    delay.setFeedback(0.6);

    delay.enableLpf(true);
    delay.setLpfParams(1000.0, 1.0, 0.0);

    delay.setMix(.8);

    delay.mod().setRateHz(2.0);
    delay.mod().setDepth(1.0);

	for (int i = 0; i < in.at(0).size(); i++) {

        siderialib::sfloat L = in.at(0).at(i);

        delay.tick(L, L);

		out.at(0).at(i) = delay.lastOutL();
		out.at(1).at(i) = delay.lastOutR();

	}
}


void apply(std::vector<std::vector<double>> in, std::vector<std::vector<double>>& out) {
    siderialib::Disperse disperse;

    float sampleRate = 44100;
    float mix = 1.0;
    float timeMs = 800.0;
    float dispersion = 0.4;
    float spread = 0.0;
    float feedback = 0.6;
    float tone = 0.5;
    float modRateHz = 2.0;
    float modDepth = 0.5;

    siderialib::DisperseArrangement arrangement = siderialib::FULL_PARALLEL;
    disperse.initialize(
            sampleRate,
            mix,
            dispersion,
            spread,
            timeMs,
            feedback,
            tone,
            modRateHz,
            modDepth,
            arrangement);

    for (int i = 0; i < in.at(0).size(); i++) {

        siderialib::sfloat L = in.at(0).at(i);

        disperse.tick(L, L);

        out.at(0).at(i) = disperse.lastOutL();
        out.at(1).at(i) = disperse.lastOutR();

    }
}