#include <stdio.h>
#include <unistd.h>
#include <inttypes.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define page_map_file "/proc/self/pagemap"

#define PFN_MASK ((((uint64_t)1)<<55)-1)
#define PFN_PRESENT_FLAG (((uint64_t)1)<<63)

int mem_addr_vir2phy(unsigned long vir, unsigned long *phy);

void main(void)
{
  int a = 0x12345678;
  unsigned long phy;
  mem_addr_vir2phy((unsigned long)&a,&phy);
  printf("viraddr=%p,phyaddr=0x%lx\n",&a,phy);
  while(1){
    sleep(100);
  }
}

int mem_addr_vir2phy(unsigned long vir, unsigned long *phy)
{
  int fd;
  int page_size=getpagesize();
  printf("page_size=%d\n",page_size);
  unsigned long vir_page_idx = vir / page_size;
  printf("vir_page_idx=%ld\n",vir_page_idx);
  unsigned long pfn_item_offset = vir_page_idx * sizeof(uint64_t);
  printf("pfn_item_offset=%ld\n",pfn_item_offset);
  uint64_t pfn_item;

  fd = open(page_map_file, O_RDONLY);
  if(fd<0)
  {
    printf("open %s failed\n", page_map_file);
    return -1;
  }
  if((off_t)-1 == lseek(fd,pfn_item_offset,SEEK_SET))
  {
    printf("lseek %s failed\n",page_map_file);
    return -1;
  }
  if(sizeof(uint64_t) != read(fd, &pfn_item, sizeof(uint64_t)))
  {
    printf("read %s failed\n",page_map_file);
    return -1;
  }
  printf("pfn_item=0x%llx\n",pfn_item);
  if(0 == (pfn_item & PFN_PRESENT_FLAG))
  {
    printf("page is not present.\n");
    return -1;
  }
  printf("PFN_MASK=0x%llx\n",PFN_MASK);
  *phy = (pfn_item & PFN_MASK)*page_size + vir % page_size;
  return 0;
}
