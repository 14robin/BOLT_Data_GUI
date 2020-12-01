/* BOLT Data GUI.cpp : Main() */

/* Includes */
#pragma once
#include "framework.h"
#include "eHandler.h"
#include <wx/stattext.h>
#include <wx/panel.h>

/* If Precompilation is Supported Include "wx/wx.h" */
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif


/* Create Abstract Application Structure */
class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};


/* Open Application */
wxIMPLEMENT_APP(MyApp);


/* Default Frame - Initial Point and Size */
bool MyApp::OnInit()
{
    MyFrame* frame = new MyFrame("BOLT Data GUI", wxPoint(50, 50), wxSize(650, 550));
    frame->Show(true);


    return true;
}