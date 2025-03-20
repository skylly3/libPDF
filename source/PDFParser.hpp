// class PDFParser

#include <fstream>
#include <string>
#include "PDFVersion.hpp"
#include "Objects.hpp"
//#include "Encryption.hpp"  //注释 by jl

#define INCLUDE_PARSER 1

// White-space characters
#define NUL char(0x00)
#define TAB char(0x09)
#define LF  char(0x0A)
#define FF  char(0x0C)
#define CR  char(0x0D)
#define SP  char(0x20)
// EOL: CR, LF, CR+LF

// header and footer
#define HEADER "%PDF-"
#define FOOTER "%%EOF"
#define SXREF  "startxref"
#define TRAIL  "trailer"
#define XREF   "xref"
#define STM    "stream"
#define ESTM   "endstream"

using namespace std;

class PDFParser{
private:
	bool error;
	int fileSize;
	int offset;
	int lastXRef;
	bool findHeader();
	bool isSpace(char a);
	bool isEOL(char a);
	bool isDelimiter(char a);
	bool isOctal(char a);
	int judgeDelimiter(bool skip);
	int judgeDelimiter(bool skip, istream* is);
	int judgeType();
	int judgeType(istream* is);
	bool gotoEOL();     //到下一行
	bool gotoEOL(int flag);
	bool findFooter();
	void backtoEOL();   //到上一行
	bool findSXref();
	void readLine(char* buffer, int n);
	int readTrailer(int position);
	int readXRef(int position);
	bool readObjID(int* objNumber, int* genNumber);
	bool readInt(int* value);
	bool readInt(int* value, istream* is);
	bool readRefID(int* objNumber, int* genNumber);
	bool readRefID(int* objNumber, int* genNumber, istream* is);
	bool readReal(double* value);
	bool readReal(double* vlaue, istream* is);
	bool readBool(bool* value);
	bool readBool(bool* value, istream* is);
	bool readToken(char* buffer, int n);
	bool readToken(char* buffer, int n, istream* is);
	bool readArray(Array* array);
	bool readArray(Array* array, istream* is);
	unsigned char* readName();
	unsigned char* readName(istream* is);
	uchar* readString();
	uchar* readString(istream* is);
	bool skipSpaces();
	bool skipSpaces(istream* is);
	bool readDict(Dictionary* dict);
	bool readDict(Dictionary* dict, istream* is);
	bool readStream(Stream* stm);
	bool readStream(Stream* stm, bool outputError);
	bool investigatePages(Indirect* pages, int* pageCount);
public:
	PDFParser(istringstream & st);
	virtual ~PDFParser();
	istringstream & file;
	PDFVersion V_header;
	PDFVersion V_catalog;
	Dictionary trailer;
	//Encryption* encryptObj;         //注释 by jl
	//Encryption* encryptObj_ex;       //注释 by jl
	int encryptObjNum;
	bool encrypted;
	Indirect** Reference;
	int ReferenceSize;
	Page** Pages;
	int PagesSize;
	int lastXRefStm;
	bool hasError();
	bool readRefObj(Indirect* ref, void** object, int* objType);
	bool readPage(int index, unsigned char* key, void** value, int* type, bool inheritable);
};
