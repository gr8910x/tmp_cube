#include "meshexception.h"
#include "mesh.h"

using namespace com_defs;

uint MeshException::counter = 0;

MeshException::MeshException() noexcept :
    CommonException (         ),
    m_mesh          ( nullptr )
{
    ++ MeshException::counter;
    fillInfoBytes();
}

MeshException::MeshException( const QString &message ) noexcept :
    CommonException ( message ),
    m_mesh          ( nullptr )
{
    ++ MeshException::counter;
    fillInfoBytes();
}

MeshException::MeshException( Mesh *mesh ) noexcept :
    CommonException (         ),
    m_mesh          ( mesh    )
{
    ++ MeshException::counter;
    fillInfoBytes();
}

MeshException::MeshException( Mesh          *mesh
                            , const QString &message ) noexcept :
    CommonException( message ),
    m_mesh         ( mesh    )
{
    ++ MeshException::counter;
    fillInfoBytes();
}

MeshException::MeshException(const MeshException &exception) noexcept:
    CommonException ( exception        ),
    m_mesh          ( exception.m_mesh )
{
}

const MeshException & MeshException::operator = (const MeshException &exception) noexcept
{
    CommonException::operator = (exception);
    m_mesh                    = exception.m_mesh;

    return *this;
}

bool MeshException::operator == (const MeshException &exception) const noexcept
{
    bool equal = false;

    if(  CommonException::operator == (exception)
      && m_mesh                    == exception.m_mesh )
    {
        equal = true;
    }

    return equal;
}

bool MeshException::operator != (const MeshException &exception) const noexcept
{
    return !(*this == exception);
}

void MeshException::setMesh(Mesh *mesh) noexcept
{
    m_mesh = mesh;
    fillInfoBytes();
}

const QByteArray & MeshException::fillInfoBytes() noexcept
{
    QString infoString = getMessage();
    if( m_mesh )
    {
        uint status = m_mesh->getStatus();
        infoString  += QString("\n Mesh name: \t %1").arg(m_mesh->getName() )
                    +  QString(". VBO id: \t %1").arg(m_mesh->getVBOId() )
                    +  QString(", IBO id: \t %1").arg(m_mesh->getIBOId() )
                    +  QString("\n Mesh description: %1").arg(m_mesh->getDescription() );
        if( !m_mesh->isGenerated() )
        {
            infoString += "\n VBO or IBO buffers not generated.";
        }
        if( (status & MeshStatus::INVALID_VBO_BUFFER_POINTER) == MeshStatus::INVALID_VBO_BUFFER_POINTER )
        {
            infoString += "\n Invalid VBO buffer pointer.";
        }
        if( (status & MeshStatus::INVALID_IBO_BUFFER_POINTER) == MeshStatus::INVALID_IBO_BUFFER_POINTER )
        {
            infoString += "\n Invalid IBO buffer pointer.";
        }
        if( (status & MeshStatus::INVALID_VBO_UNMAPPING) == MeshStatus::INVALID_VBO_UNMAPPING )
        {
            infoString += "\n Invalid VBO unmapping.";
        }
        if( (status & MeshStatus::INVALID_IBO_UNMAPPING) == MeshStatus::INVALID_IBO_UNMAPPING )
        {
            infoString += "\n Invalid IBO unmapping.";
        }
    }
    QByteArray infoBytes = infoString.toUtf8();
    setInfoBytes(infoBytes);

    return getInfoBytes();
}
