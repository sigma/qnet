# File generated by kdevelop's qmake manager. 
# ------------------------------------------- 
# Subdir relative project main directory: ./plugins/browser
# Target is a library:  

SOURCES += browserpage.cpp 
HEADERS += browserpage.h 
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
