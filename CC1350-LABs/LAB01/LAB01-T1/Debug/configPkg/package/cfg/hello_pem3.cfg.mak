# invoke SourceDir generated makefile for hello.pem3
hello.pem3: .libraries,hello.pem3
.libraries,hello.pem3: package/cfg/hello_pem3.xdl
	$(MAKE) -f C:\Users\Nathan\Desktop\School\CPE403\WorkSpaceTM4C123G\CC1350_Lab01/src/makefile.libs

clean::
	$(MAKE) -f C:\Users\Nathan\Desktop\School\CPE403\WorkSpaceTM4C123G\CC1350_Lab01/src/makefile.libs clean

