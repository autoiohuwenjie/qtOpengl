#include "sphere.h"

Sphere::Sphere():
    m_VertexBuffer(QOpenGLBuffer::VertexBuffer),
    m_rotAngle(0.0),
    m_rotAxis(1.0, 1.0, 0.0)
{
    connect(this, SIGNAL(windowChanged(QQuickWindow*)),
            this, SLOT(dealWindowsChanged(QQuickWindow*)), Qt::DirectConnection);
}

void Sphere::dealWindowsChanged(QQuickWindow* pWindow) {
    if ( pWindow == Q_NULLPTR ) return;
    connect( pWindow, SIGNAL( beforeRendering( ) ),
             this, SLOT( renderSphere() ), Qt::DirectConnection );
    pWindow->setClearBeforeRendering( false );
}

void Sphere::renderSphere() {
    static bool runOnce = initializeSphere();
    Q_UNUSED(runOnce)

    // 运动
    m_ModelViewMatrix.setToIdentity( );
    m_ModelViewMatrix.translate( 0.0f, 0.0f, -60.0f );
    m_ModelViewMatrix.rotate( m_rotAngle, m_rotAxis.x( ),
                              m_rotAxis.y( ), m_rotAxis.z( ) );

    // 渲染
    glViewport( 0, 0, window( )->width( ), window( )->height( ) );
    glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glEnable( GL_DEPTH_TEST );
    glEnable( GL_CULL_FACE );
    glFrontFace( GL_CW );

    m_ShaderProgram.bind( );
    m_VertexBuffer.bind( );
    int posLoc = m_ShaderProgram.attributeLocation( "position" );
    m_ShaderProgram.enableAttributeArray( posLoc );
    m_ShaderProgram.setAttributeBuffer( posLoc,                 // 位置
                                        GL_FLOAT,               // 类型
                                        0,                      // 偏移
                                        3,                      // 元大小
                                        0 );                    // 迈


    m_ShaderProgram.setUniformValue( "modelViewMatrix", m_ModelViewMatrix );
    m_ShaderProgram.setUniformValue( "projectionMatrix", m_ProjectionMatrix );
    glDrawArrays( GL_LINE_STRIP, 0, coordsList.size()/3);

    m_ShaderProgram.disableAttributeArray( posLoc );
    m_VertexBuffer.release( );
    m_ShaderProgram.release( );


}

bool Sphere::initializeSphere() {
    // 初始化着色器
    m_ShaderProgram.addShaderFromSourceFile( QOpenGLShader::Vertex,
                                             ":/Shader/Shader.vsh" );
    m_ShaderProgram.addShaderFromSourceFile( QOpenGLShader::Fragment,
                                             ":/Shader/Shader.fsh" );


    m_ShaderProgram.link( );

    // 初始化顶点缓存


    float Rinner = 10.0f;
    float Rring = 20.0f;
    float x0 = 0,y0 = 0,z0 = 0,x1 = 0,y1 = 0,z1 = 0;

    int count = 20;
    float alpha = 0;
    float alpha0 = 0;
    float alphaStep = (float)(PI * 2/count);
    int count0 = 20;
    float beta =0;
    float betaStep = (float)(PI * 2/count0);
    for(int i = 0; i <= count; i++){
        alpha = i * alphaStep;
        alpha0 = (i + 1) * alphaStep;
        for(int j = 0; j <= count0; j++){
            beta = j * betaStep;
            x0 = (float)((Rinner + (Rring - Rinner)/2 * cos(beta))*(cos(alpha)));
            y0 = (float)((Rinner + (Rring - Rinner)/2 * cos(beta))*(sin(alpha)));
            z0 = (float) ((Rring - Rinner) / 2 * sin(beta));

            x1 = (float)((Rinner + (Rring - Rinner)/2 * cos(beta))*(cos(alpha0)));
            y1 = (float)((Rinner + (Rring - Rinner)/2 * cos(beta))*(sin(alpha0)));
            z1 = (float) ((Rring - Rinner) / 2 * sin(beta));
            coordsList.append(x0);
            coordsList.append(y0);
            coordsList.append(z0);
            coordsList.append(x1);
            coordsList.append(y1);
            coordsList.append(z1);
        }
    }


    GLfloat vertices[coordsList.size()];
    for(int i = 0; i < coordsList.size(); ++i) {
        vertices[i] = coordsList.at(i);
    }

    m_VertexBuffer.setUsagePattern( QOpenGLBuffer::StaticDraw );

    m_VertexBuffer.create( );
    m_VertexBuffer.bind( );
    m_VertexBuffer.allocate( vertices, sizeof( vertices ) );

    // 设定模型矩阵和投影矩阵
    float aspectRatio  = float( window( )->width( ) ) / float( window( )->height( ) );
    m_ProjectionMatrix.perspective( 45.0f,
                                    aspectRatio,
                                    0.5f,
                                    500.0f );

    connect( window( )->openglContext( ),
             SIGNAL( aboutToBeDestroyed( ) ),
             this, SLOT( releaseBuffer() ),
             Qt::DirectConnection );
    return true;
}

void Sphere::releaseBuffer() {
    m_VertexBuffer.destroy();
}

void Sphere::setRotAngle(qreal value) {
    m_rotAngle = value;
    if(window() != Q_NULLPTR) {
        window() -> update();
    }
}

void Sphere::setRotAxis(QVector3D value) {
    m_rotAxis = value;
    if(window() != Q_NULLPTR) {
        window() -> update();
    }
}
