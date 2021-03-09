SET BUILDITBAT_UPX=NO

if "%1" == "" goto release
if "%1" == "help" goto help
if "%1" == "debug" goto debug
if "%1" == "upx" goto upx
if "%1" == "clean" goto clean

:upx
SET BUILDITBAT_UPX=YES
goto release

:help
echo BAT FILE BUILDER, BABY!
echo "build debug" - for exe with debugging info
echo "build release" - for release build
echo "build upx" - release, then UPX ultra-brute
echo "build clean" - to delete temp files
echo.
goto end

:debug
echo DEBUG BUILD
rc myresource.rc
cl keygen.cpp /Od /Zi /GS- /Oi- -c
link /NODEFAULTLIB /ENTRY:MyEntry /SUBSYSTEM:WINDOWS keygen.obj myresource.res user32.lib Kernel32.lib comdlg32.lib /DEBUG 
goto end

:release
echo RELEASE BUILD
rc myresource.rc
cl keygen.cpp /Ox /GS- /Oi- -c
link /NODEFAULTLIB /ENTRY:MyEntry /SUBSYSTEM:WINDOWS keygen.obj myresource.res user32.lib Kernel32.lib comdlg32.lib
if "%BUILDITBAT_UPX%" == "YES" upx keygen.exe --ultra-brute
goto end

:clean
del *~ *.swp *.pdb *.RES *.obj *.ilk *.exe *.swo

goto end

:end


