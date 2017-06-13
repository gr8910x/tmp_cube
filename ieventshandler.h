#ifndef IEVENTSHANDLER_H
#define IEVENTSHANDLER_H

#include "commonincludings.h"

class AppWindow;

//! Interface for SDL events handler implementation.
class IEventsHandler
{
public:
    virtual void handle(AppWindow *window) = 0; //! Handles SDL events.

    virtual ~IEventsHandler() {}
};

#endif // IEVENTSHANDLER_H
