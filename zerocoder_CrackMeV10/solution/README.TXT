
solution.txt            notes for solving the crackme

disasm.cpp              disassembles "VM" instructions from crackme

crackme.h               original crackme bytes (used by searchers)
search0.cpp             to find possible ascii goodboys
search1.cpp             to find remaining checksum bytes given goodboy of "True. "
search2.cpp             randomly adaptive bruter of password to produce checksum bytes from search1 ...FAILS!
search3.cpp             -random +BRUTAL bruter of password to produce checksum bytes from search1 ...WORKS!

CRACKM10.COM            original crackme
zRACKM10.COM            patched crackme (mods described in solution)

CRACKM10.MAP            namings for addresses (loadable in IDA)

README.TXT              this!