import QtQuick 2.7
import QtQuick.Scene3D 2.0
import Qt3D.Render 2.0
import Qt3D.Core 2.0
import Qt3D.Extras 2.0

Item {
    width: 500
    height: 500
    Scene3D {
        id: scene3d
        anchors.fill: parent
        anchors.margins: 10
        focus: true
        aspects: ["input", "logic"]
        cameraAspectRatioMode: Scene3D.AutomaticAspectRatio

        Entity {
            id: sceneRoot

            Camera {
                id: camera
                projectionType: CameraLens.PerspectiveProjection
                fieldOfView: 45
                nearPlane: 0.1
                farPlane: 1000.0
                position: Qt.vector3d(0.0, 0.0, 2.0)
                upVector: Qt.vector3d(0.0, 1.0, 0.0)
                viewCenter: Qt.vector3d(0.0, 0.0, 0.0)
            }

            components: [
                RenderSettings {
                    activeFrameGraph: ForwardRenderer {
                        id: renderer
                        clearColor: "transparent"
                        camera: camera
                    }
                }
            ]
            Entity {
                id: root
                property color maincolor: "red"
                components: [transform, mesh, material]


                Material {
                    id: material
                    parameters: [
                        Parameter {
                            name: "maincolor"
                            value: Qt.vector3d(root.maincolor.r, root.maincolor.g, root.maincolor.b)
                        },
                        Parameter {
                            name: "fireTexture"
                            value: Texture2D {
                                id: fireTexture
                                minificationFilter: Texture.LinearMipMapLinear
                                magnificationFilter: Texture.Linear
                                wrapMode {
                                    x: WrapMode.Repeat
                                    y: WrapMode.Repeat
                                }
                                generateMipMaps: true
                                maximumAnisotropy: 16.0
                                TextureImage { source: "qrc:/image/earth.jpg" }
                            }
                        }
                    ]
                    effect: Effect {

                        property string vertex: "qrc:/shader/gl3/fire.vert"
                        property string fragment: "qrc:/shader/gl3/fire.frag"
                        FilterKey {
                            id: forward
                            name: "renderingStyle"
                            value: "forward"
                        }
                        ShaderProgram {
                            id: gl3Shader
                            vertexShaderCode: loadSource(parent.vertex)
                            fragmentShaderCode: loadSource(parent.fragment)
                        }

                        techniques: [
                            Technique {
                                filterKeys: [forward]
                                graphicsApiFilter {
                                    api: GraphicsApiFilter.OpenGL
                                    profile: GraphicsApiFilter.CoreProfile
                                    majorVersion: 3
                                    minorVersion: 1
                                }
                                renderPasses: RenderPass {
                                    shaderProgram: gl3Shader
                                }
                            }
                        ]
                    }
                }

                Transform {
                    id: transform
                    property real rotAngle: 0.0
                    scale3D: Qt.vector3d(1.0, 1.0, 1.0)
                    rotation: fromAxisAndAngle(Qt.vector3d(1, 1, 0),rotAngle)
                    SequentialAnimation on rotAngle {
                        NumberAnimation {from: 0.0; to: 180.0; duration: 3600}
                        loops: Animation.Infinite
                    }
                }

                SphereMesh {
                    id: mesh
                    property real r: 0
                    property real x: 0
                    property real y: 0
                    property real z: 0
                    property real roll: 0
                    property real tilt: 0

                    radius: 0.6
                    generateTangents: true
                    rings: 64
                    slices: 64
                }
            }
        }
    }
}
