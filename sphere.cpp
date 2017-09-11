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
    int stack = 12;//层数
    float stackStep = (float)(PI/stack);

    int slice = 16;//水平递增的角度
    float sliceStep = (float)(PI/slice);

    float r0,r1,y0,y1,x0,x1,z0,z1;

    float alpha0 = 0, alpha1 = 0;
    float beta = 0;
    const GLfloat R = 20.0f;


    for(int i = 0; i <= stack; i++){
        alpha0 = (float)(-PI / 2 + (i * stackStep));
        alpha1 = (float)(-PI / 2 + (i + 1) * stackStep);
        y0 = (float)(R * sin(alpha0));
        r0 = (float)(R * cos(alpha0));
        y1 = (float)(R * sin(alpha1));
        r1 = (float)(R * cos(alpha1));
        for(int j = 0; j <= slice * 2 ; j++){
            beta = j * sliceStep;
            x0 = (float)(r0 * cos(beta));
            z0 = -(float)(r0 * sin(beta));
            x1 = (float)(r1 * cos(beta));
            z1 = -(float)(r1 * sin(beta));
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
