/*
 * This file is part of the libopencm3 project.
 *
 * Copyright (C) 2012 chrysn <chrysn@fsfe.org>
 *
 * This library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library. If not, see <http://www.gnu.org/licenses/>.
 */

/** @file
 *
 * Definitions for handling vector tables.
 *
 * This implements d0002_efm32_cortex-m3_reference_manual.pdf's figure 2.2
 * (from the EFM32 documentation at
 * http://www.energymicro.com/downloads/datasheets), and was seen analogously
 * in other ARM implementations' libopencm3 files.
 *
 * The structure of the vector table is implemented independently of the system
 * vector table starting at memory position 0x0, as it can be relocated to
 * other memory locations too.
 *
 * The exact size of a vector interrupt table depends on the number of
 * interrupts IRQ_COUNT, which is defined per family.
 */

#ifndef LIBOPENCM3_VECTOR_H
#define LIBOPENCM3_VECTOR_H

#include <libopencm3/cm3/common.h>
#include <libopencm3/cm3/nvic.h>

/** Type of an interrupt function. Only used to avoid hard-to-read function
 * pointers in the efm32_vector_table_t struct. */
typedef void (*vector_table_entry_t)(void);/*定义向量表函数指针类型*/

typedef struct {
	unsigned int *initial_sp_value; /**< Initial stack pointer value. */
	vector_table_entry_t reset;/*重启reset 向量函数指针*/
	vector_table_entry_t nmi;/*不可屏蔽中断向量函数指针*/
	vector_table_entry_t hard_fault;/*硬件错误hard_falut向量函数指针*/
	vector_table_entry_t memory_manage_fault; /* not in CM0 内存管理错误 向量函数指针，CM0不含此项 */
	vector_table_entry_t bus_fault;           /* not in CM0 总线错误*/
	vector_table_entry_t usage_fault;         /* not in CM0 指令使用错误*/
	vector_table_entry_t reserved_x001c[4];		/*预留*/
	vector_table_entry_t sv_call;				/*管理模式sv_call 向量函数指针*/
	vector_table_entry_t debug_monitor;       /* not in CM0 调试监控函数指针，M4和M3也没有*/
	vector_table_entry_t reserved_x0034;		/* */
	vector_table_entry_t pend_sv;				/*pend_sv向量函数指针 */
	vector_table_entry_t systick;				/* 系统时钟systick向量函数指针*/
	vector_table_entry_t irq[NVIC_IRQ_COUNT]; /*一般中断irq向量函数指针数组，宏NVIC_IRQ_COUNT被定义为0*/
} vector_table_t;

/* Common symbols exported by the linker script(s): */
extern unsigned _data_loadaddr, _data, _edata, _ebss, _stack;
extern vector_table_t vector_table;

#endif
