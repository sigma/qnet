%{
#include "floatingtab.h"
%}

%rename(floating_tab) FloatingTab;
class FloatingTab : public QWidget {

    %rename(add_tab) addTab;
    %rename(current_widget) currentWidget;
    %rename(insert_tab) insertTab;
    %rename(remove_tab) removeTab;
    %rename(tab_text) tabText;
public:
    FloatingTab(QWidget *parent = 0);

    int addTab ( QWidget * child, const QString & label );
    QWidget * currentWidget () const;
    int insertTab ( int index, QWidget * w, const QString & label );
    void removeTab ( int index );
    QString tabText ( int index ) const;
};	// end of class FloatingTab
