%{
#include <QWidget>
%}

%rename(qwidget) QWidget;
class QWidget {
    %rename(set_focus) setFocus;
public:
    void setFocus();
};
