#ifndef _CPU_LIBWRAP_H_
#define _CPU_LIBWRAP_H_

#include <dlfcn.h>

const char* LIBCUDA_PATH;
void *so_handle;

inline void* libwrap_get_sohandle()
{
    if (!so_handle) {
        if ( !(so_handle = dlopen(LIBCUDA_PATH, RTLD_LAZY)) ) {
            fprintf(stderr, "%s\n", dlerror());
            so_handle = NULL;
            return 0;
        }
    }
    return so_handle;
}

inline void libwrap_pre_call(char *ret, char *name, char *parameters)
{
    printf("%s\n", name);
}
inline void libwrap_post_call(char *ret, char *name, char *parameters)
{
    printf("%s\n", name);
}

#define DEF_FN_PTR(RET, P_TYPES...) RET (*fun)(P_TYPES)
#define CAL_FN_PTR(P_NAMES...) ret = (*fun)(P_NAMES)
#define DEF_DLSYM(RET, NAME) \
    RET ret; char* error_str; \
    *(void **)(&fun) = dlsym(libwrap_get_sohandle(), #NAME); \
    if ((error_str = dlerror()) != NULL) { \
        fprintf(stderr, "[libwrap] %s\n", error_str); \
        return ret; \
    } \

#define DEF_FN_BODY(RET, NAME, P_NAMES...) \
    DEF_DLSYM(RET, NAME) \
    printf("%s called\n", #NAME); \
    CAL_FN_PTR(P_NAMES); \
    printf("%s finished\n", #NAME); \
    return ret;

#define DEF_FN_0(RET, NAME) \
RET NAME() \
{ \
    DEF_FN_PTR(RET, void); \
    DEF_FN_BODY(RET, NAME,); \
}

#define DEF_FN_1(RET, NAME, P1_TYPE, P1_NAME) \
RET NAME(P1_TYPE P1_NAME) \
{ \
    DEF_FN_PTR(RET, P1_TYPE); \
    DEF_FN_BODY(RET, NAME, P1_NAME); \
}

#define DEF_FN_2(RET, NAME, P1_TYPE, P1_NAME, P2_TYPE, P2_NAME) \
RET NAME(P1_TYPE P1_NAME, P2_TYPE P2_NAME) \
{ \
    DEF_FN_PTR(RET, P1_TYPE, P2_TYPE); \
    DEF_FN_BODY(RET, NAME, P1_NAME, P2_NAME); \
}

#define DEF_FN_3(RET, NAME, P1_TYPE, P1_NAME, P2_TYPE, P2_NAME, P3_TYPE, P3_NAME) \
RET NAME(P1_TYPE P1_NAME, P2_TYPE P2_NAME, P3_TYPE P3_NAME) \
{ \
    DEF_FN_PTR(RET, P1_TYPE, P2_TYPE, P3_TYPE); \
    DEF_FN_BODY(RET, NAME, P1_NAME, P2_NAME, P3_NAME); \
}

#define DEF_FN_4(RET, NAME, P1_TYPE, P1_NAME, P2_TYPE, P2_NAME, P3_TYPE, P3_NAME, P4_TYPE, P4_NAME) \
RET NAME(P1_TYPE P1_NAME, P2_TYPE P2_NAME, P3_TYPE P3_NAME, P4_TYPE P4_NAME) \
{ \
    DEF_FN_PTR(RET, P1_TYPE, P2_TYPE, P3_TYPE, P4_TYPE); \
    DEF_FN_BODY(RET, NAME, P1_NAME, P2_NAME, P3_NAME, P4_NAME); \
}

#define DEF_FN_5(RET, NAME, P1_TYPE, P1_NAME, P2_TYPE, P2_NAME, P3_TYPE, P3_NAME, P4_TYPE, P4_NAME, P5_TYPE, P5_NAME) \
RET NAME(P1_TYPE P1_NAME, P2_TYPE P2_NAME, P3_TYPE P3_NAME, P4_TYPE P4_NAME, P5_TYPE P5_NAME) \
{ \
    DEF_FN_PTR(RET, P1_TYPE, P2_TYPE, P3_TYPE, P4_TYPE, P5_TYPE); \
    DEF_FN_BODY(RET, NAME, P1_NAME, P2_NAME, P3_NAME, P4_NAME, P5_NAME); \
}

#define DEF_FN_6(RET, NAME, P1_TYPE, P1_NAME, P2_TYPE, P2_NAME, P3_TYPE, P3_NAME, P4_TYPE, P4_NAME, P5_TYPE, P5_NAME, P6_TYPE, P6_NAME) \
RET NAME(P1_TYPE P1_NAME, P2_TYPE P2_NAME, P3_TYPE P3_NAME, P4_TYPE P4_NAME, P5_TYPE P5_NAME, P6_TYPE P6_NAME) \
{ \
    DEF_FN_PTR(RET, P1_TYPE, P2_TYPE, P3_TYPE, P4_TYPE, P5_TYPE, P6_TYPE); \
    DEF_FN_BODY(RET, NAME, P1_NAME, P2_NAME, P3_NAME, P4_NAME, P5_NAME, P6_NAME); \
}

#define DEF_FN_7(RET, NAME, P1_TYPE, P1_NAME, P2_TYPE, P2_NAME, P3_TYPE, P3_NAME, P4_TYPE, P4_NAME, P5_TYPE, P5_NAME, P6_TYPE, P6_NAME, P7_TYPE, P7_NAME) \
RET NAME(P1_TYPE P1_NAME, P2_TYPE P2_NAME, P3_TYPE P3_NAME, P4_TYPE P4_NAME, P5_TYPE P5_NAME, P6_TYPE P6_NAME, P7_TYPE P7_NAME) \
{ \
    DEF_FN_PTR(RET, P1_TYPE, P2_TYPE, P3_TYPE, P4_TYPE, P5_TYPE, P6_TYPE, P7_TYPE); \
    DEF_FN_BODY(RET, NAME, P1_NAME, P2_NAME, P3_NAME, P4_NAME, P5_NAME, P6_NAME, P7_NAME); \
}

#define DEF_FN_8(RET, NAME, P1_TYPE, P1_NAME, P2_TYPE, P2_NAME, P3_TYPE, P3_NAME, P4_TYPE, P4_NAME, P5_TYPE, P5_NAME, P6_TYPE, P6_NAME, P7_TYPE, P7_NAME, P8_TYPE, P8_NAME) \
RET NAME(P1_TYPE P1_NAME, P2_TYPE P2_NAME, P3_TYPE P3_NAME, P4_TYPE P4_NAME, P5_TYPE P5_NAME, P6_TYPE P6_NAME, P7_TYPE P7_NAME, P8_TYPE P8_NAME) \
{ \
    DEF_FN_PTR(RET, P1_TYPE, P2_TYPE, P3_TYPE, P4_TYPE, P5_TYPE, P6_TYPE, P7_TYPE, P8_TYPE); \
    DEF_FN_BODY(RET, NAME, P1_NAME, P2_NAME, P3_NAME, P4_NAME, P5_NAME, P6_NAME, P7_NAME, P8_NAME); \
}

#define DEF_FN_9(RET, NAME, P1_TYPE, P1_NAME, P2_TYPE, P2_NAME, P3_TYPE, P3_NAME, P4_TYPE, P4_NAME, P5_TYPE, P5_NAME, P6_TYPE, P6_NAME, P7_TYPE, P7_NAME, P8_TYPE, P8_NAME, P9_TYPE, P9_NAME) \
RET NAME(P1_TYPE P1_NAME, P2_TYPE P2_NAME, P3_TYPE P3_NAME, P4_TYPE P4_NAME, P5_TYPE P5_NAME, P6_TYPE P6_NAME, P7_TYPE P7_NAME, P8_TYPE P8_NAME, P9_TYPE P9_NAME) \
{ \
    DEF_FN_PTR(RET, P1_TYPE, P2_TYPE, P3_TYPE, P4_TYPE, P5_TYPE, P6_TYPE, P7_TYPE, P8_TYPE, P9_TYPE); \
    DEF_FN_BODY(RET, NAME, P1_NAME, P2_NAME, P3_NAME, P4_NAME, P5_NAME, P6_NAME, P7_NAME, P8_NAME, P9_NAME); \
}

#define DEF_FN_10(RET, NAME, P1_TYPE, P1_NAME, P2_TYPE, P2_NAME, P3_TYPE, P3_NAME, P4_TYPE, P4_NAME, P5_TYPE, P5_NAME, P6_TYPE, P6_NAME, P7_TYPE, P7_NAME, P8_TYPE, P8_NAME, P9_TYPE, P9_NAME, P10_TYPE, P10_NAME) \
RET NAME(P1_TYPE P1_NAME, P2_TYPE P2_NAME, P3_TYPE P3_NAME, P4_TYPE P4_NAME, P5_TYPE P5_NAME, P6_TYPE P6_NAME, P7_TYPE P7_NAME, P8_TYPE P8_NAME, P9_TYPE P9_NAME, P10_TYPE P10_NAME) \
{ \
    DEF_FN_PTR(RET, P1_TYPE, P2_TYPE, P3_TYPE, P4_TYPE, P5_TYPE, P6_TYPE, P7_TYPE, P8_TYPE, P9_TYPE, P10_TYPE); \
    DEF_FN_BODY(RET, NAME, P1_NAME, P2_NAME, P3_NAME, P4_NAME, P5_NAME, P6_NAME, P7_NAME, P8_NAME, P9_NAME, P10_NAME); \
}

#define DEF_FN_11(RET, NAME, P1_TYPE, P1_NAME, P2_TYPE, P2_NAME, P3_TYPE, P3_NAME, P4_TYPE, P4_NAME, P5_TYPE, P5_NAME, P6_TYPE, P6_NAME, P7_TYPE, P7_NAME, P8_TYPE, P8_NAME, P9_TYPE, P9_NAME, P10_TYPE, P10_NAME, P11_TYPE, P11_NAME) \
RET NAME(P1_TYPE P1_NAME, P2_TYPE P2_NAME, P3_TYPE P3_NAME, P4_TYPE P4_NAME, P5_TYPE P5_NAME, P6_TYPE P6_NAME, P7_TYPE P7_NAME, P8_TYPE P8_NAME, P9_TYPE P9_NAME, P10_TYPE P10_NAME, P11_TYPE P11_NAME) \
{ \
    DEF_FN_PTR(RET, P1_TYPE, P2_TYPE, P3_TYPE, P4_TYPE, P5_TYPE, P6_TYPE, P7_TYPE, P8_TYPE, P9_TYPE, P10_TYPE, P11_TYPE); \
    DEF_FN_BODY(RET, NAME, P1_NAME, P2_NAME, P3_NAME, P4_NAME, P5_NAME, P6_NAME, P7_NAME, P8_NAME, P9_NAME, P10_NAME, P11_NAME); \
}

#define DEF_FN_12(RET, NAME, P1_TYPE, P1_NAME, P2_TYPE, P2_NAME, P3_TYPE, P3_NAME, P4_TYPE, P4_NAME, P5_TYPE, P5_NAME, P6_TYPE, P6_NAME, P7_TYPE, P7_NAME, P8_TYPE, P8_NAME, P9_TYPE, P9_NAME, P10_TYPE, P10_NAME, P11_TYPE, P11_NAME, P12_TYPE, P12_NAME) \
RET NAME(P1_TYPE P1_NAME, P2_TYPE P2_NAME, P3_TYPE P3_NAME, P4_TYPE P4_NAME, P5_TYPE P5_NAME, P6_TYPE P6_NAME, P7_TYPE P7_NAME, P8_TYPE P8_NAME, P9_TYPE P9_NAME, P10_TYPE P10_NAME, P11_TYPE P11_NAME, P12_TYPE P12_NAME) \
{ \
    DEF_FN_PTR(RET, P1_TYPE, P2_TYPE, P3_TYPE, P4_TYPE, P5_TYPE, P6_TYPE, P7_TYPE, P8_TYPE, P9_TYPE, P10_TYPE, P11_TYPE, P12_TYPE); \
    DEF_FN_BODY(RET, NAME, P1_NAME, P2_NAME, P3_NAME, P4_NAME, P5_NAME, P6_NAME, P7_NAME, P8_NAME, P9_NAME, P10_NAME, P11_NAME, P12_NAME); \
}


#define DEF_FN_X(x, RET, NAME, P1_TYPE, P1_NAME, P2_TYPE, P2_NAME, P3_TYPE, P3_NAME, P4_TYPE, P4_NAME, P5_TYPE, P5_NAME, P6_TYPE, P6_NAME, P7_TYPE, P7_NAME, P8_TYPE, P8_NAME, P9_TYPE, P9_NAME, P10_TYPE, P10_NAME, P11_TYPE, P11_NAME, P12_TYPE, P12_NAME, FUNC, ...) FUNC

#define DEF_FN(...) DEF_FN_X(,##__VA_ARGS__,\
                    DEF_FN_12(__VA_ARGS__),,\
                    DEF_FN_11(__VA_ARGS__),,\
                    DEF_FN_10(__VA_ARGS__),,\
                    DEF_FN_9 (__VA_ARGS__),,\
                    DEF_FN_8 (__VA_ARGS__),,\
                    DEF_FN_7 (__VA_ARGS__),,\
                    DEF_FN_6 (__VA_ARGS__),,\
                    DEF_FN_5 (__VA_ARGS__),,\
                    DEF_FN_4 (__VA_ARGS__),,\
                    DEF_FN_3 (__VA_ARGS__),,\
                    DEF_FN_2 (__VA_ARGS__),,\
                    DEF_FN_1 (__VA_ARGS__),,\
                    DEF_FN_0 (__VA_ARGS__))

#endif //_CPU_LIBWRAP_H_

