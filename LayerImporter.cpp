		const char* filePath = "D:\LayerInfo.txt";
		// 打开文件
		FILE* pFile;
		if ((pFile = fopen(filePath, "r")) == NULL)
		{
			acutPrintf(L"\n无法打开文件%s进行读取操作！", filePath);
			return;
		}

		// 获取当前文档数据库指针和当前空间块ID
		AcDbDatabase* pDb = acdbHostApplicationServices()->workingDatabase();
		AcDbObjectId spaceId = acdbHostApplicationServices()->workingDatabase()->currentSpaceId();

		char line[256];
		while (fgets(line, sizeof(line), pFile)) // 逐行读取文本文件中的内容
		{
			if (strstr(line, "图层名称：") != NULL) // 判断是否为图层名称
			{
				char* layerName = &line[strlen("图层名称：")];
				// 在这里将Name乱码进行转换
				layerName[strlen(layerName) - 1] = '\0'; // 去掉换行符
				AcDbLayerTable* pLayerTbl;
				acdbHostApplicationServices()->workingDatabase()->getLayerTable(pLayerTbl, AcDb::kForRead);
				AcDbLayerTableRecord* pLayerRcd = new AcDbLayerTableRecord();
				const ACHAR* layerNameAchar = reinterpret_cast<const ACHAR*>(reinterpret_cast<const unsigned short*>(layerName));
				pLayerRcd->setName(layerNameAchar);

				// 获取颜色，线型和线宽
				fgets(line, sizeof(line), pFile); // 读取颜色
				int colorIdx = atoi(&line[strlen("颜色：")]);

				fgets(line, sizeof(line), pFile); // 读取线型
				char* linetypeName = &line[strlen("线型：")];
				linetypeName[strlen(linetypeName) - 1] = '\0'; // 去掉换行符

				fgets(line, sizeof(line), pFile); // 读取线宽
				int lineweight = atoi(&line[strlen("线宽：")]);

				// 设置颜色，线型和线宽
				AcCmColor layerColor;
				layerColor.setColorIndex(colorIdx);
				pLayerRcd->setColor(layerColor);
				AcDbLinetypeTable* pLinetypeTbl;
				acdbHostApplicationServices()->workingDatabase()->getLinetypeTable(pLinetypeTbl, AcDb::kForRead);
				AcDbLinetypeTableRecord* pLayertypeRcd = new AcDbLinetypeTableRecord();
				const ACHAR* layertypeNameAchar = reinterpret_cast<const ACHAR*>(reinterpret_cast<const unsigned short*>(linetypeName));
				pLayertypeRcd->setName(layertypeNameAchar);

				AcDbObjectId linetypeId;
				if (pLinetypeTbl->getAt(layertypeNameAchar, linetypeId) == Acad::eOk)
				{
					AcDbLinetypeTableRecord* pLinetypeRcd;
					acdbOpenObject(pLinetypeRcd, linetypeId, AcDb::kForRead);
					pLayerRcd->setLinetypeObjectId(linetypeId);
					pLinetypeRcd->close();
				}
				pLinetypeTbl->close();

				pLayerRcd->setLineWeight((AcDb::LineWeight)lineweight);

				// 添加图层
				AcDbObjectId layerId;
				if (pLayerTbl->has(layerNameAchar)) // 图层已存在
				{
					pLayerTbl->getAt(layerNameAchar, layerId, AcDb::kForRead);
					pLayerRcd->erase(); // 删除新建的空图层记录
					pLayerTbl->close();
				}
				else // 新建图层
				{
					pLayerTbl->upgradeOpen();
					pLayerTbl->add(pLayerRcd);
					pLayerTbl->close();
					layerId = pLayerRcd->objectId();
					pLayerRcd->close();
				}

				// 修改当前空间块的图层属性，未完成
				AcDbBlockTableRecord* pSpaceRcd;
				acdbOpenObject(pSpaceRcd, spaceId, AcDb::kForWrite);
				//pSpaceRcd->setLayer(layerId);
				pSpaceRcd->close();
				//pEnt->close();
			}
		}