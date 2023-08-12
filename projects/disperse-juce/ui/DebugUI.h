
#include "../PluginProcessor.h"
#include "effects/Disperse.h"

class DebugUI: public juce::Component {
private:
    juce::Slider _dispersionSlider;
    juce::Label _dispersionLabel;
    juce::Slider _spreadSlider;
    juce::Label _spreadLabel;
    juce::Slider _feedbackSlider;
    juce::Label _feedbackLabel;
    juce::Slider _timeMsSlider;
    juce::Label _timeMsLabel;
    juce::Slider _mixSlider;
    juce::Label _mixLabel;
    juce::Slider _toneSlider;
    juce::Label _toneLabel;
    juce::Slider _positionSlider;
    juce::Label _positionLabel;
    juce::Slider _modRateHzSlider;
    juce::Label _modRateHzLabel;
    juce::Slider _modDepthSlider;
    juce::Label _modDepthLabel;

    siderialib::Disperse &_disperse;
public:
    explicit DebugUI(siderialib::Disperse &disperse);

    void resized() override;

};