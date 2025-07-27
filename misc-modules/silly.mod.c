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
	{ 0xbdfb6dbb, "__fentry__" },
	{ 0x5b8239ca, "__x86_return_thunk" },
	{ 0xc6cbbc89, "capable" },
	{ 0xeb233a45, "__kmalloc" },
	{ 0x88db9f48, "__check_object_size" },
	{ 0x13c49cc2, "_copy_from_user" },
	{ 0x848d372e, "iowrite8" },
	{ 0x37a0cba, "kfree" },
	{ 0xb9e7429c, "memcpy_toio" },
	{ 0x6383b27c, "__x86_indirect_thunk_rdx" },
	{ 0x2f920aea, "__register_chrdev" },
	{ 0xde80cd09, "ioremap" },
	{ 0x122c3a7e, "_printk" },
	{ 0xedc03953, "iounmap" },
	{ 0x6bc3fbc0, "__unregister_chrdev" },
	{ 0xb19b445, "ioread8" },
	{ 0x6b10bee1, "_copy_to_user" },
	{ 0xa78af5f3, "ioread32" },
	{ 0x842c8e9d, "ioread16" },
	{ 0x7d628444, "memcpy_fromio" },
	{ 0x66cca4f9, "__x86_indirect_thunk_rcx" },
	{ 0xd824c64e, "param_ops_int" },
	{ 0xb2b23fc2, "module_layout" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "0E0EE13AD949C54BA1DE894");
