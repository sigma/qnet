/***************************************************************************
 *   Copyright (C) 2002 by Yann Hodique                                    *
 *   Yann.Hodique@lifl.fr                                                  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#include "MtpFilter.h"
#include <iostream>

MtpFilter::MtpFilter() {
    current_block = 0;
}


MtpFilter::~MtpFilter() {
    for (std::vector<GlobalFilter*>::iterator it = global.begin(); it != global.end(); ++it)
	delete *it;
    for (std::vector<BlockFilter*>::iterator it = block.begin(); it != block.end(); ++it)
	delete *it;
    for (std::vector<LineFilter*>::iterator it = line.begin(); it != line.end(); ++it)
	delete *it;
    for (std::vector<ItemFilter*>::iterator it = item.begin(); it != item.end(); ++it)
        delete *it;
    for (std::vector<InputFilter*>::iterator it = input.begin(); it != input.end(); ++it)
        delete *it;
    for (std::vector<InputFilter*>::iterator it = queue.begin(); it != queue.end(); ++it)
	delete *it;
}

QString MtpFilter::filterIn(const QString & arg) {
    QString res(arg);

    for (std::vector<InputFilter*>::iterator it = input.begin(); it != input.end(); ++it) {
        if ((*it)->isEnabled()) {
            if ((*it)->applyTo(res)) {
                res = (*it)->getResult();
                if ((*it)->memorize()) queue.push_back(*it);
                }
        }
    }
    return res;
}

QString MtpFilter::filterOut(const QString & arg) {

    QString res(arg);

    // Global Filter
    for (std::vector<GlobalFilter*>::iterator it = global.begin(); it != global.end(); ++it) {
        if ((*it)->isEnabled() && (*it)->applyTo(res)) {
            res = (*it)->getResult();
            if ((*it)->policy() == Filter::Final)
                return res;
            else
                break;
        }
    }

    // Block Filter
    if (current_block) {
        current_block->applyTo(res);
        res = current_block->getResult();
        //std::cerr << res << std::endl;
        bool stop = (current_block->policy() == Filter::Final);
        if (current_block->isFinished())
            current_block = 0;
        if (stop)
            return res;
    } else
        for (std::vector<BlockFilter*>::iterator it = block.begin(); it != block.end(); ++it) {
            if ((*it)->isEnabled()) {
                InputFilter * in;
                if ((!(in = (*it)->getInputDependency())) || ((!queue.empty()) && (queue[0] == in))) {
                    if ((*it)->applyTo(res,BlockFilter::BEGIN)) {
                        //std::cout << "Beginning of Block" << std::endl;
                        current_block = *it;
                        if (in) queue.erase(queue.begin());
                        res = (*it)->getResult();
                        if ((*it)->policy() == Filter::Final)
                            return res;
                        else
                            break;
                    }
                }
            }
        }

    // Line Filter
    for (std::vector<LineFilter*>::iterator it = line.begin(); it != line.end(); ++it) {
        if ((*it)->isEnabled() && (*it)->applyTo(res)) {
            res = (*it)->getResult();
            if ((*it)->policy() == Filter::Final)
                return res;
            else
                break;
        }
    }

    // Item Filter
    for (std::vector<ItemFilter*>::iterator it = item.begin(); it != item.end(); ++it) {
        if ((*it)->isEnabled() && (*it)->applyTo(res)) {
            res = (*it)->getResult();
        }
    }

    return res;
}

void MtpFilter::addGlobalFilter(GlobalFilter * f) {
    global.push_back(f);
}

void MtpFilter::addBlockFilter(BlockFilter * f) {
    block.push_back(f);
}

void MtpFilter::addLineFilter(LineFilter * f) {
    line.push_back(f);
}

void MtpFilter::addItemFilter(ItemFilter * f) {
    item.push_back(f);
}

void MtpFilter::addInputFilter(InputFilter * f) {
    input.push_back(f);
}

InputFilter* MtpFilter::getInputFilter(const QString& name) {
    for(std::vector<InputFilter*>::iterator it = input.begin(); it != input.end(); ++it)
        if ((*it)->getName() == name)
            return (*it);
    return 0;
}
