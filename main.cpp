/*
 * This file is part of the QRsGen distribution.
 * Copyright (c) 2019 Igor Marinescu (igor.marinescu@gmail.com).
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
//******************************************************************************
//
// QRsGen - Application
//
//******************************************************************************
#include "mainwindow.h"
#include <QApplication>

//******************************************************************************
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w(argc, argv);
    w.show();

    return a.exec();
}

//******************************************************************************
