////////////////////////////////////////
//  File      : antico.h              //
//  Written by: g_cigala@virgilio.it  //
//  Copyright : GPL                   //
////////////////////////////////////////

// X event handler
// create new frame
// set window manager init settings to "antico.cfg"
// quit window manager

////////////////////////////////////////

#ifndef ANTICO_H
#define ANTICO_H

#include "defs.h"
#include "frame.h"
#include "dockbar.h"
#include "desk.h"

class Dockbar;
class Frame;
class Desk;

////////////////////////////////////////

class Antico : public QApplication
{
    Q_OBJECT

protected:
    virtual bool x11EventFilter(XEvent *);

public:
    Antico(int &argc, char **argv);
    ~Antico();
    void create_frame(Window, Dockbar *);
    void raise_next_frame();
    void set_active_frame(Frame *);
    void send_configurenotify(Frame *);
    void wm_quit();
    void shutdown();
    void restart();
    void wm_refresh();
    void show_desktop();
    void set_settings();
    void run_app_at_startup();
    void get_atoms();
    void create_gui();
    void set_event_names();
    void send_supported_hints();
    void check_window_type(Window);
    void print_window_prop(Window);
    bool check_net_sys_tray_for(Window);
    void check_wm_transient_for(Window);
   
private:
    QHash<int, QString> event_names; // event names
    QHash<int, Frame *> mapping_clients; // mapping client and frame (key=client_win_id value=frame)
    QHash<int, Frame *> mapping_frames; // mapping frame with their winId (key=frame_win_id value=frame)
    int next_frame;
    Dockbar *dock;
    Desk *dsk;
    QStringList frame_type;
    // get WM protocols required by ICCCM
    Atom wm_protocols;
    Atom wm_delete_window;
    Atom wm_change_state;
    Atom wm_state;
    Atom wm_take_focus;
    Atom wm_resource_manager;
    Atom wm_colormaps;
    Atom wm_hints;
    Atom wm_normal_hints;
    Atom wm_name;
    Atom wm_transient_for;
    // Extensions
    Atom _net_wm_name;
    Atom _net_wm_icon;
    Atom _net_supported;
    Atom _net_wm_user_time;
    Atom _net_wm_window_type;
    Atom _net_wm_window_type_normal;
    Atom _net_wm_window_type_desktop;
    Atom _net_wm_window_type_dialog;
    Atom _net_wm_window_type_splash;
    Atom _kde_net_wm_system_tray_window_for;
};
#endif