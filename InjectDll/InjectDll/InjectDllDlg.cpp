#include "stdafx.h"
#include "InjectDll.h"
#include "InjectDllDlg.h"
#include  "InjectClass.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

InjectClass myclass1;

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CInjectDll2Dlg �Ի���




CInjectDll2Dlg::CInjectDll2Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CInjectDll2Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CInjectDll2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, M_EDIT1);
}

BEGIN_MESSAGE_MAP(CInjectDll2Dlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CInjectDll2Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CInjectDll2Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CInjectDll2Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CInjectDll2Dlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CInjectDll2Dlg ��Ϣ�������

BOOL CInjectDll2Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	CEdit* edit2 = (CEdit*)GetDlgItem(IDC_EDIT2);
	edit2->SetWindowTextW(L"���³�����ʿ");

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������


	myclass1._FreeResFile(IDR_MYIME1,L"myime",L"C:\\WINDOWS\\SYSTEM32\\Freeime.ime");
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CInjectDll2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CInjectDll2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CInjectDll2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CInjectDll2Dlg::OnBnClickedButton1()
{

	CFileDialog MYFILEDLG(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, L"li(*.dll)|*.dll|�����ļ�(*.*)|*.*|");
	int getresut=	MYFILEDLG.DoModal();
	if (getresut==IDOK)
	{
	/*
		CString CFileDialog::GetFileName( ) �õ��������ļ�����������չ���磺test.txt
		CString CFileDialog::GetExtName( ) �õ��������ļ���չ�����磺txt
		CString CFileDialog::GetFileTitle ( ) �õ��������ļ�����������Ŀ¼������չ���磺test
		POSITION CFileDialog::GetStartPosition( ) ����ѡ���˶���ļ�������õ���һ���ļ�λ�á�*/
		M_EDIT1.SetWindowText(MYFILEDLG.GetPathName());
	}
	
	
	
	
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
//
void CInjectDll2Dlg::OnBnClickedButton2()
{
	CString dllpath;
	M_EDIT1.GetWindowText(dllpath);
	if (!myclass1.ImeInstall(dllpath.GetBuffer()))
		MessageBox(L"��װʧ��");
	else
		MessageBox(L"��װ�ɹ�");

}

void CInjectDll2Dlg::OnBnClickedButton3()
{
	CEdit* edit2 = (CEdit*)GetDlgItem(IDC_EDIT2);
	CString str;
	edit2->GetWindowTextW(str);
	CWnd* myhwn;
	myhwn = FindWindow(NULL,str.GetBuffer());
	if (!myhwn) {
		MessageBox(L"�Ҳ�������");
		return;
	}
	myclass1.IMEActiv(myhwn->m_hWnd);
	
	
}

void CInjectDll2Dlg::OnBnClickedButton4()
{
	if (myclass1.ImeStop())
		MessageBox(L"ж�سɹ�");
	else
		MessageBox(L"ж��ʧ��");


	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
