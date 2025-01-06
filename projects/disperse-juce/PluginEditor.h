#pragma once

#include "PluginProcessor.h"
#ifdef DEBUG_UI
#include "debug_ui/DebugUI.h"
#else
#include "ui/DisperseUI.h"
#endif

//==============================================================================
class AudioPluginAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    explicit AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor&);
    ~AudioPluginAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    AudioPluginAudioProcessor& processorRef;

#ifdef DEBUG_UI
    DebugUI ui;
#else
    DisperseUI ui;
#endif


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioPluginAudioProcessorEditor)
};
