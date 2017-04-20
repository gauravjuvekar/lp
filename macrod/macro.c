#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"macro.h"
int check_call(char a[]);
int main() {


	FILE *in, *out/*, *mnt, *mdt*/;
	in = fopen("input2.txt", "r");
	//mnt = fopen("mnt.txt", "w");
	//mdt = fopen("mdt.txt", "w");
	out = fopen("out.txt","w");
	char la[20], mne[20], opnd[20], mdtmp[20], mne_t[20], op_t[20];;
	int mac_ct = 0, n_arg = 0, argn, check = 0, mdt_i = 0, n_act = 0;
	mdtIndex = 0;
	mntIndex = 0;
	fscanf(in,"%s%s%s", la, mne, opnd);
	mnt = (MNT *)malloc(sizeof(MNT)*10);
	mdt = (MDT *)malloc(sizeof(MDT)*100);
	while((strcmp(la,"END") != 0)) {
		if(strcmp(mne, "MACRO") == 0) {
			mac_ct++;

			/*no of arguments to macro*/
			n_arg = feed_arg(arg, opnd);

			/*Fill MNT*/
			mnt[mntIndex].para_num = n_arg;
			strcpy(mnt[mntIndex].name, la);
			mnt[mntIndex].start = mdtIndex;
			mntIndex++;
			
			fscanf(in,"%s%s%s", la, mne, opnd);
			
			/*Fill MDT */
			while(strcmp(mne, "MEND") != 0){
				argn = find_arg_index(arg, opnd, n_arg);
				if(argn != -1){
					sprintf(mdtmp,"%s\t#%d\n", mne, argn);
				strcpy(mdt[mdtIndex].line, mdtmp);
				printf("here\n");
				printf("%d\t%s\n",mdtIndex, mdt[mdtIndex].line);
				mdt[mdtIndex].index = mdtIndex;
				mdtIndex++;

				}
				else{
					
					/*check if a call is found in macro definition*/
					if((check = check_call(mne)) != -1){
						mdt_i = mnt[check].start;
						sscanf(mdt[mdt_i++].line,"%s%s", mne_t, op_t);
	
						//printf("tmp : %s\t%s\n", mne_t, op_t);
						n_act = feed_arg(act, opnd);
						
						/*This implementation accepts only actual arguments for inner macro*/
						while(strcmp(mne_t, "MEND") != 0){
							if(op_t[0] == '#')
								sprintf(mdtmp,"%s%s", mne_t, act[(op_t[1] - '0') - 1]);
							else
								sprintf(mdtmp,"%s%s", mne_t, op_t);
							strcpy(mdt[mdtIndex].line, mdtmp);
							mdt[mdtIndex].index = mdtIndex;
							mdtIndex++;
							sscanf(mdt[mdt_i++].line,"%s%s",mne_t,op_t);
						}
					}
					else{

				
						sprintf(mdtmp,"%s\t%s\n", mne, opnd);
						
				strcpy(mdt[mdtIndex].line, mdtmp);
				printf("here2\n");
				printf("%d\t%s\n",mdtIndex, mdt[mdtIndex].line);
				mdt[mdtIndex].index = mdtIndex;
				mdtIndex++;
				}
			}
					
				
				fscanf(in,"%s%s%s", la, mne, opnd);
			}
			/*end of definition*/
			strcpy(mdt[mdtIndex++].line, "MEND");
			mdt[mdtIndex].index = mdtIndex;
			fscanf(in,"%s%s%s", la, mne, opnd);
		}
		
		else{
			if(strcmp(mne,"MEND") != 0)
				fprintf(out, "%s\t%s\t%s\n", la, mne, opnd);
			fscanf(in,"%s%s%s", la, mne, opnd);
		}
	}


}
int feed_arg(char a[][5], char op[]){

	int i = 0;
	char *p = (char *)malloc(10);
	p = strtok(op, ",");
	while(p){
		strcpy(a[i], p);
		i++;
		p = strtok(NULL,",");
	}
	return i;
}
int find_arg_index(char a[][5], char op[], int narg){
	int i;
	for(i = 0; i < narg; i++){
//		printf("%s -- %s\n", op, a[i]);
		if(strcmp(a[i], op) == 0)
			return i+1;
	}
	return -1;
}
int check_call(char a[]){

	int i;
	for(i = 0; i < mntIndex; i++){
		if(strcmp(a, mnt[i].name) == 0)
			return i;
	}
	return -1;
}
