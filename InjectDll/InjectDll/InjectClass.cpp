#include "stdafx.h"

#include "InjectClass.h"

InjectClass::InjectClass(void)
{
	HKL InputHandle = NULL;

	HKL oldInputHandle = NULL;
}

InjectClass::~InjectClass(void)
{
}

typedef int  (WINAPI  *g_IMEClearPubString)();

typedef int  (WINAPI  *g_IMESetPubString)(PWCHAR tmpStr,DWORD UnloadDLL,DWORD loadNextIme,DWORD DllData1,DWORD DllData2,DWORD DllData3);

void Dbg_Print(char * formatstr,...);

g_IMEClearPubString IMEClearPubString = NULL;

g_IMESetPubString IMESetPubString = NULL;

HINSTANCE hModule = NULL;

bool InjectClass::_FreeResFile(DWORD dwResName, LPCWSTR lpResType, LPCWSTR lpFilePathName)
{
	HMODULE hInstance = ::GetModuleHandle(NULL);//�õ�����ʵ�����          
	HRSRC hResID = ::FindResource(hInstance,MAKEINTRESOURCE(dwResName),lpResType);//������Դ      
	HGLOBAL hRes = ::LoadResource(hInstance,hResID);//������Դ       
	LPVOID pRes = ::LockResource(hRes);//������Դ                   
	if (pRes == NULL)//����ʧ��       
	{           return FALSE;       
	}      
	DWORD dwResSize = ::SizeofResource(hInstance,hResID);//�õ����ͷ���Դ�ļ���С       
	HANDLE hResFile = CreateFile(lpFilePathName,GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);//�����ļ�                  
	if (INVALID_HANDLE_VALUE == hResFile)     
	{           //TRACE("�����ļ�ʧ�ܣ�");          
		return FALSE;       
	}              
	DWORD dwWritten = 0;//д���ļ��Ĵ�С          
	WriteFile(hResFile,pRes,dwResSize,&dwWritten,NULL);//д���ļ�      
	CloseHandle(hResFile);//�ر��ļ����                   
	return (dwResSize == dwWritten);//��д���С�����ļ���С�����سɹ�������ʧ�� 
	//ʹ��ʾ��: FreeResFile(IDR_MYRES,"MYRES","D:\\1.exe");
}



//ģ�鹦�ܣ��ͷ���Դ��ĳ���͵��ļ�  _FreeResFile2("Test.exe",(WORD)IDR_EXE1,"EXE"))
BOOL InjectClass:: _FreeResFile2(CString strFileName,WORD wResID,CString strFileType)
{    
	// ��Դ��С    
	DWORD   dwWrite=0;  

	//��λ���ǵ��Զ�����Դ��������Ϊ�����Ǵӱ�ģ�鶨λ��Դ�����Խ�����򵥵���ΪNULL����

	HRSRC hrscr =  FindResource(NULL, MAKEINTRESOURCE(wResID),strFileType);  

	if (NULL == hrscr)
	{
		return FALSE;
	}

	//��ȡ��Դ�Ĵ�С

	DWORD dwSize = SizeofResource( NULL,hrscr); 

	//������Դ

	HGLOBAL hGlobal = LoadResource(NULL,hrscr);   

	if (NULL == hGlobal)
	{
		return FALSE;
	}

	//������Դ

	LPVOID pBuffer = LockResource(hGlobal); 

	if (NULL == pBuffer)
	{
		return FALSE;
	}

	// �����ļ�    
	HANDLE  hFile = CreateFile(
		strFileName, 
		GENERIC_READ|GENERIC_WRITE,
		FILE_SHARE_WRITE,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL
		); 

	if ( hFile == INVALID_HANDLE_VALUE )    
	{    
		return FALSE;    
	}    

	// д���ļ�    
	WriteFile(hFile,pBuffer,dwSize,&dwWrite,NULL);   

	CloseHandle( hFile ); 

	return TRUE;    
}


//���ܣ�ȡ����Ŀ¼ 
void InjectClass::GetCurDirectory(WCHAR* CurPath)
{
	GetModuleFileName (NULL,CurPath,MAX_PATH);

	for(int i=MAX_PATH-1;i>=0;i--)
	{
		if(*(CurPath+i)!='\\')
		{
			*(CurPath+i)=0;
		}
		else
		{
			break;
		}
	}
} 

//���ܣ�ö�����뷨�����ؾ��  InputName�����뷨���ƣ�FileName ���뷨�ļ���
HKL InjectClass::EnumIme(CString InputName,CString FileName)
{
	HKL *HKLList;

	HKL Imehandle;

	int StrCount=0,FileCount=0;

	HKLList = NULL;

	UINT uCount = GetKeyboardLayoutList(0, NULL);

	if (0 != uCount)
	{
		HKLList = new HKL[uCount];

		//�����ϵͳ�������ĵ�ǰ�����Ӧ�ļ��̲��־�����ú��������������ָ���Ļ�������
		GetKeyboardLayoutList(uCount, HKLList);

		TRACE("GetKeyboardLayoutList OK!!\n");
	}
	else
	{
		int nErr = GetLastError();

		TRACE("Error is %d\n", nErr);
	}

	CString strLayoutText;

	CString strFileText;

	CString InputString;

	CString InputFile;

	for (UINT i = 0; i < uCount; i++)
	{
		//ȡ�����뷨��
		StrCount = ImmGetDescription(HKLList[i], strLayoutText.GetBuffer(256), 256);

		InputString = strLayoutText.Left(StrCount);

		if (InputString == InputName)
		{
			//�õ������뷨���ļ����ƣ����������ͬ���������뷨�����
			FileCount = ImmGetIMEFileName(HKLList[i], strFileText.GetBuffer(256), 256);

			InputFile = strFileText.Left(FileCount);

			if (InputFile = FileName)
			{
				Imehandle = HKLList[i];

				break;
			}
		}	
	}
	delete[]HKLList;

	return Imehandle;
}

//���ܣ���ȡ���뷨����ַ���
void InjectClass::GetImeHandleString()
{
	//���ָ���̵߳Ļ���̲���
	HKL iHandle = GetKeyboardLayout(NULL);

	//���������뷨���̲���
	::ActivateKeyboardLayout(InputHandle,NULL);
	//��ȡ���뷨���̲���
	::GetKeyboardLayoutName(ImeSymbol);
	//����ԭ������̲���
	::ActivateKeyboardLayout (iHandle,NULL);
}

//���ܣ����뷨ע�� 
bool InjectClass::ImeInstall(LPCWSTR lpszdllName)
{

	//����ԭʼ���̲���

	::SystemParametersInfo(SPI_GETDEFAULTINPUTLANG,NULL,oldInputHandle,NULL);

	//�����ļ���Ŀ¼

	//����Ҫ����  ��Դ�Ը� CopyFile(L"Freeime.dll",L"C:\\WINDOWS\\SYSTEM32\\Freeime.ime",FALSE);

	//CopyFile(L"Gamedll.dll",L"C:\\WINDOWS\\SYSTEM32\\Gamedll.dll",FALSE);

	//�������뷨IME�ļ�,������ǰ����أ���������DLL�����������

	hModule = LoadLibrary(L"C:\\Windows\\System32\\Freeime.ime"); 
	
	//�������뷨

	InputHandle = ImmInstallIME(L"C:\\WINDOWS\\SYSTEM32\\Freeime.ime",L"��Ʒ���.12");
	
	//��ȡ���뷨��ʶ��

	GetImeHandleString();

	//�ж����뷨����Ƿ���Ч

	if (!ImmIsIME(InputHandle))
	{
		//��������ڣ�ö�����뷨���Ҿ��
		InputHandle = EnumIme(L"�Ϲ⻪��ƴ�����뷨V6.7",L"C:\\WINDOWS\\SYSTEM32\\unispim6.ime");
	}
	if (hModule)
	{
		IMESetPubString = (g_IMESetPubString)GetProcAddress(hModule, "IMESetPubString");
		if (IMESetPubString)
		{
			/*WCHAR CurPath[MAX_PATH+1] = {NULL};

			wmemset(CurPath,0,MAX_PATH+1);

			GetCurDirectory(CurPath);

			wcscat(CurPath,lpszdllName);*/

			IMESetPubString((PWCHAR)lpszdllName, 0, 0, 0, 0, 0);
		}
		else
		{
			FreeLibrary(hModule);
			return FALSE;
		}
	}
	else
	{
		return FALSE;
	}
	return TRUE;
}

//���ܣ�����ָ���������뷨
BOOL InjectClass::IMEActiv(HWND hWnd)
{

	if (InputHandle != NULL)
	{
		//����ָ���������뷨
		::PostMessage(hWnd,WM_INPUTLANGCHANGEREQUEST,0x1,(LPARAM)InputHandle);
	} 
	else
	{
		//��������ڣ�ö�����뷨���������
		HKL imehandle = EnumIme(L"��Ʒ���7.12",L"C:\\WINDOWS\\SYSTEM32\\Freeime.ime");
		if (imehandle != NULL)
		{
			::PostMessage(hWnd,WM_INPUTLANGCHANGEREQUEST,0x1,(LPARAM)imehandle);
		}
		else
		{
			return FALSE;
		}
	}
	return TRUE;
}


//���ܣ�ֹͣ���뷨
BOOL InjectClass:: ImeStop()
{
	if (hModule)
	{
		IMEClearPubString = (g_IMEClearPubString)GetProcAddress(hModule,"IMEClearPubString"); 

		if (IMEClearPubString)
		{
			IMEClearPubString();
			FreeLibrary(hModule);
		}
		else
		{
			FreeLibrary(hModule);
			return FALSE;
		}
	}
	else
	{
		return FALSE;
	}
	return TRUE;
}


//���ܣ���ԭϵͳĬ�����뷨�����ڳ����˳�ʱ��ԭ��Ĭ�ϼ��̲��ֵĸı�.Imehandle�����뷨���
void InjectClass:: QuitImeSystemDefault(HKL imehandle)
{
	HKL retV;

	::SystemParametersInfo(SPI_GETDEFAULTINPUTLANG,0,retV,0);

	if (retV != imehandle)
	{
		::SystemParametersInfo(SPI_SETDEFAULTINPUTLANG,0,imehandle,SPIF_SENDWININICHANGE);
	}
}


//���ܣ������еĶ��������м���ָ����������뷨
void InjectClass:: SetAllWindowActiv(HKL imehandle)
{
	HWND mhWnd = NULL;

	do 
	{
		mhWnd = ::FindWindowExA(NULL,mhWnd,NULL,NULL);

		if (mhWnd != NULL)
		{
			::PostMessage(mhWnd,WM_INPUTLANGCHANGEREQUEST,0x1,(LPARAM)imehandle);
		}
	} while (mhWnd == NULL);
}


//���ܣ�ж�����뷨
BOOL InjectClass:: ImeUnInstall()
{
	HKL handle;

	//�ָ�����ԭʼ����
	QuitImeSystemDefault(oldInputHandle);

	//�����ж������ڼ���ԭʼ���̲���
	SetAllWindowActiv(oldInputHandle);

	if (InputHandle != NULL)
	{
		//ж�����뷨
		UnloadKeyboardLayout(InputHandle);
	}
	else
	{
		//���������ö�����뷨���Ҿ��
		HKL imehandle = EnumIme(L"��Ʒ���7.12",L"C:\\WINDOWS\\SYSTEM32\\Freeime.ime");

		if (imehandle != NULL)
		{
			UnloadKeyboardLayout(imehandle);
		} 
		else
		{
			return FALSE;
		}
	} 

	//���뷨��ʶ�����ڣ�ɾ�����뷨ע���
	if (ImeSymbol != L"")
	{
		ImedeleteReg();
	}	

	//ж�����뷨ģ��
	FreeLibrary(hModule);

	return TRUE;
}

//���ܣ�ɾ�����뷨ע���
void InjectClass::ImedeleteReg()
{
	HKEY phkResult;

	int i = NULL;

	TCHAR ValueName[255];  //�洢�õ��ļ�ֵ��

	TCHAR lpData[255];     //�洢�õ��ļ�ֵ����

	DWORD lenValue = 255;  //�洢��ֵ�����ݳ���

	DWORD lenData = 255;   //�洢��ֵ�����ݳ���

	//��ע�����Ŀ����ȡ���
	RegOpenKey(HKEY_CURRENT_USER,L"Keyboard Layout\\Preload",&phkResult);

	//ö��ע�����Ŀ
	while(RegEnumValue (phkResult,i,ValueName,&lenValue,NULL,NULL,(LPBYTE)lpData,&lenData) != ERROR_NO_MORE_ITEMS)
	{
		//Dbg_Print("1:%ws\n",ImeSymbol);//���뷨��ʶ��

		//Dbg_Print("2:%ws\n",ValueName);//ע�����Ŀ

		//Dbg_Print("3:%ws\n",lpData);   //ע�����Ŀ��ֵ

		if (lenData != NULL)
		{
			if (_tcscmp(ImeSymbol,lpData)==NULL)
			{
				//AfxMessageBox(_T("ɾ��ע�����"));
				RegDeleteValue (phkResult,ValueName);//ɾ����Ŀ��ֵ
				break;
			}
		}

		//�����������ñ����������������Ϊ�գ������������ݲ�ȫ �磺E0200804 ��ȫΪ��0000804

		lpData[255] = NULL;

		ValueName[255] = NULL;

		lenValue = 255; 

		lenData = 255;

		i++;
	}
}


void  InjectClass::Test(CString MSG)
{
	AfxMessageBox(MSG);
}



void InjectClass:: Stop_AND_UnInstall()
{
	ImeStop();
	ImeUnInstall();
}