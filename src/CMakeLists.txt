add_library("src" STATIC 
"text.cpp"

)
add_subdirectory("Renderer/OpenGL") 

target_link_libraries("src" PRIVATE 
	PG_OpenGL
)