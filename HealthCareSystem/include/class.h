#ifndef  CLASS_H
#define CLASS_H

#include <iostream>
#include <string>
#include "helper.h"
#include "list.h"

enum Gender {
  Male=1,
  Female=2,
  X=3
};

struct Date {
  int day;
  std::string month;
  int year;
  
  std::string monthArr[12] = {"Jan", "Feb", "March", "April", "May", "June", "July", "Aug", "Sep", "Oct", "Nov", "Dec"};  
  int daysInMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

  Date() : day(1), month("Jan"), year(1969) {}
  Date(int day, int month, int year) {
    this->day = day;
    this->month = monthArr[month-1];
    this->year = year;
  }

  std::string GetData() {
    std::string statement = std::to_string(day) + "/" + month + "/" + std::to_string(year); 
    return statement;
  }

  bool operator==(const Date& other) const {
    return (day == other.day && month == other.month && year == other.year);
  }

  Date AddDate() {

    int month;
    Assign("Month (1-12)", month);
    while (month > 12 || month < 1) {
      std::cout << "\nINVALID Month"; 
      Assign("Month (1-12)", month);
    }

    int day;
    Assign("Day (1-31)", day);
    while (day < 1 || day > daysInMonth[month-1]){
      std::cout << "\nINVALID Day"; 
      Assign("Day (1-31)", day);
    }

    int year;
    Assign("Year (without 20)", year);

    while (year > 99) {
      std::cout << "\nINVALID Year"; 
      Assign("Year (without 20)", year);
    }

    return Date(day, month, year);

  }

};

struct Medicine {
  std::string name;
  int price;
  Medicine() : name("ERROR NO NAME"), price(0) {}
  Medicine(std::string name, int price) : name(name), price(price) {}

  std::string GetData() {
    std::string statement = name + "  " + std::to_string(price) + "Rs"; 
    return statement;
  }

  bool operator==(const Medicine& other) const {
    return (name == other.name && price == other.price);
  }


};

struct Disease {
  std::string name;
  Medicine medicine; 

  Disease() : name("ERROR NO NAME"), medicine(Medicine()) {};
  Disease(std::string name, Medicine medicine) : medicine(medicine), name(name) {}

  bool operator==(const Disease& other) const {
    return (name == other.name && medicine == other.medicine);
  }

  std::string GetData() {
    std::string statement = name + "  " + medicine.GetData();
    return statement;
  } 

};

class Person {
private:

  std::string name; 
  std::string sex;
  int age;

public:

  Person() : name("ERROR NO NAME"), sex("0"), age(0) {}
  Person(std::string name, std::string sex, int age) {
    this->name = name;
    this->sex = sex;
    this->age = age;
  }

  std::string GetData() {
    std::string statement = name + "  " + std::to_string(age) + "  " + sex; 
    return statement;
  }

  bool operator==(const Person& other) const {
    return (name == other.name && sex == other.sex && age == other.age);
  }

  std::string GetName() {
    return name;
  }

};

class Patient : public Person {
private:
  Disease disease;
  Date admitDate;
  int price;
public: 

  Patient() : Person(), disease(Disease()), admitDate(Date()), price(0) {}
  Patient(Person person, Disease disease, Date admitDate, int price) : Person(person), disease(disease), admitDate(admitDate), price(price)  {} 

  bool operator==(const Patient& other) {
    return (Person::operator==(other) && disease == other.disease && admitDate == other.admitDate && price == other.price);
  }

  std::string GetData() {
    std::string statement = Person::GetData() + "  " + disease.GetData() + "  " + admitDate.GetData(); 
    return statement;
  }

  std::string GetName() {
    return Person::GetName();
  }

};

class Shedule;

class Doctor : public Person {
private: 

  std::string qualification;
  std::string password;
  Date joinDate;
  bool isEmpty;

  LinkedList<Shedule>* sheduleList;

public:

  Doctor() : Person(), qualification("0"), joinDate(Date()), password("123"), isEmpty(false), sheduleList((new LinkedList<Shedule>())) {}

  Doctor(Person person, std::string qualification, Date joinDate, LinkedList<Shedule>* sheduleList, std::string password) : Person(person), qualification(qualification), joinDate(joinDate), password(password), isEmpty(false), sheduleList(sheduleList) {}

  bool operator==(const Doctor& other) const {
    return (Person::operator==(other) && qualification == other.qualification && joinDate == other.joinDate);   
  }

  void DeleteShedule() {

    if (sheduleList->count() <= 0) return;

    int i;

    while (i > sheduleList->count()) {
      clearScreen();
      sheduleList->printList();
      Assign("which patient you want to check", i);
    }
    
    sheduleList->deleteNode(i);

    return;

  }

  void DashBoard() {

    int choice;
    bool quit = false;



    while (!quit) {

      clearScreen();

      std::cout << "=== Dashboard ===\n";
      std::cout << "0. Quit" << std::endl;
      std::cout << "1. List Shedule" << std::endl;
      std::cout << "2. Check the Patient" << std::endl;
      Assign("Enter your choice", choice);

      switch (choice) {
        case 0:
          quit = true;
          break;
        case 1:
          std::cout << "==== List Shedule ====" << std::endl;
          sheduleList->printList();
          std::cout << "======================" << std::endl;
          KeyPress();
          break;
        case 2:
          std::cout << "==== Delete Shedule ====" << std::endl;         
          DeleteShedule();
          std::cout << "========================" << std::endl;
          KeyPress();
        default:
          std::cout << "\nInvalid input.\n\n";
      }
       
    } 
    
  }

  std::string GetData() {
    std::string statement = Person::GetData() + "  " + qualification + "  " +  joinDate.GetData(); 
    return statement;
  }

  std::string GetName() {
    return this->Person::GetName();
  }

  bool IsPassword(std::string password) {
    return (this->password == password);
  }

};

class Shedule {
private:

  Patient patient;
  Date date;
  Doctor doctor;

public:

  Shedule():  patient(Patient()), date(Date()), doctor(Doctor()) {}

  bool operator ==(const Shedule& other) {
    return (doctor == other.doctor && patient == other.patient && date == other.date);
  }

  Shedule(Doctor doctor, Patient patient, Date date) {
    this->patient = patient;
    this->date = date;
    this->doctor = doctor;
  }

  std::string GetData() { 
  std::string statement = doctor.GetName() + "  " + patient.GetName() + "  " + date.GetData();
  return statement;
}

};


#endif // ! CLASS_H
