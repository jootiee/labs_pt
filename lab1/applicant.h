#ifndef APPLICANT_H
#define APPLICANT_H

#include <iostream>

/// @brief Applicant Class
class Applicant
{
public:
    std::string name;
    std::string faculty;
    std::string specialty;
    int score;

public:
    /// @brief Default constructor
    Applicant() {}

    /**
     * @brief Constructor
     *
     * @param n     name
     * @param f     faculty
     * @param s     specialty
     * @param sc    score
     */
    Applicant(const std::string &n, const std::string &f, const std::string &s, int sc) : name(n), faculty(f), specialty(s), score(sc) {}

    /// @brief Destructor
    ~Applicant() {}

    /// @brief overloading equality operator
    bool operator==(const Applicant &other) const
    {
        return name == other.name &&
               faculty == other.faculty &&
               specialty == other.specialty &&
               score == other.score;
    }

    /// @brief overloading greater than operator
    bool operator>(const Applicant &other) const
    {
        if (score != other.score)
            return score > other.score;
        if (name.compare(other.name) != 0)
            return name.compare(other.name) > 0;
        if (faculty.compare(other.faculty) != 0)
            return faculty.compare(other.faculty) > 0;
        return specialty.compare(other.specialty) > 0;
    }

    /// @brief overloading not equal operator
    bool operator!=(const Applicant &other) const
    {
        return !(*this == other);
    }

    /// @brief overloading less than operator
    bool operator<(const Applicant &other) const
    {
        return *this != other && !(*this > other);
    }

    /// @brief overloading greater than or equal operator
    bool operator>=(const Applicant &other) const
    {
        return !(*this < other);
    }

    /// @brief overloading less than or equal operator
    bool operator<=(const Applicant &other) const
    {
        return !(*this > other);
    }
};

#endif