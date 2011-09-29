#include <GL/glew.h>
#include <GL/glfw.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Util.h"
#include "Exceptions.h"
#include "GLRenderer.h"

// ========================== //

Renderer::Renderer()
{
    // Init GLFW (Window-Independent stuff)
    GLboolean res = glfwInit();
    if (res == GL_FALSE) throw GLFWException("Error initializing GLFW");

    // Set Default value for window properties
    this->wWidth = 600;
    this->wHeight = 600;
    this->wTitle = "OpenGl Rendered Window";
}

// ========================== //

Renderer::~Renderer()
{
    // Terminate GLFW - no more GLFW calls
    glfwTerminate();
}

// ========================== //

void Renderer::setWindowSize(unsigned int width, unsigned int height)
{
    this->wWidth = width;
    this->wHeight = height;
    glfwSetWindowSize( width, height );
}

// ========================== //

void Renderer::setWindowTitle(std::string title)
{
    this->wTitle = title;
    glfwSetWindowTitle(title.c_str());
}

// ========================== //

void Renderer::createWindow()
{
    // Open a window
    GLboolean res = glfwOpenWindow(
        wWidth,    // Width
        wHeight,   // Height
        8, 8, 8,        // # of RGB bits
        0, 0, 0,        // # of Alpha, Depth and Stencil bits
        GLFW_WINDOW     // Window Mode
    );
    if (res == GL_FALSE) throw GLFWException("Error opening window.");
    glewInit();
}

// ========================== //

void Renderer::render()
{
    // Swap OpenGL buffer
    glfwSwapBuffers();
}

// ========================== //

/*
 * getLog - Retrieve Log messages
 */
std::string Renderer::getLog(GLuint object)
{
    // Get error length
    GLint log_length = 0;
    if (glIsShader(object))
        glGetShaderiv(object, GL_INFO_LOG_LENGTH, &log_length);
    else if (glIsProgram(object))
        glGetProgramiv(object, GL_INFO_LOG_LENGTH, &log_length);
    else {
        return std::string("Not a shader or a program");
    }

    // Retrieve and print the error message
    char* log = new char [log_length];
    if (glIsShader(object))
        glGetShaderInfoLog(object, log_length, NULL, log);
    else if (glIsProgram(object))
        glGetProgramInfoLog(object, log_length, NULL, log);
    std::string msg = log;
    delete [] log;

    return msg;
}

// ========================== //

/**
 * Compile the shader from file 'filename', with error handling
 */
GLint Renderer::createShader(std::string filename, GLenum type)
{
    // Read shader code to string
    std::string fileContent = Util::readFile(filename);
    const GLchar* source = fileContent.c_str();
    
    // Create a new shader
    GLuint res = glCreateShader(type);

    // Bind the source code to the shader
    glShaderSource(res, 1, &source, NULL);

    // Try to compile the shader
    glCompileShader(res);
    GLint compile_ok = GL_FALSE;
    glGetShaderiv(res, GL_COMPILE_STATUS, &compile_ok);
    if (compile_ok == GL_FALSE) {
        OpenGLException se(getLog(res));
        glDeleteShader(res);
        throw se;
    }

    return res;
}

// ========================== //

Program Renderer::createProgram(std::string vShader, std::string fShader)
{
    // Create a program
    Program prog = {0, 0, 0, 0};

    try 
    {
        // Create a shader program
        prog.ShaderProgram = glCreateProgram();

        // Create, Load and Compile Vertex and Fragment Shaders
        prog.vertexShader = createShader(vShader, GL_VERTEX_SHADER);
        prog.fragmentShader = createShader(fShader, GL_FRAGMENT_SHADER);
        
        // Attach Shaders
        glAttachShader(prog.ShaderProgram, prog.vertexShader);
        glAttachShader(prog.ShaderProgram, prog.fragmentShader);

        // Bind Shader Attributes
        glBindAttribLocation(prog.ShaderProgram, 0, "InVertex");
        glBindAttribLocation(prog.ShaderProgram, 1, "InColor");

        // Link Program
        glLinkProgram(prog.ShaderProgram);
        
        // Check if Linked
        GLint IsLinked;
        glGetProgramiv(prog.ShaderProgram, GL_LINK_STATUS, (GLint *)&IsLinked);
        if(IsLinked == GL_FALSE)
        {
            std::string msg = "Failed to link shader program: ";
            msg += getLog(prog.ShaderProgram);
            throw OpenGLException(msg); 

        }   

        // Retrieve ModelView Matrix Location
        prog.modelView = glGetUniformLocation(prog.ShaderProgram, "ModelView");
        if (prog.modelView == -1)
        {
            std::string msg = "Failed to retrieve uniform 'ModelView'";
            throw OpenGLException(msg);
        }
        
    }
    // In case of OpenGL exception, clean up and re-throw
    catch (BaseException& e)
    {
        // If Vertex Shader was created, clean it
        if (prog.vertexShader != 0)
        {
            glDetachShader(prog.ShaderProgram, prog.vertexShader);
            glDeleteShader(prog.vertexShader);
        }

        // if Fragment Shader was created, clean it
        if (prog.fragmentShader != 0)
        {
            glDetachShader(prog.ShaderProgram, prog.fragmentShader);
            glDeleteShader(prog.fragmentShader);
        }

        // Clean shader program
        glDeleteProgram(prog.ShaderProgram);

        // Rethrow exception
        throw;
    }

    return prog;
}

// ========================== //

Object Renderer::createObject(std::vector<Vertex>& vList)
{
    // Our new Object
    Object obj = {0, 0, 0};

    // Number of vertices (helpful for glDrawArray and others)
    obj.numVertices = vList.size();

    // Create a new VBO to store the vertices
    // TODO: Check glGetError
    unsigned int totalSize = vList.size() * sizeof(Vertex);
    glGenBuffers(1, &obj.VBO);
    glBindBuffer(GL_ARRAY_BUFFER, obj.VBO);
    // TODO: Test it, if fails, convert to C Array
    glBufferData(GL_ARRAY_BUFFER, totalSize, &vList[0], GL_STATIC_DRAW);

    // Create a new for our object VAO
    // TODO: Check glGetError
    glGenVertexArrays(1, &obj.VAO);
    glBindVertexArray(obj.VAO);

    // Bind and setup VBO tp VAO
    glBindBuffer(GL_ARRAY_BUFFER, obj.VBO);
    glVertexAttribPointer(  // Vertex Location
            0,                  // Attrib Index 
            2,                  // Attrib Size
            GL_FLOAT,           // Attrib type
            GL_FALSE,           // Normalize?
            sizeof(Vertex),     // Stride
            BUFFER_OFFSET(0)    // Offset
    );
    glVertexAttribPointer(  // Vertex Color
            1,                  // Attrib Index 
            3,                  // Attrib Size
            GL_FLOAT,           // Attrib type
            GL_FALSE,           // Normalize?
            sizeof(Vertex),     // Stride
            BUFFER_OFFSET(sizeof(float)*2)    // Offset
    );
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    // Clean bindings
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    return obj;
}

// ========================== //

void Renderer::drawObject(Program prog, Object obj, glm::mat4 Modelview)
{
    // Set Shader Program
    glUseProgram(prog.ShaderProgram);

    // Pass to shader the ModelView Matrix
    glUniformMatrix4fv(prog.modelView, 1, GL_FALSE, glm::value_ptr(Modelview));

    // Bind Object VAO
    glBindVertexArray(obj.VAO);

    // Push Vertices to Shader
    glDrawArrays(GL_TRIANGLE_FAN, 0, obj.numVertices);
}

// ========================== //

