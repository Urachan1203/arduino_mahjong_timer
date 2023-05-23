#include "MahjongSetting.h"
#include "MahjongSettingDialog.h"
#include "Timer.h"
#include "TimerDialog.h"
#include "DialogManager.h"
#include <M5Stack.h>

MahjongSetting ms = MahjongSetting();
DialogManager dm = DialogManager();

void setup(){
  M5.begin();

  // create and display setting dialog 
  MahjongSettingDialog msd = MahjongSettingDialog(&ms, 0);
  msd.DoSetting(&dm);

  
}

void loop(){
  // TODO : 親プレイヤーの選択を行う（PlayerSelectorDialog を作る？順番割り込みの実装で使い回せそう）

  // counting
  Timer::Init(0, &ms);

  
  while(1){
    
     // TODO : 適当なステータスコードを返す
     // 0 : カウント継続 -> while を回り続ける
     // 1 : pause -> while の中で止まる
     // 2 : reset timer -> break
     // 3 : go setting -> break & show setting dialog
    Timer::CountTime();
  }

}