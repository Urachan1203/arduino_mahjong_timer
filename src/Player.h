#ifndef INCLUDED_PLAYER
#define INCLUDED_PLAYER

#include <LiquidCrystal_I2C.h>
#include<stdint.h>

#define MAX_PLAYER_NAME_STRLEN 6    // 5 + null string
#define LCD_ADDR_DUMMY 0x00

class Player {
    private:
    char player_name[MAX_PLAYER_NAME_STRLEN];
    int time_remain_sec;
    // LiquidCrystal_I2C player_lcd;

    public:
    Player();
    Player(char* player_name, int time_remain_sec, uint8_t addr);
    LiquidCrystal_I2C GetPlayerLcd();
    void PlayerLcdInit(uint8_t addr);
    char* GetPlayerName();
    void SetPlayerName(char* player_name);
    int GetTimeRemainSec();
    void SetTimeRemainSec(int time_remain_sec);

};

#endif