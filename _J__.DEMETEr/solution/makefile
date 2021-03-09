.SUFFIXES:

default: rips.obj main.obj
    link rips.obj main.obj /OUT:keygen.exe C:\openssl-0.9.8g\out32dll\libeay32.lib user32.lib

rips.obj: rips.cpp
    cl /c rips.cpp /IC:\openssl-0.9.8g\include /IC:\openssl-0.9.8g

main.obj: main.cpp
    cl /c main.cpp /IC:\openssl-0.9.8g\include /IC:\openssl-0.9.8g

clean:
	del *.obj *~ *.pdb 

