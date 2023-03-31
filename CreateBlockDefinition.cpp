	AcDbBlockTable *pBlockTable=NULL;
	acdbHostApplicationServices()->workingDatabase()->getBlockTable(pBlockTable,AcDb::kForWrite);

	AcDbBlockTableRecord *pBlockTableRecord = new AcDbBlockTableRecord();
	TCHAR BlockName[40];
	if (acedGetString(Adesk::kFalse,_T("\n输入图块的名称:"),BlockName)!=RTNORM)
	{
		pBlockTable->close();
		delete pBlockTableRecord;
		return;
	}
	pBlockTableRecord->setName(BlockName);
	AcDbObjectId BlockDefineid;
	pBlockTable->add(BlockDefineid, pBlockTableRecord);
	pBlockTable->close();

	AcGePoint3d p1(-10, 0, 0);
	AcGePoint3d p2(10, 0, 0);
	AcDbLine *pLine1 = new AcDbLine(p1, p2);
	p1.set(0, 10, 0);
	p2.set(0, -10, 0);
	AcDbLine *pLine2 = new AcDbLine(p1, p2);

	AcGeVector3d ver(0, 0, 1);
	AcDbCircle *pCircle = new AcDbCircle(AcGePoint3d::kOrigin, ver, 6);

	AcDbAttributeDefinition *pAttributeName = new AcDbAttributeDefinition(p1, _T("准星"), _T("名称："), _T("部件名称"));
	AcDbAttributeDefinition *pAttributeDiametion = new AcDbAttributeDefinition(p2, _T("12"), _T("圆心直径"), _T("准星圆心直径"));

	pBlockTableRecord->appendAcDbEntity(pLine1);
	pBlockTableRecord->appendAcDbEntity(pLine2);
	pBlockTableRecord->appendAcDbEntity(pCircle);
	pBlockTableRecord->appendAcDbEntity(pAttributeDiametion);
	pBlockTableRecord->appendAcDbEntity(pAttributeName);

	pBlockTableRecord->close();
	pLine1->close();
	pLine2->close();
	pCircle->close();
	pAttributeDiametion->close();
	pAttributeName->close();

	return;