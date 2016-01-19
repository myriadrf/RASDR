// -----------------------------------------------------------------------------
// FILE: 		TestLog.cpp
// DESCRIPTION:	Container for storing and reading messages
// DATE:		2013-05-06
// AUTHOR(s):	Lime Microsystems
// REVISIONS:
// -----------------------------------------------------------------------------
#include "TextLog.h"
#include "string.h"

TextLog::TextLog()
{
	textLines = new vector<string>();
	textLines->clear();
	textLines->reserve(10);
	iterator = 0;
	firstUnreadedLine = 0;
}

TextLog::~TextLog()
{
	textLines->clear();
	delete textLines;
}

void TextLog::LinesBegin()
{
	iterator = 0;
}

void TextLog::LinesBeginUnreaded()
{
	iterator = firstUnreadedLine;
}

bool TextLog::LinesEnd()
{
	if (iterator < textLines->size())
		return false;
	else
		return true;
}

void TextLog::NextLine()
{
	iterator++;
}

string TextLog::GetCurrentLine()
{
	if(iterator < textLines->size() )
	{
		if(iterator >= firstUnreadedLine)
			firstUnreadedLine = iterator+1;
		return textLines->at(iterator);
	}
	else
		return "There is no more messages";
}

void TextLog::AddLine(string line)
{
	textLines->push_back(line);
}

void TextLog::Clear()
{
	textLines->clear();
	iterator = 0;
	firstUnreadedLine = 0;
}

unsigned int TextLog::Length()
{
	string output = "";
	for(int i = 0; i<textLines->size(); i++)
	{
		output.append((*textLines)[i]);
		output.append("\n");
	}
	char eol = 0x00;
	output.append(&eol);
	int len = output.length()+1;
	return len;
}

void TextLog::Dump(char *buffer)
{
	string output;
	for(int i = 0; i<textLines->size(); i++)
	{
		output.append((*textLines)[i]);
		output.append("\n");
	}
	char eol = 0x00;
	output.append(&eol);
	int len = output.length();
	memcpy( buffer, output.c_str(), len+1 );
	textLines->clear();
}
