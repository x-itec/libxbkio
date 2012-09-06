#ifndef libxbkio
#define libxbkio

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


//#include <xbk/xbkstringutil.h>
#include <xbk/xbkdebug.c>
extern int errno;

#include "../include/xbkio.h" 


int xbkio::file_exists(string filename)
{
FILE *f;
if( !(f=fopen(filename.c_str(),"r")) ) 
	{return 0;}
	else{fclose(f);return 1;}
}

/*
TODO: Die Datei wird 3x im Speicher rumkopiert nur damit ich später
die strings usen kann in der Hoffnung das dies schneller funktionieren
würde und im Endeffekt wird wieder alles langsamer also so kann
das net sein. 3x hier kopieren.. zu viel.
*/



off_t xbkio::filesize(string filename)
{
DEBUG("stat %s",filename.c_str());
int x=stat(filename.c_str(),&stat_buffer);
DEBUG("stat-flag: %i",x);
#ifdef DEBUGME
if(x==-1)
	{
	DEBUG("error: %s",strerror(errno));
	}
file_size=stat_buffer.st_size;return file_size;
#endif
}





int xbkio::load(string filename)
{
char ch;
off_t counter;
char *psbuf;
file_content="";

FILE *f;
	DEBUG("fopen %s",filename.c_str());
	f=fopen(filename.c_str(),"r");
	if(f)
	{
	DEBUG("call filesize");
	filesize(filename);
	DEBUG("filesize: %i",file_size);
	DEBUG("alloc mem..");
	psbuf=new char[file_size];
	fread(psbuf,file_size,1,f);
	fclose(f);
	//das ist leider etwas dumm
	string substring(file_size,0);
	for(off_t x=0;x<file_size;x++)
		{
		substring[x]=*psbuf++;
		}
	file_content=substring;//nicht so super
	return 1;
	}
	else
	return 0;

}



string xbkio::getparam(string parameter)
{
string result;

/*
Zukunft (da mach ich aber noch ne eigene Funktion zu):
<sektionsname>
parameter=value
</sektionsname>
*/

// suche Parameter

int parameterposition;
int quoteflag=0;
int fclen=file_content.length();  
DEBUG("fclen: %i",fclen);
parameterposition = file_content.find(parameter);
DEBUG("find position: %i",parameterposition);

if(parameterposition)
	{
	DEBUG("ok, found. searching");
	int spaceflag=0;
		//1=erstes Leerzeichen erreicht
		//2=Erste, mögliche Stringposition entdeckt
	for(;;)
		{
		DEBUG("Spaceflag: %i parameterposition %i",spaceflag,parameterposition);
		if(file_content[parameterposition]=='=' && spaceflag<2)
			{
			DEBUG("Spaceflag=1");
			spaceflag=1;++parameterposition;
			}
		if(file_content[parameterposition]==' ' && spaceflag==1 && parameterposition<fclen)
			{
			DEBUG("überspringe Space");
			//Leerzeichen übergehen
			++parameterposition;
			}
		if(file_content[parameterposition]!=' ' && spaceflag==1)
			{
			DEBUG("Erstes Parameterzeichen gefunden %c",file_content[parameterposition]);
			spaceflag=2;
			if(file_content[parameterposition]=='"')
				{
				//Anführungszeichen bestimmt den Anfang
				quoteflag=1;//es gibt ein " 
				parameterposition++;
				}
			spaceflag=3;//erster Durchlauf
			}
			if(spaceflag>=2)
			{
			//Erste Stringposition entdeckt
		        //String bis zum möglichen Ende suchen, dann breake
			int resultstringlength=fclen-parameterposition;
			DEBUG("Reststringlänge: %i",resultstringlength);
			int dummycounter;
			dummycounter=0;
			char *dummyspeicher= new char[resultstringlength];
			for(;;)
				{
				DEBUG("ppos/dpos/char: %i/%i%c",parameterposition,dummycounter,file_content[parameterposition]);
			 		dummyspeicher[dummycounter++]=file_content[parameterposition++];				

					/*
					Wenn ; und danach ein Return dann break
					*/
					if(
					file_content[parameterposition]==';'
					  )
						{
						DEBUG(";");
						if(file_content[parameterposition+1]==13 || file_content[parameterposition+1]==10)
							{
							DEBUG(";break");
							break;
							}
						}
					/*
					Wenn Return dann break
					*/ 
					if(
					file_content[parameterposition]==13 || 
					file_content[parameterposition]==10
				          ) 
					  {break;}		
				}


			dummyspeicher[dummycounter]=0;
			DEBUG("LC FC QF: %c %c %i",dummyspeicher[dummycounter-1],dummyspeicher[0],quoteflag);
			if( dummyspeicher[dummycounter-1]=='"' && quoteflag==1)
			{
			DEBUG("Setze an Pos %i eine NULL",dummycounter-1);
			dummyspeicher;dummyspeicher[dummycounter-1]=0;
			}			
			
			result=dummyspeicher;//String wird kopiert	
			delete dummyspeicher;
			break;//äußere for(,,) Geschichte verlassen	
			}else
		if(parameterposition==fclen)
			{
			break;//pech
			}else
			{++parameterposition;
			}
				
		}//for;;
	}//if paramposition




return result;
}
#endif
