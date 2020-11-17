
#include "portCommuniction.h"



/* Setup Comm Port Handle */
Port::Port()
{
    /* Initialize Communication Port */
    LPCWSTR a = L"COM5";
    hComm = CreateFile(a, GENERIC_READ, 0, NULL, CREATE_NEW, FILE_FLAG_OVERLAPPED, NULL);


    /* Check if Port is Open */
    if (hComm == INVALID_HANDLE_VALUE)
        wxLogMessage(" Error - Could Not Open Serial Port ");
    else
        wxLogMessage(" Opened Serial Port Successful ");


    /* Device Control Block - Make Sure Desktop Application and xBee are Using the same Parameters */
    DCB dcbSerialParams = { 0 };
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

    GetCommState(hComm, &dcbSerialParams); // Get Comm State Reason

    dcbSerialParams.BaudRate = CBR_57600;   // Setting BaudRate = 9600
    dcbSerialParams.ByteSize = 8;           // Setting ByteSize = 8
    dcbSerialParams.StopBits = ONESTOPBIT;  // Setting StopBits = 1
    dcbSerialParams.Parity = NOPARITY;      // Setting Parity = None

    SetCommState(hComm, &dcbSerialParams); // Set Comm State Reason

    COMMTIMEOUTS timeouts = { 0 };
    timeouts.ReadIntervalTimeout = 50; // in milliseconds
    timeouts.ReadTotalTimeoutConstant = 40; // in milliseconds
    timeouts.ReadTotalTimeoutMultiplier = 10; // in milliseconds


    /* Create an Event - Recieve Character */
    SetCommMask(hComm, EV_RXCHAR);
}





/* Read Data From Comm Handle and Print to Log Message */
void Port::Read()
{
    /* Clear RX Register */
    //PurgeComm(hComm, PURGE_RXCLEAR);

    /* Wait Until Character has Been Recieved - RX buffer fills continuously? */
    DWORD dwEventMask = 0;
    WaitCommEvent(hComm, &dwEventMask, NULL);

    /* ReadFile Local Variables */
    char CollectiveDB[256];                   // Should be big enough to hold entire incomiing data
    char SingleDB = ' ';
    DWORD BytesRead = 1;
    int indexDB = 0;

    //for (int k = 0; k < 256; k++)
    //    CollectiveDB[k] = 'k';

    while (BytesRead > 0)
    {
        ReadFile(hComm,            //Handle of the Serial port
            &SingleDB,                      //Temporary character
            sizeof(SingleDB),               //Size of TempChar
            &BytesRead,                   //Number of bytes read
            NULL);

        CollectiveDB[indexDB] = SingleDB;
        indexDB++;

    }

    for (int k = 0; k < 6; k++)
        parsedData[k] = CollectiveDB[k];

    parsedData[6] = '\0';

    //wxLogMessage(parsedData);

    PurgeComm(hComm, PURGE_RXCLEAR);

















    //DWORD bytes_read;
    //// flip between waiting on read and waiting on status events
    //BOOL wait_on_read = FALSE;    // waiting on read
    //BOOL wait_on_status = FALSE;  // waiting on line status events
    //OVERLAPPED overlapped_reader = { 0 };  // overlapped structure for read operations
    //OVERLAPPED overlapped_status = { 0 };  // overlapped structure for status operations
    //HANDLE event_array[2];  // list of events that WaitForxxx functions wait on
    //char read_buffer[READ_BUFFER_SIZE];  // temp storage of read data
    //DWORD comms_event; // result from WaitCommEvent

    //// Create the overlapped event. Must be closed before exiting
    //// to avoid a handle leak.
    //overlapped_reader.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
    //if (overlapped_reader.hEvent == NULL)
    //{
    //    on_error("Error creating reader overlapped event");
    //    return;
    //}
    //overlapped_status.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
    //if (overlapped_status.hEvent == NULL)
    //{
    //    on_error("Error creating status overlapped event");
    //    return;
    //}
    //// array of handles to wait for signals - we wait on read and status events
    //event_array[0] = overlapped_reader.hEvent;
    //event_array[1] = overlapped_status.hEvent;

    //// keep thread running until shutting down flag set
    //while (!closing_port_) {
    //    if (!is_open())
    //        std::this_thread::sleep_for(std::chrono::seconds(1));
    //    else {

    //        if (!wait_on_read) {
    //            // issue read operation
    //            if (!ReadFile(pimpl_->handle_, read_buffer, READ_BUFFER_SIZE, &bytes_read, &overlapped_reader)) {
    //                if (GetLastError() != ERROR_IO_PENDING) { // read not delayed
    //                    on_error(system_error());
    //                    break;
    //                }
    //                else
    //                    wait_on_read = TRUE;
    //            }
    //            else {
    //                on_read(read_buffer, bytes_read);
    //            }
    //        }

    //        // if no status check is outstanding, then issue another one
    //        if (!wait_on_status) {
    //            if (!WaitCommEvent(pimpl_->handle_, &comms_event, &overlapped_status)) {
    //                if (GetLastError() == ERROR_IO_PENDING) {
    //                    wait_on_status = TRUE;  // have to wait for status event
    //                }
    //                else {
    //                    on_error(create_error_msg("WaitCommEvent error "));
    //                }
    //            }
    //            else {
    //                // WaitCommEvent returned immediately
    //                update_error_states(comms_event);
    //            }
    //        }

    //        // wait for pending operations to complete
    //        if (wait_on_status || wait_on_read) {
    //            DWORD wait_result = WaitForMultipleObjects(2, event_array, FALSE, OVERLAPPED_CHECK_TIMEOUT);
    //            switch (wait_result)
    //            {
    //                // read completed
    //            case WAIT_OBJECT_0:
    //                if (!GetOverlappedResult(pimpl_->handle_, &overlapped_reader, &bytes_read, FALSE)) {
    //                    if (GetLastError() == ERROR_OPERATION_ABORTED) {
    //                        on_error("Read aborted");
    //                        wait_on_read = FALSE;
    //                    }
    //                    else {
    //                        on_error(create_error_msg("GetOverlappedResult (in reader_thread_func) error "));
    //                    }
    //                }
    //                else {
    //                    // read completed successfully
    //                    if (bytes_read) {
    //                        on_read(read_buffer, bytes_read);
    //                    }
    //                }

    //                wait_on_read = FALSE;

    //                break;

    //                // status completed
    //            case WAIT_OBJECT_0 + 1:
    //            {
    //                DWORD overlapped_result;
    //                if (!GetOverlappedResult(pimpl_->handle_, &overlapped_status, &overlapped_result, FALSE)) {
    //                    if (GetLastError() == ERROR_OPERATION_ABORTED) {
    //                        on_error("WaitCommEvent aborted");
    //                    }
    //                    else {
    //                        on_error(create_error_msg("GetOverlappedResult for status wait returned "));
    //                    }
    //                }
    //                else {
    //                    // status check completed successfully
    //                    update_error_states(comms_event);
    //                    update_pin_states();
    //                }

    //                wait_on_status = FALSE;
    //            }
    //            break;
    //            case WAIT_TIMEOUT:
    //                update_pin_states();  // periodically update pin states if changed
    //                break;

    //            default:
    //                break;
    //            }
    //        }
    //    }
    //}
    //// close reader event handle - otherwise will get resource leak
    //CloseHandle(overlapped_reader.hEvent);






}


/* Close Communication Port */
void Port::closePort()
{
    wxLogMessage("serial port Cloesed");
    CloseHandle(hComm);//Closing the Serial Port
}