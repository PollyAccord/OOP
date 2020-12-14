#ifndef LISTEXERCISES_H
#define LISTEXERCISES_H
#include "QString"
#include "exercises.h"
#include "exerciseslink.h"

class ListExercises
{
public:
    ListExercises(const int n);

   ListExercises(const ListExercises &list);

   ~ListExercises();

   int NumberOfExercises() const;

   void SetExercise(const int n, Exercises *exercise);
   Exercises *GetExercise(const int n) const;
   void deleteExercise(const int n);

   int getLength() const;

   bool isEqual(const ListExercises &exercises) const;

  //double TotalCalories(const ListExercises &list);
  //double TotalTime(const ListExercises &list);


private:
  Exercises **objects = NULL; //объекты упражнений
  int n_; //количество строк в массиве
  int allocated; //количество выделенных объектов
};

void printList(const ListExercises &exercises);
bool ListToJson(const QString &string, const ListExercises &list);
ListExercises ListFromJson(const QString &string);

#endif // LISTEXERCISES_H
