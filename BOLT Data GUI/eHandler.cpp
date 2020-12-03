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

/* Function Which Allows Continuous Update of Data Plots */
void mpFXYVector::AddData(float xVal, float yVal, std::vector<double>& xVector, std::vector<double>& yVector)
{
    /* Data Vectors Must Be the Same Size in Order to Plot */
    if (xVector.size() != yVector.size()) {
        wxLogError(_("wxMathPlot Error - X and Y Vectors Are Diffrent Lengths"));
        return;
    }

    /* Push New Data Values to End of Vector */
    xVector.push_back(xVal);
    yVector.push_back(yVal);


    // If Vector Gets too Large Only Plot past 25s
    if (xVector.size() > 50)
    {
        xVector.erase(xVector.begin());
        yVector.erase(yVector.begin());
    }

    /* Write New Vectors to Class Data Structure */
    m_xs = xVector;
    m_ys = yVector;

    /* Update The Bounding Box Values */
    if (xVector.size() > 0)
    {
        m_minX = xVector[0];
        m_maxX = xVector[0];
        m_minY = yVector[0];
        m_maxY = yVector[0];

        std::vector<double>::const_iterator  it;

        for (it = xVector.begin(); it != xVector.end(); it++)
        {
            if (*it < m_minX) m_minX = *it;
            if (*it > m_maxX) m_maxX = *it;
        }
        for (it = yVector.begin(); it != yVector.end(); it++)
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


///* System Analysis Panel Class */
//class SystemAnalysisPanel : public wxPanel
//{
//public:
//    /* Default Constructor */
//    SystemAnalysisPanel(wxWindow* parent);
//
//private:
//    /* Variables for System Analysis Panel */
//
//};
//
///* Default Constructor */
//SystemAnalysisPanel::SystemAnalysisPanel(wxWindow * parent): wxPanel(parent, wxID_ANY)
//{
//    SetBackgroundColour(wxColor(*wxBLUE));
//
//
//    ///* Initialize Communication Port */
//    //HANDLE hComm;
//    //LPCWSTR a = L"COM7";
//    //hComm = CreateFile(a, GENERIC_READ, 0, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
//
//
//    ///* Check if Port is Open */
//    //if (hComm == INVALID_HANDLE_VALUE)
//    //    wxLogMessage("Error in opening serial port");
//    //else
//    //    wxLogMessage("opening serial port successful"); 
//
//
//    ///* Initialize DCB Structure */
//    //DCB dcbSerialParams = { 0 };
//    //dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
//
//    //GetCommState(hComm, &dcbSerialParams);
//
//    //dcbSerialParams.BaudRate = CBR_9600;    // Setting BaudRate = 9600
//    //dcbSerialParams.ByteSize = 8;           // Setting ByteSize = 8
//    //dcbSerialParams.StopBits = ONESTOPBIT;  // Setting StopBits = 1
//    //dcbSerialParams.Parity = NOPARITY;      // Setting Parity = None
//
//    //SetCommState(hComm, &dcbSerialParams);
//
//
//
//    ///* Create an Event - Recieve Character */
//    //SetCommMask(hComm, EV_RXCHAR);
//
//
//    ///* Windows will WAIT for Event to Happen - Then Continue ? */
//    //DWORD dwEventMask;
//    //WaitCommEvent(hComm, &dwEventMask, NULL);
//
//
//
//    //char TempChar;                              //Temporary character used for reading
//    //char SerialBuffer[256];                     //Buffer for storing Rxed Data
//    //DWORD NoBytesRead;
//    //int i = 0;                                  // Increment Position of Incoming Data
//
//    //COMMTIMEOUTS timeouts = { 0 };
//    //timeouts.ReadTotalTimeoutConstant = 100;
//
//    ///* Continuous Execution B/C UART is ALWAYS Transmitting */
//    //do
//    //{
//    //    ReadFile(hComm,           //Handle of the Serial port
//    //        &TempChar,       //Temporary character
//    //        sizeof(TempChar),//Size of TempChar
//    //        &NoBytesRead,    //Number of bytes read
//    //        NULL);
//
//    //    SerialBuffer[i] = TempChar;// Store Tempchar into buffer
//    //    i++;
//    //}
//    //while (TempChar != 'x');
//
//    //char SerialBufferCopy[256];
//    //for (int k = 0; k < i; k++)
//    //    SerialBufferCopy[k] = SerialBuffer[k];
//
//    //wxLogMessage(SerialBufferCopy);
//
//
//    //CloseHandle(hComm);//Closing the Serial Port
//
//
//    //Port xBee;
//    //xBee.Read();
//    //xBee.Read();
//    //xBee.Read();
//    //xBee.closePort();
//
//
//    //static const int INTERVAL = 300; // milliseconds
//
//
//
//    
//    //wxFFileOutputStream output(stderr);
//    //wxTextOutputStream cout(output);
//    //cout << "This is a text line" << endl;
//    //cout << 1234;
//    //cout << 1.23456;
//
//    
//
//
//    //wxPanel* p_Panel = new wxPanel(parent, wxID_ANY);
//    //wxBoxSizer* p_Box = new wxBoxSizer(wxVERTICAL);
//    //TopPanel* p_Tpanel = new TopPanel(p_Panel);
//    //BottomPanel* p_Bpanel = new BottomPanel(p_Panel);
//
//    //p_Box->Add(p_Tpanel, 1, wxEXPAND | wxALL, 5);
//    //p_Box->Add(p_Bpanel, 1, wxEXPAND | wxALL, 5);
//
//    //p_Panel->SetSizer(p_Box);
//
//    //this->Centre();
//}










/* Data Structure for Main Frame */
MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame(NULL, wxID_ANY, title, pos, size)
{
    ///* Create Serial Port Connection */
    //xBee.CreatePort();



    // Frame 
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

    ///* Timer Used to Refresh Plot Data */
    //wxTimer* m_timer = new wxTimer(this, ID_Timer);
    //m_timer->Start(600);


    /* ------------------------------- Graph Data ------------------------------- */


    /* Graph Axis */
    mpScaleX* xaxis = new mpScaleX(wxT("Time"), mpALIGN_BOTTOM || mpALIGN_LEFT, false, mpX_TIME);
    mpScaleY* yaxis = new mpScaleY(wxT("Value(units)"), mpALIGN_LEFT, true);
    wxFont graphFont(9, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    xaxis->SetFont(graphFont);
    yaxis->SetFont(graphFont);
    xaxis->SetDrawOutsideMargins(false);
    yaxis->SetDrawOutsideMargins(false);


    // vectorLayer
    vectorLayer = new mpFXYVector(_("SOC"));
    vectorLayer->SetContinuity(true);
    wxPen vectorpen(*wxBLUE, 2, wxPENSTYLE_SOLID);
    vectorLayer->SetPen(vectorpen);
    vectorLayer->SetDrawOutsideMargins(false);

    /* m_plot */
    m_plot = new mpWindow(this, -1, wxPoint(0, 0), wxSize(100, 100), wxSUNKEN_BORDER);
    m_plot->SetMargins(20, 40, 40, 80);
    m_plot->AddLayer(xaxis);
    m_plot->AddLayer(yaxis);
    m_plot->AddLayer(vectorLayer);
    m_plot->AddLayer(new mpText(wxT("SOC"), 30, 5));

    // vectorLayer
    vectorLayer1 = new mpFXYVector(_("FPV"));
    vectorLayer1->SetContinuity(true);
    vectorLayer1->SetPen(vectorpen);
    vectorLayer1->SetDrawOutsideMargins(false);

    /* m_plot */
    m_plot1 = new mpWindow(this, -1, wxPoint(0, 0), wxSize(100, 100), wxSUNKEN_BORDER);
    m_plot1->SetMargins(20, 40, 40, 85);
    m_plot1->AddLayer(xaxis);
    m_plot1->AddLayer(yaxis);
    m_plot1->AddLayer(vectorLayer1);
    m_plot1->AddLayer(new mpText(wxT("FPV"), 30, 5));

    // vectorLayer
    vectorLayer2 = new mpFXYVector(_("highTemp"));
    vectorLayer2->SetContinuity(true);
    vectorLayer2->SetPen(vectorpen);
    vectorLayer2->SetDrawOutsideMargins(false);

    /* m_plot */
    m_plot2 = new mpWindow(this, -1, wxPoint(0, 0), wxSize(100, 100), wxSUNKEN_BORDER);
    m_plot2->SetMargins(20, 40, 40, 85);
    m_plot2->AddLayer(xaxis);
    m_plot2->AddLayer(yaxis);
    m_plot2->AddLayer(vectorLayer2);
    m_plot2->AddLayer(new mpText(wxT("highTemp"), 30, 5));

    // vectorLayer
    vectorLayer3 = new mpFXYVector(_("lowTemp"));
    vectorLayer3->SetContinuity(true);
    vectorLayer3->SetPen(vectorpen);
    vectorLayer3->SetDrawOutsideMargins(false);

    /* m_plot */
    m_plot3 = new mpWindow(this, -1, wxPoint(0, 0), wxSize(100, 100), wxSUNKEN_BORDER);
    m_plot3->SetMargins(20, 40, 40, 85);
    m_plot3->AddLayer(xaxis);
    m_plot3->AddLayer(yaxis);
    m_plot3->AddLayer(vectorLayer3);
    m_plot3->AddLayer(new mpText(wxT("lowTemp"), 30, 5));

    // vectorLayer
    vectorLayer4 = new mpFXYVector(_("highVoltage"));
    vectorLayer4->SetContinuity(true);
    vectorLayer4->SetPen(vectorpen);
    vectorLayer4->SetDrawOutsideMargins(false);

    /* m_plot */
    m_plot4 = new mpWindow(this, -1, wxPoint(0, 0), wxSize(100, 100), wxSUNKEN_BORDER);
    m_plot4->SetMargins(20, 40, 40, 85);
    m_plot4->AddLayer(xaxis);
    m_plot4->AddLayer(yaxis);
    m_plot4->AddLayer(vectorLayer4);
    m_plot4->AddLayer(new mpText(wxT("highVoltage"), 30, 5));

    // vectorLayer
    vectorLayer5 = new mpFXYVector(_("lowVoltage"));
    vectorLayer5->SetContinuity(true);
    vectorLayer5->SetPen(vectorpen);
    vectorLayer5->SetDrawOutsideMargins(false);

    /* m_plot */
    m_plot5 = new mpWindow(this, -1, wxPoint(0, 0), wxSize(100, 100), wxSUNKEN_BORDER);
    m_plot5->SetMargins(20, 40, 40, 85);
    m_plot5->AddLayer(xaxis);
    m_plot5->AddLayer(yaxis);
    m_plot5->AddLayer(vectorLayer5);
    m_plot5->AddLayer(new mpText(wxT("lowVoltage"), 30, 5));

    // vectorLayer
    vectorLayer6 = new mpFXYVector(_("RPM"));
    vectorLayer6->SetContinuity(true);
    vectorLayer6->SetPen(vectorpen);
    vectorLayer6->SetDrawOutsideMargins(false);

    /* m_plot */
    m_plot6 = new mpWindow(this, -1, wxPoint(0, 0), wxSize(100, 100), wxSUNKEN_BORDER);
    m_plot6->SetMargins(20, 40, 40, 85);
    m_plot6->AddLayer(xaxis);
    m_plot6->AddLayer(yaxis);
    m_plot6->AddLayer(vectorLayer6);
    m_plot6->AddLayer(new mpText(wxT("RPM"), 30, 5));

    // vectorLayer
    vectorLayer7 = new mpFXYVector(_("motorTemp"));
    vectorLayer7->SetContinuity(true);
    vectorLayer7->SetPen(vectorpen);
    vectorLayer7->SetDrawOutsideMargins(false);

    /* m_plot */
    m_plot7 = new mpWindow(this, -1, wxPoint(0, 0), wxSize(100, 100), wxSUNKEN_BORDER);
    m_plot7->SetMargins(20, 40, 40, 85);
    m_plot7->AddLayer(xaxis);
    m_plot7->AddLayer(yaxis);
    m_plot7->AddLayer(vectorLayer7);
    m_plot7->AddLayer(new mpText(wxT("motorTemp"), 30, 5));

    // vectorLayer
    vectorLayer8 = new mpFXYVector(_("dcBusCurrent"));
    vectorLayer8->SetContinuity(true);
    vectorLayer8->SetPen(vectorpen);
    vectorLayer8->SetDrawOutsideMargins(false);

    /* m_plot */
    m_plot8 = new mpWindow(this, -1, wxPoint(0, 0), wxSize(100, 100), wxSUNKEN_BORDER);
    m_plot8->SetMargins(20, 40, 40, 85);
    m_plot8->AddLayer(xaxis);
    m_plot8->AddLayer(yaxis);
    m_plot8->AddLayer(vectorLayer8);
    m_plot8->AddLayer(new mpText(wxT("dcBusCurrent"), 30, 5));

    // vectorLayer
    vectorLayer9 = new mpFXYVector(_("motorTorque"));
    vectorLayer9->SetContinuity(true);
    vectorLayer9->SetPen(vectorpen);
    vectorLayer9->SetDrawOutsideMargins(false);

    /* m_plot */
    m_plot9 = new mpWindow(this, -1, wxPoint(0, 0), wxSize(100, 100), wxSUNKEN_BORDER);
    m_plot9->SetMargins(20, 40, 40, 85);
    m_plot9->AddLayer(xaxis);
    m_plot9->AddLayer(yaxis);
    m_plot9->AddLayer(vectorLayer9);
    m_plot9->AddLayer(new mpText(wxT("motorTorque"), 30, 5));

    // vectorLayer
    vectorLayer10 = new mpFXYVector(_("motorCtrlTemp"));
    vectorLayer10->SetContinuity(true);
    vectorLayer10->SetPen(vectorpen);
    vectorLayer10->SetDrawOutsideMargins(false);

    /* m_plot */
    m_plot10 = new mpWindow(this, -1, wxPoint(0, 0), wxSize(100, 100), wxSUNKEN_BORDER);
    m_plot10->SetMargins(20, 40, 40, 85);
    m_plot10->AddLayer(xaxis);
    m_plot10->AddLayer(yaxis);
    m_plot10->AddLayer(vectorLayer10);
    m_plot10->AddLayer(new mpText(wxT("motorCtrlTemp"), 30, 5));


    // vectorLayer
    vectorLayer11 = new mpFXYVector(_("auxVoltage"));
    vectorLayer11->SetContinuity(true);
    vectorLayer11->SetPen(vectorpen);
    vectorLayer11->SetDrawOutsideMargins(false);

    /* m_plot */
    m_plot11 = new mpWindow(this, -1, wxPoint(0, 0), wxSize(100, 100), wxSUNKEN_BORDER);
    m_plot11->SetMargins(20, 40, 40, 85);
    m_plot11->AddLayer(xaxis);
    m_plot11->AddLayer(yaxis);
    m_plot11->AddLayer(vectorLayer11);
    m_plot11->AddLayer(new mpText(wxT("auxVoltage"), 30, 5));

    // vectorLayer
    vectorLayer12 = new mpFXYVector(_("xAcc"));
    vectorLayer12->SetContinuity(true);
    vectorLayer12->SetPen(vectorpen);
    vectorLayer12->SetDrawOutsideMargins(false);

    /* m_plot */
    m_plot12 = new mpWindow(this, -1, wxPoint(0, 0), wxSize(100, 100), wxSUNKEN_BORDER);
    m_plot12->SetMargins(20, 40, 40, 85);
    m_plot12->AddLayer(xaxis);
    m_plot12->AddLayer(yaxis);
    m_plot12->AddLayer(vectorLayer12);
    m_plot12->AddLayer(new mpText(wxT("xAcc"), 30, 5));

    // vectorLayer
    vectorLayer13 = new mpFXYVector(_("yAcc"));
    vectorLayer13->SetContinuity(true);
    vectorLayer13->SetPen(vectorpen);
    vectorLayer13->SetDrawOutsideMargins(false);

    /* m_plot */
    m_plot13 = new mpWindow(this, -1, wxPoint(0, 0), wxSize(100, 100), wxSUNKEN_BORDER);
    m_plot13->SetMargins(20, 40, 40, 85);
    m_plot13->AddLayer(xaxis);
    m_plot13->AddLayer(yaxis);
    m_plot13->AddLayer(vectorLayer13);
    m_plot13->AddLayer(new mpText(wxT("yAcc"), 30, 5));

    // vectorLayer
    vectorLayer14 = new mpFXYVector(_("zAcc"));
    vectorLayer14->SetContinuity(true);
    vectorLayer14->SetPen(vectorpen);
    vectorLayer14->SetDrawOutsideMargins(false);

    /* m_plot */
    m_plot14 = new mpWindow(this, -1, wxPoint(0, 0), wxSize(100, 100), wxSUNKEN_BORDER);
    m_plot14->SetMargins(20, 40, 40, 85);
    m_plot14->AddLayer(xaxis);
    m_plot14->AddLayer(yaxis);
    m_plot14->AddLayer(vectorLayer14);
    m_plot14->AddLayer(new mpText(wxT("zAcc"), 30, 5));

    // vectorLayer
    vectorLayer15 = new mpFXYVector(_("xGyro"));
    vectorLayer15->SetContinuity(true);
    vectorLayer15->SetPen(vectorpen);
    vectorLayer15->SetDrawOutsideMargins(false);

    /* m_plot */
    m_plot15 = new mpWindow(this, -1, wxPoint(0, 0), wxSize(100, 100), wxSUNKEN_BORDER);
    m_plot15->SetMargins(20, 40, 40, 85);
    m_plot15->AddLayer(xaxis);
    m_plot15->AddLayer(yaxis);
    m_plot15->AddLayer(vectorLayer15);
    m_plot15->AddLayer(new mpText(wxT("xGyro"), 30, 5));

    // vectorLayer
    vectorLayer16 = new mpFXYVector(_("yGyro"));
    vectorLayer16->SetContinuity(true);
    vectorLayer16->SetPen(vectorpen);
    vectorLayer16->SetDrawOutsideMargins(false);

    /* m_plot */
    m_plot16 = new mpWindow(this, -1, wxPoint(0, 0), wxSize(100, 100), wxSUNKEN_BORDER);
    m_plot16->SetMargins(20, 40, 40, 85);
    m_plot16->AddLayer(xaxis);
    m_plot16->AddLayer(yaxis);
    m_plot16->AddLayer(vectorLayer16);
    m_plot16->AddLayer(new mpText(wxT("yGyro"), 30, 5));

    // vectorLayer
    vectorLayer17 = new mpFXYVector(_("zGyro"));
    vectorLayer17->SetContinuity(true);
    vectorLayer17->SetPen(vectorpen);
    vectorLayer17->SetDrawOutsideMargins(false);

    /* m_plot */
    m_plot17 = new mpWindow(this, -1, wxPoint(0, 0), wxSize(100, 100), wxSUNKEN_BORDER);
    m_plot17->SetMargins(20, 40, 40, 85);
    m_plot17->AddLayer(xaxis);
    m_plot17->AddLayer(yaxis);
    m_plot17->AddLayer(vectorLayer17);
    m_plot17->AddLayer(new mpText(wxT("zGyro"), 30, 5));

    // vectorLayer
    vectorLayer18 = new mpFXYVector(_("roll"));
    vectorLayer18->SetContinuity(true);
    vectorLayer18->SetPen(vectorpen);
    vectorLayer18->SetDrawOutsideMargins(false);

    /* m_plot */
    m_plot18 = new mpWindow(this, -1, wxPoint(0, 0), wxSize(100, 100), wxSUNKEN_BORDER);
    m_plot18->SetMargins(20, 40, 40, 85);
    m_plot18->AddLayer(xaxis);
    m_plot18->AddLayer(yaxis);
    m_plot18->AddLayer(vectorLayer18);
    m_plot18->AddLayer(new mpText(wxT("roll"), 30, 5));

    // vectorLayer
    vectorLayer19 = new mpFXYVector(_("pitch"));
    vectorLayer19->SetContinuity(true);
    vectorLayer19->SetPen(vectorpen);
    vectorLayer19->SetDrawOutsideMargins(false);

    /* m_plot */
    m_plot19 = new mpWindow(this, -1, wxPoint(0, 0), wxSize(100, 100), wxSUNKEN_BORDER);
    m_plot19->SetMargins(20, 40, 40, 85);
    m_plot19->AddLayer(xaxis);
    m_plot19->AddLayer(yaxis);
    m_plot19->AddLayer(vectorLayer19);
    m_plot19->AddLayer(new mpText(wxT("pitch"), 30, 5));







    /* Sizer to Hold Plots */
    wxBoxSizer* mainsizer = new wxBoxSizer(wxHORIZONTAL);
    leftSizer = new wxBoxSizer(wxVERTICAL);
    rightSizer = new wxBoxSizer(wxVERTICAL);

    /* Format Plot Space 2x10 */
    leftSizer->Add(m_plot, 1, wxEXPAND);
    leftSizer->Add(m_plot1, 1, wxEXPAND);
    leftSizer->Add(m_plot2, 1, wxEXPAND);
    leftSizer->Add(m_plot3, 1, wxEXPAND);
    leftSizer->Add(m_plot4, 1, wxEXPAND);
    leftSizer->Add(m_plot5, 1, wxEXPAND);
    leftSizer->Add(m_plot6, 1, wxEXPAND);
    leftSizer->Add(m_plot7, 1, wxEXPAND);
    leftSizer->Add(m_plot8, 1, wxEXPAND);
    leftSizer->Add(m_plot9, 1, wxEXPAND);

    rightSizer->Add(m_plot10, 1, wxEXPAND);
    rightSizer->Add(m_plot11, 1, wxEXPAND);
    rightSizer->Add(m_plot12, 1, wxEXPAND);
    rightSizer->Add(m_plot13, 1, wxEXPAND);
    rightSizer->Add(m_plot14, 1, wxEXPAND);
    rightSizer->Add(m_plot15, 1, wxEXPAND);
    rightSizer->Add(m_plot16, 1, wxEXPAND);
    rightSizer->Add(m_plot17, 1, wxEXPAND);
    rightSizer->Add(m_plot18, 1, wxEXPAND);
    rightSizer->Add(m_plot19, 1, wxEXPAND);

    mainsizer->Add(leftSizer, 1, wxEXPAND);
    mainsizer->Add(rightSizer, 1, wxEXPAND);

    /* Display Plot Sizers */
    SetAutoLayout(TRUE);
    SetSizer(mainsizer);


    /* Initialize X AXIS Value */
    xAxisValue = 0;
}





/* EVENT HANDLER - ABOUT */
void MyFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox("Bolt IV Graphical User Interface",
        "About Hello World", wxOK | wxICON_INFORMATION);
}

/* EVENT HANDLER - EXIT */
void MyFrame::OnExit(wxCommandEvent& event)
{
    xBee.DeletePort();
    Close(true);
}

/* EVENT HANDLER - HELLO */
void MyFrame::OnHello(wxCommandEvent& event)
{
    wxLogMessage("Bolt IV Graphical User Interface");
}

/* EVENT HANDLER - SYSTEM ANALYSIS */
void MyFrame::OnViewSA(wxCommandEvent& event)
{
    wxLogMessage("Bolt Port Closed");
}

/* EVENT HANDLER - SYSTEM OVERVIEW */
void MyFrame::OnViewSO(wxCommandEvent& event)
{
    /* Create Plotting Event */
    xBee.CreatePort();
    wxTimer* m_timer = new wxTimer(this, ID_Timer);
    m_timer->Start(600);
}




/* EVENT HANDLER - SYSTEM OVERVIEW */
void MyFrame::TimerCall(wxTimerEvent& event)
{
    /* Format Incomming Data */
    xBee.formatInputString();
    xBee.refreshBoltIVdata();

    /* Update Data Vectors */
    vectorLayer->AddData(xAxisValue, xBee.BoltIV.SOC, xAxisVector.SOC, yAxisVector.SOC);
    vectorLayer1->AddData(xAxisValue, xBee.BoltIV.FPV, xAxisVector.FPV, yAxisVector.FPV);
    vectorLayer2->AddData(xAxisValue, xBee.BoltIV.highTemp, xAxisVector.highTemp, yAxisVector.highTemp);
    vectorLayer3->AddData(xAxisValue, xBee.BoltIV.lowTemp, xAxisVector.lowTemp, yAxisVector.lowTemp);
    vectorLayer4->AddData(xAxisValue, xBee.BoltIV.highVoltage, xAxisVector.highVoltage, yAxisVector.highVoltage);
    vectorLayer5->AddData(xAxisValue, xBee.BoltIV.lowVoltage, xAxisVector.lowVoltage, yAxisVector.lowVoltage);
    vectorLayer6->AddData(xAxisValue, xBee.BoltIV.RPM, xAxisVector.RPM, yAxisVector.RPM);
    vectorLayer7->AddData(xAxisValue, xBee.BoltIV.motorTemp, xAxisVector.motorTemp, yAxisVector.motorTemp);
    vectorLayer8->AddData(xAxisValue, xBee.BoltIV.dcBusCurrent, xAxisVector.dcBusCurrent, yAxisVector.dcBusCurrent);
    vectorLayer9->AddData(xAxisValue, xBee.BoltIV.motorTorque, xAxisVector.motorTorque, yAxisVector.motorTorque);
    vectorLayer10->AddData(xAxisValue, xBee.BoltIV.motorCtrlTemp, xAxisVector.motorCtrlTemp, yAxisVector.motorCtrlTemp);
    vectorLayer11->AddData(xAxisValue, xBee.BoltIV.auxVoltage, xAxisVector.auxVoltage, yAxisVector.auxVoltage);
    vectorLayer12->AddData(xAxisValue, xBee.BoltIV.xAcc, xAxisVector.xAcc, yAxisVector.xAcc);
    vectorLayer13->AddData(xAxisValue, xBee.BoltIV.yAcc, xAxisVector.yAcc, yAxisVector.yAcc);
    vectorLayer14->AddData(xAxisValue, xBee.BoltIV.zAcc, xAxisVector.zAcc, yAxisVector.zAcc);
    vectorLayer15->AddData(xAxisValue, xBee.BoltIV.xGyro, xAxisVector.xGyro, yAxisVector.xGyro);
    vectorLayer16->AddData(xAxisValue, xBee.BoltIV.yGyro, xAxisVector.yGyro, yAxisVector.yGyro);
    vectorLayer17->AddData(xAxisValue, xBee.BoltIV.zGyro, xAxisVector.zGyro, yAxisVector.zGyro);
    vectorLayer18->AddData(xAxisValue, xBee.BoltIV.roll, xAxisVector.roll, yAxisVector.roll);
    vectorLayer19->AddData(xAxisValue, xBee.BoltIV.pitch, xAxisVector.pitch, yAxisVector.pitch);

    /* Update Plots */
    m_plot->Fit();
    m_plot1->Fit();
    m_plot2->Fit();
    m_plot3->Fit();
    m_plot4->Fit();
    m_plot5->Fit();
    m_plot6->Fit();
    m_plot7->Fit();
    m_plot8->Fit();
    m_plot9->Fit();
    m_plot10->Fit();
    m_plot11->Fit();
    m_plot12->Fit();
    m_plot13->Fit();
    m_plot14->Fit();
    m_plot15->Fit();
    m_plot16->Fit();
    m_plot17->Fit();
    m_plot18->Fit();
    m_plot19->Fit();

    /* Update x Axis Value */
    xAxisValue = xAxisValue + 500;
}