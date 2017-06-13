#ifndef ITASKSMANAGER_H
#define ITASKSMANAGER_H

#include "commonincludings.h"

//! Interface for engine tasks manager implementation.
class ITasksManager
{
public:
    virtual uint howMany() = 0;                              //! Returns number of active tasks.
    virtual bool isDepleted() = 0;                           //! Returns true if there is no more active tasks.
    virtual void start( std::function<QString ()> lambda     //! Starts execution of lambda task.
                      , std::launch policy = std::launch::async
                      ) noexcept(false) = 0;
    virtual void receiveAll() noexcept(false) = 0;           //! Waits for tasks to complete and receives results and exceptions.


    virtual ~ITasksManager() {}

protected:
    virtual uint increase() = 0;          //! Increases number of active tasks and returns their amount.
    virtual uint decrease() = 0;          //! Decreases number of active tasks and returns their amount.

};

#endif // ITASKSMANAGER_H
