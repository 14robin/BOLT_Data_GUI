
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

    char dataIn[166];

    char nIncomingByte;
    char bytearray[256];
    int kount;

    asio::io_context context;
    std::thread thrContext;
    std::unique_ptr<asio::serial_port> portX;

    bool OnUserCreate()
    {
        kount = 0;

        portX.reset(new asio::serial_port(context));
        asio::error_code ec;
        portX->open("COM5", ec);

        if (portX->is_open())
        {
            wxLogMessage("robot port open");
        }

        portX->set_option(asio::serial_port::baud_rate(57600));
        portX->set_option(asio::serial_port_base::character_size());
        portX->set_option(asio::serial_port_base::stop_bits());
        portX->set_option(asio::serial_port_base::parity());
        portX->set_option(asio::serial_port_base::flow_control());

        aRead();
        thrContext = std::thread([&]() {context.run(); });

        return true;
    }

    void aRead()
    {
        portX->async_read_some(asio::buffer(&dataIn, 165),
            [this](std::error_code ec, std::size_t length)
            {
                if (!ec)
                {
                    wxLogMessage(dataIn);
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


    serialLate* xx;

    



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