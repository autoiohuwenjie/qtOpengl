#ifndef SPHERE_H
#define SPHERE_H

#include <math.h>

#include <QVector3D>
#include <QMatrix4x4>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QQuickWindow>
#include <QQuickItem>

class Sphere : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(qreal rotAngle MEMBER m_rotAngle WRITE setRotAngle NOTIFY rotAngleChanged)
    Q_PROPERTY(QVector3D rotAxis MEMBER m_rotAxis  WRITE setRotAxis NOTIFY rotAxisChanged)

public:
    Sphere();
signals:
    void rotAngleChanged();
    void rotAxisChanged();
public slots:
    bool initializeSphere();
    void renderSphere();
    void dealWindowsChanged(QQuickWindow* );
    void releaseBuffer();

    void setRotAngle(qreal);
    void setRotAxis(QVector3D);
protected:
    QMatrix4x4 m_ModelViewMatrix;
    QMatrix4x4 m_ProjectionMatrix;
    QOpenGLBuffer m_VertexBuffer, m_IndexBuffer, m_ColorBuffer;
    QOpenGLShaderProgram m_ShaderProgram;

    qreal m_rotAngle;
    QVector3D m_rotAxis;

};

#endif // SPHERE_H
