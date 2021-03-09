!INCLUDE $(PATH_FUNCODE)\build\vars_shared.mak

# ADDITIONAL COMPILE FLAGS
CPPFLAGS = $(CPPFLAGS) \
            /I$(PATH_FUNCODE)\lib\FunWindowsHelpers \
            /I$(PATH_FUNCODE)\lib\FunKGTools \
            /Oi-

# ADDITIONAL LINK FLAGS
LINKFLAGS = $(LINKFLAGS) \
            /INCREMENTAL:NO \
            /SUBSYSTEM:WINDOWS \
            $(PATH_FUNCODE)\lib\FunWindowsHelpers\$(OUTDIR)\FunWindowsHelpers.obj \
            $(PATH_FUNCODE)\lib\FunKGTools\$(OUTDIR)\Executer.obj \
            gdi32.lib \
            kernel32.lib \
            Comdlg32.lib \
            user32.lib \
			/DLL

# THINGS TO BUILD LOCALLY
OBJS = $(OUTDIR)\keygen.obj

# RECURSIVELY BUILD DEPENDENCIES

#RECDIRSPREBUILD = 
RECDIRSPREBUILD=resource
!UNDEF RECDIRSPOSTBUILD 

# CUSTOM INFERENCE RULES
!INCLUDE $(PATH_FUNCODE)\build\inference_shared.mak

# TARGETS
default: setupdirs prebuild $(OUTDIR)\keygen.exe postbuild
     
$(OUTDIR)\keygen.exe: $(OBJS) .\resource\$(OUTDIR)\myresource.res
    link $(LINKFLAGS) $(OBJS) .\resource\$(OUTDIR)\myresource.res /OUT:.\$(OUTDIR)\keygen.dll

!INCLUDE $(PATH_FUNCODE)\build\targets_shared.mak


