/* Event Handler of Desktop Application */

/* Include */
#include "eHandler.h"

/* Event ID's */
enum
{
    ID_Hello = 1,
    ID_View_SystemAnalysis = 2,
    ID_View_SystemOverview = 3,
    ID_Button_SA = 4,
    ID_Button_SO = 5
};

/* Event Table */
wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
EVT_MENU(ID_Hello, MyFrame::OnHello)
EVT_MENU(wxID_EXIT, MyFrame::OnExit)
EVT_MENU(wxID_ABOUT, MyFrame::OnAbout)
EVT_MENU(ID_View_SystemAnalysis, MyFrame::OnViewSA)
EVT_MENU(ID_View_SystemOverview, MyFrame::OnViewSO)

EVT_BUTTON(ID_Button_SA, MyFrame::OnViewSA)
EVT_BUTTON(ID_Button_SO, MyFrame::OnViewSO)

wxEND_EVENT_TABLE()






/* -------------------------------------------- NEW SHIT -------------------------------------------- */


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
TopPanel::TopPanel(wxPanel* parent): wxPanel(parent, -1, wxPoint(-1, -1), wxSize(40, 10), wxBORDER_DEFAULT)
{
    /* Basic Setup */
    SetBackgroundColour(wxColour(*wxLIGHT_GREY));

    wxSize minSize(500, 200);
    SetMinSize(minSize);

    /* Add Event Button */
    wxButton* HelloWorld = new wxButton(this, ID_Button_SA, _T("System Analysis"), wxDefaultPosition, wxDefaultSize, 0);


    /* Add Title */

    /* Add Description */



}


/* Default Constructor */
BottomPanel::BottomPanel(wxPanel* parent): wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(40, 10), wxBORDER_DEFAULT)
{
    /* Basic Setup */
    SetBackgroundColour(wxColour(*wxLIGHT_GREY));

    wxSize minSize(500, 200);
    SetMinSize(minSize);

    /* Copy Top Panel but Change Items */
        /* Add Event Button */
    wxButton* HelloWorld = new wxButton(this, ID_Button_SO, _T("System Overview"), wxDefaultPosition, wxDefaultSize, 0);

}




/* Default Panel Class */
class DefaultPanel : public wxPanel
{
public:
    /* Default Constructor */
    DefaultPanel(wxWindow* parent);


};

/* Default Constructor */
DefaultPanel::DefaultPanel(wxWindow * parent)
{
    wxPanel* p_Panel = new wxPanel(parent, wxID_ANY);
    wxBoxSizer* p_Box = new wxBoxSizer(wxVERTICAL);
    TopPanel* p_Tpanel = new TopPanel(p_Panel);
    BottomPanel* p_Bpanel = new BottomPanel(p_Panel);

    p_Box->Add(p_Tpanel, 1, wxEXPAND | wxALL, 5);
    p_Box->Add(p_Bpanel, 1, wxEXPAND | wxALL, 5);

    p_Panel->SetSizer(p_Box);

    this->Centre();
}








/* Data Structure for Initial Frame */
MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame(NULL, wxID_ANY, title, pos, size)
{
    wxSize minSize(500, 500);
    SetMinSize(minSize);
 
    
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

    /* Initialize Panels Avalible */
    //p_defaultPanel = new DefaultPanel(this);
    //wxPanel* p_SystemAnalysisPanel = new SystemAnalysisPanel;
    //wxPanel* p_SystemOverviewPanel = new SystemOverviewPanel;

    /* ADD Sections to Default Window - Clean Up (store in defualt class ? ) */
    //p_defaultPanel->Show(true);
    ////p_SystemAnalysisPanel->Show(false);
    ////p_SystemOverviewPanel->Show(false);
    //p_defaultPanel->Show(false);


    /* Create Default Panel*/
    p_defaultPanel = new wxPanel(this, wxID_ANY);
    wxBoxSizer* p_Box = new wxBoxSizer(wxVERTICAL);
    TopPanel* p_Tpanel = new TopPanel(p_defaultPanel);
    BottomPanel* p_Bpanel = new BottomPanel(p_defaultPanel);
    p_Box->Add(p_Tpanel, 1, wxEXPAND | wxALL, 5);
    p_Box->Add(p_Bpanel, 1, wxEXPAND | wxALL, 5);
    p_defaultPanel->SetSizer(p_Box);
    this->Centre();
    // Add SystemAnal Panel
    // Add SystemOver Panel


    /* Add Panels to Default Window */
    p_defaultPanel->Show(true);
    //p_SystemAnalysisPanel->Show(false);
    //p_SystemOverviewPanel->Show(false);


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
    p_defaultPanel->Show(false);
    wxLogMessage("Change to System Analysis");
}

/* EVENT HANDLER - SYSTEM OVERVIEW */
void MyFrame::OnViewSO(wxCommandEvent& event)
{
    p_defaultPanel->Show(true);



    wxLogMessage("Default Gone");
}






/* Return Panel Pointers */
wxPanel* MyFrame::getDefaultPanelPointer()
{
    return p_defaultPanel;
}

wxPanel* MyFrame::getSystemAnalysisPointer()
{
    return p_SystemAnalysisPanel;
}

wxPanel* MyFrame::getSystemOverviewPanelPointer()
{
    return p_SystemOverviewPanel;
}
