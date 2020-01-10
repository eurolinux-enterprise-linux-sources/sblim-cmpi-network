# $Id: Makefile.am,v 1.6 2009/05/23 02:52:50 tyreld Exp $
# ==================================================================
# (C) Copyright IBM Corp. 2002, 2009
#
# THIS FILE IS PROVIDED UNDER THE TERMS OF THE ECLIPSE PUBLIC LICENSE
# ("AGREEMENT"). ANY USE, REPRODUCTION OR DISTRIBUTION OF THIS FILE
# CONSTITUTES RECIPIENTS ACCEPTANCE OF THE AGREEMENT.
#
# You can obtain a current copy of the Eclipse Public License from
# http://www.opensource.org/licenses/cpl1.0.php
#
# Author:       Viktor Mihajlovski <mihajlov@de.ibm.com>
# Contributors: Dr. Gareth S. Bestor <bestorga@us.ibm.com>
# Description:  Automake input file for OS Base Providers
# ==================================================================


# SBLIM Include Directory
sblimincdir = $(includedir)/sblim

# Start from an empty extra distribution file list
EXTRA_DIST=

# docdir defines where the documentation goes
docdir=$(datadir)/doc/$(PACKAGE)-$(VERSION)

#
# Automake instructions for documentation
#
doc_DATA=README AUTHORS COPYING 

# ADD EXTRA DOC FILES IF PRESENT
doc_DATA+=DEBUG README.tog-pegasus
EXTRA_DIST+=DEBUG README.tog-pegasus

# providerdir defines where provider libraries will be installed (@PROVIDERDIR@ is set by the configure script). 
providerdir = @PROVIDERDIR@

#
# Automake instructions for main dir
#

#  OSBase CMPI provider libraries
provider_LTLIBRARIES = 	libcmpiOSBase_EthernetPortProvider.la \
			libcmpiOSBase_TokenRingPortProvider.la \
			libcmpiOSBase_LocalLoopbackPortProvider.la \
			libcmpiOSBase_IPProtocolEndpointProvider.la \
			libcmpiOSBase_CSNetworkPortProvider.la \
			libcmpiOSBase_NetworkPortImplementsIPEndpointProvider.la 

# Ethernet Port
libcmpiOSBase_EthernetPortProvider_la_SOURCES = \
		cmpiOSBase_EthernetPortProvider.c \
		cmpiOSBase_EthernetPort.c
libcmpiOSBase_EthernetPortProvider_la_LIBADD = \
		-lOSBase_CommonNetwork 
libcmpiOSBase_EthernetPortProvider_la_LDFLAGS = -avoid-version

# Token Ring Port
libcmpiOSBase_TokenRingPortProvider_la_SOURCES = \
		cmpiOSBase_TokenRingPortProvider.c \
		cmpiOSBase_TokenRingPort.c
libcmpiOSBase_TokenRingPortProvider_la_LIBADD = \
		-lOSBase_CommonNetwork 
libcmpiOSBase_TokenRingPortProvider_la_LDFLAGS = -avoid-version

# Local Loopback Port
libcmpiOSBase_LocalLoopbackPortProvider_la_SOURCES = \
		cmpiOSBase_LocalLoopbackPortProvider.c \
		cmpiOSBase_LocalLoopbackPort.c
libcmpiOSBase_LocalLoopbackPortProvider_la_LIBADD = \
		-lOSBase_CommonNetwork 
libcmpiOSBase_LocalLoopbackPortProvider_la_LDFLAGS = -avoid-version

# IP Protocol Endpoint
libcmpiOSBase_IPProtocolEndpointProvider_la_SOURCES = \
		cmpiOSBase_IPProtocolEndpointProvider.c \
		cmpiOSBase_IPProtocolEndpoint.c \
		OSBase_IPProtocolEndpoint.c
libcmpiOSBase_IPProtocolEndpointProvider_la_LIBADD = \
		-lOSBase_CommonNetwork
libcmpiOSBase_IPProtocolEndpointProvider_la_LDFLAGS = -avoid-version

# CS Network Port (Association)
libcmpiOSBase_CSNetworkPortProvider_la_SOURCES = \
		cmpiOSBase_CSNetworkPortProvider.c
libcmpiOSBase_CSNetworkPortProvider_la_LIBADD = \
		-lOSBase_CommonNetwork
libcmpiOSBase_CSNetworkPortProvider_la_LDFLAGS = -avoid-version

# Network Port Implements IP Endpoint (Association)
libcmpiOSBase_NetworkPortImplementsIPEndpointProvider_la_SOURCES = \
		cmpiOSBase_NetworkPortImplementsIPEndpointProvider.c \
		cmpiOSBase_NetworkPortImplementsIPEndpoint.c 
libcmpiOSBase_NetworkPortImplementsIPEndpointProvider_la_LIBADD = \
		-lOSBase_CommonNetwork
libcmpiOSBase_NetworkPortImplementsIPEndpointProvider_la_LDFLAGS = -avoid-version

# OSBase support utility libraries
lib_LTLIBRARIES = libOSBase_CommonNetwork.la

libOSBase_CommonNetwork_la_SOURCES=OSBase_CommonNetwork.c
libOSBase_CommonNetwork_la_LIBADD=-lcmpiOSBase_Common

# Installable Header Files
sbliminc_HEADERS = OSBase_CommonNetwork.h

# Non-Installable Header Files
noinst_HEADERS = OSBase_IPProtocolEndpoint.h \
	cmpiOSBase_EthernetPort.h \
	cmpiOSBase_TokenRingPort.h \
	cmpiOSBase_LocalLoopbackPort.h \
	cmpiOSBase_IPProtocolEndpoint.h \
	cmpiOSBase_NetworkPortImplementsIPEndpoint.h

# We must explicity add the RPM spec file to the distribution package
EXTRA_DIST+=$(PACKAGE).spec $(PACKAGE).rh.spec

#
# Automake instructions for ./mof subdir
#
SCHEMAS=mof/Linux_Network.mof 
REGISTRATIONS=mof/Linux_Network.registration

# We must explicity add all the schema files to the distribution package
pkgdata_DATA=$(SCHEMAS) $(REGISTRATIONS)
pkgdata_SCRIPTS=provider-register.sh
EXTRA_DIST+=mof $(pkgdata_SCRIPTS)

# Register the provider(s) and class definition(s) to the current CIM server/CIMOM
postinstall:
	sh provider-register.sh -t @CIMSERVER@ -r $(REGISTRATIONS) -m $(SCHEMAS)

preuninstall:
	sh provider-register.sh -d -t @CIMSERVER@ -r $(REGISTRATIONS) -m $(SCHEMAS)

dist-hook:
	test -d "$(distdir)" &&	rm -rf `find $(distdir) -type d -name CVS`
#
# Automake instructions for ./test subdir
#
EXTRA_DIST+=test README.TEST
if TESTSUITE
testsuitedir=@TESTSUITEDIR@
testsuitesystemdir=@TESTSUITEDIR@/system/linux
testsuitecimdir=@TESTSUITEDIR@/cim

testsuite_SCRIPTS=test/test-cmpi-network.sh

testsuitesystem_DATA=test/system/linux/Linux_CSNetworkPort.system \
	test/system/linux/Linux_EthernetPort.system \
	test/system/linux/Linux_IPProtocolEndpoint.system \
	test/system/linux/Linux_LocalLoopbackPort.system \
	test/system/linux/Linux_TokenRingPort.system
testsuitesystem_SCRIPTS=test/system/linux/Linux_EthernetPort.pl \
	test/system/linux/Linux_IPProtocolEndpoint.pl \
	test/system/linux/Linux_LocalLoopbackPort.pl \
	test/system/linux/Linux_TokenRingPort.pl
testsuitecim_DATA=test/cim/Linux_CSNetworkPort.cim \
	test/cim/Linux_EthernetPort.cim \
	test/cim/Linux_IPProtocolEndpoint.cim \
	test/cim/Linux_LocalLoopbackPort.cim \
	test/cim/Linux_NetworkPortImplementsIPEndpoint.cim \
	test/cim/Linux_TokenRingPort.cim 

runtest: install
	cd $(DESTDIR)$(TESTSUITEDIR) &&	./test-cmpi-network.sh

doc_DATA+=README.TEST
endif
