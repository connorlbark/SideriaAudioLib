
#include "../PluginProcessor.h"
#include "effects/Disperse.h"
#include "lookAndFeel/DisperseLookAndFeel.h"

class DisperseUI: public juce::Component {
private:

    siderialib::Disperse &_disperse;
    DisperseLookAndFeel _lookAndFeel;

public:
    explicit DisperseUI(siderialib::Disperse &disperse);
    ~DisperseUI() override = default;

    void resized() override;

};