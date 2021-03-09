!INCLUDE $(PATH_FUNCODE)\build\vars_shared.mak

# ADDITIONAL COMPILE FLAGS
CPPFLAGS = $(CPPFLAGS)

# ADDITIONAL LINK FLAGS
LINKFLAGS = $(LINKFLAGS)

# THINGS TO BUILD LOCALLY
OBJS = $(OUTDIR)\myresource.res

# RECURSIVELY BUILD DEPENDENCIES

#RECDIRSPREBUILD = 
!UNDEF RECDIRSPREBUILD
!UNDEF RECDIRSPOSTBUILD
#= test GenerateDictionaryFiles

# CUSTOM INFERENCE RULES
!INCLUDE $(PATH_FUNCODE)\build\inference_shared.mak

# TARGETS
default: setupdirs prebuild $(OBJS) postbuild
     
$(OUTDIR)\myresource.res: myresource.rc
    rc /fo .\$(OUTDIR)\myresource.res myresource.rc

!INCLUDE $(PATH_FUNCODE)\build\targets_shared.mak


