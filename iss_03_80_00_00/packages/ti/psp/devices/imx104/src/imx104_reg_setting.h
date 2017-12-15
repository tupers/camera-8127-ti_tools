#ifndef _IMX104_REG_SETTING_H_
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
#define _IMX104_REG_SETTING_H_

#define IMX104_LVDS_FPS  2

/*frame rate select:0x0:120fps;0x01:60fps;0x02:30fps
60fps by default,
*/

#if   IMX104_LVDS_FPS==0
#define FRAME_RATE_SETTING    0x00
#define HMAX_SETTING_HIGH      0x06
#define HMAX_SETTING_LOW      0x72
#elif     IMX104_LVDS_FPS==1
#define FRAME_RATE_SETTING    0x01
#define HMAX_SETTING_HIGH      0x0c
#define HMAX_SETTING_LOW      0xe4
#elif     IMX104_LVDS_FPS==2
#define FRAME_RATE_SETTING    0x02
#define HMAX_SETTING_HIGH      0x19
#define HMAX_SETTING_LOW      0xc8
#else

#endif


#define IMX104_REG_COUNT  630*2

const unsigned short IMX104_SETTING[IMX104_REG_COUNT]={
0x0200,0x1,
0x0201,0x0,
0x0202,0x1,
0x0203,0x0,
0x0204,0x10,
0x0205,0x01,
0x0206,0x0,
#ifdef WDR_ON
0x0207,0x10,
#else
0x0207,0x20, //default 0x10
#endif
0x0208,0x10,
0x0209,FRAME_RATE_SETTING,
0x020a,0x30, //reduce from 0xf0, isif will do the extra subtraction
0x020b,0x00,
0x020c,0x0,
0x020d,0x20,
0x020e,0x01,
0x020f,0x01,
0x0210,0x39,
0x0211,0x0,
0x0212,0x50,
0x0213,0x00,
0x0214,0x0,
0x0215,0x0,
0x0216,0x08,
0x0217,0x1,
#ifdef WDR_ON
0x0218,0xee,
0x0219,0x02,
#else
0x0218,0x44, //0xee
0x0219,0x04,  //0x02
#endif
0x021a,0x00,
0x021b, HMAX_SETTING_LOW,
0x021c, HMAX_SETTING_HIGH,
0x021d,0xff,
0x021e,0x01,
0x021f,0x00,
0x0220,0x0,
0x0221,0x0,
0x0222,0x0,
0x0223,0x0,
0x0224,0x0,
0x0225,0x0,
0x0226,0x0,
0x0227,0x0,
0x0228,0x0,
0x0229,0x0,
0x022a,0x0,
0x022b,0x0,
0x022c,0x0,
0x022d,0x0,
0x022e,0x0,
0x022f,0x0,
0x0234,0x0,
0x0235,0x0,
0x0236,0x14,
0x0237,0x00,
0x0238,0x0,
0x0239,0x0,
#ifdef WDR_ON
0x023a,0x19,
0x023b,0x04,
#else
0x023a,0xc0,  //0x19
0x023b,0x03,  //0x04
#endif
0x023c,0x0,
0x023d,0x0,
#ifdef WDR_ON
0x023e,0x1c,
#else
0x023e,0x00,  //0x1c
#endif
0x023f,0x05,
//0x0244,0x1,
0x0244,0x61,/*lvds ddr output,12bit*/
0x0245,0x1,
0x0246,0x0,
0x0247,0x08,
0x0248,0x0,
0x0249,0x0,
0x024a,0x0,
0x024b,0x0,
0x024c,0x0,
0x024d,0x0,
0x024e,0x0,
0x024f,0x0,
0x0250,0x16,
0x0251,0x00,
0x0252,0x01,
0x0253,0x0,
0x0254,0x63,
0x0255,0x0,
0x0256,0xc9,
0x0257,0x64,
0x0258,0x0,
0x025b,0x0,
0x025c,0x20,
0x025d,0x0,
0x025e,0x2c,
0x025f,0x10,
0x0260,0x0,
0x0261,0x21,
0x0262,0x08,
0x0263,0xe8,
0x0264,0x0,
0x0265,0x20,
0x0266,0x0,
0x0268,0x0,
0x0269,0x0c,
0x026a,0x19,
0x026b,0x00,
0x026c,0x00,
0x026d,0x64,
0x026e,0x00,
0x026f,0x00,
0x0270,0x1,
0x0274,0x0,
0x0275,0x0,
0x0276,0x0,
0x0277,0x0,
0x0278,0x0,
0x0279,0x0,
0x027a,0x0,
0x027b,0x0,
0x027c,0x0,
0x027d,0x0,
0x027e,0x0,
0x027f,0x0,
0x0280,0x0,
0x0281,0x0,
0x0284,0x0,
0x0285,0x0,
0x0286,0x1,
0x0287,0x0,
0x0288,0x0,
0x0289,0xff,
0x028a,0x0,
0x028c,0x02,
0x028d,0x0,
0x028e,0x0,
0x028f,0x0,
0x0290,0x0,
0x0291,0x0,
0x0292,0x0,
0x0293,0x1,
0x0294,0x1,
0x0295,0x1,
0x0296,0x0,
0x0297,0x0,
0x0298,0x0,
0x0299,0x0,
0x029c,0x0,
0x029d,0x40,
0x029e,0x71,
0x029f,0x41,
0x02a0,0x0,
0x02a1,0x45,//from register map,it's 0x44
0x02a2,0x22,
0x02a3,0x06,
0x02a4,0x2a,
0x02a5,0x2a,
0x02a8,0x0,
0x02a9,0x10,
0x02aa,0x00,
0x02ab,0x10,
0x02ac,0x00,
0x02ad,0x10,
0x02ae,0x00,
0x02af,0x10,
0x02b0,0x00,
0x02b1,0xff,
0x02b2,0x01,
0x02b3,0x41,
0x02b4,0x00,
0x02b5,0x60,
0x02b6,0x12,
0x02b7,0x12,
0x02b8,0xf,
0x02b9,0x0,
0x02ba,0x0,
0x02bb,0x0,
0x02be,0x0,
0x02bf,0x10,
0x02c0,0x00,
0x02c1,0x0,
0x02c4,0x0,
0x02c5,0x20,
0x02c6,0x30,
0x02c7,0x20,
0x02c8,0x40,
0x02c9,0x21,
0x02ca,0x0,
0x02cc,0x21,
0x02cd,0x32,
0x02ce,0x00,
0x02cf,0xd1,
0x02d0,0x1b,
0x02d1,0x00,
0x02d2,0x5f,
0x02d3,0x0,
0x02d4,0x0,
0x02d5,0x0,
0x02d6,0x00,
0x02d7,0x00,
0x02d8,0x0,
0x02d9,0x0,
0x02da,0x0,
0x02db,0x0,
0x02e0,0x00,
0x02e1,0xff,
0x02e2,0xff,
0x02e3,0xff,
0x02e4,0xff,
0x02e5,0xff,
0x02e6,0xff,
0x02e8,0x0,
0x02e9,0x4,
0x02ea,0x2,
0x02eb,0x1,
0x02ec,0x2,
0x02ed,0x43,
0x02ee,0x44,
0x02ef,0x0,
0x02f0,0x50,
0x02f1,0x0,
0x02f2,0x00,
0x02f3,0x0,
0x02f4,0x50,
0x02f5,0x0,
0x02f6,0x00,
0x02f7,0x0,
0x02f8,0x50,
0x02f9,0x0,
0x02fa,0x00,
0x02fb,0x0,
0x0301,0x0,
0x0302,0x80,
0x0303,0x55,
0x0304,0x0,
0x0305,0x0,
0x0306,0x0,
0x0307,0x0,
0x030b,0x84,
0x030c,0x0,
0x030d,0xc1,
0x030e,0xef,
0x030f,0x18,
0x0310,0x0,
0x0311,0x0,
0x0312,0x0,
0x0316,0xa1,
0x0317,0x14,
0x0318,0x41,
0x0319,0x0,
0x031d,0x7,
0x031e,0x03,
0x031f,0x04,
0x0320,0x12,
0x0321,0x0,
0x0322,0x0,
0x0323,0x07,
0x0324,0xfb,
0x0325,0xef,
0x0326,0xdf,
0x0327,0x0,
0x032b,0x88,
0x032c,0x0,
0x032d,0x0,
0x0331,0x1c,
0x0332,0x00,
0x0333,0x0,
0x0334,0x0,
0x0335,0x0,
0x0339,0x0,
0x033d,0x1,
0x033e,0x0,
0x033f,0x8,
0x0340,0x1,
0x0341,0x0,
0x0342,0x0,
0x0346,0x02,//ADD  from original table,lost
0x0347,0x87,
0x0348,0x0,
0x0349,0x0,
0x034d,0x2,
0x034e,0x87,
0x034f,0x0,
0x0350,0x0,
0x0354,0x1,
0x0355,0xb,
0x0356,0x60,
0x0357,0x01,
0x0358,0x21,
0x0359,0x00,
0x035a,0x0,
0x035e,0x12,
0x035f,0x0,
0x0364,0x12,
0x0365,0x0,
0x0369,0x10,//0X10 from register map
0x036a,0x0,
0x036b,0x0,
0x036c,0x0,
0x036e,0x0,
0x036f,0xff,
0x0370,0x01,
0x0371,0x02,
0x0373,0x0,
0x0374,0x05,
0x0375,0x0,
0x0376,0x0,
0x0377,0x0,
0x0378,0x0,
0x0379,0x0,
0x037b,0x0,
0x037c,0x0,
0x037d,0x10,
0x037e,0x0,
0x037f,0x0,
0x0380,0x0,
0x0381,0x0,
0x0384,0x4,
0x0385,0x00,
0x0386,0x17,
0x0387,0x00,
0x0388,0x28,
0x0389,0x00,
0x038a,0x40,
0x038b,0x04,
0x038c,0x00,
0x038d,0x00,
0x038e,0x0,
0x038f,0x0,
0x0393,0x4,
0x0394,0x4,
0x0395,0xc,
0x0396,0xc,
0x0397,0xc,
0x0398,0x9e,
0x0399,0x00,
0x039a,0xd0,
0x039b,0x07,
0x039c,0x4e,
0x039d,0x04,
0x039e,0x0,
0x039f,0x0,
0x03a1,0x80,
0x03a2,0x8,
0x03a3,0xc,
0x03a4,0x00,
0x03a5,0x52,
0x03a6,0x01,
0x03a7,0x55,
0x03a8,0x01,
0x03aa,0x3,
0x03ab,0x3,
0x03ac,0x0,
0x03af,0x02,//ADD from register map,lost
0x03b0,0x01,
0x03b1,0x0,
0x03b2,0x0,
0x03b3,0x0,
0x03b5,0x00,
0x03b6,0x0,
0x03b7,0x0,
0x03b8,0x0,
0x03b9,0x0,
0x03ba,0x0,
0x03bb,0x0,
0x03bf,0x0,
0x03c0,0x0,
0x03c1,0x1f,
0x03c2,0x53,
0x03c3,0x06,
0x03c4,0x16,
0x03c5,0x0,
0x03c6,0x0,
0x03c7,0x0,
0x03c8,0x0,
0x03c9,0x0,
0x03ca,0x0,
0x03cb,0x0,
0x03cc,0x0,
0x03cd,0x0,
0x03ce,0x0,
0x03cf,0x0,
0x03d0,0x0,
0x03d1,0x0,
0x03d2,0x0,
0x03d3,0x0,
0x03d4,0x0,
0x03d8,0x0,
0x03d9,0x0,
0x03da,0x0,
0x03db,0x0,
0x0402,0x0,
0x0403,0xcd,
0x0404,0x00,
0x0405,0x5a,
0x0406,0x00,
0x0407,0x4b,
0x0408,0x01,
0x0409,0xe9,
0x040a,0x01,
0x040b,0x1,
0x040c,0x0,
0x040d,0x4,
0x040e,0x32,
0x040f,0x02,
0x0410,0x30,
0x0411,0x00,
0x0412,0x0,
0x0413,0x1b,
0x0414,0x01,
0x0415,0xed,
0x0416,0x01,
0x0417,0x3,
0x0418,0x9,
0x0419,0x21,
0x041a,0x19,
0x041b,0xa1,
0x041c,0x11,
0x041d,0x0,
0x041e,0x5,
0x041f,0x0,
0x0420,0x0,
0x0421,0x0,
0x0422,0x6,
0x0423,0x0,
0x0424,0x0,
0x0425,0x3,
0x0426,0x06,
0x0427,0x00,
0x0428,0x05,
0x0429,0xec,
0x042a,0x40,
0x042b,0x11,
0x042c,0x0,
0x042d,0x22,
0x042e,0x00,
0x042f,0x05,
0x0430,0x0,
0x0431,0xec,
0x0432,0x40,
0x0433,0x11,
0x0434,0x0,
0x0435,0x23,
0x0436,0xb0,
0x0437,0x04,
0x0438,0x0,
0x0439,0x24,
0x043a,0x30,
0x043b,0x04,
0x043c,0xed,
0x043d,0xc0,
0x043e,0x10,
0x043f,0x0,
0x0440,0x44,
0x0441,0xa0,
0x0442,0x04,
0x0443,0x0d,
0x0444,0x31,
0x0445,0x11,
0x0446,0x0,
0x0447,0xec,
0x0448,0xd0,
0x0449,0x1d,
0x044a,0x1,
0x044b,0x05,
0x044c,0x91,
0x044d,0x0c,
0x044e,0x0,
0x044f,0x4,
0x0450,0xa0,
0x0451,0x08,
0x0452,0xd4,
0x0453,0x20,
0x0454,0x1d,
0x0455,0x03,
0x0456,0x54,
0x0457,0x60,
0x0458,0x1f,
0x0459,0x0,
0x045a,0xa9,
0x045b,0x50,
0x045c,0x0a,
0x045d,0x25,
0x045e,0x11,
0x045f,0x12,
0x0460,0x0,
0x0461,0x9b,
0x0462,0x40,
0x0463,0x00,
0x0464,0x0,
0x0465,0x4,
0x0466,0xd0,
0x0467,0x08,
0x0468,0x0,
0x0469,0x4,
0x046a,0x20,
0x046b,0x0a,
0x046c,0x0,
0x046d,0x4,
0x046e,0x20,
0x046f,0x0a,
0x0470,0x0,
0x0471,0x4,
0x0472,0x20,
0x0473,0x0a,
0x0474,0x0,
0x0475,0xec,
0x0476,0x0,
0x0477,0x0,
0x0478,0x0,
0x0479,0x8,
0x047a,0x40,
0x047b,0x00,
0x047c,0x0,
0x047d,0xa5,
0x047e,0x20,
0x047f,0x0a,
0x0480,0x0,
0x0481,0xef,//ADD from register map,lost
0x0482,0xc0,//ADD from register map,lost
0x0483,0x0e,//ADD from register map,lost
0x0484,0x0,
0x0485,0xf6,
0x0486,0x01,
0x0487,0x05,
0x0488,0x0,
0x0489,0x50,
0x048a,0x60,
0x048b,0x1f,
0x048c,0x1,
0x048d,0xbb,
0x048e,0x90,
0x048f,0x0d,
0x0490,0x39,
0x0491,0xc1,
0x0492,0x1d,
0x0493,0x0,
0x0494,0xc9,
0x0495,0x70,
0x0496,0x0e,
0x0497,0x47,
0x0498,0xa1,
0x0499,0x1e,
0x049a,0x0,
0x049b,0xc5,
0x049c,0xb0,
0x049d,0x0e,
0x049e,0x43,
0x049f,0xe1,
0x04a0,0x1e,
0x04a1,0x0,
0x04a2,0xbb,
0x04a3,0x10,
0x04a4,0x0c,
0x04a5,0x0,
0x04a6,0xb3,
0x04a7,0x30,
0x04a8,0x0a,
0x04a9,0x29,
0x04aa,0x91,
0x04ab,0x11,
0x04ac,0x0,
0x04ad,0xb4,
0x04ae,0x40,
0x04af,0x0a,
0x04b0,0x2a,
0x04b1,0xa1,
0x04b2,0x11,
0x04b3,0x0,
0x04b4,0xab,
0x04b5,0xb0,
0x04b6,0x0b,
0x04b7,0x21,
0x04b8,0x11,
0x04b9,0x13,
0x04ba,0x0,
0x04bb,0xac,
0x04bc,0xc0,
0x04bd,0x0b,
0x04be,0x22,
0x04bf,0x21,
0x04c0,0x13,
0x04c1,0x0,
0x04c2,0xad,
0x04c3,0x10,
0x04c4,0x0b,
0x04c5,0x23,
0x04c6,0x71,
0x04c7,0x12,
0x04c8,0x0,
0x04c9,0xb5,
0x04ca,0x90,
0x04cb,0x0b,
0x04cc,0x2b,
0x04cd,0xf1,
0x04ce,0x12,
0x04cf,0x0,
0x04d0,0xbb,
0x04d1,0x10,
0x04d2,0x0c,
0x04d3,0x0,
0x04d4,0xe7,
0x04d5,0x90,
0x04d6,0x0e,
0x04d7,0x0,
0x04d8,0x45,
0x04d9,0x11,
0x04da,0x1f,
0x04db,0x1,
0x04dc,0x1,
0x04dd,0xb0,
0x04de,0x00,
0x04df,0x0,
0x04e0,0x1,
0x04e1,0x20,
0x04e2,0x00,
0x04e3,0x0,
0x04e4,0x3,
0x04e5,0x2,
0x04e6,0x2,
0x04eb,0xa4,
0x04ec,0x60,
0x04ed,0x1f,
0x04ee,0x0,
0x04ef,0x0,
0x04f0,0x0,
0x04f1,0x0,
0x04f2,0x0,
0x04f3,0x0,
0x04f4,0x0,
0x04f5,0x0,
0x04f6,0x0,
0x04f7,0x0,
0x04f8,0x0,
0x04f9,0x0,
0x04fa,0x0,
0x04fb,0x0,
0x04fd,0x0,
0x04fe,0x0
};
#endif
