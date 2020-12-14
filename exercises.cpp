#include "exercises.h"
#include <string.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

int Exercises::getType() const {
    //0 - без ссылки, 1 - с ссылкой
    return 0;
};

//печать значений
/*void Exercises::printExercise() const {
    std::cout<< "Name:" << name_ <<std::endl;
    std::cout<<"Time:"<< time_ <<std::endl;
    std::cout<<"Calories:"<< calory_ <<std::endl;
};*/

//Получение флага удаления упражнения
bool Exercises::isDeleted() const {
    return _isdeleted;
}

//Перегрузка оператора вывода
std::ostream &operator<<(std::ostream &out, const Exercises &exercise) {
    out << "Название:" << exercise.GetName() << std::endl;
    out << "Время выполнения:" << exercise.GetTime() << std::endl;
    out << "Калории на единицу времени:" << exercise.GetCalory() << std::endl;
    if (exercise.isDeleted())
        out << "DELETED" << std::endl;
    return out;
}

void Exercises::check() { //проверка отдельной функцией для экономии времени
    if (GetTime() < 0) {
        SetTime(TIME_MIN);
    }
    if (GetCalory() < CALORY_MIN) {
        SetCalory(CALORY_MIN);
    }
    else if (GetCalory() >= CALORY_MAX)
        SetCalory(CALORY_MAX);
}

//конструктор инициализации
Exercises::Exercises(std::string new_name, double new_time, double new_calory):
    name_(std::move(new_name)), // не выполняется копирование, за счет перевода состояния объекта к временному
    time_(new_time), calory_(new_calory) {
    check();
}

//конструктор копирования, адекватный вариант
Exercises::Exercises(const Exercises &exercise):
    name_(exercise.GetName()),
    time_(exercise.GetTime()), calory_(exercise.GetCalory()) {}

//селекторы и модификаторы
std::string Exercises::GetName() const {
    return name_;
};

double Exercises::GetTime() const {
    return time_;
};

double Exercises::GetCalory() const {
    return calory_;
};

void Exercises::SetName(const std::string &new_name) {
    name_ = new_name;
}

void Exercises::SetTime(const double &new_time) {
    if (new_time < 0)
        time_ = TIME_DEFAULT;
    else
        time_ = new_time;
}

void Exercises::SetCalory(const double &new_calory) {
    if (new_calory < 0)
        calory_ = CALORY_DEFAULT;
    else if (new_calory > CALORY_MAX)
        calory_ = CALORY_MAX;
    else
        calory_ = new_calory;
}













