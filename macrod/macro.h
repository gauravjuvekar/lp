typedef struct mnt{
	char name[16];
	int para_num;
	int start;	
}MNT;

typedef struct mdt{
	int index;
	char line[32];	
}MDT;

int feed_formal_arg(char a[][5], char op[]);
int find_arg_index(char a[][5], char op[], int );
char arg[5][5], act[5][5];
int mdtIndex;
int mntIndex;
MNT* mnt;
MDT* mdt;
