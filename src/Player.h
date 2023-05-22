#ifndef INCLUDED_PLAYER
#define INCLUDED_PLAYER

#define MAX_PLAYER_NAME_STRLEN 6    // 5 + null string

class Player {
    private:
    char player_name[MAX_PLAYER_NAME_STRLEN];
    int time_remain_sec;

    public:
    Player();
    Player(char* player_name, int time_remain_sec);
    char* GetPlayerName();
    void SetPlayerName(char* player_name);
    int GetTimeRemainSec();
    void SetTimeRemainSec(int time_remain_sec);

};

#endif