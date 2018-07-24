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

#include "dictool.h"

DicTool::DicTool(int &argc, char **argv) : QApplication(argc, argv)
{
    ti = nullptr;
}

DicTool::~DicTool()
{
    delete ti;
}

void DicTool::create_instance()
{
    if (ti == nullptr) {
        ti = new TrayIcon;
    }
}
