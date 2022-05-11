#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/Libraries.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/Libraries.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS
SUB_IMAGE_ADDRESS_COMMAND=--image-address $(SUB_IMAGE_ADDRESS)
else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=lib/BasicLibrary/BasicLibrary_dsPIC33FJ128MC802.c lib/EEPROM/EEPROM.c lib/Queue/Queue.c main.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/lib/BasicLibrary/BasicLibrary_dsPIC33FJ128MC802.o ${OBJECTDIR}/lib/EEPROM/EEPROM.o ${OBJECTDIR}/lib/Queue/Queue.o ${OBJECTDIR}/main.o
POSSIBLE_DEPFILES=${OBJECTDIR}/lib/BasicLibrary/BasicLibrary_dsPIC33FJ128MC802.o.d ${OBJECTDIR}/lib/EEPROM/EEPROM.o.d ${OBJECTDIR}/lib/Queue/Queue.o.d ${OBJECTDIR}/main.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/lib/BasicLibrary/BasicLibrary_dsPIC33FJ128MC802.o ${OBJECTDIR}/lib/EEPROM/EEPROM.o ${OBJECTDIR}/lib/Queue/Queue.o ${OBJECTDIR}/main.o

# Source Files
SOURCEFILES=lib/BasicLibrary/BasicLibrary_dsPIC33FJ128MC802.c lib/EEPROM/EEPROM.c lib/Queue/Queue.c main.c



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/Libraries.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=33FJ128MC802
MP_LINKER_FILE_OPTION=,--script=p33FJ128MC802.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/lib/BasicLibrary/BasicLibrary_dsPIC33FJ128MC802.o: lib/BasicLibrary/BasicLibrary_dsPIC33FJ128MC802.c  .generated_files/flags/default/fec09b85215dc35db72016d3a6f8a8e1d89a4af .generated_files/flags/default/74d464f3899599845d713a1d015fd0bf2695bd19
	@${MKDIR} "${OBJECTDIR}/lib/BasicLibrary" 
	@${RM} ${OBJECTDIR}/lib/BasicLibrary/BasicLibrary_dsPIC33FJ128MC802.o.d 
	@${RM} ${OBJECTDIR}/lib/BasicLibrary/BasicLibrary_dsPIC33FJ128MC802.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib/BasicLibrary/BasicLibrary_dsPIC33FJ128MC802.c  -o ${OBJECTDIR}/lib/BasicLibrary/BasicLibrary_dsPIC33FJ128MC802.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/lib/BasicLibrary/BasicLibrary_dsPIC33FJ128MC802.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/lib/EEPROM/EEPROM.o: lib/EEPROM/EEPROM.c  .generated_files/flags/default/94a2007556aa8e70fe9c456875efac7190558586 .generated_files/flags/default/74d464f3899599845d713a1d015fd0bf2695bd19
	@${MKDIR} "${OBJECTDIR}/lib/EEPROM" 
	@${RM} ${OBJECTDIR}/lib/EEPROM/EEPROM.o.d 
	@${RM} ${OBJECTDIR}/lib/EEPROM/EEPROM.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib/EEPROM/EEPROM.c  -o ${OBJECTDIR}/lib/EEPROM/EEPROM.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/lib/EEPROM/EEPROM.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/lib/Queue/Queue.o: lib/Queue/Queue.c  .generated_files/flags/default/6b92620d0a58177c1746222b0eccd977d9a7a30e .generated_files/flags/default/74d464f3899599845d713a1d015fd0bf2695bd19
	@${MKDIR} "${OBJECTDIR}/lib/Queue" 
	@${RM} ${OBJECTDIR}/lib/Queue/Queue.o.d 
	@${RM} ${OBJECTDIR}/lib/Queue/Queue.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib/Queue/Queue.c  -o ${OBJECTDIR}/lib/Queue/Queue.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/lib/Queue/Queue.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/main.o: main.c  .generated_files/flags/default/4a7f10c0ebd7b7ab1b78761b0a01de1baa13befd .generated_files/flags/default/74d464f3899599845d713a1d015fd0bf2695bd19
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/main.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
else
${OBJECTDIR}/lib/BasicLibrary/BasicLibrary_dsPIC33FJ128MC802.o: lib/BasicLibrary/BasicLibrary_dsPIC33FJ128MC802.c  .generated_files/flags/default/4ccd15660ca42c6dd24af77c5c2edc7ed7f0955a .generated_files/flags/default/74d464f3899599845d713a1d015fd0bf2695bd19
	@${MKDIR} "${OBJECTDIR}/lib/BasicLibrary" 
	@${RM} ${OBJECTDIR}/lib/BasicLibrary/BasicLibrary_dsPIC33FJ128MC802.o.d 
	@${RM} ${OBJECTDIR}/lib/BasicLibrary/BasicLibrary_dsPIC33FJ128MC802.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib/BasicLibrary/BasicLibrary_dsPIC33FJ128MC802.c  -o ${OBJECTDIR}/lib/BasicLibrary/BasicLibrary_dsPIC33FJ128MC802.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/lib/BasicLibrary/BasicLibrary_dsPIC33FJ128MC802.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/lib/EEPROM/EEPROM.o: lib/EEPROM/EEPROM.c  .generated_files/flags/default/dd0b81adddb0d65ff0ac80d4b91c3519cad5671f .generated_files/flags/default/74d464f3899599845d713a1d015fd0bf2695bd19
	@${MKDIR} "${OBJECTDIR}/lib/EEPROM" 
	@${RM} ${OBJECTDIR}/lib/EEPROM/EEPROM.o.d 
	@${RM} ${OBJECTDIR}/lib/EEPROM/EEPROM.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib/EEPROM/EEPROM.c  -o ${OBJECTDIR}/lib/EEPROM/EEPROM.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/lib/EEPROM/EEPROM.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/lib/Queue/Queue.o: lib/Queue/Queue.c  .generated_files/flags/default/b5217aa3f7a4ba094266ffc56860cf90827a6a97 .generated_files/flags/default/74d464f3899599845d713a1d015fd0bf2695bd19
	@${MKDIR} "${OBJECTDIR}/lib/Queue" 
	@${RM} ${OBJECTDIR}/lib/Queue/Queue.o.d 
	@${RM} ${OBJECTDIR}/lib/Queue/Queue.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib/Queue/Queue.c  -o ${OBJECTDIR}/lib/Queue/Queue.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/lib/Queue/Queue.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/main.o: main.c  .generated_files/flags/default/fcb6fecf2ebd2c29907b8837bc06943730809c11 .generated_files/flags/default/74d464f3899599845d713a1d015fd0bf2695bd19
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/main.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/Libraries.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o ${DISTDIR}/Libraries.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG=__DEBUG   -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)      -Wl,,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D__DEBUG=__DEBUG,,$(MP_LINKER_FILE_OPTION),--heap=200,--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,${DISTDIR}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	
else
${DISTDIR}/Libraries.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o ${DISTDIR}/Libraries.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--heap=200,--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,${DISTDIR}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	${MP_CC_DIR}\\xc16-bin2hex ${DISTDIR}/Libraries.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf   -mdfp="${DFP_DIR}/xc16" 
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${OBJECTDIR}
	${RM} -r ${DISTDIR}

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
