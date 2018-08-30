

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
//����FSN�ļ�
//BOC_TagData_Fromat *btf = (BOC_TagData_Fromat*)malloc(sizeof(BOC_TagData_Fromat*));
//int len = sizeof(BOC_TagData_Fromat*);
std::vector<Money_Info> FsnParser::ReadTk(CString &filename,int ncount)
{
	FILE *myf = fopen(filename, "rb");
	
	// struct{
    // int _fd;//�ļ���
    // int _cleft;//��������ʣ�µ��ַ���
    // int _mode;//�ļ�������ʽ
   //  char* _next;//�ļ���ǰ��дλ��
    // char* _buff;//�ļ�������λ��
	// }FILE;
	if (myf == NULL)
	{
		cout << "Error opening file"; 
		exit(1);
	}

	char buffer[3072] = { 0 };
	int iread_offset = 0;
	iread_offset += sizeof(BOC_Header_Fromat);
	int read_size = READ_SIZE;							//�ļ���¼
	int position = 0;
	 Vec_MoneyInfo.clear();
	fseek(myf, 0, 2);//?????????????????������1
	int fileSize = ftell(myf);                              //���ļ��ĳ���
	while(!feof(myf))  //�ж��ļ��Ƿ����
	{
		
		fseek(myf, iread_offset, SEEK_SET);
		position = ftell(myf);//ͷ������
		fread(buffer, read_size, 1, myf);
/******************
     fread()�������ڴ��ļ����ж�ȡ���ݣ���ԭ��Ϊ��
     size_t  fread(void *buffer, size_t size, size_t count, FILE * stream);

 ��������bufferΪ�������ݵĵ�ַ��sizeΪһ����Ԫ�Ĵ�С��countΪ��Ԫ������streamΪ�ļ�����
 ***************************/

		iread_offset += READ_SIZE;
/************************
ireadoffset:�ļ�ͷ���� readsize:100
*******************************************************/
		TKFSN_Record_File *pdata = (TKFSN_Record_File*)buffer;
		BOC_TagRecord_Data *bctd = new BOC_TagRecord_Data;				//���ݱ�Ǽ�¼
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
	Money_Info m_info;												//����Money��Ϣ�����ݽṹ
	for (int i = nStartPos; i < nEndPos; i++)
	{
		BOC_TagData_Fromat* pdata = &vecRecord[i]->btf;
		char tmpbuf[26];
		//SNo
		memset(tmpbuf, 0, 26);
/******************************************************
void *memset(void *s,int c,size_t n)
�ܵ����ã����ѿ����ڴ�ռ� s ���� n ���ֽڵ�ֵ��Ϊֵ c��

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
		//��ֵ
		memset(tmpbuf, 0, 26);
		sprintf(tmpbuf, "%d", pdata->Valuta);
        printout(tmpbuf,sizeof(pdata->Valuta));
		m_info.Value = tmpbuf; //
	    //�汾
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
			    m_info.Ver = "δ֪";
		}
		//
		//MomeyId ����
		memset(tmpbuf, 0, 26);
		for (j = 0; j < 4; j++)
		{
			tmpbuf[j] = pdata->MoneyFlag[j] & 0xFF;
		}
        printout(tmpbuf,4);
		if(!strcmp(tmpbuf,"CNY")){
			m_info.Kinds = "�����"; 
		}
		else{
			m_info.Kinds = "δ֪����";
		}//
		//��α
		memset(tmpbuf, 0, 26);
		sprintf(tmpbuf, "%d", pdata->tfFlag);
printout(tmpbuf,10);
		if(!strcmp(tmpbuf,"0")){
		   m_info.IsReal = "�ٱ�";
		}
		else if(!strcmp(tmpbuf,"1")){
                m_info.IsReal = "���";
		}
		else if(!strcmp(tmpbuf,"2")){
                m_info.IsReal = "�б�";
		}
		else{
			    m_info.IsReal = "δ֪";
		}
		//������
		memset(tmpbuf, 0, 26);
		idLevel = (pdata->ErrorCode[1] >> 8);
		//���߱��
		memset(tmpbuf, 0, 26);
		for (j = 0; j < 24; j++)
		{
			tmpbuf[j] = pdata->MachineSNo[j] & 0xFF;
			std::cout << tmpbuf[j];
		}
		m_info.MachineSNo = tmpbuf;//
		//ʱ���
		memset(tmpbuf, 0, 26);
		sprintf(tmpbuf, "%04d-%02d-%02d %02d:%02d:%02d", (pdata->Date >> 9) + 1980, (pdata->Date >> 5) & 0x0F, pdata->Date & 0x1F,
			(pdata->Time >> 11), (pdata->Time >> 5) & 0x3F, (pdata->Time << 1) & 0x3F);
printout(tmpbuf,24);
		m_info.time = tmpbuf;//
		return m_info;
	}
}