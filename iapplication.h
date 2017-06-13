#ifndef IAPPLICATION_H
#define IAPPLICATION_H

//! Interface for application implementation.
class IApplication
{
public:
    virtual void run() noexcept(false) = 0;   //! Runs application object.

    virtual ~IApplication() {}
    
};

#endif // IAPPLICATION_H
