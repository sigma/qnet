%{
#include "qnet.h"
%}

%name(qnet)
class QMtp {
public:
    %name(load_config_file) bool loadConfigFile();
    %name(save_config_file) bool saveConfigFile();
    %name(get_new_page) Page * getNewPage(const QString&, const QString&, ChatSession *, bool pop = true);
    %name(configure) void slotConfigure();
    %name(store_config) void slotStoreConfig();
    %name(open) void fileNew();
    %name(save) void fileSaveAs();
    %name(exit) void fileExit();
    %name(close_current_tab) void closeCurrentTab();
    %name(close_tab) void closeTab(QWidget *);

    %name(load_plugin) bool loadPlugin(const QString&);
    %name(unload_plugin) bool unloadPlugin(const QString&);

    %name(refresh_menu) void refreshMenu();
    %name(load_stylesheet) void loadStyleSheet();

    %name(launch_session) void launchSession(const QString&);
    %name(load_plugins) void loadPlugins();
    %name(unload_plugins) void unloadPlugins();
    %name(reload_plugins) void reloadPlugins(const QStringList&);

    %name(sessions_number) int sessionsNumber();
    %name(session) ChatSession *session(int i);
};
