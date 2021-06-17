#ifndef MTM_EX2_EXCEPTIONS_H
#define MTM_EX2_EXCEPTIONS_H
#include <stdexcept>
#include <string>
#include <utility>
using std::string;

namespace mtm {
    class Exception : std::exception {
    public:
        virtual const char * what() = 0;
    };

    class IllegalArgument : public Exception{
        public:
        const char * what() noexcept override{
            return "A game related error has occurred: IllegalArgument";
        }
    };

    class IllegalCell : public Exception{
        public:
        const char * what() noexcept override{
            return "A game related error has occurred: IllegalCell";
        }
    };

    class CellEmpty : public Exception{
        public:
        const char * what() noexcept override{
            return "A game related error has occurred: CellEmpty";
        }
    };

    class MoveTooFar : public Exception{
        public:
        const char * what() noexcept override{
            return "A game related error has occurred: MoveTooFar";
        }
    };

    class CellOccupied : public Exception{
        public:
        const char * what() noexcept override{
            return "A game related error has occurred: CellOccupied";
        }
    };

    class OutOfRange : public Exception{
        public:
        const char * what() noexcept override{
            return "A game related error has occurred: OutOfRange";
        }
    };

    class OutOfAmmo : public Exception{
        public:
        const char * what() noexcept override{
            return "A game related error has occurred: OutOfAmmo";
        }
    };

    class IllegalTarget : public Exception{
    public:
        const char * what() noexcept override{
            return "A game related error has occurred: IllegalTarget";
        }
    };
}


#endif //MTM_EX2_EXCEPTIONS_H
