#pragma once


typedef struct
{
	COLORREF colText;
	COLORREF colTextBk;
}TEXT_BK;


// CMyListCtrl

class CMyListCtrl : public CListCtrl
{
	DECLARE_DYNAMIC(CMyListCtrl)

public:
	CMyListCtrl();
	virtual ~CMyListCtrl();

public:
	void SetItemColor(DWORD iItem, COLORREF TextColor, COLORREF TextBkColor);   //设置某一行的前景色和背景色
	void SetAllItemColor(DWORD iItem, COLORREF TextColor, COLORREF TextBkColor);//设置全部行的前景色和背景色  
	void ClearColor();                                                          //清除颜色映射表 
	CMap<DWORD, DWORD&, TEXT_BK, TEXT_BK&> MapItemColor;
protected:
	void CMyListCtrl::OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult);

protected:
	DECLARE_MESSAGE_MAP()
};


