/**
  * This file is part of DicTool, a simple dictionary tool for KDE.
  * Copyright 2018  Chant Shao <chantsp52@gmail.com>
  *
  * This library is free software; you can redistribute it and/or
  * modify it under the terms of the GNU Lesser General Public
  * License as published by the Free Software Foundation; either
  * version 2.1 of the License, or (at your option) version 3, or any
  * later version accepted by the membership of KDE e.V. (or its
  * successor approved by the membership of KDE e.V.), which shall
  * act as a proxy defined in Section 6 of version 3 of the license.
  *
  * This library is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  * Lesser General Public License for more details.
  *
  * You should have received a copy of the GNU Lesser General Public
  * License along with this library.  If not, see <http://www.gnu.org/licenses/>.
  */

#ifndef TRAYICON_H
#define TRAYICON_H

#include <QAction>
#include <QApplication>
#include <QByteArray>
#include <QClipboard>
#include <QDesktopServices>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMenu>
#include <QUrl>

#include <QtNetwork>

#include <KAboutApplicationDialog>
#include <KAboutData>
#include <KGlobalAccel>
#include <KLocalizedString>
#include <KMessageBox>
#include <KStatusNotifierItem>

class TrayIcon : public KStatusNotifierItem
{
    Q_OBJECT
public:
    TrayIcon();
    ~TrayIcon();

private:
    const QString url;
    const QString data_option;

    QAction* action_about;
    QAction* action_help;
    QAction* action_search;

    QClipboard* qc;

    QNetworkAccessManager qnam;

    void set_actions();
    void set_trayicon();

private slots:
    void on_about();
    void on_help();
    void on_reply(QNetworkReply *reply);
    void on_search();
};

#endif // TRAYICON_H
