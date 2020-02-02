Step1:Under this folder,compile the module code-dram.c into dram.ko module by CMD:`make`
Step2:Under this folder,compile the fileview-App for checking out the physical mem content by CMD:`make fileview`
Step3:Install the module for Linux-Sys in order the fileview-App can read the memory content from kernel's drv.CMD:`sudo insmod dram.ko`
Step4:Create the device for drv(dram.ko).CMD:`sudo mknod /dev/dram c 85 0`
Step5:Run the fileview-App.CMD:`sudo ./fileview /dev/dram`
Step6:Reopen New terminal and change directory into `usrapp-test`,compile the main.c code by CMD:`make`
Step7:Run the main progress.CMD:`sudo ./main` (Notice:you must use sudo previlige to run this code because of the code using file:"/proc/self/pagemap")
Step8:After run the main code, you will get the phy && vir address.Next you can checkout the phy address with fileview-App.
Step9:In fileview-App terminal section,insert the search cmd-code:0x0000000A,and then the phy-address you getting from Step8.
      (Here you can see the content at phy-address the same as your main-code setting.)
