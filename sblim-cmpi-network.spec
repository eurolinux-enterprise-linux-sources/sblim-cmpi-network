%global provider_dir %{_libdir}/cmpi

Name:           sblim-cmpi-network
Version:        1.4.0
Release:        9%{?dist}
Summary:        SBLIM Network Instrumentation

Group:          Applications/System
License:        EPL
URL:            http://sblim.wiki.sourceforge.net/
Source0:        http://downloads.sourceforge.net/sblim/%{name}-%{version}.tar.bz2

Patch0:         sblim-cmpi-network-1.4.0-network-devices-arbitrary-names-support.patch
# Patch1: use Pegasus root/interop instead of root/PG_Interop
Patch1:         sblim-cmpi-network-1.4.0-pegasus-interop.patch

BuildRequires:  sblim-cmpi-base-devel >= 1.5 sblim-cmpi-devel
Requires:       sblim-cmpi-base >= 1.5 cim-server cim-schema

%description
Standards Based Linux Instrumentation Network Providers

%package        devel
Summary:        SBLIM Network Instrumentation Header Development Files
Group:          Development/Libraries
Requires:       %{name} = %{version}-%{release}

%description    devel
SBLIM Base Network Development Package

%package        test
Summary:        SBLIM Network Instrumentation Testcases
Group:          Applications/System
Requires:       sblim-cmpi-network = %{version}-%{release}

%description    test
SBLIM Base Network Testcase Files for SBLIM Testsuite

%prep
%setup -q
%patch0 -p1 -b .network-devices-arbitrary-names-support
%patch1 -p1 -b .pegasus-interop

%build
%ifarch s390 s390x ppc ppc64
export CFLAGS="$RPM_OPT_FLAGS -fsigned-char"
%else
export CFLAGS="$RPM_OPT_FLAGS"
%endif
%configure \
        --disable-static \
        TESTSUITEDIR=%{_datadir}/sblim-testsuite \
        PROVIDERDIR=%{provider_dir}
sed -i 's|^hardcode_libdir_flag_spec=.*|hardcode_libdir_flag_spec=""|g' libtool
sed -i 's|^runpath_var=LD_RUN_PATH|runpath_var=DIE_RPATH_DIE|g' libtool
make

%install
make install DESTDIR=$RPM_BUILD_ROOT
# remove unused libtool files
rm -f $RPM_BUILD_ROOT/%{_libdir}/*.la
rm -f $RPM_BUILD_ROOT/%{provider_dir}/*.la
# shared libraries
mkdir -p $RPM_BUILD_ROOT/%{_sysconfdir}/ld.so.conf.d
echo "%{_libdir}/cmpi" > $RPM_BUILD_ROOT/%{_sysconfdir}/ld.so.conf.d/%{name}-%{_arch}.conf

%files
%docdir %{_datadir}/doc/%{name}-%{version}
%{_datadir}/%{name}
%{_datadir}/doc/%{name}-%{version}
%{_libdir}/*.so.*
%{provider_dir}/*.so
%config(noreplace) %{_sysconfdir}/ld.so.conf.d/%{name}-%{_arch}.conf

%files devel
%{_includedir}/*
%{_libdir}/*.so
%{_datadir}/doc/%{name}-%{version}

%files test
%{_datadir}/sblim-testsuite
%{_datadir}/doc/%{name}-%{version}

%global PEGASUS_MOF CIM_IPProtocolEndpoint,CIM_NetworkPort,CIM_EthernetPort,CIM_TokenRingPort,CIM_PortImplementsEndpoint

%pre
if [ "$1" -gt 1 ]; then
# If upgrading, deregister old version
    %{_datadir}/%{name}/provider-register.sh -d \
        -t sfcb \
        -m %{_datadir}/%{name}/*.mof \
        -r %{_datadir}/%{name}/*.registration \
        > /dev/null 2>&1 || :;
fi

%post
/sbin/ldconfig
# Register Schema and Provider - this is higly provider specific  
# tog-pegasus needs some schemes registered first  
if [ -x /usr/bin/peg-loadmof.sh ]; then
   peg-loadmof.sh -n root/cimv2 /usr/share/mof/cim-current/*/{%{PEGASUS_MOF}}.mof > /dev/null 2>&1 || :;
   /sbin/service tog-pegasus try-restart > /dev/null 2>&1 || :;
fi
if [ "$1" -ge 1 ]; then
# Register Schema and Provider
    %{_datadir}/%{name}/provider-register.sh \
        -t sfcb \
        -m %{_datadir}/%{name}/*.mof \
        -r %{_datadir}/%{name}/*.registration \
        > /dev/null 2>&1 || :;
fi

%preun
if [ "$1" -eq 0 ]; then
# Deregister only if not upgrading
    %{_datadir}/%{name}/provider-register.sh -d \
        -t sfcb \
        -m %{_datadir}/%{name}/*.mof \
        -r %{_datadir}/%{name}/*.registration \
        > /dev/null 2>&1 || :;
fi

%postun -p /sbin/ldconfig

%changelog
* Wed Aug 14 2013 Vitezslav Crhonek <vcrhonek@redhat.com> - 1.4.0-9
- Use Pegasus root/interop instead of root/PG_Interop

* Thu Feb 14 2013 Fedora Release Engineering <rel-eng@lists.fedoraproject.org> - 1.4.0-8
- Rebuilt for https://fedoraproject.org/wiki/Fedora_19_Mass_Rebuild

* Wed Sep 05 2012 Vitezslav Crhonek <vcrhonek@redhat.com> - 1.4.0-7
- Fix issues found by fedora-review utility in the spec file

* Sat Jul 21 2012 Fedora Release Engineering <rel-eng@lists.fedoraproject.org> - 1.4.0-6
- Rebuilt for https://fedoraproject.org/wiki/Fedora_18_Mass_Rebuild

* Thu May 10 2012 Vitezslav Crhonek <vcrhonek@redhat.com> - 1.4.0-5
- Add support for arbitrary names of network devices in Linux_NetworkPortImplementsIPEndpoint
  association
  Resolves: #682386
- Remove macros from changelog, register to sfcb

* Sat Jan 14 2012 Fedora Release Engineering <rel-eng@lists.fedoraproject.org> - 1.4.0-4
- Rebuilt for https://fedoraproject.org/wiki/Fedora_17_Mass_Rebuild

* Wed Feb 09 2011 Fedora Release Engineering <rel-eng@lists.fedoraproject.org> - 1.4.0-3
- Rebuilt for https://fedoraproject.org/wiki/Fedora_15_Mass_Rebuild

* Wed Oct  6 2010 Praveen K Paladugu <praveen_paladugu@dell.com> - 1.4.0-2
- de-registering the providers properly in %%pre and %%preun

* Wed Oct  6 2010 Vitezslav Crhonek <vcrhonek@redhat.com> - 1.4.0-1
- Update to sblim-cmpi-network-1.4.0
- Remove CIMOM dependencies

* Thu Aug 13 2009 Srinivas Ramanatha <srinivas_ramanatha@dell.com> - 1.3.8-2
- modified the spec file to fix some rpmlint warnings

* Tue May 26 2009 Vitezslav Crhonek <vcrhonek@redhat.com> - 1.3.8-1
- Initial support
