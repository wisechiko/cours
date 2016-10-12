#!/bin/bash

# test si root
if [[ $EUID -ne 0 ]]; tje,
	echo "Run as root !" 1>&2
	exit 1
fi


######INSTALLATIONS######

#kali repo
echo "deb http://http.kali.org/kali kali-rolling main contrib non-free" >> /etc/apt/sources.list
aptitude update

#kali packages
aptitude install burpsuite john john-data johnny kali-archive-keyring metasploit-framework sqlmap wfuzz

#standard packages
aptitude install ntpdate shutter debianutils coreutils netcat tmux nmap openssh-server openssh-sftp-server openssh-client git ieee-data javacc javacc-doc libreoffice ollydbg openjdk-8-jre openjdk-8-jdk snmp tcpdump wireshark virtualbox vlc vlc-data vim vim-common vim-gtk vim-gui-common whois wine libreoffice

#suppression des repos kali
head -n -1 /etc/apt/sources.list > youpi.txt ; mv youpi.txt /etc/apt/sources.list

aptitude upgrade



######CONFS######

#bip de la machine
#$i ajoute à l'avant-dernière ligne
sed -i '$irmmod pcspkr' /etc/rc.local 

#ntp
NTPFILE=/etc/init.d/ntpdate

if [[ -f "$NTPFILE" ]]
then echo "ntpdate file already exists !"
else
	echo 'Le mettre manuellement avec les commentaires de ce script'
	#echo '#!/bin/bash' > $NTPFILE
	#echo 'ntpdate 192.168.20.254' >> $NTPFILE
	#echo 'hwclock --systohc' >> $NTPFILE
fi



######FICHIERS######

mv ../user/* /home/*/
mv ../root/* /root/
mv sources.list /etc/apt/sources.list
mv bash.bashrc /etc/bash.bashrc
mv vimrc /etc/vim/vimrc
mv sshd_config /etc/ssh/sshd_config

		#on pourrait rajouter GIT ici


#adblock, ghostery, firebug, checkmyhttps.net, ssleuth, calomel?
#Automatisable, mais posera des problème de version
echo "Adblock/Ghostery/Firebug"

updatedb
