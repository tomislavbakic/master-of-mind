#define BS              8
#define FORMFEED       12
#define CR             13
#define LF             10
#define ESC            27
#define TAB             9

#define HOMEKEY       327
#define UPKEY         72 // 328
#define PGUPKEY       73 // 329
#define LEFTKEY       75 // 331
#define RIGHTKEY      77 // 333
#define ENDKEY        335
#define DOWNKEY       80 // 336
#define PGDNKEY       81 // 337
#define INSKEY        338
#define DELKEY        339

#define CTRLHOMEKEY   375
#define CTRLPGUPKEY   388
#define CTRLENDKEY    373
#define CTRLPGDNKEY   374
#define CTRLBS        127

#define CTRLY         25
#define CTRLU         21

#define F1            315
#define F2            316
#define F3            317
#define F4            318
#define F5            319
#define F6            320
#define F7            321
#define F8            322
#define F9            323
#define F0            324

#define CTRLF1        350
#define CTRLF2        351
#define CTRLF3        352
#define CTRLF4        353
#define CTRLF5        354
#define CTRLF6        355
#define CTRLF7        356
#define CTRLF8        357
#define CTRLF9        358
#define CTRLF0        359

#define ALTF1         360
#define ALTF2         361
#define ALTF3         362
#define ALTF4         363
#define ALTF5         364
#define ALTF6         365
#define ALTF7         366
#define ALTF8         367
#define ALTF9         368
#define ALTF0         369

//error flags
#define ERROR 1
#define NO_ERROR 0

//flags
#define READ_FROM_FILE 0
#define INSERT_NAME 1

//color
int BLACK = 0;
int BLUE = 1;
int CYAN = 3;
int RED = 4;
int YELLOW = 6;
int	WHITE = 15;
int GREEN = 2;
int GRAY = 8;
int BACKGROUND_YELLOW = 96; //black font color
int BACKGROUND_WHITE = 113; //blue font color
int BACKGROUND_RED_WHITE = 79; //white font color
int BACKGROUND_GREEN_WHITE = 47; //white font color

//line
int TL = 218; //top left
int TR = 191; // top right
int BL = 192; //bottom left
int BR = 217; //bottom right
int T = 194; // T shape
int RT = 195; // right T shape
int LT = 180; // left T shape
int TT = 193; //top T
int HL = 196; //horizontal line
int VL = 179; // vertical line

//double lines
int DTL = 201;
int DTR = 187;
int DBL = 200;
int DBR = 188;
int DVL = 186;
int DHL = 205;