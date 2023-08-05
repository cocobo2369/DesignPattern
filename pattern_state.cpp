#include <iostream>
#include <string.h>
using namespace std;

class LightSwitch;

struct State
{
    string s;
    virtual void on(LightSwitch *ls)
    {
        cout << s << " light on already"<<endl;
    }

    virtual void off(LightSwitch *ls)
    {
        cout << s << " light off already"<<endl;
    }
};

struct StateOn : State
{
    StateOn() //생성자는 상태의 완료를 뜻하게 함
    {   
        s.clear();
        s.append("(state-On)");
        cout << s << " on" << endl;
    }
    //void on(LightSwitch* ls) by parent class 'State'
    void off(LightSwitch *ls) override;
};

struct StateOff : State
{
    StateOff()
    {
        s.clear();
        s.append("(state-Off)");
        cout << s << " off" << endl;
    }

    void on(LightSwitch *ls) override;
    //void off(LightSwitch* ls) by parent class 'State'
};

class LightSwitch
{
    State *state;

public:
    LightSwitch()
    {
        state = new StateOff();
    }

    void set_state(State* state)
    {
        this->state = state;
    }
    void on()
    {
        state->on(this);
    }
    void off()
    {
        state->off(this);
    }
};

void StateOff::on(LightSwitch *ls)
{
    cout << s << " off --> on" << endl;
    ls->set_state(new StateOn());
    delete this;
}
void StateOn::off(LightSwitch *ls)
{
    cout << s << " on --> off" << endl;
    ls->set_state(new StateOff());
    delete this;
}
int main()
{
    cout <<"[1]---------"<<endl;
    LightSwitch ls;
    cout <<"[2]---------"<<endl;
    ls.on();
    cout <<"[3]---------"<<endl;
    ls.off();
    cout <<"[4]---------"<<endl;
    ls.off();
}