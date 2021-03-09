goto release

:debug
cl md5.c /c /Zi
cl keygen.cpp /c /Zi
link md5.obj keygen.obj /OUT:keygen.exe /DEBUG
goto end

:release
cl md5.c /c /O1
cl keygen.cpp /c /O1
link md5.obj keygen.obj /OUT:keygen.exe
goto end

:end
