#include "hotkey.h"
#include <iostream>
#include <string>
#include <windows.h>

// WINDOWS Hotkey API
const unsigned int kKeyF = 0x46;
const unsigned int kKeyG = 0x47;
// keeping item pressed (auto repeat) will not invoke multiple hotkey notifications
const unsigned int kMOD_NOREPEAT = 0x4000;

void HotKey::Register() {

    if (RegisterHotKey(
        NULL,   //hWnd, optional. If this parameter is NULL, WM_HOTKEY messages are posted to the message queue of the calling thread and must be processed in the message loop.
        1,
        MOD_ALT | MOD_SHIFT | kMOD_NOREPEAT,
        kKeyF)) {
        std::cout << "Hotkey 1 registered" << std::endl;
    }
    if (RegisterHotKey(
        NULL,   //hWnd, optional. If this parameter is NULL, WM_HOTKEY messages are posted to the message queue of the calling thread and must be processed in the message loop.
        2,
        MOD_ALT | MOD_SHIFT | kMOD_NOREPEAT,
        kKeyG)) {
        std::cout << "Hotkey 2 registered" << std::endl;
    }
}