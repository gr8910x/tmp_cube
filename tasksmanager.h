#ifndef TASKSMANAGER_H
#define TASKSMANAGER_H

#include "commonincludings.h"
#include "itasksmanager.h"

//! Implements engine tasks manager.
class TasksManager : public ITasksManager
{
public:
    TasksManager( const QString &description = "Empty description" );      //! Default constructor.
    TasksManager( TasksManager &tasksManager ) = delete;                   //! Copying constructor.

    virtual ~TasksManager() {}

    virtual uint howMany() override;                            //! Returns number of active tasks.
    virtual bool isDepleted() override;                         //! Returns true if there is no more active tasks.
    virtual void start( std::function<QString ()> lambdaTask    //! Starts execution of lambda task.
                      , std::launch policy = std::launch::deferred
                      ) noexcept(false) override;
    virtual void receiveAll() noexcept(false) override;         //! Waits for all tasks to complete and receives results and exceptions.

public:
    uint getNumOfTasks() const { return m_numOfTasks.load(); }      //! Returns number of currently active tasks.

    const std::vector<std::future<QString> > & getFutureResults() const { return m_futureResults; }//! Returns asynchronous operations results.
    std::vector<std::future<QString> > & getFutureResults() { return m_futureResults; }            //! Returns asynchronous operations results, overloaded function.

    uint getName() const { return m_name; }                             //! Returns autogenerated name of tasks manager.

    const QString & getDescription() const { return m_description; }    //! Returns tasks manager description.
    void setDescription(const QString &description);                    //! Sets tasks manager description.

public:
    static uint getCounter() { return counter; }                        //! Returns number of created tasks managers objects.

protected:
    virtual uint increase() override;                //! Increases number of active tasks and returns their amount.
    virtual uint decrease() override;                //! Decreases number of active tasks and returns their amount.

    void setNumOfTasks(uint numOfTasks);                            //! Sets number of currently active tasks.

private:
    static uint counter;               //! Counter of created tasks managers objects.

private:
    std::atomic<uint>  m_numOfTasks; //! Number of currently active tasks.
    std::vector<std::future<QString> > m_futureResults;//! Results of asynchronous operations.

    uint               m_name;         //! Autogenerated name of tasks manager.

    QString            m_description;  //! Description of tasks manager.
};

#endif // TASKSMANAGER_H
