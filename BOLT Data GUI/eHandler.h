
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












class serialLate
{
public:

    // Data Varibales for BOLT IV Data
    int SOC, FPV, highTemp, lowTemp, highVoltage, lowVoltage, RPM, motorTemp, dcBusCurrent, motorTorque, motorCtrlTemp;
    int auxVoltage, xAcc, yAcc, zAcc, xGyro, yGyro, zGyro, roll, pitch;


    char dataIn[165];
    char startDelimiter = 0x7e;
    char endDelimiter = 0x5e;
    char nIncomingByte;
    int dataInIndex;
    bool dataInRead;


    /* Other Data */
    char BoltData[256];

    asio::io_context context;
    std::thread thrContext;
    std::unique_ptr<asio::serial_port> portX;

    void parseDataIn()
    {
        for (int k = 0; k < 148; k++)
        {
            if (dataIn[k + 17] == '\0')
                BoltData[k] = '0';
            else
                BoltData[k] = dataIn[k + 17];
        }
    }

    void parseDataInArduino()
    {
        int offset = 0;
        int track = 0;

        for (int k = 0; k < 99; k++)
        {
            BoltData[k] = dataIn[k - offset + 1];
            
            track++;
            if (track == 5)
            {
                BoltData[k] = ',';
                offset++;
                track = 0;
            }
        }
    }

    void parseBoltData()
    {
        char hold[4];
        int holdindex = 0;

        holdindex = 0;
        for (int k = 0; k < 4; k++)         // SOC
        {
            hold[holdindex] = BoltData[k];
            holdindex++;
        }
        SOC = atoi(hold);

        holdindex = 0;
        for (int k = 5; k < 9; k++)         // FPV
        {
            hold[holdindex] = BoltData[k];
            holdindex++;
        }
        FPV = atoi(hold);

        holdindex = 0;
        for (int k = 10; k < 14; k++)         // highTemp
        {
            hold[holdindex] = BoltData[k];
            holdindex++;
        }
        highTemp = atoi(hold);

        holdindex = 0;
        for (int k = 15; k < 19; k++)         // lowTemp
        {
            hold[holdindex] = BoltData[k];
            holdindex++;
        }
        lowTemp = atoi(hold);

        holdindex = 0;
        for (int k = 20; k < 24; k++)         // highVoltage
        {
            hold[holdindex] = BoltData[k];
            holdindex++;
        }
        highVoltage = atoi(hold);

        holdindex = 0;
        for (int k = 25; k < 29; k++)         // lowVoltage
        {
            hold[holdindex] = BoltData[k];
            holdindex++;
        }
        lowVoltage = atoi(hold);

        holdindex = 0;
        for (int k = 30; k < 34; k++)         // RPM
        {
            hold[holdindex] = BoltData[k];
            holdindex++;
        }
        RPM = atoi(hold);

        holdindex = 0;
        for (int k = 35; k < 39; k++)         // motorTemp
        {
            hold[holdindex] = BoltData[k];
            holdindex++;
        }
        motorTemp = atoi(hold);

        holdindex = 0;
        for (int k = 40; k < 44; k++)         // dcBusCurrent
        {
            hold[holdindex] = BoltData[k];
            holdindex++;
        }
        dcBusCurrent = atoi(hold);

        holdindex = 0;
        for (int k = 45; k < 49; k++)         // motorTorque
        {
            hold[holdindex] = BoltData[k];
            holdindex++;
        }
        motorTorque = atoi(hold);

        holdindex = 0;
        for (int k = 50; k < 54; k++)         // motorCtrlTemp
        {
            hold[holdindex] = BoltData[k];
            holdindex++;
        }
        motorCtrlTemp = atoi(hold);

        holdindex = 0;
        for (int k = 55; k < 59; k++)         // auxVoltage
        {
            hold[holdindex] = BoltData[k];
            holdindex++;
        }
        auxVoltage = atoi(hold);

        holdindex = 0;
        for (int k = 60; k < 64; k++)         // xAcc
        {
            hold[holdindex] = BoltData[k];
            holdindex++;
        }
        xAcc = atoi(hold);

        holdindex = 0;
        for (int k = 65; k < 69; k++)         // yAcc
        {
            hold[holdindex] = BoltData[k];
            holdindex++;
        }
        yAcc = atoi(hold);

        holdindex = 0;
        for (int k = 70; k < 74; k++)         // zAcc
        {
            hold[holdindex] = BoltData[k];
            holdindex++;
        }
        zAcc = atoi(hold);

        holdindex = 0;
        for (int k = 75; k < 79; k++)         // xGyro
        {
            hold[holdindex] = BoltData[k];
            holdindex++;
        }
        xGyro = atoi(hold);

        holdindex = 0;
        for (int k = 80; k < 84; k++)         // yGyro
        {
            hold[holdindex] = BoltData[k];
            holdindex++;
        }
        yGyro = atoi(hold);

        holdindex = 0;
        for (int k = 85; k < 89; k++)         // zGyro
        {
            hold[holdindex] = BoltData[k];
            holdindex++;
        }
        zGyro = atoi(hold);

        holdindex = 0;
        for (int k = 90; k < 94; k++)         // roll
        {
            hold[holdindex] = BoltData[k];
            holdindex++;
        }
        roll = atoi(hold);

        holdindex = 0;
        for (int k = 95; k < 99; k++)         // pitch
        {
            hold[holdindex] = BoltData[k];
            holdindex++;
        }
        pitch = atoi(hold);
    }

    bool OnUserCreate()
    {

        portX.reset(new asio::serial_port(context));
        asio::error_code ec;
        portX->open("COM7", ec);

        if (portX->is_open())
        {
            wxLogMessage("Bolt Port Open");
        }

        portX->set_option(asio::serial_port::baud_rate(57600));
        portX->set_option(asio::serial_port_base::character_size());
        portX->set_option(asio::serial_port_base::stop_bits());
        portX->set_option(asio::serial_port_base::parity());
        portX->set_option(asio::serial_port_base::flow_control());

        

        dataInIndex = 0;
        dataInRead = false;
        aRead();
        thrContext = std::thread([&]() {context.run(); });

        return true;
    }

    void aRead()
    {
        portX->async_read_some(asio::buffer(&nIncomingByte, 1),
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

                        /* End of Data Transmission BASED on LENGTH */
                        if (nIncomingByte == endDelimiter) // 164 for xBee Data Transmission
                        {
                            dataInRead = false;
                            dataInIndex = 0;
                        }
                    }

                    /* Set Next Read Function */
                    aRead();
                } 
            });
    }

    bool OnUserDestroy()
    {
        if (portX)
        {
            portX->cancel();
            portX->close();
        }

        if (thrContext.joinable())
        {
            thrContext.join();
        }

        portX.reset();

        return true;
    }

};

class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
    wxTextCtrl* MainEditBox;


    serialLate movedUart;


    mpWindow* m_plot;
    mpFXYVector* vectorLayer;
    wxTextCtrl* m_log;

    int wxgraphindex;
    std::vector<double> XvectorwxGraph, YvectorwxGraph;

private:
    void OnHello(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnViewSA(wxCommandEvent& event);
    void OnViewSO(wxCommandEvent& event);

    void TimerCall(wxTimerEvent& event);

    //Port xBee;
    wxPanel* p_SystemAnalysisPanel;

    wxDECLARE_EVENT_TABLE();
};