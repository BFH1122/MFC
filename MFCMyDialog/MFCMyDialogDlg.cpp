
// MFCMyDialogDlg.cpp : ʵ���ļ�
//


#include "stdafx.h"
#include "MFCMyDialog.h"
#include "MFCMyDialogDlg.h"
#include "afxdialogex.h"

#include "random.h"
#include "MyListCtrl.h"

#include <Windows.h>
#include <string>
#include <sstream>
#include <stdio.h>

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnHelps();
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_COMMAND(ID_HELPs, &CAboutDlg::OnHelps)
END_MESSAGE_MAP()


// CMFCMyDialogDlg �Ի���



CMFCMyDialogDlg::CMFCMyDialogDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFCMYDIALOG_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCMyDialogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, mList);
	DDX_Control(pDX, IDC_COMBO3, combox);
	DDX_Control(pDX, IDC_STATIC_TEXT, static_TEXT);
}

BEGIN_MESSAGE_MAP(CMFCMyDialogDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFCMyDialogDlg::OnBnClickedOk)
	ON_COMMAND(ID_xitong, &CMFCMyDialogDlg::Onxitong)
	ON_COMMAND(ID_Setting, &CMFCMyDialogDlg::OnSetting)
	ON_COMMAND(ID_HELPs, &CMFCMyDialogDlg::OnHelps)
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCMyDialogDlg::OnBnClickedButton1)
	ON_EN_CHANGE(IDC_EDIT1, &CMFCMyDialogDlg::OnEnChangeEdit1)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CMFCMyDialogDlg::OnLvnItemchangedList1)
	ON_CBN_SELCHANGE(IDC_COMBO3, &CMFCMyDialogDlg::OnCbnSelchangeCombo3)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &CMFCMyDialogDlg::OnNMClickList1)
	ON_NOTIFY(LVN_COLUMNCLICK,IDC_LIST1,&CMFCMyDialogDlg::OnColumnClick)
END_MESSAGE_MAP()


// CMFCMyDialogDlg ��Ϣ�������

BOOL CMFCMyDialogDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	//����Զ���Ĳ˵�
	m_Menu.LoadMenu(IDR_MENU1);
	SetMenu(&m_Menu);

	//����list

	DWORD dwOldStyle = mList.GetExtendedStyle();//��ȡԭ���,����������и�ѡ����ʽ�ı��
	mList.SetExtendedStyle(dwOldStyle | LVS_EX_FULLROWSELECT
		| LVS_EX_GRIDLINES);//�����ø�ѡ����ʽ���ڴ����LVS_CHECK��
							//��ȡ���Ŀ��

	mList.ModifyStyle(WS_VSCROLL | WS_HSCROLL,0);

	CRect rc;
	mList.GetClientRect(rc);
	int nWidth = rc.Width()-20;
	//ΪList��������Ϣ
	mList.InsertColumn(0, _T("���"), 0, nWidth / 6);
	mList.InsertColumn(1, _T("��һ��"), 0, nWidth / 6);
	mList.InsertColumn(2, _T("�ڶ���"), 0, nWidth / 6);
	mList.InsertColumn(3, _T("������"), 0, nWidth / 6);
	mList.InsertColumn(4, _T("������"), 0, nWidth / 6);
	mList.InsertColumn(5, _T("������"), 0, nWidth / 6);

	//���Ȼ���ֱ������ϵ
	//��ʼ��������

	char *items[5];// = new char[6];
	items[0] = "1";
	items[1] = "2";
	items[2] = "3";
	items[3] = "4";
	items[4] = "5";

	for (int i = 0; i < 5; i++) {
		combox.AddString(items[i]);
	}

	combox.SetCurSel(0);





	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMFCMyDialogDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMFCMyDialogDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}



	//����ֱ������ϵ
	startx = 20;
	starty = 20;
	endx = 20;
	endy = 180;
	midLength = 600;

	CClientDC dc(GetDlgItem(IDC_MySTATIC));

	//��ɫ����
	CPen pen(PS_SOLID, 1.5, RGB(0, 0, 0));
	CPen *oldPen = dc.SelectObject(&pen);

	dc.TextOutA(startx - 10, starty - 10, "10");
	dc.TextOutA(startx - 10, endy, "-10");
	dc.TextOutA(startx - 10, (starty + endy) / 2, "0");


	dc.MoveTo(startx, starty);
	dc.LineTo(endx, endy);
	dc.MoveTo(startx, (endy + starty) / 2);
	dc.LineTo(midLength, (endy + starty) / 2);
	dc.SelectObject(oldPen);


}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMFCMyDialogDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCMyDialogDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	CDialogEx::OnOK();
}


void CMFCMyDialogDlg::Onxitong()
{
	// TODO: �ڴ���������������
	MessageBox("���ϵͳ��ť");

}


void CMFCMyDialogDlg::OnSetting()
{
	// TODO: �ڴ���������������
	MessageBox("������ð�ť");
}


void CAboutDlg::OnHelps()
{
	// TODO: �ڴ���������������
	MessageBox("���������ť1");
}


void CMFCMyDialogDlg::OnHelps()
{
	// TODO: �ڴ���������������
	MessageBox("���������ť");
}


//������ɰ�ť֮��Ķ���
void CMFCMyDialogDlg::OnBnClickedButton1()
{

	DWORD start_time = GetTickCount();
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	char ch1[10], ch2[10], ch3[10],tmp[10];
	int n, len;
	mList.SetRedraw(FALSE);

	//ˢ���б���գ�
	mList.DeleteAllItems();
	int nIndex = combox.GetCurSel();
	combox.GetLBText(nIndex, ch2);

	GetDlgItem(IDC_EDIT1)->GetWindowText(ch1, 10);

	n = atoi(ch2);
	len = atoi(ch1);
	
	//������Ҫ���������

	NumArrays *arr = new NumArrays();
	int **nums = (*arr).getArray(n, len);


	//����������ݡ���
	for (int j = 0; j < len; j++) {
		_itoa_s(j + 1, ch3, 10);
		mList.InsertItem(j, _T("")); // ����
		mList.SetItemText(j, 0, ch3);
		for (int i = 0; i<n; i++) {
			_itoa_s(nums[i][j], tmp, 10);
			mList.SetItemText(j, i + 1, tmp);
		}

		mList.SetItemColor(j, RGB(0, 0, 0),
			j % 2 == 0 ? RGB(255, 120, 120) : RGB(120, 120, 100));
	}

	mList.SetRedraw(TRUE);


	//���Ȼ���ֱ������ϵ
	CClientDC dc(this->GetDlgItem(IDC_MySTATIC));

	//����ʹ������������Ч��Ȼ����д��ڵ��ػ�
	InvalidateRect(NULL);
	UpdateWindow();


	//��ʼ�����ʵ���ɫ
	CPen *pens[5] = {
		new CPen(PS_SOLID, 1, RGB(120, 0, 0)),
		new CPen(PS_SOLID, 1, RGB(10, 255, 0)),
		new CPen(PS_SOLID, 1, RGB(23, 0, 255)),
		new CPen(PS_SOLID, 1, RGB(125, 125, 125)),
		new CPen(PS_SOLID, 1, RGB(255, 200, 210))
	};// PS_SOLID, 1, RGB(255, 0, 0));



	//���������ص�ת��

	//��ʶ���ص������
	int x, y;
	//����ÿһ������
	for (int i = 0; i < n; i++) {
		//�������е�ÿһ�����ݵ㡣
		y = (starty + endy) / 2 - (nums[i][0] * (endy - starty) / 20);  //��һ���������
		x = midLength / len + startx; //����ĵ�λ����
		CPen *oldPen = dc.SelectObject(pens[i]);

		for (int j = 1; j < len; j++) {
			dc.MoveTo(x, y);
			y = 100 - (nums[i][j] * (endy - starty) / 20);
			x = startx + midLength / len * (j+1);
			dc.LineTo(x, y);
		}
		dc.SelectObject(oldPen);
	}

	DWORD end_time = GetTickCount();

	char *buf;

	string str = "���������ݣ�"+to_string(len)+" x "+to_string(n)+" , ��ʱ��"+to_string(end_time - start_time)+"ms .";


	static_TEXT.SetWindowTextA(str.c_str());
}


void CMFCMyDialogDlg::OnEnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CMFCMyDialogDlg::OnEnChangeEdit2()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}

void CMFCMyDialogDlg::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	
}


void CMFCMyDialogDlg::OnCbnSelchangeCombo3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

}

//�б����ݵĵ���¼�
void CMFCMyDialogDlg::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	MessageBox("����б��¼�");


	*pResult = 0;
}

void CMFCMyDialogDlg::OnColumnClick(NMHDR *pNMHDR, LRESULT *pResult) {
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int m_nSortCol;
	bool m_fAsc = true;

	m_nSortCol = pNMListView->iSubItem;

	MessageBox(("���"+to_string(m_nSortCol)+"��").c_str());

}
