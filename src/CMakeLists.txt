add_library("Source" STATIC
	"Graphics.cpp"
)

add_subdirectory(Renderer/OpenGL)

configure_file(
${PROJECT_SOURCE_DIR}/src/Renderer/Shader/GLSL/test_frag.glsl
${PROJECT_BINARY_DIR}/src/Renderer/Shader/GLSL/test_frag.glsl
COPYONLY
)
configure_file(
${PROJECT_SOURCE_DIR}/src/Renderer/Shader/GLSL/test_vert.glsl
${PROJECT_BINARY_DIR}/src/Renderer/Shader/GLSL/test_vert.glsl
COPYONLY
)

target_link_libraries("Source" PRIVATE
	PG_OpenGL
)