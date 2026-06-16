#pragma once

#ifndef ERR_H
#define ERR_H

// stdlib
#include <cerrno>
#include <cstring>
#include <iostream>

/**
 * @brief Formats and logs an error message corresponding to a failed process.
 * 
 * @param exit_code is the exit value
 * @param message is the error message log
 */
void err(int exit_code, const char* message);

#endif // ERR_H

