#ifndef _CONTROLLERS_SIGNAL_LIST_HPP_
#define _CONTROLLERS_SIGNAL_LIST_HPP_

#include <list>
#include <functional>
#include <models/signal.hpp>

namespace ctrl {

namespace mes {
   enum {
      PointerDestroyed,
      SignalDestroyed
   };
}

////////////////////////////////////////////////////////////////
// \brief Object that contains information of messages between
// signal and pointers to signal.
////////////////////////////////////////////////////////////////
struct SignalMessage {
    size_t type;  // type of message
};

class SignalPointer;

////////////////////////////////////////////////////////////////
// \brief Object that contains signal and manages connections
// with pointers.
////////////////////////////////////////////////////////////////
class SignalWrapper {
 protected:
    std::list<SignalPointer*> ptrs_;  // list of pointers
    mdl::Signal signal_;              // signal

    friend SignalPointer;

 public:
    using PtrPos =
        typename std::list<SignalPointer*>::iterator;  // type of pointer
                                                       // position

	// Construct with copy signal
	SignalWrapper(const mdl::Signal& signal);
    // Construct with move Signal
    SignalWrapper(mdl::Signal&& signal);
    // Destructor
    ~SignalWrapper();

    // Methods

    // Notify signalwrapper
    virtual void notify(SignalMessage mes);
    // Send message to all pointers
    void send(SignalMessage mes);

    // Get signal pointer
    SignalPointer getPtr();
};

////////////////////////////////////////////////////////////////
// \brief Object representing pointer to signal
////////////////////////////////////////////////////////////////
class SignalPointer {
 protected:
    using Pos = typename SignalWrapper::PtrPos;  // type of pointer position

    SignalWrapper* signal_;  // pointer to signal
    Pos pos_;                // position of pointer

    // Detaches from signal
    void detach();

 public:
    // Default constructor
    SignalPointer();
    // Constructor by signal wrapper and pointer position
    SignalPointer(SignalWrapper* signal, Pos pos);
    // Copy constructor
    SignalPointer(const SignalPointer& other);
    // Move constructor
    SignalPointer(SignalPointer&& other);
    // Destructor
    ~SignalPointer();

    // Assignment operator

    // Copy constructor
    SignalPointer& operator=(const SignalPointer& other);
    // Moversing operator
    SignalPointer& operator=(SignalPointer&& other);
    // Set pointer
    SignalPointer& operator=(SignalWrapper* other);

    // Methods

    // Notify by message
    virtual void notify(SignalMessage message);
    // Send message to signal
    void send(SignalMessage message);
    // get signal const reference
    mdl::Signal& getSignal();
    // if points to signal
    bool valid() const;
};

////////////////////////////////////////////////////////////////
// \brief SignalPointer that calls function object with message.
////////////////////////////////////////////////////////////////
class FSignalPointer : public SignalPointer {
 private:
    using Self = FSignalPointer;
    using Base = SignalPointer;
    using FunctionObject = std::function<void(SignalMessage)>;

    FunctionObject function_; // function object to call

 public:
    // Constructor by signal wrapper and pointer position
    FSignalPointer(SignalWrapper* signal, Pos pos);
    // Copy constructor
    FSignalPointer(const Self& other);
    // Move constructor
    FSignalPointer(Self&& other);
    // Destructor
    ~FSignalPointer();

    // Assignment operator

    // Copy constructor
    FSignalPointer& operator=(const FSignalPointer& other);
    // Moversing operator
    FSignalPointer& operator=(FSignalPointer&& other);

    // Methods

    // Notify signal pointer
    void notify(SignalMessage mes) override;
    // Set function object
    void setFunction(FunctionObject&& function);

};

////////////////////////////////////////////////////////////////
// \brief Object representing signal list
////////////////////////////////////////////////////////////////
class SignalList {
 protected:
    std::list<SignalWrapper> signals_;  // list of signals
    static inline SignalList* instance_;       // current signal list

	// Default constructor
	SignalList();

 public:

	using Pos = std::list<SignalWrapper>::iterator; // position of signal

	// Destructor
	~SignalList();
	
	// Get instance of signal list
	static SignalList* getInstance();
	
	// Methods

	// Add signal by copy
	Pos add(const mdl::Signal& signal);
	// Add signal by move
	Pos add(mdl::Signal&& signal);
	// Remove signal by position
	void remove(Pos pos);

	// Get position of signal with index
	Pos at(size_t index);
	// Get size of signal list
	size_t size() const;

};

}  // namespace ctrl

#endif  // _CONTROLLERS_SIGNAL_LIST_HPP