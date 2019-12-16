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

//******************************************************************************
// Includes
//******************************************************************************
#include "ArgParser.h"

//******************************************************************************
// Constructor
//******************************************************************************
ArgParser::ArgParser(int argc, char *argv[])
{
    // Copy arguments to a list
    for(int i = 0; i < argc; i++)
        argList << QString(argv[i]);

    // Reset read-index
    idx = 0;
}

//******************************************************************************
// Destructor
//******************************************************************************
ArgParser::~ArgParser()
{

}

//******************************************************************************
// Get next argument.
// Return:
//  Next argument or null string in case if no more arguments (QString::isNull())
//******************************************************************************
QString ArgParser::getNext()
{
    // Check read-index and return next argument
    if(idx < argList.size())
        return argList.at(idx++);

    // No more arguments, return Null String
    return QString();
}

//******************************************************************************
// Get next argument in Integer format.
// Parameters:
//  min, max - Valid ranges for the value (to be considered valid).
//  out - pointer to an Integer where the value is stored.
// Return:
//  true if next argument is considered valid integer (min <= val <= max)
//  false if not (out is not modified in this case)
//******************************************************************************
bool ArgParser::getNextInt(int min, int max, int * out)
{
    bool res = false;
    int temp;

    if(idx < argList.size())
        temp = argList.at(idx).toInt(&res);

    if(res && (temp >= min) && (temp <= max)){
        *out = temp;
        idx++;
        return true;
    }
    return false;
}

//******************************************************************************
// Returns true if no more arguments left.
//******************************************************************************
bool ArgParser::isEnd()
{
    return (idx >= argList.size());
}
