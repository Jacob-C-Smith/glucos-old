#include <arch/x86/CPUID.h>

processorVersionInformation_t processorVersionInformation;
featureInformationEDX_t       featureInformationEDX;
featureInformationECX_t       featureInformationECX;
extendedFeaturesEBX_t         extendedFeaturesEBX;
extendedFeaturesECX_t         extendedFeaturesECX;
extendedFeaturesEDX_t         extendedFeaturesEDX;

const char manufacturerID[13]; //12+1
const char brandstring[49];    //48+1

void CPUID_initialize( )
{
    asm volatile("cpuid":"=b"(*((u32*)manufacturerID)),"=c"(*((u32*)manufacturerID+2)),"=d"(*((u32*)manufacturerID+1)):"a"(MANUFACTURER_ID));
    asm volatile("cpuid":"=a"(processorVersionInformation),"=c"(featureInformationECX),"=d"(featureInformationEDX):"a"(PROCESSOR_INFO));
    asm volatile("cpuid":"=b"(extendedFeaturesEBX),"=c"(extendedFeaturesECX),"=d"(extendedFeaturesEDX):"a"(PROCESSOR_INFO),"c"(0));
    asm volatile("cpuid":"=a"(*((u32*)brandstring)),"=b"(*((u32*)brandstring+1)),"=c"(*((u32*)brandstring+2)),"=d"(*((u32*)brandstring+3)):"a"(PROCESSOR_BRAND_STRING1));
    asm volatile("cpuid":"=a"(*((u32*)brandstring+4)),"=b"(*((u32*)brandstring+5)),"=c"(*((u32*)brandstring+6)),"=d"(*((u32*)brandstring+7)):"a"(PROCESSOR_BRAND_STRING2));
    asm volatile("cpuid":"=a"(*((u32*)brandstring+8)),"=b"(*((u32*)brandstring+9)),"=c"(*((u32*)brandstring+10)),"=d"(*((u32*)brandstring+11)):"a"(PROCESSOR_BRAND_STRING3));
}