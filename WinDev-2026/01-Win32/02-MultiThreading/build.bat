cls

del *.exe

del *.res

del *.obj

cl.exe /c /EHsc /D UNICODE Window.c

rc.exe Window.rc

link.exe Window.obj Window.res user32.lib gdi32.lib /SUBSYSTEM:WINDOWS
