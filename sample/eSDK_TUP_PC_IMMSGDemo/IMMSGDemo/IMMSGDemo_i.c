

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Sat Aug 27 12:23:01 2016
 */
/* Compiler settings for IMMSGDemo.idl:
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

MIDL_DEFINE_GUID(IID, IID_IOleImage,0xC7DF1093,0xE590,0x4131,0x95,0xE2,0x62,0x4C,0x48,0x2B,0xA2,0xD7);


MIDL_DEFINE_GUID(IID, LIBID_IMMSGDemoLib,0xBEAD8F06,0xC8CB,0x425C,0x84,0x6F,0x96,0xDB,0xA9,0x2B,0x11,0x52);


MIDL_DEFINE_GUID(IID, DIID__IOleImageEvents,0xA57ADF29,0x4366,0x47FF,0xBB,0x72,0x25,0x04,0x03,0x9D,0xEF,0xF5);


MIDL_DEFINE_GUID(CLSID, CLSID_OleImage,0xBA505317,0x3075,0x43FD,0xB2,0x7B,0x68,0x72,0x08,0xED,0xBC,0x32);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif


