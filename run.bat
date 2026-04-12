@echo off
title 个人信息管理系统
color 0A

echo ========================================
echo     个人信息管理系统一键启动
echo ========================================
echo.

:: 检查GCC
gcc --version >nul 2>&1
if %errorlevel% neq 0 (
    echo 错误：未找到GCC编译器！
    echo 请安装Dev-C++或MinGW并添加到PATH环境变量
    echo.
    pause
    exit /b
)

:: 创建数据目录
if not exist "data" mkdir data

:: 清理旧文件
if exist "frontend.exe" del "frontend.exe"

echo 正在编译系统...
echo.

:: 编译命令
gcc frontend/frontend_main.c backend/src/api/backend_api.c backend/src/core/student_manager.c backend/src/core/consumption_manager.c backend/src/core/course_manager.c backend/src/storage/file_storage.c include/common.c -Iinclude -o frontend.exe

:: 检查编译结果
if exist "frontend.exe" (
    echo.
    echo ========================================
    echo      编译成功！系统启动中...
    echo ========================================
    echo.
    echo 启动个人信息管理系统...
    chcp 65001 >nul
    frontend.exe
) else (
    echo.
    echo 编译失败！请检查代码错误
    pause
)
