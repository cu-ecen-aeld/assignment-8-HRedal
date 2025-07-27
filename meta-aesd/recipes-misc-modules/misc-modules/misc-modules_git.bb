# Recipe created by recipetool
# This is the basis of a recipe and may need further editing in order to be fully functional.
# (Feel free to remove these comments when editing.)

# WARNING: the following LICENSE and LIC_FILES_CHKSUM values are best guesses - it is
# your responsibility to verify that the values are complete and correct.
#
# The following license files were not able to be identified and are
# represented as "Unknown" below, you will need to check them yourself:
#   LICENSE
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://LICENSE;md5=f098732a73b5f6f3430472f5b094ffdb"

SRC_URI = "git://github.com/cu-ecen-aeld/assignment-7-HRedal.git;protocol=ssh;branch=master \
           file://ldd-misc-modules \
           file://module_load.sh \
           file://module_unload.sh \
           file://0001-Finishing-misc-modules-recipe.patch \
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
INITSCRIPT_NAME:${PN} = "ldd-misc-modules"
# Specify files to be packaged
FILES:${PN} += "${bindir}/module_load.sh ${bindir}/module_unload.sh"
FILES:${PN} += "${sysconfdir}/init.d/ldd-misc-modules"

EXTRA_OEMAKE:append:task-install = " -C ${STAGING_KERNEL_DIR} M=${S}/misc-modules"
EXTRA_OEMAKE += "KERNELDIR=${STAGING_KERNEL_DIR}"

do_install:append(){
    install -d ${D}${bindir}
    install -m 0755 ${WORKDIR}/module_load.sh ${D}${bindir}/module_load.sh
    install -m 0755 ${WORKDIR}/module_unload.sh ${D}${bindir}/module_unload.sh

    # Install the init script
    install -d ${D}${sysconfdir}/init.d
    install -m 0755 ${WORKDIR}/ldd-misc-modules ${D}${sysconfdir}/init.d

}