/* Event Handler of Desktop Application */

/* Include */
#include "eHandler.h"

/* Event IDs */
enum {
    ID_Hello = 1,
    ID_View_SystemAnalysis = 2,
    ID_View_SystemOverview = 3,
    ID_Button_SA = 4,
    ID_Button_SO = 5,

    ID_Timer = 66,
    TEXT_Main = 67,
    ID_GRAPH = 68
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

EVT_TIMER(ID_Timer, MyFrame::TimerCall)

wxEND_EVENT_TABLE()


void mpFXYVector::AddData(float x, float y, std::vector<double>& xs, std::vector<double>& ys)
{
    // Check if the data vectora are of the same size
    if (xs.size() != ys.size()) {
        wxLogError(_("wxMathPlot error: X and Y vector are not of the same length!"));
        return;
    }

    //Delete first point if you need a filo buffer (i dont need it)
    //xs.erase(xs.begin());
    //xy.erase(xy.begin());

    //Add new Data points at the end
    xs.push_back(x);
    ys.push_back(y);


    // Copy the data:
    m_xs = xs;
    m_ys = ys;

    // Update internal variables for the bounding box.
    if (xs.size() > 0)
    {
        m_minX = xs[0];
        m_maxX = xs[0];
        m_minY = ys[0];
        m_maxY = ys[0];

        std::vector<double>::const_iterator  it;

        for (it = xs.begin(); it != xs.end(); it++)
        {
            if (*it < m_minX) m_minX = *it;
            if (*it > m_maxX) m_maxX = *it;
        }
        for (it = ys.begin(); it != ys.end(); it++)
        {
            if (*it < m_minY) m_minY = *it;
            if (*it > m_maxY) m_maxY = *it;
        }
        m_minX -= 0.5f;
        m_minY -= 0.5f;
        m_maxX += 0.5f;
        m_maxY += 0.5f;
    }
    else
    {
        m_minX = -1;
        m_maxX = 1;
        m_minY = -1;
        m_maxY = 1;
    }
}


/* System Analysis Panel Class */
class SystemAnalysisPanel : public wxPanel
{
public:
    /* Default Constructor */
    SystemAnalysisPanel(wxWindow* parent);

private:
    /* Variables for System Analysis Panel */

};

/* Default Constructor */
SystemAnalysisPanel::SystemAnalysisPanel(wxWindow * parent): wxPanel(parent, wxID_ANY)
{
    SetBackgroundColour(wxColor(*wxBLUE));


    ///* Initialize Communication Port */
    //HANDLE hComm;
    //LPCWSTR a = L"COM7";
    //hComm = CreateFile(a, GENERIC_READ, 0, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);


    ///* Check if Port is Open */
    //if (hComm == INVALID_HANDLE_VALUE)
    //    wxLogMessage("Error in opening serial port");
    //else
    //    wxLogMessage("opening serial port successful"); 


    ///* Initialize DCB Structure */
    //DCB dcbSerialParams = { 0 };
    //dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

    //GetCommState(hComm, &dcbSerialParams);

    //dcbSerialParams.BaudRate = CBR_9600;    // Setting BaudRate = 9600
    //dcbSerialParams.ByteSize = 8;           // Setting ByteSize = 8
    //dcbSerialParams.StopBits = ONESTOPBIT;  // Setting StopBits = 1
    //dcbSerialParams.Parity = NOPARITY;      // Setting Parity = None

    //SetCommState(hComm, &dcbSerialParams);



    ///* Create an Event - Recieve Character */
    //SetCommMask(hComm, EV_RXCHAR);


    ///* Windows will WAIT for Event to Happen - Then Continue ? */
    //DWORD dwEventMask;
    //WaitCommEvent(hComm, &dwEventMask, NULL);



    //char TempChar;                              //Temporary character used for reading
    //char SerialBuffer[256];                     //Buffer for storing Rxed Data
    //DWORD NoBytesRead;
    //int i = 0;                                  // Increment Position of Incoming Data

    //COMMTIMEOUTS timeouts = { 0 };
    //timeouts.ReadTotalTimeoutConstant = 100;

    ///* Continuous Execution B/C UART is ALWAYS Transmitting */
    //do
    //{
    //    ReadFile(hComm,           //Handle of the Serial port
    //        &TempChar,       //Temporary character
    //        sizeof(TempChar),//Size of TempChar
    //        &NoBytesRead,    //Number of bytes read
    //        NULL);

    //    SerialBuffer[i] = TempChar;// Store Tempchar into buffer
    //    i++;
    //}
    //while (TempChar != 'x');

    //char SerialBufferCopy[256];
    //for (int k = 0; k < i; k++)
    //    SerialBufferCopy[k] = SerialBuffer[k];

    //wxLogMessage(SerialBufferCopy);


    //CloseHandle(hComm);//Closing the Serial Port


    //Port xBee;
    //xBee.Read();
    //xBee.Read();
    //xBee.Read();
    //xBee.closePort();


    //static const int INTERVAL = 300; // milliseconds



    
    //wxFFileOutputStream output(stderr);
    //wxTextOutputStream cout(output);
    //cout << "This is a text line" << endl;
    //cout << 1234;
    //cout << 1.23456;

    


    //wxPanel* p_Panel = new wxPanel(parent, wxID_ANY);
    //wxBoxSizer* p_Box = new wxBoxSizer(wxVERTICAL);
    //TopPanel* p_Tpanel = new TopPanel(p_Panel);
    //BottomPanel* p_Bpanel = new BottomPanel(p_Panel);

    //p_Box->Add(p_Tpanel, 1, wxEXPAND | wxALL, 5);
    //p_Box->Add(p_Bpanel, 1, wxEXPAND | wxALL, 5);

    //p_Panel->SetSizer(p_Box);

    //this->Centre();
}










/* Data Structure for Initial Frame */
MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame(NULL, wxID_ANY, title, pos, size)
{
    //serialLate xBee;
    //xBee.OnUserCreate();

    movedUart.OnUserCreate();




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


    wxTimer* m_timer = new wxTimer(this, ID_Timer);
    m_timer->Start(600);



    /* Create System Analysis Panel*/
    p_SystemAnalysisPanel = new SystemAnalysisPanel(this);
    p_SystemAnalysisPanel->Show(true);


    MainEditBox = new wxTextCtrl(this, TEXT_Main, "<<-- Data ", wxDefaultPosition, wxSize(1150, 550),
        wxTE_MULTILINE | wxTE_RICH, wxDefaultValidator, wxTextCtrlNameStr);


    //MainEditBox->WriteText(xBee.dataIn);
    //MainEditBox->WriteText('\n');

    //MainEditBox->WriteText(xBee.dataIn);
    //MainEditBox->WriteText('\n');




    //asio::io_service io;
    //asio::serial_port xBee(io, "COM5");

    //if (xBee.is_open())
    //    wxLogMessage("FUCK YES NOW JUST READ DATA");


    //xBee.set_option(asio::serial_port::baud_rate(57600));

    //xBee.set_option(asio::serial_port_base::character_size());
    //xBee.set_option(asio::serial_port_base::stop_bits());
    //xBee.set_option(asio::serial_port_base::parity());
    //xBee.set_option(asio::serial_port_base::flow_control());

    //char nIncomingByte;
    //xBee.async_read_some(asio::buffer(&nIncomingByte, 1))
    //   
    //xBee.set_option(asio::serial_port_base::parity(PARITY_NONE));
    //xBee.set_option(asio::serial_port_base::baud_rate(BAUD_57600));
    //xBee.set_option(DATABITS_8);

    //asio::async_read(xBee, asio::buffer(m_read_message.data(), m_read_message.m_header_length), [this](asio::error_code& ec, std::size_t /*length*/)

    //for (;;)
    //{
    //    // get a string from the user, sentiel is exit
    //    std::string input;
    //    char data[512];

    //    // read bytes from the serial port
    //    // asio::read will read bytes until the buffer is filled
    //    size_t nread = asio::read(
    //        xBee, asio::buffer(data, input.length())
    //    );

    //    std::string message(data, nread);

    //    char printxBee[512];
    //    for (int k = 0; k < message.size(); k++)
    //        printxBee[k] = message[k];
    //    wxLogMessage(printxBee);
    //}



    //char data[256];
    //std::string input;

    //size_t nread = asio::read(
    //    xBee, asio::buffer(data, input.length())
    //);

    //std::string message(data, nread);




    //xBee.close();




    //xBee.OnUserDestroy();

    //wxMathPlot* m_Vector = new wxMathPlot(\);

    //m_Vector->AddData(xPos, yPos, vectorX, vectorY);
    //m_plot->Fit();


    /* ------------------------------- NEED THIS VECTOR Layer FOR GRAPH ------------------------------- */

    // Create a mpFXYVector layer
    vectorLayer = new mpFXYVector(_("Vector"));

    // Create two vectors for x,y and fill them with DEFAUL data
    std::vector<double> vectorx, vectory;
    double xcoord;
    for (unsigned int p = 0; p < 100; p++) {
        xcoord = ((double)p - 50.0) * 5.0;
        vectorx.push_back(xcoord);
        vectory.push_back(0.0001 * pow(xcoord, 3));
    }
    vectorLayer->SetData(vectorx, vectory);

    /* Set Continuity of Vector Layer to Continuous */
    vectorLayer->SetContinuity(true);

    /* How to Actually Draw the Data */
    wxPen vectorpen(*wxBLUE, 2, wxPENSTYLE_SOLID);
    vectorLayer->SetPen(vectorpen);
    vectorLayer->SetDrawOutsideMargins(false);


    /* How GRAPH IS DRAWN ? */
    wxFont graphFont(11, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    m_plot = new mpWindow(this, -1, wxPoint(0, 0), wxSize(100, 100), wxSUNKEN_BORDER);
    mpScaleX* xaxis = new mpScaleX(wxT("X"), mpALIGN_BOTTOM, true, mpX_NORMAL);
    mpScaleY* yaxis = new mpScaleY(wxT("Y"), mpALIGN_LEFT, true);
    xaxis->SetFont(graphFont);
    yaxis->SetFont(graphFont);
    xaxis->SetDrawOutsideMargins(false);
    yaxis->SetDrawOutsideMargins(false);

    m_plot->SetMargins(30, 30, 50, 100);

    m_plot->AddLayer(xaxis);
    m_plot->AddLayer(yaxis);
    m_plot->AddLayer(vectorLayer);

    m_plot->AddLayer(new mpText(wxT("BOLT DATA GUI"), 10, 10));

    wxBrush hatch(wxColour(200, 200, 200), wxBRUSHSTYLE_SOLID);
    wxBrush hatch2(wxColour(163, 208, 212), wxBRUSHSTYLE_SOLID);

    mpInfoLegend* leg;
    m_plot->AddLayer(leg = new mpInfoLegend(wxRect(200, 20, 40, 40), wxTRANSPARENT_BRUSH)); //&hatch2));
    leg->SetVisible(true);


    wxPen mypen(*wxRED, 5, wxPENSTYLE_SOLID);

    m_log = new wxTextCtrl(this, -1, wxT("This is the log window.\n"), wxPoint(0, 0), wxSize(100, 100), wxTE_MULTILINE);
    wxLog* old_log = wxLog::SetActiveTarget(new wxLogTextCtrl(m_log));
    delete old_log;

    wxBoxSizer* topsizer = new wxBoxSizer(wxVERTICAL);

    topsizer->Add(m_plot, 1, wxEXPAND);
    topsizer->Add(m_log, 0, wxEXPAND);

    SetAutoLayout(TRUE);
    SetSizer(topsizer);


    m_plot->EnableDoubleBuffer(true);
    m_plot->SetMPScrollbars(false);
    m_plot->Fit();

    wxgraphindex = 100;
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
    wxLogMessage("Bolt Port Closed");
    movedUart.OnUserDestroy();
}

/* EVENT HANDLER - SYSTEM OVERVIEW */
void MyFrame::OnViewSO(wxCommandEvent& event)
{
    wxLogMessage("MOST RECENT DATA IN");
}




/* EVENT HANDLER - SYSTEM OVERVIEW */
void MyFrame::TimerCall(wxTimerEvent& event)
{
    //movedUart.parseDataIn();

    movedUart.parseDataInArduino();
    movedUart.parseBoltData();

    //MainEditBox->WriteText(movedUart.BoltData);
    //MainEditBox->WriteText('\n');

    vectorLayer->AddData(wxgraphindex, movedUart.SOC, XvectorwxGraph, YvectorwxGraph);
    m_plot->Fit();
    wxgraphindex++;
}