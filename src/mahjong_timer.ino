#include "MahjongSetting.h"
#include "MahjongSettingDialog.h"
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
  
}