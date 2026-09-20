#ifndef ReservationManager_h
#define ReservationManager_h
#include <string>
#include "Reservation.h"
#include "Resource.h"



class ReservationManager {
   private:
   struct Node {
       Reservation data;
       Node* next;



       Node(const Reservation& res) : data(res), next(nullptr) {}
   };



   Node* head;



   struct WaitNode {
       std::string studentId;
       std::string resourceId;
       WaitNode* next;



       WaitNode(const std::string& sId, const std::string& rId)
       : studentsId(sId), resourceId(rId), next(nullptr) {}
   };



   WaitNode* waitFront;
   WaitNode* waitRear;
   int waitCount;



   public:
   ReservationManager();
   ~ReservationManager();



   void addActiveReservation(const Reservation& reservation);
   bool removeActiveReservation(const std::string& reservationId);
   bool findReservation(const std::string& reservationId) const;
   void displayAllActiveReservation() const;



   void addToWaitingList(const std::string& student, const std::string& resourceId);
   bool removeFromWaitingList(const std::string& studentId, const std::string& resourceId);
   void displayWaitingList() const;
   bool WaitingListEmpty();
   int waitingListSize();
};



#endif
