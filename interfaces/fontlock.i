%{
#include "fontlock.h"
%}

%name(face)
class Face {
public:
    Face(const QString& font, const QString& color);
};

%name(pattern)
class Pattern {
public:
    Pattern(const QString& str);
    void add(int i, Face f);
};

%name(block_pattern)
class BlockPattern {
public:
    BlockPattern(const Pattern& b, const Pattern &e, const Pattern &m);
};

%name(font_lock)
class FontLock {
public:
    %name(add_pattern) void addPattern(const Pattern&);
    %name(add_multi_pattern) void addMultiLinePattern(const BlockPattern&);
    %name(clear) void clear();
};
