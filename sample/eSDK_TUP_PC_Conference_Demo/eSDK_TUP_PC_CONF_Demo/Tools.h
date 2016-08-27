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

#include <string>

class CTools
{
private:
	CTools(void);
	~CTools(void);
public:
	static CString ANSI2UNICODE(std::string& strUtf8);
	static void CString2Char(const CString &str,char* ch,unsigned int lenth);
	static void string2CString(const std::string&,CString&);
	static std::wstring string2wstring(const std::string& str);
	static std::string UNICODE2UTF(const CString& cstr);
	static CString UTF2UNICODE(const std::string& str);
	static void OpenURL( const CString &strURI );
	static bool GetBestHostip(std::string& ip, const std::string& serverip);
	static CString getCurrentPath();
	static void GetIPPort(const std::string& serverURL,std::string& ip,int& port);
};