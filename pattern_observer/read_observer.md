# Ovserver pattern
## 1. 언제 쓸까?
    - polling으로 변화를 감지하게 하지 않도록할 때
## 2. 어떻게 쓸까?
    1) 구성 : 주는 놈, 받는 놈
        - 주는 놈
            - 관찰 대상
            - subject
            - observable
        - 받는 놈
            - 관찰자
            - listener
            - observer
    2) 주는 놈 구성
        (1) interface
            어디까지나  확장성을 위해
        (2) concrete class
            - 받는놈 vector
            - 받는 놈의 관심대상
            - subscribe() //등록-받는 놈
            - unsubscribe() //해제-받는 놈
            - notify() //알림-관심대상의 변화, 받는 놈의 callback 호출
    3) 받는 놈 구성
        (1) interface
            어디까지나  확장성을 위해
        (2) concrete class
            - callback() //notify 호출 시 동작
## 3. 추가 고려사항
### 변수 관련
    1) dependency
        관찰 대상인 변수값이 바뀔  때 함께 영향을 받는 다른 대상이 있는 경우엔
        필드가 많아지고 종속성이 복잡하면 유지보수가 매우 힘들어진다.
            예) 엑셀에서 한 셀이 바뀌면 연산에 연관된 다른 셀들도 함께 값이 바뀜
        
        해결방법 : 변수간 관련성을 관리하는 map 형 변수를 둔다. 이는 관리할 때 번거로움이 될 수 있다.

### 비동기 관련 
    1) thread safe - 수신해제 관련
        std::vector는 thread_unsafe 하다. 
        그러므로 subscribe와 unsubscribe의 동시호출이 될경우 문제발생이 가능하다. 
        
        해결방법1 : subscribe(), unsubscribe(), notify() 모두 lock을 걸어 해결한다.
        해결방법2 :  thread_safe한 concurrent_vector를 이용한다.

    2) reentrancy(재진입)
        thread safe를 위해 lock을 걸게되면 double lock 하는 시나리오를 생각해야한다.
        예를 들어 특정 상황이 되면 그것을 알리고 구독을 해제하는 경우
        ex) notify(lock) --> unsubscribe(lock)

        해결방법1 : 이런 상황을 만들지 않는다.
        해결방법2 : unsubscribe 시 삭제가 아닌 nullptr로 처리한다.이를 대비한 notify에서도 null 조건을 체크하는 로직이 추가되어야한다.
        추가로 드는 생각은 nullptr 로 변경되기 전 null 후보가 되는 observer 배열을 따로 관리해서 이는 thread safe 하니 여기서 삭제하도록 한다.
        해결방법3 : observer 배열을 복사해서 사용한다.

### observer 관리 관련
    1) subscribe를 중복할 땐?

    2) 중복된 observer 를 unsubscribe 할 때 하나만 지울 지 모두 지울지?

### container 관련
    1) 다른 종류의 container로 observer를 관리할 땐?

    2) observer 간 우선순위가 있을 땐?