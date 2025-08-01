# Recipe created by recipetool
# This is the basis of a recipe and may need further editing in order to be fully functional.
# (Feel free to remove these comments when editing.)

# WARNING: the following LICENSE and LIC_FILES_CHKSUM values are best guesses - it is
# your responsibility to verify that the values are complete and correct.
#
# The following license files were not able to be identified and are
# represented as "Unknown" below, you will need to check them yourself:
#   LICENSE
LICENSE = "Unknown"
LIC_FILES_CHKSUM = "file://LICENSE;md5=f098732a73b5f6f3430472f5b094ffdb"

SRC_URI = "git://git@github.com/cu-ecen-aeld/assignment-7-HRedal.git;protocol=ssh;branch=master \
           file://0001-Previous-step-to-modify-Makefile-of-scull.patch \
           file://ldd-scull \ 
           file://scull_load.sh \
           file://scull_unload.sh \  
           "

# Modify these as desired
PV = "1.0+git${SRCPV}"
SRCREV = "5cff85c900f7577e2c5e38abe5d6027eac5b0872"

S = "${WORKDIR}/git"

inherit module
# Adding reference class which handles startup
inherit update-rc.d
# Flag package as one that uses init scripts
INITSCRIPT_PACKAGES = "${PN}" 
INITSCRIPT_NAME:${PN} = "ldd-scull"
# Specify files to be packaged
FILES:${PN} += "${bindir}/scull_load.sh ${bindir}/scull_unload.sh"
FILES:${PN} += "${sysconfdir}/init.d/ldd-scull"
TARGET_LDFLAGS += "-pthread -lrt"

EXTRA_OEMAKE:append:task-install = " -C ${STAGING_KERNEL_DIR} M=${S}/scull"
EXTRA_OEMAKE += "KERNELDIR=${STAGING_KERNEL_DIR}"

do_install:append(){
    install -d ${D}${bindir}
    install -m 0755 ${WORKDIR}/scull_load.sh ${D}${bindir}/scull_load.sh
    install -m 0755 ${WORKDIR}/scull_unload.sh ${D}${bindir}/scull_unload.sh

    # Install the init script
    install -d ${D}${sysconfdir}/init.d
    install -m 0755 ${WORKDIR}/ldd-scull ${D}${sysconfdir}/init.d
}
