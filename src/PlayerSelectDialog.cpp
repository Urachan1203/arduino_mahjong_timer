#include "PlayerSelectDialog.h"
#include "MahjongSetting.h"
#include "M5ButtonWrapper.h"
#include <M5Stack.h>

const uint16_t CURSOR_X[4] = {150, 290, 150, 0};
const uint16_t CURSOR_Y[4] = {190, 100, 0, 100};

#define SELECT_EXIT -1


PlayerSelectDialog::PlayerSelectDialog(MahjongSetting* ms){
    SetPlayerNum(ms->GetNumPlayer());
    SetCurPlayerIdx(0); // set p1 as selected player
}

PlayerSelectDialog::PlayerSelectDialog(MahjongSetting* ms, uint8_t idx){
    SetPlayerNum(ms->GetNumPlayer());
    SetCurPlayerIdx(idx);
}

uint8_t PlayerSelectDialog::GetPlayerNum(){
    return this->player_num;
}

void PlayerSelectDialog::SetPlayerNum(uint8_t num){
    this->player_num = num;
    return;
}

uint8_t PlayerSelectDialog::GetCurPlayerIdx(){
    return this->cur_player_idx;
}

void PlayerSelectDialog::SetCurPlayerIdx(uint8_t idx){
    this->cur_player_idx = idx;
    return;
}

void PlayerSelectDialog::Display(){
    uint8_t cur_idx = this->GetCurPlayerIdx();
    M5.Lcd.clear();
    
    M5.Lcd.setTextSize(3);
    M5.Lcd.setCursor(0, 0);
    M5.Lcd.println("Select");
    M5.Lcd.println("Player");

    M5.Lcd.setTextSize(1);
    M5.Lcd.setCursor(1, 220);
    M5.Lcd.println("< select player");
    M5.Lcd.setCursor(130, 220);
    M5.Lcd.println("select player >");

    M5.Lcd.setCursor(250, 220);
    M5.Lcd.println("OK");

    // print marker
    M5.Lcd.setTextSize(3);
    M5.Lcd.setCursor(CURSOR_X[cur_idx], CURSOR_Y[cur_idx]);
    M5.Lcd.println("x");
}

int PlayerSelectDialog::ListenButtonInput(){
    while(1){
        M5.update();
        if(BtnA.wasReleased()){
            return (this->GetCurPlayerIdx() + 3) % this->GetPlayerNum();    // clockwise
        }
        if(BtnB.wasReleased()){
            return (this->GetCurPlayerIdx() + 1) % this->GetPlayerNum();    // counterclockwise
        }
        if(BtnC.wasReleased()){
            return SELECT_EXIT;
        }
    }
}

void PlayerSelectDialog::SelectPlayer(){
    this->Display();
    M5Button::RefleshAllButton();

    while(1){    
        int input = this->ListenButtonInput();
        if (input == SELECT_EXIT) return;
        this->SetCurPlayerIdx(input);
        this->Display();
    }
    return;
}