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

// RichEditCtrlEx.cpp : implementation file
//

#include "stdafx.h"
#include "IMMSGDemo.h"
#include "RichEditCtrlEx.h"
#include "OleImage.h"
#include <richole.h>

int CRichEditCtrlEx::picIndex=0;
// CRichEditCtrlEx

IMPLEMENT_DYNAMIC(CRichEditCtrlEx, CRichEditCtrl)

	CRichEditCtrlEx::CRichEditCtrlEx()
{
	m_pRichEditOle = NULL;
}

CRichEditCtrlEx::~CRichEditCtrlEx()
{
}


BEGIN_MESSAGE_MAP(CRichEditCtrlEx, CRichEditCtrl)
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()



// CRichEditCtrlEx ��Ϣ�������


//
// ���������һЩ��Ҫ���޸�
//

void CRichEditCtrlEx::PreSubclassWindow()
{
	// TODO: �ڴ����ר�ô����/����û���

	// ���������ѡ��ȥ��RichEdit��˫��������
	// ��Ϊ˵ʵ�����Ҳ�֪����ô�ֱ�������Ӣ�����壬�����λͬѧ֪�������
	// ��һ��
	DWORD fontStyle = SendMessage(EM_GETLANGOPTIONS);
	fontStyle &= ~IMF_DUALFONT;
	SendMessage(EM_SETLANGOPTIONS, 0, fontStyle);

	// �޸�Ϊ����͸����ˢ������˸�������Լ����ư�ɫ����
	ModifyStyleEx(0, WS_EX_TRANSPARENT);

	// ����ӿ�ָ��ʹ�÷ǳ�Ƶ�������������Ч��
	m_pRichEditOle = GetIRichEditOle();

	// ������ʱ�������ڸ��¶���
	SetTimer(FRM_TIMER_ID, MIN_FRM_DELAY, NULL);

	CRichEditCtrl::PreSubclassWindow();
}

//
// ��������ʱ����һЩ��Ҫ��������
//
void CRichEditCtrlEx::OnDestroy()
{
	// ֹͣ��ʱ�������Ǳ�Ҫ��
	KillTimer(FRM_TIMER_ID);
	// ������ݣ�Ŀ����ɾ�����в����COleImage����
	SetWindowText(_T(""));
	// ���Ǳ����ˣ�RichEdit֧�ֶ༶������������Ȼɾ���ˣ����ǳ�������
	// �л������ж�������ã���ճ�����������������ͷ���Щ����
	EmptyUndoBuffer();

	// ����Ĺ��������ڸ���OnDestroyǰ���ã����򴰿��Ѿ����٣�����û��
	CRichEditCtrl::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������
}

//
// ���Ʊ���
//
BOOL CRichEditCtrlEx::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CRect rc;
	GetClientRect(rc);
	pDC->FillSolidRect(rc, RGB(255, 255, 255));
	return TRUE;
}

//
// ���ҵ�һ���ַ��������ڻ����cpMin�Ķ��������ж����е�����
//
int CRichEditCtrlEx::FindFirstObject(int cpMin, int nObjectCount)
{
	// ��׼�Ķ��ֲ����㷨�����ý�����
	int low = 0;
	int high = nObjectCount - 1;
	REOBJECT reoMid = {0};
	reoMid.cbStruct = sizeof(REOBJECT);
	while (low <= high) {
		int mid = (low + high) >> 1;
		if (m_pRichEditOle->GetObject(mid, &reoMid, REO_GETOBJ_POLEOBJ) != S_OK) {
			return -1;
		}
		reoMid.poleobj->Release();
		if (reoMid.cp == cpMin) {
			return mid;
		} else if (reoMid.cp < cpMin) {
			low = mid + 1;
		} else {
			high = mid - 1;
		}
	}

	// ֻ�������û�ҵ�ʱ���Ƿ���-1�����Ƿ���low����ʱlow��Ȼ���ڻ����high
	// �պ���������
	return low;
}

//
// ��ʱ�����������¶���
//
void CRichEditCtrlEx::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	// ��ʱ��ID����Ϊ���������õĶ�ʱ��ID����Ҫ��Ϊ����SetTimer�����յ��ľ�һ��ʱ����
	// ���õĶ�ʱ���������˸��໹�������ã���һ�㲻�û��ɣ��Ҳ��Ե�����
	// ��д��ܶ����ı������������ֺ����������붯����Ȼ�����Ϲ������ײ����ټ�������
	// ��������Ȼ�����������ˣ����Ƕ���ȴ�����ر�죬��Ȼ�յ��˸���Ķ�ʱ��
	// ��������ʱ��ID�������һ�������õ�ֵ���������������һ����Ϊ1
	if (nIDEvent == FRM_TIMER_ID) {

		// �õ���������������0ʱ����Ҫˢ��
		int nObjectCount = m_pRichEditOle->GetObjectCount();
		if (nObjectCount > 0) {
			CRect rc;
			GetRect(rc); // �õ�������ľ�������
			// �ֱ�ʹ�����ϽǺ����½ǵĵ�õ���С������ַ�����
			// ���ɼ��������С������ַ�����
			int cpMin = CharFromPos(rc.TopLeft());
			int cpMax = CharFromPos(rc.BottomRight());

			// ʹ�ö��ֲ����㷨�ҵ���һ���ַ��������ڻ����cpMin�Ķ�������
			int iFirst = FindFirstObject(cpMin, nObjectCount);
			REOBJECT reo = {0};
			reo.cbStruct = sizeof(REOBJECT);

			// �ӵ�һ��������ʼ�����������֡
			for (int i = iFirst; i < nObjectCount; i++) {
				if (m_pRichEditOle->GetObject(i, &reo, REO_GETOBJ_POLEOBJ) == S_OK) {
					reo.poleobj->Release();
					// ��ǰ������ַ�������������ַ�������˵�������ڿɼ�����ֹͣ����
					if (reo.cp > cpMax) {
						break;
					}

					// ��COleImage����ʱ���ܸ���
					if (InlineIsEqualGUID(reo.clsid, CLSID_OleImage)) {
						// ����֡
						COleImage *pOleImage = COleImage::FromOleObject(reo.poleobj);
						pOleImage->ChangeFrame();
					}
				}
			}
		}
	} else {
		CRichEditCtrl::OnTimer(nIDEvent);
	}
}

//
// ����ͼ��
//
HRESULT CRichEditCtrlEx::InsertImage(LPCTSTR lpszPathName,int index)
{
	// ȫ��ʹ������ָ��
	CComPtr<IStorage> spStorage;
	CComPtr<ILockBytes> spLockBytes;
	CComPtr<IOleClientSite> spOleClientSite;	
	CComPtr<COleImage> spOleImage;
	CComPtr<IOleObject> spOleObject;
	CLSID clsid;
	REOBJECT reobject;
	HRESULT hr = E_FAIL;

	do {

		// ����LockBytes
		hr = CreateILockBytesOnHGlobal(NULL, TRUE, &spLockBytes);
		if (hr != S_OK) {
			break;
		}

		ASSERT(spLockBytes != NULL);

		// ����Storage
		hr = StgCreateDocfileOnILockBytes(spLockBytes,
			STGM_SHARE_EXCLUSIVE | STGM_CREATE | STGM_READWRITE, 0, &spStorage);
		if (hr != S_OK) {
			break;
		}

		// ��ȡClientSite
		hr = m_pRichEditOle->GetClientSite(&spOleClientSite);
		if (hr != S_OK) {
			break;
		}

		// ����COleImageʵ��
		hr = CoCreateInstance(CLSID_OleImage, NULL, CLSCTX_INPROC, IID_IOleImage, (LPVOID*) &spOleImage);
		if (hr != S_OK) {
			break;
		}

		// ����ͼ��
		hr = spOleImage->LoadFromFile(_bstr_t(lpszPathName), this, 400);
		if (hr != S_OK) {
			break;
		}

		// ��ȡIOleObject�ӿ�
		hr = spOleImage->QueryInterface(IID_IOleObject, (LPVOID *) &spOleObject);
		if (hr != S_OK) {
			break;
		}

		// ��ȡIOleObject���û�CLSID
		hr = spOleObject->GetUserClassID(&clsid);
		if (hr != S_OK) {
			break;
		}

		// ���OLE��������
		ZeroMemory(&reobject, sizeof(REOBJECT));		
		reobject.cbStruct	= sizeof(REOBJECT);
		reobject.clsid		= clsid;
		reobject.cp			= REO_CP_SELECTION;
		reobject.dvaspect	= DVASPECT_CONTENT;
		reobject.dwFlags	= REO_BELOWBASELINE;
		reobject.poleobj	= spOleObject;
		reobject.polesite	= spOleClientSite;
		reobject.pstg		= spStorage;
		reobject.dwUser     =index;
		SIZEL sizel = {0};
		reobject.sizel = sizel;

		// ����OLE����
		hr = m_pRichEditOle->InsertObject(&reobject);
		if (hr != S_OK) {
			break;
		}

		// ֪ͨOLE������֤OLE������ȷ����
		hr = OleSetContainedObject(spOleObject, TRUE);

	} while (0);

	return hr;
}

void CRichEditCtrlEx::analysisMsg()
{
	vector<PicPathInfo> pics;

	int c = m_pRichEditOle->GetObjectCount(); 

	for(int i = 0 ; i < c ; i++) //����λͼ 
	{ 
		REOBJECT object; //λͼ��Ϣ�������� 
		memset(&object,0,sizeof(REOBJECT)); 
		object.cbStruct = sizeof(REOBJECT); 
		m_pRichEditOle->GetObject(i,&object,REO_GETOBJ_ALL_INTERFACES); 

		int m_PicSize = (int)msgTxtPic.pictures.size();
		for (int j=0;j < m_PicSize;j++)
		{
			if (object.dwUser==msgTxtPic.pictures[j].index)
			{
				PicPathInfo pic;
				pic.index=object.dwUser;
				pic.pos=object.cp;
				pic.picPath=msgTxtPic.pictures[j].picPath;

				pics.push_back(pic);
			}
		}
	}

	if (msgTxtPic.pictures.size())
	{
		msgTxtPic.pictures.clear();
	}

	int m_picSize = int(pics.size());
	for (int i = 0;i < m_picSize;i++)
	{
		msgTxtPic.pictures.push_back(pics[i]);
	}

}