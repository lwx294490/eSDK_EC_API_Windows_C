#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "afxbutton.h"
#include "ShareStatic.h"

const int WIDTH = 505;
const int HEITH = 650;
const int DESKSHOW_WIDTH = 1350;

// CDataConfDlg dialog

class CDataConfDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDataConfDlg)

public:
	CDataConfDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDataConfDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_DATACONF };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	CListCtrl    m_listDataConfMember;
	CEdit        m_editAddAccount;
	CButton      m_btnAddAccount;
	CButton      m_btnRequestRole;
	CButton      m_btnStopShareDesktop;
	CButton      m_btnCancelConf;
	CButton      m_btnCloseConf;
	CStatic      m_pictureDesktop;
	int          m_intdlgModel;
	CShareStatic m_stcDeskTop;
	bool         m_bisPresent;
	std::string  m_PresentBindNum;
	bool		 m_bIsChairMan;
	std::string  m_ChairmainBindNum;

public:
	CStatic m_txtConfName;
	CStatic m_txtAccountName;
	virtual BOOL OnInitDialog();
protected:
	afx_msg LRESULT OnDataconfCreat(WPARAM wParam, LPARAM lParam);
private:
	CONF_HANDLE m_DataConfHandle;
	bool m_bChairmanFlag;
protected:
	afx_msg LRESULT OnDataconfJoinSuccess(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnClickedBtnRequestRole();
protected:
	afx_msg LRESULT OnDataConfUpdatePresentInfo(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnClickedBtnShareDesktop();
protected:
	afx_msg LRESULT OnDataConfAsScreenDataNotify(WPARAM wParam, LPARAM lParam);
public:
//	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
protected:
	afx_msg LRESULT OnDataConfAsStateNotify(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnDataConfAsOwnerNotify(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnClickedBtnStopShareDesktop();
protected:
	afx_msg LRESULT OnDataConfUserAdd(WPARAM wParam, LPARAM lParam);
private:
	BOOL FindColum(const CString& cstrKey, int iColnum, int& iFind);
public:
	afx_msg void OnBnClickedCancel();
protected:
	afx_msg LRESULT OnDataConfUserDel(WPARAM wParam, LPARAM lParam);
public:
	void SetCallId(TUP_UINT32 ulCallId);
private:
	TUP_UINT32 m_ulCallID;
	TUP_UINT32 m_ulConfID;
public:
	void RefreshMember(CALL_S_CONF_MEMBER* confMember, TUP_UINT32 memberCount);
	afx_msg void OnBnClickedCloseConf();
	afx_msg void OnNMRClickListConfMenber(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDelete();
	afx_msg void OnClickedBtnAddAccount();
protected:
	afx_msg LRESULT OnDataconfEnd(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnBnClickedShareDesktop();
	CButton m_btnShareDesktop;
protected:
	afx_msg LRESULT OnDataconfBeClosed(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnBnClickedAttach();
protected:
	afx_msg LRESULT OnDataConfAsOnChannel(WPARAM wParam, LPARAM lParam);
private:
	void MarkPresent(const TUP_ULONG uiPresentId);
protected:
	afx_msg LRESULT OnOnekeyToConfResult(WPARAM wParam, LPARAM lParam);
public:
	TUP_UINT32 GetCallId(void);
	void SetConfID(TUP_UINT32 ulConfId);
};
