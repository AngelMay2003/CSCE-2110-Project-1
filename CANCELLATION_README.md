# Cancellation history

CancellationHistory.h implements a custom linked stack. CancellationStack.h and CancellationStack.cpp adapt display to the existing Reservation class. No std::stack is used. The tests use std::list only as an isolated fixture, not as a replacement for the required manager linked list.

## Connect to the menu

Include CancellationStack.h and create one persistent `CancellationStack history;` outside the menu loop. Retrieve the actual full reservation before cancellation. The manager must add getActiveReservation and canRestoreReservation as described in TEAM_FIXES.md.

```cpp
Reservation saved;
if (manager.getActiveReservation(id, saved)) {
    bool cancelled = history.cancel(saved, [&](Reservation r) {
        return manager.removeActiveReservation(std::to_string(r.get_reservationID()));
    });
    if (!cancelled) std::cout << "Cancellation failed.\n";
} else {
    std::cout << "Reservation not found.\n";
}

auto result = history.undo([&](Reservation r) {
    if (!manager.canRestoreReservation(r)) return false;
    manager.addActiveReservation(r);
    return true;
});
if (result == CancellationStack::UndoResult::Empty)
    std::cout << "Nothing to undo.\n";
else if (result == CancellationStack::UndoResult::Blocked)
    std::cout << "Restoration blocked.\n";
else
    std::cout << "Reservation restored.\n";

history.displayHistory(std::cout);
```

This example preserves the current manager string-ID interface. The two new manager methods above are integration requirements, not existing methods. Actual callbacks must also maintain resource availability. They must leave the active system unchanged when returning false or throwing and must not modify history directly. Restoration must insert a copy, not retain a reference. If insertion can silently reject a request, change it to return success/failure and use that result.

Cancellation copies before deleting the active node. Failed cancellation removes the tentative history entry. Undo pops only after successful restoration; blocked undo retains the entry. Display is newest first and does not modify the stack. Iterative destruction frees nodes; copying the stack object is disabled to avoid double deletion.

## CELL test command

After fixing Reservation.cpp's two getter mismatches, from the repository root:

```sh
mkdir -p build
g++ -std=c++11 -Wall -Wextra -Wpedantic -Iinclude src/Reservation.cpp src/CancellationStack.cpp tests/test_cancellation_stack.cpp -o build/test_cancellation
./build/test_cancellation
```

Expected output: `Cancellation stack tests passed.` Do not compile the test main into the application. Build the completed application separately with `g++ -std=c++11 -Wall -Wextra -Wpedantic -Iinclude src/*.cpp -o build/reservations` after the existing errors are corrected. Run integrated menu, waiting-list, availability, and undo tests on CELL.

Headers belong in include/, CancellationStack.cpp in src/, and tests in tests/. ComplexityAnalysis.md is at the root. No existing teammate files are replaced. Record actual reviewed/integrated work, test results, and real commits/PRs in the group contribution report. This component alone is not the full team submission.
