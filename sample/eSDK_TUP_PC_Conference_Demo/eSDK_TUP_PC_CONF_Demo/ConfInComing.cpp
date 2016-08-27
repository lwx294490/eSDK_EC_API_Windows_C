// ConfInComing.cpp : implementation file
//

#include "stdafx.h"
#include "eSDK_TUP_PC_CONF_Demo.h"
#include "ConfInComing.h"
#include "afxdialogex.h"


// CConfInComing dialog

IMPLEMENT_DYNAMIC(CConfInComing, CDialog)

CConfInComing::CConfInComing(CWnd* pParent /*=NULL*/)
	: CDialog(CConfInComing::IDD, pParent)
{

	m_strNum = _T("");
	m_strName = _T("");
}

CConfInComing::~CConfInComing()
{
}

void CConfInComing::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_NAME, m_stcName);
	DDX_Control(pDX, IDC_STATIC_NUMBER, m_stcNum);
}


BEGIN_MESSAGE_MAP(CConfInComing, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_ACCEPT, &CConfInComing::OnClickedButtonAccept)
	ON_BN_CLICKED(IDC_BUTTON_REJECT, &CConfInComing::OnClickedButtonReject)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CConfInComing message handlers


void CConfInComing::OnClickedButtonAccept()
{
	// TODO: Add your control notification handler code here
	OnOK();
}


void CConfInComing::OnClickedButtonReject()
{
	// TODO: Add your control notification handler code here
	this->KillTimer(1);
	OnCancel();
}


BOOL CConfInComing::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	m_stcName.SetWindowText(m_strName);
	m_stcNum.SetWindowText(m_strNum);
	this->SetTimer( 1, 29000, NULL );
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CConfInComing::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	OnCancel();
	CDialog::OnTimer(nIDEvent);
}
