%{
#include "ChatSession.h"
%}

%nodefault;
%name(chatsession)
class ChatSession {
public:
    %name(display_err) void displayStderr(const QString&);
    %name(display_out) void displayStdout(const QString&);
    %name(session_name) const QString &sessionName() const;

    %name(update_filters) void updateFilters();

    %name(chatpage) MainChatPage *chatpage();

    %name(logged_p) bool isLogged() {return login_set;}

    %name(close_session) void closeSession();
    %name(link_clicked) void slotLinkClicked(const QString&);
    %name(reconnect) void slotReconnect();

    %name(kill) void kill(Page*);
    %name(send) void send(const QString&);
    %name(incoming) void incoming(const QString&);
    %name(outgoing) void outgoing(const QString&);
};
