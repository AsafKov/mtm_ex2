#ifndef MTM_EX2_EXCEPTIONS_H
#define MTM_EX2_EXCEPTIONS_H
#include <stdexcept>
#include <string>
#include <utility>
using std::string;

namespace mtm {
    const static string ERROR_MESSAGE = "A game related error has occurred: ";
    const static string ILLEGAL_ARGUMENT = "IllegalArgument";
    const static string ILLEGAL_CELL = "IllegalCell";
    const static string CELL_EMPTY = "CellEmpty";
    const static string MOVED_TOO_FAR = "MoveTooFar";
    const static string OUT_OF_RANGE = "OutOfRange";
    const static string CELL_OCCUPIED = "CellOccupied";
    const static string OUT_OF_AMMO = "OutOfAmmo";
    const static string ILLEGAL_TARGET = "IllegalTarget";
    class Exception : std::exception {
        string message;

    protected:
        ~Exception() override = default;
       explicit Exception(const string &message);

        Exception() = default;
    public:
        const char * what() const noexcept override;
    };

    class IllegalArgument : public Exception{
        public:
        IllegalArgument();
    };

    class IllegalCell : public Exception{
    public:
        IllegalCell();
    };

    class CellEmpty : public Exception{
    public:
        CellEmpty();
    };

    class MoveTooFar : public Exception{
    public:
        MoveTooFar();

    };

    class CellOccupied : public Exception{
    public:
        CellOccupied();

    };

    class OutOfRange : public Exception{
    public:
        OutOfRange();
    };

    class OutOfAmmo : public Exception{
    public:
        OutOfAmmo();
    };

    class IllegalTarget : public Exception{
    public:
        IllegalTarget();
    };
}


#endif //MTM_EX2_EXCEPTIONS_H
