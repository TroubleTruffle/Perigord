cmake_minimum_required (VERSION 3.19.0)
project ("Perigord")

find_package( OpenGL REQUIRED )

add_subdirectory(${PROJECT_SOURCE_DIR}/vendor/glfw )
add_subdirectory(${PROJECT_SOURCE_DIR}/vendor/glew )

add_subdirectory(src)

file(GLOB SHADERS "${PROJECT_SOURCE_DIR}/resources/*.frag" "${PROJECT_SOURCE_DIR}/resources/*.vert")
file(COPY ${SHADERS} DESTINATION ${PROJECT_BINARY_DIR}/resources)
add_executable (${PROJECT_NAME} Main.cpp )

target_link_libraries("Perigord" PRIVATE
	${OPENGL_LIBRARIES} 
	glfw 
	libglew_static 
	src
)
