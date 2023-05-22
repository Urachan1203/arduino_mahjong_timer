#include <M5Stack.h>
#include "MahjongSetting.h"

#ifndef INCLUDED_MAHJONG_SETTING_DIALOG
#define INCLUDED_MAHJONG_SETTING_DIALOG

class MahjongSettingDialog {
  private:
  MahjongSetting setting;
  // M5Stack* M5Stack;

  public:
  // MahjongSettingDialog(MahjongSetting* setting, M5Stack* M5S);
  MahjongSettingDialog(MahjongSetting setting);
  void SetSetting(MahjongSetting setting);
  // M5Stack* GetM5();
  // void SetM5(M5Stack* M5S);
};

#endif