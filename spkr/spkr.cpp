#include <iostream>

#include "AudioFile.h"
#include <vector>

#include "../siderialib/include/siderialib.h"
#include "../siderialib/include/effects/delay/ModulatedDelay.h"

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



	try {
		apply(in, out);
	}
	catch (std::exception e) {
		printf("Exception: %s\n", e.what());
	}

	file.setAudioBuffer(out);
	file.save(outfile);
	return 0;
}


void apply(std::vector<std::vector<double>> in, std::vector<std::vector<double>>& out) {
	siderialib::ModulatedDelay delay;

	delay.initialize(44100, 44100 * 10);

    delay.setDelayMs(100.0);
    delay.setFeedback(0.5);

    delay.enableLpf(true);
    delay.setLpfParams(5000.0, 1.0, 0.0);

	delay.setDelayMs(20.0);
	delay.setFeedback(0.0);
	delay.setMix(0.8);

    delay.mod().setRateHz(2.0);
    delay.mod().setDepth(1.0);

	for (int i = 0; i < in.at(0).size(); i++) {

        siderialib::sfloat L = in.at(0).at(i);

        delay.tick(L, L);

		out.at(0).at(i) = delay.lastOutL();
		out.at(1).at(i) = delay.lastOutR();

	}
}

