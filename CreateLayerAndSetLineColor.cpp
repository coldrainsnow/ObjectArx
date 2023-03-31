		// 定义新图层的变量
		const wchar_t* layerName = L"NewLayer";
		AcCmColor layerColor;
		layerColor.setColorIndex(1);

		// 获取当前数据库
		AcDbDatabase* pDatabase = acdbHostApplicationServices()->workingDatabase();

		// 获取图层表
		AcDbLayerTable* pLayerTable;
		acdbOpenObject(pLayerTable, pDatabase->layerTableId(), AcDb::kForWrite);

		// 检查图层是否已存在
		AcDbObjectId layerId;
		if (pLayerTable->has(layerName)) {
			// 图层已存在，返回错误消息
			acutPrintf(L"Layer %ls already exists.\n", layerName);
			return;
		}
		else {
			// 图层不存在，创建新的图层记录
			AcDbLayerTableRecord* pLayerRecord = new AcDbLayerTableRecord;
			pLayerRecord->setName(layerName);
			pLayerRecord->setColor(layerColor);

			// 添加图层记录到图层表中
			pLayerTable->add(pLayerRecord);
			acutPrintf(L"New layer %ls created successfully.\n", layerName);

			// 释放内存
			pLayerRecord->close();
		}
		// 释放内存
		pLayerTable->close();


		ads_name entSel;
		ads_point pt;
		int result = acedEntSel(L"\nSelect a line: ", entSel, pt);

		// 打开并锁定被选择的对象
		AcDbObjectId objId;
		AcDbEntity* pEnt;
		acdbGetObjectId(objId, entSel);
		acdbOpenAcDbEntity(pEnt, objId, AcDb::kForWrite);

		if (pEnt->isKindOf(AcDbLine::desc())) {
			// 选中实体是直线
			AcDbLine* pLine = AcDbLine::cast(pEnt);

			// pLine 变量包含选定的直线对象
			AcCmColor lineColor = pLine->color();
			// 将图层颜色应用到直线
			pLine->setColor(layerColor);

			// 更改完成后关闭对象
			pLine->close();
		}
		else {
			// 选中实体不是直线
			acutPrintf(L"The selected entity is not a line.\n");
		}

		// 关闭对象
		pEnt->close();