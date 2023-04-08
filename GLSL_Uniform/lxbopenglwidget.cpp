#include "lxbopenglwidget.h"
 unsigned int VAO,VBO,EBO;
// QOpenGLShaderProgram shaderProgram;


 float vertices[]={
     //FIRST TRIANGLE
     0.5f,0.5f,0.0f,
     0.5f,-0.5f,0.0f,
     -0.5f,-0.5f,0.0f,
     -0.5f,0.5f,0.0f
 };
 unsigned int indices[] = {
     0,1,3,
     1,2,3
 };

LXBOpenGLWidget::LXBOpenGLWidget(QWidget *parent): QOpenGLWidget{parent}
{
   timer.start(100);
    connect(&timer,SIGNAL(timeout()),this,SLOT(on_timeout()));
}

LXBOpenGLWidget::~LXBOpenGLWidget()
{
    makeCurrent();
    glDeleteBuffers(1,&VBO);
    glDeleteVertexArrays(1,&VAO);
    glDeleteBuffers(1,&EBO);
    doneCurrent();
}



void LXBOpenGLWidget::drawShape(Shape shape)
{
    m_shape = shape;
    update();
}

void LXBOpenGLWidget::setWireframe(bool wireframe)
{
    makeCurrent();
    if(wireframe)
        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    else {
        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    }
    update();
    doneCurrent();
}

void LXBOpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    // 创建VAO和VBO
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);

    //绑定对象
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);


    //为缓冲对象创建数据存储
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);


    //告诉显卡怎么解析缓冲,第0个属性有三个值，为float，不需要标准化，步长三个float大小，偏移量为0
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);

    //开启VAO的第一个属性值
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER,0);

    //着色器
    bool success;
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,":/shaders/shapes.vert");
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,":/shaders/shapes.frag");
//   shaderProgram.release();
    success=shaderProgram.link();
    if(!success)
        qDebug()<<"ERR:"<<shaderProgram.log();





    glGenBuffers(1,&EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);
    glBindVertexArray(0);
}

void LXBOpenGLWidget::resizeGL(int w, int h)
{
Q_UNUSED(w);Q_UNUSED(h);
}

void LXBOpenGLWidget::paintGL()
{
    glClearColor(0.2f,0.3f,0.3f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    shaderProgram.bind();
    glBindVertexArray(VAO);
    switch (m_shape) {
    case Rect:
        glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,NULL);
        break;
    default:
        break;
    }


}
#include <QTime>
void LXBOpenGLWidget::on_timeout()
{
    if(m_shape = None){
        return;
    }
    makeCurrent();

    int timeValue = QTime::currentTime().second();
    float greenValue = (sin(timeValue)/2.0f)+0.5f;
    shaderProgram.setUniformValue("ourColor",0.0f,greenValue,0.0f,1.0f);


    doneCurrent();
    update();
}
