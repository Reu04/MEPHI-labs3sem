#include "iostream"

enum Gender {
    MALE,
    FEMALE
};

class Person {
private:
    std::string name;
    std::string surname;
    int age;
    std::string nationality;
    Gender gender;

public:
    Person(std::string name, std::string surname, int age, std::string nationality, Gender gender)
            : name(name), surname(surname), age(age), nationality(nationality), gender(gender) {}

    Person(const Person& other)
            : name(other.name), surname(other.surname), age(other.age), nationality(other.nationality), gender(other.gender) {}

    Person(Person&& other)
            : name(std::move(other.name)), surname(std::move(other.surname)),
              age(std::move(other.age)), nationality(std::move(other.nationality)), gender(std::move(other.gender)) {}

    std::string get_name() const {
        return name;
    }

    std::string get_surname() const {
        return surname;
    }

    int get_age() const {
        return age;
    }

    std::string get_nationality() const {
        return nationality;
    }

    Gender get_gender() const {
        return gender;
    }

    void set_name(std::string new_name) {
        name = std::move(new_name);
    }

    void set_surname(std::string new_surname) {
        surname = std::move(new_surname);
    }

    void set_age(int new_age) {
        age = new_age;
    }

    void set_nationality(std::string new_nationality) {
        nationality = std::move(new_nationality);
    }

    void set_gender(Gender new_gender) {
        gender = new_gender;
    }
};