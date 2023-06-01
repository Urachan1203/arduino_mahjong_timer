#ifndef INCLUDED_TIMER
#define INCLUDED_TIMER

#include "MahjongSetting.h"

enum class TimerStatus{
    Continue,
    ChangeOrder,
    Pause,
    Reset,
    GoSetting,
};

class Timer {
    private:
    static MahjongSetting* ms;
    static int cur_idx;
    static int base_time_sec;
    static int time_remain_sec[MAX_PLAYER_NUM];

    public:
    static void Init(int idx, MahjongSetting* m);
    static TimerStatus CountTime(bool count_started);
    static void Down();
    static void Pause();
    static void SetMahjongSetting(MahjongSetting* m);
    static MahjongSetting* GetMahjongSetting();
    static int GetCurIdx();
    static void SetCurIdx(int idx);
    static int GetBaseTimeSec();
    static void SetBaseTimeSec(int base_time_sec);
    static int GetTimeRemainSec(int idx);
    static void SetTimeRemainSec(int idx, int time_remain_sec);
};

#endif