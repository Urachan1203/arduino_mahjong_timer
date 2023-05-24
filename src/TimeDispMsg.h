#ifndef INCLUDED_TIME_DISP_MSG
#define INCLUDED_TIME_DISP_MSG

struct TimeDispMsg {
    public:
    int idx;
    int time_remain;
    int time_base;

    TimeDispMsg(int i, int tr, int tb){
        idx = i;
        time_remain = tr;
        time_base = tb;
    }

    TimeDispMsg(){}
};

#endif