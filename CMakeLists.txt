#
cmake_minimum_required(VERSION 3.16)


#
project("edsdkpp-demo")


#
#add_compile_options(-D TARGET_OS_LINUX)
add_compile_definitions(TARGET_OS_LINUX)

if(${CMAKE_SIZEOF_VOID_P} EQUAL 8)
	set(HOST_CPU ARM64)
else()
	set(HOST_CPU ARM32)
endif()


#
##
include_directories("lib/EDSDK/Header")
link_directories("lib/EDSDK/Library/${HOST_CPU}")
set(PRIVATE_LIBS
	${PRIVATE_LIBS}
	EDSDK
)

##
include_directories("include")


#
add_executable(${PROJECT_NAME}
	src/edsdkpp-demo/_edsdkpp-demo.cpp
)


#
target_link_libraries(${PROJECT_NAME} PRIVATE ${PRIVATE_LIBS})


#
set_target_properties(
	${PROJECT_NAME} PROPERTIES 
	CXX_STANDARD 20
	BUILD_RPATH "$ORIGIN"
	INSTALL_RPATH "$ORIGIN"
)
