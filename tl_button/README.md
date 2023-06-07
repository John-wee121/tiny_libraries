# button

## 1、介绍

> 实现一个方便移植的按键驱动程\
> 实现单击，长按，连击功能

[看图](docs\figures\status.png)

这里参考了[RT-Thread文档中心的demo](https://www.rt-thread.org/document/site/#/rt-thread-version/rt-thread-standard/tutorial/beep-player/button)
和
[杰杰的驱动代码](https://github.com/jiejieTop/rtpkg_button)

### 1.1 目录结构

> button的目录结构(参考[RT-Thread文档中心的软件包开发指南](https://www.rt-thread.org/document/site/#/rt-thread-version/rt-thread-standard/development-guide/package/package))

| 名称 | 说明 |
| ---- | ---- |
| docs  | 文档目录 |
| examples | 例子目录，并有相应的一些说明 |
| inc  | 头文件目录 |
| src  | 源代码目录 |
| port | 移植代码目录 |

### 1.2 许可证

> Apache license v2.0。

button package 遵循 Apache license v2.0 许可，详见 `LICENSE` 文件。

### 1.3 依赖

> 接口开放，不做依赖

## 2、如何打开 tl_button

使用 tl_button 可以在 tl_config_tool.exe ([1] Enter config) 的包管理器中选择它，具体路径如下：

```
Tiny Libraries Kconfig
    Button --->
        [*] Using Button
        [ ]     Using Button Example
```

然后让 tl_config_tool.exe ([2] Up to config) 的包管理器更新。

## 3、使用 tl_button

> 说明：在这里介绍 package 的移植步骤、使用方法、初始化流程、准备工作、API 等等，如果移植或 API 文档内容较多，可以将其独立至 `docs` 目录下。

在打开 hello package 后，当进行 bsp 编译时，它会被加入到 bsp 工程中进行编译。

* 完整的 API 手册可以访问这个[链接](docs/api.md)
* 更多文档位于 [`/docs`](./docs) 下，使用前 **务必查看**

## 4、注意事项

> 说明：列出在使用这个 package 过程中需要注意的事项；列出常见的问题，以及解决办法。

## 5、联系方式 & 感谢

* 维护：wlx(JohnWay)
* 主页：https://github.com/RT-Thread-packages/hello
* 邮箱：1973372075@qq.com
* 感谢：[RT-Thread](https://www.rt-thread.org/document/site/#/rt-thread-version/rt-thread-standard/tutorial/beep-player/button)和[杰杰](https://github.com/jiejieTop/rtpkg_button)
