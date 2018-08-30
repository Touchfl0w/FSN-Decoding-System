

#include <iostream>
#include <stdio.h>
#include"stdafx.h"
#include<vector>
#include "guan.h"



    int OFFSET;
	std::vector<Money_Info> Vec_MoneyInfo;



void printout(char * tt,int longth){
	for(int i=0;i<longth;i++){
		cout<<tt[i];
	}
	cout<<"   ";
}




void* __cdecl memcpy(void* dst,const void* src,size_t count)
{
	void*ret = dst;
#if defined(_M_MRX000)||defined(_M_ALPHA)||defined(_M_PPC)
	{
		extern void RtlMoveMemory(void *, const void *, size_t count);
		RtlMoveMemory(dst, src, count);
	}
#else
	while (count--) {
		*(char *)dst = *(char *)src;
		dst = (char *)dst + 1;
		src = (char *)src + 1;
	}
#endif 
	return (ret);
}
//解析FSN文件
//BOC_TagData_Fromat *btf = (BOC_TagData_Fromat*)malloc(sizeof(BOC_TagData_Fromat*));
//int len = sizeof(BOC_TagData_Fromat*);
std::vector<Money_Info> FsnParser::ReadTk(CString &filename,int ncount)
{
	FILE *myf = fopen(filename, "rb");
	
	// struct{
    // int _fd;//文件号
    // int _cleft;//缓冲区所剩下的字符数
    // int _mode;//文件操作方式
   //  char* _next;//文件当前读写位置
    // char* _buff;//文件缓冲区位置
	// }FILE;
	if (myf == NULL)
	{
		cout << "Error opening file"; 
		exit(1);
	}

	char buffer[3072] = { 0 };
	int iread_offset = 0;
	iread_offset += sizeof(BOC_Header_Fromat);
	int read_size = READ_SIZE;							//文件记录
	int position = 0;
	 Vec_MoneyInfo.clear();
	fseek(myf, 0, 2);//?????????????????保留字1
	int fileSize = ftell(myf);                              //求文件的长度
	while(!feof(myf))  //判断文件是否结束
	{
		
		fseek(myf, iread_offset, SEEK_SET);
		position = ftell(myf);//头部长度
		fread(buffer, read_size, 1, myf);
/******************
     fread()函数用于从文件流中读取数据，其原型为：
     size_t  fread(void *buffer, size_t size, size_t count, FILE * stream);

 【参数】buffer为接收数据的地址，size为一个单元的大小，count为单元个数，stream为文件流。
 ***************************/

		iread_offset += READ_SIZE;
/************************
ireadoffset:文件头长度 readsize:100
*******************************************************/
		TKFSN_Record_File *pdata = (TKFSN_Record_File*)buffer;
		BOC_TagRecord_Data *bctd = new BOC_TagRecord_Data;				//数据标记记录
		memset(bctd, 0, sizeof(BOC_TagRecord_Data));
		bctd->btf.Date = pdata->u16_Date;
		bctd->btf.Time = pdata->u16_Time;
		bctd->btf.tfFlag = pdata->u16_tfFlag;
        bctd->btf.Valuta = pdata->u16_Valuta;
        bctd->btf.Ver = pdata->u16_Ver;
		memcpy(bctd->btf.ErrorCode, pdata->u16_ErrorCode, sizeof(bctd->btf.ErrorCode));
		memcpy(bctd->btf.MoneyFlag, pdata->u16_MoneyFlag, sizeof(bctd->btf.MoneyFlag));

		bctd->btf.CharNUM = pdata->u16_CharNum;
		memcpy(bctd->btf.SNo, pdata->u16_SNo, sizeof(bctd->btf.SNo));
		memcpy(bctd->btf.MachineSNo, pdata->u16_MachineSNo, sizeof(bctd->btf.MachineSNo));
		iread_offset += OFFSET;
		m_vecRecordData.push_back(bctd);
		ncount++;
		Money_Info m_info = InsList(m_vecRecordData, ncount-1);
		Vec_MoneyInfo.push_back(m_info);
	
	}

	
	fclose(myf);
	return Vec_MoneyInfo;
}
Money_Info  FsnParser::InsList(vector<BOC_TagRecord_Data*>& vecRecord, int nStartPos)
{
	int j = 0;

	unsigned char idLevel = 0;
	int nEndPos = vecRecord.size();
	Money_Info m_info;												//保存Money信息的数据结构
	for (int i = nStartPos; i < nEndPos; i++)
	{
		BOC_TagData_Fromat* pdata = &vecRecord[i]->btf;
		char tmpbuf[26];
		//SNo
		memset(tmpbuf, 0, 26);
/******************************************************
void *memset(void *s,int c,size_t n)
总的作用：将已开辟内存空间 s 的首 n 个字节的值设为值 c。

**************************************************/
		for (j = 0; j < 12; j++)
		{
			tmpbuf[j] = pdata->SNo[j] & 0xFF;
			std::cout << tmpbuf[j];
		}
		cout<<"   ";
		m_info.Id = tmpbuf;//
		//CharNum
		memset(tmpbuf, 0, 26);
		sprintf(tmpbuf, "%d", pdata->CharNUM);
		printout(tmpbuf,sizeof(pdata->CharNUM));
		m_info.CharNum = tmpbuf;//
		//面值
		memset(tmpbuf, 0, 26);
		sprintf(tmpbuf, "%d", pdata->Valuta);
        printout(tmpbuf,sizeof(pdata->Valuta));
		m_info.Value = tmpbuf; //
	    //版本
		memset(tmpbuf, 0, 26);
		sprintf(tmpbuf, "%d", pdata->Ver);
        if(!strcmp(tmpbuf,"0")){
		   m_info.Ver = "1990";
		}
		else if(!strcmp(tmpbuf,"3")){
                m_info.Ver = "1999";
		}
		else if(!strcmp(tmpbuf,"2")){
                m_info.Ver = "2005";
		}
		else{
			    m_info.Ver = "未知";
		}
		//
		//MomeyId 币种
		memset(tmpbuf, 0, 26);
		for (j = 0; j < 4; j++)
		{
			tmpbuf[j] = pdata->MoneyFlag[j] & 0xFF;
		}
        printout(tmpbuf,4);
		if(!strcmp(tmpbuf,"CNY")){
			m_info.Kinds = "人民币"; 
		}
		else{
			m_info.Kinds = "未知币种";
		}//
		//真伪
		memset(tmpbuf, 0, 26);
		sprintf(tmpbuf, "%d", pdata->tfFlag);
printout(tmpbuf,10);
		if(!strcmp(tmpbuf,"0")){
		   m_info.IsReal = "假币";
		}
		else if(!strcmp(tmpbuf,"1")){
                m_info.IsReal = "真币";
		}
		else if(!strcmp(tmpbuf,"2")){
                m_info.IsReal = "残币";
		}
		else{
			    m_info.IsReal = "未知";
		}
		//错误码
		memset(tmpbuf, 0, 26);
		idLevel = (pdata->ErrorCode[1] >> 8);
		//机具编号
		memset(tmpbuf, 0, 26);
		for (j = 0; j < 24; j++)
		{
			tmpbuf[j] = pdata->MachineSNo[j] & 0xFF;
			std::cout << tmpbuf[j];
		}
		m_info.MachineSNo = tmpbuf;//
		//时间戳
		memset(tmpbuf, 0, 26);
		sprintf(tmpbuf, "%04d-%02d-%02d %02d:%02d:%02d", (pdata->Date >> 9) + 1980, (pdata->Date >> 5) & 0x0F, pdata->Date & 0x1F,
			(pdata->Time >> 11), (pdata->Time >> 5) & 0x3F, (pdata->Time << 1) & 0x3F);
printout(tmpbuf,24);
		m_info.time = tmpbuf;//
		return m_info;
	}
}