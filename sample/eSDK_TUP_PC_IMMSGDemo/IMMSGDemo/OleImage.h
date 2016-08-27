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

// OleImage.h : Declaration of the COleImage
#pragma once
#include "resource.h"       // main symbols
#include <atlctl.h>
#include "IMMSGDemo_i.h"
#include "_IOleImageEvents_CP.h"
#include <GdiPlus.h>
using namespace Gdiplus;

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;



// COleImage
class ATL_NO_VTABLE COleImage :
	public CComObjectRootEx<CComSingleThreadModel>,
	public IDispatchImpl<IOleImage, &IID_IOleImage, &LIBID_IMMSGDemoLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public IOleControlImpl<COleImage>,
	public IOleObjectImpl<COleImage>,
	public IOleInPlaceActiveObjectImpl<COleImage>,
	public IViewObjectExImpl<COleImage>,
	public IOleInPlaceObjectWindowlessImpl<COleImage>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<COleImage>,
	public CProxy_IOleImageEvents<COleImage>,
	public IQuickActivateImpl<COleImage>,
#ifndef _WIN32_WCE
	public IDataObjectImpl<COleImage>,
#endif
	public IProvideClassInfo2Impl<&CLSID_OleImage, &__uuidof(_IOleImageEvents), &LIBID_IMMSGDemoLib>,
	public CComCoClass<COleImage, &CLSID_OleImage>,
	public CComControl<COleImage>
{
public:


	COleImage()
	{
	}

DECLARE_OLEMISC_STATUS(OLEMISC_RECOMPOSEONRESIZE |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_INSIDEOUT |
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST
)

DECLARE_REGISTRY_RESOURCEID(IDR_OLEIMAGE)


BEGIN_COM_MAP(COleImage)
	COM_INTERFACE_ENTRY(IOleImage)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IViewObjectEx)
	COM_INTERFACE_ENTRY(IViewObject2)
	COM_INTERFACE_ENTRY(IViewObject)
	COM_INTERFACE_ENTRY(IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceObject)
	COM_INTERFACE_ENTRY2(IOleWindow, IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceActiveObject)
	COM_INTERFACE_ENTRY(IOleControl)
	COM_INTERFACE_ENTRY(IOleObject)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY(IQuickActivate)
#ifndef _WIN32_WCE
	COM_INTERFACE_ENTRY(IDataObject)
#endif
	COM_INTERFACE_ENTRY(IProvideClassInfo)
	COM_INTERFACE_ENTRY(IProvideClassInfo2)
END_COM_MAP()

BEGIN_PROP_MAP(COleImage)
	PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
	PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
	// Example entries
	// PROP_ENTRY_TYPE("Property Name", dispid, clsid, vtType)
	// PROP_PAGE(CLSID_StockColorPage)
END_PROP_MAP()

BEGIN_CONNECTION_POINT_MAP(COleImage)
	CONNECTION_POINT_ENTRY(__uuidof(_IOleImageEvents))
END_CONNECTION_POINT_MAP()

BEGIN_MSG_MAP(COleImage)
	CHAIN_MSG_MAP(CComControl<COleImage>)
	DEFAULT_REFLECTION_HANDLER()
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid)
	{
		static const IID* const arr[] =
		{
			&IID_IOleImage,
		};

		for (int i=0; i<sizeof(arr)/sizeof(arr[0]); i++)
		{
			if (InlineIsEqualGUID(*arr[i], riid))
				return S_OK;
		}
		return S_FALSE;
	}

// IViewObjectEx
	DECLARE_VIEW_STATUS(VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE)

// IOleImage

	DECLARE_PROTECT_FINAL_CONSTRUCT()


	// 最小的帧延时
#define MIN_FRM_DELAY				100

private:
	CDC *m_pDCs; // 每帧的DC
	CBitmap *m_pBitmaps; // 每一帧的位图
	CBitmap **m_ppOldBmps; // 保存每一帧DC旧的位图
	int *m_pFrmIndexes; // 每个100毫秒对应的帧索引
	int m_nFrmCount; // 总帧数
	int m_nTimeCount; // 100毫秒的总数，例如GIF所有帧加起来总的延迟是1秒，则这个值为10
	volatile int m_iPrevFrm; // 前一帧，定时器触发时用于判断是否需要改换帧
	volatile int m_iCurTime; // 当前时间（即第几个100毫秒）
	CRichEditCtrl *m_pContainer; // 容器窗口指针
	static DWORD m_dwOleObjectOffset; // IOleObject接口指针距离COleImage起始地址的偏移量

public:

	// 实例化后一定会被调用的函数
	HRESULT FinalConstruct();

	// 删除实例前一定会被调用的函数
	void FinalRelease();

	// 计算IOleObject接口指针在COleImage类中的偏移量
	static DWORD GetIOleObjectOffset(void);

	// 根据IOleObjec接口指针得到COleImage的指针，其实就是减去前面的偏移量
	static COleImage *FromOleObject(IOleObject *lpOleObject);

	// 从文件加载，您也可以再添加一个从IStream加载的函数，这里只是演示而已
	HRESULT LoadFromFile(BSTR lpszPathName, CRichEditCtrl *pContainer, UINT nMaxWidth = 0);

	// 绘制函数
	HRESULT OnDraw(ATL_DRAWINFO& di);

	// 更换帧
	void ChangeFrame();

	// 这个函数一定要重写，可以不做任何事情，如果不写，双击插入的图像时会ASSERT失败
	STDMETHOD(DoVerb)(
		_In_ LONG /* iVerb */, 
		_In_opt_ LPMSG /* pMsg */, 
		_Inout_ IOleClientSite* /* pActiveSite */, 
		_In_ LONG /* lindex */,
		_In_ HWND /* hwndParent */, 
		_In_ LPCRECT /* lprcPosRect */)
	{
		return S_OK;
	}
};

OBJECT_ENTRY_AUTO(__uuidof(OleImage), COleImage)
