# File generated by kdevelop's qmake manager. 
# ------------------------------------------- 
# Subdir relative project main directory: ./plugins/drawing
# Target is a library:  

SOURCES += canvas.cpp \
           painter.cpp 
HEADERS += canvas.h \
           painter.h \
../../interfaces/master.h \
../../interfaces/page.h
TEMPLATE = lib 
CONFIG += release \
          warn_on \
          qt \
          thread 
INCLUDEPATH = ../../interfaces 