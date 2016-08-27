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

// MediaSetDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TUPSDKPCDemo.h"
#include "MediaSetDlg.h"
#include "Tools.h"
#include "VideoPreviewDlg.h"


// CMediaSetDlg �Ի���

IMPLEMENT_DYNAMIC(CMediaSetDlg, CDialog)

CMediaSetDlg::CMediaSetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMediaSetDlg::IDD, pParent)
{
	m_lSpeakerPlayHandle = 0;
	m_IsSPKon = false;
	m_IsMicOn = false;

}

CMediaSetDlg::~CMediaSetDlg()
{
	/////�رնԻ���ʱ��Ҫ�����Թ����Ƿ�λ//////

	//1.0��Ƶ������Լ��//////
	if (m_IsMicOn)
	{
		//ֹͣ������˷�
		//<1>��ʱ����ֹͣ
		(void)KillTimer(TEST_MIC_TIMEID);
		//<4>    
		(void)tup_call_close_audio_preview();
		m_IsMicOn = false;
	}
	//2.0��Ƶ������//////
	if (m_IsSPKon )
	{
		(void)tup_call_media_stopplay(m_lSpeakerPlayHandle);
		m_lSpeakerPlayHandle = 0;
		m_IsSPKon = false;
	}
	//3.0�����Ƶ��ť/////
	//��Ƶ����Ҫ��飬��Ϊ��Ƶ���رգ��������Ҳ�رղ���////
}

void CMediaSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_INDEVICE, m_cbxInputDevice);
	DDX_Control(pDX, IDC_COMBO_OUTDEVICE, m_cbxOutputDevice);
	DDX_Control(pDX, IDC_COMBO_VIDEODEVICE, m_cbxVideoDevice);
	DDX_Control(pDX, IDC_SLIDER2, m_sldMicLevel);
	DDX_Control(pDX, IDC_SLIDER1, m_sldSpkLevel);
	DDX_Control(pDX, IDC_PROGRESS1, m_prsInDevice);
}


BEGIN_MESSAGE_MAP(CMediaSetDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON3, &CMediaSetDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BT_AUD_INPUT, &CMediaSetDlg::OnBnClickedBtAudInput)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BT_AUD_OUPUT, &CMediaSetDlg::OnBnClickedBtAudOuput)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER2, &CMediaSetDlg::OnNMReleasedcaptureSlider2)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER1, &CMediaSetDlg::OnNMReleasedcaptureSlider1)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CMediaSetDlg ��Ϣ�������

BOOL CMediaSetDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	m_sldSpkLevel.SetRange(0,100);
	m_sldMicLevel.SetRange(0,100);

	GetMediaDeviceList();
	RefreshControl();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
void CMediaSetDlg::GetMediaDeviceList()
{
	g_mapInDevice.clear();
	g_mapOutDevice.clear();
	g_mapVideoDevice.clear();
	g_iIndeviceIndex = -1;
	g_iOutdeviceIndex = -1;
	g_iVideodeviceIndex = -1;
	g_iMicLevel = -1;
	g_iSpeakerLevel = -1;

	TUP_UINT32 uiSize = 10;

	CALL_S_DEVICEINFO* pstDevice = new CALL_S_DEVICEINFO[uiSize];
	TUP_RESULT tRet = tup_call_media_get_devices(&uiSize,pstDevice,CALL_E_CALL_DEVICE_MIC);
	if(tRet == TUP_FAIL)
	{
		AfxMessageBox(L"tup_call_media_get_devices Failed.");
	}
	for(TUP_UINT32 i=0;i<uiSize;i++)
	{
		g_mapInDevice[pstDevice[i].ulIndex] = pstDevice[i].strName;
	}
	delete[] pstDevice;
	pstDevice = NULL;

	TUP_UINT32 uiLevel = 0;
	tRet = tup_call_media_get_speak_volume(&uiLevel);
	if(tRet == TUP_FAIL)
	{
		AfxMessageBox(L"tup_call_media_get_speak_volume Failed.");
	}
	g_iSpeakerLevel = uiLevel;

	uiSize = 10;
	pstDevice = new CALL_S_DEVICEINFO[uiSize];
	tRet = tup_call_media_get_devices(&uiSize,pstDevice,CALL_E_CALL_DEVICE_SPEAK);
	if(tRet == TUP_FAIL)
	{
		AfxMessageBox(L"tup_call_media_get_devices Failed.");
	}
	for(TUP_UINT32 i=0;i<uiSize;i++)
	{
		g_mapOutDevice[pstDevice[i].ulIndex] = pstDevice[i].strName;
	}
	delete[] pstDevice;
	pstDevice = NULL;

	uiLevel = 0;
	tRet = tup_call_media_get_mic_volume(&uiLevel);
	if(tRet == TUP_FAIL)
	{
		AfxMessageBox(L"tup_call_media_get_speak_volume Failed.");
	}
	g_iMicLevel = uiLevel;

	uiSize = 10;
	pstDevice = new CALL_S_DEVICEINFO[uiSize];
	tRet = tup_call_media_get_devices(&uiSize,pstDevice,CALL_E_CALL_DEVICE_VIDEO);
	if(tRet == TUP_FAIL)
	{
		AfxMessageBox(L"tup_call_media_get_devices Failed.");
	}
	for(TUP_UINT32 i=0;i<uiSize;i++)
	{
		g_mapVideoDevice[pstDevice[i].ulIndex] = pstDevice[i].strName;
	}
	delete[] pstDevice;
	pstDevice = NULL;

	TUP_UINT32 uiIndex;
	tRet = tup_call_media_get_mic_index(&uiIndex);
	if(tRet == TUP_FAIL)
	{
		AfxMessageBox(L"tup_call_media_get_mic_index Failed.");
	}
	g_iIndeviceIndex = uiIndex;

	tRet = tup_call_media_get_speak_index(&uiIndex);
	if(tRet == TUP_FAIL)
	{
		AfxMessageBox(L"tup_call_media_get_mic_index Failed.");
	}
	g_iOutdeviceIndex = uiIndex;
	

	tRet = tup_call_media_get_video_index(&uiIndex);
	if(tRet == TUP_FAIL)
	{
		AfxMessageBox(L"tup_call_media_get_video_index Failed.");
	}
	g_iVideodeviceIndex = uiIndex;

	

}

void CMediaSetDlg::RefreshControl()
{
	MAP_DEVICE::iterator it = g_mapInDevice.begin();
	MAP_DEVICE::iterator itEnd = g_mapInDevice.end();
	for(;it!=itEnd;it++)
	{
		m_cbxInputDevice.InsertString(it->first,CTools::UTF2UNICODE(it->second));
	}
	m_cbxInputDevice.SetCurSel(g_iIndeviceIndex);

	it = g_mapOutDevice.begin();
	itEnd = g_mapOutDevice.end();
	for(;it!=itEnd;it++)
	{
		m_cbxOutputDevice.InsertString(it->first,CTools::UTF2UNICODE(it->second));
	}
	m_cbxOutputDevice.SetCurSel(g_iOutdeviceIndex);

	it = g_mapVideoDevice.begin();
	itEnd = g_mapVideoDevice.end();
	for(;it!=itEnd;it++)
	{
		m_cbxVideoDevice.InsertString(it->first,CTools::UTF2UNICODE(it->second));
	}
	m_cbxVideoDevice.SetCurSel(g_iVideodeviceIndex);

	m_sldMicLevel.SetPos(g_iMicLevel);
	m_sldSpkLevel.SetPos(g_iSpeakerLevel);

	//������������
	((CButton *)GetDlgItem(IDC_RADIO2))->SetCheck(1);
	//tup_call_media_set_video_tactic(TUP_FALSE);

}
void CMediaSetDlg::Save()
{
	int iSel = m_cbxInputDevice.GetCurSel();
	TUP_RESULT tRet = tup_call_media_set_mic_index(iSel);
	if(tRet == TUP_FAIL)
	{
		AfxMessageBox(L"tup_call_media_set_mic_index Failed.");
	}

	iSel = m_cbxOutputDevice.GetCurSel();
	tRet = tup_call_media_set_speak_index(iSel);
	if(tRet == TUP_FAIL)
	{
		AfxMessageBox(L"tup_call_media_set_speak_index Failed.");
	}

	iSel = m_cbxVideoDevice.GetCurSel();
	tRet = tup_call_media_set_video_index(iSel);
	if(tRet == TUP_FAIL)
	{
		AfxMessageBox(L"tup_call_media_set_video_index Failed.");
	}

	int iLevel = m_sldSpkLevel.GetPos();
	tRet = tup_call_media_set_speak_volume(CALL_E_AO_DEV_SPEAKER,iLevel);
	if(tRet == TUP_FAIL)
	{
		AfxMessageBox(L"tup_call_media_set_speak_volume Failed.");
	}

	iLevel = m_sldMicLevel.GetPos();
	tRet = tup_call_media_set_mic_volume(CALL_E_AUD_DEV_ROUTE_LOUDSPEAKER,iLevel);
	if(tRet == TUP_FAIL)
	{
		AfxMessageBox(L"tup_call_media_set_mic_volume Failed.");
	}

	int iCheck = ((CButton *)GetDlgItem(IDC_RADIO1))->GetCheck();
	if(1 == iCheck)
	{
//		tup_call_media_set_video_tactic(TUP_TRUE);
	}
	else
	{
//		tup_call_media_set_video_tactic(TUP_FALSE);
	}


}
void CMediaSetDlg::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CVideoPreviewDlg dlg;
	dlg.m_uiIndex = m_cbxVideoDevice.GetCurSel();
	dlg.DoModal();
}

void CMediaSetDlg::OnBnClickedBtAudInput()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString m_str;
	GetDlgItem(IDC_BT_AUD_INPUT)->GetWindowText(m_str);
	if (m_str == L"������Ƶ����")
	{
		GetDlgItem(IDC_BT_AUD_INPUT)->SetWindowText(L"ֹͣ����");
		//��ʼ������˷�
		//<1>������ʱ��
		(void)SetTimer(TEST_MIC_TIMEID, TEST_MIC_TIME_DURATION, NULL);
		//<2>�������������
		(void)m_prsInDevice.SetPos(0);
		(void)tup_call_open_audio_preview(); 
		m_IsMicOn = true;
	}
	else
	{
		GetDlgItem(IDC_BT_AUD_INPUT)->SetWindowText(L"������Ƶ����");
		//ֹͣ������˷�
		//<1>��ʱ����ֹͣ
		(void)KillTimer(TEST_MIC_TIMEID);
		//<2>�������������
		(void)m_prsInDevice.SetPos(0);
		//<4>    
		(void)tup_call_close_audio_preview();
		m_IsMicOn = false;
	}
}

void CMediaSetDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(TEST_MIC_TIMEID == nIDEvent)
	{
		
		int iPos = 0;
		(void)tup_call_media_get_mic_level((TUP_UINT32*)&iPos);
		(void)m_prsInDevice.SetPos((short)(iPos * TEST_MIC_LEVEL_MULTIPLE));
	//	(void)m_prsInDevice.RedrawWindow(TRUE);
	}
	else{}

	CDialog::OnTimer(nIDEvent);
}

void CMediaSetDlg::OnBnClickedBtAudOuput()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString m_str;
	GetDlgItem(IDC_BT_AUD_OUPUT)->GetWindowText(m_str);

	//////��ȡ�����ļ�·��///////
	std::string strPlayFile = CTools::UNICODE2UTF(CTools::getCurrentPath()) + "\\audio\\SoundTest.wav";
	//////��ȡ�����ļ�·��///////
	if (m_str == L"������Ƶ���")
	{
		GetDlgItem(IDC_BT_AUD_OUPUT)->SetWindowText(L"ֹͣ����");
		TUP_RESULT tRet = tup_call_media_startplay(0,strPlayFile.c_str(),&m_lSpeakerPlayHandle);
		m_IsSPKon = true;

	}
	else
	{
		GetDlgItem(IDC_BT_AUD_OUPUT)->SetWindowText(L"������Ƶ���");
		(void)tup_call_media_stopplay(m_lSpeakerPlayHandle);
		m_lSpeakerPlayHandle = 0;
		m_IsSPKon = false;
	}


}

void CMediaSetDlg::OnNMReleasedcaptureSlider2(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	////////��Ƶ��������//////
	int iLevel = m_sldMicLevel.GetPos();
	tup_call_media_set_mic_volume(CALL_E_AUD_DEV_ROUTE_LOUDSPEAKER,iLevel);
}

void CMediaSetDlg::OnNMReleasedcaptureSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	////////��Ƶ�������//////
	int iLevel = m_sldSpkLevel.GetPos();
	tup_call_media_set_speak_volume(CALL_E_AO_DEV_SPEAKER,iLevel);;
}

void CMediaSetDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialog::OnClose();
}
