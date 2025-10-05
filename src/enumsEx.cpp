#include <iostream>
#include <ctime>    // For getting the current day of the week
#include "helloEx.h" // for printLine
#include "enumsEx.h"

// 1. Define an enumeration (enum).
// Enums assign names to integer constants, making code more readable.
// By default, SUNDAY is 0, MONDAY is 1, and so on.
typedef enum Day {
    SUNDAY,
    MONDAY,
    TUESDAY,
    WEDNESDAY,
    THURSDAY,
    FRIDAY,
    SATURDAY
} Day;

// Helper function to convert enum to string for printing
const char* getDayName(Day d) {
    switch (d) {
        case SUNDAY:    return "Sunday";
        case MONDAY:    return "Monday";
        case TUESDAY:   return "Tuesday";
        case WEDNESDAY: return "Wednesday";
        case THURSDAY:  return "Thursday";
        case FRIDAY:    return "Friday";
        case SATURDAY:  return "Saturday";
        default:        return "Invalid Day";
    }
}

void enumsEx(void) {
    printLine("enumsEx function.");

    // 2. Declare a variable of our new 'enum Day' type according to the current system date
    time_t t = time(nullptr);
    tm* localTime = localtime(&t);
    int wday = localTime->tm_wday; // tm_wday gives days since Sunday (0-6)
    Day today = static_cast<Day>(wday);

    // 3. Use the enum variable in a switch statement.
    std::cout << "Today is: " << getDayName(today) << std::endl;
    switch (today) {
        case SUNDAY:
            std::cout << "It's the weekend!" << std::endl;
            break;
        case SATURDAY:
            std::cout << "It's the weekend!" << std::endl;
            break;              
        default:
            std::cout << "It's a weekday." << std::endl;
            break;
    }
}