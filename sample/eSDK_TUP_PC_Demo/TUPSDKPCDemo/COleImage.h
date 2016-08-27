// COleImage.h : CCOleImage 的声明
#pragma once
#include "resource.h"       // 主符号
#include <atlctl.h>
#include "TUPSDKPCDemo_i.h"
#include "_ICOleImageEvents_CP.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE 平台(如不提供完全 DCOM 支持的 Windows Mobile 平台)上无法正确支持单线程 COM 对象。定义 _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA 可强制 ATL 支持创建单线程 COM 对象实现并允许使用其单线程 COM 对象实现。rgs 文件中的线程模型已被设置为“Free”，原因是该模型是非 DCOM Windows CE 平台支持的唯一线程模型。"
#endif


// CCOleImage
class ATL_NO_VTABLE CCOleImage :
	public CComObjectRootEx<CComSingleThreadModel>,
	public IDispatchImpl<ICOleImage, &IID_ICOleImage, &LIBID_TUPSDKPCDemoLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public IPersistStreamInitImpl<CCOleImage>,
	public IOleControlImpl<CCOleImage>,
	public IOleObjectImpl<CCOleImage>,
	public IOleInPlaceActiveObjectImpl<CCOleImage>,
	public IViewObjectExImpl<CCOleImage>,
	public IOleInPlaceObjectWindowlessImpl<CCOleImage>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CCOleImage>,
	public CProxy_ICOleImageEvents<CCOleImage>,
	public IPersistStorageImpl<CCOleImage>,
	public ISpecifyPropertyPagesImpl<CCOleImage>,
	public IQuickActivateImpl<CCOleImage>,
#ifndef _WIN32_WCE
	public IDataObjectImpl<CCOleImage>,
#endif
	public IProvideClassInfo2Impl<&CLSID_COleImage, &__uuidof(_ICOleImageEvents), &LIBID_TUPSDKPCDemoLib>,
#ifdef _WIN32_WCE // 要在 Windows CE 上正确加载该控件，要求 IObjectSafety
	public IObjectSafetyImpl<CCOleImage, INTERFACESAFE_FOR_UNTRUSTED_CALLER>,
#endif
	public CComCoClass<CCOleImage, &CLSID_COleImage>,
	public CComControl<CCOleImage>
{
public:


	CCOleImage()
	{
	}

DECLARE_OLEMISC_STATUS(OLEMISC_RECOMPOSEONRESIZE |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_INSIDEOUT |
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST
)

DECLARE_REGISTRY_RESOURCEID(IDR_COLEIMAGE)


BEGIN_COM_MAP(CCOleImage)
	COM_INTERFACE_ENTRY(ICOleImage)
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
	COM_INTERFACE_ENTRY(IPersistStreamInit)
	COM_INTERFACE_ENTRY2(IPersist, IPersistStreamInit)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY(ISpecifyPropertyPages)
	COM_INTERFACE_ENTRY(IQuickActivate)
	COM_INTERFACE_ENTRY(IPersistStorage)
#ifndef _WIN32_WCE
	COM_INTERFACE_ENTRY(IDataObject)
#endif
	COM_INTERFACE_ENTRY(IProvideClassInfo)
	COM_INTERFACE_ENTRY(IProvideClassInfo2)
#ifdef _WIN32_WCE // 要在 Windows CE 上正确加载该控件，要求 IObjectSafety
	COM_INTERFACE_ENTRY_IID(IID_IObjectSafety, IObjectSafety)
#endif
END_COM_MAP()

BEGIN_PROP_MAP(CCOleImage)
	PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
	PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
	// 示例项
	// PROP_ENTRY_TYPE("属性名", dispid, clsid, vtType)
	// PROP_PAGE(CLSID_StockColorPage)
END_PROP_MAP()

BEGIN_CONNECTION_POINT_MAP(CCOleImage)
	CONNECTION_POINT_ENTRY(__uuidof(_ICOleImageEvents))
END_CONNECTION_POINT_MAP()

BEGIN_MSG_MAP(CCOleImage)
	CHAIN_MSG_MAP(CComControl<CCOleImage>)
	DEFAULT_REFLECTION_HANDLER()
END_MSG_MAP()
// 处理程序原型:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid)
	{
		static const IID* arr[] =
		{
			&IID_ICOleImage,
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

// ICOleImage
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
	static CCOleImage *FromOleObject(IOleObject *lpOleObject);

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

OBJECT_ENTRY_AUTO(__uuidof(COleImage), CCOleImage)
