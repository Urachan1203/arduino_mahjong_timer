#include "TimerDialog.h"
#include "Timer.h"
#include "MahjongSetting.h"
#include <M5Stack.h>

void TimerDialog::Display(MahjongSetting* ms){
    M5.Lcd.clear();
    int num_player = ms->GetNumPlayer();
    M5.Lcd.setCursor(0, 0);
    for(int i = 0; i < ms->GetNumPlayer(); i++){
        M5.Lcd.println(Timer::GetBaseTimeSec());
        M5.Lcd.println(Timer::GetTimeRemainSec(i));
    }
    return;
}