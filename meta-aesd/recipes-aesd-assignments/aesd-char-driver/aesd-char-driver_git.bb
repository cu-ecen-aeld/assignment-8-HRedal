SUMMARY = "This recipe is used for building the aesd-char-driver"
DESCRIPTION = "This recipe is used for building the aesd-char-driver"
LICENSE = "GPL-2.0-only"
LIC_FILES_CHKSUM = "file://COPYING;md5=12f884d2ae1ff87c09e5b7ccc2c4ca7e"

inherit module

SRC_URI = "git://git@github.com/cu-ecen-aeld/assignment-8-HRedal;protocol=ssh;branch=master"

S = "${WORKDIR}/aesd-char-driver"
UNPACKDIR = "${S}"

# The inherit of module.bbclass will automatically name module packages with
# "kernel-module-" prefix as required by the oe-core build environment.

RPROVIDES:${PN} += "aesd-char-driver"