
#include "portCommuniction.h"



/* Setup Comm Port Handle */
Port::Port()
{
    /* Initialize Communication Port */
    LPCWSTR a = L"COM7";
    hComm = CreateFile(a, GENERIC_READ, 0, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);


    /* Check if Port is Open */
    if (hComm == INVALID_HANDLE_VALUE)
        wxLogMessage("Error in opening serial port");
    else
        wxLogMessage("opening serial port successful");


    /* Initialize DCB Structure */
    DCB dcbSerialParams = { 0 };
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

    GetCommState(hComm, &dcbSerialParams);

    dcbSerialParams.BaudRate = CBR_57600;    // Setting BaudRate = 9600
    dcbSerialParams.ByteSize = 8;           // Setting ByteSize = 8
    dcbSerialParams.StopBits = ONESTOPBIT;  // Setting StopBits = 1
    dcbSerialParams.Parity = NOPARITY;      // Setting Parity = None

    SetCommState(hComm, &dcbSerialParams);

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

    char parsedData[7];
    for (int k = 0; k < 6; k++)
        parsedData[k] = CollectiveDB[k];

    parsedData[6] = '\0';

    wxLogMessage(parsedData);

    PurgeComm(hComm, PURGE_RXCLEAR);

}


/* Close Communication Port */
void Port::closePort()
{
    CloseHandle(hComm);//Closing the Serial Port
}