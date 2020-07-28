#ifndef _SERIAL_CTRL_H
#define _SERIAL_CTRL_H

/**************************************************************************/
/* Title: CSerialIO: a useful and simple serial control                   */
/* Author: wufengkai                                                      */
/* Email:  tojine@hotmail.com                                             */

class SerialCtrl
{
private:	
	BOOL m_portStatus;
	HANDLE m_portHandle;                  
	DCB m_portConfig;   
public:	
	SerialCtrl(void);
	~SerialCtrl(void);             
	void SetPortStatus(BOOL bOnOff);
	BOOL GetPortStatus(void);
	HANDLE GetPortHandle(void);
	BOOL OpenPort(DCB dcb, const char * portName="COM1");
	BOOL OpenPort(const char * baudRate="115200", const char * portName="COM1");
	BOOL Read(char * inputData, const unsigned int & sizeBuffer, unsigned long & length);
	BOOL Write(const char *outputData, const unsigned int & sizeBuffer, unsigned long & length);
	BOOL ClosePort(void);
};
#endif