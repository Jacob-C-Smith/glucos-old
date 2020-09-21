/*
 * CPUID.h
 * Written by Jacob Smith
 * CPUID.h provides definitions, structs, and an initializer function to fill those structs.
 */

#ifndef CPUID_H
#define CPUID_H 

#include <typedef.h>

#define MANUFACTURER_ID         0
#define PROCESSOR_INFO          1
#define CACHE_TLB_DESCRIPTOR    2
#define PROCESSOR_SERIAL_NUM    3
#define EXTENDED_FEATURES       7
#define EXTF_PAGE1              0
#define PROCESSOR_BRAND_STRING1 0x80000002
#define PROCESSOR_BRAND_STRING2 0x80000003
#define PROCESSOR_BRAND_STRING3 0x80000004

struct processorVersionInformation_s
{
    size_t steppingID       : 4;
    size_t model            : 4;
    size_t familyID         : 4;
    size_t processorType    : 2;
    size_t rsvd1            : 2;
    size_t extendedModelID  : 4;
    size_t extendedFamilyID : 8;
    size_t rsvd2            : 2;
};
typedef struct processorVersionInformation_s processorVersionInformation_t;

struct featureInformationEDX_s
{
    size_t fpu    : 1;
    size_t vme    : 1;
    size_t de     : 1;
    size_t tsc    : 1;
    size_t msr    : 1;
    size_t pae    : 1;
    size_t mce    : 1;
    size_t cx8    : 1;
    size_t apic   : 1;
    size_t rsvd1  : 1;
    size_t sep    : 1;
    size_t mtrr   : 1;
    size_t pge    : 1;
    size_t mca    : 1;
    size_t cmov   : 1;
    size_t pat    : 1;
    size_t pse36  : 1;
    size_t psn    : 1;
    size_t clfsh  : 1;
    size_t rsvd2  : 1;
    size_t ds     : 1;
    size_t acpi   : 1;
    size_t mmx    : 1;
    size_t fxsr   : 1;
    size_t sse    : 1;
    size_t sse2   : 1;
    size_t ss     : 1;
    size_t htt    : 1;
    size_t tm     : 1;
    size_t ia64   : 1;
    size_t pbe    : 1;
};
typedef struct featureInformationEDX_s featureInformationEDX_t;

struct featureInformationECX_s
{
    size_t sse3        : 1;
    size_t pclmulqdq   : 1;
    size_t dtes64      : 1;
    size_t monitor     : 1;
    size_t dscpl       : 1;
    size_t vmx         : 1;
    size_t smx         : 1;
    size_t est         : 1;
    size_t tm2         : 1;
    size_t ssse3       : 1;
    size_t cnxtid      : 1;
    size_t sdbg        : 1;
    size_t fma         : 1;
    size_t cx16        : 1;
    size_t xptr        : 1;
    size_t pdcm        : 1;
    size_t rsvd1       : 1;
    size_t pcid        : 1;
    size_t dca         : 1;
    size_t sse41       : 1;
    size_t sse42       : 1;
    size_t x2acpi      : 1;
    size_t movbe       : 1;
    size_t popcnt      : 1;
    size_t tscdeadline : 1;
    size_t aes         : 1;
    size_t xsave       : 1;
    size_t osxsave     : 1;
    size_t avx         : 1;
    size_t f16c        : 1;
    size_t rdrnd       : 1;
    size_t hypervisor  : 1;
};
typedef struct featureInformationECX_s featureInformationECX_t;

struct extendedFeaturesEBX_s
{
    size_t fsgsbase        : 1;
    size_t IA32_TSC_ADJ    : 1;
    size_t sgx             : 1;
    size_t bmi1            : 1;
    size_t hle             : 1;
    size_t avx2            : 1;
    size_t FDP_EXCPT       : 1;
    size_t smep            : 1;
    size_t bmi2            : 1;
    size_t erms            : 1;
    size_t invpcid         : 1;
    size_t rtm             : 1;
    size_t pqm             : 1;
    size_t fpusegdepric    : 1;
    size_t mpx             : 1;
    size_t pqe             : 1;
    size_t avx512_f        : 1;
    size_t avx512_dq       : 1;
    size_t rdseed          : 1;
    size_t adx             : 1;
    size_t smap            : 1;
    size_t avx512_ifma     : 1;
    size_t pcommit         : 1;
    size_t clflushopt      : 1;
    size_t lcwb            : 1;
    size_t intel_pt        : 1;
    size_t avx512_pf       : 1;
    size_t avx512_er       : 1;
    size_t avx512_cd       : 1;
    size_t sha             : 1;
    size_t avx512_bw       : 1;
    size_t avx512_vl       : 1;
};
typedef struct extendedFeaturesEBX_s extendedFeaturesEBX_t;

struct extendedFeaturesECX_s
{
    size_t prefetchwt1      : 1;
    size_t avx512_vbmi      : 1;
    size_t umip             : 1;
    size_t pku              : 1;
    size_t ospke            : 1;
    size_t waitpkg          : 1;
    size_t avx512_vbmi2     : 1;
    size_t cet_ss           : 1;
    size_t gfni             : 1;
    size_t vaes             : 1;
    size_t vpclmulqdq       : 1;
    size_t avx512_vnni      : 1;
    size_t avx512_bitalg    : 1;
    size_t rsvd1            : 1;
    size_t avx512_vpopcntdq : 1;
    size_t rsvd2            : 1;
    size_t L5Paging         : 1;
    size_t mawau1           : 1;
    size_t mawau2           : 1;
    size_t mawau3           : 1;
    size_t mawau4           : 1;
    size_t mawau5           : 1;
    size_t rdpid            : 1;
    size_t rsvd3            : 1;
    size_t rsvd4            : 1;
    size_t cldemote         : 1;
    size_t rsvd5            : 1;
    size_t movdiri          : 1;
    size_t movdi64b         : 1;
    size_t enqcmd           : 1;
    size_t sgx_lc           : 1;
    size_t pks              : 1;
};
typedef struct extendedFeaturesECX_s extendedFeaturesECX_t;

struct extendedFeaturesEDX_s
{
    size_t rsvd1                  : 1;
    size_t rsvd2                  : 1;
    size_t avx512_4vnniw          : 1;
    size_t avx512_4fmaps          : 1;
    size_t fsrm                   : 1;
    size_t rsvd3                  : 1;
    size_t rsvd4                  : 1;
    size_t rsvd5                  : 1;
    size_t avx512_vp2intersect    : 1;
    size_t rsvd6                  : 1;
    size_t md_clear               : 1;
    size_t rsvd7                  : 1;
    size_t rsvd8                  : 1;
    size_t tsx_force_abort        : 1;
    size_t SERIALIZE              : 1;
    size_t Hybrid                 : 1;
    size_t TSXLDTRK               : 1;
    size_t rsvd9                  : 1;
    size_t pconfig                : 1;
    size_t rsvd10                 : 1;
    size_t cet_ibt                : 1;
    size_t rsvd11                 : 1;
    size_t amxbf16                : 1;
    size_t rsvd12                 : 1;
    size_t amxtile                : 1;
    size_t amxint8                : 1;
    size_t specCtrl               : 1;
    size_t stibp                  : 1;
    size_t rsvd13                 : 1;
    size_t IA32_ARCH_CAPABILITIES : 1;
    size_t IA32_CORE_CAPABILITIES : 1;
    size_t ssbd                   : 1;
};
typedef struct extendedFeaturesEDX_s extendedFeaturesEDX_t; 

extern processorVersionInformation_t processorVersionInformation;
extern featureInformationEDX_t       featureInformationEDX;
extern featureInformationECX_t       featureInformationECX;
extern extendedFeaturesEBX_t         extendedFeaturesEBX;
extern extendedFeaturesECX_t         extendedFeaturesECX;
extern extendedFeaturesEDX_t         extendedFeaturesEDX;

extern const char manufacturerID[13];
extern const char brandstring[49];

void CPUID_initialize();

#endif