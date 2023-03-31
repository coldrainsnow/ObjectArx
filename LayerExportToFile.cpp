		const char* filePath = "D:\\LayerInfo.txt";
		// 打开文件
		FILE* pFile;
		if ((pFile = fopen(filePath, "w")) == NULL)
		{
			acutPrintf(L"\n无法打开文件 \"%s\" 进行写入操作！", filePath);
			return;
		}

		// 获取当前文档数据库指针
		AcDbDatabase* pDb = acdbHostApplicationServices()->workingDatabase();

		AcDbLayerTable* pLayerTbl;
		acdbHostApplicationServices()->workingDatabase()->getLayerTable(pLayerTbl, AcDb::kForRead);
		// 遍历所有图层
		AcDbLayerTableIterator* pLayerIterator = nullptr;
		Acad::ErrorStatus es = pLayerTbl->newIterator(pLayerIterator);
		if (es == Acad::eOk && pLayerIterator != NULL)
		{
			for (pLayerIterator->start(); !pLayerIterator->done(); pLayerIterator->step())
			{
				// 获取图层对象指针
				AcDbLayerTableRecord* pLayerRecord = NULL;
				if (pLayerIterator->getRecord(pLayerRecord, AcDb::kForRead) != Acad::eOk)
				{
					continue;
				}
				// 输出图层属性到文件
				ACHAR* layerName;
				pLayerRecord->getName(layerName);
				fprintf(pFile, "图层名称：%ls\n", layerName);
				fprintf(pFile, "颜色：%d\n", pLayerRecord->color().colorIndex());
				//
				AcDbLinetypeTableRecord* pLinetypeTblRcd;
				acdbOpenObject(pLinetypeTblRcd, pLayerRecord->linetypeObjectId(),
					AcDb::kForRead);
				ACHAR* linetypeName;
				pLinetypeTblRcd->getName(linetypeName);
				fprintf(pFile, "线型：%ls\n", linetypeName);
				
				fprintf(pFile, "线宽：%d\n\n", pLayerRecord->lineWeight());

				// 关闭图层读取
				pLayerRecord->close();
				pLinetypeTblRcd->close();
			}
		}
		// 释放图层表对象
		if (pLayerTbl != NULL)
		{
			pLayerTbl->close();
		}
		
		// 关闭文件
		fclose(pFile);

		// 释放迭代器
		delete pLayerIterator;