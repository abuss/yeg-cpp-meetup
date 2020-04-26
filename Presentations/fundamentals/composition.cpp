
// consider the following case

class helper_base
{
protected:
    void help_me_obiwan();
    int help_me_oprah();
};


class concrete_1 
{
    helper_base helper_;

public:
    void compute_something() 
    {
        if(helper_.help_me_oprah() == 0)
        {
            helper_.help_me_obiwan();
        }
    }
};


class concrete_2
{
    helper_base &helper_;

public:
    concrete_2(helper_base &helper)
        :helper_(helper)
    {
    }

};