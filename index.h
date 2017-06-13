#ifndef INDEX_H
#define INDEX_H

#include "commonincludings.h"

//! Implements OpenGL index used for indexing vertices.
class Index
{
public:
    Index();                                                //! Default constructor.
    Index(GLfloat index);                                   //! Parameterized constructor.

    Index(const Index &index);                              //! Copying constructor.

    virtual ~Index() {}

    const Index & operator = (const Index &index);          //! Operator " =  ".
    bool  operator == (const Index &index) const;           //! Operator " == ".
    bool  operator != (const Index &index) const;           //! Operator " != ".

public:
    const GLuint & getIndex() const { return m_index; }     //! Returns index.
    GLuint & getIndex() { return m_index; }                 //! Returns index, overloaded function.
    void setIndex(GLuint index) { m_index = index; }        //! Sets index.    

public:
    static GLuint64 getCounter() { return counter; }        //! Returns number of created indices objects.

private:
    static GLuint64  counter;           //! Counter of created indices.

private:
    GLuint      m_index;                //! Index field.

};

#endif // INDEX_H
