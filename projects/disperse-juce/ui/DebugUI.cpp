#include "DebugUI.h"

DebugUI::DebugUI(siderialib::Disperse &disperse) : _disperse(disperse) {
    addAndMakeVisible (_dispersionSlider);
    _dispersionSlider.setRange (0.0, 100.0);
    _dispersionSlider.setTextValueSuffix (" %");
    _dispersionSlider.onValueChange = [this] { _disperse.setDispersion((float)_dispersionSlider.getValue() / 100.f); };

    addAndMakeVisible (_dispersionLabel);
    _dispersionLabel.setText ("Dispersion", juce::dontSendNotification);
    _dispersionLabel.attachToComponent (&_dispersionSlider, true);


    addAndMakeVisible (_spreadSlider);
    _spreadSlider.setRange (0.0, 100.0);
    _spreadSlider.setTextValueSuffix (" %");
    _spreadSlider.onValueChange = [this] { _disperse.setSpread((float)_spreadSlider.getValue() / 100.f); };

    addAndMakeVisible (_spreadLabel);
    _spreadLabel.setText ("Spread", juce::dontSendNotification);
    _spreadLabel.attachToComponent (&_spreadSlider, true);

    addAndMakeVisible (_feedbackSlider);
    _feedbackSlider.setRange (0.0, 100.0);
    _feedbackSlider.setTextValueSuffix (" %");
    _feedbackSlider.onValueChange = [this] { _disperse.setFeedback((float)_feedbackSlider.getValue() / 100.f); };

    addAndMakeVisible (_feedbackLabel);
    _feedbackLabel.setText ("Feedback", juce::dontSendNotification);
    _feedbackLabel.attachToComponent (&_feedbackSlider, true);

    addAndMakeVisible (_timeMsSlider);
    _timeMsSlider.setRange (250.0, 4750.0);
    _timeMsSlider.setTextValueSuffix (" ms");
    _timeMsSlider.onValueChange = [this] { _disperse.setTimeMs((float)_timeMsSlider.getValue()); };

    addAndMakeVisible (_timeMsLabel);
    _timeMsLabel.setText ("Time", juce::dontSendNotification);
    _timeMsLabel.attachToComponent (&_timeMsSlider, true);

    addAndMakeVisible (_mixSlider);
    _mixSlider.setRange (0.0, 100.0);
    _mixSlider.setTextValueSuffix (" %");
    _mixSlider.onValueChange = [this] { _disperse.setMix((float)_mixSlider.getValue() / 100.f); };

    addAndMakeVisible (_mixLabel);
    _mixLabel.setText ("Mix", juce::dontSendNotification);
    _mixLabel.attachToComponent (&_mixSlider, true);

    addAndMakeVisible (_toneLabel);
    _toneLabel.setText ("Tone", juce::dontSendNotification);
    _toneLabel.attachToComponent (&_toneSlider, true);

    addAndMakeVisible (_positionSlider);
    _positionSlider.setRange (0.0, 100.0);
    _positionSlider.setTextValueSuffix (" %");
    _positionSlider.onValueChange = [this] { _disperse.setPosition((float)_positionSlider.getValue() / 100.f); };

    addAndMakeVisible (_positionLabel);
    _positionLabel.setText ("Position", juce::dontSendNotification);
    _positionLabel.attachToComponent (&_positionSlider, true);

    addAndMakeVisible (_modRateHzSlider);
    _modRateHzSlider.setRange (0.1, 10.0);
    _modRateHzSlider.setTextValueSuffix (" %");
    _modRateHzSlider.onValueChange = [this] { _disperse.setModRateHz((float)_modRateHzSlider.getValue()); };

    addAndMakeVisible (_modRateHzLabel);
    _modRateHzLabel.setText ("Mod Rate", juce::dontSendNotification);
    _modRateHzLabel.attachToComponent (&_modRateHzSlider, true);

    addAndMakeVisible (_modDepthSlider);
    _modDepthSlider.setRange (0.0, 100.0);
    _modDepthSlider.setTextValueSuffix (" %");
    _modDepthSlider.onValueChange = [this] { _disperse.setModDepth((float)_modDepthSlider.getValue() / 100.f); };

    addAndMakeVisible (_dispersionLabel);
    _modDepthLabel.setText ("Mod Depth", juce::dontSendNotification);
    _modDepthLabel.attachToComponent (&_modDepthSlider, true);


}

void DebugUI::resized() {
    auto sliderLeft = 120;
    _dispersionSlider.setBounds (sliderLeft, 20, getWidth() - sliderLeft - 10, 20);
    _spreadSlider.setBounds (sliderLeft, 50, getWidth() - sliderLeft - 10, 20);
    _timeMsSlider.setBounds (sliderLeft, 80, getWidth() - sliderLeft - 10, 20);
    _feedbackSlider.setBounds (sliderLeft, 110, getWidth() - sliderLeft - 10, 20);
    _mixSlider.setBounds (sliderLeft, 140, getWidth() - sliderLeft - 10, 20);
    _toneSlider.setBounds (sliderLeft, 170, getWidth() - sliderLeft - 10, 20);
    _positionSlider.setBounds (sliderLeft, 200, getWidth() - sliderLeft - 10, 20);
    _modRateHzSlider.setBounds (sliderLeft, 230, getWidth() - sliderLeft - 10, 20);
    _modDepthSlider.setBounds (sliderLeft, 260, getWidth() - sliderLeft - 10, 20);

}