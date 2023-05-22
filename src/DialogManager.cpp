#include "DialogManager.h"

DialogManager::DialogManager(){
}

void DialogManager::SetActiveDialog(ActiveDialog active){
    this->active = active;
    return;
}

ActiveDialog DialogManager::GetActiveDialog(){
    return this->active;
}