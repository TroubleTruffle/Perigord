Set(OPENGL_RENDERER_FILES
"Shader.cpp"
)

add_library("PG_OpenGL" STATIC ${OPENGL_RENDERER_FILES} "Shader.h")

target_include_directories(	"PG_OpenGL" PUBLIC
	${OPENGL_INCLUDE_DIRS}
	${PROJECT_SOURCE_DIR}/vendor/glew/include
	${PROJECT_SOURCE_DIR}/vendor/glfw/include
)