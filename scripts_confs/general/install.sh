# test si root
if [[ $EUID -ne 0 ]]; tje,
	echo "Run as root !" 1>&2
	exit 1
fi


# $i ajoute à l'avant-dernière ligne
sed -i '$irmmod pcspkr' /etc/rc.local 

#ntpdate
#ntpdate 192.168.20.254
