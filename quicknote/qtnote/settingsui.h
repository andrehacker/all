#ifndef SETTINGSUI_H
#define SETTINGSUI_H

class SettingsUi
{
public:
    SettingsUi() = delete;
    SettingsUi& operator=(const SettingsUi&) = delete;
    SettingsUi(const SettingsUi&) = delete;

    static bool minimizedInfoAllowed();


private:
    static int minimizedInfoCount;

};

#endif // SETTINGSUI_H
