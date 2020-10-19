#include"ch03.h"
#define BUF_SIZE 8

int main(){
	FILE *fd;
	struct iobuf{
		char buf[BUF_SIZE];
		char others[BUF_SIZE];
	}buffer;
	memset(&buffer, '\0', sizeof(struct iobuf));
	printf("Please enter a line\n");
	gets(buffer.buf); //用gets读输入数据
	printf("Get() get string \"%s\"\n", buffer.buf);
	//查看溢出情况，buffer.others顺序连接在buffer.buf的后面
	printf("buffer.others is \"%s\"\n", buffer.others);

	return 0;
}
