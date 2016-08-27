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


typedef struct 
{   
	TUP_ULONG UserID;         ////用户ID
	TUP_UINT32  DevideID;    ///设备ID
	CWnd* m_VideoHwnd;       /////视频的wnd
	CWnd* m_NameHwnd;        /////姓名的wnd
	bool isValuable;        /////是否可用
} VideoINfo;

// CFullScreenModelDlg dialog

class CFullScreenModelDlg : public CDialog
{
	DECLARE_DYNAMIC(CFullScreenModelDlg)

public:
	CFullScreenModelDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CFullScreenModelDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_FULLSCREEN_MODEL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

public:
	void InitVideoInfo();

public:
	VideoINfo FullScreenModeInfo[9];
};
