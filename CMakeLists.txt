set(CMAKE_TOOLCHAIN_FILE "C:/dev/tools/vcpkg/scripts/buildsystems/vcpkg.cmake")
cmake_minimum_required (VERSION 3.19.0)
project ("Perigord")

find_package( OpenGL REQUIRED )

add_subdirectory(${PROJECT_SOURCE_DIR}/vendor/glfw )
add_subdirectory(${PROJECT_SOURCE_DIR}/vendor/glew )
add_subdirectory(src)

add_executable (${PROJECT_NAME} Main.cpp )

target_link_libraries("Perigord" PRIVATE
	${OPENGL_LIBRARIES} 
	glfw 
	libglew_static 

	"Source"
)

