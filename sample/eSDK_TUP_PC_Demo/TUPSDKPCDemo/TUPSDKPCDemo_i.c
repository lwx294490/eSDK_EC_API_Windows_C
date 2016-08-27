

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Sat Aug 27 11:41:17 2016
 */
/* Compiler settings for TUPSDKPCDemo.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 7.00.0555 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, IID_ICOleImage,0x5084A7FF,0x1121,0x42A7,0xB7,0x96,0xFC,0x97,0xF1,0x85,0x1D,0x79);


MIDL_DEFINE_GUID(IID, LIBID_TUPSDKPCDemoLib,0xA51B0FB4,0xD3A5,0x4593,0xBD,0x55,0xE3,0xA7,0x72,0xD1,0x1E,0xE7);


MIDL_DEFINE_GUID(IID, DIID__ICOleImageEvents,0xD0F24195,0xEC44,0x4BC3,0xA2,0xE9,0x78,0x31,0x49,0x48,0x6F,0x0D);


MIDL_DEFINE_GUID(CLSID, CLSID_COleImage,0xDC0C8980,0xE8F0,0x4172,0xAF,0xA9,0x7D,0xC4,0xA6,0x66,0xCD,0xF4);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



