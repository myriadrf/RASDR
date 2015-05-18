// -----------------------------------------------------------------------------
// FILE: 		TestLog.h
// DESCRIPTION:	Header for TestLog.cpp
// DATE:		2013-05-06
// AUTHOR(s):	Lime Microsystems
// REVISIONS:
// -----------------------------------------------------------------------------
#ifndef TEXTLOG
#define TEXTLOG

#include <string>
#include <vector>
using namespace std;

class TextLog
{
	public:
		TextLog();
		~TextLog();

		void LinesBegin();
		void LinesBeginUnreaded();
		bool LinesEnd();
		void NextLine();
		string GetCurrentLine();

		void AddLine(string line);
		void Clear();

		unsigned int Length();
		void Dump(char *buffer);

	private:
		vector<string> *textLines;
		int iterator;
		int firstUnreadedLine;
};

#endif
