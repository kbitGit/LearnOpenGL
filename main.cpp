#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include <iostream>

void key_callback(GLFWwindow *window,int key,int scancode,int action,int mode);
void checkShader(GLuint shaderToCheck);
static const char* vertexShaderSource = {
  "#version 330 core \n \
  layout (location = 0) in vec3 position;\n\
  void main()\n\
  {\n\
    gl_Position = vec4(position,1.0);\n\
  }"
};
static const char* fragmentShaderSource =
{
  "#version 330 core\n\
  out vec4 color;\n\
  void main()\n\
  {\n\
    color = vec4(1.0f,0.5f,0.2f,1.0f);\n\
  }"
};
int main(int argc, char const *argv[])
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE,GL_FALSE);
    GLFWwindow* window = glfwCreateWindow(800,600,"LearnOpenGL",nullptr,nullptr);
    if(window == nullptr)
    {
      std::cout << "Failed to create GLFW window" << std::endl;
      glfwTerminate();
      return -1;
    }
    glfwMakeContextCurrent(window);

    glfwSetKeyCallback(window,key_callback);

    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK)
    {
      std::cout << "Failed to initialze GLEW" <<std::endl;
    }

    glViewport(0,0,800,600);

    GLfloat vertices[] =
    {
      0.5f,0.5f,-0.0f,
      0.5f,-0.5f,-0.0f,
      -0.5f,-0.5f,-0.0f,
      -0.5f,0.5f,-0.0f
    };

    GLuint indices[] =
    { 0,1,3,
      1,2,3
    };

    GLuint VAO;
    GLuint VBO;
    GLuint EBO;
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);
    glGenBuffers(1,&EBO);

    glBindVertexArray(VAO);
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3 * sizeof(GL_FLOAT),(GLvoid* )0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
    GLuint vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader,1,&vertexShaderSource,NULL);
    glCompileShader(vertexShader);
    checkShader(vertexShader);

    GLuint fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader,1,&fragmentShaderSource,NULL);
    glCompileShader(fragmentShader);
    checkShader(fragmentShader);

    GLuint shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram,vertexShader);
    glAttachShader(shaderProgram,fragmentShader);
    glLinkProgram(shaderProgram);

    glUseProgram(shaderProgram);

    GLint success;
    glGetProgramiv(shaderProgram,GL_LINK_STATUS,&success);
    if(!success)
    {
      GLchar infoLog[512];
      glGetProgramInfoLog(shaderProgram,512,NULL,infoLog);
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    while (!glfwWindowShouldClose(window))
    {
      glfwPollEvents();
      glClearColor(0.2f,0.3f,0.3f,1.0f);
      glClear(GL_COLOR_BUFFER_BIT);

      glUseProgram(shaderProgram);
      glBindVertexArray(VAO);
      glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
      glBindVertexArray(0);
      glfwSwapBuffers(window);
    }


    glDeleteProgram(shaderProgram);
    glfwTerminate();
    return 0;
}
void key_callback(GLFWwindow *window,int key,int scancode,int action,int mode)
{
  if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
  {
    glfwSetWindowShouldClose(window,GL_TRUE);
  }
}
void checkShader(GLuint shaderToCheck)
{
  GLint success;
  GLchar infoLog[512];
  glGetShaderiv(shaderToCheck,GL_COMPILE_STATUS, &success);
  if(!success)
  {
    glGetShaderInfoLog(shaderToCheck,512,NULL,infoLog);
    std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED \n" << infoLog << "\n";
  }
}
