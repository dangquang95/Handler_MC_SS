//______________________________________________________________________________

// [] FileName: IniFile.h
// [] History :
//		1. 2000.07.10: Created by Lee Ho Sik
//______________________________________________________________________________

#ifndef _INI_FILE_H
#define _INI_FILE_H

//______________________________________________________________________________

//const int LINE_LENGTH = 500;
#define LINE_LENGTH 500


//______________________________________________________________________________

class CIniFile
{
	
public:
	CString Path;

public:
	CIniFile();
	CIniFile(CString file_path) { Path = file_path; }
	~CIniFile();
	void SetPath(CString file_path) { Path = file_path; }
	CString GetPath() { return Path; }
	//Reading
	int ReadInt(CString strSection, CString strKey, int iDefault=0);
	CString ReadString(CString strSection, CString strKey, CString strDefault=_T(""));
	CString ReadString(CString strSection, int no, CString strDefault=_T(""));
	float ReadFloat(CString strSection, CString strKey, float fDefault=0.0f);
	double ReadDouble(CString strSection, CString strKey, double dDefault=0.0);
	int ReadHex(CString strSection, CString strKey, int iDefault=0);
	int ReadHex(CString strSection, int strKey, int iDefault);
	// Writing
	BOOL WriteInt(CString strSection, CString strKey, int iVal);
	BOOL WriteString(CString strSection, CString strKey, CString strVal);
	BOOL WriteString(CString strSection, int no, CString strVal);
	BOOL WriteFloat(CString strSection, CString strKey, float fVal);
	BOOL WriteDouble(CString strSection, CString strKey, double dVal);
	BOOL WriteHex(CString strSection, CString strKey, int iVal);	
	
};

//______________________________________________________________________________

#endif
