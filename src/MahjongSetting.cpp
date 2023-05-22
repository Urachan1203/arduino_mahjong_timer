#include "MahjongSetting.h"
#include "Player.h"
#include <string.h>

#define PLAYER_NUM_INIT 4
#define MAX_PLAYER_NAME_STRLEN 6  // 5 + null string

MahjongSetting::MahjongSetting(){
  this->SetNumPlayer(PLAYER_NUM_INIT);
  for(int i = 0; i < PLAYER_NUM_INIT; i++){

    // create display name of each player
    char name[MAX_PLAYER_NAME_STRLEN] = "p";
    name[1] = (i + 1) + '0';  // int to char, +1 for display name

    Player p = Player(name, 300);
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