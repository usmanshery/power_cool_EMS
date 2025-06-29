/**
 * Possible issues to freeze system:
 * ** [P0] Wifi Connect (red)
 * ** [P0] Bootup Time Sync (red)
 * ** [P0] Temperature Sensor Not Connected (red)
 * ** [P1] Read System Time (megenta)
 * ** [P2] Daily Time Sync (cyan)
 */

#pragma once

class Led {
    int r,g,b;
    bool ledState;
    bool freeze;

public:
    enum Color {
        RED,
        GREEN,
        BLUE,
        YELLOW,
        MEGENTA,
        CYAN,
        WHITE
    };

    int colorTranslate[7][3] = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1},
        {1, 1, 0},
        {1, 0, 1},
        {0, 1, 1},
        {1, 1, 1}
    };

    void Init();
    void Set(Color clr);
    void Set(Color clr, int brightness);
    void Test();
    /**
     * Only toggles LED on or off, does not erase the state
     */
    void Toggle();
    void Toggle(bool stateOverride);
    void Clear();
    void Freeze(bool freeze);

private:
    void UpdateStateValues(int r, int g, int b);
    void UpdateStateValues(int r, int g, int b, int intensity);
    void UpdateLedState();
};

extern Led led;