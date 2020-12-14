#include "exerciseslink.h"
#include "exercises.h"

void ExercisesLink::check() { //проверка отдельной функцией для экономии времени
    if (link_.find("youtube.com") == std::string::npos)
        link_ = LINK_DEFAULT;
}

int ExercisesLink::getType() const {
    //0 - без ссылки, 1 - с ссылкой
    return 1;
};

//конструктор инициализации, нормальный
ExercisesLink::ExercisesLink(std::string new_name, double new_time, double new_calory, std::string new_link):
    Exercises(new_name, new_time, new_calory),
    link_(new_link){
    check();
}

//конструктор копирования, адекватный вариант
ExercisesLink::ExercisesLink(const ExercisesLink &link):Exercises(link), link_(link.GetLink()) {}

//Перегрузка оператора вывода
std::ostream &operator<<(std::ostream &out, const ExercisesLink &exercise) {
    out << "Название:" << exercise.GetName() << std::endl;
    out << "Время выполнения:" << exercise.GetTime() << "s" << std::endl;
    out << "Калории на единицу времени:" << exercise.GetCalory() << std::endl;
    out << "Ссылка на технику:" <<exercise.GetLink() << std::endl;
    if (exercise.isDeleted())
        out << "DELETED" << std::endl;
    return out;
};

//модификаторы и селекторы

std::string ExercisesLink::GetLink() const {
    return link_;
};


void ExercisesLink::SetLink(const std::string &new_link) {
    if (link_.find("youtube.com") == std::string::npos)
        link_ = LINK_DEFAULT;
    else
        link_ = new_link;
};

