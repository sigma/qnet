%{
#include "interactionarea.h"
%}

%rename(interaction_area) InteractionArea;
class InteractionArea {
    %rename(display) slotDisplay;
    %rename(add_positive_filter) addPositiveFilter;
    %rename(add_negative_filter) addNegativeFilter;
    %rename(set_display_by_default) setDisplayByDefault;
public slots:
    virtual void slotDisplay(const QString& msg);

public:
    void addPositiveFilter(const QString& beg, const QString& beg_repl = "\\0",
                           const QString& end = QString::null, const QString& end_repl = "\\0",
                           const QString& middle = ".*", const QString& middle_repl = "\\0");
    void addNegativeFilter(const QString& beg, const QString& beg_repl = "\\0",
                           const QString& end = QString::null, const QString& end_repl = "\\0",
                           const QString& middle = ".*", const QString& middle_repl = "\\0");

    void setDisplayByDefault(bool b = true);

};	// end of class InteractionArea
