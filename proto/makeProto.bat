@echo off
echo 开始编译当前目录下的 .proto 文件...
echo ====================================

:: 查找当前目录所有 .proto 文件
for %%f in (*.proto) do (
    echo 正在编译: %%~nxf

    :: 生成 C++ 源文件（.cc 和 .h）
    protoc -I=. --cpp_out=. "%%~f"

    if !errorlevel! equ 0 (
        echo ✓ 成功: 生成 %%~nf.pb.h 和 %%~nf.pb.cc
    ) else (
        echo ✗ 错误: 编译失败 - 请检查 %%~nxf
    )
    echo ----------------------------
)

echo ====================================
echo 编译完成! 按任意键退出...
pause >nul