#include "stdafx.h"
#include "RS232COM.h"
#include "Pcomm.h"

#pragma comment(lib,"Pcomm.lib")
CRS232COM* gCRS232COM = NULL;
BOOL CRS232COM::CallbackFuncEndChar(pFn232Comm pCallBackFunc, BYTE EndChar)
{
	if(sio_term_irq(m_iPort, CallBackFunc, EndChar) != SIO_OK) {
		return FALSE;
	}
	CallBackString = pCallBackFunc;
	m_EndChar = EndChar;
	return TRUE;

}

BOOL CRS232COM::CallbackFuncCount(pFn232Comm pCallBackFunc)
{	
	if(sio_cnt_irq(m_iPort, CallBackFunc, 1) != SIO_OK) {
		return FALSE;
	}	
	CallBackString = pCallBackFunc;
	return TRUE;
}

void CALLBACK CRS232COM::CallBackFunc(int iPort)
{
	int len = sio_iqueue(iPort);

	if((len < 0) || (len > 4096)) {
		sio_AbortRead(iPort);
		return ;
	}
	char Data[4096] = { 0, };
	int Size = sio_read(iPort, Data, len);

	CString tmp;
	tmp = Data;


	sio_AbortRead(iPort);
	if(tmp!= "") {
		if(gCRS232COM->m_EndChar == ' ') {
			gCRS232COM->m_Buff = tmp;
			if(gCRS232COM->CallBackString != NULL) {
				gCRS232COM->CallBackString(tmp);
			}
		} else {
			AfxExtractSubString(tmp, tmp, 0, gCRS232COM->m_EndChar);
			gCRS232COM->m_Buff = tmp;
			if(gCRS232COM->CallBackString != NULL) {
				gCRS232COM->CallBackString(tmp);
			}
		}

	}
	
	

	return;

}



CRS232COM::CRS232COM()
{
	gCRS232COM = this;
	
}

CRS232COM::~CRS232COM()
{
}
BOOL CRS232COM::Initialize(int port, int baud, int data, int parity, int stop, int mode)
{
	int baud_rate[9] = { B7200, B9600, B19200, B38400, B57600, B115200, B230400, B460800, B921600 };
	int data_bit[4] = { BIT_5, BIT_6, BIT_7, BIT_8 };
	int parity_mode[3] = { P_NONE, P_ODD, P_EVEN };
	int stop_bit[2] = { STOP_1, STOP_2 };
	int flow_ctrl[4] = { 0x00, 0x0C, 0x03, 0x0F };


	if(baud < 0 || baud > 8 || parity < 0 || parity > 2 || data < 0 || data > 3 || stop < 0 || stop > 1 || mode < 0 || mode > 3) {
		return FALSE;
	}

	if(sio_open(port) != SIO_OK) {
		return FALSE;
	}

	if(sio_ioctl(port, baud_rate[baud], parity_mode[parity] | data_bit[data] | stop_bit[stop]) != SIO_OK) {
		return FALSE;
	}

	// Set flow control (bit 0: CTS flow control, bit 1: RTS flow control, 
	// bit 2: Tx XON/XOFF flow control ,bit 3: Rx XON/XOFF flow control (0 = OFF, 1 = ON))
	if(sio_flowctrl(port, flow_ctrl[mode]) != SIO_OK) {
		return FALSE;
	}
	// Set timeouts for sio_write and sio_putch()
	sio_SetWriteTimeouts(port, MAXDWORD);
	// Clear Input/Output Buffer
	sio_flush(port, 2);	

	

	m_iPort = port;
	return TRUE;
}



BOOL CRS232COM::SendData(CString Data)
{	
	int len = Data.GetLength();
	char tmpbuf[4096 + 1] = { 0, };
	memcpy(tmpbuf, CT2A(Data), len);

	if(sio_write(m_iPort, tmpbuf, len)<=0){
		return FALSE;
	}
	return TRUE;
}

BOOL CRS232COM::SendData(char* Data, int Size)
{
	if(sio_write(m_iPort, Data, Size) <= 0) {
		return FALSE;
	}
	return TRUE;
}

BOOL CRS232COM::BufferClear()
{
	sio_AbortRead(m_iPort);
	sio_flush(m_iPort, 2);

	return TRUE;
}

CString CRS232COM::ReceivedData()
{
	return m_Buff;
}
