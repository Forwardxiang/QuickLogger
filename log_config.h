#ifndef _LOG_CONFIG_H_
#define _LOG_CONFIG_H_

#define MESSAGE_TYPE				300356			//��֪��дɶ����д��˾��Ʊ�����
#define LOG_MESSAGE_QUEUE_KEY		300356			//��־��Ϣ����KEY
#define LOG_SWITCH_BYTE				1024 * 128		//��־�л�����ֽ���  
#define MAX_NORMAL_ZIP_LOGS_ON_DISK	50				//��ͨ��־ѹ������������
#define MAX_ERROR_ZIP_LOGS_ON_DISK	5				//������־ѹ������������
#define MAX_LOG_CACHE_COUNT			50				//��ͨ��־��󻺴�������������ֵ��д��FLASH
#define MAX_LOG_DIR_SPACE			1024*1024*10	//��־Ŀ¼�������ռ䣬���ڷ�����������ʱ�������ն˴洢�ռ䲻�ᱻռ��


//#define LOG_ROOT_PATH		"/mnt/hgfs/Develop/Study/QuickLogger/log/"		//��־Ŀ¼
#define LOG_ROOT_PATH		"/mnt/user/LOG/"		//��־Ŀ¼
#define ERR_SN				"sn-error-record.txt"	//������־������ļ�
#define NORMAL_SN			"sn-normal-record.txt"	//һ����־������ļ�

	



#endif // !_LOG_CONFIG_H_