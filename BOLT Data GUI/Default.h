
/* Includes */
#pragma once
#include "framework.h"
#include <wx/stattext.h>
#include <wx/panel.h>

// If Precompilation is Supported Include "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

class DefaultPanel : public wxPanel
{
public:

    /* Panel Constructor */
    DefaultPanel(wxWindow* parent);



private:

    /* Events of Panel */
    void OnViewSA(wxCommandEvent& event);
    void OnViewSO(wxCommandEvent& event);

    wxDECLARE_EVENT_TABLE();
};