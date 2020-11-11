
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

    dcbSerialParams.BaudRate = CBR_9600;    // Setting BaudRate = 9600
    dcbSerialParams.ByteSize = 8;           // Setting ByteSize = 8
    dcbSerialParams.StopBits = ONESTOPBIT;  // Setting StopBits = 1
    dcbSerialParams.Parity = NOPARITY;      // Setting Parity = None

    SetCommState(hComm, &dcbSerialParams);


    /* Create an Event - Recieve Character */
    SetCommMask(hComm, EV_RXCHAR);
}





/* Read Data From Comm Handle and Print to Log Message */
void Port::Read()
{
    /* Clear RX Register */
    PurgeComm( hComm, PURGE_RXCLEAR );

    /* Wait Until Character has Been Recieved - RX buffer fills continuously? */
    DWORD dwEventMask = 0;
    WaitCommEvent(hComm, &dwEventMask, NULL);

    /* ReadFile Local Variables */
    char TempChar = '?';            //Temporary character used for reading
    char SerialBuffer[256];         //Buffer for storing Rxed Data
    DWORD NoBytesRead = 1;
    int i = 0;                      // Index of Serial Buffer

    /* Experiemental Variables */
    int index1 = 0;
    bool index1found = false;
    bool status;

    
    /* Loop Until No Longer Reading Bytes */
    while (NoBytesRead == 1)
    {
        status = ReadFile(hComm,            //Handle of the Serial port
            &TempChar,                      //Temporary character
            sizeof(TempChar),               //Size of TempChar
            &NoBytesRead,                   //Number of bytes read
            NULL);

        if (status == false)
            wxLogMessage("READ HAS FAILED");

        if (TempChar == '1' && index1found == false)
        {
            index1found = true;
            index1 = i;
        }

        SerialBuffer[i] = TempChar;// Store Tempchar into buffer
        i++;


    }

    int index = 0;

    char SerialBufferCopy[6];
    for (int k = index1; k < index1 + 6; k++)
    {
        SerialBufferCopy[index] = SerialBuffer[k];
        index++;
    }

    wxLogMessage(SerialBufferCopy);



}


/* Close Communication Port */
void Port::closePort()
{
    CloseHandle(hComm);//Closing the Serial Port
}