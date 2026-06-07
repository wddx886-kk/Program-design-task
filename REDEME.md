个人信息管理系统
一个基于C语言开发的、采用经典前后端分离架构的命令行个人信息管理系统。该系统支持对学生基本信息、消费记录和课程成绩进行全面的增、删、改、查操作，并通过二进制文件实现数据持久化。

🚀 功能特性
学生信息管理

✅ 添加学生信息
✅ 查找学生信息 (按学号)
✅ 修改学生信息
✅ 删除学生信息
✅ 显示所有学生信息 (表格形式)
消费记录管理

✅ 添加消费记录 (自动填充日期)
✅ 查找学生消费记录
✅ 修改/删除消费记录
✅ 显示所有消费记录
✅ 统计学生消费总额
课程成绩管理

✅ 添加课程成绩
✅ 查找学生课程成绩
✅ 修改/删除课程成绩
✅ 显示所有课程成绩
✅ 统计学生成绩 (总分、平均分、课程数)
🏗️ 项目架构
本项目采用清晰的分层架构，确保了代码的模块化、可维护性和可扩展性。

.
├── backend/                # 后端目录
│   ├── backend_api.c       # API门面，实现前后端解耦
│   ├── student_manager.c   # 学生信息业务逻辑
│   ├── consumption_manager.c # 消费记录业务逻辑
│   ├── course_manager.c    # 课程成绩业务逻辑
│   └── file_storage.c      # 数据持久化层 (文件I/O)
│
├── frontend/               # 前端目录
│   └── frontend_main.c     # 命令行用户界面
│
└── include/                # 公共头文件目录
    ├── common.h            # 通用定义、常量和工具函数声明
    ├── date_structures.h   # 核心数据结构定义
    └── interfaces.h        # 后端API接口定义 (前后端契约)
核心设计亮点
前后端分离: 前端 (frontend_main.c) 通过定义在 interfaces.h 中的 BackendAPI 结构体与后端通信，两者完全解耦。
模块化设计: 学生、消费、课程管理模块各自独立，职责单一。
数据持久化: 使用二进制文件 (.dat) 存储数据，程序重启后数据不丢失。
引用完整性: 添加消费或课程记录前，会自动检查关联的学生是否存在。
健壮性: 包含输入验证、边界检查和错误处理机制。
🛠️ 技术栈
语言: C
标准库: stdio.h, stdlib.h, string.h, time.h
编译器: GCC (推荐) / Clang / MSVC
📦 安装与编译
前置条件
确保你的系统已安装GCC编译器。

Linux/macOS: 通常已预装。可通过 gcc --version 检查。
Windows: 可通过 MinGW-w64 或 WSL 安装GCC。
克隆仓库
git clone https://github.com/your-username/personal-info-system.git
cd personal-info-system
编译项目
创建一个简单的构建脚本 (可选): 你可以创建一个 build.sh (Linux/macOS) 或 build.bat (Windows) 文件来简化编译过程。

build.sh (Linux/macOS):

#!/bin/bash
echo "Compiling the Personal Information Management System..."
gcc -o personal_info_system \
    frontend/frontend_main.c \
    backend/backend_api.c \
    backend/student_manager.c \
    backend/consumption_manager.c \
    backend/course_manager.c \
    backend/file_storage.c \
    common.c
echo "Compilation successful! Run with ./personal_info_system"
build.bat (Windows):

@echo off
echo Compiling the Personal Information Management System...
gcc -o personal_info_system.exe ^
    frontend\frontend_main.c ^
    backend\backend_api.c ^
    backend\student_manager.c ^
    backend\consumption_manager.c ^
    backend\course_manager.c ^
    backend\file_storage.c ^
    common.c
echo Compilation successful! Run with personal_info_system.exe
pause
直接编译: 如果你没有创建脚本，也可以直接在终端中运行以下命令 (注意：根据你的操作系统调整路径分隔符 \ 或 /):

# 在项目根目录下执行
gcc -o personal_info_system frontend/frontend_main.c backend/*.c common.c
🎮 使用方法
编译成功后，直接运行生成的可执行文件。

Linux/macOS:
./personal_info_system
Windows:
personal_info_system.exe
程序启动后，你将看到一个主菜单，通过输入对应的数字即可进入不同的功能模块。请按照屏幕上的提示进行操作。

首次运行
程序首次运行时，会自动在可执行文件同级目录下创建一个 data/ 文件夹，并生成 students.dat, consumptions.dat, courses.dat 三个空的数据文件。

🗂️ 文件说明
data/students.dat: 存储所有学生信息的二进制文件。
data/consumptions.dat: 存储所有消费记录的二进制文件。
data/courses.dat: 存储所有课程成绩的二进制文件。
警告: 请勿手动编辑这些 .dat 文件，这可能导致数据损坏和程序崩溃。

🤝 贡献指南
欢迎提交 Issue 和 Pull Request 来帮助改进这个项目！

Fork 这个仓库。
创建你的特性分支 (git checkout -b feature/AmazingFeature)。
提交你的改动 (git commit -m 'Add some AmazingFeature')。
推送到分支 (git push origin feature/AmazingFeature)。
打开一个 Pull Request。
📝 许可证
本项目采用 MIT 许可证。详情请参阅 LICENSE [blocked] 文件。

🙏 致谢
感谢所有为C语言标准库做出贡献的开发者。
项目的设计灵感来源于现代软件工程的最佳实践。
