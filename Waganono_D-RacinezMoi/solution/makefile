.SUFFIXES :

COMPILE_FLAGS=/c \
        /Ic:\openssl-0.9.8g \
        /Ic:\openssl-0.9.8g\include \
        /D_CRT_SECURE_NO_DEPRECATE=1 \
        /Zi

LINKFLAGS= c:\openssl-0.9.8g\out32dll\libeay32.lib \
            user32.lib \
        /debug

default: keygen.exe

keygen.exe: keygen.obj extended_euclidean.obj chinese_remainder_theorem.obj quadratic_residue.obj hash_breaker.obj misc_rips.obj transforms.obj
	link keygen.obj \
        extended_euclidean.obj \
        transforms.obj \
        hash_breaker.obj \
        misc_rips.obj \
        chinese_remainder_theorem.obj \
        quadratic_residue.obj \
        $(LINKFLAGS)

transforms.obj: transforms.cpp
    cl transforms.cpp $(COMPILE_FLAGS)

quadratic_residue.obj: quadratic_residue.cpp
    cl quadratic_residue.cpp $(COMPILE_FLAGS)

misc_rips.obj: misc_rips.cpp
    cl misc_rips.cpp $(COMPILE_FLAGS)

hash_breaker.obj: hash_breaker.cpp
    cl hash_breaker.cpp $(COMPILE_FLAGS)

keygen.obj: keygen.cpp
    cl keygen.cpp $(COMPILE_FLAGS)

extended_euclidean.obj: extended_euclidean.cpp
    cl extended_euclidean.cpp $(COMPILE_FLAGS)

chinese_remainder_theorem.obj: chinese_remainder_theorem.cpp
	cl chinese_remainder_theorem.cpp $(COMPILE_FLAGS)

clean:
	del *.obj
	del *.exe
	del *.pdb
    del *.ilk
    del *~

