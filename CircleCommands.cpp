		AfxMessageBox(_T("测试!"));

		//"圆心、半径"方法画圆
		AcGePoint3d ptCenter(100, 100, 0);
		AcGeVector3d vec(0, 0, 1);
		double radius = 20;
		AcDbCircle* pCircle = new AcDbCircle(ptCenter, vec, radius);
		//将实体添加到图形数据库中
		AcDbObjectId circleId;

		AcDbBlockTable* pBlockTable;
		acdbHostApplicationServices()->workingDatabase()->getBlockTable(pBlockTable, AcDb::kForRead);

		AcDbBlockTableRecord* pBlockTableRecord;
		pBlockTable->getAt(ACDB_MODEL_SPACE, pBlockTableRecord,AcDb::kForWrite);

		AcDbObjectId entId;
		pBlockTableRecord->appendAcDbEntity(entId, pCircle);

		pBlockTable->close();
		pBlockTableRecord->close();
		pCircle->close();

		circleId = entId;