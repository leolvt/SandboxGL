#ifndef GL_RENDERER_H_INCLUDED
#define GL_RENDERER_H_INCLUDED

#include <string>
#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>

// ========================== //

#define BUFFER_OFFSET(x) ((char *)NULL + (x))

// ========================== //

typedef struct 
{
    float X, Y;
    float R, G, B;
    float padding[3];
} Vertex;

// ========================== //

typedef struct {
    GLuint ShaderProgram;
    GLuint vertexShader;
    GLuint fragmentShader;
    GLint modelView;
} Program;

// ========================== //

typedef struct {
    GLuint VAO;
    GLuint VBO;
    unsigned int numVertices;
} Object;

// ========================== //

class Renderer
{
    public:
        Renderer();
        virtual ~Renderer();
        void setWindowSize(unsigned int width, unsigned int height);
        void setWindowTitle(std::string title);
        void createWindow();
        void drawObject(Program prog, Object obj, glm::mat4 Modelview);
        void render();

        static Program createProgram(std::string vShader, std::string fShader);
        static Object createObject(std::vector<Vertex>& vList);

    private:
        std::string static getLog(GLuint object);
        GLint static createShader(std::string filename, GLenum type);

        unsigned int wWidth;
        unsigned int wHeight;
        std::string wTitle;
};

// ========================== //

#endif /* GL_RENDERER_H_INCLUDED */
