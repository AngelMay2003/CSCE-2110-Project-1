#ifndef Reservation_h
#define Reservation_h
#include <string>

class Reservation {

private:

	int reservationID;
	int studentID;
	std::string studentName;
	std::string resourceID;
	std::string reservationDate;

public:
	Reservation();

	void set_reservationID(int id);
	int get_reservationID();

	void set_studentID(int id);
	int get_student();

	void set_studentName(std::string name);
	std::string get_studentName();

	void set_resourceID(std::string id);
	std::string get_resourceID();

	void set_reservationDate(std::string date);
	std::string getreservationDate();
};

#endif
