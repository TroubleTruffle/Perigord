cmake_minimum_required (VERSION 3.19.0)
project ("Perigord")

find_package( OpenGL REQUIRED )

add_subdirectory(${PROJECT_SOURCE_DIR}/vendor/glfw )
add_subdirectory(${PROJECT_SOURCE_DIR}/vendor/glew )

add_subdirectory(src)

set(SHADERS
"${PROJECT_SOURCE_DIR}/resources/test.frag"
"${PROJECT_SOURCE_DIR}/resources/test.vert"
)

configure_file(
${PROJECT_SOURCE_DIR}/resources/test.frag 
${PROJECT_BINARY_DIR}/resources/test.frag
COPYONLY
)
configure_file(
${PROJECT_SOURCE_DIR}/resources/test.vert 
${PROJECT_BINARY_DIR}/resources/test.vert
COPYONLY
)
add_executable (${PROJECT_NAME} Main.cpp )

target_link_libraries("Perigord" PRIVATE
	${OPENGL_LIBRARIES} 
	glfw 
	libglew_static 
	src
)

