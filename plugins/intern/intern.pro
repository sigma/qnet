# File generated by kdevelop's qmake manager.
# -------------------------------------------
# Subdir relative project main directory: ./plugins/affect
# Target is a library:

SOURCES += intern.cpp
HEADERS += intern.h
TEMPLATE = lib
CONFIG += release \
          warn_on \
          qt \
          thread \
          plugin
OBJECTS_DIR = .obj
MOC_DIR = .moc
INCLUDEPATH = ../../interfaces
LIBS += ../../interfaces/libinterfaces.a
TARGETDEPS += ../../interfaces/libinterfaces.a
TARGET = ../../lib/intern
QMAKE_CXXFLAGS_DEBUG += -Werror \
                        -Wall \
                        -ansi \
                        -pedantic \
                        -Wno-long-long \
                        -g3
QMAKE_CXXFLAGS_RELEASE += -Wall \
                          -ansi \
                          -pedantic \
                          -Wno-long-long