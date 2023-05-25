#include "MahjongSetting.h"
#include "MahjongSettingDialog.h"
#include "Timer.h"
#include "TimerDialog.h"
#include "DialogManager.h"
#include <M5Stack.h>
#include "PlayerLcd.h"
#include <LiquidCrystal_I2C.h>

MahjongSetting ms;

void SystemInit(){
  M5.begin();
  Serial.begin(115200);
}

void setup(){
  SystemInit();
  
  ms = MahjongSetting();
  DialogManager dm = DialogManager(); 

  // create and display setting dialog 
  MahjongSettingDialog msd = MahjongSettingDialog(&ms, 0);
  msd.DoSetting(&dm);

}

void loop(){
  // TODO : 親プレイヤーの選択を行う（PlayerSelectorDialog を作る？順番割り込みの実装で使い回せそう）

  // resetされたらここからスタートする
  Timer::Init(0, &ms);

  bool count_started = false;
  while(1){    
     // TODO : 適当なステータスコードを返す
     // 0 : カウント継続 -> while を回り続ける
     // 1 : pause -> while の中で止まる
     // 2 : reset timer -> break
     // 3 : go setting -> break & show setting dialog
    if(TimerCommand::Reset == Timer::CountTime(count_started)) break;
    count_started = true;
  }

}