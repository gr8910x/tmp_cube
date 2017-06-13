#ifndef CAMERA_H
#define CAMERA_H

#include "commonincludings.h"
#include "icamera.h"

//! Implements OpenGL Scene 3D space camera object.
class Camera : public ICamera
{
public:
    Camera();                                                                //! Default constructor.
    Camera( GLfloat              fovy                                        //! Parameterized constructor.
          , GLfloat              width
          , GLfloat              height
          );
    Camera( GLfloat              fovy                                        //! Parameterized constructor.
          , GLfloat              width
          , GLfloat              height
          , GLfloat              zNear
          , GLfloat              zFar
          );
    Camera( const QVector3D     &position                                    //! Parameterized constructor.
          , const QVector3D     &gazePoint
          , const QVector3D     &upperDirection
          );
    Camera( GLfloat              positionX                                   //! Parameterized constructor.
          , GLfloat              positionY
          , GLfloat              positionZ
          , GLfloat              gazePointX
          , GLfloat              gazePointY
          , GLfloat              gazePointZ
          , GLfloat              upperDirectionX
          , GLfloat              upperDirectionY
          , GLfloat              upperDirectionZ
          );
    Camera( GLfloat              fovy                                        //! Parameterized constructor.
          , GLfloat              width
          , GLfloat              height
          , GLfloat              zNear
          , GLfloat              zFar
          , const QVector3D     &position
          , const QVector3D     &gazePoint
          , const QVector3D     &upperDirection
          );
    Camera( GLfloat              fovy                                        //! Parameterized constructor.
          , GLfloat              width
          , GLfloat              height
          , GLfloat              zNear
          , GLfloat              zFar
          , GLfloat              positionX
          , GLfloat              positionY
          , GLfloat              positionZ
          , GLfloat              gazePointX
          , GLfloat              gazePointY
          , GLfloat              gazePointZ
          , GLfloat              upperDirectionX
          , GLfloat              upperDirectionY
          , GLfloat              upperDirectionZ
          );
    Camera( GLfloat              fovy                                        //! Parameterized constructor.
          , GLfloat              width
          , GLfloat              height
          , GLfloat              zNear
          , GLfloat              zFar
          , const QVector3D     &position
          , const QVector3D     &gazePoint
          , const QVector3D     &upperDirection
          , com_defs::CameraMode mode
          , const QString       &description = "Empty description"
          );
    Camera( GLfloat              fovy                                        //! Parameterized constructor.
          , GLfloat              width
          , GLfloat              height
          , GLfloat              zNear
          , GLfloat              zFar
          , GLfloat              positionX
          , GLfloat              positionY
          , GLfloat              positionZ
          , GLfloat              gazePointX
          , GLfloat              gazePointY
          , GLfloat              gazePointZ
          , GLfloat              upperDirectionX
          , GLfloat              upperDirectionY
          , GLfloat              upperDirectionZ
          , com_defs::CameraMode mode
          , const QString       &description = "Empty description"
          );

    Camera( const Camera &camera );                                          //! Copying constructor.

    virtual ~Camera() {}

    void  calculate();                                                       //! Recalculates camera view, projection and projection view matrices.

    const Camera & operator = (const Camera &camera);                        //! Operator " =  ".
    bool  operator == (const Camera &camera) const;                          //! Operator " == ".
    bool  operator != (const Camera &camera) const;                          //! Operator " != ".

public:
    GLfloat getFovy() const { return m_fovy; }                               //! Returns Y axis angle.
    void setFovy(GLfloat fovy);                                              //! Sets Y axis angle.

    GLfloat getWidth() const  { return m_width; }                            //! Returns projection cut width.
    GLfloat getHeight() const { return m_height; }                           //! Returns projection cut height.
    void setWidth(GLfloat width);                                            //! Sets projection cut width.
    void setHeight(GLfloat height);                                          //! Sets projection cut height.

    GLfloat getZNear() const { return m_zNear; }                             //! Returns distance to the nearest separation plane.
    GLfloat getZFar() const  { return m_zFar; }                              //! Returns distance to the further separation plane.
    void setZNear(GLfloat zNear);                                            //! Sets distance to the nearest separation plane.
    void setZFar(GLfloat zFar);                                              //! Sets distance to the further separation plane.

    const QVector3D & getPosition() const { return m_position; }             //! Returns camera position in 3D space.
    QVector3D & getPosition() { return m_position; }                         //! Returns camera position in 3D space, overloaded function.
    void setPosition(const QVector3D &position);                             //! Sets camera position in 3D space.
    void setPosition(GLfloat x, GLfloat y, GLfloat z);                       //! Sets camera position in 3D space, overloaded function.

    const QVector3D & getGazePoint() const { return m_gazePoint; }           //! Returns point in 3D scape at which camera is looking.
    QVector3D & getGazePoint() { return m_gazePoint; }                       //! Returns point in 3D scape at which camera is looking, overloaded function.
    void setGazePoint(const QVector3D &gazePoint);                           //! Sets point in 3D scape at which camera is looking.
    void setGazePoint(GLfloat x, GLfloat y, GLfloat z);                      //! Sets point in 3D scape at which camera is looking, overloaded function.

    const QVector3D & getUpperDirection() const { return m_upperDirection; } //! Returns upper direction vector from camera eye.
    QVector3D & getUpperDirection() { return m_upperDirection; }             //! Returns upper direction vector from camera eye, overloaded function.
    void setUpperDirection(const QVector3D &upperDirection);                 //! Sets upper direction vector from camera eye.
    void setUpperDirection(GLfloat x, GLfloat y, GLfloat z);                 //! Sets upper direction vector from camera eye, overloaded function.

    const QMatrix4x4 & getView() const { return m_view; }                    //! Returns camera view matrix.
    const QMatrix4x4 & getProjection() const { return m_projection; }        //! Returns camera projection matrix.
    const QMatrix4x4 & getProjectionView() const { return m_projectionView; }//! Returns camera projection view matrix, multiplication of projection and view matrices.

    com_defs::CameraMode getMode() const { return m_mode; }                  //! Returns camera projection mode.
    void setMode(com_defs::CameraMode mode);                                 //! Sets camera projection mode.

    GLuint getName() const { return m_name; }                                //! Returns autogenerated camera name.

    const QString & getDescription() const { return m_description; }         //! Returns camera description string.
    void setDescription(const QString &description);                         //! Sets camera description string.

public:
    static GLuint  getCounter() { return counter; }                          //! Returns number of created cameras.

protected:
    void setView(const QMatrix4x4 &view) { m_view = view; }                                        //! Sets camera view matrix.
    void setProjection(const QMatrix4x4 &projection) { m_projection = projection; }                //! Sets camera projection matrix.
    void setProjectionView(const QMatrix4x4 &projectionView) { m_projectionView = projectionView; }//! Sets camera projection view matrix.

    virtual const QMatrix4x4 & calculateView() override;                     //! Calculates camera view matrix and returns it.
    virtual const QMatrix4x4 & calculateProjection() override;               //! Calculates camera projection matrix and returns it.
    virtual const QMatrix4x4 & calculateProjectionView() override;           //! Calculates camera projection view matrix and returns it.

private:
    static GLuint    counter;    //! Counter of created cameras.

private:
    GLfloat                      m_fovy;          //! Y axis angle (FOVY), 100.0f by default.

    GLfloat                      m_width;         //! Projection cut width, 640.0f by default.
    GLfloat                      m_height;        //! Projection cut height, 480.0f by default.

    GLfloat                      m_zNear;         //! Distance to the nearest separation plane, 0.1f by default.
    GLfloat                      m_zFar;          //! Distance to the further separation plane, 100.0f by default.

    QVector3D                    m_position;      //! Camera position in 3D space, { 0.0f, 0.0f, 1.0f } by default.
    QVector3D                    m_gazePoint;     //! Point in 3D scape at which camera is looking, { 0.0f, 0.0f, 0.0f } by default.
    QVector3D                    m_upperDirection;//! Upper direction vector from camera eye, { 0.0f, 1.0f, 0.0f } by default.

    QMatrix4x4                   m_view;          //! Camera view matrix.
    QMatrix4x4                   m_projection;    //! Camera projection matrix.
    QMatrix4x4                   m_projectionView;//! Camera projection view matrix, multiplication of projection and view matrices.

    com_defs::CameraMode         m_mode;          //! Camera projection mode, CameraMode::PERSPECTIVE by default.

    GLuint                       m_name;          //! Autogenerated camera name.

    QString                      m_description;   //! Camera description string.
};

#endif // CAMERA_H
