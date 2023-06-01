#ifndef INCLUDED_PLAYER_SELECT_DIALOG
#define INCLUDED_PLAYER_SELECT_DIALOG

#include "MahjongSetting.h"
#include <stdint.h>

class PlayerSelectDialog{
    private:
    uint8_t player_num;
    uint8_t cur_player_idx;

    public:
    PlayerSelectDialog(MahjongSetting* ms);
    PlayerSelectDialog(MahjongSetting* ms, uint8_t idx);
    uint8_t GetPlayerNum();
    void SetPlayerNum(uint8_t num);
    uint8_t GetCurPlayerIdx();
    void SetCurPlayerIdx(uint8_t idx);
    void Display();
    int ListenButtonInput();
    void SelectPlayer();
};

#endif