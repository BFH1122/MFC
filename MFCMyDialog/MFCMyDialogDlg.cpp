
// MFCMyDialogDlg.cpp : 实现文件
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

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CMFCMyDialogDlg 对话框



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


// CMFCMyDialogDlg 消息处理程序

BOOL CMFCMyDialogDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	//添加自定义的菜单
	m_Menu.LoadMenu(IDR_MENU1);
	SetMenu(&m_Menu);

	//控制list

	DWORD dwOldStyle = mList.GetExtendedStyle();//获取原风格,可以在添加有复选框样式的表格
	mList.SetExtendedStyle(dwOldStyle | LVS_EX_FULLROWSELECT
		| LVS_EX_GRIDLINES);//若设置复选框样式，在此添加LVS_CHECK宏
							//获取表格的宽度

	mList.ModifyStyle(WS_VSCROLL | WS_HSCROLL,0);

	CRect rc;
	mList.GetClientRect(rc);
	int nWidth = rc.Width()-20;
	//为List插入列信息
	mList.InsertColumn(0, _T("编号"), 0, nWidth / 6);
	mList.InsertColumn(1, _T("第一组"), 0, nWidth / 6);
	mList.InsertColumn(2, _T("第二组"), 0, nWidth / 6);
	mList.InsertColumn(3, _T("第三组"), 0, nWidth / 6);
	mList.InsertColumn(4, _T("第四组"), 0, nWidth / 6);
	mList.InsertColumn(5, _T("第五组"), 0, nWidth / 6);

	//首先画出直角坐标系
	//初始化的数据

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





	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCMyDialogDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}



	//画出直角坐标系
	startx = 20;
	starty = 20;
	endx = 20;
	endy = 180;
	midLength = 600;

	CClientDC dc(GetDlgItem(IDC_MySTATIC));

	//黑色画笔
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

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCMyDialogDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCMyDialogDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码

	CDialogEx::OnOK();
}


void CMFCMyDialogDlg::Onxitong()
{
	// TODO: 在此添加命令处理程序代码
	MessageBox("点击系统按钮");

}


void CMFCMyDialogDlg::OnSetting()
{
	// TODO: 在此添加命令处理程序代码
	MessageBox("点击设置按钮");
}


void CAboutDlg::OnHelps()
{
	// TODO: 在此添加命令处理程序代码
	MessageBox("点击帮助按钮1");
}


void CMFCMyDialogDlg::OnHelps()
{
	// TODO: 在此添加命令处理程序代码
	MessageBox("点击帮助按钮");
}


//点击生成按钮之后的动作
void CMFCMyDialogDlg::OnBnClickedButton1()
{

	DWORD start_time = GetTickCount();
	// TODO: 在此添加控件通知处理程序代码
	char ch1[10], ch2[10], ch3[10],tmp[10];
	int n, len;
	mList.SetRedraw(FALSE);

	//刷新列表（清空）
	mList.DeleteAllItems();
	int nIndex = combox.GetCurSel();
	combox.GetLBText(nIndex, ch2);

	GetDlgItem(IDC_EDIT1)->GetWindowText(ch1, 10);

	n = atoi(ch2);
	len = atoi(ch1);
	
	//根据需要产生随机数

	NumArrays *arr = new NumArrays();
	int **nums = (*arr).getArray(n, len);


	//插入随机数据　　
	for (int j = 0; j < len; j++) {
		_itoa_s(j + 1, ch3, 10);
		mList.InsertItem(j, _T("")); // 插入
		mList.SetItemText(j, 0, ch3);
		for (int i = 0; i<n; i++) {
			_itoa_s(nums[i][j], tmp, 10);
			mList.SetItemText(j, i + 1, tmp);
		}

		mList.SetItemColor(j, RGB(0, 0, 0),
			j % 2 == 0 ? RGB(255, 120, 120) : RGB(120, 120, 100));
	}

	mList.SetRedraw(TRUE);


	//首先画出直角坐标系
	CClientDC dc(this->GetDlgItem(IDC_MySTATIC));

	//首先使得整个区域无效。然后进行窗口的重绘
	InvalidateRect(NULL);
	UpdateWindow();


	//初始化画笔的颜色
	CPen *pens[5] = {
		new CPen(PS_SOLID, 1, RGB(120, 0, 0)),
		new CPen(PS_SOLID, 1, RGB(10, 255, 0)),
		new CPen(PS_SOLID, 1, RGB(23, 0, 255)),
		new CPen(PS_SOLID, 1, RGB(125, 125, 125)),
		new CPen(PS_SOLID, 1, RGB(255, 200, 210))
	};// PS_SOLID, 1, RGB(255, 0, 0));



	//坐标与像素的转化

	//标识像素的坐标点
	int x, y;
	//对于每一组数据
	for (int i = 0; i < n; i++) {
		//访问其中的每一个数据点。
		y = (starty + endy) / 2 - (nums[i][0] * (endy - starty) / 20);  //第一个点的坐标
		x = midLength / len + startx; //横向的单位长度
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

	string str = "产生的数据："+to_string(len)+" x "+to_string(n)+" , 耗时："+to_string(end_time - start_time)+"ms .";


	static_TEXT.SetWindowTextA(str.c_str());
}


void CMFCMyDialogDlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CMFCMyDialogDlg::OnEnChangeEdit2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

void CMFCMyDialogDlg::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	
}


void CMFCMyDialogDlg::OnCbnSelchangeCombo3()
{
	// TODO: 在此添加控件通知处理程序代码

}

//列表内容的点击事件
void CMFCMyDialogDlg::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

	MessageBox("点击列表事件");


	*pResult = 0;
}

void CMFCMyDialogDlg::OnColumnClick(NMHDR *pNMHDR, LRESULT *pResult) {
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int m_nSortCol;
	bool m_fAsc = true;

	m_nSortCol = pNMListView->iSubItem;

	MessageBox(("点击"+to_string(m_nSortCol)+"行").c_str());

}
