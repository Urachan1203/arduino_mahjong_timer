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

// #include <LiquidCrystal_I2C.h>

// //アドレス0x27 １６文字２行の液晶
// LiquidCrystal_I2C lcd(0x27, 16, 2);

// void setup() {
//   lcd.init();
//   lcd.backlight();
//   lcd.clear();
//   lcd.setCursor(0, 0);
//   lcd.print("abc");
//   lcd.setCursor(3, 1);
//   lcd.print("DEF");
// }

// void loop() {
// }