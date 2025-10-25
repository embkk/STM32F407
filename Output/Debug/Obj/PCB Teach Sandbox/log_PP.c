# 1 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/log.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 409 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/log.c" 2
# 1 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/log.h" 1
# 36 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/log.h"
# 1 "/opt/SEGGER/segger_embedded_studio_8.24/include/stdio.h" 1 3
# 20 "/opt/SEGGER/segger_embedded_studio_8.24/include/stdio.h" 3
# 1 "/opt/SEGGER/segger_embedded_studio_8.24/include/__SEGGER_RTL.h" 1 3
# 17 "/opt/SEGGER/segger_embedded_studio_8.24/include/__SEGGER_RTL.h" 3
# 1 "/opt/SEGGER/segger_embedded_studio_8.24/include/__SEGGER_RTL_ConfDefaults.h" 1 3
# 67 "/opt/SEGGER/segger_embedded_studio_8.24/include/__SEGGER_RTL_ConfDefaults.h" 3
# 1 "/opt/SEGGER/segger_embedded_studio_8.24/include/__SEGGER_RTL_Conf.h" 1 3
# 35 "/opt/SEGGER/segger_embedded_studio_8.24/include/__SEGGER_RTL_Conf.h" 3
# 1 "/opt/SEGGER/segger_embedded_studio_8.24/include/__SEGGER_RTL_Arm_Conf.h" 1 3
# 539 "/opt/SEGGER/segger_embedded_studio_8.24/include/__SEGGER_RTL_Arm_Conf.h" 3
  static __inline__ __attribute__((__always_inline__)) int __SEGGER_RTL_CLZ_U32_safe_inline(unsigned x) {
    return x == 0 ? 32 : __builtin_clz(x);
  }
# 748 "/opt/SEGGER/segger_embedded_studio_8.24/include/__SEGGER_RTL_Arm_Conf.h" 3
static __inline__ __attribute__((__always_inline__)) void __SEGGER_RTL_WR_PARTIAL_WORD_func(char *addr, unsigned w, int n) {
  switch (n) {
  default: addr[3] = (-1) > 0 ? w : w >> 24;
  case 3: addr[2] = (-1) > 0 ? w >> 8 : w >> 16;
  case 2: addr[1] = (-1) > 0 ? w >> 16 : w >> 8;
  case 1: addr[0] = (-1) > 0 ? w >> 24 : w;
  case 0: ;
  }
}

static __inline__ __attribute__((__always_inline__)) void __SEGGER_RTL_WR_WORD_func(char *addr, unsigned w) {
  __SEGGER_RTL_WR_PARTIAL_WORD_func(addr, w, 4);
}

static __inline__ __attribute__((__always_inline__)) unsigned __SEGGER_RTL_RD_WORD_func(const void *addr) {
  const unsigned char *pAddr = (const unsigned char *)addr;

  return pAddr[0] * ((-1) > 0 ? 0x1000000u : 0x1u) +
         pAddr[1] * ((-1) > 0 ? 0x10000u : 0x100u) +
         pAddr[2] * ((-1) > 0 ? 0x100u : 0x10000u) +
         pAddr[3] * ((-1) > 0 ? 0x1u : 0x1000000u);
}

static __inline__ __attribute__((__always_inline__)) unsigned __SEGGER_RTL_BYTE_PATTERN_func(unsigned x) {
  return x * 0x01010101uL;
}

static __inline__ __attribute__((__always_inline__)) unsigned __SEGGER_RTL_FILL_HEAD_func(const void *pOrigin, unsigned Word, unsigned Standin) {
  unsigned Mask;
  unsigned Fill;

  (void)pOrigin;

  Fill = __SEGGER_RTL_BYTE_PATTERN_func(Standin);
# 792 "/opt/SEGGER/segger_embedded_studio_8.24/include/__SEGGER_RTL_Arm_Conf.h" 3
  Mask = 0xFFFFFFFFu;
  Mask <<= 8 * 0;

  return (Word & Mask) | (Fill & ~Mask);


}

static __inline__ __attribute__((__always_inline__)) unsigned __SEGGER_RTL_FILL_TAIL_func(unsigned n, unsigned Word, unsigned Standin) {
  unsigned Mask;
  unsigned Fill;
# 817 "/opt/SEGGER/segger_embedded_studio_8.24/include/__SEGGER_RTL_Arm_Conf.h" 3
  if (n >= 4) {
    return Word;
  } else {
    Fill = __SEGGER_RTL_BYTE_PATTERN_func(Standin);
    Mask = 0xFFFFFFFFu << (8 * n);

    return (Fill & Mask) | (Word & ~Mask);
  }


}

static __inline__ __attribute__((__always_inline__)) unsigned __SEGGER_RTL_ZBYTE_CHECK_func(unsigned x) {



  return __builtin_arm_uqsub8(0x01010101, x);






}

static __inline__ __attribute__((__always_inline__)) unsigned __SEGGER_RTL_DIFF_INDEX_func(unsigned x, unsigned y) {



  return __SEGGER_RTL_CLZ_U32_safe_inline(__builtin_arm_rbit(x^y)) / 8;
# 873 "/opt/SEGGER/segger_embedded_studio_8.24/include/__SEGGER_RTL_Arm_Conf.h" 3
}

static __inline__ __attribute__((__always_inline__)) unsigned __SEGGER_RTL_DIFF_BYTE_func(unsigned x, int Index) {



  return (x >> (8*Index)) & 0xFF;

}

static __inline__ __attribute__((__always_inline__)) unsigned __SEGGER_RTL_ZBYTE_INDEX_func(unsigned x) {







  return __SEGGER_RTL_CLZ_U32_safe_inline(__builtin_arm_rbit(__SEGGER_RTL_ZBYTE_CHECK_func(x))) / 8;
# 926 "/opt/SEGGER/segger_embedded_studio_8.24/include/__SEGGER_RTL_Arm_Conf.h" 3
}

static __inline__ __attribute__((__always_inline__)) _Bool __SEGGER_RTL_atomic_is_lock_free(unsigned size, const volatile void *ptr) {
  switch (size) {
  case 1: return 1;
  case 2: return ((unsigned)ptr & 1) == 0;
  case 4: return ((unsigned)ptr & 3) == 0;
  default: return 0;
  }
}
# 946 "/opt/SEGGER/segger_embedded_studio_8.24/include/__SEGGER_RTL_Arm_Conf.h" 3
extern const int __aeabi_SIGABRT;
extern const int __aeabi_SIGINT;
extern const int __aeabi_SIGILL;
extern const int __aeabi_SIGFPE;
extern const int __aeabi_SIGSEGV;
extern const int __aeabi_SIGTERM;

void __aeabi_SIG_DFL(int sig);
void __aeabi_SIG_IGN(int sig);
void __aeabi_SIG_ERR(int sig);
# 36 "/opt/SEGGER/segger_embedded_studio_8.24/include/__SEGGER_RTL_Conf.h" 2 3
# 68 "/opt/SEGGER/segger_embedded_studio_8.24/include/__SEGGER_RTL_ConfDefaults.h" 2 3
# 18 "/opt/SEGGER/segger_embedded_studio_8.24/include/__SEGGER_RTL.h" 2 3
# 38 "/opt/SEGGER/segger_embedded_studio_8.24/include/__SEGGER_RTL.h" 3
  typedef struct __SEGGER_RTL_FILE_impl __SEGGER_RTL_FILE;


typedef struct __SEGGER_RTL_locale_data_s __SEGGER_RTL_locale_t;
typedef struct __SEGGER_RTL_locale_codeset_s __SEGGER_RTL_locale_codeset_t;

typedef struct {



  const char * decimal_point;
  const char * thousands_sep;
  const char * grouping;

  const char * int_curr_symbol;
  const char * currency_symbol;
  const char * mon_decimal_point;
  const char * mon_thousands_sep;
  const char * mon_grouping;
  const char * positive_sign;
  const char * negative_sign;

  char int_frac_digits;
  char frac_digits;
  char p_cs_precedes;
  char p_sep_by_space;
  char n_cs_precedes;
  char n_sep_by_space;
  char p_sign_posn;
  char n_sign_posn;
  char int_p_cs_precedes;
  char int_n_cs_precedes;
  char int_p_sep_by_space;
  char int_n_sep_by_space;
  char int_p_sign_posn;
  char int_n_sign_posn;




  const char *day_names;
  const char *abbrev_day_names;
  const char *month_names;
  const char *abbrev_month_names;
  const char *am_pm_indicator;
  const char *date_format;
  const char *time_format;
  const char *date_time_format;
} __SEGGER_RTL_locale_data_t;

struct __SEGGER_RTL_locale_data_s {
  const char * name;
  const __SEGGER_RTL_locale_data_t * data;
  const __SEGGER_RTL_locale_codeset_t * codeset;
};

struct __SEGGER_RTL_POSIX_locale_s {
  const __SEGGER_RTL_locale_t *__category[5];
};

struct timeval;
# 107 "/opt/SEGGER/segger_embedded_studio_8.24/include/__SEGGER_RTL.h" 3
extern struct __SEGGER_RTL_POSIX_locale_s __SEGGER_RTL_global_locale;
extern struct __SEGGER_RTL_POSIX_locale_s * __SEGGER_RTL_locale_ptr;
extern char * __SEGGER_RTL_locale_name_buffer;
# 118 "/opt/SEGGER/segger_embedded_studio_8.24/include/__SEGGER_RTL.h" 3
extern const __SEGGER_RTL_locale_t __SEGGER_RTL_c_locale;
extern const __SEGGER_RTL_locale_codeset_t __SEGGER_RTL_codeset_iso8859_1;
extern const __SEGGER_RTL_locale_codeset_t __SEGGER_RTL_codeset_iso8859_2;
extern const __SEGGER_RTL_locale_codeset_t __SEGGER_RTL_codeset_iso8859_3;
extern const __SEGGER_RTL_locale_codeset_t __SEGGER_RTL_codeset_iso8859_4;
extern const __SEGGER_RTL_locale_codeset_t __SEGGER_RTL_codeset_iso8859_5;
extern const __SEGGER_RTL_locale_codeset_t __SEGGER_RTL_codeset_iso8859_6;
extern const __SEGGER_RTL_locale_codeset_t __SEGGER_RTL_codeset_iso8859_7;
extern const __SEGGER_RTL_locale_codeset_t __SEGGER_RTL_codeset_iso8859_8;
extern const __SEGGER_RTL_locale_codeset_t __SEGGER_RTL_codeset_iso8859_9;
extern const __SEGGER_RTL_locale_codeset_t __SEGGER_RTL_codeset_iso8859_10;
extern const __SEGGER_RTL_locale_codeset_t __SEGGER_RTL_codeset_iso8859_11;
extern const __SEGGER_RTL_locale_codeset_t __SEGGER_RTL_codeset_iso8859_13;
extern const __SEGGER_RTL_locale_codeset_t __SEGGER_RTL_codeset_iso8859_14;
extern const __SEGGER_RTL_locale_codeset_t __SEGGER_RTL_codeset_iso8859_15;
extern const __SEGGER_RTL_locale_codeset_t __SEGGER_RTL_codeset_iso8859_16;
extern const __SEGGER_RTL_locale_codeset_t __SEGGER_RTL_codeset_cp1250;
extern const __SEGGER_RTL_locale_codeset_t __SEGGER_RTL_codeset_cp1251;
extern const __SEGGER_RTL_locale_codeset_t __SEGGER_RTL_codeset_cp1252;
extern const __SEGGER_RTL_locale_codeset_t __SEGGER_RTL_codeset_cp1253;
extern const __SEGGER_RTL_locale_codeset_t __SEGGER_RTL_codeset_cp1254;
extern const __SEGGER_RTL_locale_codeset_t __SEGGER_RTL_codeset_cp1255;
extern const __SEGGER_RTL_locale_codeset_t __SEGGER_RTL_codeset_cp1256;
extern const __SEGGER_RTL_locale_codeset_t __SEGGER_RTL_codeset_cp1257;
extern const __SEGGER_RTL_locale_codeset_t __SEGGER_RTL_codeset_cp1258;

extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_c_locale_data;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_aa_DJ_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_aa_ER_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_aa_ET_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_af_NA_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_af_ZA_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_ak_GH_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_am_ET_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_ar_AE_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_ar_BH_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_ar_DZ_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_ar_EG_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_ar_IQ_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_ar_JO_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_ar_KW_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_ar_LB_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_ar_LY_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_ar_MA_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_ar_OM_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_ar_QA_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_ar_SA_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_ar_SD_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_ar_SY_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_ar_TN_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_ar_YE_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_as_IN_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_asa_TZ_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_az_Arab_IR_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_az_AZ_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_az_Cyrl_AZ_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_az_IR_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_az_Latn_AZ_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_be_BY_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_bem_ZM_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_bez_TZ_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_bg_BG_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_bm_ML_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_bn_BD_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_bn_IN_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_bo_CN_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_bo_IN_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_br_FR_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_brx_IN_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_bs_BA_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_byn_ER_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_ca_ES_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_cch_NG_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_cgg_UG_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_chr_US_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_cs_CZ_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_cy_GB_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_da_DK_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_dav_KE_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_de_AT_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_de_BE_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_de_CH_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_de_DE_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_de_LI_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_de_LU_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_dv_MV_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_dz_BT_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_ebu_KE_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_ee_GH_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_ee_TG_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_el_CY_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_el_GR_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_en_AS_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_en_AU_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_en_BE_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_en_BW_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_en_BZ_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_en_CA_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_en_Dsrt_US_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_en_GB_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_en_GU_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_en_HK_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_en_IE_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_en_IN_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_en_JM_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_en_MH_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_en_MP_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_en_MT_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_en_MU_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_en_NA_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_en_NZ_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_en_PH_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_en_PK_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_en_SG_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_en_TT_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_en_UM_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_en_US_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_en_US_POSIX_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_en_VI_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_en_ZA_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_en_ZW_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_en_ZZ_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_es_AR_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_es_BO_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_es_CL_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_es_CO_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_es_CR_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_es_DO_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_es_EC_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_es_ES_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_es_GQ_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_es_GT_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_es_HN_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_es_MX_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_es_NI_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_es_PA_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_es_PE_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_es_PR_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_es_PY_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_es_SV_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_es_US_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_es_UY_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_es_VE_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_et_EE_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_eu_ES_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_fa_AF_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_fa_IR_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_ff_SN_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_fi_FI_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_fil_PH_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_fo_FO_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_fr_BE_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_fr_BF_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_fr_BI_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_fr_BJ_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_fr_BL_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_fr_CA_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_fr_CD_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_fr_CF_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_fr_CG_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_fr_CH_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_fr_CI_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_fr_CM_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_fr_DJ_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_fr_FR_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_fr_GA_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_fr_GN_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_fr_GP_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_fr_GQ_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_fr_KM_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_fr_LU_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_fr_MC_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_fr_MF_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_fr_MG_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_fr_ML_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_fr_MQ_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_fr_NE_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_fr_RE_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_fr_RW_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_fr_SN_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_fr_TD_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_fr_TG_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_fur_IT_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_ga_IE_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_gaa_GH_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_gez_ER_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_gez_ET_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_gl_ES_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_gsw_CH_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_gu_IN_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_guz_KE_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_gv_GB_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_ha_Arab_NG_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_ha_Arab_SD_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_ha_GH_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_ha_Latn_GH_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_ha_Latn_NE_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_ha_Latn_NG_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_ha_NE_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_ha_NG_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_ha_SD_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_haw_US_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_he_IL_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_hi_IN_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_hr_HR_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_hu_HU_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_hy_AM_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_id_ID_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_ig_NG_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_ii_CN_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_is_IS_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_it_CH_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_it_IT_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_ja_JP_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_jmc_TZ_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_ka_GE_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_kab_DZ_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_kaj_NG_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_kam_KE_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_kcg_NG_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_kde_TZ_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_kea_CV_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_kfo_CI_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_khq_ML_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_ki_KE_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_kk_Cyrl_KZ_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_kk_KZ_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_kl_GL_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_kln_KE_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_km_KH_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_kn_IN_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_ko_KR_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_kok_IN_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_kpe_GN_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_kpe_LR_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_ksb_TZ_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_ksh_DE_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_ku_Arab_IQ_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_ku_Arab_IR_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_ku_IQ_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_ku_IR_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_ku_Latn_SY_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_ku_Latn_TR_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_ku_SY_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_ku_TR_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_kw_GB_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_ky_KG_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_lag_TZ_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_lg_UG_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_ln_CD_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_ln_CG_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_lo_LA_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_lt_LT_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_luo_KE_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_luy_KE_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_lv_LV_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_mas_KE_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_mas_TZ_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_mer_KE_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_mfe_MU_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_mg_MG_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_mi_NZ_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_mk_MK_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_ml_IN_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_mn_CN_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_mn_Cyrl_MN_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_mn_MN_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_mn_Mong_CN_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_mr_IN_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_ms_BN_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_ms_MY_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_mt_MT_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_my_MM_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_naq_NA_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_nb_NO_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_nd_ZW_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_nds_DE_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_ne_IN_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_ne_NP_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_nl_BE_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_nl_NL_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_nn_NO_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_nr_ZA_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_nso_ZA_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_ny_MW_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_nyn_UG_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_oc_FR_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_om_ET_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_om_KE_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_or_IN_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_pa_Arab_PK_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_pa_Guru_IN_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_pa_IN_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_pa_PK_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_pl_PL_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_ps_AF_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_pt_AO_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_pt_BR_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_pt_GW_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_pt_MZ_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_pt_PT_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_rm_CH_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_ro_MD_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_ro_RO_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_rof_TZ_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_ru_MD_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_ru_RU_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_ru_UA_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_rw_RW_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_rwk_TZ_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_sa_IN_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_saq_KE_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_se_FI_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_se_NO_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_seh_MZ_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_ses_ML_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_sg_CF_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_sh_BA_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_sh_CS_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_sh_YU_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_shi_Latn_MA_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_shi_MA_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_shi_Tfng_MA_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_si_LK_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_sid_ET_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_sk_SK_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_sl_SI_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_sn_ZW_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_so_DJ_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_so_ET_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_so_KE_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_so_SO_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_sq_AL_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_sr_BA_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_sr_CS_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_sr_Cyrl_BA_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_sr_Cyrl_CS_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_sr_Cyrl_ME_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_sr_Cyrl_RS_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_sr_Cyrl_YU_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_sr_Latn_BA_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_sr_Latn_CS_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_sr_Latn_ME_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_sr_Latn_RS_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_sr_Latn_YU_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_sr_ME_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_sr_RS_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_sr_YU_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_ss_SZ_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_ss_ZA_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_ssy_ER_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_st_LS_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_st_ZA_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_sv_FI_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_sv_SE_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_sw_KE_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_sw_TZ_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_syr_SY_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_ta_IN_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_ta_LK_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_te_IN_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_teo_KE_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_teo_UG_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_tg_Cyrl_TJ_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_tg_TJ_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_th_TH_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_ti_ER_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_ti_ET_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_tig_ER_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_tl_PH_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_tn_ZA_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_to_TO_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_tr_TR_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_trv_TW_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_ts_ZA_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_tt_RU_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_tzm_Latn_MA_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_tzm_MA_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_ug_Arab_CN_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_ug_CN_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_uk_UA_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_ur_IN_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_ur_PK_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_uz_AF_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_uz_Arab_AF_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_uz_Cyrl_UZ_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_uz_Latn_UZ_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_uz_UZ_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_ve_ZA_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_vi_VN_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_vun_TZ_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_wal_ET_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_wo_Latn_SN_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_wo_SN_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_xh_ZA_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_xog_UG_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_yo_NG_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_zh_CN_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_zh_Hans_CN_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_zh_Hans_HK_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_zh_Hans_MO_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_zh_Hans_SG_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_zh_Hant_HK_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_zh_Hant_MO_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_zh_Hant_TW_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_zh_HK_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_zh_MO_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_zh_SG_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_zh_TW_locale;
extern const __SEGGER_RTL_locale_data_t __SEGGER_RTL_zu_ZA_locale;

extern const __SEGGER_RTL_locale_codeset_t __SEGGER_RTL_codeset_ascii;
extern const __SEGGER_RTL_locale_codeset_t __SEGGER_RTL_codeset_utf8;

extern const char __SEGGER_RTL_data_utf8_period [];
extern const char __SEGGER_RTL_data_utf8_comma [];
extern const char __SEGGER_RTL_data_utf8_space [];
extern const char __SEGGER_RTL_data_utf8_plus [];
extern const char __SEGGER_RTL_data_utf8_minus [];
extern const char __SEGGER_RTL_data_empty_string[];
# 546 "/opt/SEGGER/segger_embedded_studio_8.24/include/__SEGGER_RTL.h" 3
int __SEGGER_RTL_X_set_time_of_day (const struct timeval *__tp);
int __SEGGER_RTL_X_get_time_of_day (struct timeval *__tp);
const __SEGGER_RTL_locale_t * __SEGGER_RTL_X_find_locale (const char *__locale);
__SEGGER_RTL_FILE * __SEGGER_RTL_X_file_open (const char *__filename, const char *__mode);
__SEGGER_RTL_FILE * __SEGGER_RTL_X_file_dopen (int __descriptor, const char *__mode);
int __SEGGER_RTL_X_file_stat (__SEGGER_RTL_FILE *__stream);
int __SEGGER_RTL_X_file_read (__SEGGER_RTL_FILE *__stream, char *__s, unsigned __len);
int __SEGGER_RTL_X_file_write (__SEGGER_RTL_FILE *__stream, const char *__s, unsigned __len);
int __SEGGER_RTL_X_file_unget (__SEGGER_RTL_FILE *__stream, int __c);
int __SEGGER_RTL_X_file_close (__SEGGER_RTL_FILE *__stream);
int __SEGGER_RTL_X_file_error (__SEGGER_RTL_FILE *__stream);
int __SEGGER_RTL_X_file_flush (__SEGGER_RTL_FILE *__stream);
int __SEGGER_RTL_X_file_eof (__SEGGER_RTL_FILE *__stream);
void __SEGGER_RTL_X_file_clrerr (__SEGGER_RTL_FILE *__stream);
int __SEGGER_RTL_X_file_seek (__SEGGER_RTL_FILE *__stream, long __offset, int __whence);
int __SEGGER_RTL_X_file_getpos (__SEGGER_RTL_FILE *__stream, long *__pos);
int __SEGGER_RTL_X_file_bufsize (__SEGGER_RTL_FILE *__stream);
__SEGGER_RTL_FILE * __SEGGER_RTL_X_file_tmpfile (void);
char * __SEGGER_RTL_X_file_tmpnam (char *__s, unsigned __max);
int __SEGGER_RTL_X_file_remove (const char *__filename);
int __SEGGER_RTL_X_file_rename (const char *__old, const char *__new);
void __attribute__((__weak__)) __SEGGER_RTL_X_heap_lock (void);
void __attribute__((__weak__)) __SEGGER_RTL_X_heap_unlock (void);
int __attribute__((__weak__)) __SEGGER_RTL_X_atomic_lock (void);
void __attribute__((__weak__)) __SEGGER_RTL_X_atomic_unlock (int __state);
int __attribute__((__weak__)) __SEGGER_RTL_X_atomic_is_lock_free (unsigned int __size, void *__ptr);
void __attribute__((__weak__)) __SEGGER_RTL_X_atomic_synchronize (void);
volatile int * __aeabi_errno_addr (void);
void __aeabi_assert (const char *__expression, const char *__filename, int __line);
# 584 "/opt/SEGGER/segger_embedded_studio_8.24/include/__SEGGER_RTL.h" 3
void __SEGGER_RTL_execute_at_exit_fns (void);
void __SEGGER_RTL_set_locale_name_buffer (char *__buffer);
int __SEGGER_RTL_mb_max (const struct __SEGGER_RTL_POSIX_locale_s *__loc);
int __SEGGER_RTL_mb_cur_max (void);
void __SEGGER_RTL_init_heap (void *__ptr, unsigned int __size);
# 21 "/opt/SEGGER/segger_embedded_studio_8.24/include/stdio.h" 2 3
# 72 "/opt/SEGGER/segger_embedded_studio_8.24/include/stdio.h" 3
typedef unsigned int size_t;




typedef long fpos_t;




typedef struct __SEGGER_RTL_FILE_impl FILE;




typedef struct __SEGGER_RTL_POSIX_locale_s *locale_t;
# 97 "/opt/SEGGER/segger_embedded_studio_8.24/include/stdio.h" 3
extern FILE *stdin;
extern FILE *stdout;
extern FILE *stderr;
# 108 "/opt/SEGGER/segger_embedded_studio_8.24/include/stdio.h" 3
int putchar (int __c);
int getchar (void);
int puts (const char *__s);
char * gets (char *__s);
int sprintf (char *__s, const char *__format, ...);
int sprintf_l (char *__s, locale_t __loc, const char *__format, ...);
int snprintf (char *__s, size_t __n, const char *__format, ...);
int snprintf_l (char *__s, size_t __n, locale_t __loc, const char *__format, ...);
int vsnprintf (char *__s, size_t __n, const char *__format, __builtin_va_list __arg);
int vsnprintf_l (char *__s, size_t __n, locale_t __loc, const char *__format, __builtin_va_list __arg);
int printf (const char *__format, ...);
int printf_l (locale_t __loc, const char *__format, ...);
int vprintf (const char *__format, __builtin_va_list __arg);
int vprintf_l (locale_t __loc, const char *__format, __builtin_va_list __arg);
int vsprintf (char *__s, const char *__format, __builtin_va_list __arg);
int vsprintf_l (char *__s, locale_t __loc, const char *__format, __builtin_va_list __arg);
int vasprintf (char **__strp, const char *__format, __builtin_va_list __ap);
int vasprintf_l (char **__strp, locale_t __loc, const char *__format, __builtin_va_list __ap);
int asprintf (char **__strp, const char *__format, ...);
int asprintf_l (char **__strp, locale_t __loc, const char *__format, ...);

int scanf (const char *__format, ...);
int scanf_l (locale_t __loc, const char *__format, ...);
int sscanf (const char *__s, const char *__format, ...);
int sscanf_l (const char *__s, locale_t __loc, const char *__format, ...);
int vscanf (const char *__format, __builtin_va_list __arg);
int vscanf_l (locale_t __loc, const char *__format, __builtin_va_list __arg);
int vsscanf (const char *__s, const char *__format, __builtin_va_list __arg);
int vsscanf_l (const char *__s, locale_t __loc, const char *__format, __builtin_va_list __arg);

void clearerr (FILE *);
int fclose (FILE *);
int feof (FILE *);
int ferror (FILE *);
int fflush (FILE *);
int fgetc (FILE *);
int fgetpos (FILE *, fpos_t *);
char * fgets (char *, int, FILE *);
int fileno (FILE *);
FILE * fopen (const char *, const char *);
int fprintf (FILE *, const char *, ...);
int fprintf_l (FILE *, locale_t, const char *, ...);
int vfprintf (FILE *__stream, const char *__format, __builtin_va_list __arg);
int vfprintf_l (FILE *__stream, locale_t loc, const char *__format, __builtin_va_list __arg);
int fputc (int, FILE *);
int fputs (const char *, FILE *);
size_t fread (void *, size_t, size_t, FILE *);
FILE * freopen (const char *, const char *, FILE *);
int fscanf (FILE *, const char *, ...);
int fscanf_l (FILE *, locale_t, const char *, ...);
int vfscanf (FILE *, const char *, __builtin_va_list);
int vfscanf_l (FILE *, locale_t, const char *, __builtin_va_list);
int fseek (FILE *, long, int);
int fsetpos (FILE *, const fpos_t *);
long ftell (FILE *);
size_t fwrite (const void *, size_t, size_t, FILE *);
int getc (FILE *);
void perror (const char *);
int putc (int, FILE *);
int remove (const char *);
int rename (const char *, const char *);
void rewind (FILE *);
void setbuf (FILE *, char *);
int setvbuf (FILE *, char *, int, size_t);
FILE * tmpfile (void);
char * tmpnam (char *);
int ungetc (int, FILE *);





int dprintf (int, const char *, ...);
int vdprintf (int, const char *, __builtin_va_list);
FILE * fdopen (int, const char *);
# 37 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/log.h" 2
# 1 "/opt/SEGGER/segger_embedded_studio_8.24/include/stdarg.h" 1 3
# 29 "/opt/SEGGER/segger_embedded_studio_8.24/include/stdarg.h" 3
typedef __builtin_va_list va_list;
# 38 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/log.h" 2
# 1 "/opt/SEGGER/segger_embedded_studio_8.24/include/stdint.h" 1 3
# 272 "/opt/SEGGER/segger_embedded_studio_8.24/include/stdint.h" 3
typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef short int16_t;
typedef unsigned short uint16_t;
typedef int int32_t;
typedef unsigned int uint32_t;
typedef long long int int64_t;
typedef long long unsigned int uint64_t;

typedef signed char int_least8_t;
typedef short int_least16_t;
typedef int int_least32_t;
typedef long long int int_least64_t;
typedef unsigned char uint_least8_t;
typedef unsigned short uint_least16_t;
typedef unsigned int uint_least32_t;
typedef long long unsigned int uint_least64_t;

typedef signed char int_fast8_t;
typedef short int_fast16_t;
typedef int int_fast32_t;
typedef long long int int_fast64_t;
typedef unsigned char uint_fast8_t;
typedef unsigned short uint_fast16_t;
typedef unsigned int uint_fast32_t;
typedef long long unsigned int uint_fast64_t;

typedef int intptr_t;
typedef unsigned int uintptr_t;

typedef long long int intmax_t;
typedef long long unsigned int uintmax_t;
# 39 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/log.h" 2
# 55 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/log.h"
typedef struct {
    char message0[50]; char message1[50]; char message2[50]; char message3[50]; char message4[50]; char message5[50]; char message6[50]; char message7[50]; char message8[50]; char message9[50]; char message10[50]; char message11[50]; char message12[50]; char message13[50]; char message14[50]; char message15[50]; char message16[50]; char message17[50]; char message18[50]; char message19[50]; char message20[50]; char message21[50]; char message22[50]; char message23[50]; char message24[50]; char message25[50]; char message26[50]; char message27[50]; char message28[50]; char message29[50]; char message30[50]; char message31[50]; char message32[50]; char message33[50]; char message34[50]; char message35[50]; char message36[50]; char message37[50]; char message38[50]; char message39[50]; char message40[50]; char message41[50]; char message42[50]; char message43[50]; char message44[50]; char message45[50]; char message46[50]; char message47[50]; char message48[50]; char message49[50]; char message50[50]; char message51[50]; char message52[50]; char message53[50]; char message54[50]; char message55[50]; char message56[50]; char message57[50]; char message58[50]; char message59[50]; char message60[50]; char message61[50]; char message62[50]; char message63[50]; char message64[50]; char message65[50]; char message66[50]; char message67[50]; char message68[50]; char message69[50]; char message70[50]; char message71[50]; char message72[50]; char message73[50]; char message74[50]; char message75[50]; char message76[50]; char message77[50]; char message78[50]; char message79[50]; char message80[50]; char message81[50]; char message82[50]; char message83[50]; char message84[50]; char message85[50]; char message86[50]; char message87[50]; char message88[50]; char message89[50]; char message90[50]; char message91[50]; char message92[50]; char message93[50]; char message94[50]; char message95[50]; char message96[50]; char message97[50]; char message98[50]; char message99[50];
} log_t;


extern log_t Log;
# 2 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/log.c" 2




  log_t Log;
  uint8_t log_current_index = 0;

  void log_init_internal(void) { { void log_message_internal(const char*, ...); log_message_internal("Log init finished. %p, %p", sizeof(Log)); } }

  void log_message_internal(const char* format, ...) {
      if (log_current_index >= 100) {
          return;
      }


      char (*messages)[50] = (char (*)[50])&Log;
      char* target = messages[log_current_index];


      va_list args;
      __builtin_va_start((args), format);
      vsnprintf(target, 50, format, args);
      __builtin_va_end(args);


      log_current_index = (log_current_index + 1) % 50;
  }
