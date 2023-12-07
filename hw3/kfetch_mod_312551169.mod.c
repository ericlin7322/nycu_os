#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/elfnote-lto.h>
#include <linux/export-internal.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

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
	{ 0x6cf7f77, "try_module_get" },
	{ 0x25f7aec2, "__register_chrdev" },
	{ 0xeea3c1d8, "__class_create" },
	{ 0x6c333d48, "device_create" },
	{ 0x122c3a7e, "_printk" },
	{ 0x3e2bc4cf, "device_destroy" },
	{ 0x6a2dd7c, "class_destroy" },
	{ 0x6bc3fbc0, "__unregister_chrdev" },
	{ 0x88db9f48, "__check_object_size" },
	{ 0x13c49cc2, "_copy_from_user" },
	{ 0x7682ba4e, "__copy_overflow" },
	{ 0xa19b956, "__stack_chk_fail" },
	{ 0xc7f2fe14, "pcpu_hot" },
	{ 0x3c3ff9fd, "sprintf" },
	{ 0x854ad34a, "init_task" },
	{ 0x6b10bee1, "_copy_to_user" },
	{ 0xd1d6e0b7, "boot_cpu_data" },
	{ 0x17de3d5, "nr_cpu_ids" },
	{ 0x9e683f75, "__cpu_possible_mask" },
	{ 0x21ea5251, "__bitmap_weight" },
	{ 0xc60d0620, "__num_online_cpus" },
	{ 0x40c7247c, "si_meminfo" },
	{ 0xc4f0da12, "ktime_get_with_offset" },
	{ 0x65929cae, "ns_to_timespec64" },
	{ 0x365acda7, "set_normalized_timespec64" },
	{ 0x87a21cb3, "__ubsan_handle_out_of_bounds" },
	{ 0xbdfb6dbb, "__fentry__" },
	{ 0x5c7d5920, "module_put" },
	{ 0x5b8239ca, "__x86_return_thunk" },
	{ 0x453e7dc, "module_layout" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "22A0E5F49A01D8ECDA84A17");
