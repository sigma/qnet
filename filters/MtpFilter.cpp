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
#include "MtpContext.h"
#include "GlobalFilter.h"
#include "BlockFilter.h"
#include "LineFilter.h"
#include "ItemFilter.h"
#include "domutil.h"

//#include <iostream>

MtpFilter::MtpFilter(QDomDocument* dom, MtpContext* context) {
    current_block = 0;
    m_dom = dom;
    m_context = context;
    obsolete = false;

    QStringList filters;

    filters = DomUtil::readListEntry(*m_dom,"/general/filters/input","filter");
    for(QStringList::Iterator it = filters.begin(); it != filters.end(); ++it) {
	InputFilter* f = new InputFilter(*it,DomUtil::readBoolEntry(*m_dom,"/filters/" + *it + "/memorize",false),m_context);
	f->setRegExp(DomUtil::readEntry(*m_dom,"/filters/" + *it + "/regexp"));
	f->setResultPattern(DomUtil::readEntry(*m_dom,"/filters/" + *it + "/result"));
	f->setPolicy((Filter::Policy)DomUtil::readIntEntry(*m_dom,"/filters/" + *it + "/policy",Filter::Transient));
	f->setEnabled(DomUtil::readBoolEntry(*m_dom,"/filters/" + *it + "/active",true));

	addInputFilter(f);
    }

    filters = DomUtil::readListEntry(*m_dom,"/general/filters/item","filter");
    for(QStringList::Iterator it = filters.begin(); it != filters.end(); ++it) {
	ItemFilter* f = new ItemFilter(*it,m_context);
	f->setRegExp(DomUtil::readEntry(*m_dom,"/filters/" + *it + "/regexp"));
	f->setResultPattern(DomUtil::readEntry(*m_dom,"/filters/" + *it + "/result"));
	f->setPolicy((Filter::Policy)DomUtil::readIntEntry(*m_dom,"/filters/" + *it + "/policy",Filter::Transient));
	f->setEnabled(DomUtil::readBoolEntry(*m_dom,"/filters/" + *it + "/active",true));

	addItemFilter(f);
    }

    filters = DomUtil::readListEntry(*m_dom,"/general/filters/line","filter");
    for(QStringList::Iterator it = filters.begin(); it != filters.end(); ++it) {
	LineFilter* f = new LineFilter(*it,m_context);
	f->setRegExp(DomUtil::readEntry(*m_dom,"/filters/" + *it + "/regexp"));
	f->setResultPattern(DomUtil::readEntry(*m_dom,"/filters/" + *it + "/result"));
	f->setPolicy((Filter::Policy)DomUtil::readIntEntry(*m_dom,"/filters/" + *it + "/policy",Filter::Transient));
	f->setEnabled(DomUtil::readBoolEntry(*m_dom,"/filters/" + *it + "/active",true));

	addLineFilter(f);
    }

    filters = DomUtil::readListEntry(*m_dom,"/general/filters/block","filter");
    for(QStringList::Iterator it = filters.begin(); it != filters.end(); ++it) {
	BlockFilter* f = new BlockFilter(*it,m_context);
	f->setBeginRegExp(DomUtil::readEntry(*m_dom,"/filters/" + *it + "/begin"));
	f->setMainRegExp(DomUtil::readEntry(*m_dom,"/filters/" + *it + "/main"));
	f->setEndRegExp(DomUtil::readEntry(*m_dom,"/filters/" + *it + "/end"));
	f->setResultPattern(DomUtil::readEntry(*m_dom,"/filters/" + *it + "/result"));
    f->setBeginPattern(DomUtil::readEntry(*m_dom,"/filters/" + *it + "/beginresult"));
    f->setEndPattern(DomUtil::readEntry(*m_dom,"/filters/" + *it + "/endresult"));
	f->setPolicy((Filter::Policy)DomUtil::readIntEntry(*m_dom,"/filters/" + *it + "/policy",Filter::Transient));
	f->setEnabled(DomUtil::readBoolEntry(*m_dom,"/filters/" + *it + "/active",true));

	QString dep = DomUtil::readEntry(*m_dom,"/filters/" + *it + "/depend",QString::null);
	if(!dep.isNull()) {
	    for(std::vector<InputFilter*>::iterator iter = input.begin(); iter != input.end(); ++iter)
		if((*iter)->getName() == dep) {
		    f->setInputDependency(*iter);
		    break;
		}
	}
	addBlockFilter(f);
    }

    filters = DomUtil::readListEntry(*m_dom,"/general/filters/global","filter");
    for(QStringList::Iterator it = filters.begin(); it != filters.end(); ++it) {
	GlobalFilter* f = new GlobalFilter(*it,m_context);
	f->setResultPattern(DomUtil::readEntry(*m_dom,"/filters/" + *it + "/result"));
	f->setPolicy((Filter::Policy)DomUtil::readIntEntry(*m_dom,"/filters/" + *it + "/policy",Filter::Transient));
	f->setEnabled(DomUtil::readBoolEntry(*m_dom,"/filters/" + *it + "/active",true));

	addGlobalFilter(f);
    }
}


MtpFilter::~MtpFilter() {

    if(!obsolete) {
	QDomElement child = DomUtil::elementByPath(*m_dom,"/filters");
	if(!child.isNull()) child.parentNode().removeChild(child);
    }

    QStringList filters;

    for (std::vector<GlobalFilter*>::iterator it = global.begin(); it != global.end(); ++it) {
	if(!obsolete) {
	    QString name((*it)->getName());
	    DomUtil::writeBoolEntry(*m_dom,"/filters/" + name + "/active",(*it)->isEnabled());
	    DomUtil::writeIntEntry(*m_dom,"/filters/" + name + "/policy",(*it)->policy());
	    DomUtil::writeEntry(*m_dom,"/filters/" + name + "/result",(*it)->getResultPattern());
	    filters << name;
	}
        delete *it;
    }
    if(!obsolete) {
	DomUtil::writeListEntry(*m_dom,"/general/filters/global","filter",filters);
	filters.clear();
    }

    for (std::vector<BlockFilter*>::iterator it = block.begin(); it != block.end(); ++it) {
	if(!obsolete) {
	    QString name((*it)->getName());
	    DomUtil::writeBoolEntry(*m_dom,"/filters/" + name + "/active",(*it)->isEnabled());
	    DomUtil::writeIntEntry(*m_dom,"/filters/" + name + "/policy",(*it)->policy());
	    DomUtil::writeEntry(*m_dom,"/filters/" + name + "/result",(*it)->getResultPattern());
        DomUtil::writeEntry(*m_dom,"/filters/" + name + "/beginresult",(*it)->getBeginPattern());
        DomUtil::writeEntry(*m_dom,"/filters/" + name + "/endresult",(*it)->getEndPattern());
	    DomUtil::writeEntry(*m_dom,"/filters/" + name + "/begin",(*it)->getBeginRegExp());
	    DomUtil::writeEntry(*m_dom,"/filters/" + name + "/main",(*it)->getMainRegExp());
	    DomUtil::writeEntry(*m_dom,"/filters/" + name + "/end",(*it)->getEndRegExp());
	    if((*it)->getInputDependency())
		DomUtil::writeEntry(*m_dom,"/filters/" + name + "/depend",(*it)->getInputDependency()->getName());
	    filters << name;
	}
        delete *it;
    }
    if(!obsolete) {
	DomUtil::writeListEntry(*m_dom,"/general/filters/block","filter",filters);
	filters.clear();
    }

    for (std::vector<LineFilter*>::iterator it = line.begin(); it != line.end(); ++it) {
	if(!obsolete) {
	    QString name((*it)->getName());
	    DomUtil::writeBoolEntry(*m_dom,"/filters/" + name + "/active",(*it)->isEnabled());
	    DomUtil::writeIntEntry(*m_dom,"/filters/" + name + "/policy",(*it)->policy());
	    DomUtil::writeEntry(*m_dom,"/filters/" + name + "/result",(*it)->getResultPattern());
	    DomUtil::writeEntry(*m_dom,"/filters/" + name + "/regexp",(*it)->getRegExp());
	    filters << name;
	}
        delete *it;
    }
    if(!obsolete) {
	DomUtil::writeListEntry(*m_dom,"/general/filters/line","filter",filters);
	filters.clear();
    }

    for (std::vector<ItemFilter*>::iterator it = item.begin(); it != item.end(); ++it) {
	if(!obsolete) {
	    QString name((*it)->getName());
	    DomUtil::writeBoolEntry(*m_dom,"/filters/" + name + "/active",(*it)->isEnabled());
	    DomUtil::writeIntEntry(*m_dom,"/filters/" + name + "/policy",(*it)->policy());
	    DomUtil::writeEntry(*m_dom,"/filters/" + name + "/result",(*it)->getResultPattern());
	    DomUtil::writeEntry(*m_dom,"/filters/" + name + "/regexp",(*it)->getRegExp());
	    filters << name;
	}
        delete *it;
    }
    if(!obsolete) {
	DomUtil::writeListEntry(*m_dom,"/general/filters/item","filter",filters);
	filters.clear();
    }

    for (std::vector<InputFilter*>::iterator it = input.begin(); it != input.end(); ++it) {
	if(!obsolete) {
	    QString name((*it)->getName());
	    DomUtil::writeBoolEntry(*m_dom,"/filters/" + name + "/active",(*it)->isEnabled());
	    DomUtil::writeIntEntry(*m_dom,"/filters/" + name + "/policy",(*it)->policy());
	    DomUtil::writeEntry(*m_dom,"/filters/" + name + "/result",(*it)->getResultPattern());
	    DomUtil::writeEntry(*m_dom,"/filters/" + name + "/regexp",(*it)->getRegExp());
	    DomUtil::writeBoolEntry(*m_dom,"/filters/" + name + "/memorize",(*it)->memorize());
	    filters << name;
	}
        delete *it;
    }
    if(!obsolete) {
	DomUtil::writeListEntry(*m_dom,"/general/filters/input","filter",filters);
	filters.clear();
    }
}

QString MtpFilter::filterIn(const QString & arg) {
    QString res(arg);

    for (std::vector<InputFilter*>::iterator it = input.begin(); it != input.end(); ++it) {
        if ((*it)->isEnabled()) {
            if ((*it)->applyTo(res)) {
                res = (*it)->getResult();
                if ((*it)->memorize())
                    queue.push_back(*it);
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
                        if (in)
                            queue.erase(queue.begin());
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
