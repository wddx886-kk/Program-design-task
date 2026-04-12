#include "../include/interfaces.h"

// 全局后端API指针
BackendAPI *g_backend_api = NULL;

// 获取后端API接口
BackendAPI* get_backend_api() {
    if (g_backend_api == NULL) {
        g_backend_api = init_backend_api();
    }
    return g_backend_api;
}

// 清理后端
void cleanup_backend() {
    if (g_backend_api != NULL) {
        cleanup_backend_api(g_backend_api);
        g_backend_api = NULL;
    }
}

// 后端主程序（实际上不运行GUI，只是提供API服务）
int main() {
    // 初始化后端服务
    BackendAPI *api = get_backend_api();

    printf("Backend service initialized successfully!\n");
    printf("Waiting for frontend requests...\n");

    // 在实际应用中，这里会启动网络服务或IPC机制
    // 为了演示，我们只是保持后端运行

    // 清理资源
    cleanup_backend();
    return 0;
}
