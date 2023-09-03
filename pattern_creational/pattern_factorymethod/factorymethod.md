# 정리
1. client는 product를 직접생성하지 않고 absFactory로부터 의존성주입받았다.

2. absFactoryd 역시 product를 직접생성하지 않고 concFactory로부터 의존성 주입을 받았다.

3. factory --> abstract factory + concrete factories 로 바꾸어 concrete factory로 생성을 위임했다는 것이 중요하다!
abstract factory로 concrete factory의 함수 호출로 product를 생성할 수 있다.