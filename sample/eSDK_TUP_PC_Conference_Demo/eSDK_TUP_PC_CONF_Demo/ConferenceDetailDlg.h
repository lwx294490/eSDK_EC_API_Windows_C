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

#pragma once


// CConferenceDetailDlg dialog

class CConferenceDetailDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CConferenceDetailDlg)

public:
	CConferenceDetailDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CConferenceDetailDlg();

// Dialog Data
	enum { IDD = IDD_CONFERENCEDETAILDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString m_cstrAccessNumber;
	CString m_cstrChairman;
	CString m_cstrChairmanAccount;
	CString m_cstrConvenerAccount;
	CString m_cstrConvenerName;
	CString m_cstrConvenerTimeZone;
	CString m_cstrDuration;
	CString m_cstrForwarderAccount;
	CString m_cstrForwarderName;
	CString m_cstrHoldTime;
	CString m_cstrID;
	CString m_cstrIsForward;
	CString m_cstrMediaType;
	CString m_cstrMeetingRoom;
	CString m_cstrStart;
	CString m_cstrStatus;
	CString m_cstrTitle;
	CString m_cstrTranslateAccessNumber;
	CString m_cstrAgenda;
	CString m_cstrSecurityCode;
};
