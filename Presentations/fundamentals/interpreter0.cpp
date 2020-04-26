
#include <iostream>
#include <fstream>
#include <stack>


class interpreter 
{
    std::fstream filestream_;
    std::stack<int> stack_;
public:
    interpreter(const std::string &filename)
    :filestream_(filename)
    {
    }
    
    void run()
    {
        while(true)
        {
            std::string cmd;
            filestream_ >> cmd;
            if(cmd == "exit")
                return;
            if(cmd == "push")
            {
                push();
            }
            if(cmd == "print")
            {
                print();
            }
            if(cmd == "add")
            {
                add();
            }
        }
    }

private:

    void push()
    {
        int val(0);
        filestream_ >> val;
        stack_.push(val);
    }

    void print()
    {
        int top = stack_.top();
        std::cout << top;
    }

    void add()
    {
        int first = stack_.top();
        stack_.pop();
        int second = stack_.top();
        stack_.pop();
        int res = first + second;
        stack_.push(res);
    }

};