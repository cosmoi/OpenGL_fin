#ifndef LXBOPENGLWIDGET_H
#define LXBOPENGLWIDGET_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QTimer>
class LXBOpenGLWidget : public QOpenGLWidget,QOpenGLFunctions_3_3_Core
{
    Q_OBJECT
public:
    enum Shape{None,Rect,Circle,Triangle};
    explicit LXBOpenGLWidget(QWidget *parent = nullptr);
    ~LXBOpenGLWidget();
    void drawShape(Shape shape);
    void setWireframe(bool wireframe);
protected:
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();
    void keyPressEvent(QKeyEvent *event);
signals:

public slots:
    void on_timeout();
private:
    Shape m_shape;
    QOpenGLShaderProgram shaderProgram;
    QOpenGLTexture * textureWall;
    QOpenGLTexture * textureSmile;   
    QOpenGLTexture * textureSmall;
    QTimer timer;
};

#endif // LXBOPENGLWIDGET_H
