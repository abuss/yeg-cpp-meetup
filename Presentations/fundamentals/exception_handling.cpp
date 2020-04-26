

#include <exception>
#include <stdexcept>

struct foo;

foo * make_foo();
void release_foo(foo *);

// Prefer compile time checks where possible

void do_something(const foo * f)
{
    if(f == nullptr)
        throw std::logic_error("f cannot be null");
    // do something
}

// vs 

void do_something(const foo &f)
{
    // do something
}


// static assert preconditions


// report errors immediately when they occur

class foo_fighter
{
    enum state { idle, running, complete };
    state state_;
public:

    foo_fighter()
    :state_(idle)
    {
    }

    void run()
    {    
        foo* f = make_foo();

        if(state_ != state::idle)
            throw std::runtime_error("invalid state");
        
        state_ = state::running;

        if( f == nullptr)
            throw std::runtime_error("could not make foo");

        // ....

        release_foo(f);
        
    }

};

// vs.

class foo_fighter
{
    enum state { idle, running, complete };
    state state_;
public:

    foo_fighter()
    :state_(idle)
    {
    }

    void run()
    {    
        if(state_ != state::idle)
            throw std::runtime_error("invalid state");
        
        foo* f = make_foo();

        if( f == nullptr)
            throw std::runtime_error("could not make foo");
        
        state_ = state::running;
        
        // ....

        release_foo(f);
    }

};

// better yet. Use RAII
class foo_ptr
{
    foo *f_;
public:
    foo_ptr()
    :f_(make_foo())
    {
        if(f_ == nullptr)
            throw std::runtime_error("could not make foo");
    }

    ~foo_ptr ()
    {
        release_foo(f_);
    }
    // properators

};

class foo_fighter
{
    enum state { idle, running, complete };
    state state_;
public:

    foo_fighter()
    :state_(idle)
    {
    }

    void run()
    {    
        if(state_ != state::idle)
            throw std::runtime_error("invalid state");
        
        foo_ptr f;
        
        state_ = state::running;

        // ...
    }

};

struct input;
struct datastore;
class input_exception;
class datastore_exception;
class timeout_exception;

void report(const char *message);
void retry(const std::string &statement);


void read_and_store(input &i, datastore &d)
{
    try
    {
        const std::string statement = i.read();
        d.store(statement);
        
    }
    catch(const input_exception &e)
    {
        report(e.what());
    }
    catch(const datastore_exception& e)
    {
        report(e.what());
    }
    
}

