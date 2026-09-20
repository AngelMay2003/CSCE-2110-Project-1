#include <iostream>
#include <string>
#include "ReservationManager.h"
#include "CancellationStack.h"
#include "Reservation.h"

int main() {
    ReservationManager manager;
    CancellationStack cancelHistory;
    
    // -- This is building a couple of reservation
    Reservation r1;
    r1.set_reservationID();
    r1.set_studentID();
    r1.set_StudentName();
    r1.set_resourceID();
    r1.set_reservationDate();
    manager.addActiveReservation(r1);

    Reservation r2;
    r2.set_reservationID();
    r2.set_studentID();
    r2.set_StudentName();
    r2.set_resourceID();
    r2.set_reservationDate();
    manager.addActiveReservation(r2);

    manager.displayAllActiveReservation();

    // The waiting demo list
    manager.addToWaitingList();
    manager.addToWaitingList();
    manager.displayWaitingList();

    // The cancel of r1
    std::string cancelId = std::to_string(r1.get_reservationID());
    bool cancelled = cancelHistory.cancel(r1, [&manager, cancelId] (const Reservation&)) {
        return manager.removeActiveReservation(cancelId);
    });
    if (cancelled) {
        cout << "Reservation " << cancelId << " cancelled.\n";
    } else {
        cout << "Could not cancel reservation " << cancelId << ".\n";
    }

    manager.displayAllActiveReservation();

    cout << "\n--- Cancellation History ---\n";
    cancelHistory.displayHistory(cout);

    // The undo of most recent cancellation
    auto result = cancelHistory.undo([&manager](const Reservation& reservation) {
        manager.addActiveResrvation(reservation);
        return true;
    });

    switch (result) {
        case CancellationStack::UndoResult::Restored: cout << "\nMost recent cancellation restored.\n";
        break;
        case CancellationStack::UndoResult::Empty: cout << "\nNothing to restore.\n";
        break;
        case CancellationStack::UndoResult::Blocked: cout << "\nRestore was blocked.\n";
        break;
    }

    manager.displayAllActiveReservation();

    cout << "\n--- Cancellation History After Undo ---\n";
    cancelHistory.displayHistory(cout);

    return 0;
}
