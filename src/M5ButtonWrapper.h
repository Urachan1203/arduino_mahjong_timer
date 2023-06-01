#ifndef INCLUDED_M5_BUTTON_WRAPPER
#define INCLUDED_M5_BUTTON_WRAPPER

#include <M5Stack.h>

class M5Button {
    private:
    Button* btn;
    time_t* init_pressed_time;
    bool active;

    public:
    M5Button(Button* b);
    static void RefleshAllButton();
    time_t* GetInitPressedTime();
    void SetInitPressedtime();
    void ActivateButton();
    void DeactivateButton();
    bool wasReleased();
    bool isLongPressed(double sec);
};

extern M5Button BtnA;
extern M5Button BtnB;
extern M5Button BtnC;

#endif