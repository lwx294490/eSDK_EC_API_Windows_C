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

#include <vector>
#include <string>
#include "Tools.h"
// CRichEditCtrlEx

#define FRM_TIMER_ID			1

class CRichEditCtrlEx : public CRichEditCtrl
{
	DECLARE_DYNAMIC(CRichEditCtrlEx)

public:
	CRichEditCtrlEx();
	virtual ~CRichEditCtrlEx();
private:
	CComPtr<IRichEditOle> m_pRichEditOle;
protected:
	DECLARE_MESSAGE_MAP()
	virtual void PreSubclassWindow();
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnDestroy();
	int FindFirstObject(int cpMin, int nObjectCount);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	HRESULT InsertImage(LPCTSTR lpszPathName,int index);
	static int picIndex;
	MsgToSend msgTxtPic;
	void analysisMsg();
};


