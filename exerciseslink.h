#ifndef EXERCISESLINK_H
#define EXERCISESLINK_H
#include "exercises.h"

class ExercisesLink : public Exercises {
public:
    static constexpr const char* LINK_DEFAULT = "youtube.com";

    ExercisesLink() = default;

    ExercisesLink(std::string name, double time, double calory, std::string link);

    ExercisesLink(const ExercisesLink &link);

    std::string GetLink() const;

    void SetLink(const std::string &new_link);

       virtual int getType() const;

       //деструктор
       virtual ~ExercisesLink() {};

    private:
       void check(); //для проверки корректности введённых данных
       //полям класса присваиваем значения по умолчанию
       std::string link_ = LINK_DEFAULT;
};

std::ostream& operator<<(std::ostream& out, const ExercisesLink &exercise);


#endif // EXERCISESLINK_H
