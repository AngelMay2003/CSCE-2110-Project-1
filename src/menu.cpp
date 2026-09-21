#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Resource.h"
#include "Reservation.h"
#include "ReservationManager.h"
#include "CancellationStack.h"

using namespace std;

int main()
{
    ReservationManager manager;
    
    CancellationStack cancellationStack;
    
    vector <Resource> resources;
    
    ifstream resourceText("resources.txt");
    
    string id;
    string name;
    string type;
    string availabilityStatus;
    
    while (getline(resourceText, id, "|"))
    {
        getline(resourceText, name, '|');
        getline(resourceText, type, '|');
        getline(resourceText, availabilityStatus);
        
        Resource resource;
        
        resource.set_resourceID(id);
        resource.set_resourceName(name);
        resource.set_resourceType(type);
        
        if (availibilyStatus == "Available")
        {
            resource.set_availabilityStatus(true);
        }
        
        else
        {
            resource.set_availabilityStatus(false);
        }
        
        resources.push_back(resource);
        
    }
    resourceText.close();
    
    ifstream reservationText("reservation.txt");
    
    string reservationID;
    string studentID;
    string studentName;
    string resourceID;
    string date;
    
    while (getline(reservationText, reservationID, '|'))
    {
        getline(reservationText, studentID, '|');
        getline(reservationText, studentName, '|');
        getline(reservationText, resourceID, '|');
        getline(reservationText, reservationDate);
        
        Reservation reservation;
        
        reservation.set_reservationID(stoi(reservationID)); //changes string to int
        reservation.set_studentID(stoi(studentID)); //changes string to int
        reservation.set_studentName(studentName);
        reservation.set_resourceID(resourceID);
        reservation.set_reservationDate(date);
        
        manager.addActiveReservation(reservation);
    }
    
    reservationText.close();
    
    int menu;
    
    do {
        
        cout << "===== Campus Resource Reservation System =====" << endl;
        
        cout << "1. View Resources" << endl;
        cout << "2. Create Reservation" << endl;
        cout << "3. Cancel Reservation" << endl;
        cout << "4. View Waiting Lists" << endl;
        cout << "5. Undo Cancellation" << endl;
        cout << "6. Search Reservations" << endl;
        cout << "7. Sort Resources" << endl;
        cout << "8. Exit" << endl;
        
        cout << "Enter your choice: ";
        
        cin >> menu;
        
        if (menu == 1)
        {
            for (int i = 0; i < resources.size; i++)
            {
                cout << resources[i].get_resourceID() << " | ";
                cout << resources[i].get_resourceName() << " | ";
                cout << resources[i].get_resourceType() << " | ";
                
                if (resources[i].get_availabilityStatus())
                {
                    cout << "Available";
                }
                else
                {
                    cout << "Unavailable";
                }
                cout << endl;
            }
        }
        
        else if (menu == 2)
        {
            int reservationID;
            int studentID;
            string studentName;
            string resourceID;
            string reservationDate;
            
            cout << "Enter Reservation ID: ";
            cin >> reservationID;
            
            cout << "Enter Student ID: ";
            cin >> studentID;
            
            cout << "Enter Student Name: ";
            cin >> studentName;
            
            cout << "Enter Resource ID: ";
            cin >> resourceID;
            
            cout << "Enter date for reservation: ";
            cin >> reservationDate;
            
            Reservation reservation;
            
            reservation.set_reservationID(reservationID);
            reservation.set_studentID(studentID);
            reservation.set_studentName(studentName);
            reservation.set_resourceID(resourceID);
            reservation.set_reservationDate(date);
            
            manager.addActiveReservation(reservation);
            
            cout << "Your reservation has been created" << endl;
        }
        
        else if (menu == 3)
        {
            
        }
        
        
        else if (menu == 4)
        {
            
        }
        
        
        else if (menu == 5)
        {
            
        }
            
            
        else if (menu = 6)
        {
            
        }
        
        
        else if (menu = 7)
        {
            
        }
        
        
        else if (menu = 8)
        {
            cout << "Thanks for using our system." << endl;
        }
        
        else
        {
            cout << "Invalid: Use menu from 1-8." << endl;
        }
        
    } while (menu != 8);
    
    return 0;
}
