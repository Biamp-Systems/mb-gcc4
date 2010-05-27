/* This file is tc-microblaze.h

   Copyright (C) 1999, 2000 Free Software Foundation, Inc.

   This file is part of GAS, the GNU Assembler.

   GAS is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   GAS is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with GAS; see the file COPYING.  If not, write to the
   Free Software Foundation, 59 Temple Place - Suite 330, Boston, MA
   02111-1307, USA.  */

/*
 * Copyright (c) 2001 Xilinx, Inc.  All rights reserved. 
 *
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by Xilinx, Inc.  The name of the Company may not be used to endorse 
 * or promote products derived from this software without specific prior 
 * written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 *	Xilinx, Inc.
 */

#ifndef	TC_MICROBLAZE
#define TC_MICROBLAZE 1

#ifndef BFD_ASSEMBLER
#error MICROBLAZE support requires BFD_ASSEMBLER
#endif


#define TARGET_ARCH	bfd_arch_microblaze

/* Used to initialise target_big_endian.  */
#ifndef TARGET_BYTES_BIG_ENDIAN
#define TARGET_BYTES_BIG_ENDIAN 1
#endif

#if TARGET_BYTES_BIG_ENDIAN
#define MB_BIG_ENDIAN   1
#else
#define MB_BIG_ENDIAN   0
#endif

#define IGNORE_NONSTANDARD_ESCAPES

#define TC_RELOC_MANGLE(a,b,c) tc_reloc_mangle (a, b, c)

/* We need to handle expressions of type "symbol op symbol" and create
   relocs for such expressions as -relax in linker can change the value
   of such expressions */
#define TC_CONS_FIX_NEW cons_fix_new_microblaze
#define TC_PARSE_CONS_EXPRESSION(EXP, NBYTES) parse_cons_expression_microblaze (EXP, NBYTES)
extern void parse_cons_expression_microblaze PARAMS ((expressionS *, int));

#define TC_FORCE_RELOCATION_SECTION(FIXP,SEG) 1
#define UNDEFINED_DIFFERENCE_OK 1

#define TC_FORCE_RELOCATION_LOCAL(FIX)	\
  (!(FIX)->fx_pcrel			\
   || (FIX)->fx_plt			\
   || (FIX)->fx_r_type == BFD_RELOC_MICROBLAZE_64_GOT	\
   || (FIX)->fx_r_type == BFD_RELOC_MICROBLAZE_64_PLT	\
   || (FIX)->fx_r_type == BFD_RELOC_MICROBLAZE_64_GOTOFF	\
   || (FIX)->fx_r_type == BFD_RELOC_MICROBLAZE_32_GOTOFF	\
   || TC_FORCE_RELOCATION (FIX))

#define tc_fix_adjustable(X)  tc_microblaze_fix_adjustable(X)
extern int tc_microblaze_fix_adjustable PARAMS ((struct fix *));

extern const struct relax_type md_relax_table[];
#define TC_GENERIC_RELAX_TABLE md_relax_table

/* We don't need to handle .word strangely.  */
#define WORKING_DOT_WORD

#define LISTING_HEADER        	"Xilinx MicroBlaze GAS Version 2.9.4"
#define LISTING_LHS_CONT_LINES	4

#define NEED_FX_R_TYPE	1

/* We want local label support.  */
#define LOCAL_LABELS_FB 1
     
/* Want the section information too... */
#define MD_PCREL_FROM_SECTION(FIXP, SEC) md_pcrel_from_section (FIXP, SEC)

#define MD_APPLY_FIX3  /* We want the segment as well.  */

/* We set the fx_done field appropriately in md_apply_fix.  */
#define TC_HANDLES_FX_DONE

#ifdef OBJ_ELF

#define TARGET_FORMAT (target_big_endian ? "elf32-microblaze" : "elf32-microblazele")

#define ELF_TC_SPECIAL_SECTIONS \
  { ".sdata",		SHT_PROGBITS,	SHF_ALLOC + SHF_WRITE }, \
  { ".sbss",		SHT_NOBITS,	SHF_ALLOC + SHF_WRITE }, \
  { ".sdata2",		SHT_PROGBITS,	SHF_ALLOC }, \
  { ".sbss2",		SHT_PROGBITS,	SHF_ALLOC }, \
/* Other special sections not generated by the assembler: .reginfo,
   .liblist, .conflict, .gptab, .got, .dynamic, .rel.dyn.  */

#endif /* OBJ_ELF */

#ifndef TARGET_FORMAT
# error No target format specified.
#endif

#include "write.h"        /* For definition of fixS */
  
extern void      md_begin            PARAMS ((void));
extern void      md_assemble         PARAMS ((char *));
extern symbolS * md_undefined_symbol PARAMS ((char *));
extern char *    md_atof             PARAMS ((int, char *, int *));
extern int       md_parse_option     PARAMS ((int, char *));
extern void      md_show_usage       PARAMS ((FILE *));
extern void      md_convert_frag               PARAMS ((bfd *, segT, fragS *));
// extern int       md_apply_fix3                 PARAMS ((fixS *, valueT *, segT));
extern void      md_operand                    PARAMS ((expressionS *));
extern int       md_estimate_size_before_relax PARAMS ((fragS *, segT));
extern void      md_number_to_chars            PARAMS ((char *, valueT, int));
extern valueT    md_section_align              PARAMS ((segT, valueT));
extern long      md_pcrel_from_section         PARAMS ((fixS *, segT));
extern arelent * tc_gen_reloc                  PARAMS ((asection *, fixS *));
extern void 	 cons_fix_new_microblaze       PARAMS ((fragS *, int, int, expressionS *));


#define EXTERN_FORCE_RELOC -1

#endif /* TC_MICROBLAZE */
