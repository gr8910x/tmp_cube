#include "camera.h"

using namespace com_defs;

GLuint Camera::counter = 0;

Camera::Camera() :
    m_fovy           ( 100.0f                  ),
    m_width          ( 640.0f                  ),
    m_height         ( 480.0f                  ),
    m_zNear          ( 0.1f                    ),
    m_zFar           ( 100.0f                  ),
    m_position       ( 0.0f, 0.0f, 1.0f        ),
    m_gazePoint      ( 0.0f, 0.0f, 0.0f        ),
    m_upperDirection ( 0.0f, 1.0f, 1.0f        ),
    m_view           (                         ),
    m_projection     (                         ),
    m_projectionView (                         ),
    m_mode           ( CameraMode::PERSPECTIVE ),
    m_description    ( "Empty description"     )

{
    m_name = ++ Camera::counter;
    calculate();
}

Camera::Camera( GLfloat fovy
              , GLfloat width
              , GLfloat height
              ) :
    m_fovy           ( fovy                    ),
    m_width          ( width                   ),
    m_height         ( height                  ),
    m_zNear          ( 0.1f                    ),
    m_zFar           ( 100.0f                  ),
    m_position       ( 0.0f, 0.0f, 1.0f        ),
    m_gazePoint      ( 0.0f, 0.0f, 0.0f        ),
    m_upperDirection ( 0.0f, 1.0f, 1.0f        ),
    m_view           (                         ),
    m_projection     (                         ),
    m_projectionView (                         ),
    m_mode           ( CameraMode::PERSPECTIVE ),
    m_description    ( "Empty description"     )
{
    m_name = ++ Camera::counter;
    calculate();
}

Camera::Camera( GLfloat fovy
              , GLfloat width
              , GLfloat height
              , GLfloat zNear
              , GLfloat zFar
              ) :
    m_fovy           ( fovy                    ),
    m_width          ( width                   ),
    m_height         ( height                  ),
    m_zNear          ( zNear                   ),
    m_zFar           ( zFar                    ),
    m_position       ( 0.0f, 0.0f, 1.0f        ),
    m_gazePoint      ( 0.0f, 0.0f, 0.0f        ),
    m_upperDirection ( 0.0f, 1.0f, 1.0f        ),
    m_view           (                         ),
    m_projection     (                         ),
    m_projectionView (                         ),
    m_mode           ( CameraMode::PERSPECTIVE ),
    m_description    ( "Empty description"     )
{
    m_name = ++ Camera::counter;
    calculate();
}

Camera::Camera( const QVector3D &position
              , const QVector3D &gazePoint
              , const QVector3D &upperDirection
              ) :
    m_fovy           ( 100.0f                  ),
    m_width          ( 640.0f                  ),
    m_height         ( 480.0f                  ),
    m_zNear          ( 0.1f                    ),
    m_zFar           ( 100.0f                  ),
    m_position       ( position                ),
    m_gazePoint      ( gazePoint               ),
    m_upperDirection ( upperDirection          ),
    m_view           (                         ),
    m_projection     (                         ),
    m_projectionView (                         ),
    m_mode           ( CameraMode::PERSPECTIVE ),
    m_description    ( "Empty description"     )
{
    m_name = ++ Camera::counter;
    calculate();
}

Camera::Camera( GLfloat positionX
              , GLfloat positionY
              , GLfloat positionZ
              , GLfloat gazePointX
              , GLfloat gazePointY
              , GLfloat gazePointZ
              , GLfloat upperDirectionX
              , GLfloat upperDirectionY
              , GLfloat upperDirectionZ
              ) :
    m_fovy           ( 100.0f                                            ),
    m_width          ( 640.0f                                            ),
    m_height         ( 480.0f                                            ),
    m_zNear          ( 0.1f                                              ),
    m_zFar           ( 100.0f                                            ),
    m_position       ( positionX,       positionY,       positionZ       ),
    m_gazePoint      ( gazePointX,      gazePointY,      gazePointZ      ),
    m_upperDirection ( upperDirectionX, upperDirectionY, upperDirectionZ ),
    m_view           (                                                   ),
    m_projection     (                                                   ),
    m_projectionView (                                                   ),
    m_mode           ( CameraMode::PERSPECTIVE                           ),
    m_description    ( "Empty description"                               )
{
    m_name = ++ Camera::counter;
    calculate();
}

Camera::Camera( GLfloat           fovy
              , GLfloat           width
              , GLfloat           height
              , GLfloat           zNear
              , GLfloat           zFar
              , const QVector3D  &position
              , const QVector3D  &gazePoint
              , const QVector3D  &upperDirection
              ) :
    m_fovy           ( fovy                    ),
    m_width          ( width                   ),
    m_height         ( height                  ),
    m_zNear          ( zNear                   ),
    m_zFar           ( zFar                    ),
    m_position       ( position                ),
    m_gazePoint      ( gazePoint               ),
    m_upperDirection ( upperDirection          ),
    m_view           (                         ),
    m_projection     (                         ),
    m_projectionView (                         ),
    m_mode           ( CameraMode::PERSPECTIVE ),
    m_description    ( "Empty description"     )
{
    m_name = ++ Camera::counter;
    calculate();
}

Camera::Camera( GLfloat fovy
              , GLfloat width
              , GLfloat height
              , GLfloat zNear
              , GLfloat zFar
              , GLfloat positionX
              , GLfloat positionY
              , GLfloat positionZ
              , GLfloat gazePointX
              , GLfloat gazePointY
              , GLfloat gazePointZ
              , GLfloat upperDirectionX
              , GLfloat upperDirectionY
              , GLfloat upperDirectionZ
              ) :
    m_fovy           ( fovy                                              ),
    m_width          ( width                                             ),
    m_height         ( height                                            ),
    m_zNear          ( zNear                                             ),
    m_zFar           ( zFar                                              ),
    m_position       ( positionX,       positionY,       positionZ       ),
    m_gazePoint      ( gazePointX,      gazePointY,      gazePointZ      ),
    m_upperDirection ( upperDirectionX, upperDirectionY, upperDirectionZ ),
    m_view           (                                                   ),
    m_projection     (                                                   ),
    m_projectionView (                                                   ),
    m_mode           ( CameraMode::PERSPECTIVE                           ),
    m_description    ( "Empty description"                               )
{
    m_name = ++ Camera::counter;
    calculate();
}

Camera::Camera( GLfloat          fovy
              , GLfloat          width
              , GLfloat          height
              , GLfloat          zNear
              , GLfloat          zFar
              , const QVector3D &position
              , const QVector3D &gazePoint
              , const QVector3D &upperDirection
              , CameraMode       mode
              , const QString   &description
              ) :
    m_fovy           ( fovy                    ),
    m_width          ( width                   ),
    m_height         ( height                  ),
    m_zNear          ( zNear                   ),
    m_zFar           ( zFar                    ),
    m_position       ( position                ),
    m_gazePoint      ( gazePoint               ),
    m_upperDirection ( upperDirection          ),
    m_view           (                         ),
    m_projection     (                         ),
    m_projectionView (                         ),
    m_mode           ( mode                    ),
    m_description    ( description             )
{
    m_name = ++ Camera::counter;
    calculate();
}

Camera::Camera( GLfloat        fovy
              , GLfloat        width
              , GLfloat        height
              , GLfloat        zNear
              , GLfloat        zFar
              , GLfloat        positionX
              , GLfloat        positionY
              , GLfloat        positionZ
              , GLfloat        gazePointX
              , GLfloat        gazePointY
              , GLfloat        gazePointZ
              , GLfloat        upperDirectionX
              , GLfloat        upperDirectionY
              , GLfloat        upperDirectionZ
              , CameraMode     mode
              , const QString &description
              ) :
    m_fovy           ( fovy                                              ),
    m_width          ( width                                             ),
    m_height         ( height                                            ),
    m_zNear          ( zNear                                             ),
    m_zFar           ( zFar                                              ),
    m_position       ( positionX,       positionY,       positionZ       ),
    m_gazePoint      ( gazePointX,      gazePointY,      gazePointZ      ),
    m_upperDirection ( upperDirectionX, upperDirectionY, upperDirectionZ ),
    m_view           (                                                   ),
    m_projection     (                                                   ),
    m_projectionView (                                                   ),
    m_mode           ( mode                                              ),
    m_description    ( description                                       )
{
    m_name = ++ Camera::counter;
    calculate();
}

Camera::Camera(const Camera &camera) :
    m_fovy           ( camera.m_fovy           ),
    m_width          ( camera.m_width          ),
    m_height         ( camera.m_height         ),
    m_zNear          ( camera.m_zNear          ),
    m_zFar           ( camera.m_zFar           ),
    m_position       ( camera.m_position       ),
    m_gazePoint      ( camera.m_gazePoint      ),
    m_upperDirection ( camera.m_upperDirection ),
    m_view           ( camera.m_view           ),
    m_projection     ( camera.m_projection     ),
    m_projectionView ( camera.m_projectionView ),
    m_mode           ( camera.m_mode           ),
    m_name           ( camera.m_name           ),
    m_description    ( camera.m_description    )
{
}

void Camera::calculate()
{
    calculateView();
    calculateProjection();
    calculateProjectionView();
}

const Camera & Camera::operator = (const Camera &camera)
{
    m_fovy           = camera.m_fovy;
    m_width          = camera.m_width;
    m_height         = camera.m_height;
    m_zNear          = camera.m_zNear;
    m_zFar           = camera.m_zFar;
    m_position       = camera.m_position;
    m_gazePoint      = camera.m_gazePoint;
    m_upperDirection = camera.m_upperDirection;
    m_view           = camera.m_view;
    m_projection     = camera.m_projection;
    m_projectionView = camera.m_projectionView;
    m_mode           = camera.m_mode;
    m_description    = camera.m_description;

    return *this;
}

bool Camera::operator == (const Camera &camera) const
{
    bool equal = false;

    if(  m_fovy           == camera.m_fovy
      && m_width          == camera.m_width
      && m_height         == camera.m_height
      && m_zNear          == camera.m_zNear
      && m_zFar           == camera.m_zFar
      && m_position       == camera.m_position
      && m_gazePoint      == camera.m_gazePoint
      && m_upperDirection == camera.m_upperDirection
      && m_view           == camera.m_view
      && m_projection     == camera.m_projection
      && m_projectionView == camera.m_projectionView
      && m_mode           == camera.m_mode )
    {
        equal = true;
    }

    return equal;
}

bool Camera::operator != (const Camera &camera) const
{
    return !(*this == camera);
}

void Camera::setFovy(GLfloat fovy)
{
    m_fovy = fovy;
    if( m_mode == CameraMode::PERSPECTIVE )
    {
        calculateProjection();
        calculateProjectionView();
    }
}

void Camera::setWidth(GLfloat width)
{
    m_width = width;
    calculateProjection();
    calculateProjectionView();
}

void Camera::setHeight(GLfloat height)
{
    m_height = height;
    calculateProjection();
    calculateProjectionView();
}

void Camera::setZNear(GLfloat zNear)
{
    m_zNear = zNear;
    calculateProjection();
    calculateProjectionView();
}

void Camera::setZFar(GLfloat zFar)
{
    m_zFar = zFar;
    calculateProjection();
    calculateProjectionView();
}

void Camera::setPosition(const QVector3D &position)
{
    m_position = position;
    calculateView();
    calculateProjectionView();
}

void Camera::setPosition(GLfloat x, GLfloat y, GLfloat z)
{
    m_position.setX(x);
    m_position.setY(y);
    m_position.setZ(z);
    calculateView();
    calculateProjectionView();
}

void Camera::setGazePoint(const QVector3D &gazePoint)
{
    m_gazePoint = gazePoint;
    calculateView();
    calculateProjectionView();
}

void Camera::setGazePoint(GLfloat x, GLfloat y, GLfloat z)
{
    m_gazePoint.setX(x);
    m_gazePoint.setY(y);
    m_gazePoint.setZ(z);
    calculateView();
    calculateProjectionView();
}

void Camera::setUpperDirection(const QVector3D &upperDirection)
{
    m_upperDirection = upperDirection;
    calculateView();
    calculateProjectionView();
}

void Camera::setUpperDirection(GLfloat x, GLfloat y, GLfloat z)
{
    m_upperDirection.setX(x);
    m_upperDirection.setY(y);
    m_upperDirection.setZ(z);
    calculateView();
    calculateProjectionView();
}

void Camera::setMode(CameraMode mode)
{
    m_mode = mode;
    calculateProjection();
    calculateProjectionView();
}

void Camera::setDescription(const QString &description)
{
    m_description = description;
}

const QMatrix4x4 & Camera::calculateView()
{
    m_view.setToIdentity();
    m_view.lookAt(m_position, m_gazePoint, m_upperDirection);

    return m_view;
}

const QMatrix4x4 & Camera::calculateProjection()
{
    switch ( m_mode )
    {
    case CameraMode::ORTHOGRAPHIC:
        m_projection.setToIdentity();
        //glOrtho ((float)-w/(float)h, (float)w/(float)h, -1, 1, 0.8, 100);
        m_projection.ortho( - (m_width  / m_height) * ORTHOGRAPHIC_CAMERA_SCALE
                          ,   (m_width  / m_height) * ORTHOGRAPHIC_CAMERA_SCALE
                          , - 1.0f * ORTHOGRAPHIC_CAMERA_SCALE
                          ,   1.0f * ORTHOGRAPHIC_CAMERA_SCALE
                          , m_zNear
                          , m_zFar );
        break;
    case CameraMode::PERSPECTIVE:
        m_projection.setToIdentity();
        m_projection.perspective(m_fovy, m_width / m_height, m_zNear, m_zFar);
        break;
    }

    return m_projection;
}

const QMatrix4x4 & Camera::calculateProjectionView()
{
    m_projectionView = m_projection * m_view;

    return m_projectionView;
}
