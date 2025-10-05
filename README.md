# c++ exercising

> 저는 현장에서 java, c#, javascript, python 등 다양한 언어를 사용하고 있지만, 
> 가장 기본이 되는 언어는 C/C++ 언어라고 생각합니다.
> C언어는 시스템 프로그래밍, 임베디드 시스템, 운영체제 개발 등 다양한 분야에서 사용되며, 
> 다른 언어의 기초가 되는 중요한 언어입니다.
> C언어에 이어 거의 같은 소스들로 C++ 소스코딩을 하여 정리 했습니다.
> 이 저장소는 C++언어의 다양한 예제를 통해 학습하고자 하는 분들에게 도움이 되고자 합니다.

##  ✨  Project 구조

- main.cpp 내 메뉴구조체를 선언 하고  메뉴배열을 만들어 사용합니다.
- 한습이 진행되는 동안 각 학습 주제별 소스를 생성한 후 메뉴구조체 배열의 요소로 추가하여
- 사용자가 선택하여 실행 되도록 합니다.

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
