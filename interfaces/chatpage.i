%{
#include "chatpage.h"
%}

%name(chat_page)
class ChatPage {
public:
    %name(toggle_user_box) void toggleUserBox();
    %name(font_lock) FontLock * fontLock();

};

