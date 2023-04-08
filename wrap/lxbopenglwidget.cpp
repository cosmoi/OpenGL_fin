#include "lxbopenglwidget.h"
 unsigned int VAO,VBO,EBO;
// QOpenGLShaderProgram shaderProgram;


 float vertices[]={
     //positions        //colors     //texture coords
     0.9f,0.9f,0.0f,   1.0f,0.0f,0.0f,  1.0f,1.0f,
     0.9,-0.9f,0.0f,  0.0f,1.0f,0.0f,  1.0f,0.0f,
     -0.9f,-0.9f,0.0f, 0.0f,0.0f,1.0f,  0.0f,0.0f,
     -0.9f,0.9f,0.0f,  1.0f,1.0f,1.0f,  0.0f,1.0f
 };
 unsigned int indices[] = {
     0,1,3,
     1,2,3
 };
float ratio = 0.5;
LXBOpenGLWidget::LXBOpenGLWidget(QWidget *parent): QOpenGLWidget{parent}
{
    setFocusPolicy(Qt::StrongFocus);
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


    //告诉显卡怎么解析缓冲,第0个属性有三个值，为float，不需要标准化，步长6个float大小，偏移量为0
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)0);
    //开启VAO的第一个属性值
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(6*sizeof(float)));
    glEnableVertexAttribArray(2);

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

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    textureWall = new QOpenGLTexture(QImage(":/images/images/fuhua1.jpg").mirrored());
    textureSmile = new QOpenGLTexture(QImage(":/images/images/ying1.jpg").mirrored());
    textureSmall = new QOpenGLTexture(QImage(":/images/images/small.jpg").mirrored());
    shaderProgram.bind();
    shaderProgram.setUniformValue("textureWall",0);
    shaderProgram.setUniformValue("textureSmile",1);
    shaderProgram.setUniformValue("textureSmall",2);
    glBindVertexArray(0);

    textureSmall->bind(2);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
}

void LXBOpenGLWidget::resizeGL(int w, int h)
{
Q_UNUSED(w);Q_UNUSED(h);
}

void LXBOpenGLWidget::paintGL()
{

    float borderColor[] = {1.0f,0.0f,0.0f,1.0f};

    glClearColor(0.2f,0.3f,0.3f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    shaderProgram.bind();
    shaderProgram.setUniformValue("ratio",ratio);
    glBindVertexArray(VAO);
    switch (m_shape) {
    case Rect:
        textureWall->bind(0);
        textureSmile->bind(1);
        textureSmall->bind(2);



        glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,NULL);
        break;
    default:
        break;
    }


}
#include <QKeyEvent>
void LXBOpenGLWidget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Up:
        ratio +=0.1;
        break;
    case Qt::Key_Down:
        ratio -=0.1;
    default:
        break;
    }
    if(ratio>1) ratio = 1;
    if(ratio<1) ratio = 0;
    shaderProgram.bind();
    shaderProgram.setUniformValue("ratio",ratio);
    update();
}
