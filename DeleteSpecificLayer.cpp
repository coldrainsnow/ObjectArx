		const wchar_t* layerName = L"myLayer";

		// 获取一个图层名的ID
		AcDbDatabase* pDb = acdbHostApplicationServices()->workingDatabase();
		AcDbLayerTable* pLayerTbl;
		pDb->getLayerTable(pLayerTbl, AcDb::kForRead);
		AcDbObjectId layerId;
		pLayerTbl->getAt(layerName, layerId);

		// 
		AcDbLayerTableRecord* pLayerTableRecord = nullptr;
		if (acdbOpenObject(pLayerTableRecord, layerId, AcDb::kForWrite) == Acad::eOk)
		{
			pLayerTableRecord->erase();
			pLayerTableRecord->close();
			acutPrintf(L"delete successful");
		}