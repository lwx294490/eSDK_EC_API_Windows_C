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


