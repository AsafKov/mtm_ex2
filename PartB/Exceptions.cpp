#include "Exceptions.h"

mtm::Exception::Exception(const string &message) : message(ERROR_MESSAGE + message){}

const char *mtm::Exception::what() const noexcept {
    return message.c_str();
};

mtm::IllegalArgument::IllegalArgument() : Exception(ILLEGAL_ARGUMENT){};

mtm::IllegalCell::IllegalCell() : Exception(ILLEGAL_CELL){};

mtm::OutOfAmmo::OutOfAmmo() : Exception(OUT_OF_AMMO){};

mtm::MoveTooFar::MoveTooFar() : Exception(MOVED_TOO_FAR){};

mtm::CellEmpty::CellEmpty() : Exception(CELL_EMPTY){};

mtm::IllegalTarget::IllegalTarget() : Exception(ILLEGAL_TARGET){};

mtm::CellOccupied::CellOccupied() : Exception(CELL_OCCUPIED){};

mtm::OutOfRange::OutOfRange() : Exception(OUT_OF_RANGE){};

