#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Resource.h"
#include "Reservation.h"
#include "ReservationManager.h"
#include "CancellationStack.h"
#include "Sorting.h"

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
    
    while (getline(resourceText, id, '|'))
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
        reservation.set_reservationDate(reservationDate);
        
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
            
            cin.ignore();
            
            cout << "Enter Student Name (no spaces): ";
            getline (cin, studentName);
            
            cout << "Enter Resource ID: ";
            cin >> resourceID;
            
            cout << "Enter date for reservation: ";
            cin >> reservationDate;
            
            Reservation reservation;
            
            reservation.set_reservationID(reservationID);
            reservation.set_studentID(studentID);
            reservation.set_studentName(studentName);
            reservation.set_resourceID(resourceID);
            reservation.set_reservationDate(reservationDate);
            
            manager.addActiveReservation(reservation);
            
            cout << "Your reservation has been created" << endl;
        }
        
        else if (menu == 3)
        {
            string reservationID;
            
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
                string reservationID;
                
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
            
            int sortChoice;

            cout << "=== Sort ===" << endl;
            cout << "1. Resource by name";
            cout << "2. Reservation by date" << endl;
            cout << "3. Reservation by popularity" << endl;
            cout << "Enter choice: ";
            cin >> sortChoice;

            if (sortChoice == 1)
            {
                if (resources.empty())
                {
                    cout << "There are no resources." << endl;
                }
                else
                {
                    quickSortResources(resources, 0, resources.size() - 1);
                    for (int i =0; i < resources.size(); i++)
                    {
                    cout << resources[i].get_resourceID() << " | "
                            << resources[i].get_resourceName() << " | "
                            << resources[i].get_resourceType() << endl;
                    }
                }
            }
            else if (sortChoice == 2)
            {
                vector<Reservation> all = manager.getAllReservations();

                if (all.empty())
                {
                    cout << "There are no active reservations." << endl;
                }
                else
                {
                    quickSortReservations(all, 0, all.size() - 1);
                    for (int i = 0; i < all.size(); i++)
                    {
                        cout << "Reservation " << all[i].get_reservationID()
                            << " | " << all[i].get_resourceID()
                            << " | " << all[i].get_reservationDate() << endl;
                    }
                }
            }
            else if (sortChoice == 3)
            {
                vector<Reservation> all = manager.getAllReservations();
                vector<PopularityEntry> entries;

                // This count how many active reservations of each resource has
                for (int j = 0; j < resources.size(); j++)
                {
                    PopularityEntry entry;
                    entry.resource = resource[i];
                    entry.count = 0;
                    
                    for (int j = 0; j < all.size(); j++)
                        {
                            if (all[j].get_resourceID() == resources[i].get_resourceID())
                            {
                            entry.count++;
                            }
                        }
                        entries.push_back(entry);
                    }

                    if (entries.empty())
                    {
                        cout << "There are no resources." << endl;
                    }
                    else
                    {
                        quickSortPopularity(entries, 0, entries.size() - 1);

                        cout << "--- Resources sorted by popularity ---" << endl;
                        for (int i = 0; i < entries.size(); i++)
                        {
                            cout << entires[i].get_resourceID() << " | "
                            << entires[i].get_resourceName() << " | "
                            << entires[i].count << " reservation(s)" << endl;
                    }
                }
            }

            else
            {
                cout << "Invalid choice." << endl;
            }
        }
        
        else if (menu == 8)
        {
            
            
            manager.generateReport(resources, cout);
            
            
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
