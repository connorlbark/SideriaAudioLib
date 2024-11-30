#include "DisperseUI.h"

DisperseUI::DisperseUI(siderialib::Disperse &disperse) : _disperse(disperse) {
    this->setLookAndFeel(&_lookAndFeel);
}

void DisperseUI::resized() {

}