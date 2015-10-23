#includes	"config.h"
 
#define LCD1602_DB  P0
/*ЦёБо
http://wenku.baidu.com/link?url=iX2vq_zkqrwLJt-uB-Du2j5cCdvRt-sQbbmYbKIaFBOyvBBzG9WgnYyYuJy3uASZFBJInKmIJgke9TCrA3btdu_1Oro9NYybDgb7SJ6VI9y

*/
sbit LCD1602_RS = P1^0;
sbit LCD1602_RW = P1^1;
sbit LCD1602_E = P1^5;
void LcdWaitReady();
void LcdWriteCmd(unsigned char cmd);
void LcdWriteDat(unsigned char dat);
void LcdSetCursor(unsigned char x, unsigned char y);
void LcdShowStr(unsigned char x, unsigned char y, unsigned char *str);
void InitLcd1602();