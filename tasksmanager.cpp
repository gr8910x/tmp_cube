#include "tasksmanager.h"

uint TasksManager::counter = 0;

TasksManager::TasksManager( const QString &description ) :
    m_numOfTasks    ( 0           ),
    m_futureResults (             ),
    m_description   ( description )
{
    m_name = ++ TasksManager::counter;
}

uint TasksManager::increase()
{
    m_numOfTasks ++;

    return m_numOfTasks.load();
}

uint TasksManager::decrease()
{
    m_numOfTasks --;

    return m_numOfTasks.load();
}

uint TasksManager::howMany()
{
    return getNumOfTasks();
}

bool TasksManager::isDepleted()
{
    return ( m_numOfTasks.load() <= 0 );
}

void TasksManager::start(std::function<QString ()> lambdaTask, std::launch policy)
{
    m_futureResults.push_back(  std::async(  policy                                   // Launching task.
                                          ,  [lambdaTask, this] () -> QString {

                                                 increase();                          // Increasing number of launched tasks.
                                                 QString value = lambdaTask();        // Executing lambda task.
                                                 decrease();                          // Decreasing number of launched tasks.

                                                 return value;
                                             })
                                );
}

void TasksManager::receiveAll()
{
    for( size_t i = 0; i < m_futureResults.size(); ++i )
    {
        if( m_futureResults[i].valid() )
        {
            m_futureResults[i].get();     // Receiving result.
        }
    }
}

void TasksManager::setNumOfTasks(uint numOfTasks)
{
    m_numOfTasks = numOfTasks;
}

void TasksManager::setDescription(const QString &description)
{
    m_description = description;
}
