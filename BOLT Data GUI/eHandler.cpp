

#include "eHandler.h"

/* Event ID's */
enum
{
    ID_Hello = 1,
    ID_View_SystemAnalysis = 2,
    ID_View_SystemOverview = 3
};

/* Event Table */
wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
EVT_MENU(ID_Hello, MyFrame::OnHello)
EVT_MENU(wxID_EXIT, MyFrame::OnExit)
EVT_MENU(wxID_ABOUT, MyFrame::OnAbout)
EVT_MENU(ID_View_SystemAnalysis, MyFrame::OnViewSA)
EVT_MENU(ID_View_SystemOverview, MyFrame::OnViewSO)
wxEND_EVENT_TABLE()






/* -------------------------------------------- NEW SHIT -------------------------------------------- */

class LeftPanel : public wxPanel
{
public:
    LeftPanel(wxPanel* parent);

    //void OnPlus(wxCommandEvent& event);
    //void OnMinus(wxCommandEvent& event);

    //wxButton* m_plus;
    //wxButton* m_minus;
    //wxPanel* m_parent;
    //int count;

};

class RightPanel : public wxPanel
{
public:
    RightPanel(wxPanel* parent);

    //void OnSetText(wxCommandEvent& event);

    //wxStaticText* m_text;

};

const int ID_PLUS = 101;
const int ID_MINUS = 102;

LeftPanel::LeftPanel(wxPanel* parent)
    : wxPanel(parent, -1, wxPoint(-1, -1), wxSize(-1, -1), wxBORDER_DEFAULT)
{

    SetBackgroundColour(wxColour(*wxLIGHT_GREY));



    //count = 0;
    //m_parent = parent;
    //m_plus = new wxButton(this, ID_PLUS, wxT("+"),
    //    wxPoint(10, 10));
    //m_minus = new wxButton(this, ID_MINUS, wxT("-"),
    //    wxPoint(10, 60));
    //Connect(ID_PLUS, wxEVT_COMMAND_BUTTON_CLICKED,
    //    wxCommandEventHandler(LeftPanel::OnPlus));
    //Connect(ID_MINUS, wxEVT_COMMAND_BUTTON_CLICKED,
    //    wxCommandEventHandler(LeftPanel::OnMinus));
}

//void LeftPanel::OnPlus(wxCommandEvent& WXUNUSED(event))
//{
//    count++;
//
//    Communicate* comm = (Communicate*)m_parent->GetParent();
//    comm->m_rp->m_text->SetLabel(wxString::Format(wxT("%d"), count));
//}
//
//void LeftPanel::OnMinus(wxCommandEvent& WXUNUSED(event))
//{
//    count--;
//
//    Communicate* comm = (Communicate*)m_parent->GetParent();
//    comm->m_rp->m_text->SetLabel(wxString::Format(wxT("%d"), count));
//}


RightPanel::RightPanel(wxPanel* parent)
    : wxPanel(parent, wxID_ANY, wxDefaultPosition,
        wxSize(270, 150), wxBORDER_DEFAULT)
{
    SetBackgroundColour(wxColour(*wxLIGHT_GREY));


    //m_text = new wxStaticText(this, -1, wxT("0"), wxPoint(40, 60));
}



class Communicate : public wxFrame
{
public:
    Communicate(const wxString& title);


    LeftPanel* m_lp;
    RightPanel* m_rp;
    wxPanel* m_parent;
};

Communicate::Communicate(const wxString& title)
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(290, 150))
{
    m_parent = new wxPanel(this, wxID_ANY);

    wxBoxSizer* hbox = new wxBoxSizer(wxVERTICAL);

    m_lp = new LeftPanel(m_parent);
    m_rp = new RightPanel(m_parent);

    hbox->Add(m_lp, 1, wxEXPAND | wxALL, 5);
    hbox->Add(m_rp, 1, wxEXPAND | wxALL, 5);

    m_parent->SetSizer(hbox);

    this->Centre();
}













/* Data Structure for Initial Frame */
MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame(NULL, wxID_ANY, title, pos, size)
{
    /* NEW MENU */
    wxMenuBar* menuBar = new wxMenuBar;

    /* NEW MENU ITEM - FILE */
    wxMenu* menuFile = new wxMenu;
    menuFile->Append(ID_Hello, "&Hello...\tCtrl-H",
        "Help string shown in status bar for this menu item");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);
    menuBar->Append(menuFile, "&File");

    /* NEW MENU ITEM - ABOUT */
    wxMenu* menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);
    menuBar->Append(menuHelp, "&Help");

    /* NEW MENU ITEM - VIEW */
    wxMenu* menuView = new wxMenu;
    menuView->Append(ID_View_SystemAnalysis, "&System Analysis", "View System Analysis");
    menuView->Append(ID_View_SystemOverview, "&System Overview", "View System Overview");
    menuBar->Append(menuView, "&View");

    SetMenuBar(menuBar);

    /* Status Bar at Bottom of Page */
    CreateStatusBar();
    SetStatusText("Welcome to wxWidgets!");

    /* ADD PANELS */
    Communicate* communicate = new Communicate(wxT("Widgets communicate"));
    communicate->Show(true);

}





/* EVENT HANDLER - ABOUT */
void MyFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox("This is a wxWidgets' Hello world sample",
        "About Hello World", wxOK | wxICON_INFORMATION);
}

/* EVENT HANDLER - EXIT */
void MyFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}

/* EVENT HANDLER - HELLO */
void MyFrame::OnHello(wxCommandEvent& event)
{
    wxLogMessage("Hello world from wxWidgets!");
}

/* EVENT HANDLER - SYSTEM ANALYSIS */
void MyFrame::OnViewSA(wxCommandEvent& event)
{
    wxLogMessage("Change to System Analysis");
}

/* EVENT HANDLER - SYSTEM OVERVIEW */
void MyFrame::OnViewSO(wxCommandEvent& event)
{
    wxLogMessage("Change to System Overview");
}