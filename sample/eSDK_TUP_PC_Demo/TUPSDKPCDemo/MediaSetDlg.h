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
static const int TEST_MIC_TIMEID  = 10001;      //测试麦克风的定时器ID
static const int TEST_SPK_TIMEID  = 10002;      //测试扬声器的定时器ID
static const int TEST_MIC_TIME_DURATION = 20;   //测试麦克风的定时器时长
static const int TEST_MIC_LEVEL_MULTIPLE = 10;  //获取的Level和设置的进度条倍率换算 为10倍


// CMediaSetDlg 对话框

class CMediaSetDlg : public CDialog
{
	DECLARE_DYNAMIC(CMediaSetDlg)

public:
	CMediaSetDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMediaSetDlg();

// 对话框数据
	enum { IDD = IDD_MEDIA_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	int m_lSpeakerPlayHandle;                           //扬声器播放句柄
	bool m_IsSPKon ;                                    ///是否开启扬声器
	bool m_IsMicOn ;                                    ///是否开启麦克风////

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
