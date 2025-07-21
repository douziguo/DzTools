# CrashHandle

崩溃捕获模块



### 使用方式

pro 文件中

```bash
# 引入崩溃捕获模块
include(pathTo/CrashHandle.pri)
```

main 函数中

```c++
// 注册崩溃捕获功能
initCrashHandle();
```



## TODO

- [ ] dmp 文件自动上报



## 更新日志

#### 2021/11/10

- 整理为独立的模块
