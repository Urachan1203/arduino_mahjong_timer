#ifndef INCLUDED_TIMER_DIALOG
#define INCLUDED_TIMER_DIALOG

#include <M5Stack.h>
#include "MahjongSetting.h"
#include "Timer.h"


class TimerDialog {
    public:
    static void Display(MahjongSetting* ms, TimerStatus tc);
};

#endif