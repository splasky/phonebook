#ifndef HASH_FUNCTION_H_VDMEOP0X
#define HASH_FUNCTION_H_VDMEOP0X

/* hash functions */
unsigned int RSHASH(const char* str, unsigned int length);
unsigned int JSHash(const char* str, unsigned int length);
unsigned int PJWHash(const char* str, unsigned int length);
unsigned int ELFHash(const char* str, unsigned int length);
unsigned int BKDRHash(const char* str, unsigned int length);
unsigned int SDBMHash(const char* str, unsigned int length);
unsigned int DJBHash(const char* str, unsigned int length);
unsigned int DEKHash(const char* str, unsigned int length);
unsigned int APHash(const char* str, unsigned int length);

#endif /* end of include guard: HASH_FUNCTION_H_VDMEOP0X */
