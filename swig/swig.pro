TEMPLATE = lib

CONFIG += release warn_off precompile_header staticlib

SWIG = swig
SWIG_FLAGS = -guile -c++ -module internal -scm -Linkage module

QMAKE_LFLAGS_DEBUG += -lguile
QMAKE_LFLAGS_RELEASE += -lguile

QMAKE_CXXFLAGS_DEBUG += -ansi -Wall -O0 -g3 -Wno-long-long
QMAKE_CXXFLAGS_RELEASE += -ansi -Wall -O0 -g3 -Wno-long-long

SWIG_TARGET = main_wrap.cxx
SOURCES += $$SWIG_TARGET

SWIG_MAIN = main.i
SWIG_HEADERS = fontlock.i mainwindow.i qstring.i mtpsocket.i mode.i	\
	dispatcher.i mtpprotocol.i qiodevice.i mtparea.i

INCLUDEPATH += ../src

QT += network

MOC_DIR=./.moc
OBJECTS_DIR=./.obj

guile.target = $$SWIG_TARGET
guile.commands = $$SWIG $$SWIG_FLAGS -o $$SWIG_TARGET $$SWIG_MAIN
guile.depends = $$SWIG_MAIN $$SWIG_HEADERS

QMAKE_CLEAN += $$SWIG_TARGET

QMAKE_EXTRA_UNIX_TARGETS += guile
PRE_TARGETDEPS += $$guile.target