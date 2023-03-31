		// 定义要创建的图层名称和颜色
		const wchar_t* layerName = L"MyLayer";
		AcCmColor layerColor;
		layerColor.setColorIndex(1);

		AcDbDatabase* pDatabase = acdbHostApplicationServices()->workingDatabase();

		// 检查图层是否已存在，如存在则直接返回图层 ID
		AcDbObjectId layerId = AcDbObjectId::kNull;
		AcDbLayerTable* pExistingLayerTable = nullptr;
		if (pDatabase->getLayerTable(pExistingLayerTable, AcDb::kForRead) == Acad::eOk)
		{
			if (pExistingLayerTable->has(layerName))
			{
				pExistingLayerTable->getAt(layerName, layerId);
				pExistingLayerTable->close();
				acutPrintf(L"Layer %ls already exists.\n", layerName);
				return;
			}
			pExistingLayerTable->close();
		}

		// 图层不存在，创建新的图层记录
		AcDbLayerTableRecord* pLayerRecord = new AcDbLayerTableRecord;
		pLayerRecord->setName(layerName);
		pLayerRecord->setColor(layerColor);

		// 添加图层记录到图层表中
		AcDbLayerTable* pLayerTable = nullptr;
		if (pDatabase->getLayerTable(pLayerTable, AcDb::kForWrite) == Acad::eOk)
		{
			pLayerTable->add(pLayerRecord);
			pLayerTable->close();
		}

		// 获取新创建图层的 ID
		if (pDatabase->getLayerTable(pExistingLayerTable, AcDb::kForRead) == Acad::eOk)
		{
			if (pExistingLayerTable->has(layerName))
			{
				pExistingLayerTable->getAt(layerName, layerId);
				pExistingLayerTable->close();
				acutPrintf(L"New layer %ls created successfully, ID is %d.\n", layerName, layerId);
			}
			pExistingLayerTable->close();
		}

		// 释放内存
		pLayerRecord->close();