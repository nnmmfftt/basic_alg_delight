#include <stdlib.h>
#include <stdio.h>

int add_before_overflow(){
unsigned int i = 0;
for (i ;i<0xFFFFFFFF;++i){
	continue;
	}
printf("%u",i);
}
int main(){
add_before_overflow();
return 0;
}

