#include "MahjongSetting.h"
#include "Player.h"
#include <string.h>
#include "PlayerLcd.h"
#include <M5Stack.h>

#define PLAYER_NUM_INIT 4
#define MAX_PLAYER_NAME_STRLEN 6  // 5 + null string
#define BASE_TIME_SEC 10

MahjongSetting::MahjongSetting(){
  this->SetNumPlayer(PLAYER_NUM_INIT);
  this->SetBaseTimeSec(BASE_TIME_SEC);

  // create display name of each player
  for(int i = 0; i < PLAYER_NUM_INIT; i++){
    char name[MAX_PLAYER_NAME_STRLEN] = "p";
    name[1] = (i + 1) + '0';  // int to char, +1 for display name
    Player p = Player(name, 300, PlayerLcd::lcd_addr_list[i]);
    this->SetPlayer(i, p);
  }
}

void MahjongSetting::SetNumPlayer(int num_player){
  this->num_player = num_player;
  return;
}

int MahjongSetting::GetNumPlayer(){
  return this->num_player;
}

void MahjongSetting::SetPlayer(int idx, Player p){
  (this->players)[idx] = p;
  return; 
}

Player* MahjongSetting::GetPlayer(int idx){
  return &(this->players[idx]);
}

void MahjongSetting::SetBaseTimeSec(int base_time_sec){
  this->base_time_sec = base_time_sec;
  return;
}

int MahjongSetting::GetBaseTimeSec(){
  return this->base_time_sec;
}