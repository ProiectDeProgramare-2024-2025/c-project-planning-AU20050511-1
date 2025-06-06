#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>

bool validateDate(const std::string& date);
void getValidInput(const std::string& prompt, std::string& input, size_t maxLen = 50);
void getValidDate(const std::string& prompt, std::string& date);
void clear();