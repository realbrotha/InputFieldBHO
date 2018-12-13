# InputFieldBHO
## Description
제작 : 2012년도 1~2월쯤 </br>
개발 환경 : vs 6.0 + SDK ->vs2015 포팅 진행</br>

## Issue....

**대학을 막졸업한뒤라 코드상의 문제점이 엄청나게 많다.**</br>
**사실 공유하기도 부끄러울 코드지만 ... 포트폴리오 성으로 남겨둔다..**</br>

1. Ansi 코드로 작성함 (COM 객체들이 ansi 스타일에 사용이 편해서 ... 사용했었던것으로 보임)</br>
2. 여러가지 이벤트 나 예외처리가 부족하여 특정 상황에서 IE 브라우저에 Crash가 발생함.</br>
3. Key값을 대충 출력함 (대소문자 / 한글 상태 여부 등등)</br>
4. 키보드 필터드라이버 사용 X</br>

## Release

v1.0 : vs6.0 -> vs2015 포팅 진행 (x64 컴파일 테스트)</br>
v0.9 : 다이어로그 추가</br>
v0.6 : 방어코드 추가</br>
v0.5 : 이상한 구조 변경 / 이해하지 못하던 코드들 삭제</br> 
v0.1 : 초기 작업</br>

## How to ??

> cmd -> regsvr32 InputFieldBHO.dll
> IE 브라우저 실행 -> 원하는 페이지로 이동 -> F9 Key 입력 -> 키로깅 가능 여부 확인 / DOM을 이용한 Input Value 획득 확인

![id_pwd](https://user-images.githubusercontent.com/28824715/49877259-5e7b6880-fe68-11e8-8c5e-abf901063e6c.jpg)

