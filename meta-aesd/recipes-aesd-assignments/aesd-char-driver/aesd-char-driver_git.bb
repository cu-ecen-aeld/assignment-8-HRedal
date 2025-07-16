SUMMARY = "This recipe is used for building the aesd-char-driver"
DESCRIPTION = "This recipe is used for building the aesd-char-driver"
LICENSE = "Unknown"
LIC_FILES_CHKSUM = "file://${WORKDIR}/aesd-char-driver/LICENSE;md5=f098732a73b5f6f3430472f5b094ffdb"

inherit module

SRC_URI = "git://git@github.com/cu-ecen-aeld/assignment-8-HRedal;protocol=ssh;branch=master"
SRCREV = "b31d8c64cdffb7ee4bde9eea0968051b5dd03117"
PV = "1.0+git${SRCPV}"

S = "${WORKDIR}/git/aesd-char-driver"
UNPACKDIR = "${S}"

# The inherit of module.bbclass will automatically name module packages with
# "kernel-module-" prefix as required by the oe-core build environment.
inherit module

EXTRA_OEMAKE:append:task-install = " -C ${STAGING_KERNEL_DIR} M=${S}"
EXTRA_OEMAKE += "KERNELDIR=${STAGING_KERNEL_DIR}"

inherit update-rc.d
INITSCRIPT_PACKAGES = "${PN}"
INITSCRIPT_NAME:${PN} = "aesd-char-driver_init"

KERNEL_VERSION_2 = "5.15.166-yocto-standard"
FILES:${PN} += "${sysconfdir}/*"
FILES:${PN} += "${base_libdir}/modules/${KERNEL_VERSION_2}/aesdchar_load"
FILES:${PN} += "${base_libdir}/modules/${KERNEL_VERSION_2}/aesdchar_unload"

do_configure () {
        :
}

do_compile () {
        oe_runmake
}



do_install () {
        # TODO: Install your binaries/scripts here.
        # Be sure to install the target directory with install -d first
        # Yocto variables ${D} and ${S} are useful here, which you can read about at 
        # https://docs.yoctoproject.org/ref-manual/variables.html?highlight=workdir#term-D
        # and
        # https://docs.yoctoproject.org/ref-manual/variables.html?highlight=workdir#term-S
        # See example at https://github.com/cu-ecen-aeld/ecen5013-yocto/blob/ecen5013-hello-world/meta-ecen5013/recipes-ecen5013/ecen5013-hello-world/ecen5013-hello-world_git.bb
        install -d ${D}${sysconfdir}/init.d
        install -m 0755 ${WORKDIR}/aesd-char-driver_init ${D}${sysconfdir}/init.d

        install -d ${D}${base_libdir}/modules/${KERNEL_VERSION_2}/

	install -m 0755 ${S}/aesdchar_unload ${D}${base_libdir}/modules/${KERNEL_VERSION_2}/
	install -m 0755 ${S}/aesdchar_load ${D}${base_libdir}/modules/${KERNEL_VERSION_2}/
	install -m 0755 ${S}/aesdchar.ko ${D}${base_libdir}/modules/${KERNEL_VERSION_2}/
}

RPROVIDES:${PN} += "aesd-char-driver"