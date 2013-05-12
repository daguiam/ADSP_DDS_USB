# Generated by the VisualDSP++ IDDE

# Note:  Any changes made to this Makefile will be lost the next time the
# matching project file is loaded into the IDDE.  If you wish to preserve
# changes, rename this file and run it externally to the IDDE.

# The syntax of this Makefile is such that GNU Make v3.77 or higher is
# required.

# The current working directory should be the directory in which this
# Makefile resides.

# Supported targets:
#     Test ADSP21369_Debug
#     Test ADSP21369_Debug_clean

# Define this variable if you wish to run this Makefile on a host
# other than the host that created it and VisualDSP++ may be installed
# in a different directory.

ADI_DSP=C:\Program Files (x86)\Analog Devices\VisualDSP 5.0


# $VDSP is a gmake-friendly version of ADI_DIR

empty:=
space:= $(empty) $(empty)
VDSP_INTERMEDIATE=$(subst \,/,$(ADI_DSP))
VDSP=$(subst $(space),\$(space),$(VDSP_INTERMEDIATE))

RM=cmd /C del /F /Q

#
# Begin "Test ADSP21369_Debug" configuration
#

ifeq ($(MAKECMDGOALS),Test ADSP21369_Debug)

Test\ ADSP21369_Debug : ./Debug/Test\ ADSP21369.dxe 

Debug/configADC.doj :src/configADC.c h/configADC.h h/general.h $(VDSP)/213xx/include/Cdef21369.h $(VDSP)/213xx/include/def21369.h $(VDSP)/213xx/include/stdio.h $(VDSP)/213xx/include/stdio_21xxx.h $(VDSP)/213xx/include/sysreg.h $(VDSP)/213xx/include/signal.h $(VDSP)/213xx/include/sru.h $(VDSP)/213xx/include/sru21369.h h/configDDS.h 
	@echo ".\src\configADC.c"
	$(VDSP)/cc21k.exe -c .\src\configADC.c -file-attr ProjectName=Test\ ADSP21369 -g -structs-do-not-overlap -no-multiline -double-size-32 -warn-protos -si-revision 0.2 -proc ADSP-21369 -o .\Debug\configADC.doj -MM

Debug/configDDS.doj :src/configDDS.c h/configDDS.h h/general.h $(VDSP)/213xx/include/Cdef21369.h $(VDSP)/213xx/include/def21369.h $(VDSP)/213xx/include/stdio.h $(VDSP)/213xx/include/stdio_21xxx.h $(VDSP)/213xx/include/sysreg.h $(VDSP)/213xx/include/signal.h $(VDSP)/213xx/include/sru.h $(VDSP)/213xx/include/sru21369.h h/configADC.h 
	@echo ".\src\configDDS.c"
	$(VDSP)/cc21k.exe -c .\src\configDDS.c -file-attr ProjectName=Test\ ADSP21369 -g -structs-do-not-overlap -no-multiline -double-size-32 -warn-protos -si-revision 0.2 -proc ADSP-21369 -o .\Debug\configDDS.doj -MM

Debug/configUSB.doj :src/configUSB.c h/configUSB.h h/general.h $(VDSP)/213xx/include/Cdef21369.h $(VDSP)/213xx/include/def21369.h $(VDSP)/213xx/include/stdio.h $(VDSP)/213xx/include/stdio_21xxx.h $(VDSP)/213xx/include/sysreg.h $(VDSP)/213xx/include/signal.h $(VDSP)/213xx/include/sru.h $(VDSP)/213xx/include/sru21369.h h/configDDS.h h/configADC.h 
	@echo ".\src\configUSB.c"
	$(VDSP)/cc21k.exe -c .\src\configUSB.c -file-attr ProjectName=Test\ ADSP21369 -g -structs-do-not-overlap -no-multiline -double-size-32 -warn-protos -si-revision 0.2 -proc ADSP-21369 -o .\Debug\configUSB.doj -MM

Debug/initPLL_SDRAM.doj :initPLL_SDRAM.c $(VDSP)/213xx/include/def21369.h $(VDSP)/213xx/include/cdef21369.h 
	@echo ".\initPLL_SDRAM.c"
	$(VDSP)/cc21k.exe -c .\initPLL_SDRAM.c -file-attr ProjectName=Test\ ADSP21369 -g -structs-do-not-overlap -no-multiline -double-size-32 -warn-protos -si-revision 0.2 -proc ADSP-21369 -o .\Debug\initPLL_SDRAM.doj -MM

Debug/Test\ ADSP21369.doj :Test\ ADSP21369.c h/general.h $(VDSP)/213xx/include/Cdef21369.h $(VDSP)/213xx/include/def21369.h $(VDSP)/213xx/include/stdio.h $(VDSP)/213xx/include/stdio_21xxx.h $(VDSP)/213xx/include/sysreg.h $(VDSP)/213xx/include/signal.h $(VDSP)/213xx/include/sru.h $(VDSP)/213xx/include/sru21369.h h/configDDS.h h/configADC.h 
	@echo ".\Test ADSP21369.c"
	$(VDSP)/cc21k.exe -c .\Test\ ADSP21369.c -file-attr ProjectName=Test\ ADSP21369 -g -structs-do-not-overlap -no-multiline -double-size-32 -warn-protos -si-revision 0.2 -proc ADSP-21369 -o .\Debug\Test\ ADSP21369.doj -MM

./Debug/Test\ ADSP21369.dxe :$(VDSP)/213xx/ldf/ADSP-21369.LDF $(VDSP)/213xx/lib/2136x_LX3_rev_0.1/369_hdr.doj ./Debug/configADC.doj ./Debug/configDDS.doj ./Debug/configUSB.doj ./Debug/initPLL_SDRAM.doj ./Debug/Test\ ADSP21369.doj $(VDSP)/213xx/lib/2136x_LX3_rev_0.1/libc36x.dlb $(VDSP)/213xx/lib/2136x_LX3_rev_0.1/libio.dlb $(VDSP)/213xx/lib/2136x_LX3_rev_0.1/libdsp36x.dlb $(VDSP)/213xx/lib/2136x_LX3_rev_0.1/libcpp.dlb 
	@echo "Linking..."
	$(VDSP)/cc21k.exe .\Debug\configADC.doj .\Debug\configDDS.doj .\Debug\configUSB.doj .\Debug\initPLL_SDRAM.doj .\Debug\Test\ ADSP21369.doj -L .\Debug -add-debug-libpaths -flags-link -od,.\Debug -o .\Debug\Test\ ADSP21369.dxe -proc ADSP-21369 -si-revision 0.2 -MM

endif

ifeq ($(MAKECMDGOALS),Test ADSP21369_Debug_clean)

Test\ ADSP21369_Debug_clean:
	-$(RM) "Debug\configADC.doj"
	-$(RM) "Debug\configDDS.doj"
	-$(RM) "Debug\configUSB.doj"
	-$(RM) "Debug\initPLL_SDRAM.doj"
	-$(RM) "Debug\Test ADSP21369.doj"
	-$(RM) ".\Debug\Test ADSP21369.dxe"
	-$(RM) ".\Debug\*.ipa"
	-$(RM) ".\Debug\*.opa"
	-$(RM) ".\Debug\*.ti"
	-$(RM) ".\Debug\*.pgi"
	-$(RM) ".\*.rbld"

endif


