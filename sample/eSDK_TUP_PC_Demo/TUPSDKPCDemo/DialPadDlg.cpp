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

// DialPadDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TUPSDKPCDemo.h"
#include "DialPadDlg.h"
#include "Tools.h"


// CDialPadDlg 对话框

IMPLEMENT_DYNAMIC(CDialPadDlg, CDialog)

CDialPadDlg::CDialPadDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDialPadDlg::IDD, pParent)
{

}

CDialPadDlg::~CDialPadDlg()
{
}

void CDialPadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDialPadDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_ONE, &CDialPadDlg::OnBnClickedButtonOne)
	ON_BN_CLICKED(IDC_BUTTON2, &CDialPadDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CDialPadDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CDialPadDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON7, &CDialPadDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CDialPadDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &CDialPadDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON10, &CDialPadDlg::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON6, &CDialPadDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON11, &CDialPadDlg::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON12, &CDialPadDlg::OnBnClickedButton12)
	ON_BN_CLICKED(IDC_BUTTON13, &CDialPadDlg::OnBnClickedButton13)
END_MESSAGE_MAP()


// CDialPadDlg 消息处理程序

void CDialPadDlg::OnBnClickedButtonOne()
{
	// TODO: 在此添加控件通知处理程序代码
	m_key =CALL_E_DTMF1;
	std::string m_strPlayFile = GetAudePath()+ "\\audio\\Key\\1.wav";
	SendDTMF(m_ulCallId,m_key,m_strPlayFile);
//	OnOK();
}

void CDialPadDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_key =CALL_E_DTMF2;
	std::string m_strPlayFile = GetAudePath() + "\\audio\\Key\\2.wav";
	SendDTMF(m_ulCallId,m_key,m_strPlayFile);
//	OnOK();
}

void CDialPadDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	m_key =CALL_E_DTMF3;
	std::string m_strPlayFile = GetAudePath() + "\\audio\\Key\\3.wav";
	SendDTMF(m_ulCallId,m_key,m_strPlayFile);
//	OnOK();
}

void CDialPadDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	m_key = CALL_E_DTMF4;
	std::string m_strPlayFile = GetAudePath() + "\\audio\\Key\\4.wav";
	SendDTMF(m_ulCallId,m_key,m_strPlayFile);
//	OnOK();
}

void CDialPadDlg::OnBnClickedButton7()
{
	// TODO: 在此添加控件通知处理程序代码
	m_key = CALL_E_DTMF5;
	std::string m_strPlayFile = GetAudePath() + "\\audio\\Key\\5.wav";
	SendDTMF(m_ulCallId,m_key,m_strPlayFile);
//	OnOK();
}

void CDialPadDlg::OnBnClickedButton8()
{
	// TODO: 在此添加控件通知处理程序代码
	m_key = CALL_E_DTMF6;
	std::string m_strPlayFile = GetAudePath() + "\\audio\\Key\\6.wav";
	SendDTMF(m_ulCallId,m_key,m_strPlayFile);
//	OnOK();
}

void CDialPadDlg::OnBnClickedButton9()
{
	// TODO: 在此添加控件通知处理程序代码
	m_key = CALL_E_DTMF7;
	std::string m_strPlayFile = GetAudePath() + "\\audio\\Key\\7.wav";
	SendDTMF(m_ulCallId,m_key,m_strPlayFile);
//	OnOK();
}

void CDialPadDlg::OnBnClickedButton10()
{
	// TODO: 在此添加控件通知处理程序代码
	m_key = CALL_E_DTMF8;
	std::string m_strPlayFile = GetAudePath() + "\\audio\\Key\\8.wav";
	SendDTMF(m_ulCallId,m_key,m_strPlayFile);
//	OnOK();
}

void CDialPadDlg::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	m_key = CALL_E_DTMF9;
	std::string m_strPlayFile = GetAudePath() + "\\audio\\Key\\9.wav";
	SendDTMF(m_ulCallId,m_key,m_strPlayFile);
//	OnOK();
}

void CDialPadDlg::OnBnClickedButton11()
{
	// TODO: 在此添加控件通知处理程序代码
	m_key = CALL_E_DTMFJIN;
	std::string m_strPlayFile = GetAudePath() + "\\audio\\Key\\Jin.wav";
	SendDTMF(m_ulCallId,m_key,m_strPlayFile);
//	OnOK();
}

void CDialPadDlg::OnBnClickedButton12()
{
	// TODO: 在此添加控件通知处理程序代码
	m_key =  CALL_E_DTMF0;
	std::string m_strPlayFile = GetAudePath() + "\\audio\\Key\\0.wav";
	SendDTMF(m_ulCallId,m_key,m_strPlayFile);
//	OnOK();
}

void CDialPadDlg::OnBnClickedButton13()
{
	// TODO: 在此添加控件通知处理程序代码
	m_key = CALL_E_DTMFSTAR;
	std::string m_strPlayFile = GetAudePath() + "\\audio\\Key\\Xin.wav";
	SendDTMF(m_ulCallId,m_key,m_strPlayFile);
//	OnOK();
}

BOOL CDialPadDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
void CDialPadDlg::SendDTMF(TUP_UINT32 callId,CALL_E_DTMF_TONE Tone ,std::string m_Tonepath)
{
	TUP_INT32 tupHandle = 0;
	(void)tup_call_send_DTMF(callId,Tone);
	(void)tup_call_media_startplay(0,m_Tonepath.c_str(),&tupHandle);
	Sleep(200);
	(void)tup_call_media_stopplay(tupHandle);

}

std::string CDialPadDlg::GetAudePath(void)
{
	CString m_strPlayFile = CTools::getCurrentPath();
	std::string strPlayFile = CTools::UNICODE2UTF(m_strPlayFile);
	return strPlayFile;

}
