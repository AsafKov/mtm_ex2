#ifndef MTM_EX2_EXCEPTIONS_H
#define MTM_EX2_EXCEPTIONS_H
#include <stdexcept>
#include <string>
#include <utility>
using std::string;

namespace mtm {
    class Exceptions : std::exception {
    protected:
        const char * what() const noexcept override;
    };

    class IllegalArgument : public Exceptions{
        public:
        const char * what() const noexcept override{
            return "A game related error occurred: IllegalArgument";
        }
    };

    class IllegalCell : public Exceptions{
        public:
        const char * what() const noexcept override{
            return "A game related error occurred: IllegalCell";
        }
    };

    class CellEmpty : public Exceptions{
        public:
        const char * what() const noexcept override{
            return "A game related error occurred: CellEmpty";
        }
    };

    class MoveTooFar : public Exceptions{
        public:
        const char * what() const noexcept override{
            return "A game related error occurred: MoveTooFar";
        }
    };

    class CellOccupied : public Exceptions{
        public:
        const char * what() const noexcept override{
            return "A game related error occurred: CellOccupied";
        }
    };

    class OutOfRange : public Exceptions{
        public:
        const char * what() const noexcept override{
            return "A game related error occurred: OutOfRange";
        }
    };

    class OutOfAmmo : public Exceptions{
        public:
        const char * what() const noexcept override{
            return "A game related error occurred: OutOfAmmo";
        }
    };

    class IllegalTarget : public Exceptions{
    public:
        const char * what() const noexcept override{
            return "A game related error occurred: IllegalTarget";
        }
    };
}


#endif //MTM_EX2_EXCEPTIONS_H
