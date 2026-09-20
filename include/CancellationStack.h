#ifndef CANCELLATION_STACK_H
#define CANCELLATION_STACK_H
#include "CancellationHistory.h"
#include "Reservation.h"
#include <ostream>
class CancellationStack : public CancellationHistory<Reservation> {
public:
    void displayHistory(std::ostream& out) const;
};
#endif
