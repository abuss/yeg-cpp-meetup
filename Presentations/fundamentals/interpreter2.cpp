
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <stack>
#include <exception>

enum kind
{
    unknown,
    literal,
    eol,
    eof
};

struct token
{
    kind type;
    std::string value;
    int line;
    int col;
};

// his job is to turn input into tokens
class lexer
{
    std::istream &stream_;

    bool iseol(char c)
    {
        return c == '\r';
    }

public:
    lexer(std::istream &stream)
        : stream_(stream)
    {
    }

    token next()
    {
        char c;
        token t;
        int line =0;
        int col = 0;
        while(stream_.get(c))
        {
            col++;
            if(std::isspace(c))
                return t;
            if(iseol(c))
            {
                t.type = kind::eol; 
                line++;
                return t;
            }

            t.value.push_back(c);
        }
        t.type = kind::eof;
        return t;
    }
};

enum operation
{
    unknown,
    push,
    print,
    add,
    exit
};

struct instruction
{
    operation op;
    int value;
};

class parse_error : public std::exception
{
    int line_;
    int col_;

public:
    parse_error(int line, int col)
        : std::exception("failed to parse"), line_(line), col_(col)
    {
    }
};

// his job is to turn the lexer into a list of
// instructions
class parser
{
    lexer &lexer_;

    enum state
    {
        unknown,
        expect_op,
        expect_value,
        expect_eol,
    };
    state state_;

public:
    parser(lexer &l)
        : lexer_(l), state_(state::expect_op)
    {
    }

    instruction next()
    {
        while (1)
        {
            instruction inst;
            auto t = lexer_.next();

            if(t.type == kind::eof)
                return instruction { operation::exit };

            switch (state_)
            {
            case state::expect_op:
            {
                if (t.type != kind::literal)
                    throw parse_error(t.col, t.line);

                state_ = parse_op(t.value, inst);
                if(state_ == state::unknown)
                    throw parse_error(t.col, t.line);
            }
            case state::expect_value:
            {
                if (t.type != kind::literal)
                    throw parse_error(t.col, t.line);
                state_ = parse_value(t.value, inst);
            }
            case state::expect_eol:
            if (t.type != kind::eol)
                    throw parse_error(t.col, t.line);
                return inst;
            }
        }
    }

private:
    state parse_op(const std::string &value, instruction &i)
    {
        if(value == "push")
        {
            i.op = operation::push;
            return state::expect_value;
        }
        if(value == "print")
        {
            i.op = operation::print;
            return state::expect_op;
        }
        if(value == "add")
        {
            i.op = operation::add;
            return state::expect_op;
        }

        return state::unknown;
    }

    state parse_value(const std::string &value, instruction &i)
    {
        std::stringstream ss(value);
        int val=0;
        ss >> val;

        i.value = val;

        return state::expect_eol;
    }
};

// his job is to run the logistics of
// our operation
class machine
{
    std::stack<int> stack_;

public:
    int top()
    {
        return stack_.top();
    }

    void add()
    {
        int first = stack_.top();
        stack_.pop();
        int second = stack_.top();
        stack_.pop();
        stack_.push(first + second);
    }

    void push(int value)
    {
        stack_.push(value);
    }
};

// his job is to combine all the different components to
// work together.
class interpreter
{
    lexer lexer_;
    parser parser_;
    machine machine_;

public:
    interpreter(std::istream &stream)
        : lexer_(stream), parser_(lexer_)
    {
    }

    void run()
    {
        while (true)
        {
            auto inst = parser_.next();
            switch (inst.op)
            {
            case operation::push:
                machine_.push(inst.value);
            case operation::print:
                std::cout << machine_.top();
            case operation::add:
                machine_.add();
            case operation::exit:
                return;
            }
        }
    }
};