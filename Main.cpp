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

    window = glfwCreateWindow(500, 500, "Truffle", NULL, NULL);
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
     0.5f,  0.5f, 0.0f,     1.0f, 0.0f, 0.0f,   //top-right
     0.5f, -0.5f, 0.0f,     0.0f, 1.0f, 0.0f,   //bottom right
    -0.5f, -0.5f, 0.0f,     0.0f, 0.0f, 1.0f,   //bottom-left
    -0.5f,  0.5f, 0.0f,     1.0f, 1.0f, 1.0f    //top-left
    };
    uint32_t VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    uint32_t vertexBuffer;
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBufferArray), vertexBufferArray, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(0));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)) );
    glEnableVertexAttribArray(1);
    /*Vertex Array-end--------------------------------*/

    /*Index Array----------------------------------*/
    uint32_t indexBufferArray[] =
    {
    0, 1, 3,   
    1, 2, 3    
    };
    uint32_t indexArrayID;
    glGenBuffers(1, &indexArrayID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexArrayID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexBufferArray), indexBufferArray, GL_STATIC_DRAW);
    /*Index Array-end---------------------------------*/

    /*GLSL shader-------------------------------------*/
    auto source = PerigordGL::parseShader("resources/test"); //exclude file type
    uint32_t shader = PerigordGL::createShader(std::get<0>(source), std::get<1>(source));
    glUseProgram(shader);
    /*GLSL shader-end------------------------------------*/

    float bgColor[3]{0.1f, 0.3f, 0.2f};
    glClearColor(bgColor[0], bgColor[1], bgColor[2], 0.0f);

    glfwSwapInterval(0);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    while (!glfwWindowShouldClose(window))
    {
        auto start = std::chrono::high_resolution_clock::now();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(shader);

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);

        /*Buffer binding---------------------------------*/
        glBindVertexArray(VertexArrayID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexArrayID);
        /*Buffer binding-end--------------------------------*/
        /*Uniforms------------------------------*/
        float timeValue = glfwGetTime();
        float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
        float blueValue = (cos(timeValue) / 2.0f) + 0.5f;
        float redValue = 1.0f - ((cos(timeValue) / 2.0f) + 0.5f);


        uint32_t FragUniform = glGetUniformLocation(shader, "uColor");
        glUniform4f(FragUniform, redValue, greenValue, blueValue, 0.2f);

        uint32_t VertUniform = glGetUniformLocation(shader, "u_Position");
        glUniform3f(VertUniform, blueValue - 0.5, (1.0f - greenValue) - 0.5, 1.0f);
        /*Uniforms-end--------------------------*/
        /*Draw------------------------*/
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);
        /*Draw-end-----------------------*/

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glfwSwapBuffers(window);
        /* Poll for and process events */
        glfwPollEvents();

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> ElapsedTime = end - start;
        std::cout << "Time per frame: " << ElapsedTime.count() << "s\n";
    }
    glfwTerminate();
}