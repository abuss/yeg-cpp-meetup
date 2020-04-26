


const int & get_value()
{
    int value = 5;
    return value;
}



struct foo 
{
    bool bar();
};

struct foo_factory
{
    // caller must delete or call free
    static foo* make_foo();
    static void free_foo(foo *f);
};

// What could go wrong?
void can_something_go_wrong()
{
    foo *f = new foo();

    f->bar();

    delete f;
}

void who_does_what()
{
    foo * f = foo_factory::make_foo();
    if(!f->bar())
        return;

    foo_factory::free_foo(f);
}




class SafeFoo
{
private:
    foo *f_;
public:

    SafeFoo()
    {
        f_ = foo_factory::make_foo();
    }

    ~SafeFoo()
    {
        foo_factory::free_foo(f_);
    }

    SafeFoo(const SafeFoo &)=delete;
    SafeFoo& operator=(const SafeFoo&)=delete;

    SafeFoo(SafeFoo &&)=delete;
    SafeFoo& operator=(SafeFoo&&)=delete;

    void bar()
    {
        f_->bar();
    }
};

// by value
void call_me_maybe(foo f);

// by pointer
void call_me_maybe(foo *f);

// by reference
void call_me_maybe(foo& f);

// by rvalue reference
void call_me_maybe(foo &&f);

// by const pointer
void call_me_maybe(const foo *f);

// by const reference
void call_me_maybe(const foo &f);

// by const value
void call_me_maybe(const foo f);

foo* find_me_maybe(const foo arr[]);


