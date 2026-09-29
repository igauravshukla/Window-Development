cls

del *.dll

del *.exp

del *.obj

del *.lib

cl.exe /c /EHsc MyMathTwo.cpp

link.exe MyMathTwo.obj /DLL /DEF:MyMathTwo.def user32.lib /SUBSYSTEM:WINDOWS
