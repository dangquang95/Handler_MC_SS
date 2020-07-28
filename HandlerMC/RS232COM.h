#pragma once

typedef void (CALLBACK *CALLBACK_FUNCTION)(int);
typedef void(*pFn232Comm)(CString);

#define		STX 		0x02
#define		DLE			0x10
#define		ETX 		0x03
#define		ACK 		0x06
#define		NAK 		0x15
#define		CR	 		0x0D
#define		LF	 		0x0A

class CRS232COM
{
public:
	CRS232COM();
	~CRS232COM();
protected:
	int m_iPort;		

public:
	pFn232Comm CallBackString = NULL;

	BOOL Initialize(int port, int baud, int data = 3, int parity = 0, int stop = 0, int mode = 0);		
	BOOL SendData(CString Data);
	BOOL SendData(char* Data, int Size);	
	BOOL CallbackFuncEndChar(pFn232Comm handler, BYTE EndChar = ETX);
	BOOL CallbackFuncCount(pFn232Comm pCallBackFunc);
	BOOL BufferClear();
	static void CALLBACK CallBackFunc(int iPort);
	BYTE m_EndChar = ' ';
	CString m_Buff;
	CString ReceivedData();
	
};

