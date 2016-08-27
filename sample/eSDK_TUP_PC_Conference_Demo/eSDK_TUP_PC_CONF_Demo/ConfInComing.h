#pragma once


// CConfInComing dialog

class CConfInComing : public CDialog
{
	DECLARE_DYNAMIC(CConfInComing)

public:
	CConfInComing(CWnd* pParent = NULL);   // standard constructor
	virtual ~CConfInComing();

// Dialog Data
	enum { IDD = IDD_DIALOG_INCOMING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString m_strNum;
	CString m_strName;
	CStatic m_stcName;
	CStatic m_stcNum;
	afx_msg void OnClickedButtonAccept();
	afx_msg void OnClickedButtonReject();
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
