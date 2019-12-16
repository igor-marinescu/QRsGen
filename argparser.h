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
// ArgParser - Argument Parser
//
// Module provides methods for parsing command-line arguments.
//
//******************************************************************************
#ifndef ARGPARSER_H
#define ARGPARSER_H

//******************************************************************************
// Includes
//******************************************************************************
#include <QStringList>

//******************************************************************************
// Defines
//******************************************************************************

//******************************************************************************
// Class
//******************************************************************************
class ArgParser {

    QStringList argList;
    int idx;

public:

    explicit ArgParser(int argc, char *argv[]);
    virtual ~ArgParser();

    QString getNext();
    bool getNextInt(int min, int max, int * out);
    bool isEnd();
};

//******************************************************************************
#endif // ARGPARSER_H
