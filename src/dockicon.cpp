////////////////////////////////////////
//  File      : dockicon.cpp          //
//  Written by: g_cigala@virgilio.it  //
//  Copyright : GPL                   //
////////////////////////////////////////

#include "dockicon.h"

////////////////////////////////////////

Dockicon::Dockicon(Frame *frame, Systray *sys_tr, QWidget *parent) : QWidget(parent)
{
    frm = frame;
    title = frm->cl_name();
    sys = sys_tr;
    read_settings();
    iconize = true;
    bdr_width = 1;
}

Dockicon::~Dockicon()
{}

void Dockicon::read_settings()
{
    // get style path
    QSettings *antico = new QSettings(QCoreApplication::applicationDirPath() + "/antico.cfg", QSettings::IniFormat, this);
    antico->beginGroup("Style");
    QString stl_name = antico->value("name").toString();
    QString stl_path = antico->value("path").toString();
    antico->endGroup(); //Style
    // get style values
    style = new QSettings(stl_path + stl_name, QSettings::IniFormat, this);
    style->beginGroup("Dockicon");
    d_icon_pix = stl_path + style->value("d_icon_pix").toString();
    title_color = style->value("title_color").value<QColor>();
    style->endGroup(); //Dockicon
    style->beginGroup("Other");
    close_dock_pix = stl_path + style->value("close_dock_pix").toString();
    add_to_sys_pix = stl_path + style->value("add_to_sys_pix").toString();
    style->endGroup(); //Other
    pix = QPixmap(d_icon_pix);
}

void Dockicon::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QPen(title_color, bdr_width, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter.drawRoundedRect(0, 0, width(), height(), 5, 5);
    painter.drawText(QRect(height()+3, 0, width(), height()), Qt::AlignVCenter, title); // dock title
    painter.drawPixmap(QRect(0, 0, width(), height()), pix, QRect(0, 0, pix.width(), pix.height()));// dock pixmap
    painter.drawPixmap(QRect(3, 3, height()-6, height()-6), frm->cl_icon(), QRect(0, 0, frm->cl_icon().width(), frm->cl_icon().height()));// dock icon
}

void Dockicon::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        if(iconize)
        {
            frm->raise();
            iconize = false;
        }
        else
        {
            frm->iconify();
            iconize = true;
        }
    }
    if (event->button() == Qt::RightButton)
    {
        QMenu *menu = new QMenu(this);
        menu->addAction(QIcon(close_dock_pix), tr("Close"));
        menu->addAction(QIcon(add_to_sys_pix), tr("Add to System Tray"));
        menu->popup(event->globalPos());
        connect(menu, SIGNAL(triggered(QAction *)), this, SLOT(run_menu(QAction *)));
    }
}

void Dockicon::enterEvent(QEvent *event)
{
    Q_UNUSED(event);
    bdr_width = 2;
    update();
}

void Dockicon::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);
    bdr_width = 1;
    update();
}

void Dockicon::run_menu(QAction *act)
{
    if (act->text() == tr("Close"))
    {
        emit destroy_dock(this);
        frm->destroy();
        close();
    }
    if (act->text() == tr("Add to System Tray"))
    {
        emit destroy_dock(this);
        sys->add(frm); // add Dockicon to System Tray
        qDebug() << "Dockicon add to System Tray";
        frm->unmap();
        close();
    }
}

void Dockicon::update_name(const QString &name)
{
    title = name;
    update();
}

void Dockicon::update_style()
{
    read_settings();
    update();
}