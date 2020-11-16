#include"my.h"

usernode input(FILE* fp){
	usernode x = (usernode)malloc(sizeof(struct user));
	int flag;
	do{
		printf("请输入以下内容：\n");
        	printf("index: ");
		scanf("%d", &x->id);
        	printf("name(8): ");
        	scanf("%s", x->name);
        	printf("htel(12): ");
        	scanf("%s", x->htel);
        	printf("tel(12): ");
      		scanf("%s", x->tel);
		flag = (randdat(x) && checkid(x->id, fp));
		if(flag==0){
			printf("Please enter again:\n");
		}
	}while(flag==0);

	return x;
}

int save(FILE* fp){
	usernode x = input(fp);
	fseek(fp, 0, SEEK_END);
	int ret = fprintf(fp, "%d %s %s %s\n", x->id, x->name, x->htel, x->tel);
	free(x);
	return ret;
}

void output(usernode x){
	printf("%03d\t%s\t%s\t%s\n", x->id, x->name, x->htel, x->tel);
}

int myWrite(FILE* fp){
	int ret = 0;
	usernode x = (usernode)malloc(sizeof(struct user));
	printf("userid\tname\thtel\ttel\n");
	while(!feof(fp)){
		ret += fscanf(fp, "%d %s %s %s\n", &x->id, x->name, x->htel, x->tel);
		output(x);
	}
	free(x);
	return ret;
}

int randdat(usernode x){
	int flag = 1;
	if(strlen(x->name)>8){
		printf("Name is limited with 8 characters!\n");
		flag = 0;
	}
	if(strlen(x->htel)>12){
		printf("Htel is limited with 12 characters!\n");
		flag = 0;
	}
	if(strlen(x->tel)>12){
		printf("Tel is limited with 12 characters!\n");
		flag = 0;
	}
	x->name[0] = toupper(x->name[0]);
	for(int i=1; i<8; i++){
		x->name[i] = tolower(x->name[i]);
	}
	return flag;
}

int cmp1(const void* p1, const void* p2){
	usernode u1 = (usernode)p1;
	usernode u2 = (usernode)p2;
	int rtn = strcmp(u1->name, u2->name);
	return rtn;
}

int cmp2(const void* p1, const void* p2){
        usernode u1 = (usernode)p1;
        usernode u2 = (usernode)p2;
        int rtn = strcmp(u2->name, u1->name);
        return rtn;
}

int userlen(FILE* fp){
	rewind(fp);
	int cnt = 0;
	struct user tmp;
	while(!feof(fp)){
		fscanf(fp, "%d %s %s %s\n", &tmp.id, tmp.name, tmp.htel, tmp.tel);
		cnt++;
	}
	return cnt;
}

int checkid(int xid, FILE* fptr){
	rewind(fptr);
	int tmpid, flag=1;
	char tmp1[8], tmp2[12], tmp3[12];
	while(!feof(fptr)){
		fscanf(fptr, "%d %s %s %s\n", &tmpid, tmp1, tmp2, tmp3);
		if(tmpid == xid){
			flag = 0;
			printf("The id has already existed!\n");
			break;
		}
	}
	
	return flag;
}

void usersort(FILE* fp){
	//rewind(fp);
	int n = userlen(fp);
	usernode pu = (usernode)malloc(n*sizeof(struct user));
	int i=0;
	rewind(fp);
	while(!feof(fp) && i<n){
		fscanf(fp, "%d %s %s %s\n", &pu[i].id, pu[i].name, pu[i].htel, pu[i].tel);
		i++;
	}
	printf("Please choose: 0.DESC\t1.ASC\n");
	int ans;
	scanf("%d", &ans);
	if(ans==0 || ans==1){
		mysort(pu, n, ans);
	}
	else{
		printf("Don't have this option.\n");
	}
	fclose(fp);
	remove("./user.dat");
	
	fp = fopen("./user.dat", "a+");
	for(int i=0; i<n; i++){
		fprintf(fp, "%d %s %s %s\n", pu[i].id, pu[i].name, pu[i].htel, pu[i].tel);
	}
	free(pu);
}

void mysort(usernode pu, int n, int flag){
	if(flag == 1){ //ASC
		qsort(pu, n, sizeof(struct user), cmp1);
	}
	if(flag == 0){ //DESC
		qsort(pu, n, sizeof(struct user), cmp2);
	}
}
