#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/ProfileServiceHandler.o \
	${OBJECTDIR}/src/ServerApp.o \
	${OBJECTDIR}/thrift-gen/ProfileService.o \
	${OBJECTDIR}/thrift-gen/profile_constants.o \
	${OBJECTDIR}/thrift-gen/profile_types.o

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/TestFiles/f3 \
	${TESTDIR}/TestFiles/f1 \
	${TESTDIR}/TestFiles/f2

# Test Object Files
TESTOBJECTFILES= \
	${TESTDIR}/test/ClientTest.o \
	${TESTDIR}/test/LRUCacheLogicTest.o \
	${TESTDIR}/test/LRUCachePerformanceTest.o

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=/usr/local/lib/libkyotocabinet.a /usr/local/lib/libboost_chrono.a /usr/local/lib/libboost_serialization.a /usr/local/lib/libboost_thread.a /usr/local/lib/libboost_system.a /usr/local/lib/libthrift.a /usr/local/lib/libthriftnb.a /usr/local/lib/libthriftz.a /usr/lib/x86_64-linux-gnu/libevent.a /usr/local/lib/libPocoUtil.a /usr/local/lib/libPocoJSON.a /usr/local/lib/libPocoNet.a /usr/local/lib/libPocoXML.a /usr/local/lib/libPocoFoundation.a -lpthread /usr/lib/x86_64-linux-gnu/libz.a /usr/lib/x86_64-linux-gnu/liblzma.a -llzo2

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/profile-service

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/profile-service: /usr/local/lib/libkyotocabinet.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/profile-service: /usr/local/lib/libboost_chrono.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/profile-service: /usr/local/lib/libboost_serialization.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/profile-service: /usr/local/lib/libboost_thread.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/profile-service: /usr/local/lib/libboost_system.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/profile-service: /usr/local/lib/libthrift.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/profile-service: /usr/local/lib/libthriftnb.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/profile-service: /usr/local/lib/libthriftz.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/profile-service: /usr/lib/x86_64-linux-gnu/libevent.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/profile-service: /usr/local/lib/libPocoUtil.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/profile-service: /usr/local/lib/libPocoJSON.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/profile-service: /usr/local/lib/libPocoNet.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/profile-service: /usr/local/lib/libPocoXML.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/profile-service: /usr/local/lib/libPocoFoundation.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/profile-service: /usr/lib/x86_64-linux-gnu/libz.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/profile-service: /usr/lib/x86_64-linux-gnu/liblzma.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/profile-service: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/profile-service ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/src/ProfileServiceHandler.o: src/ProfileServiceHandler.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/ProfileServiceHandler.o src/ProfileServiceHandler.cpp

${OBJECTDIR}/src/ServerApp.o: src/ServerApp.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/ServerApp.o src/ServerApp.cpp

${OBJECTDIR}/thrift-gen/ProfileService.o: thrift-gen/ProfileService.cpp
	${MKDIR} -p ${OBJECTDIR}/thrift-gen
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/thrift-gen/ProfileService.o thrift-gen/ProfileService.cpp

${OBJECTDIR}/thrift-gen/profile_constants.o: thrift-gen/profile_constants.cpp
	${MKDIR} -p ${OBJECTDIR}/thrift-gen
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/thrift-gen/profile_constants.o thrift-gen/profile_constants.cpp

${OBJECTDIR}/thrift-gen/profile_types.o: thrift-gen/profile_types.cpp
	${MKDIR} -p ${OBJECTDIR}/thrift-gen
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/thrift-gen/profile_types.o thrift-gen/profile_types.cpp

# Subprojects
.build-subprojects:

# Build Test Targets
.build-tests-conf: .build-tests-subprojects .build-conf ${TESTFILES}
.build-tests-subprojects:

${TESTDIR}/TestFiles/f3: ${TESTDIR}/test/ClientTest.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} -o ${TESTDIR}/TestFiles/f3 $^ ${LDLIBSOPTIONS}   

${TESTDIR}/TestFiles/f1: ${TESTDIR}/test/LRUCacheLogicTest.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} -o ${TESTDIR}/TestFiles/f1 $^ ${LDLIBSOPTIONS}   

${TESTDIR}/TestFiles/f2: ${TESTDIR}/test/LRUCachePerformanceTest.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} -o ${TESTDIR}/TestFiles/f2 $^ ${LDLIBSOPTIONS}   


${TESTDIR}/test/ClientTest.o: test/ClientTest.cpp 
	${MKDIR} -p ${TESTDIR}/test
	${RM} "$@.d"
	$(COMPILE.cc) -g -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${TESTDIR}/test/ClientTest.o test/ClientTest.cpp


${TESTDIR}/test/LRUCacheLogicTest.o: test/LRUCacheLogicTest.cpp 
	${MKDIR} -p ${TESTDIR}/test
	${RM} "$@.d"
	$(COMPILE.cc) -g -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${TESTDIR}/test/LRUCacheLogicTest.o test/LRUCacheLogicTest.cpp


${TESTDIR}/test/LRUCachePerformanceTest.o: test/LRUCachePerformanceTest.cpp 
	${MKDIR} -p ${TESTDIR}/test
	${RM} "$@.d"
	$(COMPILE.cc) -g -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${TESTDIR}/test/LRUCachePerformanceTest.o test/LRUCachePerformanceTest.cpp


${OBJECTDIR}/src/ProfileServiceHandler_nomain.o: ${OBJECTDIR}/src/ProfileServiceHandler.o src/ProfileServiceHandler.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/ProfileServiceHandler.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/ProfileServiceHandler_nomain.o src/ProfileServiceHandler.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/ProfileServiceHandler.o ${OBJECTDIR}/src/ProfileServiceHandler_nomain.o;\
	fi

${OBJECTDIR}/src/ServerApp_nomain.o: ${OBJECTDIR}/src/ServerApp.o src/ServerApp.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/ServerApp.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/ServerApp_nomain.o src/ServerApp.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/ServerApp.o ${OBJECTDIR}/src/ServerApp_nomain.o;\
	fi

${OBJECTDIR}/thrift-gen/ProfileService_nomain.o: ${OBJECTDIR}/thrift-gen/ProfileService.o thrift-gen/ProfileService.cpp 
	${MKDIR} -p ${OBJECTDIR}/thrift-gen
	@NMOUTPUT=`${NM} ${OBJECTDIR}/thrift-gen/ProfileService.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/thrift-gen/ProfileService_nomain.o thrift-gen/ProfileService.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/thrift-gen/ProfileService.o ${OBJECTDIR}/thrift-gen/ProfileService_nomain.o;\
	fi

${OBJECTDIR}/thrift-gen/profile_constants_nomain.o: ${OBJECTDIR}/thrift-gen/profile_constants.o thrift-gen/profile_constants.cpp 
	${MKDIR} -p ${OBJECTDIR}/thrift-gen
	@NMOUTPUT=`${NM} ${OBJECTDIR}/thrift-gen/profile_constants.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/thrift-gen/profile_constants_nomain.o thrift-gen/profile_constants.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/thrift-gen/profile_constants.o ${OBJECTDIR}/thrift-gen/profile_constants_nomain.o;\
	fi

${OBJECTDIR}/thrift-gen/profile_types_nomain.o: ${OBJECTDIR}/thrift-gen/profile_types.o thrift-gen/profile_types.cpp 
	${MKDIR} -p ${OBJECTDIR}/thrift-gen
	@NMOUTPUT=`${NM} ${OBJECTDIR}/thrift-gen/profile_types.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/thrift-gen/profile_types_nomain.o thrift-gen/profile_types.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/thrift-gen/profile_types.o ${OBJECTDIR}/thrift-gen/profile_types_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${TESTDIR}/TestFiles/f3 || true; \
	    ${TESTDIR}/TestFiles/f1 || true; \
	    ${TESTDIR}/TestFiles/f2 || true; \
	else  \
	    ./${TEST} || true; \
	fi

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
