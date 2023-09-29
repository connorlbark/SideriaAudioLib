#include "daisy_petal.h"
#include "daisysp.h"
#include "siderialib.h"
#include "effects/Disperse.h"
#include "util/TrackedParameter.h"
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

TrackedParameter time;
TrackedParameter position;
TrackedParameter dispersion;
TrackedParameter mix;
TrackedParameter feedback;
TrackedParameter modDepth;

Oscillator timeLfo;
float timeLfoValue;

Led bypassLed;
Led timeLed;
bool effectActive = false;

bool downsample = false;
bool downsampleMore = false;

const float defaultSpread = 0.f;
const float defaultTone = 0.f;
const float defaultModHz = 0.f;
const int defaultDownsampleFactor = 0;

void InitDisperse()
{
    bypassLed.Init(hardware.seed.GetPin(terrarium::Terrarium::LED_2), false, SAMPLE_RATE);
    timeLed.Init(hardware.seed.GetPin(terrarium::Terrarium::LED_1), false, SAMPLE_RATE);
    timeLfo.Init(SAMPLE_RATE);

    time.Init(hardware.knob[terrarium::Terrarium::KNOB_1], 30.0, 5000.0, Parameter::CUBE, true, 30.0f);
    feedback.Init(hardware.knob[terrarium::Terrarium::KNOB_2], 0.0, 0.99, Parameter::LINEAR, true);
    dispersion.Init(hardware.knob[terrarium::Terrarium::KNOB_3], 0.0, 1.0, Parameter::LINEAR, false);
    mix.Init(hardware.knob[terrarium::Terrarium::KNOB_4], 0.0, 1.0, Parameter::LINEAR, true);
    position.Init(hardware.knob[terrarium::Terrarium::KNOB_6], 0.0, 1.0, Parameter::LINEAR, false);
    modDepth.Init(hardware.knob[terrarium::Terrarium::KNOB_5], 0.0, 1.0, Parameter::LINEAR, true);

    disperse.initialize(
        voice1,
        voice2,
        voice3,
        voice4,
        voice5,
        voice6,
        MAX_DELAY_SAMPLES * 2,
        SAMPLE_RATE);

    disperse.setAllParams(
        mix.Value(),
        dispersion.Value(),
        defaultSpread,
        time.Value(),
        feedback.Value(),
        defaultTone,
        defaultModHz,
        modDepth.Value(),
        position.Value(),
        defaultDownsampleFactor,
        siderialib::DisperseArrangement::FULL_PARALLEL);
}

inline bool hasChanged(float param, float curr, float sensitivity = 0.01)
{
    return abs(param - curr) > sensitivity;
}

void UpdateParams()
{
    hardware.ProcessAllControls();

    time.Process();
    position.Process();
    dispersion.Process();
    mix.Process();
    feedback.Process();
    modDepth.Process();

    effectActive ^= hardware.switches[terrarium::Terrarium::FOOTSWITCH_2].RisingEdge();
    downsample = hardware.switches[terrarium::Terrarium::SWITCH_1].Pressed();
    downsampleMore = hardware.switches[terrarium::Terrarium::SWITCH_2].Pressed();

    if (time.Changed())
    {
        disperse.setTimeMs(time.Value());
    }

    if (position.Changed())
    {
        disperse.setPosition(position.Value());
    }

    if (dispersion.Changed())
    {
        disperse.setDispersion(dispersion.Value());
    }

    if (mix.Changed())
    {
        disperse.setMix(mix.Value());
    }

    if (feedback.Changed())
    {
        disperse.setFeedback(feedback.Value());
    }

    if (modDepth.Changed())
    {
        disperse.setModDepth(modDepth.Value());
    }

    if (downsample)
    {
        disperse.setDownsampleFactor(downsampleMore ? 2 : 1);
    }
    else
    {
        disperse.setDownsampleFactor(0);
    }
}

void Tick()
{
    timeLed.Set(effectActive ? (timeLfo.Process() + 1.f) / 2.f : 0.f);
    bypassLed.Set(effectActive ? 1.f : 0.f);
}

CpuLoadMeter meter;

void AudioCallback(AudioHandle::InterleavingInputBuffer in,
                   AudioHandle::InterleavingOutputBuffer out,
                   size_t size)
{
    meter.OnBlockStart();
    UpdateParams();
    Tick();

    // Fill the block with samples
    for (size_t i = 0; i < size; i += 2)
    {
        if (effectActive)
        {
            disperse.tick(in[i], in[i]);

            out[i] = disperse.lastOutL();
            out[i + 1] = disperse.lastOutR();
        }
        else
        {
            disperse.tick(in[i], in[i]);

            out[i] = in[i];
            out[i + 1] = in[i + 1];
        }
    }

    meter.OnBlockEnd();

    if (meter.GetMaxCpuLoad() > .99f)
    {
        hardware.seed.SetLed(true);
    }
    else
    {
        hardware.seed.SetLed(false);
    }
}

const int blockSize = 32;
int main(void)
{
    // Initialize the Daisy Seed
    hardware.Init();
    hardware.seed.PrintLine("Starting up!");
    hardware.SetAudioBlockSize(blockSize);

    hardware.SetAudioSampleRate(SaiHandle::Config::SampleRate::SAI_48KHZ);

    hardware.seed.PrintLine("Initializing disperse...");
    InitDisperse();
    hardware.seed.PrintLine("Done. Starting audio...");

    hardware.StartAdc();
    hardware.StartAudio(AudioCallback);

    meter.Init(SAMPLE_RATE, blockSize);

    // Loop forever
    for (;;)
    {
    }
}
