#include "MahjongSetting.h"
#include "MahjongSettingDialog.h"
#include "Timer.h"
#include "TimerDialog.h"
#include "DialogManager.h"
#include <M5Stack.h>
#include "PlayerLcd.h"

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
// #include <stdint.h>
// void setup(){
//   LiquidCrystal_I2C lcds[4];
//   uint8_t addr[4] = {0x23, 0x25, 0x26, 0x27};

//   for(int i = 0; i < 4; i++){
//     LiquidCrystal_I2C lcd = LiquidCrystal_I2C(addr[i], 16, 2);
//     lcd.init();
//     lcd.init();
//     lcd.backlight();
//     lcd.clear();
//     lcd.setCursor(0, 0);
//     lcds[i] = lcd;
//   }
//   for(int i = 0; i < 4; i++){
//     lcds[i].print("init");
//   }
// }

// void loop(){

// }