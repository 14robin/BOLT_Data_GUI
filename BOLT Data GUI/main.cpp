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
wxIMPLEMENT_APP(MyApp);                         // Function which Executes the Application Operation


/* Default Frame - Initial Point and Size */
bool MyApp::OnInit()
{
    MyFrame* frame = new MyFrame("BOLT Data GUI", wxPoint(50, 50), wxSize(650, 550));
    frame->Show(true);



    return true;
}



///* Default Frame - Initial Point and Size */
//bool MyApp::OnInit()
//{
//    Communicate* communicate = new Communicate(wxT("Widgets communicate"));
//    communicate->Show(true);
//
//
//
//    //MyFrame* frame = new MyFrame("BOLT Data GUI", wxPoint(50, 50), wxSize(650, 550));
//    //frame->Show(true);
//    //return true;
//}

///* Data Structure for Initial Frame */
//MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
//    : wxFrame(NULL, wxID_ANY, title, pos, size) 
//{
//    /* NEW MENU */
//    wxMenuBar* menuBar = new wxMenuBar;
//
//    /* NEW MENU ITEM - FILE */
//    wxMenu* menuFile = new wxMenu;
//    menuFile->Append(ID_Hello, "&Hello...\tCtrl-H",
//        "Help string shown in status bar for this menu item");
//    menuFile->AppendSeparator();
//    menuFile->Append(wxID_EXIT);
//    menuBar->Append(menuFile, "&File");
//
//    /* NEW MENU ITEM - ABOUT */
//    wxMenu* menuHelp = new wxMenu;
//    menuHelp->Append(wxID_ABOUT);
//    menuBar->Append(menuHelp, "&Help");
//
//    /* NEW MENU ITEM - VIEW */
//    wxMenu* menuView = new wxMenu;
//    menuView->Append(ID_View_SystemAnalysis, "&System Analysis", "View System Analysis");
//    menuView->Append(ID_View_SystemOverview, "&System Overview", "View System Overview");
//    menuBar->Append(menuView, "&View");
//
//    SetMenuBar(menuBar);
//
//    /* Status Bar at Bottom of Page */
//    CreateStatusBar();
//    SetStatusText("Welcome to wxWidgets!");
//
//    /* ADD PANELS */
//    Communicate* communicate = new Communicate(wxT("Widgets communicate"));
//    communicate->Show(true);
//
//}



