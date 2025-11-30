# c++ exercising

> 저는 현장에서 java, c#, javascript, python 등 다양한 언어를 사용하고 있지만,
> 가장 기본이 되는 언어는 C/C++ 언어라고 생각합니다.
> C언어에서 구현했던 소스들을 C++ 소스코딩을 하여 정리 했습니다.
> 이 저장소는 C++언어의 다양한 예제를 통해 학습하고자 하는 분들에게 도움이 되고자 합니다.

##  ✨  Project 구조

- main.cpp 내 메뉴구조체를 선언 하고  메뉴배열을 만들어 사용합니다.
- 한습이 진행되는 동안 각 학습 주제별 소스를 생성한 후 메뉴구조체 배열의 요소로 추가하여
- 사용자가 선택하여 실행 되도록 합니다.

```
# JSON 라이브러리 추가
# ++에는 기본 JSON 라이브러리가 없으므로,
# 널리 사용되는 헤더 파일 하나로 구성된 nlohmann/json 라이브러리를 사용
# 다운로드: 이 링크를 클릭하여 json.hpp 파일을 다운로드하세요.
# 파일 이동: 다운로드한 json.hpp 파일을 프로젝트의 include 폴더 안으로 옮겨주세요.
# Single-Header 버전 사용: 모든 코드가 하나의 거대한 json.hpp 파일에 포함되어 있어,
# 이 파일 하나만 있으면 다른 파일 없이도 라이브러리를 사용할 수 있습니다.

https://github.com/nlohmann/json/releases
```

---

```
# Project 기본 구조
cppEx/
├── .vscode/
│   ├── launch.json
│   └── tasks.json
├── bin/
├── include/
│   ├── helloEx.h
│   └── vectorEx.h
├── src/
│   ├── helloEx.c
│   ├── main.cpp
│   └── vectorEx.cpp
├── Makefile
└── README.md
```

---

##  ✨ .vscode/tasks.json

```
    Purpose

    Encapsulates shell commands (compile, run linters, generate docs) as named tasks the editor can run.
    Let VS Code show build output and link errors to the editor via problem matchers.
    Contract (simple)

    Inputs: active file(s) or workspace variables (e.g. ${file}, ${workspaceFolder}), the compiler command and args.
    Output: compiled binary (or other generated artifacts), and compiler diagnostics surfaced in Problems panel.
    Error modes: task fails (non-zero exit) and problem matcher parses errors; VS Code shows diagnostics.
    Success criteria: binary created at expected path, Problems panel either empty or shows parseable errors.
    Key fields you’ll commonly use

    version: tasks schema version (usually "2.0.0").
    tasks: array of task definitions.
    label: task name (used by preLaunchTask and UI).
    type: "shell" (runs a shell command) or "process".
    command: command to run (e.g., clang++).
    args: array of arguments; use variables like ${file}, ${fileDirname}, ${fileBasenameNoExtension}.
    group: marks task as build/test (so Cmd+Shift+B picks default).
    problemMatcher: e.g. "$gcc" so clang/clang++ errors are clickable.
    options.cwd: working directory for the command.
    presentation: controls terminal visibility.
    isBackground: for watch tasks.

```

```json
    {
        "version": "2.0.0",
        "tasks": [
            {
            "label": "build project",
            "type": "shell",
            "command": "clang++",
            "args": [
                "-std=c++17",
                "-O0",
                "-g",
                "-Wall",
                "-o",
                "${workspaceFolder}/main",
                "${workspaceFolder}/*.cpp",
                "${workspaceFolder}/*.c"
            ],
            "group": {
                "kind": "build",
                "isDefault": true
            },
            "problemMatcher": ["$gcc"],
            "detail": "Compile all .cpp and .c files in the project with clang++"
            }
        ]
    }
```

```
    How to use
    Open a C++ file and press Cmd+Shift+B to run the build task (creates executable next to the source file).
    Reference label from launch.json as preLaunchTask so debugging automatically builds.

    Edge cases / tips
    Ensure your compiler is on PATH (e.g. xcode-select --install) or use full path clang++.
    If you install LLVM from Homebrew, point to that compiler explicitly or update PATH.
    Use problemMatcher so errors become clickable; if mismatch, you won’t get clickable errors.

```


##  ✨ .vscode/launch.json


```
    Purpose

    Defines how VS Code starts or attaches a debugger to your program.
    Stores multiple debug configs (launch variants, attach-to-process, remote, core dump).
    Contract (simple)

    Inputs: path to compiled program (program), optional preLaunchTask, debugger type (lldb/cppdbg), program arguments.
    Output: debugger session where you can set breakpoints, inspect variables, step.
    Error modes: missing binary, missing debug symbols, or mismatched debugger type cause failures.
    Success criteria: breakpoints hit, variables visible, program controllable from VS Code.
    Key fields you’ll commonly use

    version: schema version (usually "0.2.0").
    configurations: array of debug configs.
    name: shown in run/debug dropdown.
    type: "lldb" (CodeLLDB) or "cppdbg" (Microsoft C++ debugger). On mac, lldb (CodeLLDB) is recommended.
    request: "launch" or "attach".
    program: path to executable (use variables like ${fileDirname}/${fileBasenameNoExtension} or ${workspaceFolder}/bin/myprog).
    args: program command-line args.
    cwd: working directory (often ${workspaceFolder} or ${fileDirname}).
    preLaunchTask: label of a task from tasks.json to run before launching (typically your build task).
    stopOnEntry / stopAtEntry: whether to pause at start.
    env: environment variables.
    externalConsole / runInTerminal: whether to open a separate terminal for I/O.
```

```json
    {
        "version": "0.2.0",
        "configurations": [
            {
            "name": "Launch Project (lldb)",
            "type": "lldb",
            "request": "launch",
            "program": "${workspaceFolder}/main",
            "args": [],
            "cwd": "${workspaceFolder}",
            "preLaunchTask": "build project",
            "stopOnEntry": false
            }
        ]
    }
```

```
    Type choice: lldb vs cppdbg

    lldb (CodeLLDB extension) — easy to use on macOS, modern UI, fast.
    cppdbg (ms-vscode.cpptools) — cross-platform, supports GDB/LLDB via MIMode; requires more config (MIMode, miDebuggerPath) to use LLDB properly.

    Common pitfalls
    Debugger says binary not found: check program path and that preLaunchTask produced the executable there.
    Breakpoints are ignored: ensure binary built with -g and -O0 (debug symbols, no optimization).
    preLaunchTask label mismatch: the label in tasks.json must exactly match.
    Path variables: ${file} vs ${workspaceFolder} — use ${fileDirname} for single-file launches.


    How to use
    Press F5 to run the selected configuration.
    Use preLaunchTask to build before debugging automatically.
    Set a breakpoint in the editor and run; the debugger should stop there.

    Example workflow for your main.cpp (copy-and-paste)
    Build from terminal (manual quick test):

    $ clang++ -std=c++17 -O0 -g -Wall -o main main.cpp
    # ./main


    VS Code (automated)

    Add tasks.json with a task labeled e.g. "build active file".
    Add launch.json referencing that preLaunchTask.
    Open main.cpp, press Cmd+Shift+B to build, or press F5 to build+debug.
```

## Getting Started
1. Clone the repository to your local machine.
2. Navigate to the directory containing the examples.
3. Compile all example using `make` command.
4. Run the compiled executable ( ./main ) to see the output.
---

![memory_segment](memory_segment.png)

```c
// Contents

MenuItem menu_items[] = {
    {"Hello World", say_hello},                                              // Example function from helloEx.c
    {"Data Types Example", data_typesEx},                                    // Example function from data_typesEx.cpp
    {"Preprocessor Directives Example", preprocessor_directivesEx},          // Example function from preprocessor_directivesEx.cpp
    {"Bit Manipulation Example", bit_manipulationEx},                        // Example function from bit_manipulationEx.cpp
    {"Functions Example", functionsEx},                                      // Example function from functionsEx.cpp
    {"Arrays Example", arraysEx},                                            // Example function from arraysEx.cpp
    {"Pointers Example", pointersEx},                                        // Example function from pointersEx.cpp
    {"Vector Example", vectorEx},                                            // Example function from vectorEx.cpp
    {"Typedefs Example", typedefsEx},                                        // Example function from typedefsEx.cpp
    {"Structures Example", structuresEx},                                    // Example function from structuresEx.cpp
    {"Unions Example", unionsEx},                                            // Example function from unionsEx.cpp
    {"Enums Example", enumsEx},                                              // Example function from enumsEx.cpp
    {"C++ Class Example", cpp_classEx},                                      // Example function from cpp_classEx.cpp
    {"Polymorphism and Interfaces Example", polymorphismEx},                 // Example function from polymorphismEx.cpp
    {"Task Management Example", taskManagementEx},                           // Example function from taskManagementEx.cpp
    {"Memory Management Example", memory_managementEx},                      // Example function from memory_managementEx.cpp
    {"Dynamic Memory Allocation Example", dynamic_memory_allocationEx},      // Example function from dynamic_memory_allocationEx.cpp
    {"File I/O Example", file_ioEx},                                         // Example function from file_ioEx.cpp
    {"Searching Algorithms Example", searching_algorithmsEx},                // Example function from searching_algorithmsEx.cpp
    {"Sorting Algorithms Example", sorting_algorithmsEx},                    // Example function from sorting_algorithmsEx.cpp
    {"Stack Data Structure Example", stack_data_structureEx},                // Example function from stack_data_structureEx.cpp
    {"Queue Data Structure Example", queue_data_structureEx},                // Example function from queue_data_structureEx.cpp
    {"Linked List Data Structure Example", linked_list_data_structureEx},    // Example function from linked_list_data_structureEx.cpp
    {"Double Linked List Example", double_linked_list_data_structureEx},     // Example function from double_linked_list_data_structureEx.cpp
    {"Circular Linked List Example", circular_linked_list_data_structureEx}, // Example function from circular_linked_list_data_structureEx.cpp
    {"Binary Tree Example", binary_tree_data_structureEx},                   // Example function from binary_tree_data_structureEx.cpp
    {"Hash Table Example", hash_table_data_structureEx},                     // Example function from hash_table_data_structureEx.cpp
    {"Graphs Example", graphs_data_structureEx},                             // Example function from graphs_data_structureEx.cpp
    {"Error Handling Example", error_handlingEx},                            // Example function from error_handlingEx.cpp
    {"Smart Pointers Example", smart_pointerEx},                             // Example function from smart_pointerEx.cpp
    {"Socket Programming Example", socket_programmingEx},                    // Example function from socket_programmingEx.cpp
    {"Networking Basics Example", networking_basicsEx},                      // Example function from networking_basicsEx.cpp
    {"Multithreading Example", multithreadingEx},                            // Example function from multithreadingEx.cpp
    {"Task Management (Smart Pointers)", task_management_using_smart_pointerEx}, // Example function from task_management_using_smart_pointerEx.cpp
    {"*** Snake Game Example", snake_gameEx},                                     // Example function from snake_gameEx.cpp
    {"*** Tetris Game Example", tetris_gameEx}                                      // Example function from tetris_gameEx.cpp
};
```

---

## 📝 상세 설명

### 1. 프로젝트 목적
*   C/C++의 기본 문법부터 심화 내용까지 다양한 예제를 코드로 직접 확인하고 실행해 볼 수 있습니다.
*   `main.cpp`가 **메뉴 역할**을 하여, 프로그램을 실행하면 원하는 예제를 선택해서 동작을 확인할 수 있는 구조로 되어 있습니다.

### 2. 주요 포함 내용 (`src` 폴더)
다양한 주제의 예제 코드가 포함되어 있습니다.
*   **기본 문법**: 포인터, 구조체, 공용체, 함수, 비트 연산 등
*   **자료구조**: 연결 리스트(Linked List), 스택(Stack), 큐(Queue), 이진 트리(Binary Tree), 해시 테이블(Hash Table) 등
*   **알고리즘**: 정렬(Sorting), 탐색(Searching)
*   **시스템 프로그래밍**: 멀티스레딩, 소켓 프로그래밍, 파일 I/O
*   **미니 게임**: 스네이크 게임(`snake_gameEx`), 테트리스(`tetris_gameEx`)

### 3. 프로젝트 구조 설명
*   **`src/`**: 소스 코드 파일들이 위치합니다. (`main.cpp` 및 각 예제 파일들)
*   **`include/`**: 헤더 파일들이 위치합니다.
*   **`bin/`**: 컴파일된 실행 파일과 오브젝트 파일(`*.o`)이 저장되는 폴더입니다.
*   **`Makefile`**: `make` 명령어를 통해 프로젝트를 쉽게 빌드할 수 있도록 설정된 파일입니다.
*   **`.vscode/`**: VS Code 사용자를 위한 빌드(`tasks.json`) 및 디버깅(`launch.json`) 설정이 포함되어 있습니다.

### 4. 실행 방법 (Make)
터미널에서 다음 명령어를 사용하여 빌드하고 실행할 수 있습니다.

1.  **빌드**: `make`
2.  **빌드 후 main 파일 복사**: `make copy_main`
3.  **실행**: `main`

### 5. 개발 환경 설정 (VS Code IntelliSense)

이 프로젝트는 VS Code에서 원활한 코드 분석 및 자동 완성을 위해 `compile_commands.json`을 사용합니다.

#### `compile_commands.json`
*   **용도**: 컴파일 데이터베이스 파일로, 각 소스 파일의 컴파일 명령어 정보를 담고 있습니다.
*   **효과**: VS Code(IntelliSense)가 이 파일을 참조하여 헤더 파일 경로를 인식하고, 정확한 코드 자동 완성 및 에러 표시 기능을 제공합니다.

#### `generate_compile_commands.py`
*   **용도**: `compile_commands.json` 파일을 자동으로 생성하는 파이썬 스크립트입니다.
*   **사용법**: 새로운 소스 파일을 추가하거나 빌드 설정이 바뀌었을 때 아래 명령어를 실행하세요.
    ```bash
    python3 generate_compile_commands.py
    ```



