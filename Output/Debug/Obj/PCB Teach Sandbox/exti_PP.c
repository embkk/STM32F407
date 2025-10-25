# 1 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/exti.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 409 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/exti.c" 2
# 1 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/exti.h" 1



# 1 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/validation.h" 1
# 5 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/exti.h" 2
# 2 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/exti.c" 2
# 1 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/test.h" 1
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
# 2 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/test.h" 2
# 3 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/exti.c" 2
# 1 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/STM32F4xx/Device/Include/stm32f407xx.h" 1
# 65 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/STM32F4xx/Device/Include/stm32f407xx.h"
typedef enum
{

  NonMaskableInt_IRQn = -14,
  MemoryManagement_IRQn = -12,
  BusFault_IRQn = -11,
  UsageFault_IRQn = -10,
  SVCall_IRQn = -5,
  DebugMonitor_IRQn = -4,
  PendSV_IRQn = -2,
  SysTick_IRQn = -1,

  WWDG_IRQn = 0,
  PVD_IRQn = 1,
  TAMP_STAMP_IRQn = 2,
  RTC_WKUP_IRQn = 3,
  FLASH_IRQn = 4,
  RCC_IRQn = 5,
  EXTI0_IRQn = 6,
  EXTI1_IRQn = 7,
  EXTI2_IRQn = 8,
  EXTI3_IRQn = 9,
  EXTI4_IRQn = 10,
  DMA1_Stream0_IRQn = 11,
  DMA1_Stream1_IRQn = 12,
  DMA1_Stream2_IRQn = 13,
  DMA1_Stream3_IRQn = 14,
  DMA1_Stream4_IRQn = 15,
  DMA1_Stream5_IRQn = 16,
  DMA1_Stream6_IRQn = 17,
  ADC_IRQn = 18,
  CAN1_TX_IRQn = 19,
  CAN1_RX0_IRQn = 20,
  CAN1_RX1_IRQn = 21,
  CAN1_SCE_IRQn = 22,
  EXTI9_5_IRQn = 23,
  TIM1_BRK_TIM9_IRQn = 24,
  TIM1_UP_TIM10_IRQn = 25,
  TIM1_TRG_COM_TIM11_IRQn = 26,
  TIM1_CC_IRQn = 27,
  TIM2_IRQn = 28,
  TIM3_IRQn = 29,
  TIM4_IRQn = 30,
  I2C1_EV_IRQn = 31,
  I2C1_ER_IRQn = 32,
  I2C2_EV_IRQn = 33,
  I2C2_ER_IRQn = 34,
  SPI1_IRQn = 35,
  SPI2_IRQn = 36,
  USART1_IRQn = 37,
  USART2_IRQn = 38,
  USART3_IRQn = 39,
  EXTI15_10_IRQn = 40,
  RTC_Alarm_IRQn = 41,
  OTG_FS_WKUP_IRQn = 42,
  TIM8_BRK_TIM12_IRQn = 43,
  TIM8_UP_TIM13_IRQn = 44,
  TIM8_TRG_COM_TIM14_IRQn = 45,
  TIM8_CC_IRQn = 46,
  DMA1_Stream7_IRQn = 47,
  FSMC_IRQn = 48,
  SDIO_IRQn = 49,
  TIM5_IRQn = 50,
  SPI3_IRQn = 51,
  UART4_IRQn = 52,
  UART5_IRQn = 53,
  TIM6_DAC_IRQn = 54,
  TIM7_IRQn = 55,
  DMA2_Stream0_IRQn = 56,
  DMA2_Stream1_IRQn = 57,
  DMA2_Stream2_IRQn = 58,
  DMA2_Stream3_IRQn = 59,
  DMA2_Stream4_IRQn = 60,
  ETH_IRQn = 61,
  ETH_WKUP_IRQn = 62,
  CAN2_TX_IRQn = 63,
  CAN2_RX0_IRQn = 64,
  CAN2_RX1_IRQn = 65,
  CAN2_SCE_IRQn = 66,
  OTG_FS_IRQn = 67,
  DMA2_Stream5_IRQn = 68,
  DMA2_Stream6_IRQn = 69,
  DMA2_Stream7_IRQn = 70,
  USART6_IRQn = 71,
  I2C3_EV_IRQn = 72,
  I2C3_ER_IRQn = 73,
  OTG_HS_EP1_OUT_IRQn = 74,
  OTG_HS_EP1_IN_IRQn = 75,
  OTG_HS_WKUP_IRQn = 76,
  OTG_HS_IRQn = 77,
  DCMI_IRQn = 78,
  RNG_IRQn = 80,
  FPU_IRQn = 81
} IRQn_Type;







# 1 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/CMSIS_5/CMSIS/Core/Include/core_cm4.h" 1
# 29 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/CMSIS_5/CMSIS/Core/Include/core_cm4.h" 3





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
# 35 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/CMSIS_5/CMSIS/Core/Include/core_cm4.h" 2 3
# 63 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/CMSIS_5/CMSIS/Core/Include/core_cm4.h" 3
# 1 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/CMSIS_5/CMSIS/Core/Include/cmsis_version.h" 1 3
# 29 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/CMSIS_5/CMSIS/Core/Include/cmsis_version.h" 3
# 64 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/CMSIS_5/CMSIS/Core/Include/core_cm4.h" 2 3
# 162 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/CMSIS_5/CMSIS/Core/Include/core_cm4.h" 3
# 1 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/CMSIS_5/CMSIS/Core/Include/cmsis_compiler.h" 1 3
# 54 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/CMSIS_5/CMSIS/Core/Include/cmsis_compiler.h" 3
# 1 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/CMSIS_5/CMSIS/Core/Include/cmsis_gcc.h" 1 3
# 29 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/CMSIS_5/CMSIS/Core/Include/cmsis_gcc.h" 3
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-conversion"
#pragma GCC diagnostic ignored "-Wconversion"
#pragma GCC diagnostic ignored "-Wunused-parameter"
# 71 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/CMSIS_5/CMSIS/Core/Include/cmsis_gcc.h" 3
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpacked"
#pragma GCC diagnostic ignored "-Wattributes"
  struct __attribute__((packed)) T_UINT32 { uint32_t v; };
#pragma GCC diagnostic pop



#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpacked"
#pragma GCC diagnostic ignored "-Wattributes"
  struct __attribute__((packed, aligned(1))) T_UINT16_WRITE { uint16_t v; };
#pragma GCC diagnostic pop



#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpacked"
#pragma GCC diagnostic ignored "-Wattributes"
  struct __attribute__((packed, aligned(1))) T_UINT16_READ { uint16_t v; };
#pragma GCC diagnostic pop



#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpacked"
#pragma GCC diagnostic ignored "-Wattributes"
  struct __attribute__((packed, aligned(1))) T_UINT32_WRITE { uint32_t v; };
#pragma GCC diagnostic pop



#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpacked"
#pragma GCC diagnostic ignored "-Wattributes"
  struct __attribute__((packed, aligned(1))) T_UINT32_READ { uint32_t v; };
#pragma GCC diagnostic pop
# 131 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/CMSIS_5/CMSIS/Core/Include/cmsis_gcc.h" 3
__attribute__((always_inline)) static inline __attribute__((__noreturn__)) void __cmsis_start(void)
{
  extern void _start(void) __attribute__((__noreturn__));

  typedef struct {
    uint32_t const* src;
    uint32_t* dest;
    uint32_t wlen;
  } __copy_table_t;

  typedef struct {
    uint32_t* dest;
    uint32_t wlen;
  } __zero_table_t;

  extern const __copy_table_t __copy_table_start__;
  extern const __copy_table_t __copy_table_end__;
  extern const __zero_table_t __zero_table_start__;
  extern const __zero_table_t __zero_table_end__;

  for (__copy_table_t const* pTable = &__copy_table_start__; pTable < &__copy_table_end__; ++pTable) {
    for(uint32_t i=0u; i<pTable->wlen; ++i) {
      pTable->dest[i] = pTable->src[i];
    }
  }

  for (__zero_table_t const* pTable = &__zero_table_start__; pTable < &__zero_table_end__; ++pTable) {
    for(uint32_t i=0u; i<pTable->wlen; ++i) {
      pTable->dest[i] = 0u;
    }
  }

  _start();
}
# 258 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/CMSIS_5/CMSIS/Core/Include/cmsis_gcc.h" 3
__attribute__((always_inline)) static inline void __ISB(void)
{
  __asm volatile ("isb 0xF":::"memory");
}







__attribute__((always_inline)) static inline void __DSB(void)
{
  __asm volatile ("dsb 0xF":::"memory");
}







__attribute__((always_inline)) static inline void __DMB(void)
{
  __asm volatile ("dmb 0xF":::"memory");
}
# 292 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/CMSIS_5/CMSIS/Core/Include/cmsis_gcc.h" 3
__attribute__((always_inline)) static inline uint32_t __REV(uint32_t value)
{



  uint32_t result;

  __asm ("rev %0, %1" : "=r" (result) : "r" (value) );
  return result;

}
# 311 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/CMSIS_5/CMSIS/Core/Include/cmsis_gcc.h" 3
__attribute__((always_inline)) static inline uint32_t __REV16(uint32_t value)
{
  uint32_t result;

  __asm ("rev16 %0, %1" : "=r" (result) : "r" (value) );
  return result;
}
# 326 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/CMSIS_5/CMSIS/Core/Include/cmsis_gcc.h" 3
__attribute__((always_inline)) static inline int16_t __REVSH(int16_t value)
{



  int16_t result;

  __asm ("revsh %0, %1" : "=r" (result) : "r" (value) );
  return result;

}
# 346 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/CMSIS_5/CMSIS/Core/Include/cmsis_gcc.h" 3
__attribute__((always_inline)) static inline uint32_t __ROR(uint32_t op1, uint32_t op2)
{
  op2 %= 32U;
  if (op2 == 0U)
  {
    return op1;
  }
  return (op1 >> op2) | (op1 << (32U - op2));
}
# 373 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/CMSIS_5/CMSIS/Core/Include/cmsis_gcc.h" 3
__attribute__((always_inline)) static inline uint32_t __RBIT(uint32_t value)
{
  uint32_t result;




   __asm ("rbit %0, %1" : "=r" (result) : "r" (value) );
# 393 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/CMSIS_5/CMSIS/Core/Include/cmsis_gcc.h" 3
  return result;
}
# 403 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/CMSIS_5/CMSIS/Core/Include/cmsis_gcc.h" 3
__attribute__((always_inline)) static inline uint8_t __CLZ(uint32_t value)
{
# 414 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/CMSIS_5/CMSIS/Core/Include/cmsis_gcc.h" 3
  if (value == 0U)
  {
    return 32U;
  }
  return __builtin_clz(value);
}
# 432 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/CMSIS_5/CMSIS/Core/Include/cmsis_gcc.h" 3
__attribute__((always_inline)) static inline uint8_t __LDREXB(volatile uint8_t *addr)
{
    uint32_t result;







   __asm volatile ("ldrexb %0, [%1]" : "=r" (result) : "r" (addr) : "memory" );

   return ((uint8_t) result);
}
# 454 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/CMSIS_5/CMSIS/Core/Include/cmsis_gcc.h" 3
__attribute__((always_inline)) static inline uint16_t __LDREXH(volatile uint16_t *addr)
{
    uint32_t result;







   __asm volatile ("ldrexh %0, [%1]" : "=r" (result) : "r" (addr) : "memory" );

   return ((uint16_t) result);
}
# 476 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/CMSIS_5/CMSIS/Core/Include/cmsis_gcc.h" 3
__attribute__((always_inline)) static inline uint32_t __LDREXW(volatile uint32_t *addr)
{
    uint32_t result;

   __asm volatile ("ldrex %0, %1" : "=r" (result) : "Q" (*addr) );
   return(result);
}
# 493 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/CMSIS_5/CMSIS/Core/Include/cmsis_gcc.h" 3
__attribute__((always_inline)) static inline uint32_t __STREXB(uint8_t value, volatile uint8_t *addr)
{
   uint32_t result;

   __asm volatile ("strexb %0, %2, %1" : "=&r" (result), "=Q" (*addr) : "r" ((uint32_t)value) );
   return(result);
}
# 510 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/CMSIS_5/CMSIS/Core/Include/cmsis_gcc.h" 3
__attribute__((always_inline)) static inline uint32_t __STREXH(uint16_t value, volatile uint16_t *addr)
{
   uint32_t result;

   __asm volatile ("strexh %0, %2, %1" : "=&r" (result), "=Q" (*addr) : "r" ((uint32_t)value) );
   return(result);
}
# 527 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/CMSIS_5/CMSIS/Core/Include/cmsis_gcc.h" 3
__attribute__((always_inline)) static inline uint32_t __STREXW(uint32_t value, volatile uint32_t *addr)
{
   uint32_t result;

   __asm volatile ("strex %0, %2, %1" : "=&r" (result), "=Q" (*addr) : "r" (value) );
   return(result);
}






__attribute__((always_inline)) static inline void __CLREX(void)
{
  __asm volatile ("clrex" ::: "memory");
}
# 593 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/CMSIS_5/CMSIS/Core/Include/cmsis_gcc.h" 3
__attribute__((always_inline)) static inline uint32_t __RRX(uint32_t value)
{
  uint32_t result;

  __asm volatile ("rrx %0, %1" : "=r" (result) : "r" (value) );
  return(result);
}
# 608 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/CMSIS_5/CMSIS/Core/Include/cmsis_gcc.h" 3
__attribute__((always_inline)) static inline uint8_t __LDRBT(volatile uint8_t *ptr)
{
    uint32_t result;







   __asm volatile ("ldrbt %0, [%1]" : "=r" (result) : "r" (ptr) : "memory" );

   return ((uint8_t) result);
}
# 630 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/CMSIS_5/CMSIS/Core/Include/cmsis_gcc.h" 3
__attribute__((always_inline)) static inline uint16_t __LDRHT(volatile uint16_t *ptr)
{
    uint32_t result;







   __asm volatile ("ldrht %0, [%1]" : "=r" (result) : "r" (ptr) : "memory" );

   return ((uint16_t) result);
}
# 652 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/CMSIS_5/CMSIS/Core/Include/cmsis_gcc.h" 3
__attribute__((always_inline)) static inline uint32_t __LDRT(volatile uint32_t *ptr)
{
    uint32_t result;

   __asm volatile ("ldrt %0, %1" : "=r" (result) : "Q" (*ptr) );
   return(result);
}
# 667 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/CMSIS_5/CMSIS/Core/Include/cmsis_gcc.h" 3
__attribute__((always_inline)) static inline void __STRBT(uint8_t value, volatile uint8_t *ptr)
{
   __asm volatile ("strbt %1, %0" : "=Q" (*ptr) : "r" ((uint32_t)value) );
}
# 679 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/CMSIS_5/CMSIS/Core/Include/cmsis_gcc.h" 3
__attribute__((always_inline)) static inline void __STRHT(uint16_t value, volatile uint16_t *ptr)
{
   __asm volatile ("strht %1, %0" : "=Q" (*ptr) : "r" ((uint32_t)value) );
}
# 691 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/CMSIS_5/CMSIS/Core/Include/cmsis_gcc.h" 3
__attribute__((always_inline)) static inline void __STRT(uint32_t value, volatile uint32_t *ptr)
{
   __asm volatile ("strt %1, %0" : "=Q" (*ptr) : "r" (value) );
}
# 949 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/CMSIS_5/CMSIS/Core/Include/cmsis_gcc.h" 3
__attribute__((always_inline)) static inline void __enable_irq(void)
{
  __asm volatile ("cpsie i" : : : "memory");
}







__attribute__((always_inline)) static inline void __disable_irq(void)
{
  __asm volatile ("cpsid i" : : : "memory");
}







__attribute__((always_inline)) static inline uint32_t __get_CONTROL(void)
{
  uint32_t result;

  __asm volatile ("MRS %0, control" : "=r" (result) );
  return(result);
}
# 1001 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/CMSIS_5/CMSIS/Core/Include/cmsis_gcc.h" 3
__attribute__((always_inline)) static inline void __set_CONTROL(uint32_t control)
{
  __asm volatile ("MSR control, %0" : : "r" (control) : "memory");
  __ISB();
}
# 1027 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/CMSIS_5/CMSIS/Core/Include/cmsis_gcc.h" 3
__attribute__((always_inline)) static inline uint32_t __get_IPSR(void)
{
  uint32_t result;

  __asm volatile ("MRS %0, ipsr" : "=r" (result) );
  return(result);
}







__attribute__((always_inline)) static inline uint32_t __get_APSR(void)
{
  uint32_t result;

  __asm volatile ("MRS %0, apsr" : "=r" (result) );
  return(result);
}







__attribute__((always_inline)) static inline uint32_t __get_xPSR(void)
{
  uint32_t result;

  __asm volatile ("MRS %0, xpsr" : "=r" (result) );
  return(result);
}







__attribute__((always_inline)) static inline uint32_t __get_PSP(void)
{
  uint32_t result;

  __asm volatile ("MRS %0, psp" : "=r" (result) );
  return(result);
}
# 1099 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/CMSIS_5/CMSIS/Core/Include/cmsis_gcc.h" 3
__attribute__((always_inline)) static inline void __set_PSP(uint32_t topOfProcStack)
{
  __asm volatile ("MSR psp, %0" : : "r" (topOfProcStack) : );
}
# 1123 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/CMSIS_5/CMSIS/Core/Include/cmsis_gcc.h" 3
__attribute__((always_inline)) static inline uint32_t __get_MSP(void)
{
  uint32_t result;

  __asm volatile ("MRS %0, msp" : "=r" (result) );
  return(result);
}
# 1153 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/CMSIS_5/CMSIS/Core/Include/cmsis_gcc.h" 3
__attribute__((always_inline)) static inline void __set_MSP(uint32_t topOfMainStack)
{
  __asm volatile ("MSR msp, %0" : : "r" (topOfMainStack) : );
}
# 1204 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/CMSIS_5/CMSIS/Core/Include/cmsis_gcc.h" 3
__attribute__((always_inline)) static inline uint32_t __get_PRIMASK(void)
{
  uint32_t result;

  __asm volatile ("MRS %0, primask" : "=r" (result) );
  return(result);
}
# 1234 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/CMSIS_5/CMSIS/Core/Include/cmsis_gcc.h" 3
__attribute__((always_inline)) static inline void __set_PRIMASK(uint32_t priMask)
{
  __asm volatile ("MSR primask, %0" : : "r" (priMask) : "memory");
}
# 1261 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/CMSIS_5/CMSIS/Core/Include/cmsis_gcc.h" 3
__attribute__((always_inline)) static inline void __enable_fault_irq(void)
{
  __asm volatile ("cpsie f" : : : "memory");
}







__attribute__((always_inline)) static inline void __disable_fault_irq(void)
{
  __asm volatile ("cpsid f" : : : "memory");
}







__attribute__((always_inline)) static inline uint32_t __get_BASEPRI(void)
{
  uint32_t result;

  __asm volatile ("MRS %0, basepri" : "=r" (result) );
  return(result);
}
# 1313 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/CMSIS_5/CMSIS/Core/Include/cmsis_gcc.h" 3
__attribute__((always_inline)) static inline void __set_BASEPRI(uint32_t basePri)
{
  __asm volatile ("MSR basepri, %0" : : "r" (basePri) : "memory");
}
# 1338 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/CMSIS_5/CMSIS/Core/Include/cmsis_gcc.h" 3
__attribute__((always_inline)) static inline void __set_BASEPRI_MAX(uint32_t basePri)
{
  __asm volatile ("MSR basepri_max, %0" : : "r" (basePri) : "memory");
}







__attribute__((always_inline)) static inline uint32_t __get_FAULTMASK(void)
{
  uint32_t result;

  __asm volatile ("MRS %0, faultmask" : "=r" (result) );
  return(result);
}
# 1379 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/CMSIS_5/CMSIS/Core/Include/cmsis_gcc.h" 3
__attribute__((always_inline)) static inline void __set_FAULTMASK(uint32_t faultMask)
{
  __asm volatile ("MSR faultmask, %0" : : "r" (faultMask) : "memory");
}
# 1588 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/CMSIS_5/CMSIS/Core/Include/cmsis_gcc.h" 3
__attribute__((always_inline)) static inline uint32_t __get_FPSCR(void)
{






  return __builtin_arm_get_fpscr();
# 1606 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/CMSIS_5/CMSIS/Core/Include/cmsis_gcc.h" 3
}







__attribute__((always_inline)) static inline void __set_FPSCR(uint32_t fpscr)
{






  __builtin_arm_set_fpscr(fpscr);






}
# 1643 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/CMSIS_5/CMSIS/Core/Include/cmsis_gcc.h" 3
__attribute__((always_inline)) static inline uint32_t __SADD8(uint32_t op1, uint32_t op2)
{
  uint32_t result;

  __asm volatile ("sadd8 %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2) );
  return(result);
}

__attribute__((always_inline)) static inline uint32_t __QADD8(uint32_t op1, uint32_t op2)
{
  uint32_t result;

  __asm ("qadd8 %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2) );
  return(result);
}

__attribute__((always_inline)) static inline uint32_t __SHADD8(uint32_t op1, uint32_t op2)
{
  uint32_t result;

  __asm ("shadd8 %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2) );
  return(result);
}

__attribute__((always_inline)) static inline uint32_t __UADD8(uint32_t op1, uint32_t op2)
{
  uint32_t result;

  __asm volatile ("uadd8 %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2) );
  return(result);
}

__attribute__((always_inline)) static inline uint32_t __UQADD8(uint32_t op1, uint32_t op2)
{
  uint32_t result;

  __asm ("uqadd8 %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2) );
  return(result);
}

__attribute__((always_inline)) static inline uint32_t __UHADD8(uint32_t op1, uint32_t op2)
{
  uint32_t result;

  __asm ("uhadd8 %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2) );
  return(result);
}


__attribute__((always_inline)) static inline uint32_t __SSUB8(uint32_t op1, uint32_t op2)
{
  uint32_t result;

  __asm volatile ("ssub8 %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2) );
  return(result);
}

__attribute__((always_inline)) static inline uint32_t __QSUB8(uint32_t op1, uint32_t op2)
{
  uint32_t result;

  __asm ("qsub8 %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2) );
  return(result);
}

__attribute__((always_inline)) static inline uint32_t __SHSUB8(uint32_t op1, uint32_t op2)
{
  uint32_t result;

  __asm ("shsub8 %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2) );
  return(result);
}

__attribute__((always_inline)) static inline uint32_t __USUB8(uint32_t op1, uint32_t op2)
{
  uint32_t result;

  __asm volatile ("usub8 %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2) );
  return(result);
}

__attribute__((always_inline)) static inline uint32_t __UQSUB8(uint32_t op1, uint32_t op2)
{
  uint32_t result;

  __asm ("uqsub8 %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2) );
  return(result);
}

__attribute__((always_inline)) static inline uint32_t __UHSUB8(uint32_t op1, uint32_t op2)
{
  uint32_t result;

  __asm ("uhsub8 %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2) );
  return(result);
}


__attribute__((always_inline)) static inline uint32_t __SADD16(uint32_t op1, uint32_t op2)
{
  uint32_t result;

  __asm volatile ("sadd16 %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2) );
  return(result);
}

__attribute__((always_inline)) static inline uint32_t __QADD16(uint32_t op1, uint32_t op2)
{
  uint32_t result;

  __asm ("qadd16 %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2) );
  return(result);
}

__attribute__((always_inline)) static inline uint32_t __SHADD16(uint32_t op1, uint32_t op2)
{
  uint32_t result;

  __asm ("shadd16 %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2) );
  return(result);
}

__attribute__((always_inline)) static inline uint32_t __UADD16(uint32_t op1, uint32_t op2)
{
  uint32_t result;

  __asm volatile ("uadd16 %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2) );
  return(result);
}

__attribute__((always_inline)) static inline uint32_t __UQADD16(uint32_t op1, uint32_t op2)
{
  uint32_t result;

  __asm ("uqadd16 %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2) );
  return(result);
}

__attribute__((always_inline)) static inline uint32_t __UHADD16(uint32_t op1, uint32_t op2)
{
  uint32_t result;

  __asm ("uhadd16 %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2) );
  return(result);
}

__attribute__((always_inline)) static inline uint32_t __SSUB16(uint32_t op1, uint32_t op2)
{
  uint32_t result;

  __asm volatile ("ssub16 %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2) );
  return(result);
}

__attribute__((always_inline)) static inline uint32_t __QSUB16(uint32_t op1, uint32_t op2)
{
  uint32_t result;

  __asm ("qsub16 %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2) );
  return(result);
}

__attribute__((always_inline)) static inline uint32_t __SHSUB16(uint32_t op1, uint32_t op2)
{
  uint32_t result;

  __asm ("shsub16 %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2) );
  return(result);
}

__attribute__((always_inline)) static inline uint32_t __USUB16(uint32_t op1, uint32_t op2)
{
  uint32_t result;

  __asm volatile ("usub16 %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2) );
  return(result);
}

__attribute__((always_inline)) static inline uint32_t __UQSUB16(uint32_t op1, uint32_t op2)
{
  uint32_t result;

  __asm ("uqsub16 %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2) );
  return(result);
}

__attribute__((always_inline)) static inline uint32_t __UHSUB16(uint32_t op1, uint32_t op2)
{
  uint32_t result;

  __asm ("uhsub16 %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2) );
  return(result);
}

__attribute__((always_inline)) static inline uint32_t __SASX(uint32_t op1, uint32_t op2)
{
  uint32_t result;

  __asm volatile ("sasx %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2) );
  return(result);
}

__attribute__((always_inline)) static inline uint32_t __QASX(uint32_t op1, uint32_t op2)
{
  uint32_t result;

  __asm ("qasx %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2) );
  return(result);
}

__attribute__((always_inline)) static inline uint32_t __SHASX(uint32_t op1, uint32_t op2)
{
  uint32_t result;

  __asm ("shasx %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2) );
  return(result);
}

__attribute__((always_inline)) static inline uint32_t __UASX(uint32_t op1, uint32_t op2)
{
  uint32_t result;

  __asm volatile ("uasx %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2) );
  return(result);
}

__attribute__((always_inline)) static inline uint32_t __UQASX(uint32_t op1, uint32_t op2)
{
  uint32_t result;

  __asm ("uqasx %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2) );
  return(result);
}

__attribute__((always_inline)) static inline uint32_t __UHASX(uint32_t op1, uint32_t op2)
{
  uint32_t result;

  __asm ("uhasx %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2) );
  return(result);
}

__attribute__((always_inline)) static inline uint32_t __SSAX(uint32_t op1, uint32_t op2)
{
  uint32_t result;

  __asm volatile ("ssax %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2) );
  return(result);
}

__attribute__((always_inline)) static inline uint32_t __QSAX(uint32_t op1, uint32_t op2)
{
  uint32_t result;

  __asm ("qsax %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2) );
  return(result);
}

__attribute__((always_inline)) static inline uint32_t __SHSAX(uint32_t op1, uint32_t op2)
{
  uint32_t result;

  __asm ("shsax %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2) );
  return(result);
}

__attribute__((always_inline)) static inline uint32_t __USAX(uint32_t op1, uint32_t op2)
{
  uint32_t result;

  __asm volatile ("usax %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2) );
  return(result);
}

__attribute__((always_inline)) static inline uint32_t __UQSAX(uint32_t op1, uint32_t op2)
{
  uint32_t result;

  __asm ("uqsax %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2) );
  return(result);
}

__attribute__((always_inline)) static inline uint32_t __UHSAX(uint32_t op1, uint32_t op2)
{
  uint32_t result;

  __asm ("uhsax %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2) );
  return(result);
}

__attribute__((always_inline)) static inline uint32_t __USAD8(uint32_t op1, uint32_t op2)
{
  uint32_t result;

  __asm ("usad8 %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2) );
  return(result);
}

__attribute__((always_inline)) static inline uint32_t __USADA8(uint32_t op1, uint32_t op2, uint32_t op3)
{
  uint32_t result;

  __asm ("usada8 %0, %1, %2, %3" : "=r" (result) : "r" (op1), "r" (op2), "r" (op3) );
  return(result);
}
# 1965 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/CMSIS_5/CMSIS/Core/Include/cmsis_gcc.h" 3
__attribute__((always_inline)) static inline uint32_t __UXTB16(uint32_t op1)
{
  uint32_t result;

  __asm ("uxtb16 %0, %1" : "=r" (result) : "r" (op1));
  return(result);
}

__attribute__((always_inline)) static inline uint32_t __UXTAB16(uint32_t op1, uint32_t op2)
{
  uint32_t result;

  __asm ("uxtab16 %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2) );
  return(result);
}

__attribute__((always_inline)) static inline uint32_t __SXTB16(uint32_t op1)
{
  uint32_t result;

  __asm ("sxtb16 %0, %1" : "=r" (result) : "r" (op1));
  return(result);
}

__attribute__((always_inline)) static inline uint32_t __SXTB16_RORn(uint32_t op1, uint32_t rotate)
{
  uint32_t result;
  if (__builtin_constant_p(rotate) && ((rotate == 8U) || (rotate == 16U) || (rotate == 24U))) {
    __asm volatile ("sxtb16 %0, %1, ROR %2" : "=r" (result) : "r" (op1), "i" (rotate) );
  } else {
    result = __SXTB16(__ROR(op1, rotate)) ;
  }
  return result;
}

__attribute__((always_inline)) static inline uint32_t __SXTAB16(uint32_t op1, uint32_t op2)
{
  uint32_t result;

  __asm ("sxtab16 %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2) );
  return(result);
}

__attribute__((always_inline)) static inline uint32_t __SXTAB16_RORn(uint32_t op1, uint32_t op2, uint32_t rotate)
{
  uint32_t result;
  if (__builtin_constant_p(rotate) && ((rotate == 8U) || (rotate == 16U) || (rotate == 24U))) {
    __asm volatile ("sxtab16 %0, %1, %2, ROR %3" : "=r" (result) : "r" (op1) , "r" (op2) , "i" (rotate));
  } else {
    result = __SXTAB16(op1, __ROR(op2, rotate));
  }
  return result;
}


__attribute__((always_inline)) static inline uint32_t __SMUAD (uint32_t op1, uint32_t op2)
{
  uint32_t result;

  __asm volatile ("smuad %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2) );
  return(result);
}

__attribute__((always_inline)) static inline uint32_t __SMUADX (uint32_t op1, uint32_t op2)
{
  uint32_t result;

  __asm volatile ("smuadx %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2) );
  return(result);
}

__attribute__((always_inline)) static inline uint32_t __SMLAD (uint32_t op1, uint32_t op2, uint32_t op3)
{
  uint32_t result;

  __asm volatile ("smlad %0, %1, %2, %3" : "=r" (result) : "r" (op1), "r" (op2), "r" (op3) );
  return(result);
}

__attribute__((always_inline)) static inline uint32_t __SMLADX (uint32_t op1, uint32_t op2, uint32_t op3)
{
  uint32_t result;

  __asm volatile ("smladx %0, %1, %2, %3" : "=r" (result) : "r" (op1), "r" (op2), "r" (op3) );
  return(result);
}

__attribute__((always_inline)) static inline uint64_t __SMLALD (uint32_t op1, uint32_t op2, uint64_t acc)
{
  union llreg_u{
    uint32_t w32[2];
    uint64_t w64;
  } llr;
  llr.w64 = acc;


  __asm volatile ("smlald %0, %1, %2, %3" : "=r" (llr.w32[0]), "=r" (llr.w32[1]): "r" (op1), "r" (op2) , "0" (llr.w32[0]), "1" (llr.w32[1]) );




  return(llr.w64);
}

__attribute__((always_inline)) static inline uint64_t __SMLALDX (uint32_t op1, uint32_t op2, uint64_t acc)
{
  union llreg_u{
    uint32_t w32[2];
    uint64_t w64;
  } llr;
  llr.w64 = acc;


  __asm volatile ("smlaldx %0, %1, %2, %3" : "=r" (llr.w32[0]), "=r" (llr.w32[1]): "r" (op1), "r" (op2) , "0" (llr.w32[0]), "1" (llr.w32[1]) );




  return(llr.w64);
}

__attribute__((always_inline)) static inline uint32_t __SMUSD (uint32_t op1, uint32_t op2)
{
  uint32_t result;

  __asm volatile ("smusd %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2) );
  return(result);
}

__attribute__((always_inline)) static inline uint32_t __SMUSDX (uint32_t op1, uint32_t op2)
{
  uint32_t result;

  __asm volatile ("smusdx %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2) );
  return(result);
}

__attribute__((always_inline)) static inline uint32_t __SMLSD (uint32_t op1, uint32_t op2, uint32_t op3)
{
  uint32_t result;

  __asm volatile ("smlsd %0, %1, %2, %3" : "=r" (result) : "r" (op1), "r" (op2), "r" (op3) );
  return(result);
}

__attribute__((always_inline)) static inline uint32_t __SMLSDX (uint32_t op1, uint32_t op2, uint32_t op3)
{
  uint32_t result;

  __asm volatile ("smlsdx %0, %1, %2, %3" : "=r" (result) : "r" (op1), "r" (op2), "r" (op3) );
  return(result);
}

__attribute__((always_inline)) static inline uint64_t __SMLSLD (uint32_t op1, uint32_t op2, uint64_t acc)
{
  union llreg_u{
    uint32_t w32[2];
    uint64_t w64;
  } llr;
  llr.w64 = acc;


  __asm volatile ("smlsld %0, %1, %2, %3" : "=r" (llr.w32[0]), "=r" (llr.w32[1]): "r" (op1), "r" (op2) , "0" (llr.w32[0]), "1" (llr.w32[1]) );




  return(llr.w64);
}

__attribute__((always_inline)) static inline uint64_t __SMLSLDX (uint32_t op1, uint32_t op2, uint64_t acc)
{
  union llreg_u{
    uint32_t w32[2];
    uint64_t w64;
  } llr;
  llr.w64 = acc;


  __asm volatile ("smlsldx %0, %1, %2, %3" : "=r" (llr.w32[0]), "=r" (llr.w32[1]): "r" (op1), "r" (op2) , "0" (llr.w32[0]), "1" (llr.w32[1]) );




  return(llr.w64);
}

__attribute__((always_inline)) static inline uint32_t __SEL (uint32_t op1, uint32_t op2)
{
  uint32_t result;

  __asm volatile ("sel %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2) );
  return(result);
}

__attribute__((always_inline)) static inline int32_t __QADD( int32_t op1, int32_t op2)
{
  int32_t result;

  __asm volatile ("qadd %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2) );
  return(result);
}

__attribute__((always_inline)) static inline int32_t __QSUB( int32_t op1, int32_t op2)
{
  int32_t result;

  __asm volatile ("qsub %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2) );
  return(result);
}
# 2197 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/CMSIS_5/CMSIS/Core/Include/cmsis_gcc.h" 3
__attribute__((always_inline)) static inline int32_t __SMMLA (int32_t op1, int32_t op2, int32_t op3)
{
 int32_t result;

 __asm ("smmla %0, %1, %2, %3" : "=r" (result): "r" (op1), "r" (op2), "r" (op3) );
 return(result);
}





#pragma GCC diagnostic pop
# 55 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/CMSIS_5/CMSIS/Core/Include/cmsis_compiler.h" 2 3
# 163 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/CMSIS_5/CMSIS/Core/Include/core_cm4.h" 2 3
# 264 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/CMSIS_5/CMSIS/Core/Include/core_cm4.h" 3
typedef union
{
  struct
  {
    uint32_t _reserved0:16;
    uint32_t GE:4;
    uint32_t _reserved1:7;
    uint32_t Q:1;
    uint32_t V:1;
    uint32_t C:1;
    uint32_t Z:1;
    uint32_t N:1;
  } b;
  uint32_t w;
} APSR_Type;
# 303 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/CMSIS_5/CMSIS/Core/Include/core_cm4.h" 3
typedef union
{
  struct
  {
    uint32_t ISR:9;
    uint32_t _reserved0:23;
  } b;
  uint32_t w;
} IPSR_Type;
# 321 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/CMSIS_5/CMSIS/Core/Include/core_cm4.h" 3
typedef union
{
  struct
  {
    uint32_t ISR:9;
    uint32_t _reserved0:1;
    uint32_t ICI_IT_1:6;
    uint32_t GE:4;
    uint32_t _reserved1:4;
    uint32_t T:1;
    uint32_t ICI_IT_2:2;
    uint32_t Q:1;
    uint32_t V:1;
    uint32_t C:1;
    uint32_t Z:1;
    uint32_t N:1;
  } b;
  uint32_t w;
} xPSR_Type;
# 376 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/CMSIS_5/CMSIS/Core/Include/core_cm4.h" 3
typedef union
{
  struct
  {
    uint32_t nPRIV:1;
    uint32_t SPSEL:1;
    uint32_t FPCA:1;
    uint32_t _reserved0:29;
  } b;
  uint32_t w;
} CONTROL_Type;
# 411 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/CMSIS_5/CMSIS/Core/Include/core_cm4.h" 3
typedef struct
{
  volatile uint32_t ISER[8U];
        uint32_t RESERVED0[24U];
  volatile uint32_t ICER[8U];
        uint32_t RESERVED1[24U];
  volatile uint32_t ISPR[8U];
        uint32_t RESERVED2[24U];
  volatile uint32_t ICPR[8U];
        uint32_t RESERVED3[24U];
  volatile uint32_t IABR[8U];
        uint32_t RESERVED4[56U];
  volatile uint8_t IP[240U];
        uint32_t RESERVED5[644U];
  volatile uint32_t STIR;
} NVIC_Type;
# 445 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/CMSIS_5/CMSIS/Core/Include/core_cm4.h" 3
typedef struct
{
  volatile const uint32_t CPUID;
  volatile uint32_t ICSR;
  volatile uint32_t VTOR;
  volatile uint32_t AIRCR;
  volatile uint32_t SCR;
  volatile uint32_t CCR;
  volatile uint8_t SHP[12U];
  volatile uint32_t SHCSR;
  volatile uint32_t CFSR;
  volatile uint32_t HFSR;
  volatile uint32_t DFSR;
  volatile uint32_t MMFAR;
  volatile uint32_t BFAR;
  volatile uint32_t AFSR;
  volatile const uint32_t PFR[2U];
  volatile const uint32_t DFR;
  volatile const uint32_t ADR;
  volatile const uint32_t MMFR[4U];
  volatile const uint32_t ISAR[5U];
        uint32_t RESERVED0[5U];
  volatile uint32_t CPACR;
} SCB_Type;
# 724 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/CMSIS_5/CMSIS/Core/Include/core_cm4.h" 3
typedef struct
{
        uint32_t RESERVED0[1U];
  volatile const uint32_t ICTR;
  volatile uint32_t ACTLR;
} SCnSCB_Type;
# 764 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/CMSIS_5/CMSIS/Core/Include/core_cm4.h" 3
typedef struct
{
  volatile uint32_t CTRL;
  volatile uint32_t LOAD;
  volatile uint32_t VAL;
  volatile const uint32_t CALIB;
} SysTick_Type;
# 816 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/CMSIS_5/CMSIS/Core/Include/core_cm4.h" 3
typedef struct
{
  volatile union
  {
    volatile uint8_t u8;
    volatile uint16_t u16;
    volatile uint32_t u32;
  } PORT [32U];
        uint32_t RESERVED0[864U];
  volatile uint32_t TER;
        uint32_t RESERVED1[15U];
  volatile uint32_t TPR;
        uint32_t RESERVED2[15U];
  volatile uint32_t TCR;
        uint32_t RESERVED3[32U];
        uint32_t RESERVED4[43U];
  volatile uint32_t LAR;
  volatile const uint32_t LSR;
        uint32_t RESERVED5[6U];
  volatile const uint32_t PID4;
  volatile const uint32_t PID5;
  volatile const uint32_t PID6;
  volatile const uint32_t PID7;
  volatile const uint32_t PID0;
  volatile const uint32_t PID1;
  volatile const uint32_t PID2;
  volatile const uint32_t PID3;
  volatile const uint32_t CID0;
  volatile const uint32_t CID1;
  volatile const uint32_t CID2;
  volatile const uint32_t CID3;
} ITM_Type;
# 904 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/CMSIS_5/CMSIS/Core/Include/core_cm4.h" 3
typedef struct
{
  volatile uint32_t CTRL;
  volatile uint32_t CYCCNT;
  volatile uint32_t CPICNT;
  volatile uint32_t EXCCNT;
  volatile uint32_t SLEEPCNT;
  volatile uint32_t LSUCNT;
  volatile uint32_t FOLDCNT;
  volatile const uint32_t PCSR;
  volatile uint32_t COMP0;
  volatile uint32_t MASK0;
  volatile uint32_t FUNCTION0;
        uint32_t RESERVED0[1U];
  volatile uint32_t COMP1;
  volatile uint32_t MASK1;
  volatile uint32_t FUNCTION1;
        uint32_t RESERVED1[1U];
  volatile uint32_t COMP2;
  volatile uint32_t MASK2;
  volatile uint32_t FUNCTION2;
        uint32_t RESERVED2[1U];
  volatile uint32_t COMP3;
  volatile uint32_t MASK3;
  volatile uint32_t FUNCTION3;
} DWT_Type;
# 1051 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/CMSIS_5/CMSIS/Core/Include/core_cm4.h" 3
typedef struct
{
  volatile const uint32_t SSPSR;
  volatile uint32_t CSPSR;
        uint32_t RESERVED0[2U];
  volatile uint32_t ACPR;
        uint32_t RESERVED1[55U];
  volatile uint32_t SPPR;
        uint32_t RESERVED2[131U];
  volatile const uint32_t FFSR;
  volatile uint32_t FFCR;
  volatile const uint32_t FSCR;
        uint32_t RESERVED3[759U];
  volatile const uint32_t TRIGGER;
  volatile const uint32_t FIFO0;
  volatile const uint32_t ITATBCTR2;
        uint32_t RESERVED4[1U];
  volatile const uint32_t ITATBCTR0;
  volatile const uint32_t FIFO1;
  volatile uint32_t ITCTRL;
        uint32_t RESERVED5[39U];
  volatile uint32_t CLAIMSET;
  volatile uint32_t CLAIMCLR;
        uint32_t RESERVED7[8U];
  volatile const uint32_t DEVID;
  volatile const uint32_t DEVTYPE;
} TPI_Type;
# 1213 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/CMSIS_5/CMSIS/Core/Include/core_cm4.h" 3
typedef struct
{
  volatile const uint32_t TYPE;
  volatile uint32_t CTRL;
  volatile uint32_t RNR;
  volatile uint32_t RBAR;
  volatile uint32_t RASR;
  volatile uint32_t RBAR_A1;
  volatile uint32_t RASR_A1;
  volatile uint32_t RBAR_A2;
  volatile uint32_t RASR_A2;
  volatile uint32_t RBAR_A3;
  volatile uint32_t RASR_A3;
} MPU_Type;
# 1309 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/CMSIS_5/CMSIS/Core/Include/core_cm4.h" 3
typedef struct
{
        uint32_t RESERVED0[1U];
  volatile uint32_t FPCCR;
  volatile uint32_t FPCAR;
  volatile uint32_t FPDSCR;
  volatile const uint32_t MVFR0;
  volatile const uint32_t MVFR1;
  volatile const uint32_t MVFR2;
} FPU_Type;
# 1421 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/CMSIS_5/CMSIS/Core/Include/core_cm4.h" 3
typedef struct
{
  volatile uint32_t DHCSR;
  volatile uint32_t DCRSR;
  volatile uint32_t DCRDR;
  volatile uint32_t DEMCR;
} CoreDebug_Type;
# 1653 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/CMSIS_5/CMSIS/Core/Include/core_cm4.h" 3
static inline void __NVIC_SetPriorityGrouping(uint32_t PriorityGroup)
{
  uint32_t reg_value;
  uint32_t PriorityGroupTmp = (PriorityGroup & (uint32_t)0x07UL);

  reg_value = ((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->AIRCR;
  reg_value &= ~((uint32_t)((0xFFFFUL << 16U) | (7UL << 8U)));
  reg_value = (reg_value |
                ((uint32_t)0x5FAUL << 16U) |
                (PriorityGroupTmp << 8U) );
  ((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->AIRCR = reg_value;
}







static inline uint32_t __NVIC_GetPriorityGrouping(void)
{
  return ((uint32_t)((((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->AIRCR & (7UL << 8U)) >> 8U));
}
# 1684 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/CMSIS_5/CMSIS/Core/Include/core_cm4.h" 3
static inline void __NVIC_EnableIRQ(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    __asm volatile("":::"memory");
    ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ISER[(((uint32_t)IRQn) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)IRQn) & 0x1FUL));
    __asm volatile("":::"memory");
  }
}
# 1703 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/CMSIS_5/CMSIS/Core/Include/core_cm4.h" 3
static inline uint32_t __NVIC_GetEnableIRQ(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    return((uint32_t)(((((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ISER[(((uint32_t)IRQn) >> 5UL)] & (1UL << (((uint32_t)IRQn) & 0x1FUL))) != 0UL) ? 1UL : 0UL));
  }
  else
  {
    return(0U);
  }
}
# 1722 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/CMSIS_5/CMSIS/Core/Include/core_cm4.h" 3
static inline void __NVIC_DisableIRQ(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ICER[(((uint32_t)IRQn) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)IRQn) & 0x1FUL));
    __DSB();
    __ISB();
  }
}
# 1741 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/CMSIS_5/CMSIS/Core/Include/core_cm4.h" 3
static inline uint32_t __NVIC_GetPendingIRQ(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    return((uint32_t)(((((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ISPR[(((uint32_t)IRQn) >> 5UL)] & (1UL << (((uint32_t)IRQn) & 0x1FUL))) != 0UL) ? 1UL : 0UL));
  }
  else
  {
    return(0U);
  }
}
# 1760 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/CMSIS_5/CMSIS/Core/Include/core_cm4.h" 3
static inline void __NVIC_SetPendingIRQ(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ISPR[(((uint32_t)IRQn) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)IRQn) & 0x1FUL));
  }
}
# 1775 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/CMSIS_5/CMSIS/Core/Include/core_cm4.h" 3
static inline void __NVIC_ClearPendingIRQ(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ICPR[(((uint32_t)IRQn) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)IRQn) & 0x1FUL));
  }
}
# 1792 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/CMSIS_5/CMSIS/Core/Include/core_cm4.h" 3
static inline uint32_t __NVIC_GetActive(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    return((uint32_t)(((((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->IABR[(((uint32_t)IRQn) >> 5UL)] & (1UL << (((uint32_t)IRQn) & 0x1FUL))) != 0UL) ? 1UL : 0UL));
  }
  else
  {
    return(0U);
  }
}
# 1814 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/CMSIS_5/CMSIS/Core/Include/core_cm4.h" 3
static inline void __NVIC_SetPriority(IRQn_Type IRQn, uint32_t priority)
{
  if ((int32_t)(IRQn) >= 0)
  {
    ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->IP[((uint32_t)IRQn)] = (uint8_t)((priority << (8U - 4U)) & (uint32_t)0xFFUL);
  }
  else
  {
    ((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->SHP[(((uint32_t)IRQn) & 0xFUL)-4UL] = (uint8_t)((priority << (8U - 4U)) & (uint32_t)0xFFUL);
  }
}
# 1836 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/CMSIS_5/CMSIS/Core/Include/core_cm4.h" 3
static inline uint32_t __NVIC_GetPriority(IRQn_Type IRQn)
{

  if ((int32_t)(IRQn) >= 0)
  {
    return(((uint32_t)((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->IP[((uint32_t)IRQn)] >> (8U - 4U)));
  }
  else
  {
    return(((uint32_t)((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->SHP[(((uint32_t)IRQn) & 0xFUL)-4UL] >> (8U - 4U)));
  }
}
# 1861 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/CMSIS_5/CMSIS/Core/Include/core_cm4.h" 3
static inline uint32_t NVIC_EncodePriority (uint32_t PriorityGroup, uint32_t PreemptPriority, uint32_t SubPriority)
{
  uint32_t PriorityGroupTmp = (PriorityGroup & (uint32_t)0x07UL);
  uint32_t PreemptPriorityBits;
  uint32_t SubPriorityBits;

  PreemptPriorityBits = ((7UL - PriorityGroupTmp) > (uint32_t)(4U)) ? (uint32_t)(4U) : (uint32_t)(7UL - PriorityGroupTmp);
  SubPriorityBits = ((PriorityGroupTmp + (uint32_t)(4U)) < (uint32_t)7UL) ? (uint32_t)0UL : (uint32_t)((PriorityGroupTmp - 7UL) + (uint32_t)(4U));

  return (
           ((PreemptPriority & (uint32_t)((1UL << (PreemptPriorityBits)) - 1UL)) << SubPriorityBits) |
           ((SubPriority & (uint32_t)((1UL << (SubPriorityBits )) - 1UL)))
         );
}
# 1888 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/CMSIS_5/CMSIS/Core/Include/core_cm4.h" 3
static inline void NVIC_DecodePriority (uint32_t Priority, uint32_t PriorityGroup, uint32_t* const pPreemptPriority, uint32_t* const pSubPriority)
{
  uint32_t PriorityGroupTmp = (PriorityGroup & (uint32_t)0x07UL);
  uint32_t PreemptPriorityBits;
  uint32_t SubPriorityBits;

  PreemptPriorityBits = ((7UL - PriorityGroupTmp) > (uint32_t)(4U)) ? (uint32_t)(4U) : (uint32_t)(7UL - PriorityGroupTmp);
  SubPriorityBits = ((PriorityGroupTmp + (uint32_t)(4U)) < (uint32_t)7UL) ? (uint32_t)0UL : (uint32_t)((PriorityGroupTmp - 7UL) + (uint32_t)(4U));

  *pPreemptPriority = (Priority >> SubPriorityBits) & (uint32_t)((1UL << (PreemptPriorityBits)) - 1UL);
  *pSubPriority = (Priority ) & (uint32_t)((1UL << (SubPriorityBits )) - 1UL);
}
# 1911 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/CMSIS_5/CMSIS/Core/Include/core_cm4.h" 3
static inline void __NVIC_SetVector(IRQn_Type IRQn, uint32_t vector)
{
  uint32_t *vectors = (uint32_t *)((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->VTOR;
  vectors[(int32_t)IRQn + 16] = vector;

}
# 1927 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/CMSIS_5/CMSIS/Core/Include/core_cm4.h" 3
static inline uint32_t __NVIC_GetVector(IRQn_Type IRQn)
{
  uint32_t *vectors = (uint32_t *)((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->VTOR;
  return vectors[(int32_t)IRQn + 16];
}






__attribute__((__noreturn__)) static inline void __NVIC_SystemReset(void)
{
  __DSB();

  ((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->AIRCR = (uint32_t)((0x5FAUL << 16U) |
                           (((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->AIRCR & (7UL << 8U)) |
                            (1UL << 2U) );
  __DSB();

  for(;;)
  {
    __asm volatile ("nop");
  }
}
# 1960 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/CMSIS_5/CMSIS/Core/Include/core_cm4.h" 3
# 1 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/CMSIS_5/CMSIS/Core/Include/mpu_armv7.h" 1 3
# 29 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/CMSIS_5/CMSIS/Core/Include/mpu_armv7.h" 3
# 183 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/CMSIS_5/CMSIS/Core/Include/mpu_armv7.h" 3
typedef struct {
  uint32_t RBAR;
  uint32_t RASR;
} ARM_MPU_Region_t;




static inline void ARM_MPU_Enable(uint32_t MPU_Control)
{
  __DMB();
  ((MPU_Type *) ((0xE000E000UL) + 0x0D90UL) )->CTRL = MPU_Control | (1UL );

  ((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->SHCSR |= (1UL << 16U);

  __DSB();
  __ISB();
}



static inline void ARM_MPU_Disable(void)
{
  __DMB();

  ((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->SHCSR &= ~(1UL << 16U);

  ((MPU_Type *) ((0xE000E000UL) + 0x0D90UL) )->CTRL &= ~(1UL );
  __DSB();
  __ISB();
}




static inline void ARM_MPU_ClrRegion(uint32_t rnr)
{
  ((MPU_Type *) ((0xE000E000UL) + 0x0D90UL) )->RNR = rnr;
  ((MPU_Type *) ((0xE000E000UL) + 0x0D90UL) )->RASR = 0U;
}





static inline void ARM_MPU_SetRegion(uint32_t rbar, uint32_t rasr)
{
  ((MPU_Type *) ((0xE000E000UL) + 0x0D90UL) )->RBAR = rbar;
  ((MPU_Type *) ((0xE000E000UL) + 0x0D90UL) )->RASR = rasr;
}






static inline void ARM_MPU_SetRegionEx(uint32_t rnr, uint32_t rbar, uint32_t rasr)
{
  ((MPU_Type *) ((0xE000E000UL) + 0x0D90UL) )->RNR = rnr;
  ((MPU_Type *) ((0xE000E000UL) + 0x0D90UL) )->RBAR = rbar;
  ((MPU_Type *) ((0xE000E000UL) + 0x0D90UL) )->RASR = rasr;
}






static inline void ARM_MPU_OrderedMemcpy(volatile uint32_t* dst, const uint32_t* __restrict src, uint32_t len)
{
  uint32_t i;
  for (i = 0U; i < len; ++i)
  {
    dst[i] = src[i];
  }
}





static inline void ARM_MPU_Load(ARM_MPU_Region_t const* table, uint32_t cnt)
{
  const uint32_t rowWordSize = sizeof(ARM_MPU_Region_t)/4U;
  while (cnt > 4U) {
    ARM_MPU_OrderedMemcpy(&(((MPU_Type *) ((0xE000E000UL) + 0x0D90UL) )->RBAR), &(table->RBAR), 4U*rowWordSize);
    table += 4U;
    cnt -= 4U;
  }
  ARM_MPU_OrderedMemcpy(&(((MPU_Type *) ((0xE000E000UL) + 0x0D90UL) )->RBAR), &(table->RBAR), cnt*rowWordSize);
}
# 1961 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/CMSIS_5/CMSIS/Core/Include/core_cm4.h" 2 3
# 1981 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/CMSIS_5/CMSIS/Core/Include/core_cm4.h" 3
static inline uint32_t SCB_GetFPUType(void)
{
  uint32_t mvfr0;

  mvfr0 = ((FPU_Type *) ((0xE000E000UL) + 0x0F30UL) )->MVFR0;
  if ((mvfr0 & ((0xFUL << 4U) | (0xFUL << 8U))) == 0x020U)
  {
    return 1U;
  }
  else
  {
    return 0U;
  }
}
# 2022 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/CMSIS_5/CMSIS/Core/Include/core_cm4.h" 3
static inline uint32_t SysTick_Config(uint32_t ticks)
{
  if ((ticks - 1UL) > (0xFFFFFFUL ))
  {
    return (1UL);
  }

  ((SysTick_Type *) ((0xE000E000UL) + 0x0010UL) )->LOAD = (uint32_t)(ticks - 1UL);
  __NVIC_SetPriority (SysTick_IRQn, (1UL << 4U) - 1UL);
  ((SysTick_Type *) ((0xE000E000UL) + 0x0010UL) )->VAL = 0UL;
  ((SysTick_Type *) ((0xE000E000UL) + 0x0010UL) )->CTRL = (1UL << 2U) |
                   (1UL << 1U) |
                   (1UL );
  return (0UL);
}
# 2052 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/CMSIS_5/CMSIS/Core/Include/core_cm4.h" 3
extern volatile int32_t ITM_RxBuffer;
# 2064 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/CMSIS_5/CMSIS/Core/Include/core_cm4.h" 3
static inline uint32_t ITM_SendChar (uint32_t ch)
{
  if (((((ITM_Type *) (0xE0000000UL) )->TCR & (1UL )) != 0UL) &&
      ((((ITM_Type *) (0xE0000000UL) )->TER & 1UL ) != 0UL) )
  {
    while (((ITM_Type *) (0xE0000000UL) )->PORT[0U].u32 == 0UL)
    {
      __asm volatile ("nop");
    }
    ((ITM_Type *) (0xE0000000UL) )->PORT[0U].u8 = (uint8_t)ch;
  }
  return (ch);
}
# 2085 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/CMSIS_5/CMSIS/Core/Include/core_cm4.h" 3
static inline int32_t ITM_ReceiveChar (void)
{
  int32_t ch = -1;

  if (ITM_RxBuffer != ((int32_t)0x5AA55AA5U))
  {
    ch = ITM_RxBuffer;
    ITM_RxBuffer = ((int32_t)0x5AA55AA5U);
  }

  return (ch);
}
# 2105 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/CMSIS_5/CMSIS/Core/Include/core_cm4.h" 3
static inline int32_t ITM_CheckChar (void)
{

  if (ITM_RxBuffer == ((int32_t)0x5AA55AA5U))
  {
    return (0);
  }
  else
  {
    return (1);
  }
}
# 167 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/STM32F4xx/Device/Include/stm32f407xx.h" 2
# 1 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/STM32F4xx/Device/Include/system_stm32f4xx.h" 1
# 57 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/STM32F4xx/Device/Include/system_stm32f4xx.h"
extern uint32_t SystemCoreClock;

extern const uint8_t AHBPrescTable[16];
extern const uint8_t APBPrescTable[8];
# 86 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/STM32F4xx/Device/Include/system_stm32f4xx.h"
extern void SystemInit(void);
extern void SystemCoreClockUpdate(void);
# 168 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/STM32F4xx/Device/Include/stm32f407xx.h" 2
# 178 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/STM32F4xx/Device/Include/stm32f407xx.h"
typedef struct
{
  volatile uint32_t SR;
  volatile uint32_t CR1;
  volatile uint32_t CR2;
  volatile uint32_t SMPR1;
  volatile uint32_t SMPR2;
  volatile uint32_t JOFR1;
  volatile uint32_t JOFR2;
  volatile uint32_t JOFR3;
  volatile uint32_t JOFR4;
  volatile uint32_t HTR;
  volatile uint32_t LTR;
  volatile uint32_t SQR1;
  volatile uint32_t SQR2;
  volatile uint32_t SQR3;
  volatile uint32_t JSQR;
  volatile uint32_t JDR1;
  volatile uint32_t JDR2;
  volatile uint32_t JDR3;
  volatile uint32_t JDR4;
  volatile uint32_t DR;
} ADC_TypeDef;

typedef struct
{
  volatile uint32_t CSR;
  volatile uint32_t CCR;
  volatile uint32_t CDR;

} ADC_Common_TypeDef;






typedef struct
{
  volatile uint32_t TIR;
  volatile uint32_t TDTR;
  volatile uint32_t TDLR;
  volatile uint32_t TDHR;
} CAN_TxMailBox_TypeDef;





typedef struct
{
  volatile uint32_t RIR;
  volatile uint32_t RDTR;
  volatile uint32_t RDLR;
  volatile uint32_t RDHR;
} CAN_FIFOMailBox_TypeDef;





typedef struct
{
  volatile uint32_t FR1;
  volatile uint32_t FR2;
} CAN_FilterRegister_TypeDef;





typedef struct
{
  volatile uint32_t MCR;
  volatile uint32_t MSR;
  volatile uint32_t TSR;
  volatile uint32_t RF0R;
  volatile uint32_t RF1R;
  volatile uint32_t IER;
  volatile uint32_t ESR;
  volatile uint32_t BTR;
  uint32_t RESERVED0[88];
  CAN_TxMailBox_TypeDef sTxMailBox[3];
  CAN_FIFOMailBox_TypeDef sFIFOMailBox[2];
  uint32_t RESERVED1[12];
  volatile uint32_t FMR;
  volatile uint32_t FM1R;
  uint32_t RESERVED2;
  volatile uint32_t FS1R;
  uint32_t RESERVED3;
  volatile uint32_t FFA1R;
  uint32_t RESERVED4;
  volatile uint32_t FA1R;
  uint32_t RESERVED5[8];
  CAN_FilterRegister_TypeDef sFilterRegister[28];
} CAN_TypeDef;





typedef struct
{
  volatile uint32_t DR;
  volatile uint8_t IDR;
  uint8_t RESERVED0;
  uint16_t RESERVED1;
  volatile uint32_t CR;
} CRC_TypeDef;





typedef struct
{
  volatile uint32_t CR;
  volatile uint32_t SWTRIGR;
  volatile uint32_t DHR12R1;
  volatile uint32_t DHR12L1;
  volatile uint32_t DHR8R1;
  volatile uint32_t DHR12R2;
  volatile uint32_t DHR12L2;
  volatile uint32_t DHR8R2;
  volatile uint32_t DHR12RD;
  volatile uint32_t DHR12LD;
  volatile uint32_t DHR8RD;
  volatile uint32_t DOR1;
  volatile uint32_t DOR2;
  volatile uint32_t SR;
} DAC_TypeDef;





typedef struct
{
  volatile uint32_t IDCODE;
  volatile uint32_t CR;
  volatile uint32_t APB1FZ;
  volatile uint32_t APB2FZ;
}DBGMCU_TypeDef;





typedef struct
{
  volatile uint32_t CR;
  volatile uint32_t SR;
  volatile uint32_t RISR;
  volatile uint32_t IER;
  volatile uint32_t MISR;
  volatile uint32_t ICR;
  volatile uint32_t ESCR;
  volatile uint32_t ESUR;
  volatile uint32_t CWSTRTR;
  volatile uint32_t CWSIZER;
  volatile uint32_t DR;
} DCMI_TypeDef;





typedef struct
{
  volatile uint32_t CR;
  volatile uint32_t NDTR;
  volatile uint32_t PAR;
  volatile uint32_t M0AR;
  volatile uint32_t M1AR;
  volatile uint32_t FCR;
} DMA_Stream_TypeDef;

typedef struct
{
  volatile uint32_t LISR;
  volatile uint32_t HISR;
  volatile uint32_t LIFCR;
  volatile uint32_t HIFCR;
} DMA_TypeDef;





typedef struct
{
  volatile uint32_t MACCR;
  volatile uint32_t MACFFR;
  volatile uint32_t MACHTHR;
  volatile uint32_t MACHTLR;
  volatile uint32_t MACMIIAR;
  volatile uint32_t MACMIIDR;
  volatile uint32_t MACFCR;
  volatile uint32_t MACVLANTR;
  uint32_t RESERVED0[2];
  volatile uint32_t MACRWUFFR;
  volatile uint32_t MACPMTCSR;
  uint32_t RESERVED1;
  volatile uint32_t MACDBGR;
  volatile uint32_t MACSR;
  volatile uint32_t MACIMR;
  volatile uint32_t MACA0HR;
  volatile uint32_t MACA0LR;
  volatile uint32_t MACA1HR;
  volatile uint32_t MACA1LR;
  volatile uint32_t MACA2HR;
  volatile uint32_t MACA2LR;
  volatile uint32_t MACA3HR;
  volatile uint32_t MACA3LR;
  uint32_t RESERVED2[40];
  volatile uint32_t MMCCR;
  volatile uint32_t MMCRIR;
  volatile uint32_t MMCTIR;
  volatile uint32_t MMCRIMR;
  volatile uint32_t MMCTIMR;
  uint32_t RESERVED3[14];
  volatile uint32_t MMCTGFSCCR;
  volatile uint32_t MMCTGFMSCCR;
  uint32_t RESERVED4[5];
  volatile uint32_t MMCTGFCR;
  uint32_t RESERVED5[10];
  volatile uint32_t MMCRFCECR;
  volatile uint32_t MMCRFAECR;
  uint32_t RESERVED6[10];
  volatile uint32_t MMCRGUFCR;
  uint32_t RESERVED7[334];
  volatile uint32_t PTPTSCR;
  volatile uint32_t PTPSSIR;
  volatile uint32_t PTPTSHR;
  volatile uint32_t PTPTSLR;
  volatile uint32_t PTPTSHUR;
  volatile uint32_t PTPTSLUR;
  volatile uint32_t PTPTSAR;
  volatile uint32_t PTPTTHR;
  volatile uint32_t PTPTTLR;
  volatile uint32_t RESERVED8;
  volatile uint32_t PTPTSSR;
  uint32_t RESERVED9[565];
  volatile uint32_t DMABMR;
  volatile uint32_t DMATPDR;
  volatile uint32_t DMARPDR;
  volatile uint32_t DMARDLAR;
  volatile uint32_t DMATDLAR;
  volatile uint32_t DMASR;
  volatile uint32_t DMAOMR;
  volatile uint32_t DMAIER;
  volatile uint32_t DMAMFBOCR;
  volatile uint32_t DMARSWTR;
  uint32_t RESERVED10[8];
  volatile uint32_t DMACHTDR;
  volatile uint32_t DMACHRDR;
  volatile uint32_t DMACHTBAR;
  volatile uint32_t DMACHRBAR;
} ETH_TypeDef;





typedef struct
{
  volatile uint32_t IMR;
  volatile uint32_t EMR;
  volatile uint32_t RTSR;
  volatile uint32_t FTSR;
  volatile uint32_t SWIER;
  volatile uint32_t PR;
} EXTI_TypeDef;





typedef struct
{
  volatile uint32_t ACR;
  volatile uint32_t KEYR;
  volatile uint32_t OPTKEYR;
  volatile uint32_t SR;
  volatile uint32_t CR;
  volatile uint32_t OPTCR;
  volatile uint32_t OPTCR1;
} FLASH_TypeDef;







typedef struct
{
  volatile uint32_t BTCR[8];
} FSMC_Bank1_TypeDef;





typedef struct
{
  volatile uint32_t BWTR[7];
} FSMC_Bank1E_TypeDef;





typedef struct
{
  volatile uint32_t PCR2;
  volatile uint32_t SR2;
  volatile uint32_t PMEM2;
  volatile uint32_t PATT2;
  uint32_t RESERVED0;
  volatile uint32_t ECCR2;
  uint32_t RESERVED1;
  uint32_t RESERVED2;
  volatile uint32_t PCR3;
  volatile uint32_t SR3;
  volatile uint32_t PMEM3;
  volatile uint32_t PATT3;
  uint32_t RESERVED3;
  volatile uint32_t ECCR3;
} FSMC_Bank2_3_TypeDef;





typedef struct
{
  volatile uint32_t PCR4;
  volatile uint32_t SR4;
  volatile uint32_t PMEM4;
  volatile uint32_t PATT4;
  volatile uint32_t PIO4;
} FSMC_Bank4_TypeDef;





typedef struct
{
  volatile uint32_t MODER;
  volatile uint32_t OTYPER;
  volatile uint32_t OSPEEDR;
  volatile uint32_t PUPDR;
  volatile uint32_t IDR;
  volatile uint32_t ODR;
  volatile uint32_t BSRR;
  volatile uint32_t LCKR;
  volatile uint32_t AFR[2];
} GPIO_TypeDef;





typedef struct
{
  volatile uint32_t MEMRMP;
  volatile uint32_t PMC;
  volatile uint32_t EXTICR[4];
  uint32_t RESERVED[2];
  volatile uint32_t CMPCR;
} SYSCFG_TypeDef;





typedef struct
{
  volatile uint32_t CR1;
  volatile uint32_t CR2;
  volatile uint32_t OAR1;
  volatile uint32_t OAR2;
  volatile uint32_t DR;
  volatile uint32_t SR1;
  volatile uint32_t SR2;
  volatile uint32_t CCR;
  volatile uint32_t TRISE;
} I2C_TypeDef;





typedef struct
{
  volatile uint32_t KR;
  volatile uint32_t PR;
  volatile uint32_t RLR;
  volatile uint32_t SR;
} IWDG_TypeDef;






typedef struct
{
  volatile uint32_t CR;
  volatile uint32_t CSR;
} PWR_TypeDef;





typedef struct
{
  volatile uint32_t CR;
  volatile uint32_t PLLCFGR;
  volatile uint32_t CFGR;
  volatile uint32_t CIR;
  volatile uint32_t AHB1RSTR;
  volatile uint32_t AHB2RSTR;
  volatile uint32_t AHB3RSTR;
  uint32_t RESERVED0;
  volatile uint32_t APB1RSTR;
  volatile uint32_t APB2RSTR;
  uint32_t RESERVED1[2];
  volatile uint32_t AHB1ENR;
  volatile uint32_t AHB2ENR;
  volatile uint32_t AHB3ENR;
  uint32_t RESERVED2;
  volatile uint32_t APB1ENR;
  volatile uint32_t APB2ENR;
  uint32_t RESERVED3[2];
  volatile uint32_t AHB1LPENR;
  volatile uint32_t AHB2LPENR;
  volatile uint32_t AHB3LPENR;
  uint32_t RESERVED4;
  volatile uint32_t APB1LPENR;
  volatile uint32_t APB2LPENR;
  uint32_t RESERVED5[2];
  volatile uint32_t BDCR;
  volatile uint32_t CSR;
  uint32_t RESERVED6[2];
  volatile uint32_t SSCGR;
  volatile uint32_t PLLI2SCFGR;
} RCC_TypeDef;





typedef struct
{
  volatile uint32_t TR;
  volatile uint32_t DR;
  volatile uint32_t CR;
  volatile uint32_t ISR;
  volatile uint32_t PRER;
  volatile uint32_t WUTR;
  volatile uint32_t CALIBR;
  volatile uint32_t ALRMAR;
  volatile uint32_t ALRMBR;
  volatile uint32_t WPR;
  volatile uint32_t SSR;
  volatile uint32_t SHIFTR;
  volatile uint32_t TSTR;
  volatile uint32_t TSDR;
  volatile uint32_t TSSSR;
  volatile uint32_t CALR;
  volatile uint32_t TAFCR;
  volatile uint32_t ALRMASSR;
  volatile uint32_t ALRMBSSR;
  uint32_t RESERVED7;
  volatile uint32_t BKP0R;
  volatile uint32_t BKP1R;
  volatile uint32_t BKP2R;
  volatile uint32_t BKP3R;
  volatile uint32_t BKP4R;
  volatile uint32_t BKP5R;
  volatile uint32_t BKP6R;
  volatile uint32_t BKP7R;
  volatile uint32_t BKP8R;
  volatile uint32_t BKP9R;
  volatile uint32_t BKP10R;
  volatile uint32_t BKP11R;
  volatile uint32_t BKP12R;
  volatile uint32_t BKP13R;
  volatile uint32_t BKP14R;
  volatile uint32_t BKP15R;
  volatile uint32_t BKP16R;
  volatile uint32_t BKP17R;
  volatile uint32_t BKP18R;
  volatile uint32_t BKP19R;
} RTC_TypeDef;





typedef struct
{
  volatile uint32_t POWER;
  volatile uint32_t CLKCR;
  volatile uint32_t ARG;
  volatile uint32_t CMD;
  volatile const uint32_t RESPCMD;
  volatile const uint32_t RESP1;
  volatile const uint32_t RESP2;
  volatile const uint32_t RESP3;
  volatile const uint32_t RESP4;
  volatile uint32_t DTIMER;
  volatile uint32_t DLEN;
  volatile uint32_t DCTRL;
  volatile const uint32_t DCOUNT;
  volatile const uint32_t STA;
  volatile uint32_t ICR;
  volatile uint32_t MASK;
  uint32_t RESERVED0[2];
  volatile const uint32_t FIFOCNT;
  uint32_t RESERVED1[13];
  volatile uint32_t FIFO;
} SDIO_TypeDef;





typedef struct
{
  volatile uint32_t CR1;
  volatile uint32_t CR2;
  volatile uint32_t SR;
  volatile uint32_t DR;
  volatile uint32_t CRCPR;
  volatile uint32_t RXCRCR;
  volatile uint32_t TXCRCR;
  volatile uint32_t I2SCFGR;
  volatile uint32_t I2SPR;
} SPI_TypeDef;






typedef struct
{
  volatile uint32_t CR1;
  volatile uint32_t CR2;
  volatile uint32_t SMCR;
  volatile uint32_t DIER;
  volatile uint32_t SR;
  volatile uint32_t EGR;
  volatile uint32_t CCMR1;
  volatile uint32_t CCMR2;
  volatile uint32_t CCER;
  volatile uint32_t CNT;
  volatile uint32_t PSC;
  volatile uint32_t ARR;
  volatile uint32_t RCR;
  volatile uint32_t CCR1;
  volatile uint32_t CCR2;
  volatile uint32_t CCR3;
  volatile uint32_t CCR4;
  volatile uint32_t BDTR;
  volatile uint32_t DCR;
  volatile uint32_t DMAR;
  volatile uint32_t OR;
} TIM_TypeDef;





typedef struct
{
  volatile uint32_t SR;
  volatile uint32_t DR;
  volatile uint32_t BRR;
  volatile uint32_t CR1;
  volatile uint32_t CR2;
  volatile uint32_t CR3;
  volatile uint32_t GTPR;
} USART_TypeDef;





typedef struct
{
  volatile uint32_t CR;
  volatile uint32_t CFR;
  volatile uint32_t SR;
} WWDG_TypeDef;





typedef struct
{
  volatile uint32_t CR;
  volatile uint32_t SR;
  volatile uint32_t DR;
} RNG_TypeDef;




typedef struct
{
  volatile uint32_t GOTGCTL;
  volatile uint32_t GOTGINT;
  volatile uint32_t GAHBCFG;
  volatile uint32_t GUSBCFG;
  volatile uint32_t GRSTCTL;
  volatile uint32_t GINTSTS;
  volatile uint32_t GINTMSK;
  volatile uint32_t GRXSTSR;
  volatile uint32_t GRXSTSP;
  volatile uint32_t GRXFSIZ;
  volatile uint32_t DIEPTXF0_HNPTXFSIZ;
  volatile uint32_t HNPTXSTS;
  uint32_t Reserved30[2];
  volatile uint32_t GCCFG;
  volatile uint32_t CID;
  uint32_t Reserved40[48];
  volatile uint32_t HPTXFSIZ;
  volatile uint32_t DIEPTXF[0x0F];
} USB_OTG_GlobalTypeDef;




typedef struct
{
  volatile uint32_t DCFG;
  volatile uint32_t DCTL;
  volatile uint32_t DSTS;
  uint32_t Reserved0C;
  volatile uint32_t DIEPMSK;
  volatile uint32_t DOEPMSK;
  volatile uint32_t DAINT;
  volatile uint32_t DAINTMSK;
  uint32_t Reserved20;
  uint32_t Reserved9;
  volatile uint32_t DVBUSDIS;
  volatile uint32_t DVBUSPULSE;
  volatile uint32_t DTHRCTL;
  volatile uint32_t DIEPEMPMSK;
  volatile uint32_t DEACHINT;
  volatile uint32_t DEACHMSK;
  uint32_t Reserved40;
  volatile uint32_t DINEP1MSK;
  uint32_t Reserved44[15];
  volatile uint32_t DOUTEP1MSK;
} USB_OTG_DeviceTypeDef;




typedef struct
{
  volatile uint32_t DIEPCTL;
  uint32_t Reserved04;
  volatile uint32_t DIEPINT;
  uint32_t Reserved0C;
  volatile uint32_t DIEPTSIZ;
  volatile uint32_t DIEPDMA;
  volatile uint32_t DTXFSTS;
  uint32_t Reserved18;
} USB_OTG_INEndpointTypeDef;




typedef struct
{
  volatile uint32_t DOEPCTL;
  uint32_t Reserved04;
  volatile uint32_t DOEPINT;
  uint32_t Reserved0C;
  volatile uint32_t DOEPTSIZ;
  volatile uint32_t DOEPDMA;
  uint32_t Reserved18[2];
} USB_OTG_OUTEndpointTypeDef;




typedef struct
{
  volatile uint32_t HCFG;
  volatile uint32_t HFIR;
  volatile uint32_t HFNUM;
  uint32_t Reserved40C;
  volatile uint32_t HPTXSTS;
  volatile uint32_t HAINT;
  volatile uint32_t HAINTMSK;
} USB_OTG_HostTypeDef;




typedef struct
{
  volatile uint32_t HCCHAR;
  volatile uint32_t HCSPLT;
  volatile uint32_t HCINT;
  volatile uint32_t HCINTMSK;
  volatile uint32_t HCTSIZ;
  volatile uint32_t HCDMA;
  uint32_t Reserved[2];
} USB_OTG_HostChannelTypeDef;
# 4 "/home/unmanned-john-doe/git/embedded/pcbteach_sandbox/exti.c" 2








void Test(void) {
  ((EXTI_TypeDef *) ((0x40000000UL + 0x00010000UL) + 0x3C00UL))->PR |= (0x1UL << (10U)); ((EXTI_TypeDef *) ((0x40000000UL + 0x00010000UL) + 0x3C00UL))->FTSR |= (0x1UL << (10U)); ((EXTI_TypeDef *) ((0x40000000UL + 0x00010000UL) + 0x3C00UL))->IMR |= (0x1UL << (10U));; ((EXTI_TypeDef *) ((0x40000000UL + 0x00010000UL) + 0x3C00UL))->PR |= (0x1UL << (11U)); ((EXTI_TypeDef *) ((0x40000000UL + 0x00010000UL) + 0x3C00UL))->FTSR |= (0x1UL << (11U)); ((EXTI_TypeDef *) ((0x40000000UL + 0x00010000UL) + 0x3C00UL))->IMR |= (0x1UL << (11U));; ((EXTI_TypeDef *) ((0x40000000UL + 0x00010000UL) + 0x3C00UL))->PR |= (0x1UL << (12U)); ((EXTI_TypeDef *) ((0x40000000UL + 0x00010000UL) + 0x3C00UL))->FTSR |= (0x1UL << (12U)); ((EXTI_TypeDef *) ((0x40000000UL + 0x00010000UL) + 0x3C00UL))->IMR |= (0x1UL << (12U));;


  ((EXTI_TypeDef *) ((0x40000000UL + 0x00010000UL) + 0x3C00UL))->PR |= (0x1UL << (10U)) | (0x1UL << (11U)) | (0x1UL << (12U));
  ((EXTI_TypeDef *) ((0x40000000UL + 0x00010000UL) + 0x3C00UL))->FTSR |= (0x1UL << (10U)) | (0x1UL << (11U)) | (0x1UL << (12U));
  ((EXTI_TypeDef *) ((0x40000000UL + 0x00010000UL) + 0x3C00UL))->IMR |= (0x1UL << (10U)) | (0x1UL << (11U)) | (0x1UL << (12U));
}
