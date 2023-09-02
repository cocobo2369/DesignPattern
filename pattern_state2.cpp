#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

enum class State
{
    off_hook,   //수화기를 든 상태
    connecting, //연결 시도 상태 - 연결음
    connected,  //연결된 상태 - 대화
    on_hold,    //대기 상태
    on_hook     //수화기 내린 상태
};
inline ostream& operator<<(ostream& os, const State& s)
{
  switch (s)
  {
    case State::off_hook:
      os << "수화기를 든 상태";
      break;
    case State::connecting:
      os << "연결 시도 상태 - 연결음";
      break;
    case State::connected:
      os << "연결된 상태 - 대화";
      break;
    case State::on_hold:
      os << "대기 상태";
      break;
    case State::on_hook:
      os << "수화기 내린 상태";
      break;
  }
  return os;
}
enum class Trigger
{
  call_dialed,      //동작 : 전화 걸기
  hung_up,          //동작 : 전화 끊기
  call_connected,   //동작 : 전화 연결됨
  placed_on_hold,   //동작 : 대기
  taken_off_hold,   //동작 : 대기 종료
  left_message,     //동작 : 메세지 남기기
  stop_using_phone  //동작 : 전화 사용 종료
};

inline ostream& operator<<(ostream& os, const Trigger& t)
{
  switch (t)
  {
    case Trigger::call_dialed:
      os << "동작 : 전화 걸기";
      break;
    case Trigger::hung_up:
      os << "동작 : 전화 끊기";
      break;
    case Trigger::call_connected:
      os << "동작 : 전화 연결됨";
      break;
    case Trigger::placed_on_hold:
      os << "동작 : 대기";
      break;
    case Trigger::taken_off_hold:
      os << "동작 : 대기 종료";
      break;
    case Trigger::left_message:
      os << "동작 : 메세지 남기기";
      break;
    case Trigger::stop_using_phone:
      os << "동작 : 전화 사용 종료";
      break;
    default: break;
  }
  return os;
}

int main()
{
  map<State, vector<pair<Trigger, State>>> rules;
  /*
  key : 현재 state
  value : state를 변경하는 동작, 바뀐 state
  rules[현재 state] = {{변경동작1, 바뀐 state1},{변경동작2, 바뀐 state2}}
  이처럼 현재 state에 대해 여러 변경동작으로 state가 여러가지로 바뀔 수 있다.
  단 하나의 동작으로 여러개의 state가 존재하게 하는 방식은 다시 설계해야겠지?
  */

  rules[State::off_hook] = {
    {Trigger::call_dialed, State::connecting},
    {Trigger::stop_using_phone, State::on_hook}
  };

  rules[State::connecting] = {
    {Trigger::hung_up, State::off_hook},
    {Trigger::call_connected, State::connected}
  };

  rules[State::connected] = {
    {Trigger::left_message, State::off_hook},
    {Trigger::hung_up, State::off_hook},
    {Trigger::placed_on_hold, State::on_hold}
  };

  rules[State::on_hold] = {
    {Trigger::taken_off_hold, State::connected},
    {Trigger::hung_up, State::off_hook}
  };

  State currentState{ State::off_hook },
    exitState{ State::on_hook };

  while (true)
  {
    cout << "현재 전화 상태 : " << currentState << endl;
    select_trigger:
    cout << "동작을 선택하세요 :" << "\n";
 
    int i = 0;
    for (auto item : rules[currentState])
    {
      cout << i++ << ". " << item.first << "\n";
    }

    int input;
    cin >> input;
    if (input < 0 || (input+1) > rules[currentState].size())
    {
      cout << "잘못된 동작입니다. 다시 선택해주세요" << "\n";
      goto select_trigger;
    }

    currentState = rules[currentState][input].second;
    if (currentState == exitState) break;
  }

  cout << "전화의 사용을 종료합니다." << "\n";

  getchar();
  getchar();
  return 0;
}
