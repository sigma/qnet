TEMPLATE = app

CONFIG += release warn_on precompile_header

QMAKE_LFLAGS_DEBUG += -lguile
QMAKE_LFLAGS_RELEASE += -lguile

QMAKE_CXXFLAGS_DEBUG += -ansi -Wall -O0 -g3 -Wno-long-long
QMAKE_CXXFLAGS_RELEASE += -ansi -Wall -O0 -g3 -Wno-long-long -Werror

HEADERS += dispatcher.h launcher.h mtpprotocol.h floatingtab.h floatingtabbar.h	\
	   mainwindow.h interactionarea.h mtpinput.h mtpoutput.h mtparea.h	\
	   mtpbrowser.h mtpedit.h mtpinfo.h mode.h fontlock.h keymap.h scm.h	\
	   mtpsocket.h

SOURCES += dispatcher.cpp launcher.cpp mtpprotocol.cpp floatingtab.cpp		\
	   floatingtabbar.cpp mainwindow.cpp main.cpp interactionarea.cpp	\
	   mtparea.cpp mtpbrowser.cpp mtpedit.cpp mtpinfo.cpp mode.cpp		\
	   fontlock.cpp keymap.cpp scm.cpp mtpsocket.cpp

PRECOMPILED_HEADER = all.h

QT += network

MOC_DIR=./.moc
OBJECTS_DIR=./.obj

LIBS += -L../swig -lswig

POST_TARGETDEPS += ../swig/libswig.a
