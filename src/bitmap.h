#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
 
#define BITMAP_OK    1;
#define BITMAP_ERROR 0;
 
typedef struct bitmap_s{
    /*有几个bit位*/
    int bits;
    /*为0个数*/
    int zero_count;
    /*为1的个数*/
    int one_count;
    /*字节数组*/
    unsigned char buf[];
}bitmap_t;
static bitmap_t *bitmap;
/*初始化*/
bitmap_t *bitmap_init(int size);
/*在字节数组的指定index设置0或1*/
int   bitmap_set(bitmap_t  *bitmap  ,int index,int flag);
/*释放字节数组*/
void  bitmap_free(bitmap_t *bitmap);
/*在指定index获取flag*/
int   bitmap_get(bitmap_t  *bitmap  ,int index);
 
//bitmap 初始化
bitmap_t* bitmap_init(int size){
     int nbytes;
     if(size%8!=0)
        nbytes = size/8 + 1;
     else
        nbytes = size/8;
     bitmap = (bitmap_t*)malloc(sizeof(bitmap_t)+nbytes*sizeof(char));
     if(bitmap==NULL)
        return NULL;
     bitmap->bits = size;
     memset(bitmap->buf,0,nbytes);
     bitmap->zero_count = bitmap->bits;
     bitmap->one_count  = bitmap->bits - bitmap->zero_count;
     return bitmap;
}
 
/*在指定索引index上设置flag*/
int  bitmap_set(bitmap_t *bitmap,int index,int flag){
    if(index>=bitmap->bits)
        return BITMAP_ERROR;
    int seg         = index / 8;
    int offset      = index % 8;
    unsigned char *p= bitmap->buf + seg;
    if(flag == 1 && bitmap_get(bitmap,index)==0){
            unsigned char tmp  = 0x1<<(8-offset-1);
            *p |= tmp;
            bitmap->zero_count --;
            bitmap->one_count ++ ;
    }
    if(flag == 0 && bitmap_get(bitmap,index)==1){
        unsigned char temp = (0x1<<(8-offset-1))-1;
        *p &= temp;
        bitmap->zero_count ++;
        bitmap->one_count  --;
    }
    return BITMAP_OK;
}
 
/*获取index位置的flag*/
int bitmap_get(bitmap_t *bitmap,int index){
    if(index>=bitmap->bits)
        return BITMAP_ERROR;
    int seg         = index / 8;
    int offset      = index % 8;
    int tmp = bitmap->buf[seg] & (0x1<<(8-offset-1));
    return tmp >0 ? 1 :0;
}
 
/*释放bitmap*/
void bitmap_free(bitmap_t *bitmap){
    free(bitmap);
}