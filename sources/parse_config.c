#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

void parse_endpoints(const char *directory) {
  DIR *d;
  struct dirent *dir;
  char buffer[1024];
  

  d = opendir(directory);
  if (d) {
    while ((dir = readdir(d)) != NULL) {
      //if (dir->d_name == ".."
      //  || dir->d_name == ".")
      //continue;
      snprintf(buffer, sizeof(buffer), "%s/%s", directory, dir->d_name);
      printf("%s\n", buffer);
    }
  }
  else
    fprintf(stderr, "failed to open configuration folder\n");
}
