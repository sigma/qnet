%{
#include "interactionarea.h"
%}

%rename(interaction_area) InteractionArea;
class InteractionArea {
public:
    virtual void display(const QString& msg);
};	// end of class InteractionArea
