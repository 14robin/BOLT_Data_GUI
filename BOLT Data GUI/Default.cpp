
/* Include */
#include "Default.h"

enum {
    ID_Button_SA = 1,
    ID_Button_SO = 2
};


wxBEGIN_EVENT_TABLE(DefaultPanel, wxPanel)
EVT_BUTTON(ID_Button_SA, DefaultPanel::OnViewSA)
EVT_BUTTON(ID_Button_SO, DefaultPanel::OnViewSO)
wxEND_EVENT_TABLE()




/* Top Panel Class */
class TopPanel : public wxPanel
{
public:
    /* Default Constructor */
    TopPanel(wxPanel* parent);


};

/* Bottom Panel Class */
class BottomPanel : public wxPanel
{
public:
    /* Default Constructor */
    BottomPanel(wxPanel* parent);
};


/* Default Constructor */
TopPanel::TopPanel(wxPanel* parent) : wxPanel(parent, -1, wxPoint(-1, -1), wxSize(40, 10), wxBORDER_DEFAULT)
{
    /* Basic Setup */
    SetBackgroundColour(wxColour(*wxLIGHT_GREY));

    wxSize minSize(500, 200);
    SetMinSize(minSize);

    /* Add Event Button */
    wxButton* HelloWorld = new wxButton(this, ID_Button_SA, _T("System Analysis"), wxDefaultPosition, wxDefaultSize, 0);

}


/* Default Constructor */
BottomPanel::BottomPanel(wxPanel* parent) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(40, 10), wxBORDER_DEFAULT)
{
    /* Basic Setup */
    SetBackgroundColour(wxColour(*wxLIGHT_GREY));

    wxSize minSize(500, 200);
    SetMinSize(minSize);

    /* Copy Top Panel but Change Items */
        /* Add Event Button */
    wxButton* HelloWorld = new wxButton(this, ID_Button_SO, _T("System Overview"), wxDefaultPosition, wxDefaultSize, 0);

}

/* Data Structure for Initial Frame */
DefaultPanel::DefaultPanel(wxWindow* parent)
    : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize)
{

    wxBoxSizer* p_Box = new wxBoxSizer(wxVERTICAL);
    TopPanel* p_Tpanel = new TopPanel(this);
    BottomPanel* p_Bpanel = new BottomPanel(this);
    p_Box->Add(p_Tpanel, 1, wxEXPAND | wxALL, 5);
    p_Box->Add(p_Bpanel, 1, wxEXPAND | wxALL, 5);
    this->SetSizer(p_Box);

}

/* EVENT HANDLER - SYSTEM ANALYSIS */
void DefaultPanel::OnViewSA(wxCommandEvent& event)
{
    //p_defaultPanel->Show(false);
    //p_SystemAnalysisPanel->Show(true);
    wxLogMessage("Change to System Analysis");
}

/* EVENT HANDLER - SYSTEM OVERVIEW */
void DefaultPanel::OnViewSO(wxCommandEvent& event)
{
    //p_defaultPanel->Show(true);
    //p_SystemAnalysisPanel->Show(false);


    wxLogMessage("Default Gone");
}