%{
#include "mode.h"
%}

%rename(mode) Mode;
class Mode {

    %rename(get_mode) getMode;
    %rename(get_font_lock) getFontLock;
    %rename(get_key_map) getKeyMap;
public:
    static Mode* getMode(const QString&);
    static Mode* getMode(QWidget*);

    FontLock* getFontLock() const;
    KeyMap* getKeyMap() const;
    void derive(Mode *);
};
