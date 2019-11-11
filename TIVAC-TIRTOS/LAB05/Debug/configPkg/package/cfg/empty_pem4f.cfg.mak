# invoke SourceDir generated makefile for empty.pem4f
empty.pem4f: .libraries,empty.pem4f
.libraries,empty.pem4f: package/cfg/empty_pem4f.xdl
	$(MAKE) -f C:\Users\Nathan\Desktop\TIVAC_TIRTOS_WS_LABS\TIVAC_TIRTOS_WS_LABS\Start\Lab_05\Project/src/makefile.libs

clean::
	$(MAKE) -f C:\Users\Nathan\Desktop\TIVAC_TIRTOS_WS_LABS\TIVAC_TIRTOS_WS_LABS\Start\Lab_05\Project/src/makefile.libs clean

