/*Copyright 2015 Huawei Technologies Co., Ltd. All rights reserved.
eSDK is licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at
		http://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.*/

// ConferenceDetailDlg.cpp : implementation file
//

#include "stdafx.h"
#include "eSDK_TUP_PC_CONF_Demo.h"
#include "ConferenceDetailDlg.h"
#include "afxdialogex.h"


// CConferenceDetailDlg dialog

IMPLEMENT_DYNAMIC(CConferenceDetailDlg, CDialogEx)

CConferenceDetailDlg::CConferenceDetailDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CConferenceDetailDlg::IDD, pParent)
{

	m_cstrAccessNumber = _T("");
	//  m_editAgenda = _T("");
	m_cstrChairman = _T("");
	m_cstrChairmanAccount = _T("");
	m_cstrConvenerAccount = _T("");
	m_cstrConvenerName = _T("");
	m_cstrConvenerTimeZone = _T("");
	m_cstrDuration = _T("");
	m_cstrForwarderAccount = _T("");
	m_cstrForwarderName = _T("");
	m_cstrHoldTime = _T("");
	m_cstrID = _T("");
	m_cstrIsForward = _T("");
	m_cstrMediaType = _T("");
	m_cstrMeetingRoom = _T("");
	m_cstrStart = _T("");
	m_cstrStatus = _T("");
	m_cstrTitle = _T("");
	m_cstrTranslateAccessNumber = _T("");
	m_cstrAgenda = _T("");
	m_cstrSecurityCode = _T("");
}

CConferenceDetailDlg::~CConferenceDetailDlg()
{
}

void CConferenceDetailDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ACCESSNUMER, m_cstrAccessNumber);
	DDX_Text(pDX, IDC_EDIT_CHAIRMAN, m_cstrChairman);
	DDX_Text(pDX, IDC_EDIT_CHAIRMANACCOUNT, m_cstrChairmanAccount);
	DDX_Text(pDX, IDC_EDIT_CONVENERACCOUNT, m_cstrConvenerAccount);
	DDX_Text(pDX, IDC_EDIT_CONVENERNAME, m_cstrConvenerName);
	DDX_Text(pDX, IDC_EDIT_CONVENERTIMEZONE, m_cstrConvenerTimeZone);
	DDX_Text(pDX, IDC_EDIT_DURATION, m_cstrDuration);
	DDX_Text(pDX, IDC_EDIT_FORWARDERACCOUNT, m_cstrForwarderAccount);
	DDX_Text(pDX, IDC_EDIT_FORWARDERNAME, m_cstrForwarderName);
	DDX_Text(pDX, IDC_EDIT_HOLDTIME, m_cstrHoldTime);
	DDX_Text(pDX, IDC_EDIT_ID, m_cstrID);
	DDX_Text(pDX, IDC_EDIT_ISFORWARD, m_cstrIsForward);
	DDX_Text(pDX, IDC_EDIT_MEDIATYPE, m_cstrMediaType);
	DDX_Text(pDX, IDC_EDIT_MEETINGROOM, m_cstrMeetingRoom);
	DDX_Text(pDX, IDC_EDIT_START, m_cstrStart);
	DDX_Text(pDX, IDC_EDIT_STATUS, m_cstrStatus);
	DDX_Text(pDX, IDC_EDIT_TITLE, m_cstrTitle);
	DDX_Text(pDX, IDC_EDIT_TRANSLATEACCESSNUMBER, m_cstrTranslateAccessNumber);
	DDX_Text(pDX, IDC_EDIT_AGENDA, m_cstrAgenda);
	DDX_Text(pDX, IDC_EDIT_SECURITYCODE, m_cstrSecurityCode);
}


BEGIN_MESSAGE_MAP(CConferenceDetailDlg, CDialogEx)
END_MESSAGE_MAP()