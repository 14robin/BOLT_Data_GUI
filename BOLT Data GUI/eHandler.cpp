/* Event Handler of Desktop Application */

/* Include */
#include "eHandler.h"

/* Event IDs */
enum{
    ID_Hello = 1,
    ID_View_SystemAnalysis = 2,
    ID_View_SystemOverview = 3,
    ID_Button_SA = 4,
    ID_Button_SO = 5,

    ID_Timer = 66,
    TEXT_Main = 67
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

    MainEditBox->WriteText(movedUart.BoltData);
    MainEditBox->WriteText('\n');
}