%{
#include "mainwindow.h"
%}

%nodefault;
%name(mainwindow)
class MainWindow {
public:
    %name(get_floating_tab) FloatingTab* getFloatingTab() {return ft;}
    %name(get_tool_bar) ToolBar* getToolBar() {return toolbar;}
};
