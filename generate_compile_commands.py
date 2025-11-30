import json
import os
import glob

# 프로젝트 루트 디렉토리 (스크립트가 실행되는 위치 기준)
project_dir = os.getcwd()
src_dir = os.path.join(project_dir, "src")
include_dir = os.path.join(project_dir, "include")
bin_dir = os.path.join(project_dir, "bin")

compile_commands = []

# src 디렉토리의 모든 .c 파일 찾기
src_files = glob.glob(os.path.join(src_dir, "*.cpp"))

print(f"Found {len(src_files)} source files in {src_dir}")

for src_file in src_files:
    filename = os.path.basename(src_file)
    # 객체 파일 이름 (예: main.c -> main.o)
    obj_name = os.path.splitext(filename)[0] + ".o"
    # 객체 파일 경로 (bin/main.o)
    obj_path = os.path.join("bin", obj_name)
    # 소스 파일 상대 경로 (src/main.c)
    rel_src_path = os.path.join("src", filename)

    # 컴파일 명령어 구성
    # Makefile에서 사용하는 옵션과 동일하게 맞춰줍니다.
    # clang -Wall -g -pthread -Iinclude -c -o bin/xxx.o src/xxx.c
    command = f"clang -Wall -g -pthread -Iinclude -c -o {obj_path} {rel_src_path}"

    entry = {
        "directory": project_dir,
        "command": command,
        "file": rel_src_path
    }
    compile_commands.append(entry)

# JSON 파일로 저장
output_path = os.path.join(project_dir, "compile_commands.json")
with open(output_path, "w") as f:
    json.dump(compile_commands, f, indent=4)

print(f"Successfully created {output_path}")
