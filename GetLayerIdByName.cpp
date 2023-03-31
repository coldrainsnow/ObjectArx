		AcDbDatabase* pDb = acdbHostApplicationServices()->workingDatabase();
		AcDbLayerTable* pLayerTbl;
		pDb->getLayerTable(pLayerTbl, AcDb::kForRead);
		AcDbObjectId layerId;
		pLayerTbl->getAt(layerName, layerId);