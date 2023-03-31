		const wchar_t* layerName = L"0";
		//获取id
		AcDbDatabase* pDb = acdbHostApplicationServices()->workingDatabase();
		AcDbLayerTable* pLayerTbl;
		pDb->getLayerTable(pLayerTbl, AcDb::kForRead);

		AcDbObjectId layerId;
		if (pLayerTbl->getAt(layerName, layerId) == Acad::eOk)
		{
			AcDbLayerTableRecord* pLayerTableRecord = NULL;
			if (acdbOpenObject(pLayerTableRecord, layerId, AcDb::kForWrite) == Acad::eOk)
			{
				AcCmColor color;
				color.setColorIndex(1);
				pLayerTableRecord->setColor(color);
				pLayerTableRecord->close();
			}
			pLayerTableRecord->close();
		}
		pLayerTbl->close();