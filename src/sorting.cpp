#include "Sorting.h"

// the resource name
int partitionResource(std::vector<Resource>& v, int low, int high) {
  std::string pivot = v[high].get_resourceName();
  int i = low - 1;

  for (int j = low; j < high; j++) {
    if (v[j].get_resourceName() <= pivot) {
      i++;
      Resource temp = v[i];
      v[i] = v[j];
      v[j] = temp;
    }
  }
  Resource temp = v[i+1];
  v[i+1] = v[high];
  v[high] = temp;
  return i + 1;
}

void quickSortResources(std::vector<Resource>& v, int low, int high) {
  if (low < high) {
    int p = partitionResource(v, low, high);
    quickSortResources(v, low, p - 1);
    quickSortResources(v, p + 1, high);
  }
}

// The reservation by the date
int dateKey(const std::string& d) {
  if (d.size() < 10) return 0;
  int month = std::stoi(d.substr(0, 2));
  int day = std::stoi(d.substr(3, 2));
  int year = std::stoi(d.substr(6, 4));
  return year * 10000 + month * 100 + day;
}

int partitionResource(std::vector<Resource>& v, int low, int high) {
  int pivot = dateKey(v[high].get_reservationDate());
  int i = low -1;

  for (int j = low; j < high; j++) {
    if (dateKEy(v[j].get_reservationDate()) <= pivot) {
      i++;
      Reservation temp = v[i];
      v[i] = v[j];
      v[j] = temp;
    }
  }
  Reservation temp = v[i+1];
  v[i+1] = v[high];
  v[high] = temp;
  return i + 1;
}

void quickSortReservations(std::vector<Reservation>& v, int low, int high) {
  if (low < high) {
    int p = partitionReservation(v, low, high);
    quickSortReservations(v, low, p - 1);
    quickSortReservations(v, p + 1, high);
  }
}
