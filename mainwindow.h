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
// QRsGen - Main Window
//
//******************************************************************************
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//******************************************************************************
// Includes
//******************************************************************************
#include <QMainWindow>
#include <QKeyEvent>
#include "lib/qrencode.h"

//******************************************************************************
// Defines
//******************************************************************************

#define FONT_SIZE   11

//******************************************************************************
namespace Ui {
class MainWindow;
}

//******************************************************************************
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(int argc, char *argv[], QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_edtDataText_textEdited(const QString &arg1);

private:
    Ui::MainWindow *ui;

    // Qr Code
    QRcode *qrcode;
    QRecLevel qrEcLevel;
    QRencodeMode qrEncodingMode;
    int qrCaseSensitive;
    QString qrText;
    QString qrErrorText;

    QString strHeader;
    QStringList strOutList;
    bool showHelpFlag;
    bool showEditFlag;

    // Colors used to draw QR code (background/foreground)
    QColor clBack;
    QColor clFore;

    void generateQR(const QString str);
    void buildHeaderStr();

    bool parseArgs(int argc, char *argv[]);
    void showHelp();

protected:
    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent* e);
};

//******************************************************************************
#endif // MAINWINDOW_H
