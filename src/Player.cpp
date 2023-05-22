#include "Player.h"
#include <string.h>

Player::Player(){
    
}

Player::Player(char* player_name, int time_remain_sec){
    this->SetPlayerName(player_name);
    this->SetTimeRemainSec(time_remain_sec);
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