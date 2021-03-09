!INCLUDE $(PATH_FUNCODE)\build\vars_shared.mak

# ADDITIONAL COMPILE FLAGS
CPPFLAGS = $(CPPFLAGS) \
		   /I$(PATH_OPENSSL) \
		   /I$(PATH_FUNCODE)\lib\miracl5.3.3\include \
           /I$(PATH_FUNCODE)\lib\funcrypto\md5 \
		   /D_CRT_SECURE_NO_DEPRECATE=1

# ADDITIONAL LINK FLAGS
LINKFLAGS = $(LINKFLAGS) \
			$(PATH_FUNCODE)\lib\miracl5.3.3\ms32.lib \
			$(PATH_FUNCODE)\lib\funcrypto\md5\$(OUTDIR)\md5.obj \
			/SUBSYSTEM:CONSOLE \
			/NODEFAULTLIB:libc.lib \
			user32.lib

# THINGS TO BUILD LOCALLY
OBJS = $(OUTDIR)\keygen.obj

# RECURSIVELY BUILD DEPENDENCIES
!UNDEF RECDIRSPREBUILD
!UNDEF RECDIRSPOSTBUILD

# CUSTOM INFERENCE RULES
!INCLUDE $(PATH_FUNCODE)\build\inference_shared.mak

# TARGETS
default: setupdirs prebuild $(OUTDIR)\keygen.exe postbuild
       
$(OUTDIR)\keygen.exe: $(OBJS)
    link $(LINKFLAGS) $(OBJS) /OUT:$(OUTDIR)\keygen.exe

!INCLUDE $(PATH_FUNCODE)\build\targets_shared.mak

