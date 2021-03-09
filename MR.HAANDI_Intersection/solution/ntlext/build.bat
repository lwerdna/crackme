if "%1" == "RELEASE" goto release
if "%1" == "release" goto release
if "%1" == "CLEAN" goto clean
if "%1" == "clean" goto clean
:debug
echo DEBUG MODE!
if not exist debug mkdir debug
cl bn.cpp /c /Zi /Fo.\debug\main.obj /Fd.\debug\main.pdb
link /MACHINE:X86 /DLL /DEBUG /DEF:bn.def .\debug\main.obj dbgeng.lib c:\code\lib\miracl5.3.3\ms32.lib /OUT:.\debug\bn.dll
copy /Y .\debug\bn.dll "C:\program files\Debugging Tools for Windows (x86)\winext\bn.dll"
goto done
:release
echo RELEASE MODE!
if not exist release mkdir release
cl bn.cpp /c /O1 /Fo.\release\main.obj
link /MACHINE:X86 /DLL /DEF:bn.def .\release\main.obj dbgeng.lib c:\code\lib\miracl5.3.3\ms32.lib /OUT:.\release\bn.dll
copy /Y .\release\bn.dll "C:\program files\Debugging Tools for Windows (x86)\winext\bn.dll"
goto done
:clean
echo CLEAN!
if exist debug del /S /Q debug
if exist release del /S /Q release
goto done
:done


