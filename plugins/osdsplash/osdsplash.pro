# File generated by kdevelop's qmake manager. 
# ------------------------------------------- 
# Subdir relative project main directory: ./plugins/splash
# Target is a library:  

SOURCES += osdsplash.cpp 
HEADERS += osdsplash.h 
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
TARGET = ../../lib/osdsplash