cd C:\temp\digired-windows-1p3p3-signed\docs
makecert.exe -n "CN=RASDR Software Development Authority,O=RASDR LLC,OU=Dev,L=Oak Ridge,S=TN,C=US" -r -pe -a sha1 -cy authority -sv RASDR-authority.pvk RASDR-authority.cer
pvk2pfx -pvk RASDR-authority.pvk -spc RASDR-authority.cer -pfx RASDR-authority.pfx
@echo please review certmgr-import-1.png thru certmgr-import-4.png for details on what to say in the dialog boxes...
certmgr.exe
makecert.exe -n "CN=RASDR Software Development and Testing" -ic RASDR-authority.cer -iv RASDR-authority.pvk -a sha1 -sky exchange -pe -sv RASDR-signing.pvk RASDR-signing.cer
pvk2pfx -pvk RASDR-signing.pvk -spc RASDR-signing.cer -pfx RASDR-signing.pfx
@echo please review certmgr-import-5.png thru certmgr-import-8.png for details on what to say in the dialog boxes...
certmgr.exe
