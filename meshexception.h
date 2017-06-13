#ifndef MESHEXCEPTION_H
#define MESHEXCEPTION_H

#include "commonincludings.h"
#include "commonexception.h"

class Mesh;

//! Implements exceptions linked with OpenGL mesh objects.
class MeshException : public CommonException
{
public:
    MeshException() noexcept;                                                          //! Default constructor.
    MeshException( const QString &message ) noexcept;                                  //! Parameterized constructor.
    MeshException( Mesh          *mesh    ) noexcept;                                  //! Parameterized constructor.
    MeshException( Mesh          *mesh                                                 //! Parameterized constructor.
                 , const QString &message ) noexcept;

    MeshException( const MeshException &exception ) noexcept;                          //! Copying constructor.

    virtual ~MeshException() {}   

    const MeshException & operator = (const MeshException &exception) noexcept;        //! Operator " =  ".
    bool  operator == (const MeshException &exception) const noexcept;                 //! Operator " == ".
    bool  operator != (const MeshException &exception) const noexcept;                 //! Operator " != ".

public:
    const Mesh * getMesh() const noexcept { return m_mesh; }                           //! Returns pointer to mesh object where exception occured.
    Mesh * getMesh() noexcept { return m_mesh; }                                       //! Returns pointer to mesh object where exception occured, overloaded function.
    void setMesh(Mesh *mesh) noexcept;                                                 //! Sets pointer to mesh object where exception occured.

public:
    static uint  getCounter() { return counter; }                                      //! Returns number of created mesh exceptions objects.

protected:
    virtual const QByteArray & fillInfoBytes() noexcept override;                      //! Fills info bytes array with bytes and returns it.

private:
    static uint  counter;             //! Counter of created mesh exceptions objects.

private:
    Mesh *       m_mesh;              //! A pointer to the mesh object where exception occurred.
};

#endif // MESHEXCEPTION_H
