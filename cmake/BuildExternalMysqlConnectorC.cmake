# Build the MysqlConnectorC vendor library

set(mysql_c_source "${CMAKE_CURRENT_SOURCE_DIR}/vendor/mysql-connector-c")

ExternalProject_Add(mysql-connector-c
	PREFIX ${VENDOR_PREFIX}
	URL ${mysql_c_source}
	UPDATE_COMMAND ""
	PATCH_COMMAND ""
	CMAKE_ARGS
    	-DCMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG:PATH=${VENDOR_PREFIX}/src/mysql-connector-c-install/lib
    	-DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG:PATH=${VENDOR_PREFIX}/src/mysql-connector-c-install/lib
    	-DCMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE:PATH=${VENDOR_PREFIX}/src/mysql-connector-c-install/lib
    	-DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE:PATH=${VENDOR_PREFIX}/src/mysql-connector-c-install/lib
		-DCMAKE_INSTALL_PREFIX:PATH=${VENDOR_PREFIX}/src/mysql-connector-c-install
)

# Set the path to the built MysqlConnectorC for use by other projects
set(MysqlConnectorC_INCLUDE_DIR "${VENDOR_PREFIX}/src/mysql-connector-c-install/include/mysql" CACHE PATH "" FORCE)
set(MysqlConnectorC_LIBRARY_DIRS "${VENDOR_PREFIX}/src/mysql-connector-c-install/lib/mysql" CACHE PATH "" FORCE)
