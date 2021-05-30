#include "src/text.h"

#include <cstdlib>
#include <chrono>

int main(int argc, char* argv[])
{
    /*------GLFW and GLEW initialization and testing------*/
    GLFWwindow* window;
    if (!glfwInit())
    {
        std::cerr << "GLFW: failed to initialize" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(500, 300, "Truffle", NULL, NULL);
	glfwMakeContextCurrent(window);
    glewExperimental = true;
	if (!window)
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

    /*Vertex Array---------------------------------*/
    float vertexBufferArray[] =
    {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f,
    };
    uint32_t VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    uint32_t vertexBuffer;
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBufferArray), vertexBufferArray, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)(0));
    /*Vertex Array-end--------------------------------*/

    /*GLSL shader-------------------------------------*/
    auto source = PerigordGL::parseShader("resources/test"); //exclude file type
    uint32_t shader = PerigordGL::createShader(std::get<0>(source), std::get<1>(source));
    glUseProgram(shader);
    /*GLSL shader-end------------------------------------*/

    float bgColor[3]{0.1f, 0.3f, 0.2f};
    glClearColor(bgColor[0], bgColor[1], bgColor[2], 0.0f);

    glfwSwapInterval(1);
    while (!glfwWindowShouldClose(window))
    {
        auto start = std::chrono::high_resolution_clock::now();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        /*Vertex Array---------------------------------*/
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDisableVertexAttribArray(0);
        /*Vertex Array-end--------------------------------*/

        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> ElapsedTime = end - start;
        std::cout << "Time per frame: " << ElapsedTime.count() << "\n";
        std::cout << "FPS: " << 60 / ElapsedTime.count() << "\n";
    }
    glfwTerminate();
}