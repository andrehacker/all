#include <iostream>
#include <string>
#include <windows.h>
#include "hotkey.h"
// stored in C:\cygwin\usr\include\w32api\windows.h

// WINDOWS Hotkey API
const unsigned int kKeyF = 0x46;
const unsigned int kKeyG = 0x47;
// keeping item pressed (auto repeat) will not invoke multiple hotkey notifications
const unsigned int kMOD_NOREPEAT = 0x4000;

void hotKeyLoop();

int main(int argc, char *argv[])
{
    HotKey hotKey;
    hotKey.Register();
    hotKeyLoop();

    return 0;
}

void hotKeyLoop() {
 
    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0) != 0) {
        if (msg.message == WM_HOTKEY)
        {
            std::cout << "WM_HOTKEY received with lparam: " << msg.lParam << std::endl;
            //MessageBox(NULL, "You pressed the key!", "Key Press Alert", MB_OK);
            if ( static_cast<unsigned int>(msg.lParam>>16) == kKeyF) {
                std::cout << "pressed F" << std::endl;
            }
            if ( static_cast<unsigned int>(msg.lParam>>16) == kKeyG) {
                std::cout << "pressed G" << std::endl;
            }
        }
    }
}
