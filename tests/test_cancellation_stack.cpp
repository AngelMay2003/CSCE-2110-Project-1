#include "CancellationStack.h"
#include <cassert>
#include <list>
#include <sstream>
#include <stdexcept>
#include <iostream>
Reservation makeReservation(int id, const std::string& resource) {
    Reservation r;
    r.set_reservationID(id);
    r.set_studentID(1000 + id);
    r.set_studentName("Test Student");
    r.set_resourceID(resource);
    r.set_reservationDate("09/20/2026");
    return r;
}
int main() {
    CancellationStack history;
    // Fixture only; the application uses the team's custom linked list.
    std::list<Reservation> active;
    active.push_back(makeReservation(1, "R101"));
    active.push_back(makeReservation(2, "R102"));
    auto remove = [&](Reservation r) {
        for (auto it = active.begin(); it != active.end(); ++it) {
            if (it->get_reservationID() == r.get_reservationID()) {
                active.erase(it); return true;
            }
        }
        return false;
    };
    auto restore = [&](Reservation r) {
        for (auto& item : active) {
            if (item.get_reservationID() == r.get_reservationID() ||
                (item.get_resourceID() == r.get_resourceID() &&
                 item.get_reservationDate() == r.get_reservationDate()))
                return false;
        }
        active.push_front(r); return true;
    };
    using Result = CancellationStack::UndoResult;
    assert(history.empty() && history.peek() == nullptr && !history.pop());
    assert(history.undo(restore) == Result::Empty);
    assert(history.cancel(active.front(), remove));
    assert(history.cancel(active.front(), remove));
    assert(active.empty() && history.size() == 2);
    std::ostringstream first, second;
    history.displayHistory(first); history.displayHistory(second);
    assert(first.str() == second.str() && history.size() == 2);
    assert(first.str().find("Reservation ID: 2") == 0);
    assert(first.str().find("Student ID: 1002") != std::string::npos);
    active.push_back(makeReservation(3, "R102"));
    assert(history.undo(restore) == Result::Blocked && history.size() == 2);
    active.clear();
    assert(history.undo(restore) == Result::Restored);
    assert(active.front().get_reservationID() == 2);
    assert(active.front().get_studentName() == "Test Student");
    assert(active.front().get_resourceID() == "R102");
    assert(active.front().get_reservationDate() == "09/20/2026");
    assert(history.undo(restore) == Result::Restored);
    assert(active.front().get_reservationID() == 1 && history.empty());
    assert(!history.cancel(makeReservation(99, "R199"), remove));
    assert(history.empty() && active.size() == 2);
    try {
        history.cancel(active.front(), [](const Reservation&) -> bool {
            throw std::runtime_error("failed removal");
        });
        assert(false);
    } catch (const std::runtime_error&) {}
    assert(history.empty());
    history.push(active.front());
    try {
        history.undo([](const Reservation&) -> bool {
            throw std::runtime_error("failed restoration");
        });
        assert(false);
    } catch (const std::runtime_error&) {}
    assert(history.size() == 1);
    history.clear();
    std::ostringstream empty;
    history.displayHistory(empty);
    assert(empty.str() == "No cancelled reservations.\n");
    for (int i = 0; i < 10000; ++i) history.push(makeReservation(i, "R101"));
    std::cout << "Cancellation stack tests passed.\n";
}
