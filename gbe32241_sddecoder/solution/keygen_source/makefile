default: attack.exe keygen.exe 

bitvects.obj: bitvects.cpp bitvects.h
	cl bitvects.cpp /O1 /c

random.obj: random.cpp
	cl random.cpp /O1 /c

common.obj: common.cpp
	cl common.cpp /O1 /c

gf2.obj: gf2.cpp
	cl gf2.cpp /O1 /c

attack.obj: attack.cpp
	cl attack.cpp /O1 /c

keygen.obj: keygen.cpp
	cl keygen.cpp /O1 /c

fevaluate.obj: fevaluate.cpp fevaluate.h
    cl fevaluate.cpp /O1 /c

attack.exe: bitvects.obj attack.obj random.obj common.obj fevaluate.obj gf2.obj
	link bitvects.obj random.obj attack.obj common.obj advapi32.lib fevaluate.obj gf2.obj /OUT:attack.exe /DEBUG

keygen.exe: bitvects.obj keygen.obj random.obj common.obj fevaluate.obj gf2.obj
	link bitvects.obj random.obj keygen.obj common.obj advapi32.lib fevaluate.obj gf2.obj /OUT:keygen.exe /DEBUG

clean:
	del *.obj *.pdb *.ilk *.exe

