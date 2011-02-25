# Build the GMock vendor library
set(GMock_ROOT "${VENDOR_PREFIX}/src/gmock")

if(MSVC)
	set(gmock_lib_args -Dgtest_force_shared_crt=ON)
else()	
	set(gmock_lib_args "")
endif()

ExternalProject_Add(GMock
	PREFIX ${VENDOR_PREFIX}
	GIT_REPOSITORY https://github.com/anhstudios/gmock.git
	GIT_TAG 6f315ddc
	UPDATE_COMMAND ""
	BUILD_IN_SOURCE 1
	CMAKE_ARGS ${gmock_lib_args}
	INSTALL_COMMAND ""
)
