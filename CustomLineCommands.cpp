		AcGePoint3d ptStart(0, 0, 0);//创建一个3d空间的点
		AcGePoint3d ptEnd(100, 100, 0);

		AcDbLine* pLine = new AcDbLine(ptStart, ptEnd);//这个类代表了CAD里面的线实体，起始点终结点

		pLine->setColorIndex(1);

		//获取指向块表的指针
		AcDbBlockTable* pBlockTable;//声明指向块表的指针
		acdbHostApplicationServices()->workingDatabase()->getBlockTable(pBlockTable, AcDb::kForRead);//获取快表指针
		AcDbBlockTableRecord* pBlockTableRecord;// 声明一个块表记录区的指针
		pBlockTable->getAt(ACDB_MODEL_SPACE, pBlockTableRecord, AcDb::kForWrite);

		AcDbObjectId lineld;//声明ID
		pBlockTableRecord->appendAcDbEntity(lineld, pLine);//将ID与实体传入
		pBlockTable->close();
		pBlockTableRecord->close();
		pLine->close();