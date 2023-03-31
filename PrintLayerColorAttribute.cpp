		AcDbDatabase* pCurDb = acdbHostApplicationServices()->workingDatabase();

		// 获取当前图层 ID
		AcDbObjectId layerId = pCurDb->clayer();

		// 根据 ID 获取图层记录对象
		AcDbLayerTableRecord* pLayerRecord = nullptr;
		if (acdbOpenObject(pLayerRecord, layerId, AcDb::kForRead) == Acad::eOk)
		{
			// 获取图层的颜色属性
			AcCmColor layerColor = pLayerRecord->color();
			acutPrintf(_T("\nCurrent layer color: %d"), layerColor.colorIndex());

			// 关闭图层记录对象
			pLayerRecord->close();
		}
		else
		{
			acutPrintf(_T("\nFailed to get current layer record."));
		}