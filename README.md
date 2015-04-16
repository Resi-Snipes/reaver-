
#Overview
	reaver-wps-fork-t6x is a modification done from a fork of reaver (https://code.google.com/p/reaver-wps-fork/)
	This modified version uses the attack Pixie Dust to find the correct pin number of wps
	The attack used in this version was developed by Wiire (https://github.com/wiire/pixiewps)

#Install Required Libraries and Tools

	Libraries for reaver
		sudo apt-get install libpcap-dev aircrack-ng sqlite3 libsqlite3-dev
    
	Tools
		You must have installed the pixiewps created by Wiire (https://github.com/wiire/pixiewps)


#Compile and Install

	Build Reaver
	
		cd reaver-wps-fork-t6x-master
		cd src
		./configure
		make

	Install Reaver
	
	sudo make install
    
#Usage Reaver

	Reaver v1.5.1 WiFi Protected Setup Attack Tool
	Copyright (c) 2011, Tactical Network Solutions, Craig Heffner <cheffner@tacnetsol.com>
	mod by t6_x <t6_x@hotmail.com>
	mod by DataHead

	Required Arguments:
			-i, --interface=<wlan>          Name of the monitor-mode interface to use
			-b, --bssid=<mac>               BSSID of the target AP

	Optional Arguments:
			-m, --mac=<mac>                 MAC of the host system
			-e, --essid=<ssid>              ESSID of the target AP
			-c, --channel=<channel>         Set the 802.11 channel for the interface (implies -f)
			-o, --out-file=<file>           Send output to a log file [stdout]
			-s, --session=<file>            Restore a previous session file
			-C, --exec=<command>            Execute the supplied command upon successful pin recovery
			-D, --daemonize                 Daemonize reaver
			-a, --auto                      Auto detect the best advanced options for the target AP
			-f, --fixed                     Disable channel hopping
			-5, --5ghz                      Use 5GHz 802.11 channels
			-v, --verbose                   Display non-critical warnings (-vv for more)
			-q, --quiet                     Only display critical messages
			-K, --pixie-dust=<number>       [1] PKE & E-Hash1, E-Hash2 ( implies -S)
							[2] PKE & E-Hash1, E-Hash2 & E-Nonce ( implies -S)
							[3] PKE, PKR & E-Hash1, E-Hash2 & E-Nonce
							
			-Z, --no-auto-pass              Do NOT run retrieve WPA password if PixieWps attack is successful 
			-h, --help                      Show help

	Advanced Options:
			-p, --pin=<wps pin>             Use the specified 4 or 8 digit WPS pin
			-d, --delay=<seconds>           Set the delay between pin attempts [1]
			-l, --lock-delay=<seconds>      Set the time to wait if the AP locks WPS pin attempts [60]
			-g, --max-attempts=<num>        Quit after num pin attempts
			-x, --fail-wait=<seconds>       Set the time to sleep after 10 unexpected failures [0]
			-r, --recurring-delay=<x:y>     Sleep for y seconds every x pin attempts
			-t, --timeout=<seconds>         Set the receive timeout period [5]
			-T, --m57-timeout=<seconds>     Set the M5/M7 timeout period [0.20]
			-A, --no-associate              Do not associate with the AP (association must be done by another application)
			-N, --no-nacks                  Do not send NACK messages when out of order packets are received
			-S, --dh-small                  Use small DH keys to improve crack speed
			-L, --ignore-locks              Ignore locked state reported by the target AP
			-E, --eap-terminate             Terminate each WPS session with an EAP FAIL packet
			-n, --nack                      Target AP always sends a NACK [Auto]
			-w, --win7                      Mimic a Windows 7 registrar [False]
			-X, --exhaustive                Set exhaustive mode from the beginning of the session [False]
			-1, --p1-index                  Set initial array index for the first half of the pin [False]
			-2, --p2-index                  Set initial array index for the second half of the pin [False]
			
			-P, --pixiedust-loop            Set into PixieLoop mode (doesn't send M4, and loops through to M3) [False]

	Example:
			reaver -i mon0 -b 00:90:4C:C1:AC:21 -vv -K 1
			
#Option (K)

	The -K option 1 run pixiewps without PKR and the hash1 = hash2 = 0
	The -K option 2 runs pixiewps without PKR and the hash1 = hash2 = 0 but using the -n option of pixiewps (E-Nonce)
	The -K option 3 runs pixiewps with PKE, PKR and the hash1 = hash2 = e-Nonce	

	**Use the reaver with the option -S when you take your test without the PKR	


#Usage Wash

	Wash v1.5.1 WiFi Protected Setup Scan Tool
	Copyright (c) 2011, Tactical Network Solutions, Craig Heffner <cheffner@tacnetsol.com>
	mod by t6_x <t6_x@hotmail.com> & DataHead

	Required Arguments:
			-i, --interface=<iface>              Interface to capture packets on
			-f, --file [FILE1 FILE2 FILE3 ...]   Read packets from capture files

	Optional Arguments:
			-c, --channel=<num>                  Channel to listen on [auto]
			-o, --out-file=<file>                Write data to file
			-n, --probes=<num>                   Maximum number of probes to send to each AP in scan mode [15]
			-D, --daemonize                      Daemonize wash
			-C, --ignore-fcs                     Ignore frame checksum errors
			-5, --5ghz                           Use 5GHz 802.11 channels
			-s, --scan                           Use scan mode
			-u, --survey                         Use survey mode [default]
			-P, --file-output-piped              Allows Wash output to be piped. Example. wash x|y|z...
			-g, --get-chipset                    Pipes output and runs reaver alongside to get chipset
			-h, --help                           Show help

	Example:
			wash -i mon0
			
			
#Option (g)
		The option -g of wash, automatically runs the reaver to receive the chipset data. 
		If the AP does not respond to them quickly, this option will be slower to display the data,
		because reaver will stay running until it gets the data or until you reach your timeout limit (30 secs)		
			
			

#Contribution
	Modifications made by t6_x
	Modifications made by DataHead

	Some ideas made by nuroo
	Some ideas made by kcdtv

#Special thanks
	Soxrok2212 for all work done to help in the development of tools
	Wiire for developing the pixiewps
	Craig Heffner for creating the reaver
