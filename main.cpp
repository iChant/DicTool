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

#include <QApplication>
#include <QCommandLineParser>

#include <KAboutData>
#include <KDBusService>
#include <KLocalizedString>

#include "dictool.h"

int main(int argc, char *argv[])
{
    DicTool app(argc, argv);
    KLocalizedString::setApplicationDomain("dictool");
    KAboutData about_data("dictool", i18n("DicTool"), "0.1.0",
                          i18n("A simple dictionary tool"),
                          KAboutLicense::LGPL_V2_1,
                          i18n("(c) 2018 , Chant Shao"), QString(),
                          "https://github.com/iChant/DicTool");
    about_data.addAuthor(i18n("Chant Shao"), i18n("Author"),
                         "chantsp52@gmail.com",
                         "https://ichant.github.io");
    about_data.setBugAddress(QByteArray("chantsp52@gmail.com"));
    about_data.setOrganizationDomain(QByteArray("kde.org"));
    about_data.setProductName(QByteArray("dictool"));
    KAboutData::setApplicationData(about_data);

    app.setApplicationName(about_data.componentName());
    app.setApplicationDisplayName(about_data.displayName());
    app.setApplicationVersion(about_data.version());
    app.setOrganizationDomain(about_data.organizationDomain());

    KDBusService dbus_service(KDBusService::Unique);

    QCommandLineParser parser;
    parser.addVersionOption();
    parser.addHelpOption();
    about_data.setupCommandLine(&parser);
    parser.process(app);
    about_data.processCommandLine(&parser);

    app.create_instance();
    return app.exec();
}
