// Shader.vsh
attribute highp vec3 position;

uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;

varying highp vec4 v_Color;

void main( void )
{
    gl_Position = projectionMatrix *
            modelViewMatrix *
            vec4( position, 1.0 );
}
