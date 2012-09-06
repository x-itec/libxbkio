#ifndef libxbkioh
#define libxbkioh 
#include<string>
#include<stdio.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <vector>
#include <time.h>
#include <sys/types.h>
#include <sys/resource.h>
#include <string.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

#include <map>
#include <iostream>
#include <fstream>


class xbkio_base
{
public:
string file_name;//der zuletzt benutze Filename
off_t file_size;
string file_content;//Inhalt der Datei

struct stat stat_buffer;//wird von filesize gefuellt

//rueckgabewerte von getparam
string param_name;
string param_value;

virtual int file_exists(string filename)=0;//0=nein,1=ja
virtual int load(string filename)=0;//0=Problem;1=ok
virtual off_t filesize(string filename)=0;//liefert den Rückgabewert von ::stat() und setzt Dateigroesse nach file_size
virtual string getparam(string parameter)=0;//leer = nicht gefunden oder eben leer
};

class xbkio : public xbkio_base
{
public:

int file_exists(string filename);
int load(string filename);
string getparam(string parameter); 
off_t filesize(string filename);
};
#endif
