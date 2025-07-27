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
	{ 0xe2964344, "__wake_up" },
	{ 0x9d2ab8ac, "__tasklet_schedule" },
	{ 0x24d273d1, "add_timer" },
	{ 0xe2c17b5d, "__SCT__might_resched" },
	{ 0xfe487975, "init_wait_entry" },
	{ 0x1000e51, "schedule" },
	{ 0x8c26d495, "prepare_to_wait_event" },
	{ 0x82ee90dc, "timer_delete_sync" },
	{ 0xf0fdf6cb, "__stack_chk_fail" },
	{ 0x30eb19e, "remove_proc_entry" },
	{ 0xad73041f, "autoremove_wake_function" },
	{ 0xd5fd90f1, "prepare_to_wait" },
	{ 0x2d3385d3, "system_wq" },
	{ 0xc5b6f236, "queue_work_on" },
	{ 0x92540fbf, "finish_wait" },
	{ 0xb2fcb56d, "queue_delayed_work_on" },
	{ 0xa6059065, "param_ops_long" },
	{ 0xbdfb6dbb, "__fentry__" },
	{ 0xffeedf6a, "delayed_work_timer_fn" },
	{ 0xc6f46339, "init_timer_key" },
	{ 0x2364c85a, "tasklet_init" },
	{ 0xb42ee1dd, "seq_read" },
	{ 0x736dd663, "single_release" },
	{ 0x2bcd0276, "seq_lseek" },
	{ 0x8e7bdec2, "proc_create" },
	{ 0x5b8239ca, "__x86_return_thunk" },
	{ 0x31264a9f, "single_open" },
	{ 0x15ba50a6, "jiffies" },
	{ 0x2d57e435, "pcpu_hot" },
	{ 0x7ac144ac, "seq_printf" },
	{ 0x4a438502, "seq_puts" },
	{ 0xb2b23fc2, "module_layout" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "03EE6C5C8FA078D75CE91B5");
