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

//******************************************************************************
// Includes
//******************************************************************************
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>

#include "argparser.h"

//******************************************************************************
// Constructor
//******************************************************************************
MainWindow::MainWindow(int argc, char *argv[], QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    (void) argc;
    (void) argv;

    ui->setupUi(this);
    setWindowTitle(windowTitle() + " V1.0 (invoke with -h for help)");

    // Default arguments
    qrEcLevel = QR_ECLEVEL_L;
    qrEncodingMode = QR_MODE_8;
    qrCaseSensitive = 1;
    showHelpFlag = false;

    // Check command line arguments
    if(parseArgs(argc, argv)){
        if(showHelpFlag)
            showHelp();
    }
    buildHeaderStr();

    // Set colors
    clBack = QColor(Qt::white);
    clFore = QColor(Qt::black);

    // Show Edit Box if no Text as argument and no Error and no Help
    showEditFlag = (qrText.isEmpty() && strOutList.isEmpty());
    if(showEditFlag){
        // Set focus on Edit box
        ui->edtDataText->setFocus();
        ui->edtDataText->selectAll();
        qrText = ui->edtDataText->text();
    }
    else{
        // Hide Edit Box
        ui->edtDataText->setVisible(false);
    }

    // Generate QR Code
    qrcode = nullptr;
    generateQR(qrText);
}

//******************************************************************************
// Destructor
//******************************************************************************
MainWindow::~MainWindow()
{
    // Destroy code
    if(qrcode != nullptr)
        QRcode_free(qrcode);

    delete ui;
}

//******************************************************************************
void MainWindow::generateQR(const QString str)
{
    // Destroy old code
    if(qrcode != nullptr){
        QRcode_free(qrcode);
        qrcode = nullptr;
    }

    //QString str2 = QString("\"") + str + QString("\"");

    // Generate new code
    QByteArray ba = str.toLocal8Bit();
    const char *c_str2 = ba.data();
    qrcode = QRcode_encodeString(c_str2, 0, qrEcLevel, qrEncodingMode, qrCaseSensitive);

    // Check if QR Code generated
    qrErrorText.clear();
    if((qrcode == nullptr) || (qrcode->width <= 0))
        qrErrorText = QString("Cannot generate QR for \"%1\" using these settings").arg(qrText);

    // Repaint the whole window
    repaint();
}

//******************************************************************************
void MainWindow::keyPressEvent(QKeyEvent* e){

    switch(e->key()){
    // If ESC pressed, close the window
    case Qt::Key_Escape:
        this->close();
        break;
    }
}

//******************************************************************************
void MainWindow::paintEvent(QPaintEvent *){

    int textY = FONT_SIZE;

    QPainter painter(this);
    painter.setBrush(clBack);
    painter.setPen(Qt::NoPen);

    // Draw background, 50px at bottom side are reserved for Edit element
    int w = size().width();
    int h = size().height() - (showEditFlag ? 50 : 0);
    painter.drawRect(0, 0, w, h);

    QFont font = painter.font();
    font.setPixelSize(FONT_SIZE);
    painter.setFont(font);
    painter.setPen(QPen());

    // Output (Error/Help) to be displayed?
    if(!strOutList.isEmpty()){
        foreach(const QString &str, strOutList){
            painter.drawText(FONT_SIZE, textY, str);
            textY += FONT_SIZE;
        }
        return;
    }

    // Display Header
    painter.drawText(FONT_SIZE, textY, strHeader);
    textY += FONT_SIZE;

    // Display Footer (QR Text, center aligned)
    QFontMetrics fm(font);
    painter.drawText((w>>1) - (fm.width(qrText)>>1), h - FONT_SIZE, qrText);

    // Check if QR valid (no error while generating code)
    if(!qrErrorText.isEmpty()){
        painter.drawText(FONT_SIZE, textY, qrErrorText);
        return;
    }

    painter.setBrush(clFore);
    painter.setPen(Qt::NoPen);

    int qrBitsCnt = qrcode->width;
    unsigned char * qrData = qrcode->data;

    // Calculate size of one block (in pixels) of QR code:
    //      blockSize = (len - 100) / blocksCnt
    // len - is the minimum value between Width and Height
    // An empty space between QR code and window edge is reserved
    //  50px left + 50px right = 100px
    int qrBlockSize = 0;
    int len = (w < h) ? w : h;
    if(len > 100)
        qrBlockSize = (len - 100) / qrBitsCnt;
    if(qrBlockSize == 0)
        qrBlockSize = 1;

    // Calculate the start coordinates (top/left corner) of QR-code
    // based on the center of window
    int start_x = (w>>1) - ((qrBitsCnt * qrBlockSize)>>1);
    int start_y = (h>>1) - ((qrBitsCnt * qrBlockSize)>>1);

    for(int y = 0; y < qrBitsCnt; y++){
        for(int x = 0; x < qrBitsCnt; x++){
            if(*qrData & 1)
                painter.drawRect(start_x + (x * qrBlockSize), start_y + (y * qrBlockSize), qrBlockSize, qrBlockSize);
            qrData++;
        }
    }
}

//******************************************************************************
void MainWindow::on_edtDataText_textEdited(const QString &arg1)
{
    generateQR(qrText = arg1);
}

//******************************************************************************
void MainWindow::buildHeaderStr(){

    strHeader = "Error Correction Level: ";
    switch(qrEcLevel){
    case QR_ECLEVEL_L: strHeader += "L"; break;
    case QR_ECLEVEL_M: strHeader += "M"; break;
    case QR_ECLEVEL_Q: strHeader += "Q"; break;
    case QR_ECLEVEL_H: strHeader += "H"; break;
    default: strHeader += "?";
    }

    strHeader += " | Encoding Mode: ";
    switch(qrEncodingMode){
    case QR_MODE_NUM:   strHeader += "NUM"; break;
    case QR_MODE_AN:    strHeader += "ANUM"; break;
    case QR_MODE_8:     strHeader += "BYTE"; break;
    case QR_MODE_KANJI: strHeader += "KAN"; break;
    default: strHeader += "?";
    }

    strHeader += " | Case Sensitive: ";
    if(qrCaseSensitive)
        strHeader += " ON";
    else
        strHeader += " OFF";
}

//******************************************************************************
bool MainWindow::parseArgs(int argc, char *argv[]){

    int temp;
    bool status = true;

    ArgParser argParser(argc, argv);
    // Skip first argument (program path)
    argParser.getNext();

    while(status){
        QString str = argParser.getNext();
        if(str.isNull())
            break;

        QString arg = str.toLower();

        // Qr Error Correction Level
        // typedef enum {
        //  QR_ECLEVEL_L = 0, ///< lowest
        //  QR_ECLEVEL_M,
        //  QR_ECLEVEL_Q,
        //  QR_ECLEVEL_H      ///< highest
        // } QRecLevel;
        if((arg == "--error") || (arg == "-e")){
            status = argParser.getNextInt((int) QR_ECLEVEL_L, (int) QR_ECLEVEL_H, &temp);
            if(status)
                qrEcLevel = (QRecLevel) temp;
        }
        // Qr Encoding Mode
        // typedef enum {
        //    QR_MODE_NUL = -1,   ///< Terminator (NUL character). Internal use only
        //    QR_MODE_NUM = 0,    ///< Numeric mode
        //    QR_MODE_AN,         ///< Alphabet-numeric mode
        //    QR_MODE_8,          ///< 8-bit data mode
        //    QR_MODE_KANJI,      ///< Kanji (shift-jis) mode
        //    QR_MODE_STRUCTURE,  ///< Internal use only
        //    QR_MODE_ECI,        ///< ECI mode
        //    QR_MODE_FNC1FIRST,  ///< FNC1, first position
        //    QR_MODE_FNC1SECOND, ///< FNC1, second position
        // } QRencodeMode;
        else if((arg == "--encoding" || (arg == "-c"))){
            status = argParser.getNextInt((int) QR_MODE_NUM, (int) QR_MODE_KANJI, &temp);
            if(status)
                qrEncodingMode = (QRencodeMode) temp;
        }
        // Qr Case Sensitive
        else if((arg == "--sensitive" || (arg == "-s"))){
            status = argParser.getNextInt(0, 1, &temp);
            if(status)
                qrCaseSensitive = temp;
        }
        // Show Help
        else if((arg == "--help" || (arg == "-h"))){
            showHelpFlag = true;
        }
        // Unknown argument
        else{
            // If this was the last argument - this is the text to be displayed
            if(argParser.isEnd())
                qrText = str;
            else{
                strOutList << "Unknwon argument '" + str + "'";
                return false;
            }
        }

        // Incorrect parameter format
        if(!status){
            strOutList << "Incorrect argument format for '" + str + "'";
        }
    }
    return status;
}

//******************************************************************************
void MainWindow::showHelp(){
    strOutList << "QR Code Simple Generator (based on fukuchi/libqrencode)";
    strOutList << "";
    strOutList << "QRsGen.exe [-e <level>] [-c <mode>] [-s <on>] [-h] [text]";
    strOutList << "";
    strOutList << "Arguments:";
    strOutList << "";
    strOutList << "     -e <level> | --error <level>";
    strOutList << "";
    strOutList << "         Error Correction Level. Valid values for <level>: 0 .. 3";
    strOutList << "             0   Lowest";
    strOutList << "             3   Highest";
    strOutList << "";
    strOutList << "     -c <mode> | --encoding <mode>";
    strOutList << "";
    strOutList << "         Encoding Mode. Valid values for <mode>: 0 .. 3";
    strOutList << "             0   Numeric mode";
    strOutList << "             1   Alphabet-numeric mode";
    strOutList << "             2   8-bit data mode";
    strOutList << "             3   Kanji (shift-jis) mode";
    strOutList << "";
    strOutList << "     -s <on> | --sensitive <on>";
    strOutList << "";
    strOutList << "         Case Sensitive On/Off. Valid values:";
    strOutList << "             0   Case non-sensitive";
    strOutList << "             1   Case sensitive";
    strOutList << "";
    strOutList << "     -h | --help Displays this help";
    strOutList << "";
    strOutList << "     text Text to be displayed as QR Code";
    strOutList << "";
    strOutList << "Example:";
    strOutList << "";
    strOutList << "     QRsGen.exe -e 1 -c 2 -s 1 \"Hello World\"";
    strOutList << "";
    strOutList << "     Generates QR-Code from \"Hello World\", Error Correction Level=Medium, ";
    strOutList << "     Encoding Mode=8-bit data, case sensitive.";
}
