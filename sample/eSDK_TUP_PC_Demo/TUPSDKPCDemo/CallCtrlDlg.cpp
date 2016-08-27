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

// CallCtrlDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TUPSDKPCDemo.h"
#include "CallCtrlDlg.h"
#include "IMDlg.h"
#include "TransDlg.h"
#include "Tools.h"
#include "LevelDlg.h"
#include "DialPadDlg.h"


// CCallCtrlDlg 对话框

IMPLEMENT_DYNAMIC(CCallCtrlDlg, CDialog)

CCallCtrlDlg::CCallCtrlDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCallCtrlDlg::IDD, pParent)
	, m_state(NO_CALL)
	, m_pLevelDlg(NULL)
	, m_RecordPath("")
{
	m_strPath = CTools::getCurrentPath();
}

CCallCtrlDlg::~CCallCtrlDlg()
{
}

void CCallCtrlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_CALLSTATE, m_stcCalling);
	DDX_Control(pDX, IDC_BUTTON_HANGUP, m_btnHangup);
	DDX_Control(pDX, IDC_BUTTON2, m_btnHold);
	DDX_Control(pDX, IDC_BUTTON_MIC, m_btnMic);
	DDX_Control(pDX, IDC_BUTTON_SPK, m_btnSpk);
	DDX_Control(pDX, IDC_BUTTON_REC, m_btnRec);
	DDX_Control(pDX, IDC_BUTTON_TRAN, m_btnTrans);
	DDX_Control(pDX, IDC_STATIC_NET_LEVEL, m_imgStcNetLevel);
	DDX_Control(pDX, IDC_STATIC_NET_ERROR, m_stcErrInfo);
}


BEGIN_MESSAGE_MAP(CCallCtrlDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_HANGUP, &CCallCtrlDlg::OnBnClickedButtonHangup)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON2, &CCallCtrlDlg::OnBnClickedButtonHold)
	ON_BN_CLICKED(IDC_BUTTON_MIC, &CCallCtrlDlg::OnBnClickedButtonMic)
	ON_BN_CLICKED(IDC_BUTTON_SPK, &CCallCtrlDlg::OnBnClickedButtonSpk)
	ON_BN_CLICKED(IDC_BUTTON_REC, &CCallCtrlDlg::OnBnClickedButtonRec)
	ON_BN_CLICKED(IDC_BUTTON_TRAN, &CCallCtrlDlg::OnBnClickedButtonTran)
	ON_NOTIFY(BCN_HOTITEMCHANGE, IDC_BUTTON_MIC, &CCallCtrlDlg::OnBnHotItemChangeButtonMic)
	ON_BN_CLICKED(IDC_BUTTON1, &CCallCtrlDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CCallCtrlDlg 消息处理程序

BOOL CCallCtrlDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	if(NULL == m_pLevelDlg)
	{
		m_pLevelDlg = new CLevelDlg;
	}
	if(!::IsWindow(m_pLevelDlg->GetSafeHwnd()))
	{
		m_pLevelDlg->Create(CLevelDlg::IDD,this);
	}

	CString strImage = m_strPath;
	strImage += _T("\\image\\NetLevel\\0.png");
	m_imgStcNetLevel.SetImageFile(strImage);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CCallCtrlDlg::SetCallState(int istate)
{
	m_btnHangup.SetWindowText(L"挂断");

	m_state = istate;
	switch (m_state)
	{
	case NO_CALL:
		ShowWindow(SW_HIDE);
		break;
	case CALLING:
		m_stcCalling.SetWindowText(L"正在呼叫...");
		m_btnHold.ShowWindow(SW_HIDE);
		m_btnMic.ShowWindow(SW_HIDE);
		m_btnSpk.ShowWindow(SW_HIDE);
		m_btnRec.ShowWindow(SW_HIDE);
		m_btnTrans.ShowWindow(SW_HIDE);
		m_imgStcNetLevel.ShowWindow(SW_HIDE);
		m_stcErrInfo.ShowWindow(SW_HIDE);
		ShowWindow(SW_SHOW);
		break;
	case CALL_CONNECTED:	
		m_stcCalling.ShowWindow(SW_HIDE);
		m_btnHold.ShowWindow(SW_SHOW);
		m_btnMic.ShowWindow(SW_SHOW);
		m_btnSpk.ShowWindow(SW_SHOW);
		m_btnRec.ShowWindow(SW_SHOW);
		m_btnTrans.ShowWindow(SW_SHOW);
		m_imgStcNetLevel.ShowWindow(SW_SHOW);
		m_stcErrInfo.ShowWindow(SW_SHOW);
		break;
	}

}

void CCallCtrlDlg::OnBnClickedButtonHangup()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_state == CALLING || m_state == CALL_CONNECTED)
	{
		CIMDlg* pDlg = (CIMDlg*)this->GetParent()->GetParent();
		if(NULL != pDlg)
		{	
			pDlg->PostMessage(WM_HANGUP,NULL,NULL);
			pDlg->PubSelfStatus(IM_E_STATUS_ONLINE);
		}
	}

	ReshCallCtrlWindow();
}

void CCallCtrlDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialog::OnTimer(nIDEvent);
}

void CCallCtrlDlg::OnBnClickedButtonHold()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_state == CALL_CONNECTED)
	{
		CIMDlg* pDlg = (CIMDlg*)this->GetParent()->GetParent();
		
		CString cstrHold;
		m_btnHold.GetWindowText(cstrHold);

		if(cstrHold == L"呼叫保持")
		{
			if(NULL != pDlg)
			{
				pDlg->SendMessage(WM_CAll_HOLD,NULL,NULL);
			}
		}
		else		
		{
			if(NULL != pDlg)
			{
				pDlg->SendMessage(WM_CAll_UNHOLD,NULL,NULL);
			}
		}
	}


}

void CCallCtrlDlg::OnBnClickedButtonMic()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_state != CALL_CONNECTED)
	{
		return;
	}
	CIMDlg* pDlg = (CIMDlg*)this->GetParent()->GetParent();
	if(NULL == pDlg)
	{
		return;
	}
	CString cstrMic;
	m_btnMic.GetWindowText(cstrMic);
	if(cstrMic == L"麦克风静音")
	{
		LRESULT lRet = pDlg->SendMessage(WM_CALL_MIC_MUTE,NULL,NULL);
		m_btnMic.SetWindowText(L"取消静音");
		tup_call_media_mute_mic(pDlg->GetCallid(),TUP_TRUE);
		
	}
	else
	{
		LRESULT lRet = pDlg->SendMessage(WM_CALL_MIC_UNMUTE,NULL,NULL);
		m_btnMic.SetWindowText(L"麦克风静音");
		tup_call_media_mute_mic(pDlg->GetCallid(),TUP_FALSE);
	}
}

void CCallCtrlDlg::OnBnClickedButtonSpk()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_state != CALL_CONNECTED)
	{
		return;
	}
	CIMDlg* pDlg = (CIMDlg*)this->GetParent()->GetParent();
	if(NULL == pDlg)
	{
		return;
	}
	CString cstrSpk;
	m_btnSpk.GetWindowText(cstrSpk);
	if(cstrSpk == L"扬声器静音")
	{
		LRESULT lRet = pDlg->SendMessage(WM_CALL_SPK_MUTE,NULL,NULL);
		m_btnSpk.SetWindowText(L"取消静音");
		tup_call_media_mute_speak(pDlg->GetCallid(),TUP_TRUE);

	}
	else
	{
		LRESULT lRet = pDlg->SendMessage(WM_CALL_SPK_UNMUTE,NULL,NULL);
		m_btnSpk.SetWindowText(L"扬声器静音");
		tup_call_media_mute_speak(pDlg->GetCallid(),TUP_FALSE);
	}
}

void CCallCtrlDlg::OnBnClickedButtonRec()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_state != CALL_CONNECTED)
	{
		return;
	}
	CIMDlg* pDlg = (CIMDlg*)this->GetParent()->GetParent();
	if(NULL == pDlg)
	{
		return;
	}
	CString cstrRec;
	pDlg->m_btnVideoCall.GetWindowText(cstrRec);
	///////检测是不是视频通话//////
	TUP_BOOL m_IsVideoCall = TUP_TRUE;
	if (L"视频降级" != cstrRec)
	{
		m_IsVideoCall = TUP_FALSE;
	}

	m_btnRec.GetWindowText(cstrRec);
	if(cstrRec == L"开始录制")
	{
		///////获取录音文件夹////////
		m_RecordPath = CTools::UNICODE2UTF(CTools::getCurrentPath()) + "\\RecordFile";
		CTime cur = CTime::GetCurrentTime();
		if (m_IsVideoCall)
		{
			m_RecordPath.append("\\"+CTools::num2str(cur.GetTime())+".avi");
		}
		else
		{
			m_RecordPath.append("\\"+CTools::num2str(cur.GetTime())+".wav");

		}

		m_btnRec.SetWindowText(L"停止录制");
		tup_call_media_startrecord(pDlg->GetCallid(),m_RecordPath.c_str(),m_IsVideoCall);
	}
	else
	{
		m_btnRec.SetWindowText(L"开始录制");
		tup_call_media_stoprecord(pDlg->GetCallid());
		CString m_filePath = CTools::UTF2UNICODE(m_RecordPath);
		m_filePath = _T("录制文件存放在") + m_filePath;
		AfxMessageBox(m_filePath);
	}
}

void CCallCtrlDlg::OnBnClickedButtonTran()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_state != CALL_CONNECTED)
	{
		return;
	}
	CIMDlg* pDlg = (CIMDlg*)this->GetParent()->GetParent();
	if(NULL == pDlg)
	{
		return;
	}

	CTransDlg dlg(pDlg);
	if(IDOK == dlg.DoModal())
	{
		std::string strNum = CTools::UNICODE2UTF( dlg.m_cstrTransNUM);
		pDlg->SendMessage(WM_CALL_BLIND_TRAN,(WPARAM)(strNum.c_str()),NULL);
	}
	
}

void CCallCtrlDlg::OnBnHotItemChangeButtonMic(NMHDR *pNMHDR, LRESULT *pResult)
{
	// 此功能要求 Internet Explorer 6 或更高版本。
	// 符号 _WIN32_IE 必须是 >= 0x0600。
	LPNMBCHOTITEM pHotItem = reinterpret_cast<LPNMBCHOTITEM>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	//CIMDlg* pDlg = (CIMDlg*)this->GetParent()->GetParent();
	//if(NULL == pDlg)
	//{
	//	return;
	//}

	//CPoint pt;
	//GetCursorPos(&pt);
	//CRect rc;
	//pDlg->GetClientRect(&rc);

	//rc.MoveToXY(pt);
	//m_pLevelDlg->MoveWindow(&rc,TRUE);
	//if( pHotItem->dwFlags & HICF_ENTERING )
	//{
	//	m_pLevelDlg->ShowWindow(SW_HIDE);
	//}
	//else
	//{
	//	m_pLevelDlg->ShowWindow(SW_SHOW);
	//}

	*pResult = 0;
}
void CCallCtrlDlg::SetNetInfoLevel(TUP_UINT32 level,TUP_UINT32 errorinfo)
{
	m_stcErrInfo.ShowWindow(SW_HIDE);
	m_imgStcNetLevel.ShowWindow(SW_HIDE);

	m_NetLevel = level;
	m_NetErrorInfo = errorinfo;

	CString strImage = m_strPath;
	
	if(m_NetErrorInfo == 0)
	{
		m_stcErrInfo.SetWindowText(L"收发正常");
		if(m_NetLevel == 0)
		{
			strImage += _T("\\image\\NetLevel\\0.png");
		}
		else if(m_NetLevel == 1)
		{
			strImage += _T("\\image\\NetLevel\\1.png");
		}
		else if(m_NetLevel == 2)
		{
			strImage += _T("\\image\\NetLevel\\2.png");
		}
		else if(m_NetLevel == 3)
		{
			strImage += _T("\\image\\NetLevel\\3.png");
		}
		else
		{
			strImage += _T("\\image\\NetLevel\\4.png");
		}
	}
	else
	{
		strImage += _T("\\image\\NetLevel\\0.png");
		if(m_NetErrorInfo == 1)
		{
			m_stcErrInfo.SetWindowText(L"发端错误");

		}
		else if(m_NetErrorInfo == 2)
		{
			m_stcErrInfo.SetWindowText(L"收端错误");

		}
		else
		{
			m_stcErrInfo.SetWindowText(L"收发错误");

		}
	}

	m_imgStcNetLevel.SetImageFile(strImage);

	m_stcErrInfo.ShowWindow(SW_SHOW);
	m_imgStcNetLevel.ShowWindow(SW_SHOW);


}

void CCallCtrlDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CIMDlg* pDlg = (CIMDlg*)this->GetParent()->GetParent();
	if(NULL == pDlg)
	{
		return;
	}
	CDialPadDlg dlg;
	dlg.SetCallId(pDlg->GetCallid());
	dlg.DoModal();
}

void CCallCtrlDlg::ReshCallCtrlWindow()
{
	/////刷新CallCtrl窗口//////
	GetDlgItem(IDC_BUTTON1)->SetWindowText(L"二次拨号");
	GetDlgItem(IDC_BUTTON1)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_HANGUP)->SetWindowText(L"挂断");
	GetDlgItem(IDC_BUTTON_HANGUP)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON2)->SetWindowText(L"呼叫保持");
	GetDlgItem(IDC_BUTTON2)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_MIC)->SetWindowText(L"麦克风静音");
	GetDlgItem(IDC_BUTTON_MIC)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_SPK)->SetWindowText(L"扬声器静音");
	GetDlgItem(IDC_BUTTON_SPK)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_REC)->SetWindowText(L"开始录制");
	GetDlgItem(IDC_BUTTON_REC)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_TRAN)->SetWindowText(L"转移");
	GetDlgItem(IDC_BUTTON_TRAN)->EnableWindow(TRUE);
}