
/* Includes */
#pragma once
#include "framework.h"
#include "mathplot.h"
#include <wx/stattext.h>
#include <wx/panel.h>
#include <windows.h>
#include <stdio.h>
//#include "portCommuniction.h"
#include <wx/txtstrm.h>
#include <wx/wfstream.h>


#define ASIO_STANDALONE
#include "asio.hpp"

// If Precompilation is Supported Include "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif



/* Struct to Organize and Track Bolt IV Data */
struct BoltIVdata
{
    int SOC, FPV, highTemp, lowTemp, highVoltage, lowVoltage, RPM, motorTemp, dcBusCurrent, motorTorque, motorCtrlTemp;
    int auxVoltage, xAcc, yAcc, zAcc, xGyro, yGyro, zGyro, roll, pitch;
};

/* Struct to Organize and Track Bolt IV Data */
struct BoltIVdataVectors
{
    std::vector<double> SOC, FPV, highTemp, lowTemp, highVoltage, lowVoltage, RPM, motorTemp, dcBusCurrent, motorTorque, motorCtrlTemp;
    std::vector<double> auxVoltage, xAcc, yAcc, zAcc, xGyro, yGyro, zGyro, roll, pitch;
};


/* Class to Interface with Computer Port */
class portClass
{
public:

    /* Initialize Structure for Bolt IV Data */
    BoltIVdata BoltIV;

    /* Low Level Port Variables */
    asio::io_context context;
    std::thread thrContext;
    std::unique_ptr<asio::serial_port> port_handle;

    /* High Level Port Variables */
    char nIncomingByte;
    char dataIn[165];
    char dataInFormated[165];
    char startDelimiter;
    char endDelimiter;
    int dataInIndex;
    bool dataInRead;


    // Use for Xbee Transmission - NOT ARDUINO
    //void parseDataIn()
    //{
    //    for (int k = 0; k < 148; k++)
    //    {
    //        if (dataIn[k + 17] == '\0')
    //            BoltData[k] = '0';
    //        else
    //            BoltData[k] = dataIn[k + 17];
    //    }
    //}


    /* ARDUINO - Convert Incomming String to xBee Transmission */
    void formatInputString()
    {
        int offset = 0;
        int track = 0;

        for (int k = 0; k < 99; k++)
        {
            dataInFormated[k] = dataIn[k - offset + 1];
            
            track++;
            if (track == 5)
            {
                dataInFormated[k] = ',';
                offset++;
                track = 0;
            }
        }
    }

    /* Update the Bolt IV Struct Variables with the Latest Recieved Data */
    void refreshBoltIVdata()
    {
        char hold[4];
        int holdindex = 0;

        holdindex = 0;
        for (int k = 0; k < 4; k++)             // SOC
        {
            hold[holdindex] = dataInFormated[k];
            holdindex++;
        }
        BoltIV.SOC = atoi(hold);

        holdindex = 0;
        for (int k = 5; k < 9; k++)             // FPV
        {
            hold[holdindex] = dataInFormated[k];
            holdindex++;
        }
        BoltIV.FPV = atoi(hold);

        holdindex = 0;
        for (int k = 10; k < 14; k++)           // highTemp
        {
            hold[holdindex] = dataInFormated[k];
            holdindex++;
        }
        BoltIV.highTemp = atoi(hold);

        holdindex = 0;
        for (int k = 15; k < 19; k++)           // lowTemp
        {
            hold[holdindex] = dataInFormated[k];
            holdindex++;
        }
        BoltIV.lowTemp = atoi(hold);

        holdindex = 0;
        for (int k = 20; k < 24; k++)           // highVoltage
        {
            hold[holdindex] = dataInFormated[k];
            holdindex++;
        }
        BoltIV.highVoltage = atoi(hold);

        holdindex = 0;
        for (int k = 25; k < 29; k++)           // lowVoltage
        {
            hold[holdindex] = dataInFormated[k];
            holdindex++;
        }
        BoltIV.lowVoltage = atoi(hold);

        holdindex = 0;
        for (int k = 30; k < 34; k++)           // RPM
        {
            hold[holdindex] = dataInFormated[k];
            holdindex++;
        }
        BoltIV.RPM = atoi(hold);

        holdindex = 0;
        for (int k = 35; k < 39; k++)           // motorTemp
        {
            hold[holdindex] = dataInFormated[k];
            holdindex++;
        }
        BoltIV.motorTemp = atoi(hold);

        holdindex = 0;
        for (int k = 40; k < 44; k++)           // dcBusCurrent
        {
            hold[holdindex] = dataInFormated[k];
            holdindex++;
        }
        BoltIV.dcBusCurrent = atoi(hold);

        holdindex = 0;
        for (int k = 45; k < 49; k++)           // motorTorque
        {
            hold[holdindex] = dataInFormated[k];
            holdindex++;
        }
        BoltIV.motorTorque = atoi(hold);

        holdindex = 0;
        for (int k = 50; k < 54; k++)           // motorCtrlTemp
        {
            hold[holdindex] = dataInFormated[k];
            holdindex++;
        }
        BoltIV.motorCtrlTemp = atoi(hold);

        holdindex = 0;
        for (int k = 55; k < 59; k++)           // auxVoltage
        {
            hold[holdindex] = dataInFormated[k];
            holdindex++;
        }
        BoltIV.auxVoltage = atoi(hold);

        holdindex = 0;
        for (int k = 60; k < 64; k++)           // xAcc
        {
            hold[holdindex] = dataInFormated[k];
            holdindex++;
        }
        BoltIV.xAcc = atoi(hold);

        holdindex = 0;
        for (int k = 65; k < 69; k++)           // yAcc
        {
            hold[holdindex] = dataInFormated[k];
            holdindex++;
        }
        BoltIV.yAcc = atoi(hold);

        holdindex = 0;
        for (int k = 70; k < 74; k++)           // zAcc
        {
            hold[holdindex] = dataInFormated[k];
            holdindex++;
        }
        BoltIV.zAcc = atoi(hold);

        holdindex = 0;
        for (int k = 75; k < 79; k++)           // xGyro
        {
            hold[holdindex] = dataInFormated[k];
            holdindex++;
        }
        BoltIV.xGyro = atoi(hold);

        holdindex = 0;
        for (int k = 80; k < 84; k++)           // yGyro
        {
            hold[holdindex] = dataInFormated[k];
            holdindex++;
        }
        BoltIV.yGyro = atoi(hold);

        holdindex = 0;
        for (int k = 85; k < 89; k++)           // zGyro
        {
            hold[holdindex] = dataInFormated[k];
            holdindex++;
        }
        BoltIV.zGyro = atoi(hold);

        holdindex = 0;
        for (int k = 90; k < 94; k++)           // roll
        {
            hold[holdindex] = dataInFormated[k];
            holdindex++;
        }
        BoltIV.roll = atoi(hold);

        holdindex = 0;
        for (int k = 95; k < 99; k++)           // pitch
        {
            hold[holdindex] = dataInFormated[k];
            holdindex++;
        }
        BoltIV.pitch = atoi(hold);
    }


    /* Default Constructor */
    bool CreatePort()
    {
        /* Initialize Port */
        port_handle.reset(new asio::serial_port(context));
        asio::error_code ec;
        port_handle->open("COM7", ec);

        /* Signal if Port is Open */
        if (port_handle->is_open())
            wxLogMessage("Port is Now Open");
        else
            return false;

        /* Set Port Parameters */
        port_handle->set_option(asio::serial_port::baud_rate(57600));
        port_handle->set_option(asio::serial_port_base::character_size());
        port_handle->set_option(asio::serial_port_base::stop_bits());
        port_handle->set_option(asio::serial_port_base::parity());
        port_handle->set_option(asio::serial_port_base::flow_control());

        /* Initialize Read Variables */
        dataInIndex     = 0;
        dataInRead      = false;
        startDelimiter  = 0x7e;
        endDelimiter    = 0x5e;

        /* Prime the Read Function */
        portRead();
        thrContext = std::thread([&]() {context.run(); });

        /* Return */
        return true;
    }


    /* Asynchronous Port Read Function */
    void portRead()
    {
        port_handle->async_read_some(asio::buffer(&nIncomingByte, 1),
            [this](std::error_code ec, std::size_t length)
            {
                /* If No Error */
                if (!ec)
                {
                    /* If Incomming Byte Signals Start of Data Transmission */
                    if (nIncomingByte == startDelimiter)
                        dataInRead = true;

                    /* While Reading Data */
                    if (dataInRead)
                    {
                        /* Write Incomming Byte to Data In Variable */    
                        if (!(nIncomingByte == dataIn[dataInIndex - 1] && nIncomingByte == '~'))
                        {
                            dataIn[dataInIndex] = nIncomingByte;
                            dataInIndex++;
                        }

                        /* If Incomming Byte Signals End of Data Transmission */
                        if (nIncomingByte == endDelimiter)
                        {
                            dataInRead = false;
                            dataInIndex = 0;
                        }
                    }

                    /* Prime Next Read Function */
                    portRead();
                } 
            });
    }


    /* Default Destructor */
    bool DeletePort()
    {
        if (port_handle)
        {
            port_handle->cancel();
            port_handle->close();
        }

        if (thrContext.joinable())
        {
            thrContext.join();
        }

        port_handle.reset();

        return true;
    }
};


/* Main Application Frame Class */
class MyFrame : public wxFrame
{
public:

    /* Default Constructor */
    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);

    /* Port Varible */
    portClass xBee;

    /* Display Pointers */
    wxTextCtrl* MainEditBox;

    mpWindow *m_plot, *m_plot1, * m_plot2, * m_plot3, * m_plot4, * m_plot5, * m_plot6, * m_plot7, * m_plot8, * m_plot9, * m_plot10, * m_plot11, * m_plot12, * m_plot13, * m_plot14, * m_plot15, * m_plot16, * m_plot17, * m_plot18, * m_plot19;
    mpFXYVector* vectorLayer, * vectorLayer1, *vectorLayer2, * vectorLayer3, * vectorLayer4, * vectorLayer5, * vectorLayer6, * vectorLayer7, * vectorLayer8, * vectorLayer9, * vectorLayer10, * vectorLayer11, * vectorLayer12, * vectorLayer13, * vectorLayer14, * vectorLayer15, * vectorLayer16, * vectorLayer17, * vectorLayer18, * vectorLayer19;

    wxBoxSizer* leftSizer;
    wxBoxSizer* rightSizer;

    /* Data Members Needed To Plot Bolt IV Data */
    int xAxisValue;
    BoltIVdataVectors xAxisVector;
    BoltIVdataVectors yAxisVector;

private:

    /* Call On User Event */
    void OnHello(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnViewSA(wxCommandEvent& event);
    void OnViewSO(wxCommandEvent& event);

    /* Call on Timer Event */
    void TimerCall(wxTimerEvent& event);

    /* Initialize the Event Table Used */
    wxDECLARE_EVENT_TABLE();

  
    // Delete ?
    wxPanel* p_SystemAnalysisPanel;
};