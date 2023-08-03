#include "daisy_petal.h"
#include "daisysp.h"
#include "siderialib.h"
#include "effects/Disperse.h"
#include "util/SmoothedParameter.h"
#include "params.h"

// Use the daisy namespace to prevent having to type
// daisy:: before all libdaisy functions
using namespace daisy;
using namespace daisysp;

// Declare a DaisySeed object called hardware
DaisyPetal hardware;
siderialib::Disperse disperse;

float DSY_SDRAM_BSS voice1[MAX_DELAY_SAMPLES * 2]; // stereo, so *2 for all of them
float DSY_SDRAM_BSS voice2[MAX_DELAY_SAMPLES * 2];
float DSY_SDRAM_BSS voice3[MAX_DELAY_SAMPLES * 2];
float DSY_SDRAM_BSS voice4[MAX_DELAY_SAMPLES * 2];
float DSY_SDRAM_BSS voice5[MAX_DELAY_SAMPLES * 2];
float DSY_SDRAM_BSS voice6[MAX_DELAY_SAMPLES * 2];

SmoothedParameter time;
Parameter spread;
Parameter dispersion;
Parameter mix;
Parameter feedback;
Parameter tone;
Parameter modDepth;

Oscillator timeLfo;
float timeLfoValue;

Led bypassLed;
Led timeLed;
bool effectActive = false;

void InitDisperse()
{
    bypassLed.Init(hardware.seed.GetPin(terrarium::Terrarium::LED_2), false, SAMPLE_RATE);
    timeLed.Init(hardware.seed.GetPin(terrarium::Terrarium::LED_1), false, SAMPLE_RATE);
    timeLfo.Init(SAMPLE_RATE);

    time.param.Init(hardware.knob[terrarium::Terrarium::KNOB_1], 30.0, 5000.0, Parameter::CUBE);
    feedback.Init(hardware.knob[terrarium::Terrarium::KNOB_2], 0.0, 0.99, Parameter::LINEAR);
    dispersion.Init(hardware.knob[terrarium::Terrarium::KNOB_3], 0.0, 1.0, Parameter::LINEAR);
    mix.Init(hardware.knob[terrarium::Terrarium::KNOB_6], 0.0, 1.0, Parameter::LINEAR);
    tone.Init(hardware.knob[terrarium::Terrarium::KNOB_4], 0.0, 1.0, Parameter::LINEAR);
    modDepth.Init(hardware.knob[terrarium::Terrarium::KNOB_5], 0.0, 1.0, Parameter::LINEAR);

    disperse.initialize(
        voice1,
        voice2,
        voice3,
        voice4,
        voice5,
        voice6,
        MAX_DELAY_SAMPLES * 2,
        SAMPLE_RATE,
        0.0,
        0.0,
        0.0,
        100.0,
        0.0,
        0.5,
        1.0,
        0.0,
        siderialib::DisperseArrangement::FULL_PARALLEL);
}

inline bool hasChanged(float param, float curr, float sensitivity = 0.01)
{
    return abs(param - curr) > sensitivity;
}

void UpdateParams()
{
    hardware.ProcessAllControls();

    disperse.setAllParams(
        mix.Value(),
        dispersion.Value(),
        spread.Value(),
        time.Value(),
        feedback.Value(),
        tone.Value(),
        2.0,
        modDepth.Value(),
        siderialib::DisperseArrangement::FULL_PARALLEL);
}

void Tick()
{
    timeLed.Set(effectActive ? (timeLfo.Process() + 1.f) / 2.f : 0.f);
    bypassLed.Set(effectActive ? 1.f : 0.f);
}

void AudioCallback(AudioHandle::InterleavingInputBuffer in,
                   AudioHandle::InterleavingOutputBuffer out,
                   size_t size)
{
    UpdateParams();
    Tick();

    // Fill the block with samples
    for (size_t i = 0; i < size; i += 2)
    {

        disperse.tick(in[i], in[i + 1]);

        out[i] = disperse.lastOutL();
        out[i + 1] = disperse.lastOutR();
    }
}

int main(void)
{
    // Initialize the Daisy Seed
    hardware.Init();

    InitDisperse();

    hardware.ChangeAudioCallback(AudioCallback);

    // Loop forever
    for (;;)
    {
    }
}
