/***************************************************************************
 *   Copyright (C) 2002 by Yann Hodique                                    *
 *   Yann.Hodique@lifl.fr                                                  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#ifndef _MTPFILTER_H_
#define _MTPFILTER_H_

#include <vector>

#include <qstring.h>

/**
 *
 * Yann Hodique
 **/

class GlobalFilter;
class BlockFilter;
class LineFilter;
class ItemFilter;
class InputFilter;
class QDomDocument;
class MtpContext;

class MtpFilter {

    typedef enum {
        Global = 0,
        Block,
        Line,
        Item
    } FilterType;

public:
    MtpFilter(QDomDocument*, MtpContext*);
    ~MtpFilter();

    QString filterIn(const QString &);
    QString filterOut(const QString &);
    void addGlobalFilter(GlobalFilter*);
    void addBlockFilter(BlockFilter*);
    void addLineFilter(LineFilter*);
    void addItemFilter(ItemFilter*);
    void addInputFilter(InputFilter*);

    InputFilter * getInputFilter(const QString& name);

    void setObsolete() {obsolete = true;}

private:
    std::vector<GlobalFilter*> global;
    std::vector<BlockFilter*> block;
    std::vector<LineFilter*> line;
    std::vector<ItemFilter*> item;
    std::vector<InputFilter*> input, queue;

    BlockFilter *current_block;

    QDomDocument* m_dom;
    MtpContext* m_context;
    bool obsolete;
};

#endif
