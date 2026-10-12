#include "ReservationManager.h"
#include <iostream> // copies the ReservationManager header file onto here

// Constructor: this is to initialise the quene pointers alongside head
ReservationManager::ReservationManager() : head(nullptr), waitFront(nullptr), waitRear(nullptr), waitCount(0) {}

// Destructor: This is the free both structures
ReservationManager::~ReservationManager() {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }

    while (waitFront != nullptr) {
        WaitNode* temp = waitFront;
        waitFront = waitFront->next;
        delete temp;
    }
    waitRear = nullptr;
    waitCount = 0;
}


// This function will insert at the head
void ReservationManager::addActiveReservation(const Reservation& reservation) {
    Node* newNode = new Node(reservation);
    newNode->next = head;
    head = newNode;

    std::cout << "Reservation " << newNode->data.get_reservationID() << " added.\n";
}

// This removes the students from waiting list
bool ReservationManager::removeActiveReservation(const std::string& reservationId) {
    Node* current = head;
    Node* previous = nullptr;

    while (current != nullptr) {
        if (std::to_string(current->data.get_reservationID()) == reservationId) {
            if (previous == nullptr) {
                head = current->next;
            } else {
                previous->next = current->next;
            }
            delete current;
            std::cout << "Reservation " << reservationId << " removed.\n";
            return true;
        }
        previous = current;
        current = current->next;
    }
    std::cout << "Reservation " << reservationId << " not found.\n";
    return false;
}

// This is walk the list comparing IDs; returns true on the first match.
bool ReservationManager::findReservation(const std::string& reservationId) const {
    Node* current = head;
    while (current != nullptr) {
        if (std::to_string(current->data.get_reservationID()) == reservationId) {
            return true;
        }
        current = current->next;
    }
    return false;
}

// This display the waiting list in queue order
void ReservationManager::displayAllActiveReservation() const {
    if (head == nullptr) {
        std::cout << "There are no active reservation.\n";
        return;
    }

    std::cout << "--- Active Reservations ---\n";
    Node* current = head;
    while (current != nullptr) {
        std::cout << "Reservation ID: " << current->data.get_reservationID() << "\n";
        current = current->next;
    }
    std::cout << "--------------------\n";
}

    
// This functions is waiting list
void ReservationManager::addToWaitingList(const std::string& studentId, const std::string& resourceId) {
    WaitNode* newNode = new WaitNode(studentId, resourceId);

    if (waitRear == nullptr) { // the queue is empty
        waitFront = newNode;
        waitRear = newNode;       
    } else {
        waitRear->next = newNode;
        waitRear = newNode;
    }
    waitCount++;

    std::cout << "Student " << studentId << " added to the waiting list for " << resourceId << " (position " << waitCount << ").\n";
}

bool ReservationManager::removeFromWaitingList(const std::string& studentId, const std::string& resourceId) {
    WaitNode* current = waitFront;
    WaitNode* previous = nullptr;

    while (current != nullptr) {
        if (current->studentId == studentId && current->resourceId == resourceId) {

            if (previous == nullptr) {
                waitFront = current->next;
            } else {
                previous->next = current->next;
            }

            if (current == waitRear) {
                waitRear = previous;
            }
            
            delete current;
            waitCount--;
            return true;
        }
        previous = current;
        current = current->next;
    }
    return false;
}

void ReservationManager::displayWaitingList() const {
    if (waitFront == nullptr) {
        std::cout << "The waiting list is empty.\n";
        return;
    }

    std::cout << "--- Waiting List (" << waitCount << " student(s)) ---\n";
    int position = 1;
    WaitNode* current = waitFront;
    while (current != nullptr) {
        std::cout << position << ". Student: " << current->studentId << " | Resource: " << current->resourceId << "\n";
        position++;
        current = current->next;
    }
    std::cout << "-----------------------------\n";
}

bool ReservationManager::isWaitingListEmpty() {
    return waitFront == nullptr;
}

int ReservationManager::waitingListSize() const {
    return waitCount;
}

// Reject duplicate IDs and occupied resource/date pairs before undo.
bool ReservationManager::canRestoreReservation(Reservation reservation) const {
    for (Node* current = head; current; current = current->next) {
        if (current->data.get_reservationID() == reservation.get_reservationID() ||
            (current->data.get_resourceID() == reservation.get_resourceID() &&
             current->data.get_reservationDate() == reservation.get_reservationDate()))
            return false;
    }
    return true;
}


void ReservationManager::generateReport(const std::vector<Resource>& resources, std::ostream& out) const {
    out << "\n===== SYSTEM REPORT =====\n";
    out << "\n--- Active Reservations ---\n";
    int activeCount = 0;
    for (Node* current = head; current != nullptr; current = current->next) {
        out << "Reservation " << current->data.get_reservationID()
            << " | Student " << current->data.get_student()
            << " | " << current->data.get_studentName()
            << " | " << current->data.get_resourceID()
            << " | " << current->data.get_reservationDate() << '\n';
        activeCount++;
    }
    if (activeCount == 0) out << "No active reservations.\n";
    out << "Total active reservations: " << activeCount << '\n';

    std::vector<int> reservationCounts(resources.size(), 0);
    std::vector<int> waitingCounts(resources.size(), 0);
    int highestCount = 0;
    for (std::size_t i = 0; i < resources.size(); i++) {
        Resource resource = resources[i];
        for (Node* current = head; current != nullptr; current = current->next) {
            if (current->data.get_resourceID() == resource.get_resourceID())
                reservationCounts[i]++;
        }
        for (WaitNode* current = waitFront; current != nullptr; current = current->next) {
            if (current->resourceId == resource.get_resourceID())
                waitingCounts[i]++;
        }
        if (reservationCounts[i] > highestCount) highestCount = reservationCounts[i];
    }

    out << "\n--- Resource Utilization and Current Availability ---\n";
    if (resources.empty()) out << "No resources loaded.\n";
    for (std::size_t i = 0; i < resources.size(); i++) {
        Resource resource = resources[i];
        out << resource.get_resourceID() << " | " << resource.get_resourceName()
            << " | Active reservations: " << reservationCounts[i]
            << " | " << (resource.get_availabilityStatus() ? "Available" : "Unavailable") << '\n';
    }

    // Popularity uses current active reservation counts, not lifetime history.
    out << "\n--- Most Requested Resources (by active reservations) ---\n";
    if (highestCount == 0) out << "No reserved resources.\n";
    else {
        for (std::size_t i = 0; i < resources.size(); i++) {
            if (reservationCounts[i] == highestCount) {
                Resource resource = resources[i];
                out << resource.get_resourceID() << " | " << resource.get_resourceName()
                    << " | Reservations: " << highestCount << '\n';
            }
        }
    }

    out << "\n--- Waiting-List Statistics ---\n";
    if (waitFront == nullptr) out << "No students waiting.\n";
    for (std::size_t i = 0; i < resources.size(); i++) {
        Resource resource = resources[i];
        out << resource.get_resourceID() << " | " << resource.get_resourceName()
            << " | Waiting requests: " << waitingCounts[i] << '\n';
    }
    int waitingTotal = 0;
    for (WaitNode* current = waitFront; current != nullptr; current = current->next)
        waitingTotal++;
    out << "Total waiting requests: " << waitingTotal << '\n';
}
