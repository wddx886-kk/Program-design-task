# 编译后端
gcc -c backend/backend_main.c -Iinclude -o backend_main.o

# 编译前端  
gcc -c frontend/frontend_main.c -Iinclude -o frontend_main.o
gcc -c include/common.c -Iinclude -o common.o

# 链接生成可执行文件
gcc frontend_main.o common.o -o frontend.exe

# 运行程序
frontend.exe