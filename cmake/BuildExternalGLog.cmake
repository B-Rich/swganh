# Build the GLog vendor library
set(GLog_SOURCEDIR "${VENDOR_PREFIX}/src/GLog")

if(WIN32)
    set(glog_configure "")
	set(glog_build msbuild "${GLog_SOURCEDIR}/google-glog_vc10.sln")
    set(glog_install "")

    set(GLog_INCLUDEDIR "${GLog_SOURCEDIR}/src/GLog/src/windows")
    set(GLog_LIBRARYDIR "${VENDOR_PREFIX}/src/GLog")
else()
    set(glog_configure ${GLog_SOURCEDIR}/configure --prefix=${GLog_SOURCEDIR})
	set(glog_build make)
    set(glog_install make install)


    set(GLog_INCLUDEDIR "${VENDOR_PREFIX}/src/GLog/include")
    set(GLog_LIBRARYDIR "${VENDOR_PREFIX}/src/GLog/lib")
endif()

ExternalProject_Add(GLog
	PREFIX ${VENDOR_PREFIX}
	GIT_REPOSITORY https://github.com/anhstudios/glog.git
	GIT_TAG 92b92d0e
	UPDATE_COMMAND ""
	BUILD_IN_SOURCE 1
	CONFIGURE_COMMAND "${glog_configure}"
	BUILD_COMMAND ${glog_build}
	INSTALL_COMMAND ${glog_install}
)
