#include "Reservation.h"
// copies the reservation header file onto here

Reservation::Reservation()
{
        reservationID = 0;
        studentID = 0;
        studentName = "";
        resourceID = "";
        reservationDate = "";
} //Constructor

void Reservation::set_reservationID(int id)
{
        reservationID = id;
} //updates the reservationId

int Reservation::get_reservationID()
{
    return reservationID;
} //returns the update reservationID

void Reservation::set_studentID(int id)
{
    studentID = id;
}// updates the students id

int Reservation::get_student()
{
    return studentID;
} // returns the updated student id

void Reservation::set_studentName(std::string name)
{
    studentName = name;
} // updates the student name

std::string Reservation::get_studentName()
{
    return studentName;
} //returns the updated student name

void Reservation::set_resourceID(std::string id)
{
    resourceID = id;
}//updates the resource id

std::string Reservation::get_resourceID()
{
    return resourceID;
} //returns the update resourceID

void Reservation::set_reservationDate(std::string date)
{
    reservationDate = date;
}// updates the reservation date

std::string Reservation::get_reservationDate()
{
    return reservationDate;
} //returns the updated date
