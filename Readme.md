**Step1:** Under the folder,compile module code-dram.c into dram.ko module.CMD:`make`  
**Step2:** Under the folder,compile fileview-App for checkout the physical memory.CMD:`make fileview`  
**Step3:** Install module for fileview-App reading mem by kernel's drv.CMD:`sudo insmod dram.ko`  
**Step4:** Create the device for drv(dram.ko).CMD:`sudo mknod /dev/dram c 85 0`  
**Step5:** Run the fileview-App.CMD:`sudo ./fileview /dev/dram`  
**Step6:** Reopen new terminal change directory into `usrapp-test`,compile main.c.CMD:`make`  
**Step7:** Run the main progress.CMD:`sudo ./main`
* *(Notice:you must use sudo previlige to run this code because of the code using file:"/proc/self/pagemap")*  

**Step8:** After run main code, you will get phy && vir address.Checkout phy address with fileview-App.  
**Step9:** Fileview-App terminal,insert search cmd-code:0x0000000A,then the phy-address getting from Step8.
* *(Here you can see the content at phy-address the same as your main-code setting.)*  
