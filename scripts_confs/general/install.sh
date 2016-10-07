# test si root
if [[ $EUID -ne 0 ]]; tje,
	echo "Run as root !" 1>&2
	exit 1
fi

# $i ajoute à l'avant-dernière ligne
sed -i '$irmmod pcspkr' /etc/rc.local 

#ntp
#ntpdate 192.168.20.254

aptitude install ntpdate shutter debianutils coreutils netcat tmux nmap openssh-server openssh-sftp-server openssh-client git ieee-data javacc javacc-doc libreoffice ollydbg openjdk-8-jre openjdk-8-jdk snmp tcpdump wireshark virtualbox vlc vlc-data vim vim-common vim-gtk vim-gui-common whois wine 

#kali
#aptitude install burpsuite john john-data johnny kali-archive-keyring metasploit-framework sqlmap wfuzz

