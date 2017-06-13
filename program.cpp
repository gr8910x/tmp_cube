#include "program.h"
#include "programexception.h"

using namespace com_defs;

GLuint Program::counter = 0;

Program::Program() :
    m_vertexShader   (                             ),
    m_fragmentShader (                             ),
    m_id             (  0                          ),
    m_description    (  "Empty description"        ),
    m_using          (  false                      ),
    m_status         (  ProgramStatus::NOT_CREATED
                      | ProgramStatus::NOT_LINKED  )
{
    m_name = ++ Program::counter;
}

Program::Program( const VertexShader   &vertexShader
                , const FragmentShader &fragmentShader ) :
    m_vertexShader    (  vertexShader               ),
    m_fragmentShader  (  fragmentShader             ),
    m_id              (  0                          ),
    m_description     (  "Empty description"        ),
    m_using           (  false                      ),
    m_status          (  ProgramStatus::NOT_CREATED
                       | ProgramStatus::NOT_LINKED  )
{
    m_name = ++ Program::counter;
}

Program::Program( const VertexShader   &vertexShader
                , const FragmentShader &fragmentShader
                , const QString        &description ) :
    m_vertexShader   (  vertexShader               ),
    m_fragmentShader (  fragmentShader             ),
    m_id             (  0                          ),
    m_description    (  description                ),
    m_using          (  false                      ),
    m_status         (  ProgramStatus::NOT_CREATED
                      | ProgramStatus::NOT_LINKED  )
{
    m_name = ++ Program::counter;
}

Program::Program( const QString &vertexPath
                , const QString &fragmentPath ) :
    m_vertexShader   (  vertexPath                 ),
    m_fragmentShader (  fragmentPath               ),
    m_id             (  0                          ),
    m_description    (  "Empty description"        ),
    m_using          (  false                      ),
    m_status         (  ProgramStatus::NOT_CREATED
                      | ProgramStatus::NOT_LINKED  )
{
    m_name = ++ Program::counter;
}

Program::Program( const QString &vertexPath
                , const QString &fragmentPath
                , const QString &description ) :
    m_vertexShader   (  vertexPath                 ),
    m_fragmentShader (  fragmentPath               ),
    m_id             (  0                          ),
    m_description    (  description                ),
    m_using          (  false                      ),
    m_status         (  ProgramStatus::NOT_CREATED
                      | ProgramStatus::NOT_LINKED  )
{
    m_name = ++ Program::counter;
}

Program::Program( const QString &vertexPath
                , const QString &vertexDescription
                , const QString &fragmentPath
                , const QString &fragmentDescription
                , const QString &programDescription ) :
    m_vertexShader   (  vertexPath,   vertexDescription   ),
    m_fragmentShader (  fragmentPath, fragmentDescription ),
    m_id             (  0                                 ),
    m_description    (  programDescription                ),
    m_using          (  false                             ),
    m_status         (  ProgramStatus::NOT_CREATED
                      | ProgramStatus::NOT_LINKED         )
{
    m_name = ++ Program::counter;
}

Program::~Program()
{
    stopUse();
    m_vertexShader.remove(m_id);
    m_fragmentShader.remove(m_id);
    remove();
}

Program::Program( const Program &program ) :
    m_vertexShader    ( program.m_vertexShader   ),
    m_fragmentShader  ( program.m_fragmentShader ),
    m_id              ( program.m_id             ),
    m_name            ( program.m_name           ),
    m_description     ( program.m_description    ),
    m_using           ( program.m_using          ),
    m_status          ( program.m_status         )
{
}

GLuint Program::create() noexcept(false)
{
    m_vertexShader.read();
    m_fragmentShader.read();
    m_vertexShader.create();
    m_fragmentShader.create();

    m_id = glCreateProgram();

    m_status &= ~ProgramStatus::NOT_CREATED;

    glAttachShader(m_id, m_vertexShader.getId()   );
    glAttachShader(m_id, m_fragmentShader.getId() );

    return m_id;
}

GLuint Program::link() noexcept(false)
{
    glLinkProgram(m_id);

    GLint success = 0;
    glGetProgramiv(m_id, GL_LINK_STATUS, &success);

    ( success == GL_FALSE ) ? m_status |=  ProgramStatus::NOT_LINKED   // Changing status.
                            : m_status &= ~ProgramStatus::NOT_LINKED;

    if( (m_status & ProgramStatus::NOT_LINKED) == ProgramStatus::NOT_LINKED )
    {
        GLint maxLength = 0;
        glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &maxLength);

        QVector<GLchar> errorLog(maxLength);
        glGetProgramInfoLog(m_id, maxLength, &maxLength, &errorLog[0]);
        QString errorString;

        for( const GLchar &letter: errorLog )
        {
            errorString += letter;
        }

        errorString = errorString.trimmed();

        throw ProgramException(this, "Program exception occured", errorString);
    }

    m_vertexShader.remove(m_id);
    m_fragmentShader.remove(m_id);

    return m_id;
}

GLuint Program::use() noexcept(false)
{
    if( m_status == ProgramStatus::FINE )
    {
        glUseProgram(m_id);
        m_using = true;
    }
    else
    {        
        throw ProgramException(this, "Program exception occured");
    }

    return m_id;
}

GLuint Program::stopUse()
{
    glUseProgram(0);
    m_using = false;
    return m_id;
}

GLuint Program::remove()
{
    GLuint id = m_id;
    if( (m_status & ProgramStatus::NOT_CREATED) != ProgramStatus::NOT_CREATED )
    {
        glDeleteProgram(m_id);
        m_status |= ( ProgramStatus::NOT_CREATED | ProgramStatus::NOT_LINKED );
        m_id = 0;
    }

    return id;
}

const Program & Program::operator = (const Program &program)
{
    m_vertexShader      = program.m_vertexShader;
    m_fragmentShader    = program.m_fragmentShader;
    m_description       = program.m_description;

    return *this;
}

bool Program::operator == (const Program &program) const
{
    bool equal = false;

    if(  m_vertexShader    == program.m_vertexShader
      && m_fragmentShader  == program.m_fragmentShader
      )
    {
        equal = true;
    }

    return equal;
}

bool Program::operator != (const Program &program) const
{
    return !(*this == program);
}

void Program::setVertexShader(const VertexShader &vertexShader)
{
    m_vertexShader = vertexShader;
}

void Program::setFragmentShader(const FragmentShader &fragmentShader)
{
    m_fragmentShader = fragmentShader;
}

void Program::setDescription(const QString &description)
{
    m_description = description;
}

std::shared_ptr<Program> Program::createObject()
{
    return std::make_shared<Program>();
}
