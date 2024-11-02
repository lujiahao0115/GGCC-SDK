[![Page Views Count](https://badges.toozhao.com/badges/01JBP5B1BD7X0MZWRNMAJB7R1B/green.svg)](https://badges.toozhao.com/stats/01JBP5B1BD7X0MZWRNMAJB7R1B "Get your own page views count badge on badges.toozhao.com")

# GGCC-SDK

## 说明

GGCC-SDK 由 GGCC-Studio 出品，包括 GGCC-UI 图形界面库、动画库、物理引擎库、几何库等模块。

本存储库收录了由 [wangxun2008](https://github.com/wangxun2008) 编写的 GGCC-SDK 的历史版本，你可以在 [Releases](https://github.com/lujiahao0115/GGCC-SDK/releases) 页面查看更新日志，下载对应版本的 GGCC-SDK。

## 如何使用 GGCC-SDK

### 1. 全局配置

将 ggcc 文件夹复制到小熊猫 C++ 安装位置的 `mingw64\x86_64-w64-mingw32\include` 目录下。

### 2. 项目配置

将 ggcc 文件夹复制到对应的项目文件夹中，以便使用。

## 如何编译

在编译时需要链接 `-lraylib -lopengl32 -lgdi32 -lwinmm`，或者使用小熊猫 C++ 的自动链接功能。

## 其他注意事项

- GGCC-SDK 需要小熊猫 C++ 3.1.2871 才能正常使用，请先下载安装小熊猫 C++ 3.1.2871，再使用 GGCC-SDK。下载地址：[小熊猫 C++](http://royqh.net/redpandacpp/download/)

## 鸣谢

[wangxun2008](https://github.com/wangxun2008)、[Ltabsyy](https://github.com/Ltabsyy)

