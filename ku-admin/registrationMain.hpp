#ifndef REGISTRATIONMAIN_HPP
#define REGISTRATIONMAIN_HPP

#include <string>

bool doesGmailExist(const std::string& gmail);
bool removeUserByGmail(const std::string& gmail);
bool changePhoneNumber(const std::string& gmail, const std::string& new_phone_number);
bool removeFromPhoneNIdTable(const std::string& gmail);


#endif // REGISTRATIONMAIN_HPP
