%{
#include "fontlock.h"
%}

%rename(face) Face;
class Face {
public:
    Face(const QString& family, const QString& color, int size, int weight, int italic);
};

%rename(pattern) Pattern;
class Pattern {
public:
    Pattern(const QString& str);
    void add(int i, Face f);
};

%rename(block_pattern) BlockPattern;
class BlockPattern {
public:
    BlockPattern(const Pattern& b, const Pattern &e, const Pattern &m);
};

%rename(font_lock) FontLock;
class FontLock {
    %rename(add_pattern) addPattern(const Pattern&);
    %rename(add_multi_pattern) addMultiLinePattern(const BlockPattern&);
public:
    void addPattern(const Pattern&);
    void addMultiLinePattern(const BlockPattern&);
    void clear();
};
