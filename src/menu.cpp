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
    
    ifstream resourceText("data/resources.txt");
    
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
        
        if (availabilityStatus == "Available")
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
    
    ifstream reservationText("data/reservations.txt");
    
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
        getline(reservationText, date);
        
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
        cout << "6. Search using ID" << endl;
        cout << "7. Sort Reservations/Resources" << endl;
        cout << "8. Generate Report" << endl;
        cout << "9. Exit" << endl;
        
        cout << "Enter your choice: ";
        
        cin >> menu;
        
        if (menu == 1)
        {
            for (int i = 0; i < resources.size(); i++)
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
            cin.ignore();
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
            int reservationID;
            
            cout << endl;
            cout << "Enter your reservation id: ";
            cin >> reservationID;
            
            if (manager.findReservation(reservationID))
            {
                manager.removeActiveReservation(reservationID);
                
                cout << "Your reservation has been cancelled." << endl;
            }
            
            else
            {
                cout << "Your reservation couldn't be found." << endl;
            }
        }
        
        
        else if (menu == 4)
        {
            manager.displayWaitingList();
        }
        
        
        else if (menu == 5)
        {
            if (!cancellationStack.empty())
            {
                Reservation reservation = *cancellationStack.peek();
                
                cancellationStack.pop();
                
                manager.addActiveReservation(reservation);
                
                cout << "Cancellation has beem undone." << endl;
            }
            else
            {
                cout << "There is nothing to undo." << endl;
            }
        }
            
            
        else if (menu == 6)
        {
            int search;
            
            cout << "=== Search using ID ===" << endl;
            cout << "1. Search for resource" << endl;
            cout << "2. Search for reservation" << endl;
            cout << "3. Go back to main menu" << endl;
            
            cout << "Enter choice: " << endl;
            cin >> search;
            
            if (search == 1)
            {
                string resourceID;
                
                cout << "Enter your resource ID: ";
                cin >> resourceID;
                
                bool resourceFound = false;
                
                for (int i = 0; i < resources.size(); i++)
                {
                    if (resources[i].get_resourceID() == resourceID)
                    {
                        cout << "Resource has been found" << endl;
                        resourceFound = true;
                    }
                }
                
                if (resourceFound == false)
                {
                    cout << "Resource was not found" << endl;
                }
            }
            
            else if (search == 2)
            {
                int reservationID;
                
                cout << "Enter your reservation ID: ";
                cin >> reservationID;
                
                if (manager.findReservation(reservationID))
                {
                    cout << "Your reservation has been found." << endl;
                }
                
                else
                {
                    cout << "Your reservation couldn't be found." << endl;
                }
            }
            
            else if (search == 3)
            {
                cout << "Going back to main menu" << endl;
            }
            
            else
            {
                cout << "Invalid input, Re-enter another input" << endl;
            }
            
        }
        
            
            
        else if (menu == 7)
        {
            
            //Add sorting here
            
            
        }
        
        
        else if (menu == 8)
        {
            
            
            //Generate Report here
            
            
        }
        
        
        else if (menu == 9)
        {
            cout << "Thanks for using our system." << endl;
        }
        
        else
        {
            cout << "Invalid: Use menu from 1-9." << endl;
        }
        
    } while (menu != 9);
    
    return 0;
}
