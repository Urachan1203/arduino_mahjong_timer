#include <M5Stack.h>
#include <LiquidCrystal_I2C.h>
#include "MahjongSetting.h"
#include "MahjongSettingDialog.h"
#include "Timer.h"

MahjongSetting ms;

void SystemInit(){
  M5.begin();
  Serial.begin(115200);
}

void setup(){
  SystemInit();
  ms = MahjongSetting();
  MahjongSettingDialog msd = MahjongSettingDialog(&ms, 0);
  msd.DoSetting();
}

void loop(){
  Timer::Init(0, &ms);
  bool count_started = false;

  while(1){    
    if(TimerStatus::Reset == Timer::CountTime(count_started)) break;
    count_started = true;
  }
}