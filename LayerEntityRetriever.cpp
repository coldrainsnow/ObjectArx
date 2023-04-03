		// 获得当前图层 ID
		AcDbObjectId curLayerId = acdbHostApplicationServices()->workingDatabase()->clayer();

		// 打开包含当前图层的 AcDbBlockTableRecord 对象
		AcDbBlockTable* pBlockTable = nullptr;
		acdbHostApplicationServices()->workingDatabase()->getBlockTable(pBlockTable, AcDb::kForRead);
		AcDbBlockTableRecord* pCurBlockBlkTblRec = nullptr;
		pBlockTable->getAt(ACDB_MODEL_SPACE, pCurBlockBlkTblRec, AcDb::kForWrite);


		// 创建该图层所有实体的迭代器
		AcDbBlockTableRecordIterator* iter = nullptr;
		if (pCurBlockBlkTblRec->newIterator(iter) != Acad::eOk)
		{
			acutPrintf(L"Failed to create iterator.\n");
			pBlockTable->close();
			pCurBlockBlkTblRec->close();
			return;
		}

		// 循环遍历该图层的实体，对每个实体进行操作
		for (; !iter->done(); iter->step())
		{
			AcDbEntity* pEntity = nullptr;
			if (iter->getEntity(pEntity, AcDb::kForRead) != Acad::eOk)
			{
				continue;
			}
			
			if (curLayerId == pEntity->layerId())
			{
				acutPrintf(L"successful");
			}
			// 在该实体上执行操作，例如获得实体类型，实体包围盒等。
			// 释放每个实体的指针以及实体的内存
			// 获取实体类型
			acutPrintf(L"Entity type: %s\n", pEntity->isA()->name());

			// 获取实体包围盒
			AcDbExtents ext;
			pEntity->getGeomExtents(ext); // 在实体对象上调用 getGeomExtents 函数，就可以获取实体的包围盒
			acutPrintf(L"Entity extents: (%lf, %lf, %lf) - (%lf, %lf, %lf)\n", ext.minPoint().x, ext.minPoint().y, ext.minPoint().z, ext.maxPoint().x, ext.maxPoint().y, ext.maxPoint().z);

			pEntity->close();
		}

		// 释放AcDbBlockTableRecordIterator的指针以及 pCurLayerBlkTblRec 和 pBlockTable 的指针
		delete iter;
		pCurBlockBlkTblRec->close();
		pBlockTable->close();