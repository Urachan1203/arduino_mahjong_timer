#include "TimerDialog.h"
#include "Timer.h"
#include "MahjongSetting.h"
#include <M5Stack.h>

void TimerDialog::Display(MahjongSetting* ms, TimerCommand tc){
    M5.Lcd.clear();
    int num_player = ms->GetNumPlayer();

    if(tc == TimerCommand::Pause){
        M5.Lcd.setTextSize(3);
        M5.Lcd.setCursor(10, 10);
        M5.Lcd.println("Status : Pause");
    }else{
        M5.Lcd.setTextSize(3);
        M5.Lcd.setCursor(10, 10);
        M5.Lcd.println("Status : Playing");
    }

    M5.Lcd.setTextSize(7);
    M5.Lcd.setCursor(190, 110);
    M5.Lcd.println("+");
    M5.Lcd.setCursor(230, 110);
    M5.Lcd.println(Timer::GetBaseTimeSec());

    M5.Lcd.setTextSize(1);
    M5.Lcd.setCursor(1, 220);
    M5.Lcd.println("Next");
    M5.Lcd.setCursor(1, 230);
    M5.Lcd.println("Pause/Continue");
    M5.Lcd.setCursor(130, 220);
    M5.Lcd.println("Change Order");
    M5.Lcd.setCursor(250, 220);
    M5.Lcd.println("Next");

    M5.Lcd.setTextSize(3);
    for(int i = 0; i < ms->GetNumPlayer(); i++){

        if(Timer::GetCurIdx() == i){
            M5.Lcd.setCursor(20, 80 + 30 * i);
            M5.Lcd.println("x");
        }
        M5.Lcd.setCursor(70, 80 + 30 * i);
        M5.Lcd.println(ms->GetPlayer(i)->GetPlayerName());
        M5.Lcd.setCursor(120, 80 + 30 * i);
        M5.Lcd.println(Timer::GetTimeRemainSec(i));
    }
    return;
}