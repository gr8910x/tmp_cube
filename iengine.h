#ifndef IENGINE_H
#define IENGINE_H

//! Interface for engine implementation.
class IEngine
{
public:
    virtual void init() noexcept(false) = 0;          //! Initializes engine and SDL library.
    virtual void close() = 0;                         //! Closes and deinitializes engine.

    virtual ~IEngine() {}
};

#endif // IENGINE_H
