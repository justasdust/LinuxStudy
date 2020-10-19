#include<stdio.h>
#include<float.h>

int main(){
	printf("float Max=%e Min=%e\n", FLT_MAX, FLT_MIN);
	printf("float Max=%f Min=%f\n", FLT_MAX, FLT_MIN);

	printf("double Max=%e Min=%e\n", DBL_MAX, DBL_MIN);
	printf("double Max=%lf Min=%lf\n", DBL_MAX, DBL_MIN);
	
	return 0;
}
