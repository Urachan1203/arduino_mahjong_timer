#include "MahjongSettingDialog.h"
#include <M5Stack.h>

MahjongSettingDialog::MahjongSettingDialog(MahjongSetting setting){
    // SetM5(M5S);
    SetSetting(setting);
    M5.Lcd.println("SettingDialog launched.");
}

void MahjongSettingDialog::SetSetting(MahjongSetting setting){
    this->setting = setting;
    return;
}

// M5Stack* MahjongSettingDialog::GetM5(){
//     return this->M5Stack;
// }

// void MahjongSettingDialog::SetM5(M5Stack* M5S){
//     this->M5Stack = M5S;
//     return; 
// }