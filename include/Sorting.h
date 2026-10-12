#ifndef SORTING_H
#define SORTING_H

#include <string>
#include <vector>
#include "Resource.h"
#include "Reservation.h"

// Resource by name
int partitionResources(std::vector<Resource>& v, int low, int high);
void quickSortResources(std::vector<Resource>& v, int low, int high);

// Reservations by date
int dateKey(const std::string& d);
int partitionReservations(std::vector<Reservations>& v, int low, int high);
void quickSortReservations(std::vector<Reservations>& v, int low, int high);

#endif
