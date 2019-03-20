
#ifndef _READCONFIG_H_
#define _READCONFIG_H_


int config_string_get( char *configfile,char *section, char *key,char* ret_buf);

int config_int_get( char* configfile,char *_section, char *key,int* ret_val);

int config_float_get( char* configfile,char *_section, char *key,float* ret_val);

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef __cplusplus
}
#endif

#endif //READCONFIG_H
