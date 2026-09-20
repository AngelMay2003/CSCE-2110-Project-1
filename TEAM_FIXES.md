# Team integration fixes

Review of revision 8017b80a61dcb6d6663f0363c273f2f84433f430. Existing team files are not modified by this contribution.

- main.cpp: add the semicolon after using namespace std; complete int main(), its closing brace, and menu/application logic.
- Reservation.cpp: get_reservationID(int id) must be get_reservationID(). Rename get_studentID() to get_student() to match the current header, or rename both consistently and update the cancellation printer.
- Resource.cpp: change Resource:get_resourceID() to Resource::get_resourceID().
- ReservationManager.h: change studentsId(sId) to studentId(sId).
- ReservationManager.cpp: include "ReservationManager.h" and <iostream>; add void before addActiveReservation.
- Replace nonexistent getReservationId()/getReservation() calls with get_reservationID(). IDs in Reservation are int while manager parameters are string: choose one consistent type, or compare std::to_string(current->data.get_reservationID()) with the string parameter.
- The insertion argument is const while getters are non-const. Make getter declarations and definitions const, or print from the copied newNode->data.
- displayAllActiveReservation must check head, not waitFront, and use while (current != nullptr).
- Change waitRer to waitRear.
- Match WaitingListEmpty/isWaitingListEmpty names and waitingListSize const qualifiers between header and implementation.

Cancellation needs a manager method getActiveReservation(id, out) that copies the complete stored record before deletion. Undo needs canRestoreReservation(record), checking duplicate ID, resource/date conflicts, resource existence, and the team's availability policy. These methods do not exist yet.

Connect the stack to the menu and update availability consistently. If waiting-list promotion occupies the canceled slot, undo must retain history and report blocked. The queue currently stores only student/resource IDs; promotion may need names/dates from another lookup or a revised queue record.

Other missing functionality visible in this revision: file loading, resource collection/display, completed validation, application menu, and automatic promotion. Agree on date-specific availability: sample reservations reuse resources on different dates while Resource has one availability boolean.
