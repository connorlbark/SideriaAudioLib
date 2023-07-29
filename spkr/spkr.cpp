#include <iostream>

#include "AudioFile.h"
#include <vector>

#include "../siderialib/include/effects/delay/ModulatedDelay.h"
#include "../siderialib/include/effects/filter/BiquadFilter.h"

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
	siderialib::BiquadFilter lpf;

	lpf.initialize(44100, siderialib::BiquadType::LPF, 1000.0, 2.0);

	delay.initialize(44100, 44100 * 10);

	delay.setDelayMs(20.0);
	delay.setFeedback(0.0);
	delay.setMix(1.0);


	for (int i = 0; i < in.at(0).size(); i++) {

		sfloat L = in.at(0).at(i);
		//sfloat R = in.at(0).at(i);

		sfloat filtered = lpf.tick(L);
        //delay.tick(L,R);

		out.at(0).at(i) = filtered;//delay.lastOutL();
		out.at(1).at(i) = L;//delay.lastOutR();

	}
}

