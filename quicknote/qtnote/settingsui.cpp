#include "settingsui.h"

int SettingsUi::minimizedInfoCount = 0;

bool SettingsUi::minimizedInfoAllowed() {
    ++minimizedInfoCount;
    return (minimizedInfoCount == 1);
}
