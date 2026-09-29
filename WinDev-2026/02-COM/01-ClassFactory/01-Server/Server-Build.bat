cls

del *.dll

del *.exp

del *.obj

del *.lib

cl.exe /c /EHsc ClassFactoryDllServerWithRegFile.cpp

link.exe ClassFactoryDllServerWithRegFile.obj /DLL /DEF:ClassFactoryDllServerWithRegFile.def user32.lib /SUBSYSTEM:WINDOWS
