#pragma once

#include "../Std_Libraries.h"

namespace io {

/**
 * @brief Read a numeric value in [minValue, maxValue] with validation loop.
 */
template <typename T>
T readBoundedNumber(T minValue, T maxValue, const std::string& prompt) {
    T value{};
    while (true) {
        std::cout << prompt;

        if (!(std::cin >> value)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a numeric value.\n";
            continue;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (value < minValue || value > maxValue) {
            std::cout << "Value out of range. Valid range is [" << minValue << ", " << maxValue << "].\n";
            continue;
        }

        return value;
    }
}

/**
 * @brief Read a non-empty text line.
 */
inline std::string readNonEmptyLine(const std::string& prompt) {
    while (true) {
        std::cout << prompt;
        std::string value;
        std::getline(std::cin, value);

        if (!value.empty()) {
            return value;
        }

        std::cout << "Input cannot be empty.\n";
    }
}

/**
 * @brief Read yes/no question and normalize answer to lower-case ('y' or 'n').
 */
inline char readYesNo(const std::string& prompt) {
    while (true) {
        std::cout << prompt;
        char choice{};

        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter y or n.\n";
            continue;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        choice = static_cast<char>(std::tolower(static_cast<unsigned char>(choice)));

        if (choice == 'y' || choice == 'n') {
            return choice;
        }

        std::cout << "Invalid input. Please enter y or n.\n";
    }
}

}  // namespace io
