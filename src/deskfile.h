////////////////////////////////////////
//  File      : deskfile.h            //
//  Written by: g_cigala@virgilio.it  //
//  Copyright : GPL                   //
////////////////////////////////////////

// file added on the desk

////////////////////////////////////////

#ifndef DESKFILE_H
#define DESKFILE_H

#include "defs.h"
#include "filedialog.h"
#include "utils.h"

////////////////////////////////////////

class Deskfile : public QLabel
{
    Q_OBJECT

public:
    Deskfile(const QString &dir_name, const QString &dir_path, QString pix, QWidget *parent=0);
    ~Deskfile();
    void read_settings();
    void init();
    void update_style();

protected:
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);
    void contextMenuEvent(QContextMenuEvent *);

signals:

public slots:
    void del_file();

private:
    QMenu *main_menu;
    QMenu *open_menu;
    QString file_name;
    QString file_path;
    QString delete_link_pix;
    QString open_with_pix;
    QPoint mousepos;
    QColor d_file_col;
    QPixmap d_file_pix;
    QSettings *style;
    QSettings *antico;
    Categorymenu * cat_menu;
};

#endif
