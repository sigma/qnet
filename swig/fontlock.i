%{
#include "fontlock.h"
%}

%rename(face) Face;
class Face {
    %rename(default_face) defaultFace;
    %rename(set_default_face) setDefaultFace;
public:

    %rename(light) Light;
    %rename(normal) Normal;
    %rename(demi_bold) DemiBold;
    %rename(bold) Bold;
    %rename(black) Black;
    typedef enum {
        Light,
        Normal,
        DemiBold,
        Bold,
        Black
    } Weight;

    Face(const QString& family, const QString& color, int size, int weight, bool italic);

    static const Face& defaultFace() {return default_face;}
    static void setDefaultFace(const Face& f) {default_face = f;}

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
