#include <iostream>

#include "AudioFile.h"
#include <vector>

#include "../siderialib/include/effects/delay/ModulatedDelay.h"

void apply(std::vector<std::vector<double>> in, std::vector<std::vector<double>>& out);

int main(int argc, char *argv[]) {
	if (argc != 3) {
		std::cout << "Use:\n./spkr <input/file> <output/file>" << std::endl;
	}

	char* filename = argv[1];
	char* outfile = argv[2];

	AudioFile<double> file;
	file.load(filename);

	std::vector<std::vector<double>> out;
	std::vector<std::vector<double>> in = file.samples;
	apply(in, out);

	AudioFile<double> output;
	output.setAudioBufferSize(2, out.at(0).size());
	output.setAudioBuffer(out);
	output.setSampleRate(44100);
	output.save(outfile);
}


void apply(std::vector<std::vector<double>> in, std::vector<std::vector<double>>& out) {
	siderialib::ModulatedDelay delay;

	delay.initialize(44100, 44100 * 10);

	delay.setDelayMs(1000.0);
	delay.setFeedback(0.6);
	delay.setMix(0.5);

	for (int i = 0; i < in.at(0).size(); i++) {
		sfloat L = in.at(0).at(i);
		sfloat R = in.at(1).at(i);

		svec2 inVec = svec2(L, R);
		svec2 outVec;

		delay.tick(inVec, outVec);

		out.at(0).at(i) = outVec.L();
		out.at(1).at(i) = outVec.R();

	}
}

