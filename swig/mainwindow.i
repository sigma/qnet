%{
#include "mainwindow.h"
%}

%nodefault;
%rename(main_window) MainWindow;
class MainWindow {
    %rename(get_floating_tab) getFloatingTab();
    %rename(get_tool_bar) getToolBar();
public:
    FloatingTab* getFloatingTab();
    ToolBar* getToolBar();
};
