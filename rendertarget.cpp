#include "rendertarget.h"

using namespace com_defs;

GLuint RenderTarget::counter = 0;

RenderTarget::RenderTarget() :
    m_texturesIds ( { { TargetTextures::DIFFUSE,                0 }
                    , { TargetTextures::NORMALS,                0 }
                    , { TargetTextures::DEPTH,                  0 }
                    , { TargetTextures::LIGHT,                  0 }
                    , { TargetTextures::RANGE_OF_DEPTH_BLUR,    0 }
                    , { TargetTextures::DIFFUSE_LIGHT_COMBINED, 0 }
                    , { TargetTextures::RESULT,                 0 }
                    , { TargetTextures::SHADOW_DIRECT,          0 }
                    } ),
    m_attachments ( { { TargetTextures::DIFFUSE,                0 }
                    , { TargetTextures::NORMALS,                0 }
                    , { TargetTextures::DEPTH,                  0 }
                    , { TargetTextures::LIGHT,                  0 }
                    , { TargetTextures::RANGE_OF_DEPTH_BLUR,    0 }
                    , { TargetTextures::DIFFUSE_LIGHT_COMBINED, 0 }
                    , { TargetTextures::RESULT,                 0 }
                    , { TargetTextures::SHADOW_DIRECT,          0 }
                    } )
{
    m_name = ++ RenderTarget::counter;
}

RenderTarget::RenderTarget( const RenderTarget &target ) :
    m_texturesIds      ( target.m_texturesIds ),
    m_attachments      ( target.m_attachments ),
    m_name             ( target.m_name        )
{
}

const RenderTarget & RenderTarget::operator = (const RenderTarget &target)
{
    m_texturesIds    = target.m_texturesIds;
    m_attachments    = target.m_attachments;

    return *this;
}

bool RenderTarget::operator == (const RenderTarget &target) const
{
    bool equal = false;

    if(  m_texturesIds   == target.m_texturesIds
      && m_attachments   == target.m_attachments )
    {
        equal = true;
    }

    return equal;
}

bool RenderTarget::operator != (const RenderTarget &target) const
{
    return !(*this == target);
}

void RenderTarget::setTexturesIds(const QHash<TargetTextures::Textures, GLuint> &texturesIds)
{
    m_texturesIds = texturesIds;
}

void RenderTarget::setAttachments(const QHash<TargetTextures::Textures, GLenum> &attachments)
{
    m_attachments = attachments;
}
