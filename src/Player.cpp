#include "Player.h"
#include <string.h>
#include <LiquidCrystal_I2C.h>
#include "PlayerLcd.h"
#include <stdint.h>

#include <M5Stack.h>

Player::Player(){

}

Player::Player(char* player_name, int time_remain_sec, uint8_t addr){
    this->PlayerLcdInit(addr);
    this->SetPlayerName(player_name);
    this->SetTimeRemainSec(time_remain_sec);
}

LiquidCrystal_I2C Player::GetPlayerLcd(){
    return this->player_lcd;
}

void Player::PlayerLcdInit(uint8_t addr){

    Serial.println(addr);
    this->player_lcd = LiquidCrystal_I2C(addr, 16, 2);
    this->player_lcd.init();
    this->player_lcd.backlight();
    this->player_lcd.clear();
    this->player_lcd.setCursor(0, 0);
    this->player_lcd.print("Successfully");
    this->player_lcd.setCursor(0, 1);
    this->player_lcd.print("Initialized!");    
    
    return;
}

char* Player::GetPlayerName(){
    return this->player_name;
}

void Player::SetPlayerName(char* player_name){
    strcpy(this->player_name, player_name);
    return;
}

int Player::GetTimeRemainSec(){
    return this->time_remain_sec;
}

void Player::SetTimeRemainSec(int time_remain_sec){
    this->time_remain_sec = time_remain_sec;
    return;
}