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

#include "trayicon.h"

#include <QDebug>

TrayIcon::TrayIcon() :
    KStatusNotifierItem("dictool"),
    url("http://fy.iciba.com/ajax.php?a=fy"),
    data_option("&f=auto&t=auto&w=%1"),
    qc(QApplication::clipboard())
{
    set_actions();
    set_trayicon();
    connect(&qnam, &QNetworkAccessManager::finished, this, &TrayIcon::on_reply);

}

TrayIcon::~TrayIcon()
{
    delete action_about;
    action_about = nullptr;
    delete action_search;
    action_search = nullptr;
    delete action_help;
    action_help = nullptr;
    qc = nullptr;
}

void TrayIcon::set_actions()
{
    action_about  = new QAction(i18n("&About..."), this);
    action_help   = new QAction(i18n("&Help"), this);
    action_search = new QAction(i18n("&Search"), this);
    action_about->setObjectName("dictool-about");
    action_help->setObjectName("dictool-help");
    action_search->setObjectName("dictool-search");
    connect(action_about, &QAction::triggered, this, &TrayIcon::on_about);
    connect(action_search, &QAction::triggered, this, &TrayIcon::on_search);
}

void TrayIcon::set_trayicon()
{
    QIcon icon("icon.png");
    setIconByPixmap(icon);
    contextMenu()->addAction(action_about);
    KGlobalAccel::self()->setGlobalShortcut(action_search, QKeySequence("Meta+F11"));
}

void TrayIcon::on_about()
{
    KAboutApplicationDialog dlg(KAboutData::applicationData());
    dlg.exec();
}

void TrayIcon::on_help()
{
    QDesktopServices::openUrl(QUrl("https://github.com/iChant/DicTool/blob/master/README.md"));
}

void TrayIcon::on_reply(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray res(reply->readAll());
        QJsonObject content = QJsonDocument::fromJson(res).object()["content"].toObject();
        QString out = "";
        if (content.contains("word_mean")) {
            qDebug() << "word_mean";
            QJsonArray word_mean = content["word_mean"].toArray();
            for (QJsonValue i : word_mean) {
                out += i.toString() + "\n";
            }
        } else if (content.contains("out")) {
            qDebug() << "out";
            out = content["out"].toString();
        } else {
            out = "Sorry, cannot parse the json from server";
        }
        showMessage("DicTool", out, QString());
    } // else on_ERROR
    else {
        showMessage("DicTool", i18n("Error to connect to the server!"), QString());
    }
}

void TrayIcon::on_search()
{
    qDebug() << "Search triggered";
    QString word = qc->text(QClipboard::Selection);
    if(word != "") {
        qDebug() << word;
        QByteArray data = data_option.arg(word).toUtf8();
        QNetworkRequest req(url);
        req.setHeader(QNetworkRequest::UserAgentHeader,
                      QVariant("Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/67.0.3396.99 Safari/537.36"));
        qnam.post(req, data);
    }
}
