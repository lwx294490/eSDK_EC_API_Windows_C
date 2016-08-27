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

// MyHtmlEditCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "IMMSGDemo.h"
#include "MyHtmlEditCtrl.h"


IMPLEMENT_DYNAMIC(CMyHtmlEditCtrl, CWnd)

void CMyHtmlEditCtrl::OnFinalRelease()
{
	CWnd::OnFinalRelease();
}
BEGIN_MESSAGE_MAP(CMyHtmlEditCtrl, CWnd)
END_MESSAGE_MAP()
BEGIN_EVENTSINK_MAP(CMyHtmlEditCtrl,CWnd)
	ON_EVENT_REFLECT(CMyHtmlEditCtrl, 252 /* NavigateComplete2 */, OnNavigateComplete2, VTS_DISPATCH VTS_PVARIANT)
END_EVENTSINK_MAP()
// CMyHtmlEditCtrl 消息处理程序
void CMyHtmlEditCtrl::OnNavigateComplete2(LPDISPATCH lpDispatch, VARIANT* varUrl)
{
	ATLTRACE(_T("CMyHtmlEditCtrl::OnNavigateComplete2()"));
}
BOOL CMyHtmlEditCtrl::GetDHtmlDocument(IHTMLDocument2 **ppDocument) const
{
	if(ppDocument == NULL)
	{
		ASSERT(FALSE);
		return FALSE;
	}
	*ppDocument = NULL;    
	CMyHtmlEditCtrl *pThis = const_cast<CMyHtmlEditCtrl*>(this);
	CComQIPtr<IWebBrowser2> pBrowserApp = pThis->GetControlUnknown();
	ASSERT(pBrowserApp != NULL);
	if (pBrowserApp)
	{
		CComPtr<IDispatch> spDispDocument;
		HRESULT hr = pBrowserApp->get_Document(&spDispDocument);
		if (SUCCEEDED(hr) && spDispDocument)
		{
			return S_OK == spDispDocument->QueryInterface(ppDocument) ? TRUE : FALSE;
		}
	}
	return FALSE;
}


BOOL CMyHtmlEditCtrl::Create(LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd,
	int nID, CCreateContext *pContext) 
{
	BOOL bRet = FALSE;
	// create the control window
	AfxEnableControlContainer();
	if (CreateControl(CLSID_WebBrowser, lpszWindowName,
		WS_VISIBLE | WS_CHILD, rect, pParentWnd, nID))
	{
		// in order to put the webbrowser in design mode, you must
		// first load a document into it. "about:blank" seems to
		// be the safest thing to load for a good starting point.
		CComQIPtr<IWebBrowser2> pBrowserApp = GetControlUnknown();
		ASSERT(pBrowserApp);
		if (pBrowserApp)
		{
			CComVariant vEmpty;
			LPCTSTR szDoc = GetStartDocument();
			if (szDoc)
			{
				CComBSTR bstrStart(szDoc);
				if (S_OK == pBrowserApp->Navigate(bstrStart, 
					&vEmpty,
					&vEmpty,
					&vEmpty,
					&vEmpty))
				{
					bRet = TRUE;
				}
			}
			else
				bRet = TRUE;
		}
	}
	if (!bRet)
		DestroyWindow();
	return bRet;
}


LPCTSTR CMyHtmlEditCtrl::GetStartDocument()
{
	LPCTSTR szDefaultDoc = _T("about:blank");
	return szDefaultDoc;
}