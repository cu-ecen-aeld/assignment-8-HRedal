#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/elfnote-lto.h>
#include <linux/export-internal.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

#ifdef CONFIG_UNWINDER_ORC
#include <asm/orc_header.h>
ORC_HEADER;
#endif

BUILD_SALT;
BUILD_LTO_INFO;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif



static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0x15ba50a6, "jiffies" },
	{ 0x1000e51, "schedule" },
	{ 0x7ac144ac, "seq_printf" },
	{ 0x5b8239ca, "__x86_return_thunk" },
	{ 0x2d57e435, "pcpu_hot" },
	{ 0x8ddd8aad, "schedule_timeout" },
	{ 0xe2c17b5d, "__SCT__might_resched" },
	{ 0xfe487975, "init_wait_entry" },
	{ 0x8c26d495, "prepare_to_wait_event" },
	{ 0x92540fbf, "finish_wait" },
	{ 0xf0fdf6cb, "__stack_chk_fail" },
	{ 0x9ec6ca96, "ktime_get_real_ts64" },
	{ 0x484f6edf, "ktime_get_coarse_real_ts64" },
	{ 0x24d273d1, "add_timer" },
	{ 0xe2964344, "__wake_up" },
	{ 0xb42ee1dd, "seq_read" },
	{ 0x736dd663, "single_release" },
	{ 0x2bcd0276, "seq_lseek" },
	{ 0x8e7bdec2, "proc_create" },
	{ 0xaf289fb5, "proc_create_data" },
	{ 0x31264a9f, "single_open" },
	{ 0x30eb19e, "remove_proc_entry" },
	{ 0x4c03a563, "random_kmalloc_seed" },
	{ 0x29ac0981, "kmalloc_caches" },
	{ 0xdc327b3c, "kmalloc_trace" },
	{ 0x4a438502, "seq_puts" },
	{ 0xc6f46339, "init_timer_key" },
	{ 0x37a0cba, "kfree" },
	{ 0x3e3bad0a, "__tasklet_hi_schedule" },
	{ 0x9d2ab8ac, "__tasklet_schedule" },
	{ 0x2364c85a, "tasklet_init" },
	{ 0xd824c64e, "param_ops_int" },
	{ 0xbdfb6dbb, "__fentry__" },
	{ 0xd9a5ea54, "__init_waitqueue_head" },
	{ 0xb2b23fc2, "module_layout" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "1AD3EC83DB5837FA98F8704");
