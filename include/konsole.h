/* ----------------------------------------------------------------------- */
/*                                                                         */
/* [konsole.h]                      Konsole                                   */
/*                                                                            */
/* -------------------------------------------------------------------------- */
/*                                                                            */
/* Copyright (c) 1997,1998 by Lars Doelle <lars.doelle@on-line.de>            */
/*                                                                            */
/* This file is part of Konsole, an X terminal.                               */
/*                                                                            */
/* The material contained in here more or less directly orginates from        */
/* kvt, which is copyright (c) 1996 by Matthias Ettrich <ettrich@kde.org>     */
/*                                                                            */
/* -------------------------------------------------------------------------- */

#ifndef KONSOLE_H
#define KONSOLE_H


#include <kmainwindow.h>
#include <ksimpleconfig.h>
#include <kaction.h>
#include <kpopupmenu.h>
#include <qstrlist.h>
#include <qintdict.h>
#include <qptrdict.h>

#include "TEPty.h"
#include "TEWidget.h"
#include "TEmuVt102.h"
#include "session.h"
#include "schema.h"

#undef PACKAGE
#undef VERSION
#define PACKAGE "konsole"
#define VERSION "1.0.2"

class KRootPixmap;

class Konsole : public KMainWindow
{
    Q_OBJECT

    friend class KonsoleSessionManaged;
public:

  Konsole(const char * name, const char* pgm, QStrList & _args,
    int histon, bool, QCString mytitle, QCString type = 0, bool b_inRestore = false);
  ~Konsole();
  void setColLin(int columns, int lines);
  void setFullScreen(bool on);
  void initFullScreen();
  void initSessionSchema(int schemaNo);
  void initSessionTitle(QString title);
  void initRenameSession(QString sTitle);

public slots:

  void makeGUI();
  void newSession();
  void newRestoredSession(QString title);

protected:

 bool queryClose();
 void saveProperties(KConfig* config);
 void readProperties(KConfig* config);
 void saveGlobalProperties(KConfig* config);
 void readGlobalProperties(KConfig* config);

 void showFullScreen();

private slots:
  void slotBackgroundChanged(int desk);
  void configureRequest(TEWidget*,int,int,int);
  void activateSession();
  void activateSession(TESession*);
  void doneSession(TESession*,int);
  void opt_menu_activated(int item);
  void schema_menu_activated(int item);
  void pixmap_menu_activated(int item);
  void keytab_menu_activated(int item);
  void schema_menu_check();
  void tecRef();
  //what's this intended for ? aleXXX
  //void newSessionSelect();
  void newSession(int kind);
  void updateSchemaMenu();

  void changeColumns(int);
  void notifySize(int,int);
  void setHeader();
  void changeTitle(int, const QString&);
  void prevSession();
  void nextSession();
  void allowPrevNext();
  void setSchema(int n);
  void sendSignal(int n);
  void slotToggleToolbar();
  void slotToggleMenubar();
  void slotToggleFrame();
  void slotRenameSession();
  void slotWordSeps();
  void slotSelectSize();
  void slotSelectFont();
  void slotSelectScrollbar();
  void slotWarnQuit();
  void loadScreenSessions();

private:
  TESession *newSession(KSimpleConfig *co);
  void readProperties(KConfig *config, const QString &schema);
  void applySettingsToGUI();
  void makeBasicGUI();
  void runSession(TESession* s);
  void addSession(TESession* s);
  void setColorPixmaps();

  void setHistory(bool);

  void setSchema(const QString & path);
  void setSchema(ColorSchema* s);
  void setFont(int fontno);

  void addSessionCommand(const QString & path);
  void loadSessionCommands();
  void addScreenSession(const QString & socket);
  QSize calcSize(int columns, int lines);


  QPtrDict<TESession> action2session;
  QPtrDict<KRadioAction> session2action;
  QList<TESession> sessions;
  QIntDict<KSimpleConfig> no2command;

  TEWidget*      te;
  TESession*     se;
  TESession*     m_initialSession;
  ColorSchemaList* colors;

  KRootPixmap*   rootxpm;

  KMenuBar*   menubar;
  KStatusBar* statusbar;

  KPopupMenu* m_file;
  KPopupMenu* m_sessions;
  KPopupMenu* m_options;
  KPopupMenu* m_schema;
  KPopupMenu* m_keytab;
  KPopupMenu* m_codec;
  KPopupMenu* m_toolbarSessionsCommands;
  KPopupMenu* m_signals;
  KPopupMenu* m_help;

  KToggleAction *showToolbar;
  KToggleAction *showMenubar;
  KToggleAction *showScrollbar;
  KToggleAction *showFrame;
  KSelectAction *selectSize;
  KSelectAction *selectFont;
  KSelectAction *selectScrollbar;

  KToggleAction *warnQuit;                      // Warn when closing this session on quit

  int cmd_serial;
  int cmd_first_screen;
  int session_no;
  int         n_keytab;
  int         n_oldkeytab;
  int         n_font;
  int         n_defaultFont; // font as set in config to use as default for new sessions
  int         n_scroll;
  int         n_render;
  int         curr_schema; // current schema no
  QString     s_schema;
  QString     s_kconfigSchema;
  QString     s_word_seps;			// characters that are considered part of a word
  QString     pmPath; // pixmap path
  QString     dropText;
  QFont       defaultFont;
  QSize       defaultSize;

  const char* pgm;
  QStrList    args;
  QRect       _saveGeometry;

  bool        b_scroll:1;
  bool        b_framevis:1;
  bool        b_fullscreen:1;
  bool        m_menuCreated:1;
  bool        skip_exit_query:1;
  bool        b_warnQuit:1;
  bool        alreadyNoticedBackgroundChange_:1;
  bool        isRestored;
  bool        wasRestored;

public:

  QString     title;
};

#endif
