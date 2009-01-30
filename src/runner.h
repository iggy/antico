////////////////////////////////////////
//  File      : runner.h              //
//  Written by: g_cigala@virgilio.it  //
//  Copyright : GPL                   //
////////////////////////////////////////

// start an application from command line

////////////////////////////////////////

#ifndef RUNNER_H
#define RUNNER_H

#include "defs.h"
#include "msgbox.h"

////////////////////////////////////////

class Runner : public QDialog
{
    Q_OBJECT

public:
    Runner(QWidget *parent=0);
    ~Runner();
    void init();

protected:
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);

signals:

public slots:
    void run();
    void quit();

private:
    QPoint mousepos;
    QLineEdit *command;
};


#endif