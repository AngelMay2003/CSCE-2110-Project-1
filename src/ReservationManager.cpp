#include "ReservationManager" // copies the ReservationManager header file onto here

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
ReservationManager::addActiveReservation(const Reservation& reservation) {
    Node* newNode = new Node(reservation);
    newNode->next = head;
    head = newNode;

    std::cout << "Reservation " << reservation.getReservationId() << " added.\n";
}

// This removes the students from waiting list
bool ReservationManager::removeActiveReservation(const std::string& reservationId) {
    Node* current = head;
    Node* previous = nullptr;

    while (current != nullptr) {
        if (current->data.getReservation() == reservationId) {
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
        if (current->data.getReservationId() == reservationId) {
            return true;
        }
        current = current->next;
    }
    return false;
}

// This display the waiting list in queue order
void ReservationManager::displayAllActiveReservation() const {
    if (waitFront == nullptr) {
        std::cout << "There are no active reservation.\n";
        return;
    }

    std::cout << "--- Active Reservations ---\n";
    Node* current = head;
    while (current !=) {
        std::cout << "Reservation ID: " << current->data.getReservationId() << "\n";
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
                waitRer = previous;
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
