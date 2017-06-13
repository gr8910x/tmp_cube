#include "commonincludings.h"
#include "application.h"

//! Main function of the program.
int main(int argc, char *argv[])
{
    Application app("Application object");      // Creating application object.

    std::thread appThread(app);                 // Starting application object thread.
    appThread.join();                           // Waiting for application thread to complete.

    //aux_funcs::initGLEW();
    //QVector<Vertex> vertices = {  Vertex()
    //                            , Vertex()
    //                            , Vertex() };
    //QVector<Index> indices   = {  Index()
    //                            , Index()
    //                            , Index()
    //                            , Index()  };
    //Mesh meshOne(vertices, indices);
    //Mesh meshTwo;
    //
    //meshTwo = meshOne;

    return 0;
}

