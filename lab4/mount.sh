#! /bin/sh
echo "making"
make
echo "mounting mmc1"
mount /mnt/mmc1
cp kernel/kernel.bin /mnt/mmc1
cp tasks/bin/*.bin /mnt/mmc1
umount /mnt/mmc1
echo "done mounting"
