# Build the GTest vendor library
set(GTest_ROOT "${VENDOR_PREFIX}/src/GTest")

if(MSVC)
	set(gtest_lib_args
		-Dgtest_force_shared_crt=ON
	)
else()	
	set(gtest_lib_args)
endif()

ExternalProject_Add(GTest
	PREFIX ${VENDOR_PREFIX}	
	GIT_REPOSITORY https://github.com/anhstudios/gtest.git
	GIT_TAG 9b0cb547
	UPDATE_COMMAND ""
	PATCH_COMMAND ""
	BUILD_IN_SOURCE 1
	CMAKE_ARGS
		${gtest_lib_args}
	INSTALL_COMMAND ""
)

