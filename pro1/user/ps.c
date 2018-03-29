#include "types.h"
#include "stat.h"
#include "user.h"
#include "ProcessInfo.h"
#include "param.h"


int
main(int argc, char *argv[])
{
	struct ProcessInfo processInfoTable[NPROC];
	int i;
	int num = 0;
	char *s[] = {"UNUSED","EMBRYO","SLEEPING","RUNNABLE","RUNNING","ZOMBIE"};


	if(argc < 1){
		printf(1, "usage: type 'ps' to list current processes...\n");
		exit();
	}
	num = getprocs(processInfoTable);

	for (i = 0; i < num; ++i)
	{
		printf(1,"%d %d %s %d %s \n",processInfoTable[i].pid, processInfoTable[i].ppid,
		s[processInfoTable[i].state], processInfoTable[i].sz, processInfoTable[i].name);
	}
	exit();
}