# File generated by kdevelop's qmake manager.
# -------------------------------------------
# Subdir relative project main directory: ./utils
# Target is a library:

SOURCES += domutil.cpp
HEADERS += domutil.h
TEMPLATE = lib
CONFIG += release \
          warn_on \
          qt \
          thread \
          staticlib
OBJECTS_DIR = .obj
MOC_DIR = .moc
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
