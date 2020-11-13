/* Includes */
#pragma once
#include "framework.h"
#include <wx/stattext.h>
#include <wx/panel.h>
#include<windows.h>
#include<stdio.h>

// If Precompilation is Supported Include "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif


/* Port Communication Structure */
class Port
{
public:

    /* Default Constructor */
    Port();

    /* Read */
    void Read();

    /* Close Communication Port */
    void closePort();

    /* Parse Data */
    char parsedData[7];

    /* Actual Data Variables - Public */


private:

    /* Private Variables of class Port */
    char rawDataIn[256];

    HANDLE hComm;
};