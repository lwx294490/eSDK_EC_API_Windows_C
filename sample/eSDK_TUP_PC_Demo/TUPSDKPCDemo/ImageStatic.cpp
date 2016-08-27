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

// ImageStatic.cpp : 实现文件
//

#include "stdafx.h"
#include "TUPSDKPCDemo.h"
#include "ImageStatic.h"


// CImageStatic

IMPLEMENT_DYNAMIC(CImageStatic, CStatic)

CImageStatic::CImageStatic()
: m_cstrImageFile(L"")
, m_pImgBuffer(NULL)
, m_nImgBufSize(0)
{

}

CImageStatic::~CImageStatic()
{
	if (NULL != m_pImgBuffer)
	{
		delete[] m_pImgBuffer;
		m_pImgBuffer = NULL;
	}

	m_nImgBufSize = 0;
}


BEGIN_MESSAGE_MAP(CImageStatic, CStatic)
	ON_WM_PAINT()
END_MESSAGE_MAP()

// CImageStatic 消息处理程序

void CImageStatic::DrawImageFromBuffer()
{
	if(NULL == m_pImgBuffer || m_nImgBufSize == 0)
	{
		return;
	}

	LPVOID pvData = NULL;
	HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, m_nImgBufSize);
	pvData = GlobalLock(hGlobal);
	memcpy(pvData, m_pImgBuffer, m_nImgBufSize);
	GlobalUnlock(hGlobal);

	IStream *pStream = NULL;
	CreateStreamOnHGlobal(hGlobal, TRUE, &pStream);

	Image image(pStream);
	GlobalFree(hGlobal);

	CRect rc;
	GetClientRect(&rc);

	CDC* pDC = GetDC();
	Graphics graphics( pDC->m_hDC);
	graphics.DrawImage(&image, 0,0,rc.Width(),rc.Height());
}

void CImageStatic::DrawImageFromFile()
{
	if(m_cstrImageFile.IsEmpty())
	{
		return;
	}

	CRect rc;
	GetClientRect(&rc);
	CDC* pDC = GetDC();
	Graphics graphics( pDC->m_hDC);
	Image image(m_cstrImageFile, FALSE);
	graphics.DrawImage(&image, 0,0,rc.Width(),rc.Height());
}

void CImageStatic::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	//Modified by w00321336 to draw byte image for DTS2015010701095 at 2015-1-21 begin
	if(!m_cstrImageFile.IsEmpty())
	{
		DrawImageFromFile();
	}
	else
	{
		DrawImageFromBuffer();
	}
	//Modified by w00321336 end
}

void CImageStatic::SetImageFile(const CString& cstrImageFile)
{
	m_cstrImageFile = cstrImageFile;
}

void CImageStatic::SetImgBuffer(TUP_CHAR* pBuffer, int nSize)
{
	if (NULL != m_pImgBuffer)
	{
		delete[] m_pImgBuffer;
		m_pImgBuffer = NULL;
	}

	m_pImgBuffer = new TUP_CHAR[nSize+1];
	memset(m_pImgBuffer,0,nSize+1);
	m_nImgBufSize = nSize;
	memcpy(m_pImgBuffer,pBuffer,nSize);
}


