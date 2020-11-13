
/* Includes */
#pragma once
#include "framework.h"
#include <wx/stattext.h>
#include <wx/panel.h>
#include<windows.h>
#include<stdio.h>
#include"portCommuniction.h"
#include <wx/txtstrm.h>
#include <wx/wfstream.h>

// If Precompilation is Supported Include "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif


class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
    wxTextCtrl* MainEditBox;

private:
    void OnHello(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnViewSA(wxCommandEvent& event);
    void OnViewSO(wxCommandEvent& event);

    void TimerCall(wxTimerEvent& event);

    Port xBee;
    wxPanel* p_SystemAnalysisPanel;

    wxDECLARE_EVENT_TABLE();
};