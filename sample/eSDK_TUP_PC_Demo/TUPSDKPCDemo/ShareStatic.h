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


// CShareStatic

class CShareStatic : public CStatic
{
	DECLARE_DYNAMIC(CShareStatic)

public:
	CShareStatic();
	virtual ~CShareStatic();
	virtual void OnDraw(CDC* pDC);

protected:
	DECLARE_MESSAGE_MAP()

protected:
	HBITMAP m_hASBitmap;
	RECT borderRc;
public:

	void SetBitmap2(BITMAP *pBMP);
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	CONF_HANDLE m_handle;
	
};


