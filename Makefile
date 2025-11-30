# ------------------------------------------------------------
# Makefile을 사용하는 이유
# ------------------------------------------------------------
# 증분 빌드 (Incremental Build):
# - Makefile의 가장 큰 장점입니다.
#   소스 코드의 일부만 변경했을 때,
#   전체 프로젝트를 다시 컴파일하는 대신 변경된 부분과 관련된 파일만 다시 컴파일합니다.
#   프로젝트가 커질수록 빌드 시간을 획기적으로 줄여줍니다.
#
# 유연성 및 확장성:
# - 소스 파일을 src 폴더에, 헤더 파일을 include 폴더에,
#   빌드 결과물을 bin 폴더에 두는 등 복잡한 프로젝트 구조를 쉽게 관리할 수 있습니다.
#
# 이식성:
# - Makefile은 표준 빌드 시스템이므로,
#   VS Code가 없는 환경에서도 터미널에서 make 명령어 하나로 프로젝트를 빌드할 수 있습니다.
#
# ```
# # Project 기본 구조
# cppEx/
# ├── .vscode/
# │   ├── launch.json
# │   └── tasks.json
# ├── bin/
# ├── include/
# │   ├── helloEx.h
# │   └── vectorEx.h
# ├── src/
# │   ├── helloEx.c
# │   ├── main.cpp
# │   └── vectorEx.cpp
# ├── Makefile
# └── README.md
# ```
#
# ------------------------------------------------------------

# 컴파일러 설정
CXX = clang++
CC = clang

# 디렉토리 경로 설정
SRC_DIR = src
INCLUDE_DIR = include
BIN_DIR = bin

# 컴파일러 플래그
# -g: 디버깅 정보 포함
# -Wall: 모든 경고 활성화
# -std=c++17: C++17 표준 사용
# -I$(INCLUDE_DIR): include 폴더를 헤더 검색 경로에 추가
CXXFLAGS = -g -Wall -std=c++17 -I$(INCLUDE_DIR)
CFLAGS = -g -Wall -I$(INCLUDE_DIR)

# 링커 플래그 (필요 시 라이브러리 추가, 예: -lm)
LDFLAGS =

# 실행 파일 이름
TARGET = $(BIN_DIR)/main

# 소스 파일 자동 탐색
# wildcard 함수를 사용해 현재 디렉토리의 모든 .cpp와 .c 파일을 찾습니다.
CPP_SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
C_SOURCES = $(wildcard $(SRC_DIR)/*.c)

# 소스 파일로부터 오브젝트 파일(.o) 목록 생성
# 예: src/main.cpp -> bin/main.o
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(BIN_DIR)/%.o, $(CPP_SOURCES))
OBJECTS += $(patsubst $(SRC_DIR)/%.c, $(BIN_DIR)/%.o, $(C_SOURCES))

# --- 빌드 규칙 ---

# 기본 규칙: 'make' 또는 'make all'을 실행하면 TARGET을 빌드합니다.
all: $(TARGET)

# bin 디렉토리가 없으면 생성
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# 실행 파일(TARGET)을 빌드하는 규칙
# 오브젝트 파일들($(OBJECTS))을 링크하여 최종 실행 파일을 생성합니다.
$(TARGET): $(OBJECTS) | $(BIN_DIR)
	$(CXX) $(LDFLAGS) -o $@ $^

# C++ 소스 파일(.cpp)을 오브젝트 파일(.o)로 컴파일하는 규칙
# bin/%.o: src/%.cpp
$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# C 소스 파일(.c)을 오브젝트 파일(.o)로 컴파일하는 규칙
# bin/%.o: src/%.c
$(BIN_DIR)/%.o: $(SRC_DIR)/%.c | $(BIN_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

# --- 정리 규칙 ---

# 'make clean'을 실행하면 생성된 파일들을 삭제합니다.
clean:
	@echo "Cleaning up build files..."
	rm -rf $(BIN_DIR)
copy_main:
	@echo "Copying main executable to current directory..."
	cp $(TARGET) .

# 가상 타겟(Phony Target) 선언
# all, clean은 실제 파일 이름이 아니므로 .PHONY로 선언합니다.

