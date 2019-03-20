
#include"../inc/debug.h"
#include"../inc/readconfig.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int config_string_get( char* configfile,char *_section, char *key,char* ret_buf)
{
    FILE  *fp            = NULL;
    char  buf[128];
    char  key_buf[128]  = {'\0'};
    char  section[128] = {'\0'};
    int len = 0;
    int i = 0;

    // 先对输入参数进行异常判断
    if (section == NULL || key == NULL ||  configfile == NULL)
    {
        DEBUG("GetConfigFileStringValue: input parameter(s) is NULL!\n");
        return 0;
    }
    if((fp = fopen(configfile,"r")) == NULL)
    {
        perror("open config file err");
        return 0;
    }
    sprintf(section, "[%s]", _section);
    while(feof(fp) == 0)
    {
        memset(buf,'\0',sizeof(buf)); //清空缓冲区
        fgets(buf,sizeof(buf),fp); //读取一行

        //过滤注释行，或以特殊字符开头的行
        if (buf[0] == '#' || buf[0] == '\r' || buf[0] == '\n' || buf[0] == '\0')
        {
            continue;
        }
        //匹配段名
        if (strncasecmp(section, buf, strlen(section)) ==0)
        {
            //匹配字段
            while(feof(fp) ==0)
            {
                memset(buf,'\0',sizeof(buf));
                fgets(buf,sizeof(buf),fp);
                if (buf[0] == '#' || buf[0] == '\r' || buf[0] == '\n' || buf[0] == '\0')
                {
                    continue;
                }
                if (strncasecmp(key, buf, strlen(key)) ==0) //忽略大小写
                {
                    //匹配字段成功
                    len = strlen(key);
                    //过滤多余字符
                    for(i=len;i<strlen(buf);i++)
                    {
                        if(buf[i] == '=')
                        {
                            break;
                        }
                    }
                    for(i=i+1;i<len;i++)
                    {
                        if(buf[i] == '\0')
                        {
                            continue;
                        }
                        else
                        {
                            break;
                        }
                    }
                    strcpy(ret_buf,buf+i);
                    return 0;
                }
            }
        }
    }
    fclose(fp);
    fp = NULL;
    memset(ret_buf,'\0',strlen(ret_buf));
    return -1;
}


int config_int_get( char* configfile,char *_section, char *key,int* ret_val)
{
    char buf[128];
    int ret = config_string_get(configfile,_section,key,buf);
    if(ret != 0)
        return ret;
    *ret_val = atoi(buf);
    return 0;
}


int config_float_get( char* configfile,char *_section, char *key,float* ret_val)
{
    char buf[128];
    int ret = config_string_get(configfile,_section,key,buf);
    if(ret != 0)
        return ret;
    *ret_val = atof(buf);
    return 0;
}
