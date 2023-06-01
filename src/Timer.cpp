#include "Timer.h"
#include "MahjongSetting.h"
#include "TimerDialog.h"
#include "TimeDispMsg.h"
#include "PlayerSelectDialog.h"
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
    TimerDialog::Display(Timer::GetMahjongSetting(), TimerStatus::Continue);

    pause_enabled = true;

    TimeDispMsg msg = TimeDispMsg(cur_idx, Timer::GetTimeRemainSec(cur_idx), Timer::GetBaseTimeSec());
    xQueueSend(xQueue, &msg, 0);

    return;
}

void Timer::Init(int idx, MahjongSetting* m){

    Timer::SetMahjongSetting(m);
    Timer::SetCurIdx(idx);
    Timer::SetBaseTimeSec(m->GetBaseTimeSec());

    // LCDに初期時間表示
    // TODO : Timerのinitializationじゃないので別箇所に移行すべき？
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

    // タイマー関係
    timer = timerBegin(0, 80, true);
    timerAttachInterrupt(timer, &onTimer, true);
    timerAlarmWrite(timer, 1000000, true);      // call onTimer every 1 sec
    xQueue = xQueueCreate(3, sizeof(TimeDispMsg));

    // 親の選択をして，誰からタイマーを開始するか決定
    PlayerSelectDialog psd = PlayerSelectDialog(m);
    psd.SelectPlayer();
    Timer::SetCurIdx(psd.GetCurPlayerIdx());

    return;
}

TimerStatus Timer::CountTime(bool count_started){
    int time_tmp = Timer::GetBaseTimeSec();
    timerAlarmEnable(timer);

    TimerStatus status;

    while(1){
        M5.update();
        //! 自分のターンが終わったら押下
        if(M5.BtnA.wasReleased() || M5.BtnC.wasReleased()){
            status = TimerStatus::Continue;
            break;
        }
        //! 順番変更時に押下
        if(M5.BtnB.wasReleased()){
            status = TimerStatus::ChangeOrder;
            break;
        }
        //! ポーズ
        if(! count_started  || (M5.BtnA.pressedFor(1000) && pause_enabled)){
            status = TimerStatus::Pause;
            Timer::Pause();
            status = TimerStatus::Continue;
            count_started = true;
            pause_enabled = false;
        }
        //! リセット
        if(M5.BtnC.pressedFor(2000) && pause_enabled){
            status = TimerStatus::Reset;
            break;
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
    timerAlarmDisable(timer);           // カウントを停止
    Timer::SetBaseTimeSec(time_tmp);    // カウントが終了したので、basetimeを元に戻す

    // 次の人に順番を回す
    if(status == TimerStatus::ChangeOrder){
        PlayerSelectDialog psd = PlayerSelectDialog(Timer::GetMahjongSetting(), Timer::GetCurIdx());
        psd.SelectPlayer();
        Timer::SetCurIdx(psd.GetCurPlayerIdx());
    }else{
        Timer::SetCurIdx((Timer::GetCurIdx() + 1) % Timer::GetMahjongSetting()->GetNumPlayer());
    }

    return status;
}

// press BtnA for 1 sec to continue
void Timer::Pause(){
    timerAlarmDisable(timer);
    TimerDialog::Display(ms, TimerStatus::Pause);
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
    TimerDialog::Display(Timer::GetMahjongSetting(), TimerStatus::Continue);
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