#include "MahjongSettingDialog.h"
#include "DialogManager.h"
#include "Player.h"
#include <M5Stack.h>

MahjongSettingDialog::MahjongSettingDialog(MahjongSetting* setting, int cur_idx){
    SetSetting(setting);
    SetCurIdx(cur_idx);
}

void MahjongSettingDialog::SetSetting(MahjongSetting* setting){
    this->setting = setting;
    return;
}

MahjongSetting* MahjongSettingDialog::GetSetting(){
    return this->setting;
}

int MahjongSettingDialog::GetCurIdx(){
    return this->cur_idx;
}

void MahjongSettingDialog::SetCurIdx(int idx){
    this->cur_idx = idx;
    return;
}

void MahjongSettingDialog::Display(){
    MahjongSetting* s = GetSetting();

    int num_player = s->GetNumPlayer();

    M5.Lcd.setTextSize(3);
    M5.Lcd.setCursor(10, 10);
    M5.Lcd.println("Mahjong Timer");
    M5.Lcd.setTextSize(2);
    M5.Lcd.setCursor(250, 25);
    M5.Lcd.println("v0.0");
    M5.Lcd.setTextSize(3);
    M5.Lcd.setCursor(10, 40);
    if(num_player == 4) M5.Lcd.println("4 Player");
    else M5.Lcd.println("3 Player");

    M5.Lcd.setTextSize(1);
    M5.Lcd.setCursor(1, 220);
    M5.Lcd.println("select player");
    M5.Lcd.setCursor(1, 230);
    M5.Lcd.println("switch yomma/samma");
    M5.Lcd.setCursor(130, 220);
    M5.Lcd.println("set time +");
    M5.Lcd.setCursor(250, 220);
    M5.Lcd.println("set time -");
    M5.Lcd.setCursor(250, 230);
    M5.Lcd.println("exit");
    

    for(int i = 0; i < s->GetNumPlayer(); i++){
        M5.Lcd.setTextSize(3);
        Player* p = s->GetPlayer(i);
        if(this->cur_idx == i){
            M5.Lcd.setCursor(60, 80 + 30 * i);
            M5.Lcd.println("x");
        }
        M5.Lcd.setCursor(110, 80 + 30 * i);
        M5.Lcd.println(p->GetPlayerName());
        M5.Lcd.setCursor(160, 80 + 30 * i);
        M5.Lcd.println(p->GetTimeRemainSec());
    }
    return;
}

void MahjongSettingDialog::DoSetting(DialogManager* dm){
    
    this->Display();
    dm->SetActiveDialog(ActiveDialog::MahjongSettingDialog);

    int num_player = this->GetSetting()->GetNumPlayer();

    while(1){
        M5.update();

        // select player
        if (M5.BtnA.wasReleased()){
            this->cur_idx = (cur_idx + 1) % num_player;
            M5.Lcd.clear();
            this->Display();
        }

        // select game mode (4player or samma)
        if (M5.BtnA.wasReleasefor(1000)){
            if (this->GetSetting()->GetNumPlayer() == 4) this->GetSetting()->SetNumPlayer(3);
            else if (this->GetSetting()->GetNumPlayer() == 3) this->GetSetting()->SetNumPlayer(4);
            num_player = this->GetSetting()->GetNumPlayer(); //update
            // M5.Lcd.clear();
            this->Display();
        }
        
        // set time limit for each player
        if (M5.BtnB.wasReleased()){
            int cur_time = this->GetSetting()->GetPlayer(this->cur_idx)->GetTimeRemainSec();
            this->GetSetting()->GetPlayer(this->cur_idx)->SetTimeRemainSec((cur_time + 10) % 400);
            // M5.Lcd.clear();
            this->Display();
        }

        if (M5.BtnC.wasReleased()){
            int cur_time = this->GetSetting()->GetPlayer(this->cur_idx)->GetTimeRemainSec();
            this->GetSetting()->GetPlayer(this->cur_idx)->SetTimeRemainSec((cur_time - 10) % 400);
            // M5.Lcd.clear();
            this->Display();
        }

        // exit setting
        if (M5.BtnC.wasReleasefor(1000)) break;
    }

    return;
}