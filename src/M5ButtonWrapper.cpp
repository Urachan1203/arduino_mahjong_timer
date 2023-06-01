#include <M5Stack.h>
#include <time.h>
#include "M5ButtonWrapper.h"

M5Button BtnA = M5Button(&M5.BtnA);
M5Button BtnB = M5Button(&M5.BtnB);
M5Button BtnC = M5Button(&M5.BtnC);

time_t tmp;

M5Button::M5Button(Button* b){
    this->btn = b;
    this->init_pressed_time = nullptr;
    this->active = true;
}

// ボタン長押しによってコールされたダイアログが表示された後にこれを呼ぶこと
void M5Button::RefleshAllButton(){
    while(1){
        M5.update();
        if(M5.BtnA.isReleased() && M5.BtnB.isReleased() && M5.BtnC.isReleased()){
            BtnA.ActivateButton();
            BtnB.ActivateButton();
            BtnC.ActivateButton();
            break;
        }
    }
}

void M5Button::SetInitPressedtime(){
    tmp = time(NULL);
    this->init_pressed_time = &tmp;
}

time_t* M5Button::GetInitPressedTime(){
    return this->init_pressed_time;
}

void M5Button::ActivateButton(){
    this->active = true;
}

void M5Button::DeactivateButton(){
    this->active = false;
}

bool M5Button::wasReleased(){
    if(this->active && this->btn->wasReleased()) return true;
    else return false;
}

bool M5Button::isLongPressed(double sec){

    time_t* init_pressed_time = this->GetInitPressedTime();

    if(this->btn->isReleased()) {
        this->ActivateButton();
        this->init_pressed_time = nullptr;
        return false;
    }

    if(!this->active){
        return false;
    }
    
    // initial push
    if(this->btn->isPressed() && init_pressed_time == nullptr){
        this->SetInitPressedtime();
        return false;
    }

    if(this->btn->isPressed() && init_pressed_time != nullptr){
        time_t now = time(NULL);
        Serial.println("pushed");
        Serial.println(difftime(now, *init_pressed_time));
        if(difftime(now, *init_pressed_time) > sec){
            this->DeactivateButton();
            return true;
        }
    }
    return false;
}