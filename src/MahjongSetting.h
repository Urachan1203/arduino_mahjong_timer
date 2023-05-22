#ifndef INCLUDED_MAHJONG_SETTING
#define INCLUDED_MAHJONG_SETTING

class MahjongSetting {

  private:
  int num_player;
  int limit_time_mu;
  
  public:
  MahjongSetting();
  void Init();
  void SetNumPlayer(int num_player);
  void SetLimitTimeSec(int limit_time_sec);
  
};

#endif