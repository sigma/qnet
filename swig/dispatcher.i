%{
#include "dispatcher.h"
%}

%rename(dispatcher) Dispatcher;
class Dispatcher {

    %rename(get_internal_append_hook) getAppendHook;
    %rename(add_interaction_area) addInteractionArea;
    %rename(append_text) appendText;
public:
    Dispatcher(MtpProtocol * p, QObject *parent = 0);
    SCM getAppendHook();
    void addInteractionArea(InteractionArea* area);
    void appendText(const QString& txt);
};
