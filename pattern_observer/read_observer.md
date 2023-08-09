polling으로 매번 변화를 관찰하는 것이아닌,
변경이 일어날 때마다 호출되는 멤버함수 ==> 콜백

동시성 문제에서 vector의 사용
- mutex를 활용
- concurrent_vector 사용


---
## Ovserver pattern

- polling 방식처럼 변화를 반복적으로 감지하지 않을 때 사용하기 용이한 패턴
- 변경되었을 때 통보 = 콜백함수 방식
- 변경 전/후의 상태 차이가 필요할 수도 있다.
- subject = observable(관찰대상)이 observer들에게 변화를 통보한다.
- observer(관찰자) 는 변화를 통보받는다. observer의 변화를 subject에 전달하여 다른 observer들에게 통보할 수 있다.
- 변화되는 리소스는 subject or observable이 갖고 있다. 하지만 이 리소스는 observer가 필요로하는 리소스이기 때문에 통보받아야하는 것이다.
- subject는 observer의 목록을 가진다.
- subect의 기본 구조는
    - 통보할 대상
    - observer 
        - 등록 함수
        - 삭제 함수
        - 통보 함수
- 비동기로 observer들이 통보받을 수 있는데, 이를 위해서 mutex lock을 걸거나, concurrent_vector를 이용한다.