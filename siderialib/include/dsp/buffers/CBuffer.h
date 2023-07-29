#pragma once

#include "../Buffer.h"


namespace siderialib {
	class CBuffer : public Buffer {
	private:
		sfloat* buf;
		int _numChannels;
		int _numSamples;

		inline int flattenIndex(int channel, int sample);
	public:

        ~CBuffer();

		virtual void initialize(int numChannels, int numSamples);

		sfloat read(int channel, int sample) override final;

		void write(sfloat val, int channel, int sample) override final;

		int size() override final;

		int numChannels() override final;
	};
}
