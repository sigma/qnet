%{
#include "mainwin.h"
%}

%nodefault;
%name(mainwin)
class MainWin {
public:
    %name(set_use_dock) void setUseDock();
    %name(qmtp) QMtp* qmtp();
};
