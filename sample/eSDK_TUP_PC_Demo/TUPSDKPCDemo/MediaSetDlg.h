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
#include "afxwin.h"
#include "afxcmn.h"
static const int TEST_MIC_TIMEID  = 10001;      //������˷�Ķ�ʱ��ID
static const int TEST_SPK_TIMEID  = 10002;      //�����������Ķ�ʱ��ID
static const int TEST_MIC_TIME_DURATION = 20;   //������˷�Ķ�ʱ��ʱ��
static const int TEST_MIC_LEVEL_MULTIPLE = 10;  //��ȡ��Level�����õĽ��������ʻ��� Ϊ10��


// CMediaSetDlg �Ի���

class CMediaSetDlg : public CDialog
{
	DECLARE_DYNAMIC(CMediaSetDlg)

public:
	CMediaSetDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMediaSetDlg();

// �Ի�������
	enum { IDD = IDD_MEDIA_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	int m_lSpeakerPlayHandle;                           //���������ž��
	bool m_IsSPKon ;                                    ///�Ƿ���������
	bool m_IsMicOn ;                                    ///�Ƿ�����˷�////

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CComboBox m_cbxInputDevice;
	CComboBox m_cbxOutputDevice;
	CComboBox m_cbxVideoDevice;
	void GetMediaDeviceList();
	void RefreshControl();
	void Save();
	CSliderCtrl m_sldMicLevel;
	CSliderCtrl m_sldSpkLevel;
	CProgressCtrl m_prsInDevice;
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedBtAudInput();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedBtAudOuput();
	afx_msg void OnNMReleasedcaptureSlider2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMReleasedcaptureSlider1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClose();
};
