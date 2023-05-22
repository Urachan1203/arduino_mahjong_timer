#include "MahjongSetting.h"
#include "MahjongSettingDialog.h"
#include <M5Stack.h>

void setup(){
  M5.begin();
  MahjongSetting ms = MahjongSetting();
  MahjongSettingDialog msd = MahjongSettingDialog(ms);
}

void loop(){

}