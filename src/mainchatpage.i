%{
#include "MainChatPage.h"
%}

%name(main_chat_page)
class MainChatPage : public ChatPage {
public:
    %name(toggle_user_box) void toggleUserBox();
    %name(font_lock) FontLock * fontLock();
};
