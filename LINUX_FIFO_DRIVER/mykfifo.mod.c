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
	{ 0x139f2189, "__kfifo_alloc" },
	{ 0x122c3a7e, "_printk" },
	{ 0xa916b694, "strnlen" },
	{ 0xf23fcb99, "__kfifo_in" },
	{ 0x5b8239ca, "__x86_return_thunk" },
	{ 0xcbd4898c, "fortify_panic" },
	{ 0xf0fdf6cb, "__stack_chk_fail" },
	{ 0x13d0adf7, "__kfifo_out" },
	{ 0xdb760f52, "__kfifo_free" },
	{ 0xbdfb6dbb, "__fentry__" },
	{ 0x2fa5cadd, "module_layout" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "E0FCFAD04A508B4CE85990E");
