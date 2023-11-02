/* options Header */

#ifndef HEADER_OPTIONS_H
#define HEADER_OPTIONS_H

#define OPTIONS_SIZE 5000
#define OPTIONS_PARM_SIZE 10000
#define OPTIONS_ENV_SIZE 1000
#define OPTIONS_MAXCOND 1000

#define OPT_Z   0x00000000
#define OPT_RUN 0x80000000
#define OPT_RTO 0x40000000

#define MAXINT  0x7fffffff

#define OPT_GROUP_SHORT            0x0000
#define OPT_GROUP_CONTROL          0x0100
#define OPT_GROUP_CONDITIONAL      0x0200
#define OPT_GROUP_DEBUGGING        0x0300
#define OPT_GROUP_DISKDRIVES       0x0400
#define OPT_GROUP_DISPLAY          0x0500
#define OPT_GROUP_MODEL            0x0600
#define OPT_GROUP_OSD              0x0700
#define OPT_GROUP_INFORMATION      0x0800
#define OPT_GROUP_PARALLEL_PRINTER 0x0900
#define OPT_GROUP_SERIAL           0x0a00
#define OPT_GROUP_SOUND            0x0b00
#define OPT_GROUP_SPEED            0x0c00
#define OPT_GROUP_TAPE             0x0d00
#define OPT_GROUP_RTC              0x0e00
#define OPT_GROUP_JOYSTICK         0x0f00
#define OPT_GROUP_MOUSE            0x1000
#define OPT_GROUP_APPLICATION      0x1100
#define OPT_GROUP_QUICKLOAD        0x1200
#define OPT_GROUP_PARALLEL_PORT    0x1300
#define OPT_GROUP_COMPUMUSE        0x1400
#define OPT_GROUP_RESERVED         0x1500

// Control related
enum
{
 OPT_ACCOUNT=OPT_GROUP_CONTROL,
 OPT_ALIAS_DISKS,
 OPT_ALIAS_ROMS,
 OPT_ARGS_ERROR,
 OPT_BOOTKEY,
 OPT_CFMODE,
 OPT_CONFIG,
 OPT_CMD_REPEAT1,
 OPT_CMD_REPEAT2,
 OPT_CPU_DELAY,
 OPT_DCLICK,
 OPT_EXIT,
 OPT_EXIT_CHECK,
 OPT_GUI_PERSIST,
 OPT_KEYSTD_MOD,
 OPT_LOCKFIX_WIN32,
 OPT_LOCKFIX_X11,
 OPT_MD5_CREATE,
 OPT_MMODE,
 OPT_MOUSE_WHEEL,
 OPT_NODISK,
 OPT_OPTIONS_WARN,
 OPT_OUTPUT,
 OPT_POWERCYC,
 OPT_PREFIX,
 OPT_RESET,
 OPT_RUNSECS,
 OPT_SDL_PUTENV,
 OPT_SLASHES,
 OPT_SPAD,
 OPT_STATUS,
 OPT_TITLE,
 OPT_VARSET,
 OPT_VARUSET,
 OPT_VERBOSE
};

// Conditional option parsing
enum
{
 OPT_IF_EGT=OPT_GROUP_CONDITIONAL,
 OPT_IF_ELT,
 OPT_IF_EQ,
 OPT_IF_GT,
 OPT_IF_LT,
 OPT_IF_NEGT,
 OPT_IF_NELT,
 OPT_IF_NEQ,
 OPT_IF_NGT,
 OPT_IF_NLT,
 OPT_IF_NSET,
 OPT_IF_SET,
 OPT_IF_SYSTEM,
 OPT_IF_FALSE,
 OPT_IF_TRUE,
 OPT_IF_ELSE,
 OPT_IF_END,
 OPT_IF_CMPMODE
};

// Debugging tools
enum
{
 OPT_BP=OPT_GROUP_DEBUGGING,
 OPT_BPR,
 OPT_BPCLR,
 OPT_BPC,
 OPT_DASM_LINES,
 OPT_DB_BP,
 OPT_DB_BPR,
 OPT_DB_BPCLR,
 OPT_DB_BPOS,
 OPT_DB_BPC,
 OPT_DB_BP_PORT,
 OPT_DB_BPCLR_PORT,
 OPT_DB_BPR_PORT,
 OPT_DB_BP_RST,
 OPT_DB_BPCLR_RST,
 OPT_DB_BPR_RST,
 OPT_DB_BREAK,
 OPT_DB_BP_MEM,
 OPT_DB_BPCLR_MEM,
 OPT_DB_BP_MEML,
 OPT_DB_BPCLR_MEML,
 OPT_DB_CONT,
 OPT_DB_DASM,
 OPT_DB_DASML,
 OPT_DB_DUMP,
 OPT_DB_DUMPB,
 OPT_DB_DUMPL,
 OPT_DB_DUMPLB,
 OPT_DB_DUMPP,
 OPT_DB_DUMPR,
 OPT_DB_FILLB,
 OPT_DB_FILLM,
 OPT_DB_FINDB,
 OPT_DB_FINDM,
 OPT_DB_GO,
 OPT_DB_LOADB,
 OPT_DB_LOADM,
 OPT_DB_MOVE,
 OPT_DB_POPM,
 OPT_DB_POPR,
 OPT_DB_PORTR,
 OPT_DB_PORTW,
 OPT_DB_PUSHM,
 OPT_DB_PUSHR,
 OPT_DB_SAVEB,
 OPT_DB_SAVEM,
 OPT_DB_SETB,
 OPT_DB_SETM,
 OPT_DB_SETR,
 OPT_DB_STEP,
 OPT_DB_TRACE,
 OPT_DB_TRACE_CLR,
 OPT_BREAK,
 OPT_CONT,
 OPT_DEBUG,
 OPT_DEBUG_CLOSE,
 OPT_DEBUG_OPEN,
 OPT_DUMP,
 OPT_DUMP_HEADER,
 OPT_DUMP_LINES,
 OPT_ECHO,
 OPT_ECHOQ,
 OPT_FIND_COUNT,
 OPT_MODIO,
 OPT_REGS
};

// Disk drive images
enum
{
 OPT_DISK_CREATE=OPT_GROUP_DISKDRIVES,
 OPT_HDD0,
 OPT_HDD1,
 OPT_HDD2,
 OPT_HDD3,
 OPT_HDD4,
 OPT_HDD5,
 OPT_HDD6,

 OPT_HDD3_CLOSE,
 OPT_HDD4_CLOSE,
 OPT_HDD5_CLOSE,
 OPT_HDD6_CLOSE,

 OPT_IDE_A0,
 OPT_IDE_A1,
 OPT_IDE_B0,
 OPT_IDE_B1,

 OPT_IMAGE_A,
 OPT_IMAGE_B,
 OPT_IMAGE_C,
 OPT_IMAGE_D,

 OPT_A_CLOSE,
 OPT_B_CLOSE,
 OPT_C_CLOSE,
 OPT_D_CLOSE,

#ifdef USE_LIBDSK
 OPT_CPM3,
 OPT_DSTEP,
 OPT_DSTEP_HD,
 OPT_FORMAT,
 OPT_LFORMAT,
 OPT_LTYPE,
 OPT_SIDE1AS0,
 OPT_TYPE,
#endif

 OPT_PSEC
};

// Display related
enum
{
 OPT_ASPECT=OPT_GROUP_DISPLAY,
 OPT_FULLSCREEN,
 OPT_MONITOR,

 OPT_MON_BG_B,
 OPT_MON_BG_G,
 OPT_MON_BG_R,
 OPT_MON_BGI_B,
 OPT_MON_BGI_G,
 OPT_MON_BGI_R,
 OPT_MON_FG_B,
 OPT_MON_FG_G,
 OPT_MON_FG_R,
 OPT_MON_FGI_B,
 OPT_MON_FGI_G,
 OPT_MON_FGI_R,

 OPT_MON_FGL_B,
 OPT_MON_FGL_G,
 OPT_MON_FGL_R,

 OPT_RGB_00_R,
 OPT_RGB_00_G,
 OPT_RGB_00_B,
 OPT_RGB_01_R,
 OPT_RGB_01_G,
 OPT_RGB_01_B,
 OPT_RGB_02_R,
 OPT_RGB_02_G,
 OPT_RGB_02_B,
 OPT_RGB_03_R,
 OPT_RGB_03_G,
 OPT_RGB_03_B,
 OPT_RGB_04_R,
 OPT_RGB_04_G,
 OPT_RGB_04_B,
 OPT_RGB_05_R,
 OPT_RGB_05_G,
 OPT_RGB_05_B,
 OPT_RGB_06_R,
 OPT_RGB_06_G,
 OPT_RGB_06_B,
 OPT_RGB_07_R,
 OPT_RGB_07_G,
 OPT_RGB_07_B,
 OPT_RGB_08_R,
 OPT_RGB_08_G,
 OPT_RGB_08_B,
 OPT_RGB_09_R,
 OPT_RGB_09_G,
 OPT_RGB_09_B,
 OPT_RGB_10_R,
 OPT_RGB_10_G,
 OPT_RGB_10_B,
 OPT_RGB_11_R,
 OPT_RGB_11_G,
 OPT_RGB_11_B,
 OPT_RGB_12_R,
 OPT_RGB_12_G,
 OPT_RGB_12_B,
 OPT_RGB_13_R,
 OPT_RGB_13_G,
 OPT_RGB_13_B,
 OPT_RGB_14_R,
 OPT_RGB_14_G,
 OPT_RGB_14_B,
 OPT_RGB_15_R,
 OPT_RGB_15_G,
 OPT_RGB_15_B,

 OPT_VIDEO,
 OPT_VIDEO_DEPTH,
 OPT_VIDEO_TYPE,

#ifdef USE_OPENGL
 OPT_GL_ASPECT_BEE,
 OPT_GL_ASPECT_MON,
 OPT_GL_FILTER_FS,
 OPT_GL_FILTER_MAX,
 OPT_GL_FILTER_WIN,
 OPT_GL_MAX,
 OPT_GL_VSYNC,
 OPT_GL_WINPCT,
 OPT_GL_WINPIX
#endif
};

// Model emulation
enum
{
 OPT_BASIC=OPT_GROUP_MODEL,
 OPT_BASICA,
 OPT_BASICB,
 OPT_BASICC,
 OPT_BASICD,

 OPT_BASRAM,
 OPT_CHARROM,
 OPT_COL,
 OPT_COL_TYPE,
 OPT_COLPROM,
 OPT_DINT,
 OPT_HINT,
 OPT_HARDWARE,
 OPT_HWFLASH,
 OPT_HWFLASHR,
 OPT_LMODEL,
 OPT_LPEN,
 OPT_MODEL,
 OPT_MONO,
 OPT_NETRAM,
 OPT_NETROM,

 OPT_PAK0,
 OPT_PAK1,
 OPT_PAK2,
 OPT_PAK3,
 OPT_PAK4,
 OPT_PAK5,
 OPT_PAK6,
 OPT_PAK7,

 OPT_PAKRAM,

 OPT_PCG,
 OPT_PIOB7,
 OPT_PORT58H,

 OPT_ROM1,
 OPT_ROM2,
 OPT_ROM3,

 OPT_ROM256K,

 OPT_SRAM,
 OPT_SRAM_BACKUP, 
 OPT_SRAM_FILE,
 OPT_SRAM_LOAD,
 OPT_SRAM_SAVE,

 OPT_SYS,
 OPT_VDU
};

// On Screen Display (OSD)
enum
{
 OPT_OSD=OPT_GROUP_OSD,
 OPT_OSD_CON_POS,
 OPT_OSD_CON_SIZE,
 OPT_OSD_CURSOR_RATE,
 OPT_OSD_LIST,
 OPT_OSD_SCHEME,
 OPT_OSD_SET_BTN_MAIN,
 OPT_OSD_SET_BTN_TEXT,
 OPT_OSD_SET_DIA_MAIN,
 OPT_OSD_SET_DIA_TEXT,
 OPT_OSD_SET_WID_ICON,
 OPT_OSD_SET_WID_MAIN,
 OPT_OSD_SET_WID_TEXT,
};

// Information output
enum
{
 OPT_CONIO=OPT_GROUP_INFORMATION,
 OPT_HELP,
 OPT_LCON,
 OPT_LCONW,
 OPT_LCONS,
 OPT_USAGE,
 OPT_VERSION
};

// Parallel printer emulation
enum
{
 OPT_PRINT=OPT_GROUP_PARALLEL_PRINTER,
 OPT_PRINT_CLOSE,
 OPT_PRINTA,
 OPT_PRINTA_CLOSE
};

// Compumuse options
enum
{
 OPT_COMPUMUSE_INIT=OPT_GROUP_COMPUMUSE,
 OPT_COMPUMUSE_CLOCK,
};

// Serial port emulation
enum
{
 OPT_BAUD=OPT_GROUP_SERIAL,
 OPT_BAUDRX,
 OPT_BAUDTX,
 OPT_COMS,
 OPT_COMS_CLOSE,
 OPT_DATAB,
 OPT_STOPB
};

// Sound emulation
enum
{
 OPT_SOUND=OPT_GROUP_SOUND,
 OPT_SND_ALG1,
 OPT_SND_FREQ,
 OPT_SND_FREQADJ,
 OPT_SND_FREQLOW,
 OPT_SND_HOLDOFF,
 OPT_SND_HQ,
 OPT_SND_MUTE,
 OPT_SND_SAMPLES,
 OPT_SND_VOLUME,
 OPT_VOL
};

// Speed related
enum
{
 OPT_CLOCK=OPT_GROUP_SPEED,
 OPT_CLOCK_DEF,
 OPT_FRATE,
 OPT_MAXCPULAG,
 OPT_VBLANK,
 OPT_XTAL,
 OPT_SPEEDSEL,
 OPT_TURBO,
 OPT_Z80DIV
};

// Tape port emulation and TAP file support
enum
{
 OPT_TAPEI=OPT_GROUP_TAPE,
 OPT_TAPEI_CLOSE,
 OPT_TAPE_DET,
 OPT_TAPEO,
 OPT_TAPEO_CLOSE,
 OPT_TAPESAMP,
 OPT_TAPEVOL,
 OPT_TAPFILE_LIST,
 OPT_TAPFILEI,
 OPT_TAPFILEI_CLOSE,
 OPT_TAPFILEO,
 OPT_TAPFILEO_CLOSE
};

// Real Time Clock (RTC) emulation and time
enum
{
 OPT_CENTURY=OPT_GROUP_RTC,
 OPT_RTC
};

// Joystick emulation
enum
{
 OPT_JS=OPT_GROUP_JOYSTICK,
 OPT_JS_AXIS,
 OPT_JS_AXISB,
 OPT_JS_AXISL,
 OPT_JS_HAT,
 OPT_JS_HATB,
 OPT_JS_SHIFT,

 OPT_JS_CLEAR,
 OPT_JS_MBEE,
 OPT_JS_UP,
 OPT_JS_RIGHT,
 OPT_JS_DOWN,
 OPT_JS_LEFT,
 OPT_JS_FIRE,
 OPT_JS_PLAY1,
 OPT_JS_PLAY2,
 OPT_JS_SPARE,

 OPT_JS_CLIST,
 OPT_JS_KLIST,
 OPT_JS_KBD,
 OPT_JS_KK,
 OPT_JS_KB,
 OPT_JS_KKB,
 OPT_JS_KSET,
 OPT_JS_KSEL
};

// Mouse emulation
enum
{
 OPT_MOUSE=OPT_GROUP_MOUSE
};

// Application dependent
enum
{
 OPT_FILE_APP=OPT_GROUP_APPLICATION,
 OPT_FILE_EXEC,
 OPT_FILE_EXIT,
 OPT_FILE_LIST,
 OPT_FILE_LIST_Q,
 OPT_FILE_LOAD,
 OPT_FILE_RUN
};

// Parallel port devices which may be connected
enum
{
 OPT_PARALLEL_PORT = OPT_GROUP_PARALLEL_PORT,
};

// Quickload support
enum
{
 OPT_QL_LIST=OPT_GROUP_QUICKLOAD,
 OPT_QL_LOAD,
 OPT_QL_X,
#ifdef USE_ARC
 OPT_QLA_ARC,
 OPT_QLA_DIR,
 OPT_QLA_LIST,
 OPT_QLA_LOAD,
#endif
};

void options_init (void);
void options_make_pointers (char *s);
int options_ubee512_envvar_set (char *s);
int options_process (int argc, char *argv[]);

typedef struct short_options_trans_t
   {
    int option;
    int longno;
   }short_options_trans_t;

typedef struct help_t
   {
    int state;
    int index;
    int lineswanted;
    int lw;
   }help_t;

void options_usage_state (help_t *help);

#endif /* HEADER_OPTIONS_H */