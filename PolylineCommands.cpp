		// 定义多段线的顶点，共有五个顶点
		AcGePoint2dArray points;
		points.append(AcGePoint2d(0, 0));
		points.append(AcGePoint2d(1, 1));
		points.append(AcGePoint2d(2, 1));
		points.append(AcGePoint2d(3, 3));
		points.append(AcGePoint2d(2, 2));

		// 创建一个新的多段线对象
		AcDbPolyline* pPline = new AcDbPolyline();

		// 为多段线对象设置顶点
		for (int i = 0; i < points.length(); i++)
		{
			pPline->addVertexAt(i, points[i], 0.0);
		}

		// 将多段线对象添加到当前的空间中
		AcDbBlockTable* pBlockTable = nullptr;
		acdbHostApplicationServices()->workingDatabase()->getBlockTable(pBlockTable, AcDb::kForRead);

		AcDbBlockTableRecord* pBlockTableRecord = nullptr;
		pBlockTable->getAt(ACDB_MODEL_SPACE, pBlockTableRecord, AcDb::kForWrite);

		AcDbObjectId lineld;//声明ID
		pBlockTableRecord->appendAcDbEntity(lineld, pPline);
		pBlockTable->close();
		pBlockTableRecord->close();
		pPline->close();