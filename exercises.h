#ifndef EXERCISES_H
#define EXERCISES_H
#include <iostream>
#include <string>

class Exercises
{
public:
    constexpr static const double CALORY_MIN = 0;
    constexpr static const double TIME_DEFAULT = 20;
    constexpr static const double TIME_MIN = 0;
    constexpr static const double CALORY_MAX = 10000;
    constexpr static const double CALORY_DEFAULT = 50;
    static constexpr const char* NAME_DEFAULT = "name";
    Exercises() = default;
    Exercises(std::string name, double time, double calory);
    Exercises(const Exercises &exercise);
    //селекторы и модификаторы

    std::string GetName() const;

    double GetTime() const;
    double GetCalory() const;
    void SetName(const std::string &new_name);
    void SetTime(const double &new_time);
    void SetCalory(const double &new_calory);

   // virtual void printExercise() const;

    bool isDeleted() const;
    virtual ~Exercises() {};

    //с ссылкой или без
    virtual int getType() const;


private:
    void check();
    std::string name_ = NAME_DEFAULT;
    double time_ = TIME_DEFAULT;
    double calory_ = CALORY_DEFAULT;
    /*struct date {
        int day = 1;
        int month = 1;
        int year = 2020;
    };*/
     bool _isdeleted = false;
};

std::ostream& operator<<(std::ostream& out, const Exercises &exercise);

#endif // EXERCISES_H
