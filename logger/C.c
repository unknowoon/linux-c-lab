int A();  // A 함수 선언 (순환!)

int C() {
    A();
    return 0;
}