#ifndef INCLUDED_MAHJONG_SETTING
#define INCLUDED_MAHJONG_SETTING

#include "Player.h"

#define MAX_PLAYER_NUM 4

class MahjongSetting {

  private:
  int num_player;
  Player players[MAX_PLAYER_NUM];
  
  public:
  MahjongSetting();
  void SetNumPlayer(int num_player);
  int GetNumPlayer();
  void SetPlayer(int idx, Player p);
  Player* GetPlayer(int idx);
};

#endif