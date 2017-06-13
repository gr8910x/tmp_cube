#include "index.h"

GLuint64 Index::counter = 0;

Index::Index() :
    m_index ( 0      )
{
    ++ Index::counter;
}

Index::Index(GLfloat index) :
    m_index ( index )
{
    ++ Index::counter;
}

Index::Index(const Index &index) :
    m_index  ( index.m_index )
{    
}

const Index & Index::operator = (const Index &index)
{
    m_index = index.m_index;

    return *this;
}

bool Index::operator == (const Index &index) const
{
    bool equal = false;

    if( m_index == index.m_index )
    {
        equal = true;
    }

    return equal;
}

bool Index::operator != (const Index &index) const
{
    return !(*this == index);
}
