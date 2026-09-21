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
    r1.set_reservationID(1);
    r1.set_studentID(1001);
    r1.set_studentName("Demo Student 1001");
    r1.set_resourceID("R101");
    r1.set_reservationDate("09/20/2026");
    manager.addActiveReservation(r1);

    Reservation r2;
    r2.set_reservationID(2);
    r2.set_studentID(1002);
    r2.set_studentName("Demo Student 1002");
    r2.set_resourceID("R102");
    r2.set_reservationDate("09/20/2026");
    manager.addActiveReservation(r2);

    manager.displayAllActiveReservation();

    // The waiting demo list
    manager.addToWaitingList("1003", "R101");
    manager.addToWaitingList("1004", "R102");
    manager.displayWaitingList();

    // The cancel of r1
    std::string cancelId = std::to_string(r1.get_reservationID());
    bool cancelled = cancelHistory.cancel(r1, [&manager, cancelId] (const Reservation&) {
        return manager.removeActiveReservation(cancelId);
    });
    if (cancelled) {
        std::cout << "Reservation " << cancelId << " cancelled.\n";
    } else {
        std::cout << "Could not cancel reservation " << cancelId << ".\n";
    }

    manager.displayAllActiveReservation();

    std::cout << "\n--- Cancellation History ---\n";
    cancelHistory.displayHistory(std::cout);

    // The undo of most recent cancellation
    auto result = cancelHistory.undo([&manager](const Reservation& reservation) {
        if (!manager.canRestoreReservation(reservation)) return false;
        manager.addActiveReservation(reservation);
        return true;
    });

    switch (result) {
        case CancellationStack::UndoResult::Restored: std::cout << "\nMost recent cancellation restored.\n";
        break;
        case CancellationStack::UndoResult::Empty: std::cout << "\nNothing to restore.\n";
        break;
        case CancellationStack::UndoResult::Blocked: std::cout << "\nRestore was blocked.\n";
        break;
    }

    manager.displayAllActiveReservation();

    std::cout << "\n--- Cancellation History After Undo ---\n";
    cancelHistory.displayHistory(std::cout);

    return 0;
}
