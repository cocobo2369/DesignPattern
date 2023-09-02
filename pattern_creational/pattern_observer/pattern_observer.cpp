#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Person;

struct PersonListener
{
    virtual ~PersonListener() = default;
    virtual void person_changed(Person& p, const string& property_name,int age) = 0;
};

struct Person //subject
{
    explicit Person(int age) : age(age){}

    int get_age() const
    {
        return age;
    }

    void set_age(const int age); 

    bool get_can_vote() const{
        return  age >=20;
    }

    void subscribe(PersonListener* pl);

    void notify(const string& proprety_name,int age);
private:
    int age;
    vector<PersonListener*> listener;

};

void Person::set_age(const int age){
    if(this->age == age) return;

    auto before_young_votable = get_can_vote();

    this->age = age;


    auto now_old_votable = get_can_vote();
    if(before_young_votable != now_old_votable)
        notify("can vote age",this->age);
}
void Person::subscribe(PersonListener * pl)
{
    listener.push_back(pl);
}

void Person::notify(const string& property_name,int age)
{
    for(const auto i : listener)
    i->person_changed(*this, property_name, age);
}

struct ConsoleListener : PersonListener
{
    void person_changed(Person& p, const string& property_name,int age){
        cout << property_name <<"   "<< age << endl;
    }
};
int main()
{
    Person p{14};
    ConsoleListener person1;
    p.subscribe(&person1);
    p.set_age(11);
    p.set_age(20);

    return 0;
}