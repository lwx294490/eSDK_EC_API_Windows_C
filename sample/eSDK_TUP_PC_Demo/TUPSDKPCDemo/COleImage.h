// COleImage.h : CCOleImage ������
#pragma once
#include "resource.h"       // ������
#include <atlctl.h>
#include "TUPSDKPCDemo_i.h"
#include "_ICOleImageEvents_CP.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE ƽ̨(�粻�ṩ��ȫ DCOM ֧�ֵ� Windows Mobile ƽ̨)���޷���ȷ֧�ֵ��߳� COM ���󡣶��� _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA ��ǿ�� ATL ֧�ִ������߳� COM ����ʵ�ֲ�����ʹ���䵥�߳� COM ����ʵ�֡�rgs �ļ��е��߳�ģ���ѱ�����Ϊ��Free����ԭ���Ǹ�ģ���Ƿ� DCOM Windows CE ƽ̨֧�ֵ�Ψһ�߳�ģ�͡�"
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
#ifdef _WIN32_WCE // Ҫ�� Windows CE ����ȷ���ظÿؼ���Ҫ�� IObjectSafety
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
#ifdef _WIN32_WCE // Ҫ�� Windows CE ����ȷ���ظÿؼ���Ҫ�� IObjectSafety
	COM_INTERFACE_ENTRY_IID(IID_IObjectSafety, IObjectSafety)
#endif
END_COM_MAP()

BEGIN_PROP_MAP(CCOleImage)
	PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
	PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
	// ʾ����
	// PROP_ENTRY_TYPE("������", dispid, clsid, vtType)
	// PROP_PAGE(CLSID_StockColorPage)
END_PROP_MAP()

BEGIN_CONNECTION_POINT_MAP(CCOleImage)
	CONNECTION_POINT_ENTRY(__uuidof(_ICOleImageEvents))
END_CONNECTION_POINT_MAP()

BEGIN_MSG_MAP(CCOleImage)
	CHAIN_MSG_MAP(CComControl<CCOleImage>)
	DEFAULT_REFLECTION_HANDLER()
END_MSG_MAP()
// �������ԭ��:
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
	// ��С��֡��ʱ
#define MIN_FRM_DELAY				100

private:
	CDC *m_pDCs; // ÿ֡��DC
	CBitmap *m_pBitmaps; // ÿһ֡��λͼ
	CBitmap **m_ppOldBmps; // ����ÿһ֡DC�ɵ�λͼ
	int *m_pFrmIndexes; // ÿ��100�����Ӧ��֡����
	int m_nFrmCount; // ��֡��
	int m_nTimeCount; // 100���������������GIF����֡�������ܵ��ӳ���1�룬�����ֵΪ10
	volatile int m_iPrevFrm; // ǰһ֡����ʱ������ʱ�����ж��Ƿ���Ҫ�Ļ�֡
	volatile int m_iCurTime; // ��ǰʱ�䣨���ڼ���100���룩
	CRichEditCtrl *m_pContainer; // ��������ָ��
	static DWORD m_dwOleObjectOffset; // IOleObject�ӿ�ָ�����COleImage��ʼ��ַ��ƫ����
public:
	// ʵ������һ���ᱻ���õĺ���
	HRESULT FinalConstruct();

	// ɾ��ʵ��ǰһ���ᱻ���õĺ���
	void FinalRelease();

	// ����IOleObject�ӿ�ָ����COleImage���е�ƫ����
	static DWORD GetIOleObjectOffset(void);

	// ����IOleObjec�ӿ�ָ��õ�COleImage��ָ�룬��ʵ���Ǽ�ȥǰ���ƫ����
	static CCOleImage *FromOleObject(IOleObject *lpOleObject);

	// ���ļ����أ���Ҳ���������һ����IStream���صĺ���������ֻ����ʾ����
	HRESULT LoadFromFile(BSTR lpszPathName, CRichEditCtrl *pContainer, UINT nMaxWidth = 0);

	// ���ƺ���
	HRESULT OnDraw(ATL_DRAWINFO& di);

	// ����֡
	void ChangeFrame();

	// �������һ��Ҫ��д�����Բ����κ����飬�����д��˫�������ͼ��ʱ��ASSERTʧ��
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
