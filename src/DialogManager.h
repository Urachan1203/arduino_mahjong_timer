#ifndef INCLUDED_DIALOG_MANAGER
#define INCLUDED_DIALOG_MANAGER

enum class ActiveDialog{
    MahjongSettingDialog,
};

class DialogManager {
    private:
    ActiveDialog active;

    public:
    DialogManager();
    void SetActiveDialog(ActiveDialog active);
    ActiveDialog GetActiveDialog();
};

#endif