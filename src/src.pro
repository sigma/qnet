# File generated by kdevelop's qmake manager. 
# ------------------------------------------- 
# Subdir relative project main directory: ./src
# Target is an application:  ../bin/qnet

DBFILE = qnet.db
LANGUAGE = C++
SOURCES += main.cpp \
           qnet.cpp \
           telnetmanager.cpp \
           MtpFilter.cpp \
           GlobalFilter.cpp \
           BlockFilter.cpp \
           LineFilter.cpp \
           ItemFilter.cpp \
           Filter.cpp \
           ChatSession.cpp \
           InputFilter.cpp \
           domutil.cpp \
           SessionsDialog.cpp \
           UrlSettings.cpp \
           PrefixSettings.cpp \
           MtpRegExp.cpp \
           remotecontrol.cpp \
           chatpage.cpp 
HEADERS += qnet.h \
           telnetmanager.h \
           MtpFilter.h \
           GlobalFilter.h \
           BlockFilter.h \
           LineFilter.h \
           ItemFilter.h \
           Filter.h \
           ChatSession.h \
           InputFilter.h \
           version.h \
           domutil.h \
           SessionsDialog.h \
           UrlSettings.h \
           PrefixSettings.h \
           MtpRegExp.h \
           remotecontrol.h \
           chatpage.h 
IMAGES += images/filenew \
          images/fileopen \
          images/filesave \
          images/print \
          images/undo \
          images/redo \
          images/editcut \
          images/editcopy \
          images/editpaste \
          images/searchfind 
FORMS += qnet_base.ui \
         connectionbox.ui \
         sessionsdialogbase.ui \
         mtpfilterssettings.ui \
         mtpsettings.ui \
         urlsettingsbase.ui \
         prefixsettingsbase.ui \
         fortunesettings.ui \
         appearancesettings.ui 
TEMPLATE = app 
CONFIG += release \
          warn_on \
          qt \
          thread 
TARGET = ../bin/qnet 
QMAKE_CXXFLAGS_DEBUG += -g3 \
                        -pg \
                        -Werror \
                        -ansi \
                        -pedantic 
QMAKE_CXXFLAGS_RELEASE += -Os \
                          -Werror \
                          -ansi \
                          -pedantic 
OBJECTS_DIR = .obj 
MOC_DIR = .moc 
INCLUDEPATH = ../interfaces 
LIBS += ../interfaces/libinterfaces.a 
TARGETDEPS += ../interfaces/libinterfaces.a 
