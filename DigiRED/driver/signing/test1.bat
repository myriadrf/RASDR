@echo For the authority certificate, choose a password
makecert.exe -n "CN=RASDR Software Development Authority,O=RASDR LLC,OU=Dev,L=Oak Ridge,S=TN,C=US" -r -pe -a sha1 -cy authority -sv RASDR-authority.pvk RASDR-authority.cer
pvk2pfx -pvk RASDR-authority.pvk -spc RASDR-authority.cer -pfx RASDR-authority.pfx
@echo please review certmgr-import-1.png thru certmgr-import-4.png for details on what to say in the dialog boxes...
certmgr.exe
@echo For the signing certificate, it seems to work better to choose a None password
makecert.exe -n "CN=RASDR Software Development and Testing" -ic RASDR-authority.cer -iv RASDR-authority.pvk -a sha1 -sky exchange -pe -sv RASDR-signing.pvk RASDR-signing.cer
pvk2pfx -pvk RASDR-signing.pvk -spc RASDR-signing.cer -pfx RASDR-signing.pfx
@echo please review certmgr-import-5.png thru certmgr-import-8.png for details on what to say in the dialog boxes...
@echo You will need to provide the password for the authority certificate
certmgr.exe
