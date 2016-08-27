#pragma once


// CShareStatic

class CShareStatic : public CStatic
{
	DECLARE_DYNAMIC(CShareStatic)

public:
	CShareStatic();
	virtual ~CShareStatic();
	virtual void OnDraw(CDC* pDC);

protected:
	DECLARE_MESSAGE_MAP()

protected:
	HBITMAP m_hASBitmap;
	RECT borderRc;
public:

	void SetBitmap2(BITMAP *pBMP);
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	CONF_HANDLE m_handle;

};

