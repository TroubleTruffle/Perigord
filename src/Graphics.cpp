#include "Graphics.h"

int graphicsMain()
{
     /*------GLFW and GLEW initialization and testing------*/
    GLFWwindow* perigord;
    if(!glfwInit())
    {
        std::cerr << "GLFW: failed to initialize" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    perigord = glfwCreateWindow(500, 500, "Truffle", NULL, NULL);
    glfwMakeContextCurrent(perigord);
    glewExperimental = true;

     if (!perigord)
    {
        std::cerr << "failed to make window" << std::endl;
        glfwTerminate();
        return -1;
    }
    if (glewInit() != GLEW_OK)
    {
        std::cerr << "GLEW: failed to initialize" << std::endl;
        return -1;
    }
/*------GLFW and GLEW initialization and testing-end-----*/
	return 1;
}