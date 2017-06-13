#ifndef OPENGLAPIFUNCTIONS_H
#define OPENGLAPIFUNCTIONS_H

// OpenGL GLEW
#undef main
#ifdef _WIN32
    #define GLEW_STATIC
    #include "glew.h"
#else
    #include "GL/gl.h"
    #include "GL/glu.h"
#endif // _WIN32

#endif // OPENGLAPIFUNCTIONS_H
