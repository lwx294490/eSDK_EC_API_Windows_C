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


// CImageStatic
#define MAX_IMG_BUFFER 
class CImageStatic : public CStatic
{
	DECLARE_DYNAMIC(CImageStatic)

public:
	CImageStatic();
	virtual ~CImageStatic();

protected:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnPaint();

private:
	CString m_cstrImageFile;
	TUP_CHAR* m_pImgBuffer;
	int m_nImgBufSize;

	//Add by w00321336 to draw byte image at 2015-1-21 begin
protected:
	void DrawImageFromBuffer();
	void DrawImageFromFile();
	//Add by w00321336 to draw byte image at 2015-1-21 end

public:
	void SetImageFile(const CString& cstrImageFile);
	void SetImgBuffer(TUP_CHAR* pBuffer, int nSize);//Add by w00321336 to draw byte image at 2015-1-21
};


