#include <stdio.h>
#include "bitmap.h"
 
//static bitmap_t *bitmap;  
 
/**
*  API 函数
*
* bitmap_t *bitmap_init(int size);                              //初始化
* int       bitmap_set(bitmap_t  *bitmap  ,int index,int flag); //在字节数组的指定index设置0或1
* void      bitmap_free(bitmap_t *bitmap);                      //释放字节数组
* int       bitmap_get(bitmap_t  *bitmap  ,int index);          //在指定index获取flag
*/
 
int main(){
    bitmap_t *p=NULL;
    if(p=bitmap_init(10)){
        bitmap_set(p,6,1);
        bitmap_set(p,2,1);
        bitmap_set(p,2,1);
        bitmap_set(p,3,1);
        printf("%d\n",bitmap_get(p,0));
        printf("%d\n",bitmap_get(p,1));
        printf("%d\n",bitmap_get(p,2));
        printf("%d\n",bitmap_get(p,6));
        printf("%d\n",p->buf[0]);
        printf("zero_count=%d,one_count=%d\n",bitmap->zero_count,bitmap->one_count);
    }
    return 0;
}