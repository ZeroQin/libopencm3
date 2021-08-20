/*
 * This file is part of the libopencm3 project.
 *
 * Copyright (C) 2010 Piotr Esden-Tempski <piotr@esden.net>,
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

#include <libopencm3/cm3/scb.h>
#include <libopencm3/cm3/vector.h>

/* load optional platform dependent initialization routines */
#include "../dispatch/vector_chipset.c"
/* load the weak symbols for IRQ_HANDLERS */
#include "../dispatch/vector_nvic.c"

/* Less common symbols exported by the linker script(s): */
typedef void (*funcp_t) (void);
extern funcp_t __preinit_array_start, __preinit_array_end;
extern funcp_t __init_array_start, __init_array_end;
extern funcp_t __fini_array_start, __fini_array_end;

void main(void);
void blocking_handler(void);
void null_handler(void);

__attribute__ ((section(".vectors")))/* 变量vector_table属于vectors段 */
vector_table_t vector_table = {
	.initial_sp_value = &_stack,/* 栈指针指向的地址，_stack在链接脚本中被定义为ram区最高地址 */
	.reset = reset_handler,/* 重启reset向量函数，reset_handler 弱属性 */
	.nmi = nmi_handler,/*不可屏蔽中断，默认什么都不做*/
	.hard_fault = hard_fault_handler,/*硬件错误，默认死循环*/

/* Those are defined only on CM3 or CM4 */
#if defined(__ARM_ARCH_7M__) || defined(__ARM_ARCH_7EM__)/*若为CM3和CM4*/
	.memory_manage_fault = mem_manage_handler,/*内存管理错误，死循环*/
	.bus_fault = bus_fault_handler,/*总线错误，死循环*/
	.usage_fault = usage_fault_handler,/*指令使用错误,死循环*/
	.debug_monitor = debug_monitor_handler,/*调试监控，什么都不做*/
#endif

	.sv_call = sv_call_handler,/*管理模式，什么都不做*/
	.pend_sv = pend_sv_handler,/*什么都不做*/
	.systick = sys_tick_handler,/*弱属性 ,再bl.c中被重定义了*/
	.irq = {/* 空*/
		IRQ_HANDLERS
	}
};

/* 定义为弱属性，可直接在其他地方重写此函数；
*  定义为裸属性，确保编译器对reset_handler函数不添加任何加载和卸载代码 */

void __attribute__ ((weak, naked)) reset_handler(void)
{
	volatile unsigned *src, *dest;
	funcp_t *fp;

	/* 用数据段存储的参数初始化内存空间，变量定义见链接脚本。 */
	/* _data_loadaddr：数据段的起始加载地址，即在flash上的首地址 */
	/* _data：数据段的起始运行地址，即在RAM中的首地址 */
	/* _edata：数据段的截止运行地址，即在RAM中的末地址 */
	for (src = &_data_loadaddr, dest = &_data;
		dest < &_edata;
		src++, dest++) {
		*dest = *src;
	}

	/* BSS段清零，变量定义见各自的链接脚本 */
	/* _ebss：bss段的截止运行地址，其起始运行地址紧接数据段的末地址 */
	while (dest < &_ebss) {/*把_edata 到 _ebss 之间置零*/
		*dest++ = 0;
	}

	/* Ensure 8-byte alignment of stack pointer on interrupts */
	/* Enabled by default on most Cortex-M parts, but not M3 r1 */
	/* 确保进入异常模式时堆栈指针8字节对齐。此设置对M3和R1架构不起作用 */
	SCB_CCR |= SCB_CCR_STKALIGN;

	/* might be provided by platform specific vector.c */
	/* 调用与架构相关的pre_main函数
	*（主控FMU在文件libopencm3/lib/stm32/f4/vector_chipset.c中；
	*IO协处理器在文件libopencm3/lib/cm3/vector.c中，且为空函数）。 */
	pre_main();

	/* Constructors. */
	/* 依次调用所有C++定义的构造函数，变量定义见链接脚本。 */
	/* __preinit_array_start：preinit_array段首地址 */
	/* __preinit_array_end：preinit_array段末地址 */
	/* __init_array_start：init_array段首地址 */
	/* __init_array_end：init_array段末地址 */
	for (fp = &__preinit_array_start; fp < &__preinit_array_end; fp++) {
		(*fp)();
	}
	for (fp = &__init_array_start; fp < &__init_array_end; fp++) {
		(*fp)();
	}

	/* Call the application's entry point. */
	/* 调用main函数（主控FMU在文件main_f4.c中，IO协处理器在文件main_f1.c中）。 */
	main();

	/* Destructors. */
	/* 依次调用所有C++定义的析构函数，变量定义见链接脚本 */
	/* __fini_array_start：fini_array段首地址 */
	/* __fini_array_end：fini_array段末地址 */
	for (fp = &__fini_array_start; fp < &__fini_array_end; fp++) {
		(*fp)();
	}
}

void blocking_handler(void)
{
	while (1);
}

void null_handler(void)
{
	/* Do nothing. */
}
/*采用 #pragma weak name 形式时，指令使 name 成为弱符号*/
#pragma weak nmi_handler = null_handler
#pragma weak hard_fault_handler = blocking_handler
#pragma weak sv_call_handler = null_handler
#pragma weak pend_sv_handler = null_handler
#pragma weak sys_tick_handler = null_handler

/* Those are defined only on CM3 or CM4 */
#if defined(__ARM_ARCH_7M__) || defined(__ARM_ARCH_7EM__)
#pragma weak mem_manage_handler = blocking_handler
#pragma weak bus_fault_handler = blocking_handler
#pragma weak usage_fault_handler = blocking_handler
#pragma weak debug_monitor_handler = null_handler
#endif

