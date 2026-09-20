#include "CancellationStack.h"
void CancellationStack::displayHistory(std::ostream& out) const {
    display(out, [](std::ostream& stream, const Reservation& saved) {
        // Current team getters are non-const; inspect a value copy.
        Reservation reservation = saved;
        stream << "Reservation ID: " << reservation.get_reservationID()
               << " | Student ID: " << reservation.get_student()
               << " | Student: " << reservation.get_studentName()
               << " | Resource: " << reservation.get_resourceID()
               << " | Date: " << reservation.get_reservationDate();
    });
}
