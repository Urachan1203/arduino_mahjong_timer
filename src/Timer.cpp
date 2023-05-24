#include "Timer.h"
#include "MahjongSetting.h"
#include "TimerDialog.h"
#include "TimeDispMsg.h"
#include <M5Stack.h>
#include <LiquidCrystal_I2C.h>

MahjongSetting* Timer::ms;
int Timer::cur_idx;
int Timer::base_time_sec;
int Timer::time_remain_sec[MAX_PLAYER_NUM];

QueueHandle_t xQueue;

hw_timer_t * timer = NULL;

bool pause_enabled = true;

void IRAM_ATTR onTimer() {

    int cur_idx = Timer::GetCurIdx();

    if(Timer::GetBaseTimeSec() > 0){
        Timer::SetBaseTimeSec(Timer::GetBaseTimeSec() - 1);
    }
    else if(Timer::GetTimeRemainSec(cur_idx) > 0){
        Timer::SetTimeRemainSec(cur_idx, Timer::GetTimeRemainSec(cur_idx) - 1); // count down 1 sec
    }
    TimerDialog::Display(Timer::GetMahjongSetting(), TimerCommand::Continue);

    pause_enabled = true;

    TimeDispMsg msg = TimeDispMsg(cur_idx, Timer::GetTimeRemainSec(cur_idx), Timer::GetBaseTimeSec());
    xQueueSend(xQueue, &msg, 0);

    return;
}

void Timer::Init(int idx, MahjongSetting* m){
    Timer::SetMahjongSetting(m);
    Timer::SetCurIdx(idx);
    Timer::SetBaseTimeSec(m->GetBaseTimeSec());

    for(int i = 0; i < m->GetNumPlayer(); i++){
        Timer::SetTimeRemainSec(i, m->GetPlayer(i)->GetTimeRemainSec());
        LiquidCrystal_I2C target_lcd = m->GetPlayer(i)->GetPlayerLcd();

        // TODO : 関数化？
        Serial.println((long) &target_lcd);
        target_lcd.clear();
        target_lcd.setCursor(0, 0);
        target_lcd.print("Time Left : ");
        target_lcd.setCursor(13, 0);
        target_lcd.print(Timer::GetTimeRemainSec(i));
    }

    // timer initialization
    timer = timerBegin(0, 80, true);
    timerAttachInterrupt(timer, &onTimer, true);
    timerAlarmWrite(timer, 1000000, true);      // call onTimer every 1 sec

    xQueue = xQueueCreate(3, sizeof(TimeDispMsg));

    return;
}

void Timer::CountTime(){
    int time_tmp = Timer::GetBaseTimeSec();
    timerAlarmEnable(timer);

    TimerCommand cmd;

    while(1){
        M5.update();
        //! 自分のターンが終わったら押下
        if(M5.BtnA.wasReleased() || M5.BtnC.wasReleased()){
            cmd = TimerCommand::Continue;
            break;
        }
        //! 順番変更時に押下
        if(M5.BtnB.wasReleased()){
            cmd = TimerCommand::ChangeOrder;
            break;
        }
        //! ポーズ
        if(M5.BtnA.pressedFor(1000) && pause_enabled){
            cmd = TimerCommand::Pause;
            Timer::Pause();
            cmd = TimerCommand::Continue;
            pause_enabled = false;
        }

        TimeDispMsg recv;
        portBASE_TYPE ret = xQueueReceive(xQueue, &recv, 0);

        if(ret == pdTRUE){
            Serial.println("received.");
            Serial.println(recv.idx);
            Serial.println(recv.time_remain);
            Serial.println(recv.time_base);
            LiquidCrystal_I2C target_lcd = Timer::GetMahjongSetting()->GetPlayer(recv.idx)->GetPlayerLcd(); 
            target_lcd.clear();
            target_lcd.setCursor(0, 0);
            target_lcd.print("Time Left : ");
            target_lcd.setCursor(13, 0);
            target_lcd.print(recv.time_remain);
            target_lcd.setCursor(0, 1);
            target_lcd.print("Turn time : ");    // 13 character
            target_lcd.setCursor(13, 1);
            target_lcd.print(recv.time_base);
        }
        
    }
    timerAlarmDisable(timer);

    Timer::SetBaseTimeSec(time_tmp);    // カウントが終了したので、basetimeを元に戻す

    //! cur_idx を次の人へ
    //! ポン発生時はこの限りではないので、順番割り込みを行うダイアログの実装がTODO
    Timer::SetCurIdx((Timer::GetCurIdx() + 1) % Timer::GetMahjongSetting()->GetNumPlayer());
    return;
}

// press BtnA for 1 sec to continue
void Timer::Pause(){
    timerAlarmDisable(timer);
    TimerDialog::Display(ms, TimerCommand::Pause);
    sleep(2);
    while(1){
        M5.update();
        if(M5.BtnA.pressedFor(1000)){
            timerAlarmEnable(timer);
            break;
        }
    }
}

void Timer::Down(){
    if(Timer::GetBaseTimeSec() > 0){
        Timer::SetBaseTimeSec(Timer::GetBaseTimeSec() - 1);
    }
    else if(Timer::GetTimeRemainSec(Timer::GetCurIdx()) > 0){
        Timer::SetTimeRemainSec(Timer::GetCurIdx(), Timer::GetTimeRemainSec(Timer::GetCurIdx()) - 1);
    }
    TimerDialog::Display(Timer::GetMahjongSetting(), TimerCommand::Continue);
    return;
}

MahjongSetting* Timer::GetMahjongSetting(){
    return Timer::ms;
}

void Timer::SetMahjongSetting(MahjongSetting* m){
    Timer::ms = m;
    return;
}

int Timer::GetCurIdx(){
    return Timer::cur_idx;
}

void Timer::SetCurIdx(int idx){
    cur_idx = idx;
    return;
}

int Timer::GetBaseTimeSec(){
    return Timer::base_time_sec;
}

void Timer::SetBaseTimeSec(int base_time_sec){
    Timer::base_time_sec = base_time_sec;
    return;
}

int Timer::GetTimeRemainSec(int idx){
    return Timer::time_remain_sec[idx];
}

void Timer::SetTimeRemainSec(int idx, int time_remain_sec){
    Timer::time_remain_sec[idx] = time_remain_sec;
    return;
}