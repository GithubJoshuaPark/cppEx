# C++ Exercising Project (cppEx)

[![c++](httPs://img.shields.io/badge/c%2B%2B-17-blue)](https://github.com/GithubJoshuaPark/cppEx.git)

> 저는 현장에서 java, c#, javascript, python 등 다양한 언어를 사용하고 있지만,
> 가장 기본이 되는 언어는 C/C++ 언어라고 생각합니다.
> C언어에서 구현했던 소스들을 C++ 소스코딩을 하여 정리 했습니다.
> 이 저장소는 C++언어의 다양한 예제를 통해 학습하고자 하는 분들에게 도움이 되고자 합니다.

---

## 📝 프로젝트 소개

이 프로젝트(**cppEx**)는 C와 C++ 언어의 다양한 기능, 자료구조, 알고리즘을 학습하고 실습하기 위해 만들어진 예제 모음입니다.
`main.cpp`가 **메뉴 역할**을 하여, 프로그램을 실행하면 원하는 예제를 선택해서 동작을 확인할 수 있는 구조로 되어 있습니다.

## ✨ 주요 기능 및 내용

다양한 주제의 예제 코드가 `src` 폴더에 포함되어 있습니다.

- **기본 문법**: 포인터, 구조체, 공용체, 함수, 비트 연산 등
- **자료구조**: 연결 리스트(Linked List), 스택(Stack), 큐(Queue), 이진 트리(Binary Tree), 해시 테이블(Hash Table) 등
- **알고리즘**: 정렬(Sorting), 탐색(Searching)
- **시스템 프로그래밍**: 멀티스레딩, 소켓 프로그래밍, 파일 I/O, 메모리 관리
- **미니 게임**: 스네이크 게임(`snake_gameEx`), 테트리스(`tetris_gameEx`)

---

## 📂 프로젝트 구조

```text
cppEx/
├── .vscode/                # VS Code 설정 파일 (빌드, 디버그, 인텔리센스)
├── bin/                    # 빌드 결과물 (실행 파일 및 .o 파일)
├── include/                # 헤더 파일 (.h, .hpp)
│   └── json.hpp            # JSON 라이브러리 (nlohmann/json)
├── src/                    # 소스 코드 (.c, .cpp)
│   ├── main.cpp            # 메인 엔트리 포인트 (메뉴 시스템)
│   └── ...                 # 각 예제 소스 파일들
├── Makefile                # 빌드 설정 파일
├── generate_compile_commands.py # IntelliSense용 설정 생성 스크립트
└── README.md               # 프로젝트 설명서
```

---

## 🚀 시작하기 (Build & Run)

### 필수 요구 사항

- C/C++ 컴파일러 (clang 또는 gcc)
- Make

### 빌드 및 실행 방법

터미널에서 다음 명령어를 순서대로 실행하세요.

1.  **프로젝트 빌드**

    ```bash
    make
    ```

2.  **실행 파일 복사 (선택 사항)**
    `bin` 폴더에 있는 실행 파일을 현재 디렉토리로 복사합니다.

    ```bash
    make copy_main
    ```

3.  **실행**

    ```bash
    # 복사했을 경우
    ./main

    # 또는 bin 폴더에서 직접 실행
    ./bin/main
    ```

---

## 💻 개발 환경 설정 (VS Code)

이 프로젝트는 **Visual Studio Code**에서 최적의 개발 경험을 제공하도록 설정되어 있습니다.

### 1. IntelliSense 설정 (`compile_commands.json`)

VS Code가 코드를 정확하게 분석하고 자동 완성을 제공하기 위해 **컴파일 데이터베이스**를 사용합니다.

- **설정 방법**: 새로운 소스 파일을 추가하거나 빌드 설정이 변경되면, 아래 파이썬 스크립트를 실행하여 `compile_commands.json`을 갱신하세요.
  ```bash
  python3 generate_compile_commands.py
  ```

### 2. VS Code 설정 파일 (`.vscode/`)

`.vscode` 폴더 내의 파일들은 다음과 같은 역할을 합니다.

- **`c_cpp_properties.json`**: C/C++ 확장 프로그램 설정 (컴파일러 경로, 인텔리센스 모드 등).
- **`tasks.json`**: 빌드 작업 설정. `Cmd+Shift+B`를 눌러 `make`를 실행할 수 있습니다.
- **`launch.json`**: 디버깅 설정. `F5`를 눌러 빌드 후 디버깅을 시작할 수 있습니다.
- **`settings.json`**: 프로젝트 전용 에디터 설정 (파일 연관 설정 등).

---

## 📚 예제 목록

`main.cpp`를 실행하면 아래의 예제들을 선택하여 실행할 수 있습니다.

- Hello World
- Data Types
- Preprocessor Directives
- Bit Manipulation
- Functions, Arrays, Pointers
- Vector (STL)
- Typedefs, Structures, Unions, Enums
- C++ Class, Polymorphism
- Task Management (Basic & Smart Pointers)
- Memory Management (Dynamic Allocation)
- File I/O
- Searching & Sorting Algorithms
- Data Structures: Stack, Queue, Linked Lists (Single, Double, Circular), Binary Tree, Hash Table, Graphs
- Error Handling
- Smart Pointers
- Socket Programming, Networking Basics
- Multithreading
- **Snake Game**
- **Tetris Game**
