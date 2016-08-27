
IMMSGDemops.dll: dlldata.obj IMMSGDemo_p.obj IMMSGDemo_i.obj
	link /dll /out:IMMSGDemops.dll /def:IMMSGDemops.def /entry:DllMain dlldata.obj IMMSGDemo_p.obj IMMSGDemo_i.obj \
		kernel32.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \
.c.obj:
	cl /c /Ox /DREGISTER_PROXY_DLL \
		$<

clean:
	@del IMMSGDemops.dll
	@del IMMSGDemops.lib
	@del IMMSGDemops.exp
	@del dlldata.obj
	@del IMMSGDemo_p.obj
	@del IMMSGDemo_i.obj
