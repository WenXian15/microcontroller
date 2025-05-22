Raspberry PI uart bring up 
overlay - https://forums.raspberrypi.com/viewtopic.php?t=244827
/boot/config.txt
/dev/tty*

Issues
1. Issues with enabling uart0
2. ttyAMA2 is Uart2 or Uart3 and what is ttyAMA0?


block devices and character devices
lsblk
cat /proc/devices
cat /proc/interrupt


Ch. 9 Persistent Storage
stat -fc %s
stat -f /

https://adil.medium.com/ext4-filesystem-data-blocks-super-blocks-inode-structure-1afb95c8e4ab
