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

#include <afxhtml.h>

// CMyHtmlEditCtrl

class CMyHtmlEditCtrl : public CWnd, public CHtmlEditCtrlBase<CHtmlEditCtrl>
{
	DECLARE_DYNAMIC(CMyHtmlEditCtrl)

public:
	CMyHtmlEditCtrl(){}
	virtual ~CMyHtmlEditCtrl(){}
	virtual void OnFinalRelease();
	virtual BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle,
		const RECT& rect, CWnd* pParentWnd, int nID, CCreateContext *pContext=NULL);
	virtual LPCTSTR GetStartDocument();
	BOOL GetDHtmlDocument(IHTMLDocument2 **ppDocument) const;

protected:
	DECLARE_MESSAGE_MAP()
	DECLARE_EVENTSINK_MAP()
	void OnNavigateComplete2(LPDISPATCH lpDispatch, VARIANT* varUrl);
};