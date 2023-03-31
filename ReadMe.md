此项目为本人在进行ObjectArx练习时的总结

# 参考项目

[lysjq/AutoCAD-ObjectArx: AutoCAD-ObjectARX最常用功能封装，便于日常调用 (github.com)](https://github.com/lysjq/AutoCAD-ObjectArx)



# 实现功能

以下所有示例代码，均在一个自定义的无返回值，无参数的函数中，格式如下

```C++
static void CMDTEST()
{
    example code
}
```

| 绘图               | 对应文件               |
| ------------------ | ---------------------- |
| 自定义两点创建直线 | CustomLineCommands.cpp |
| 圆                 | CircleCommands.cpp     |
| 多段线             | PolylineCommands.cpp   |

| 图层                                                         | 对应文件                       |
| ------------------------------------------------------------ | ------------------------------ |
| 新建图层以及选中一条直线，将直线的图层颜色赋值               | CreateLayerAndSetLineColor.cpp |
| 将某一图层的颜色赋值                                         | SetLayerColor.cpp              |
| 获取图层中的颜色属性并输出                                   | PrintLayerColorAttribute.cpp   |
| 删除名字为myLayer的图层                                      | DeleteSpecificLayer.cpp        |
| 获取一个图层名的ID(可以写成函数)                             | GetLayerIdByName.cpp           |
| 定义图层，并且查看他的id                                     | LayerDefinitionAndIdViewer.cpp |
| 将当前图纸中存在的所有图层及其特性(图层名称、颜色、图层线型、图层线宽等)导出到指定的文本文件中 | LayerExportToFile.cpp          |
| 按照指定文本文件中的图层列表属性(图层名称、颜色、图层线型、图层线宽等)在当前图形中创建图层 （获取到的中文名称乱码，目前有bug） | LayerImporter.cpp              |

| 块         | 对应文件                  |
| ---------- | ------------------------- |
| 新增块定义 | CreateBlockDefinition.cpp |



