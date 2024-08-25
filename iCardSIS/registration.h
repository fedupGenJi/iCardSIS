#ifndef REGISTRATION_H
#define REGISTRATION_H
#include<string>
#include<QString>

bool registerUser(const std::string& mobile_number, const std::string& password, const std::string& confirm_password, const std::string& gmail);
std::string generatecrypt(std::string data);
bool isPhoneNumberRegistered(const std::string& mobile_number);
void completeMessage(const QString &message);
bool isGmailValid(const std::string& gmail);
void showError(const QString &errorMessage);
bool isGmailRegistered(const std::string& gmail);

#endif // REGISTRATION_H
