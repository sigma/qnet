/*  Time-stamp: <13/02/2005 12:18:02 Yann Hodique>  */

/**
 *  @file interactionarea.h
 *  @date Thursday, December 30, 2004
 *  @author Yann Hodique <Yann.Hodique@lifl.fr>
 */

/************************************************************************
 *                                                                      *
 * This program is free software; you can redistribute it and/or modify *
 * it under the terms of the GNU General Public License as published by *
 * the Free Software Foundation; either version 2 of the License, or    *
 * (at your option) any later version.                                  *
 *                                                                      *
 ************************************************************************/

#ifndef _INTERACTIONAREA_H_
#define _INTERACTIONAREA_H_

#include <QObject>
#include <QList>
#include <QRegExp>

class MtpOutput;
class MtpInput;

/**
 * Interface for describing interaction between a user and a service
 *
 */
class InteractionArea : public QObject {

    Q_OBJECT

public:
    /**
     * Constructor
     *
     * @param parent the parent QObject
     *
     */
    InteractionArea(QObject *parent = 0);

    /**
     * Destructor
     *
     */
    virtual ~InteractionArea();

    static const QString DefaultMatch;
    static const QString DefaultReplace;

/**
 * Add a new positive filter to this InteractionArea. The regular expression
 * are the usual ones, the replacements can contain backward references as \\0,
 * \\1, ... \\9 to refer to captured texts. It \a end is null, the filter is a
 * single line filter, else it is a multi-line filter.
 *
 * \sa addNegativeFilter()
 *
 * @param beg regular expression matching the beginning of the filter
 * @param beg_repl replacement for \a beg
 * @param end regular expression matching the end of the filter
 * @param end_repl replacement for \a end
 * @param middle regular expression matching the middle of the filter
 * @param middle_repl replacement for \a midle
 */
    void addPositiveFilter(const QString& beg, const QString& beg_repl = DefaultReplace,
                           const QString& end = QString::null, const QString& end_repl = DefaultReplace,
                           const QString& middle = DefaultMatch, const QString& middle_repl = DefaultReplace);

/**
 * Add a new negative filter to this InteractionArea. The regular expression
 * are the usual ones, the replacements can contain backward references as \\0,
 * \\1, ... \\9 to refer to captured texts. It \a end is null, the filter is a
 * single line filter, else it is a multi-line filter.
 *
 * \sa addPositiveFilter()
 *
 * @param beg regular expression matching the beginning of the filter
 * @param beg_repl replacement for \a beg
 * @param end regular expression matching the end of the filter
 * @param end_repl replacement for \a end
 * @param middle regular expression matching the middle of the filter
 * @param middle_repl replacement for \a midle
 */
    void addNegativeFilter(const QString& beg, const QString& beg_repl = DefaultReplace,
                           const QString& end = QString::null, const QString& end_repl = DefaultReplace,
                           const QString& middle = DefaultMatch, const QString& middle_repl = DefaultReplace);

/**
 * Sets the default display policy for this InteractionArea. If \a b is true,
 * then any string is displayed unless explicitely mentioned in the negative
 * filters. If \a b is false, the opposite behavior
 * is adopted. This function should not be used after
 * the InteractionArea is un use, or at least, when in the middle of a filter,
 * or strange things might happen.
 *
 * @todo provide a secure way of switching behavior
 * \sa addNegativeFilter()
 * \sa addPositiveFilter()
 *
 * @param b boolean
 */
    void setDisplayByDefault(bool b = true) {default_display = b;}

protected:
    /**
     * the output device
     *
     * @return where to output things
     */
    virtual MtpOutput * getOutput() const = 0;

    /**
     * the input device
     *
     * @return from where to read things
     */
    virtual MtpInput * getInput() const = 0;

public slots:
    /**
     * display a message on the output
     * @lisp display
     * @param msg message to display
     */
    virtual void slotDisplay(const QString& msg);

    virtual void slotSend(const QString& msg);

signals:
    /**
     * signal emitted when a user wants to send a message
     *
     * @param msg the message to send
     *
     */
    void send(const QString& msg);

private:
    QString shouldDisplay(const QString& msg);
    void addFilter(bool type, const QString& beg, const QString& beg_repl,
                   const QString& end, const QString& end_repl,
                   const QString& middle, const QString& middle_repl);

    QString replace(QString, QRegExp, QString);

    typedef struct {
        QPair<QRegExp,QString> begin, end, middle;
    } Replacement;

    QList<Replacement> positive;
    QList<Replacement> positive_blocks;
    QList<Replacement> negative;
    QList<Replacement> negative_blocks;
    QStack<int> m_nested;
    bool default_display;
};	// end of class InteractionArea


#endif /* _INTERACTIONAREA_H_ */
