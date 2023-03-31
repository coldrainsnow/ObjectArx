This project is a summary of my ObjectArx practice

[中文]([wozhuyinghao/ObjectArx (github.com)](https://github.com/wozhuyinghao/ObjectArx#readme_cn))

# Reference project

[lysjq/AutoCAD-ObjectArx: AutoCAD-ObjectARX最常用功能封装，便于日常调用 (github.com)](https://github.com/lysjq/AutoCAD-ObjectArx)



# Realize function

All the following sample codes are in a custom function with no return value and no parameters, and the format is as follows

```C++
static void CMDTEST()
{
    example code
}
```

| Drawing                          | Associated Files       |
| -------------------------------- | ---------------------- |
| Customize a line with two points | CustomLineCommands.cpp |
| Circle                           | CircleCommands.cpp     |
| Polyline                         | PolylineCommands.cpp   |

| Layer                                                        | Associated Files               |
| ------------------------------------------------------------ | ------------------------------ |
| Create a new layer and assign the color to a straight line   | CreateLayerAndSetLineColor.cpp |
| Assign a color to a specific layer                           | SetLayerColor.cpp              |
| Get the color attribute in a layer and output it             | PrintLayerColorAttribute.cpp   |
| Delete a layer named "myLayer"                               | DeleteSpecificLayer.cpp        |
| Get the ID of a layer name (can be written as a function)    | GetLayerIdByName.cpp           |
| Define a layer and view its ID                               | LayerDefinitionAndIdViewer.cpp |
| Export all layers in the current drawing and their attributes (layer name, color, layer line type, layer line width, etc.) to a specified text file | LayerExportToFile.cpp          |
| Create layers with the properties (layer name, color, layer line type, layer line width, etc.) listed in the specified text file in the current drawing (The Chinese name obtained is garbled, currently has a bug) | LayerImporter.cpp              |

| Block                         | Associated Files          |
| ----------------------------- | ------------------------- |
| Create a new block definition | CreateBlockDefinition.cpp |



