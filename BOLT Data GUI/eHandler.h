
/* Includes */
#pragma once
#include "framework.h"
#include <wx/stattext.h>
#include <wx/panel.h>
#include <windows.h>
#include <stdio.h>
#include "portCommuniction.h"
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

    char dataIn[165];
    char startDelimiter = 0x7e;
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


    bool OnUserCreate()
    {

        portX.reset(new asio::serial_port(context));
        asio::error_code ec;
        portX->open("COM5", ec);

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
                        dataIn[dataInIndex] = nIncomingByte;
                        dataInIndex++;

                        /* End of Data Transmission BASED on LENGTH */
                        if (dataInIndex > 164)
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