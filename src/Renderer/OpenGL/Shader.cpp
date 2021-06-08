#include "Shader.h"



std::tuple<std::string,std::string> parseShader(const std::string& filepath)
{
    std::ifstream vertex(filepath + ".vert");
    if (!vertex.is_open()) std::cerr << "Vertex Shader Failed to open" << std::endl;
    std::ifstream fragment(filepath + ".frag");
    if (!fragment.is_open()) std::cerr << "Fragment Shader Failed to open" << std::endl;
    std::stringstream vertexFragment[2];
    std::string line;

    while (std::getline(vertex, line))
    {
        vertexFragment[0] << line << '\n';
    }

    while (std::getline(fragment, line))
    {
        vertexFragment[1] << line << '\n';
    }
    vertex.close(); fragment.close();

    return std::make_tuple(vertexFragment[0].str(), vertexFragment[1].str() );
}

uint32_t compileShader(uint32_t type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    /*Error Handling---------------------------*/
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);

    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)_malloca(sizeof(char) * length);

        glGetShaderInfoLog(id, length, &length, message);

        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << "shader" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        assert(0);
        return 0;
    }
    /*Error Handling-end--------------------------*/
    return id;
}

uint32_t createShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vertShader = compileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fragShader = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vertShader);
    glAttachShader(program, fragShader);

    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vertShader);
    glDeleteShader(fragShader);

    return program;
}
