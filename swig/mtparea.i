%{
#include "mtparea.h"
%}

%rename(mtparea) MtpArea;
class MtpArea : public InteractionArea, public QWidget {

    %rename(get_output) getOutput;
    %rename(get_input) getInput;
    %rename(toggle_user_box) toggleUserBox;
public:
    MtpArea(QWidget *parent = 0);

    MtpOutput * getOutput();
    MtpInput * getInput();

    void toggleUserBox();
};
