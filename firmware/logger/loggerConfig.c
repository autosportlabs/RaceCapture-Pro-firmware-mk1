#include "loggerConfig.h"
#include "string.h"
#include "memory.h"
#include "AT91SAM7S256.h"
#include "Board.h"



struct LoggerConfig g_savedLoggerConfig __attribute__ ((aligned (128))) __attribute__((section(".text\n\t#"))) = DEFAULT_LOGGER_CONFIG;
struct LoggerConfig g_workingLoggerConfig;

void updateActiveLoggerConfig(){
	memcpy(&g_workingLoggerConfig,&g_savedLoggerConfig,sizeof(struct LoggerConfig));
}

int flashLoggerConfig(){
	return flash_write((void *)&g_savedLoggerConfig,(void *)&g_workingLoggerConfig);	
}

