#include <jit/jit.h>
#include "ibniz.h"
#include "gen.h"

#ifdef AMD64
#define NUMREGS 6
#else
#define NUMREGS 14
#endif

char*regnames[]={
  "eax","ecx","edx","ebx", "esp","ebp","esi","edi"
#ifdef AMD64
  ,"r8d","r9d","r10d","r11d","r12d","r13d","r14d","r15d"
#endif
};

char*regallocorder={
  1,3,5,7,2,0,
#ifdef AMD64
  8,9,10,11,12,13,14,15
#endif
};

jit_context_t gen_jit_context;


/*
  0 eax, 1 ecx, 2 edx,  3 ebx, 4 esp, 5 ebp, 6 esi, 7 edi
  8 r8d, 9 r9d, ...
*/

// mask out unallocable regs

void gen_nativeinit()
{
  jit_init();
  gen_jit_context = jit_context_create();
}

void gen_nativefinish()
{
  jit_context_destroy(gen_jit_context);
  printf("ret\n");
}

gen_mov_reg_imm(int t,uint32_t imm)
{
  // DEBUG(stderr,"mov %s,0x%X",regnames[t],imm);
#ifdef AMD64
  if(t&8) *gen.co++=0x41;
#endif
  *gen.co++=0xB8+(t&7);
  *((uint32_t*)gen.co)=imm;
  gen.co+=4;
}

gen_mov_reg_reg(int t,int s)
{
  // DEBUG(stderr,"mov %s,%s",regnames[t],regnames[s]);
#ifdef AMD64
  if((t&8) || (s&8)) *gen.co++=0x40|((t&8)>>3)|((s&8)>>1);
#endif
  *gen.co++=0x89;
  *gen.co++=0xC0+(((t&7)<<3)|(s&7));
}

gen_add_reg_imm(int t,uint32_t imm)
{
  // DEBUG(stderr,"add %s,0x%X",regnames[t],imm);
#ifdef AMD64
  if(t&8) *gen.co++=0x41;
#endif
  if(!t)
    *gen.co++=0x05;
  else
  {  
    *gen.co++=0x81;
    *gen.co++=0xC0|(t&7);
  }
  *((uint32_t*)gen.co)=imm;
  gen.co+=4;
}

gen_add_reg_reg(int t,int s)  
{
  // DEBUG(stderr,"add %s,%s",regnames[t],regnames[s]);
#ifdef AMD64
  if((t&8) || (s&8)) *gen.co++=0x40|((t&8)>>3)|((s&8)>>1);
#endif
  *gen.co++=0x01;
  *gen.co++=0xC0+(((t&7)<<3)|(s&7));
}

/* TODO FINISH */


void gen_nativerun(void*a) {}
void gen_load_reg_reg(int t, int a) {}
void gen_load_reg_imm(int t, int32_t a) {}
void gen_store_reg_reg(int a, int s) {}
void gen_store_reg_imm(int a, int32_t s) {}
void gen_store_imm_reg(int32_t a, int s) {}
void gen_store_imm_imm(int32_t a, int32_t s) {}
void gen_mov_reg_ivar(int r, int v) {}
void gen_mov_ivar_reg(int v, int r) {}
void gen_add_reg_reg_reg(int t, int s1, int s) {}
void gen_add_reg_reg_imm(int t, int s1, int32_t i) {}
void gen_sub_reg_reg_reg(int t, int s1, int s) {}
void gen_sub_reg_reg_imm(int t, int s1, int32_t i) {}
void gen_mul_reg_reg_reg(int t, int s1, int s) {}
void gen_mul_reg_reg_imm(int t, int s1, int32_t i) {}
void gen_div_reg_reg_reg(int t, int s1, int s) {}
void gen_div_reg_reg_imm(int t, int s1, int32_t i) {}
void gen_mod_reg_reg_reg(int t, int s1, int s) {}
void gen_mod_reg_reg_imm(int t, int s1, int32_t i) {}
void gen_and_reg_reg_reg(int t, int s1, int s) {}
void gen_and_reg_reg_imm(int t, int s1, int32_t i) {}
void gen_or_reg_reg_reg(int t, int s1, int s) {}
void gen_or_reg_reg_imm(int t, int s1, int32_t i) {}
void gen_xor_reg_reg_reg(int t, int s1, int s) {}
void gen_xor_reg_reg_imm(int t, int s1, int32_t i) {}
void gen_ror_reg_reg_reg(int t, int s1, int s) {}
void gen_ror_reg_reg_imm(int t, int s1, int32_t i) {}
void gen_shl_reg_reg_reg(int t, int s1, int s) {}
void gen_shl_reg_reg_imm(int t, int s1, int32_t i) {}
void gen_neg_reg_reg(int t, int s) {}
void gen_atan2_reg_reg_reg(int t, int s1, int s) {}
void gen_atan2_reg_reg_imm(int t, int s1, int32_t i) {}
void gen_sin_reg_reg(int t, int s) {}
void gen_sqrt_reg_reg(int t, int s) {}
void gen_isneg_reg_reg(int t, int s) {}
void gen_ispos_reg_reg(int t, int s) {}
void gen_iszero_reg_reg(int t, int s) {}
void gen_push_reg(int s) {}
void gen_push_imm(int32_t i) {}
void gen_pop_reg(int t) {}
void gen_pop_noreg() {}
void gen_dup_reg(int t) {}
void gen_pick_reg_reg(int t,int i) {}
void gen_pick_reg_imm(int t,int32_t i) {}
void gen_bury_regreg(int t,int s) {}
void gen_bury_reg_imm(int t,int32_t s) {}
void gen_bury_imm_reg(int32_t i,int s) {}
void gen_bury_imm_imm(int32_t i,int32_t s) {}
void gen_rpush_reg_reg(int s) {}
void gen_rpush_reg_imm(int32_t i) {}
void gen_rpush_reg_lab(int l) {}
void gen_rpop_reg_reg(int t) {}
void gen_beq_reg_lab(int s,int l) {}
void gen_bne_reg_lab(int s,int l) {}
void gen_beq_reg_rstack(int s) {}
void gen_bne_reg_rstack(int s) {}
void gen_bne_lab(int l) {}
void gen_beq_lab(int l) {}
void gen_bmi_lab(int l) {}
void gen_bpl_lab(int l) {}
void gen_jmp_lab(int l) {}
void gen_jsr_lab(int i) {}
void gen_jsr_reg(int r) {}
void gen_label(int l) {}
void gen_nativeret() {}
void gen_nativeterminate() {}
void gen_nativeuserin() {}

void gen_rpush_lab(int l) {}
void gen_jmp_rstack() {}
void gen_rpop_noreg() {}
void gen_rpush_reg(int s) {}
void gen_rpush_imm(int32_t s) {}
void gen_rpop_reg(int t) {}
