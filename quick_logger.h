#ifndef _QUICK_LOGGER_H_
#define _QUICK_LOGGER_H_

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <list>
#include <string>
#include <stdio.h>
#include <stdlib.h>

#include "log_user.h"

using namespace std;


#define MESSAGE_TYPE				300356			//��֪��дɶ����д��˾��Ʊ�����
#define LOG_MESSAGE_QUEUE_KEY		300356			//��־��Ϣ����KEY
#define LOG_SWITCH_BYTE				1024 * 128		//��־�л�����ֽ���  
#define MAX_NORMAL_ZIP_LOGS_ON_DISK	50				//��ͨ��־ѹ������������
#define MAX_ERROR_ZIP_LOGS_ON_DISK	5				//������־ѹ������������
#define MAX_LOG_CACHE_COUNT			50				//��ͨ��־��󻺴�������������ֵ��д��FLASH
#define MAX_LOG_POOL_BYTES			512				//��־�������󻺴���������ֹ����־���Ⱥܳ����������������࣬����һֱ��д���ļ�������
#define MAX_LOG_DIR_SPACE			1024*1024*10	//��־Ŀ¼�������ռ䣬���ڷ�����������ʱ�������ն˴洢�ռ䲻�ᱻռ��


#define LOG_ROOT_PATH		"/mnt/hgfs/Develop/Study/QuickLogger/log/"		//��־Ŀ¼
//#define LOG_ROOT_PATH		"/mnt/user/LOG/"		//��־Ŀ¼
#define ERR_SN				"sn-error-record.txt"	//������־������ļ�
#define NORMAL_SN			"sn-normal-record.txt"	//һ����־������ļ�

#define BCD2DEC(x)	(((x)&0x0F)+((x)>>4)*10)
#define DEC2BCD(x)	((((x)/10)<<4)+(x)%10)

typedef struct _ST_LOG_HEADER
{
	long			message_type;	/* ��Ϣ����Ԥ���������� */
	unsigned int	sender;			/* �����ߵ�pid */
	unsigned int	type;			/* ��Ϣ���� */
	unsigned int	level;			/* ��Ϣ�ȼ� */
	unsigned int	length;			/* DATA����ֽ��� */
}ST_LOGHEADER;

typedef struct _ST_MESSAGE
{
	long msg_type;							/* ��Ϣ��ʶ�� */
	char msg_text[10240 - sizeof(long)];	/* ��Ϣ���� */
}ST_MESSAGE;

int LogSend(LOG_TYPE log_type, LOG_LEVEL log_level, const char* pSendBuff, unsigned short nSendBuffLen);
int GetFirstKeyPosition(const char* pStr, char nKey);

class LogManager {
public:
	static LogManager& GetInstance();
	unsigned int ReadCurrentLogSn(LOG_LEVEL log_level);
	unsigned int WriteCurrentLogSn(LOG_LEVEL log_level, unsigned int log_sn);

public:
	list<string> m_logs_pool;				//��־�����
	pthread_mutex_t m_logs_pool_lock;		//��־�������
	unsigned int m_logs_pool_total_len;		//��־��������ֽ��ܳ���

	unsigned int m_logs_current_normal_sn;	//��ǰ��ͨ��־sn����ţ�
	unsigned int m_logs_current_error_sn;	//��ǰ������־sn����ţ�
	unsigned int m_logs_normal_written_byte;//��ǰ��ͨ��־д���ļ��ֽ�ƫ��
	unsigned int m_logs_error_written_byte;	//��ǰ������־д���ļ��ֽ�ƫ��

	bool m_logs_sync_flag;					//log����ͬ����־
	bool m_logs_zipped_flag;				//log��ѹ����־��0δѹ�� 1 ��ѹ��  

	int LogAppend(LOG_LEVEL log_level, const char* send_buff);
	int LogCompress(LOG_LEVEL log_level, unsigned int sn);
	int LogWrite();
	int LogSwitch();
	int LogClean();

private:
	LogManager();
	LogManager(const LogManager&);
	LogManager& operator= (const LogManager&);
private:
	static LogManager * m_log_manage_instance;
};



#endif // !_QUICK_LOGGER_H_