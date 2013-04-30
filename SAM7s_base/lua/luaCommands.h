/*
 * luaCommands.h
 *
 *  Created on: Jul 24, 2011
 *      Author: brent
 */

#ifndef LUACOMMANDS_H_
#define LUACOMMANDS_H_
#include "command.h"
#include "serial.h"

#define LUA_COMMANDS \
		{"lua", "Enter the lua script interpreter.","", ExecLuaInterpreter}, \
		{"reloadScript", "Reloads the current script","",ReloadScript}, \
		{"writeScriptPage", "Writes the base64 encoded script to the specified 256 byte page.","<page> <encodedScript>",WriteScriptPage}, \
		{"readScriptPage", "Returns the specified script page in base64 encoded format.","<page>", ReadScriptPage}, \
		{"showLuaStats", "Info on Lua State and System memory.","", ShowLuaStats} \

Serial *getLuaSerialContext();
void ExecLuaInterpreter(Serial *serial, unsigned int argc, char **argv);
void ReloadScript(Serial *serial, unsigned int argc, char **argv);
void WriteScriptPage(Serial *serial, unsigned int argc, char **argv);
void ReadScriptPage(Serial *serial, unsigned int argc, char **argv);
void ShowMemInfo(Serial *serial, unsigned int argc, char **argv);
void ShowLuaStats(Serial *serial, unsigned int argc, char **argv);

#endif /* LUACOMMANDS_H_ */
