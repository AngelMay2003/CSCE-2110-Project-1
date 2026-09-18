#ifndef resource_h
#define resource_h
#include <string>

class Resource {

private:
	std::string resourceID;
	std::string resourceName;
	std::string resourceType;
	bool availabilityStatus;

public:
	Resource();

	void set_resourceID(std::string id);
	std::string get_resourceID();

	void set_resourceName(std::string name);
	std::string get_resourceName();

	void set_resourceType(std::string type);
	std::string get_resourceType();

	void set_availabilityStatus(bool status);
	bool getavailabilityStatus();
};

#endif

