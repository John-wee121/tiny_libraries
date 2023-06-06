# tl_timer

## 1、介绍

这是一个软件定时器的实现。

### 1.1 目录结构

| 名称 | 说明 |
| ---- | ---- |
| docs  | 文档目录 |
| examples | 例子目录，并有相应的一些说明 |
| inc  | 头文件目录 |
| src  | 源代码目录 |
| port | 移植代码目录。如果没有移植代码，可以不需要 |

### 1.2 许可证

tl_timer 遵循 Apache license v2.0 许可，详见 `LICENSE` 文件。

### 1.3 依赖

- 依赖底层定时器。

## 2、如何打开 tl_timer

使用 tl_timer 可以在 tl_config_tool.exe ([1] Enter config) 的包管理器中选择它，具体路径如下：

```
Tiny Libraries Kconfig
    Timer --->
        [*] Using Timer
        [ ]     Using Timer Example
```

然后让 tl_config_tool.exe ([2] Up to config) 的包管理器更新。

## 3、使用 tl_timer

> 说明：在这里介绍 package 的移植步骤、使用方法、初始化流程、准备工作、API 等等，如果移植或 API 文档内容较多，可以将其独立至 `docs` 目录下。

在打开 tl_timer 后，当进行编译时，它会被加入到工程中进行编译。

* 完整的 API 手册可以访问这个[链接](docs/api.md)
* 更多文档位于 [`/docs`](./docs) 下，使用前 **务必查看**

## 4、注意事项

> 说明：列出在使用这个 package 过程中需要注意的事项；列出常见的问题，以及解决办法。

## 5、联系方式 & 感谢

* 维护：JohnWay(wlx)
* 主页：https://github.com/John-wee121/tiny_libraries/tree/master/tl_timer
* 感谢：RT-Thread