
TUPSDKPCDemops.dll: dlldata.obj TUPSDKPCDemo_p.obj TUPSDKPCDemo_i.obj
	link /dll /out:TUPSDKPCDemops.dll /def:TUPSDKPCDemops.def /entry:DllMain dlldata.obj TUPSDKPCDemo_p.obj TUPSDKPCDemo_i.obj \
		kernel32.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \
.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del TUPSDKPCDemops.dll
	@del TUPSDKPCDemops.lib
	@del TUPSDKPCDemops.exp
	@del dlldata.obj
	@del TUPSDKPCDemo_p.obj
	@del TUPSDKPCDemo_i.obj
