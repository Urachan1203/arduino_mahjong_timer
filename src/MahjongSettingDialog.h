#include <M5Stack.h>
#include "MahjongSetting.h"
#include "DialogManager.h"

#ifndef INCLUDED_MAHJONG_SETTING_DIALOG
#define INCLUDED_MAHJONG_SETTING_DIALOG

class MahjongSettingDialog {
  private:
  MahjongSetting* setting;
  int cur_idx;

  public:
  MahjongSettingDialog(MahjongSetting* setting, int cur_idx);
  void SetSetting(MahjongSetting* setting);
  MahjongSetting* GetSetting();
  void SetCurIdx(int idx);
  int GetCurIdx();
  void Display();
  void DoSetting(DialogManager* dm);
};

#endif