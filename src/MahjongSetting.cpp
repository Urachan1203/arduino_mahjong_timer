#include "MahjongSetting.h"

MahjongSetting::MahjongSetting(){
  this->Init();
}

void MahjongSetting::Init(){
  this->SetNumPlayer(4);
  this->SetLimitTimeSec(300);
  return;
}

void MahjongSetting::SetNumPlayer(int num_player){
  this->num_player = num_player;
  return;
}

void MahjongSetting::SetLimitTimeSec(int limit_time_sec){
  this->limit_time_mu = limit_time_sec * 1000 * 1000;
  return;
}