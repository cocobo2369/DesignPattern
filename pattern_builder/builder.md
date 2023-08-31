# Builder pattern
## 1. 언제 쓸까?
    - 복합객체를 생성할 때
        -   복합객체를 사용하는 경우?
            - A라는 객체를 만들기 위해 default, a, b  라는 부품이 사용 가능할 때,
            필수인 default를 제외한 a,b 의 조합 2x2 = 4 가지를 생성 가능하게 만들 수 있다. 
            - 정리하면 builder 패턴은 여러 객체(default, a,b) 를 담는 객체를 여러 조합 방식(2x2)을 선택하여 하나의 복합객체를 만들 때 사용하는 패턴이다.
            - case) 한 생성자에 너무 많은 파라미터를 전달
                - 몇번 째 파라미터에 어떤 값인가? 에 대한 실수 유발이 쉽다.
                - 생성자엔 반드시 초기화할 파라미터만 전달하고, 필요에 따라 함수로 나머지 값을 전달하여, 최종 복합객체를 생성한다.


## 2. 어떻게 쓸까?
    1. client
        - builder가 생성한 객체를 사용
    2. director(생략가능)
        - builder의 여러 결과물을 만들 수 있는 함수 제시
        - 만드는 방식이 하나 뿐이라면 director는 생략 가능
    3. builder_interface
    4. builder_concrete
        - 생성을 위임받은 객체
        - 복합 객체 생성
        - 부품 객체의 setter 함수
        - 생성된 객체를 반환하는 함수 필요
    5. result
        - builder 산출물

## 3. 추가 고려사항
### fluent builder
    builder 자기자신을 return 할수 있게 하여 객체 생성 시 생성자에는 필수로 사용할 파라미터만 전달받고, 선별적으로 사용할 파라미터는 setter 함수를 호출하여 객체를 생성함. 가독성이 높아짐
    ```
        Result A = new Builder::builder('defaultA','defaultB')
                    .setPartsC(123)
                    .setPartsD("cb")
                    .build();
    ```