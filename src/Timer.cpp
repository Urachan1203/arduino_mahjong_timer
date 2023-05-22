#include "Timer.h"
#include "MahjongSetting.h"
#include <MsTimer2.h>
#include <M5Stack.h>

MahjongSetting* Timer::ms;
int Timer::cur_idx;
int Timer::base_time_sec;
int Timer::time_remain_sec[MAX_PLAYER_NUM];

void Timer::Init(int idx, MahjongSetting* m){
    Timer::SetCurIdx(idx);
    Timer::SetBaseTimeSec(m->GetBaseTimeSec());

    for(int i = 0; i < m->GetNumPlayer(); i++){
        Timer::SetTimeRemainSec(i, m->GetPlayer(i)->GetTimeRemainSec());
    }
    return;
}

void Timer::CountTime(){
    int time_tmp = Timer::GetBaseTimeSec();
    MsTimer2::set(1000, Down);
    MsTimer2::start();
    while(1){
        M5.update();
        //! 自分のターンが終わったら押下
        if(M5.BtnA.wasPressed() || M5.BtnC.wasPressed()){
            break;
        }
        //! ポン発生時に押下
        if(M5.BtnB.wasPressed()){
            break;
        }
    }
    MsTimer2::stop();

    Timer::SetBaseTimeSec(time_tmp);    // カウントが終了したので、basetimeを元に戻す

    //! cur_idx を次の人へ
    //! ポン発生時はこの限りではないので、順番割り込みを行うダイアログの実装がTODO
    Timer::SetCurIdx((Timer::GetCurIdx() + 1) % ms->GetNumPlayer());
    return;
}

void Timer::Down(){
    if(Timer::GetBaseTimeSec() > 0){
        Timer::SetBaseTimeSec(Timer::GetBaseTimeSec() - 1);
    }
    else if(Timer::GetTimeRemainSec(Timer::GetCurIdx()) > 0){
        Timer::SetTimeRemainSec(Timer::GetCurIdx(), Timer::GetTimeRemainSec(Timer::GetCurIdx()) - 1);
    }
    return;
}

MahjongSetting* Timer::GetMahjongSetting(){
    return Timer::ms;
}

int Timer::GetCurIdx(){
    return cur_idx;
}

void Timer::SetCurIdx(int idx){
    cur_idx = idx;
    return;
}

int Timer::GetBaseTimeSec(){
    return base_time_sec;
}

void Timer::SetBaseTimeSec(int base_time_sec){
    Timer::base_time_sec = base_time_sec;
    return;
}

int Timer::GetTimeRemainSec(int idx){
    return time_remain_sec[idx];
}

void Timer::SetTimeRemainSec(int idx, int time_remain_sec){
    Timer::time_remain_sec[idx] = time_remain_sec;
    return;
}