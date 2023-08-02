#include "daisy_petal.h"
#include "siderialib.h"
#include "effects/Disperse.h"
#include "util/SmoothedParameter.h"
#include "params.h"

// Use the daisy namespace to prevent having to type
// daisy:: before all libdaisy functions
using namespace daisy;

// Declare a DaisySeed object called hardware
DaisyPetal hardware;
siderialib::Disperse disperse;

float DSY_SDRAM_BSS voice1[MAX_DELAY_SAMPLES * 2]; // stereo
float DSY_SDRAM_BSS voice2[MAX_DELAY_SAMPLES * 2];
float DSY_SDRAM_BSS voice3[MAX_DELAY_SAMPLES * 2];
float DSY_SDRAM_BSS voice4[MAX_DELAY_SAMPLES * 2];
float DSY_SDRAM_BSS voice5[MAX_DELAY_SAMPLES * 2];
float DSY_SDRAM_BSS voice6[MAX_DELAY_SAMPLES * 2];

Parameter p;

void InitDisperse()
{

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

void UpdateParams()
{
    hardware.ProcessAllControls();
}

void AudioCallback(AudioHandle::InterleavingInputBuffer in,
                   AudioHandle::InterleavingOutputBuffer out,
                   size_t size)
{

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
    // Declare a variable to store the state we want to set for the LED.
    bool led_state;
    led_state = true;

    // Initialize the Daisy Seed
    hardware.Init();

    InitDisperse();

    hardware.ChangeAudioCallback(AudioCallback);

    // Loop forever
    for (;;)
    {
        // Set the onboard LED
        hardware.seed.SetLed(led_state);

        // Toggle the LED state for the next time around.
        led_state = !led_state;

        // Wait 500ms
        System::Delay(500);
    }
}
