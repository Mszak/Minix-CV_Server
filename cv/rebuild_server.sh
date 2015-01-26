service down cv
cp -r /mnt/Shared/CV_Server/cv /usr/src/servers/
make
make install
service up /usr/sbin/cv