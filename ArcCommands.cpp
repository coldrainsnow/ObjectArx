		// 设置圆弧参数
		AcGePoint3d center(0, 0, 0);
		double radius = 5;
		double startAngle = 0.0;
		double endAngle = 90.0;

		// 创建一个新的圆弧对象
		AcDbArc* pArc = new AcDbArc(center, AcGeVector3d::kZAxis, radius, startAngle, endAngle);

		// 将圆弧对象添加到当前空间中
		AcDbBlockTable* pBlockTable;
		acdbHostApplicationServices()->workingDatabase()->getBlockTable(pBlockTable, AcDb::kForRead);

		AcDbBlockTableRecord* pBlockTableRecord = nullptr;
		pBlockTable->getAt(ACDB_MODEL_SPACE, pBlockTableRecord, AcDb::kForWrite);

		AcDbObjectId lineId;//声明ID
		pBlockTableRecord->appendAcDbEntity(lineId, pArc);//将ID与实体传入
		pBlockTable->close();
		pBlockTableRecord->close();
		pArc->close();