#ifndef ENGINE_H
#define ENGINE_H

#include "commonincludings.h"
#include "enginecontext.h"
#include "tasksmanager.h"
#include "iengine.h"

//! Engine class which manages entire rendering process, objects creating and user input.
class Engine : public IEngine
{
public:
    Engine();                                                       //! Default constructor.
    Engine( const QString &engineDescription                        //! Parameterized constructor.
          , Uint32         sdlInitFlags                    = SDL_INIT_EVERYTHING
          , const QString &engineContextDescription        = "Empty description"
          , const QString &engineTasksManagerDescription   = "Empty description"
          );

    Engine( const Engine &engine ) = delete;                        //! Copying constructor.

    virtual ~Engine();

    virtual void init() noexcept(false) override;                   //! Initializes engine and SDL library.
    virtual void close() override;                                  //! Closes and deinitializes engine.

    const Engine & operator = (const Engine &engine);               //! Operator " =  ".

public:
    const EngineContext & getContext() const { return m_context; }  //! Returns engine context.
    EngineContext & getContext() { return m_context; }              //! Returns engine context, overloaded function.

    Uint32 getSDLInitFlags() const { return m_sdlInitFlags; }       //! Returns SDL initialization flags bitmask.
    void setSDLInitFlags(Uint32 sdlInitFlags);                      //! Sets SDL initialization flags bitmask.

    uint getStatus() const { return m_status; }                     //! Returns engine status bitmask.
    uint getName() const { return m_name; }                         //! Returns autogenerated name of engine.

    const TasksManager & getTasksManager() const { return m_tasksManager; }//! Returns engine tasks manager object.
    TasksManager & getTasksManager() { return m_tasksManager; }            //! Returns engine tasks manager object, overloaded function.

    const QString & getDescription() const { return m_description; }//! Returns engine object description.
    void setDescription(const QString &description);                //! Sets engine object description.

    bool isInited() const;                                          //! Returns true if engine was initialized.

public:
    static uint getCounter() { return counter; }                    //! Returns number of created engine objects.

protected:
    void setEngineContext(const EngineContext &context) { m_context = context; }//! Sets engine context.
    void setStatus(uint status) { m_status = status; }              //! Sets engine status bitmask.

private:
    static uint counter;            //! Counter of created engine objects.

private:
    EngineContext       m_context;  //! Engine context.

    Uint32              m_sdlInitFlags;//! SDL initialization flags bitmask, SDL_INIT_EVERYTHING by default.

    uint                m_name;     //! Autogenerated name of engine.
    uint                m_status;   //! Engine status bitmask.

    TasksManager        m_tasksManager;//! Engine tasks manager object.

    QString             m_description;//! Description of engine object.
};

#endif // ENGINE_H
