#include "Resource.h"
//copies the resource header file and "pastes" it here

Resource::Resource() //Constructor
{
	resourceID = "";   //sets the resourceID to an empty string
	resourceName = ""; //sets the resourceName to an empty string
	resourceType = ""; //sets the resourceTyoe to empty
	availabilityStatus = true; //sets the status to true by default
}

void Resource::set_resourceID(std::string id)
{
	resourceID = id;
} //changes the resourceID

std::string Resource:get_resourceID()
{
	return resourceID;
}//returns the new resourceID

void Resource::set_resourceName(std::string name)
{
	resourceName = name;
}// changes/updates the resourceName

std::string Resource::get_resourceName()
{
	return resourceName;
}// returns the new updated resourceName

void Resource::set_resourceType(std::string type)
{
	resourceType = type;
}// changes/updates the resourceType

std::string Resource::get_resourceType()
{
	return resourceType;
}// returns the new updated resourceType

void Resource::set_availabilityStatus(bool status)
{
	availabilityStatus = status;
} // updates the status of the availability

bool Resource::get_availabilityStatus()
{
	return availabilityStatus;
}// returns the updated status of availability
 
