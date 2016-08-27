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

// ShareStatic.cpp : 实现文件
//

#include "stdafx.h"
#include "tup_conf_baseapi.h"
#include "ShareStatic.h"


// CShareStatic

IMPLEMENT_DYNAMIC(CShareStatic, CStatic)

CShareStatic::CShareStatic()
{
	m_hASBitmap = NULL;
	memset(&borderRc, 0, sizeof(RECT));

}

CShareStatic::~CShareStatic()
{
	if (m_hASBitmap)
	{
		::DeleteObject(m_hASBitmap);
	}
	m_handle = 0;
}


BEGIN_MESSAGE_MAP(CShareStatic, CStatic)
	ON_WM_PAINT()
	ON_WM_CREATE()
END_MESSAGE_MAP()



// CShareStatic 消息处理程序
HPEN hPen = NULL;
void CShareStatic::OnDraw(CDC* pDC)
{
	CRect rect;
	HDC hdc = pDC->GetSafeHdc();	
	//return;
	GetClientRect(&rect);
	if (m_hASBitmap==NULL)
	{
		CBrush bs;

		bs.CreateSolidBrush(RGB(255,255,255));

		pDC->FillRect(&rect,&bs);
		//////DTS2015103102033窗体刷新时，白板内容有时刷新不出来  by c00327158  2015.11.2 START//////
		HDC *data = (HDC*)tup_conf_ds_get_surfacebmp(m_handle, IID_COMPONENT_WB,NULL,NULL);
		if(data)
		{
			::BitBlt(pDC->m_hDC, 0, 0, rect.Width(), rect.Height(), (HDC)data, 0, 0, SRCCOPY);
		}
		/////DTS2015103102033窗体刷新时，白板内容有时刷新不出来  by c00327158  2015.11.2 END/////
	}
	else
	{
		HDC memDc = ::CreateCompatibleDC(pDC->GetSafeHdc());
		HBITMAP old = (HBITMAP)::SelectObject(memDc,(HGDIOBJ)m_hASBitmap);
		BITMAP m_bitmap;
		GetObject(m_hASBitmap,sizeof(m_bitmap),&m_bitmap);
		//半色调模式，解决画面拉伸失真问题
		::SetStretchBltMode(hdc,HALFTONE);
		//拉伸画面，适合对话框界面输出
		::StretchBlt(hdc,0,0,rect.Width(),rect.Height(),memDc,0,0,m_bitmap.bmWidth,m_bitmap.bmHeight,SRCCOPY);
		{
			SelectObject(hdc, GetStockObject(NULL_BRUSH));
			if (NULL == hPen)
			{
			    //hPen = CreatePen(PS_SOLID, 1, RGB(0,255,255));
				hPen = CreatePen(PS_SOLID, 1, RGB(255,0,0));
			}
			SelectObject(hdc, hPen);
			//SelectObject(hdc, GetStockObject(WHITE_PEN));
			Rectangle(hdc, borderRc.left, borderRc.top, borderRc.right+1, borderRc.bottom+1);
		}
		::SelectObject(memDc,old);
		::DeleteDC(memDc);
		
	}
	
	
}


void CShareStatic::SetBitmap2(BITMAP *pBMP)
{
	//////////////////////////////////////////////////////////////////////////
	GetClientRect(&borderRc);
	if (!pBMP)
	{
		if (m_hASBitmap)
		{
			::DeleteObject(m_hASBitmap);
			m_hASBitmap = NULL;
			Invalidate(TRUE);
		}
		return ;
	}
	if (m_hASBitmap==NULL)
	{
		m_hASBitmap = CreateBitmap(pBMP->bmWidth, pBMP->bmHeight, pBMP->bmPlanes, pBMP->bmBitsPixel, pBMP->bmBits);
	}
	else
	{	
		::DeleteObject(m_hASBitmap);
		m_hASBitmap = CreateBitmap(pBMP->bmWidth, pBMP->bmHeight, pBMP->bmPlanes, pBMP->bmBitsPixel, pBMP->bmBits);
		
	}

	Invalidate(TRUE);
}

void CShareStatic::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CStatic::OnPaint()
	OnDraw(&dc);
}

int CShareStatic::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CStatic::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	//RECT rc;
	GetClientRect(&borderRc);
	//borderRc.left = 5;
	//borderRc.top = 5;
	//borderRc.right = 50;
	//borderRc.bottom = 50;

	return 0;
}

