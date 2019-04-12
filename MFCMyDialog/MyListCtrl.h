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
	void SetItemColor(DWORD iItem, COLORREF TextColor, COLORREF TextBkColor);   //����ĳһ�е�ǰ��ɫ�ͱ���ɫ
	void SetAllItemColor(DWORD iItem, COLORREF TextColor, COLORREF TextBkColor);//����ȫ���е�ǰ��ɫ�ͱ���ɫ  
	void ClearColor();                                                          //�����ɫӳ��� 
	CMap<DWORD, DWORD&, TEXT_BK, TEXT_BK&> MapItemColor;
protected:
	void CMyListCtrl::OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult);

protected:
	DECLARE_MESSAGE_MAP()
};


