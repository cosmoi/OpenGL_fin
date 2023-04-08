#include "lxbopenglwidget.h"
// unsigned int VAO,VBO,EBO;
 unsigned int VBOs[2],VAOs[2];
 unsigned int shaderProgram,shaderProgram2;

 float firstTriangle[]={
     -0.9f,-0.5f,0.0f,//left
     -0.0f,-0.5f,0.0f,
     -0.45f,0.5f,0.0f
};
 float secondTriangle[]={
     0.0f,-0.5f,0.0f,
     0.9f,-0.5f,0.0f,
     0.45f,0.5f,0.0f,
 };

 const char *vertexShaderSource = "#version 330 core\n"
                                  "layout(location = 0) in vec3 aPos;\n" "void main()\n"
                                  "{\n"
                                  "gl_Position = vec4(aPos.x,aPos.y,aPos.z,1.0);\n"
                                  "}\0";
 const char *fragmentShaderSource = "#version 330 core\n"
                                    "out vec4 FragColor;\n"
                                    "void main()\n"
                                    "{\n"
                                    "FragColor = vec4(1.0f,0.5f,0.2f,1.0f);\n" "}\n\0";
 const char *fragmentShaderSource2 = "#version 330 core\n"
                                    "out vec4 FragColor;\n"
                                    "void main()\n"
                                    "{\n"
                                    "FragColor = vec4(1.0f,1.0f,0.0f,1.0f);\n" "}\n\0";

LXBOpenGLWidget::LXBOpenGLWidget(QWidget *parent): QOpenGLWidget{parent}
{

}

void LXBOpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    // 创建VAO和VBO
    glGenVertexArrays(2, VAOs);
    glGenBuffers(2, VBOs);

    //绑定对象
    glBindVertexArray(VAOs[0]);
    glBindBuffer(GL_ARRAY_BUFFER,VBOs[0]);
    //为缓冲对象创建数据存储
    glBufferData(GL_ARRAY_BUFFER,sizeof(firstTriangle),firstTriangle,GL_STATIC_DRAW);

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
    //开启VAO的第一个属性值
    glEnableVertexAttribArray(0);



    //绑定对象
    glBindVertexArray(VAOs[1]);
    glBindBuffer(GL_ARRAY_BUFFER,VBOs[1]);
    //为缓冲对象创建数据存储
    glBufferData(GL_ARRAY_BUFFER,sizeof(secondTriangle),secondTriangle,GL_STATIC_DRAW);

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
    //开启VAO的第一个属性值
    glEnableVertexAttribArray(0);








    //顶点着色器
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader,1,&vertexShaderSource,NULL);
    glCompileShader(vertexShader);
    //片段着色器1
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader,1,&fragmentShaderSource,NULL);
    glCompileShader(fragmentShader);
    //片段着色器2
    unsigned int fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader2,1,&fragmentShaderSource2,NULL);
    glCompileShader(fragmentShader2);


    //着色器连接1
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram,vertexShader);
    glAttachShader(shaderProgram ,fragmentShader);
    glLinkProgram(shaderProgram);
    //着色器连接2
    shaderProgram2 = glCreateProgram();
    glAttachShader(shaderProgram2,vertexShader);
    glAttachShader(shaderProgram2 ,fragmentShader2);
    glLinkProgram(shaderProgram2);


    //删除着色器
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteShader(fragmentShader2);

}

void LXBOpenGLWidget::resizeGL(int w, int h)
{

}

void LXBOpenGLWidget::paintGL()
{
    glClearColor(0.2f,0.3f,0.3f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);
    glBindVertexArray(VAOs[0]);
    glDrawArrays(GL_TRIANGLES,0,3);

    glUseProgram(shaderProgram2);
    glBindVertexArray(VAOs[1]);
    glDrawArrays(GL_TRIANGLES,0,3);


}
